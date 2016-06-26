--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 6/14/16
-- Time: 7:25 PM
-- To change this template use File | Settings | File Templates.
--

--[[
-- Inputs:
--      -   Le nombre d'objets qui sont devant moi et dont j'ai besoin pour mon élévation
--      -   Le nombre de nourriture que j'ai dans mon inventaire
--      -   Le nombre de nourriture qu'il y a sur ma case
--      -   Le nombre de joueurs devant moi
--      -   Pourcentage d'objets necessaires pour l'incantation complete
--      -   SearchMode
--
-- Outputs:
--      -   Avance
--      -   Tourne à droite
--      -   Tourne à gauche
--      -   Se Nourrir
--      -   Processus d'incantation => (prendre ressources, poser ressources, broadcast)
--      -   Prendre ressources necessaire
--
--  todo modification sur les outputs au niveau de 'se nourrir'
--  todo ajouter des actions automatiques:
--      'prendre ressource necessaire'
--      'poser ressource pour incantation' (si nb players sur la case suffisant)
--      'incantation' si les conditions sont ok
 ]]

local path = debug.getinfo(1).source:match("@?(.*/)") or "";

local net = require(path.."neural-network/Network");
local queue = require(path.."Queue");

local neuralNet;
local netActions = {};
local actionQueue = queue.new();
local paramQueu = queue.new();
local pendingActions = queue.new();
local pendingSize = 0;
local searching = 0.0;
local askForElevation = false;

FORWARD = 1
TURN_R = 2
TURN_L = 3
FEED = 4
INC_PROCESS = 5
TAKE_NEED_R = 6;

function PushAction(action, param, times)
    param = param or "";
    times = times or 1;

    print("push process");
    for i=1, times do
        print("pushing");
        queue.push(actionQueue, action);
        queue.push(paramQueu, param);
    end
    print("push done");
end

function doAction(action, param)
    param = param or "";

    queue.push(pendingActions, action);
    IA:SetParameter(param);
    pendingSize = pendingSize + 1;
    print("doiing '"..action.." "..param.."'");
    return action;
end

local function GetNbOfNeededRessources(fullSight)
    local nb = 0;

    for i=LINEMATE, THYSTAME do
        local localNb = fullSight:GetNbOf(i);

        if (localNb > 0 and IA:NeedRessources(i)) then
            nb = nb + localNb;
        end
    end
    return nb;
end

function OnStart()
    netActions[FORWARD] = function ()
        print("Avance");
        PushAction(MOVE);
    end;
    netActions[TURN_R] = function ()
        print("Tourne a droite");
        PushAction(RIGHT);
    end;
    netActions[TURN_L] = function ()
        print("Tourne a gauche");
        PushAction(LEFT);
    end;
    netActions[FEED] = function ()
        print("Me nourrir");
        PushAction(TAKE, Inventory.GetNameOf(FOOD));
    end;
    netActions[INC_PROCESS] = function ()
        print("Incantation process");
        --For each ressources needed in my inventory drop it
        --For each don't wanted ressources at pos take it
        --Broadcast the message

        local sight = IA:GetSightAt(0);
        local inventory = IA:GetInventory();

        for i=FOOD, THYSTAME do
            local need = IA:GetNbNeededRessources(i);
            local present = sight:GetNbOf(i);
            local have = inventory:GetNbOf(i);

            print("for ressource: "..Inventory.GetNameOf(i).."(present: "..present..", need: "..need..", have: "..have..")");
            if (need > 0 and need - present > 0) then
                if (have >= need - present) then
                    print("Drop "..(need - present).." times");
                    PushAction(DROP, Inventory.GetNameOf(i), need - present);
                else
                    print("Drop "..have.." times");
                    PushAction(DROP, Inventory.GetNameOf(i), have);
                end
            elseif (need - present <= 0) then
                print("Take "..(present - need).." times");
                PushAction(TAKE, Inventory.GetNameOf(i), present - need);
            end
        end
        if (sight:GetNbOf(PLAYER) < IA:GetNbNeededPlayers() + 1) then
            PushAction(BROADCAST, "Incant "..IA:GetLevel(), math.floor(MAPW / 2 + MAPH / 2));
        end
        netActions[TAKE_NEED_R]();
    end;
    netActions[TAKE_NEED_R] = function ()
        print("Prendre ressource necessaire");
        local sight = IA:GetSightAt(0);
        local inventory = IA:GetInventory();

        for i=LINEMATE, THYSTAME do
            local need = IA:GetNbNeededRessources(i);
            local present = sight:GetNbOf(i);
            local have = inventory:GetNbOf(i);

            print("for ressource "..Inventory.GetNameOf(i).." (need: "..need..", present: "..present..", have: "..have..")");
            if (need > 0 and present > 0 and have < need) then
                if (need - have >= present) then
                    print("taking "..present.." times");
                    PushAction(TAKE, Inventory.GetNameOf(i), present);
                else
                    print("taking "..(need - have).." times");
                    PushAction(TAKE, Inventory.GetNameOf(i), need - have);
                end
            else
                print("do nothing");
            end
        end
    end
    local filename = io.read();
    if (filename == "") then
        neuralNet = net.new(6, 6, {2, 5, 2});
    else
        neuralNet = net.deserialize(filename);
    end
end

--[[function CanTakeDropRessource(takeordrop)
    local sigthAtPos = IA:GetSightAt(0);

    for i=LINEMATE, THYSTAME do
        if (IA:NeedRessources(i) and takeordrop(sigthAtPos, i)) then
            return Inventory.GetNameOf(i);
        end
    end
    return nil;
end

function TakeNeedRessource()
    local sight = IA:GetSightAt(0);
    local inventory = IA:GetInventory();

    for i=LINEMATE, THYSTAME do
        local needed = IA:GetNbNeededRessources(i);
        local present = sight:GetNbOf(i);
        local have = inventory:GetNbOf(i);

        if (needed > 0 and present > 0 and have < needed) then
            if (needed - have <= present) then
                PushAction(TAKE, Inventory.GetNameOf(i), needed - have);
            else
                PushAction(TAKE, Inventory.GetNameOf(i), present);
            end
        end
    end
end]]

function OnUpdate()

    if (IA:IsSaturated() or askForElevation or IA:IsIncanting() or pendingSize > 0) then
        return NONE;
    end

    if (IA:IsPossibleToElevate()) then
        askForElevation = true;
        searching = 0.0;
        return doAction(INCANTATION);
    end

    local todo = queue.pop(actionQueue);

    if (todo == nil and pendingSize == 0) then
        local fullSight = IA:GetFullSight();

        net.compute(neuralNet, {
            GetNbOfNeededRessources(fullSight),
            IA:GetInventory():GetNbOf(FOOD),
            IA:GetSightAt(0):GetNbOf(FOOD),
            fullSight:GetNbOf(PLAYER),
            1.0 - IA:ElevationPercentage(),
            searching
        });
        for i=1, #neuralNet.output.neurons do
            if (neuralNet.output.neurons[i].value > 0.75) then
                netActions[i]();
            end
        end;
        todo = queue.pop(actionQueue);
    end
    if (todo == nil) then
        return NONE;
    end
    return doAction(todo, queue.pop(paramQueu));
end

function OnReceive(reqCode, answer)
    local doing = true;

    if (reqCode == BROADCAST and answer ~= "ok") then
        local lvl = answer:match("Incant (%d+)");

        if (lvl ~= nil and tonumber(lvl) == IA:GetLevel()) then
            searching = tonumber(answer:match("message (%d)"));
        end
        return;
    end

    --Si l'action reçue est l'action attendue
    if (reqCode == queue.front(pendingActions)) then
        if (reqCode == BROADCAST) then
            if (answer == "ok") then
                doing = false;
            end
        elseif (reqCode == INCANTATION) then
            if (answer == "elevation en cours" or answer == "ko") then
                doing = false;
                askForElevation = false;
            end
        else
            doing = false;
        end
    end
    if (doing and reqCode == INCANTATION) then
        if (answer:match("niveau actuel : (%d+)") ~= nil) then
            actionQueue = queue.new();
            paramQueu = queue.new();
            pendingSize = 0;
        end
        return;
    end
    if (doing == false) then
        queue.pop(pendingActions);
        pendingSize = pendingSize - 1;
    end
end
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
--      -   Le nombre de nourriture qu'il y a devant moi
--      -   Le nombre de joueurs devant moi
--      -   Pourcentage d'objets necessaires pour l'incantation complete
--      -   SearchMode
--
-- Outputs:
--      -   Avance
--      -   Tourne à droite
--      -   Tourne à gauche
--      -   Prendre
--      -   Poser
--      -   Broadcast pour incantation
 ]]

local path = debug.getinfo(1).source:match("@?(.*/)") or "";

local net = require(path.."neural-network/Network");
local queue = require(path.."Queue");

local neuralNet;
local netActions = {};
local actionQueue = queue.new();
local pendingActions = queue.new();
local doingAction = false;
local searching = 0.0;

function OnStart()
    netActions[1] = MOVE;
    netActions[2] = RIGHT;
    netActions[3] = LEFT;
    netActions[4] = TAKE;
    netActions[5] = DROP;
    netActions[6] = BROADCAST;
    local filename = io.read();
    if (filename == "") then
        neuralNet = net.new(6, 6, {2, 5, 2});
        net.serialize(neuralNet, "lala.json");
    else
        print("deserializing: "..filename);
        neuralNet = net.deserialize(filename);
        net.serialize(neuralNet, "tem.json");
    end
    --load a neural network from a filename
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

function OnUpdate()
    local todo;
    local fullSight = IA:GetFullSight();

    todo = queue.pop(actionQueue);
    if (todo == nil and doingAction == false) then
        print("[-------------nothing-------------]");
        net.compute(neuralNet, {
            GetNbOfNeededRessources(fullSight),
            IA:GetInventory():GetNbOf(FOOD),
            fullSight:GetNbOf(FOOD),
            fullSight:GetNbOf(PLAYER),
            1.0 - IA:ElevationPercentage(),
            searching
        });
        print("------outputs------");
        for i=1, #neuralNet.output.neurons do
            if (neuralNet.output.neurons[i].value > 0.75) then
                print("pushing "..netActions[i]);
                queue.push(actionQueue, netActions[i]);
            end
            print("for action "..netActions[i].." has value "..neuralNet.output.neurons[i].value);
        end
        print("-------------------");
        todo = queue.pop(actionQueue);
    end
    if (todo == nil) then
        return NONE;
    end
    print("todo =====> "..todo);
    if (todo == BROADCAST) then
        IA:SetParameter("Come incant modafukas");
    end
    doingAction = true;
    queue.push(pendingActions, todo);
    return todo;
end

function OnReceive(reqCode, answer)
    print("code: "..reqCode.." => '"..answer.."'");
    if (reqCode == pendingActions[pendingActions.last]) then
        if (reqCode == BROADCAST) then
            if (answer == "ok") then
                doingAction = false;
            end
        elseif (reqCode == INCANTATION) then
            if (answer == "elevation en cours") then
                doingAction = false;
            end
        else
            doingAction = false;
        end
    else
        if (reqCode == BROADCAST) then
            if (answer == "Come incant modafukas") then
                searching = 1.0;
            else
                searching = 0.0;
            end
        end
    end
    if (doingAction == false) then
        queue.pop(pendingActions);
    end
end
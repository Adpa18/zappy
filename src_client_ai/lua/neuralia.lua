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

local neuralNet = net.new(6, 6, {4, 3, 10});
local netActions = {MOVE, RIGHT, LEFT, TAKE, DROP, BROADCAST};
local actionQueue = queue.new();
local doingAction = false;
local pendingAction;
local searching = 0.0;

function OnStart()
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
    if (doingAction) then
        return NONE;
    end

    local todo;
    local fullSight = IA:GetFullSight();

    todo = queue.pop(actionQueue);
    if (todo == nil) then
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
            if (neuralNet.output.neurons[i].value > 0.5) then
                if (netActions[i] == BROADCAST) then
                    IA:SetParameter("Come incant modafukas");
                end
            end
            print();
        end
        print("-------------------");
        todo = queue.pop(actionQueue);
    end
    if (todo == nil) then
        return NONE;
    end
    doingAction = true;
    pendingAction = todo;
    return todo;
end

function OnReceive(reqCode, answer)
    if (reqCode == pendingAction) then
        if (reqCode == BROADCAST) then
            if (answer == "Come incant modafukas") then
                searching = 1.0;
            elseif (answer == "ok") then
                doingAction = false;
            else
                searching = 0.0;
            end
        elseif (reqCode == INCANTATION) then
            doingAction = (answer ~= "elevation en cours");
        else
            doingAction = false;
        end
    end
end
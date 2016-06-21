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
--
-- Outputs:
--      -   Avance
--      -   Tourne à droite
--      -   Tourne à gauche
--      -   Prendre
--      -   Poser
--      -   Broadcast pour incantation
 ]]

local path = debug.getinfo(1).source:match("@?(.*/)");

local net = require(path.."neural-network/Network");
local neuralNet = {}

function OnStart()
    print(IA);
    print(IA:GetSightAt(0):HasObject(FOOD));
    print(IA:GetInventory():GetNbOf(FOOD));
end

function OnUpdate()
    return NONE;
end

function OnReceive()
end

--local net = require "lua/neural-network/Network"
--
-- Created by IntelliJ IDEA.
-- User: gouet_v and wery_a
-- Date: 6/8/16
-- Time: 12:50 PM
-- To change this template use File | Settings | File Templates.
--

local path = "src_client_ai/lua/"

local canAct = true;
local Queue = require (path.."Queue")

local wait = false
local idle = false
local boss = {true, true, true, true, true, true, true, true}

local dataQueue = {}
local serverAnswer = {}
local objectOnMap = {}

function OnStart()
    dataQueue = Queue.new()

    objectOnMap[FOOD] = "nourriture"
    objectOnMap[LINEMATE] = "linemate"
    objectOnMap[DERAUMERE] = "deraumere"
    objectOnMap[SIBUR] = "sibur"
    objectOnMap[MENDIANE] = "mendiane"
    objectOnMap[PHIRAS] = "phiras"
    objectOnMap[THYSTAME] = "thystame"

    serverAnswer[MOVE] = onCallMove
    serverAnswer[LEFT] = onCallMove
    serverAnswer[RIGHT] = onCallMove
    serverAnswer[TAKE] = onCallTake
    serverAnswer[DROP] = onCallDrop
    serverAnswer[LAYEGG] = nil
    serverAnswer[BROADCAST] = onBroadCast
    serverAnswer[INCANTATION] = onIncantation
end

function onIncantation(requestCode, responseServer)
    local level = responseServer:match("niveau actuel : ([0-9])")
    if level then
        canAct = true
        idle = false
        wait = false
        Queue.clear(dataQueue)
        print("debug UP_niveau "..level)
    end
end

function onBroadCast(requestCode, responseServer)
    if responseServer == "ok" then
        canAct = true
        return
    end
    if wait then
        return
    end
    print(responseServer)
    local dir, level = responseServer:match("message ([0-9]), elevate ([0-9])")
    if dir == nil or level == nil then
        print("failed")
        return
    end
    print(dir, level)
    if IA:GetLevel() == tonumber(level) then
    boss[IA:GetLevel() - 1] = false
    if dir == "0" then
        idle = true
        Queue.clear(dataQueue)
    elseif dir == "1" then
        Queue.push(dataQueue, {MOVE, nil})
    elseif dir == "2" then
        Queue.push(dataQueue, {MOVE, nil})
        Queue.push(dataQueue, {LEFT, nil})
        Queue.push(dataQueue, {MOVE, nil})
    elseif dir == "3" then
        Queue.push(dataQueue, {LEFT, nil})
        Queue.push(dataQueue, {MOVE, nil})
    elseif dir == "4" then
        Queue.push(dataQueue, {LEFT, nil})
        Queue.push(dataQueue, {MOVE, nil})
        Queue.push(dataQueue, {LEFT, nil})
        Queue.push(dataQueue, {MOVE, nil})
    elseif dir == "5" then
        Queue.push(dataQueue, {LEFT, nil})
        Queue.push(dataQueue, {LEFT, nil})
        Queue.push(dataQueue, {MOVE, nil})
    elseif dir == "6" then
        Queue.push(dataQueue, {RIGHT, nil})
        Queue.push(dataQueue, {MOVE, nil})
        Queue.push(dataQueue, {RIGHT, nil})
        Queue.push(dataQueue, {MOVE, nil})
    elseif dir == "7" then
        Queue.push(dataQueue, {RIGHT, nil})
        Queue.push(dataQueue, {MOVE, nil})
    elseif dir == "8" then
        Queue.push(dataQueue, {MOVE, nil})
        Queue.push(dataQueue, {RIGHT, nil})
        Queue.push(dataQueue, {MOVE, nil})
    end
    end
    wait = true
end

function onCallDrop(requestCode, responseServer)
    canAct = true
end

function onCallTake(requestCode, responseServer)
    canAct = true
end

function onCallMove(requestCode, responseServer)
    canAct = true
end

function needRessource(ressource)
    if (IA:GetNbNeededRessources(ressource) > IA:GetInventory():GetNbOf(ressource)) then
        return (true)
    end
    return (false)
end

function elevateDarracq()
    if boss[IA:GetLevel() - 1] == false then
        return
    end
    for ressources, ressourcesString in ipairs(objectOnMap) do
        local i = 0
        while i < IA:GetNbNeededRessources(ressources) do
            Queue.push(dataQueue, {DROP, ressourcesString})
            i = i + 1
        end
    end
    Queue.push(dataQueue, {INCANTATION, nil})
end

function moveDarracq()
    local move = math.random(0, 3)
    if (move == 0) then
        Queue.push(dataQueue, {RIGHT, nil})
    elseif (move == 1) then
        Queue.push(dataQueue, {MOVE, nil})
    end
    Queue.push(dataQueue, {MOVE, nil})
end

function onElevate()
    if IA:CanElevate() == false then
        return false
    end

    if IA:GetNbNeededPlayers() ~= IA:GetSightAt(0):GetNbOf(PLAYER) + 1 then
        if boss[IA:GetLevel() - 1] then
            Queue.push(dataQueue, { BROADCAST, "elevate "..IA:GetLevel() })
        end
        return false
    end
    return true
end

function clearCase()
    for ressources, ressourcesString in ipairs(objectOnMap) do
        if IA:GetSightAt(0):HasObject(ressources) then
            Queue.push(dataQueue, {TAKE, ressourcesString})
        end
    end
end

function onSeeAndAct()
    local hasTakeSomething = false

    for ressources, ressourcesString in ipairs(objectOnMap) do
        if (ressources == FOOD or needRessource(ressources))
        and IA:GetSightAt(0):HasObject(ressources) then
            Queue.push(dataQueue, {TAKE, ressourcesString})
            hasTakeSomething = true
        end
    end

    if onElevate() then
        clearCase()
        elevateDarracq()
    elseif (hasTakeSomething == false) then
        moveDarracq()
    end
end

function OnUpdate()
    if canAct == false then
        return NONE
    end
    local value = Queue.pop(dataQueue)

    if value then
        canAct = false
        if (value[2]) then
            IA:SetParameter(value[2])
        end
        return value[1]
    else
        wait = false
    end

    if wait == false and idle == false then
        onSeeAndAct()
    end

    return NONE
end

function OnReceive(requestCode, responseServer)
    if (serverAnswer[requestCode]) then
        serverAnswer[requestCode](requestCode, responseServer)
    else
        print(requestCode)
        print(responseServer)
    end
end

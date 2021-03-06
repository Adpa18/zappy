--
-- Created by IntelliJ IDEA.
-- User: gouet_v and wery_a
-- Date: 6/8/16
-- Time: 12:50 PM
-- To change this template use File | Settings | File Templates.
--

local path = "src_client_ai/lua/"

local Queue = require (path.."Queue")
local canAct = true;

function genToken()
    return math.ceil(os.time() * math.random())
end

local name = 0
local channel = 0
local nbClients = 1

local wait = false
local idle = false

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
    serverAnswer[EXPULSE] = onExpulse

    math.randomseed(os.time())
    name = genToken()
    reset()
    reset_broadcast()
    print("debug name => "..name)
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

-- Callback Start

function OnReceive(requestCode, responseServer)
    if (serverAnswer[requestCode]) then
        serverAnswer[requestCode](requestCode, responseServer)
    else
        print(requestCode)
        print(responseServer)
    end
end

function onCallDrop(requestCode, responseServer)
    reset()
end

function onExpulse(requestCode, responseServer)
    reset()
end

function onCallTake(requestCode, responseServer)
    reset()
end

function onCallMove(requestCode, responseServer)
    reset()
end

function onIncantation(requestCode, responseServer)
    local level = responseServer:match("niveau actuel : ([0-9])")
    if level or responseServer == "ko" then
        reset()
        reset_broadcast()
        Queue.clear(dataQueue)
    end
    if level then
        print("debug UP_niveau "..level)
    end
end

function onBroadCast(requestCode, responseServer)
    if responseServer == "ok" then
        canAct = true
        return
    end
    local dir, type, _name, _channel = responseServer:match("message ([0-9]), (.*) #(.*) #(.*)")
    if dir == nil or type == nil or _name == nil then
        print("failed")
        return
    end
    -- print("debug OK "..name.." => "..responseServer)
    if type == "JOIN" then
        if tonumber(_channel) == name and nbClients < getNbNeededClients() then
            Queue.push(dataQueue, { BROADCAST, "FOLLOW #".._name.." #"..name })
            nbClients = nbClients + 1;
        end
    elseif type == "FOLLOW" then
        Queue.clear(dataQueue)
        if tonumber(_name) == name then
            channel = tonumber(_channel)
        end
    else
        local level = type:match("ELEVATE ([0-9])")
        if tonumber(level) == IA:GetLevel() then
            if channel == 0 and nbClients == 1 then
                Queue.push(dataQueue, { BROADCAST, "JOIN #"..name.." #".._name })
            elseif channel == tonumber(_name) then
                Queue.clear(dataQueue)
                follow_dir(dir)
            end
        end
    end
end

-- Callback End

function reset()
    canAct = true
    idle = false
    wait = false
end

function reset_broadcast()
    channel = 0
    nbClients = 1
end

function getNbNeededClients()
    local lvl = IA:GetLevel()

    if lvl == 0 then
        return 1
    end
    return (lvl + 1 - (lvl + 1) % 2)
end

function needRessource(ressource)
    if (IA:GetNbNeededRessources(ressource) > IA:GetInventory():GetNbOf(ressource)) then
        return (true)
    end
    return (false)
end

function elevateDarracq()
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

    if IA:GetSightAt(0):GetNbOf(PLAYER) + 1 > IA:GetNbNeededPlayers() then
        if channel == 0 then
            Queue.push(dataQueue, { EXPULSE, nil})
        end
        return false
    elseif IA:GetSightAt(0):GetNbOf(PLAYER) + 1 < IA:GetNbNeededPlayers() then
        if channel == 0 then
            Queue.push(dataQueue, { BROADCAST, "ELEVATE "..IA:GetLevel().." #"..name.." #"..name })
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
        if channel == 0 then
            clearCase()
            elevateDarracq()
        end
    elseif (hasTakeSomething == false) then
        moveDarracq()
    end
end

function follow_dir(dir)
    if wait then
        return
    end
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
    wait = true
end

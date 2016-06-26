--
-- Created by a genious
-- User: tavern_d
--

Queue = {};
canAct = true;
teamName = "";
takePriority = true;
findFood = false;

function Queue.new()
    return { first = 0, last = -1 };
end

function Queue.pushBack(list, value)
    local topush = list.first - 1;
    list.first = topush;
    list[topush] = value;
end

function Queue.pushLeft(list, value)
    local last = list.last + 1
    list.last = last
    list[last] = value
end

function Queue.pop(list)
    local last = list.last;
    if list.first > last then
        return nil;
    end
    local value = list[last];
    list[last] = nil;
    list.last = last - 1;
    return value;
end

actionList = Queue.new()
priorityQueue = Queue.new();
plsQueue = Queue.new();

function CreatePath(case)
    local path = Queue.new();
    local f = 3;
    local n = 1;
    local i = 1;
    local y = 0;
    if case == 0 then
        for w = 0, (IA:GetSightAt(y):GetNbOf(FOOD) - 1) do
            Queue.pushBack(path, "TAKE nourriture");
        end
        return path;
    end
    while n <= IA:GetLevel() do
        if i <= case and case <= i + n * 2 then
            for j = 0, n - 1, 1 do
                Queue.pushBack(path, "MOVE");
                y = y + (j + 1) * 2;
                if IA:GetSightAt(y):HasObject(FOOD) == true then
                    for w = 0, (IA:GetSightAt(y):GetNbOf(FOOD) - 1) do
                        Queue.pushBack(path, "TAKE nourriture");
                    end
                end
            end
            if case == y then
                return path;
            elseif case < y then
                Queue.pushBack(path, "LEFT");
                while y > case do
                    Queue.pushBack(path, "MOVE");
                    y = y - 1;
                    if IA:GetSightAt(y):HasObject(FOOD) == true then
                        for w = 0, (IA:GetSightAt(y):GetNbOf(FOOD) - 1) do
                            Queue.pushBack(path, "TAKE nourriture");
                        end
                    end
                end
                return path;
            else
                Queue.pushBack(path, "RIGHT")
                while y < case do
                    Queue.pushBack(path, "MOVE");
                    y = y + 1;
                    if IA:GetSightAt(y):HasObject(FOOD) == true then
                        for w = 0, (IA:GetSightAt(y):GetNbOf(FOOD) - 1) do
                            Queue.pushBack(path, "TAKE nourriture");
                        end
                    end
                end
                return path;
            end
        end
        n = n + 1;
        i = i + f;
        f = f + 2;
    end
end

function OnStart()
    teamName = IA:GetTeamName();
end

function FindRessources(ressource)
    local n = 0;
    local i = 3;
    local find = false;
    while n <= i and find == false do
        local ncase = IA:GetSightAt(n);
        if ncase == nil then
            return NONE;
        end
        if ncase:HasObject(ressource) == true then
            find = true;
            actionList = CreatePath(n);
            for w = 0, (IA:GetSightAt(n):GetNbOf(ressource) - 1) do
                if ressource == LINEMATE then
                    Queue.pushBack(actionList, "TAKE linemate");
                elseif ressource == DERAUMERE then
                    Queue.pushBack(actionList, "TAKE deraumere");
                elseif ressource == SIBUR then
                    Queue.pushBack(actionList, "TAKE sibur");
                elseif ressource == MENDIANE then
                    Queue.pushBack(actionList, "TAKE mendiane");
                elseif ressource == PHIRAS then
                    Queue.pushBack(actionList, "TAKE phiras");
                else
                    Queue.pushBack(actionList, "TAKE thystame");
                end
                return NONE;
            end
        end
        n = n + 1;
    end
    local ran = math.random(0, 2);
    if ran == 0 then
        Queue.pushBack(actionList, "LEFT");
    elseif ran == 1 then
        Queue.pushBack(actionList, "RIGHT");
    else
        for j = 0, IA:GetLevel() do
            Queue.pushBack(actionList, "MOVE");
            if IA:GetSightAt(2):HasObject(FOOD) == true then
                for w = 0, (IA:GetSightAt(2):GetNbOf(FOOD) - 1) do
                    Queue.pushBack(actionList, "TAKE nourriture");
                end
            end
        end
    end
end

function OnUpdate()
    if canAct == true then
        local food = IA:GetInventory():GetNbOf(FOOD);
        local lvl = IA:GetLevel();
        local i = 3;
        local GetEnoughRessources = true;

        if food >= 30 then
            findFood = false;
        end
        for ressource = LINEMATE, THYSTAME do
            if (IA:GetSightAt(0):GetNbOf(ressource) + IA:GetInventory():GetNbOf(ressource)) < IA:GetNbNeededRessources(ressource) then
                GetEnoughRessources = false;
            end
        end
        for n = 2, lvl do
            i = i + (n * 2 + 1);
        end

        local plsAct = Queue.pop(plsQueue);
        if plsAct ~= nil then
            if string.find(plsAct, "MOVE") ~= nil then
                canAct = false;
                return MOVE;
            elseif string.find(plsAct, "RIGHT") ~= nil then
                canAct = false;
                return RIGHT;
            elseif string.find(plsAct, "LEFT") ~= nil then
                canAct = false;
                return LEFT;
            elseif string.find(plsAct, "TAKE") ~= nil then
                if string.find(plsAct, "nourriture") ~= nil then
                    if food >= 40 then
                        return NONE;
                    end
                    IA:SetParameter("nourriture");
                elseif string.find(plsAct, "linemate") ~= nil then
                    IA:SetParameter("linemate");
                elseif string.find(plsAct, "deraumere") ~= nil then
                    IA:SetParameter("deraumere");
                elseif string.find(plsAct, "sibur") ~= nil then
                    IA:SetParameter("sibur");
                elseif string.find(plsAct, "mendiane") ~= nil then
                    IA:SetParameter("mendiane");
                elseif string.find(plsAct, "phiras") ~= nil then
                    IA:SetParameter("phiras");
                elseif string.find(plsAct, "thystame") ~= nil then
                    IA:SetParameter("thystame");
                end
                canAct = false;
                return TAKE;
            end
        end
        if food < 7 or findFood == true then
            -- recherche de food
            local n = 0;
            local find = false;

            priorityQueue = Queue.new();
            findFood = true;
            while n <= i and find == false do
                local ncase = IA:GetSightAt(n);
                if ncase == nil then
                    return NONE;
                end
                if ncase:HasObject(FOOD) == true then
                    find = true;
                    plsQueue = CreatePath(n);
                    return NONE;
                end
                n = n + 1;
            end
            local ran = math.random(0, 2);
            if ran == 0 then
                Queue.pushBack(plsQueue, "LEFT");
                Queue.pushBack(plsQueue, "MOVE");
                Queue.pushBack(plsQueue, "MOVE");
            elseif ran == 1 then
                Queue.pushBack(plsQueue, "RIGHT");
                Queue.pushBack(plsQueue, "MOVE");
                Queue.pushBack(plsQueue, "MOVE");
            else
                for j = 0, (lvl - 1) do
                    Queue.pushBack(plsQueue, "MOVE");
                end
            end
            return NONE;
        end
        local priority = Queue.pop(priorityQueue);
        if priority ~= nil then
            if string.find(priority, "MOVE") ~= nil then
                canAct = false;
                return MOVE;
            elseif string.find(priority, "RIGHT") ~= nil then
                canAct = false;
                return RIGHT;
            elseif string.find(priority, "LEFT") ~= nil then
                canAct = false;
                return LEFT;
            elseif string.find(priority, "EXPULSE") ~= nil then
                canAct = false;
                return EXPULSE;
            elseif string.find(priority, "INCANTATION") ~= nil then
                canAct = false;
                return INCANTATION;
            elseif string.find(priority, "BROADCAST") ~= nil then
                IA:SetParameter(action:match("BROADCAST (.*)"));
                canAct = false;
                return BROADCAST;
            elseif string.find(priority, "LAYEGG") ~= nil then
                canAct = false;
                return LAYEGG;
            elseif string.find(priority, "TAKE") ~= nil then
                if string.find(priority, "nourriture") ~= nil then
                    if food >= 40 then
                        return NONE;
                    end
                    IA:SetParameter("nourriture");
                elseif string.find(priority, "linemate") ~= nil then
                    IA:SetParameter("linemate");
                elseif string.find(priority, "deraumere") ~= nil then
                    IA:SetParameter("deraumere");
                elseif string.find(priority, "sibur") ~= nil then
                    IA:SetParameter("sibur");
                elseif string.find(priority, "mendiane") ~= nil then
                    IA:SetParameter("mendiane");
                elseif string.find(priority, "phiras") ~= nil then
                    IA:SetParameter("phiras");
                elseif string.find(priority, "thystame") ~= nil then
                    IA:SetParameter("thystame");
                end
                canAct = false;
                return TAKE;
            elseif string.find(priority, "DROP") ~= nil then
                if string.find(priority, "nourriture") ~= nil then
                    IA:SetParameter("nourriture");
                elseif string.find(priority, "linemate") ~= nil then
                    IA:SetParameter("linemate");
                elseif string.find(priority, "deraumere") ~= nil then
                    IA:SetParameter("deraumere");
                elseif string.find(priority, "sibur") ~= nil then
                    IA:SetParameter("sibur");
                elseif string.find(priority, "mendiane") ~= nil then
                    IA:SetParameter("mendiane");
                elseif string.find(priority, "phiras") ~= nil then
                    IA:SetParameter("phiras");
                elseif string.find(priority, "thystame") ~= nil then
                    IA:SetParameter("thystame");
                end
                canAct = false;
                return DROP;
            end
        else
            takePriority = true;
        end
        local action = Queue.pop(actionList);
        if action ~= nil then
            if string.find(action, "MOVE") ~= nil then
                canAct = false;
                return MOVE;
            elseif string.find(action, "RIGHT") ~= nil then
                canAct = false;
                return RIGHT;
            elseif string.find(action, "LEFT") ~= nil then
                canAct = false;
                return LEFT;
            elseif string.find(action, "EXPULSE") ~= nil then
                canAct = false;
                return EXPULSE;
            elseif string.find(action, "INCANTATION") ~= nil then
                canAct = false;
                return INCANTATION;
            elseif string.find(action, "LAYEGG") ~= nil then
                canAct = false;
                return LAYEGG;
            elseif string.find(action, "BROADCAST") ~= nil then
                IA:SetParameter(action:match("BROADCAST (.*)"));
                canAct = false;
                return BROADCAST;
            elseif string.find(action, "TAKE") ~= nil then
                if string.find(action, "nourriture") ~= nil then
                    if food >= 40 then
                        return NONE;
                    end
                    IA:SetParameter("nourriture");
                elseif string.find(action, "linemate") ~= nil then
                    IA:SetParameter("linemate");
                elseif string.find(action, "deraumere") ~= nil then
                    IA:SetParameter("deraumere");
                elseif string.find(action, "sibur") ~= nil then
                    IA:SetParameter("sibur");
                elseif string.find(action, "mendiane") ~= nil then
                    IA:SetParameter("mendiane");
                elseif string.find(action, "phiras") ~= nil then
                    IA:SetParameter("phiras");
                elseif string.find(action, "thystame") ~= nil then
                    IA:SetParameter("thystame");
                end
                canAct = false;
                return TAKE;
            elseif string.find(action, "DROP") ~= nil then
                if string.find(action, "nourriture") ~= nil then
                    IA:SetParameter("nourriture");
                elseif string.find(action, "linemate") ~= nil then
                    IA:SetParameter("linemate");
                elseif string.find(action, "deraumere") ~= nil then
                    IA:SetParameter("deraumere");
                elseif string.find(action, "sibur") ~= nil then
                    IA:SetParameter("sibur");
                elseif string.find(action, "mendiane") ~= nil then
                    IA:SetParameter("mendiane");
                elseif string.find(action, "phiras") ~= nil then
                    IA:SetParameter("phiras");
                elseif string.find(action, "thystame") ~= nil then
                    IA:SetParameter("thystame");
                end
                canAct = false;
                return DROP;
            end
        elseif GetEnoughRessources == true then
            local canElevate = true;
            if IA:GetSightAt(0):GetNbOf(FOOD) ~= 0 then
                for w = 1, IA:GetSightAt(0):GetNbOf(FOOD) do
                    Queue.pushBack(actionList, "TAKE nourriture");
                end
            end
            for ressource = LINEMATE, THYSTAME do
                if IA:GetSightAt(0):GetNbOf(ressource) < IA:GetNbNeededRessources(ressource) then
                    for w = 1, (IA:GetNbNeededRessources(ressource) - IA:GetSightAt(0):GetNbOf(ressource)) do
                        if ressource == LINEMATE then
                            Queue.pushBack(actionList, "DROP linemate");
                        elseif ressource == DERAUMERE then
                            Queue.pushBack(actionList, "DROP deraumere");
                        elseif ressource == SIBUR then
                            Queue.pushBack(actionList, "DROP sibur");
                        elseif ressource == MENDIANE then
                            Queue.pushBack(actionList, "DROP mendiane");
                        elseif ressource == PHIRAS then
                            Queue.pushBack(actionList, "DROP phiras");
                        else
                            Queue.pushBack(actionList, "DROP thystame");
                        end
                    end
                    canElevate = false;
                end
                if IA:GetSightAt(0):GetNbOf(ressource) > IA:GetNbNeededRessources(ressource) then
                    for w = 1, (IA:GetSightAt(0):GetNbOf(ressource) - IA:GetNbNeededRessources(ressource)) do
                        if ressource == LINEMATE then
                            Queue.pushBack(actionList, "TAKE linemate");
                        elseif ressource == DERAUMERE then
                            Queue.pushBack(actionList, "TAKE deraumere");
                        elseif ressource == SIBUR then
                            Queue.pushBack(actionList, "TAKE sibur");
                        elseif ressource == MENDIANE then
                            Queue.pushBack(actionList, "TAKE mendiane");
                        elseif ressource == PHIRAS then
                            Queue.pushBack(actionList, "TAKE phiras");
                        else
                            Queue.pushBack(actionList, "TAKE thystame");
                        end
                    end
                    canElevate = false;
                end
            end
            if canElevate == true then
                if IA:GetSightAt(0):GetNbOf(PLAYER) == (IA:GetNbNeededPlayers() - 1) then
                    Queue.pushBack(actionList, "INCANTATION");
                    return NONE;
                elseif IA:GetSightAt(0):GetNbOf(PLAYER) > (IA:GetNbNeededPlayers() - 1) then
                    Queue.pushBack(actionList, "EXPULSE");
                    return NONE;
                else
                    Queue.pushBack(actionList, "BROADCAST " .. "On se regroupe! Equipe " .. teamName .. "! Level " .. lvl);
                    return NONE;
                end
            end
        else
            --recherche des ressources nécessaires
            for ressource = LINEMATE, THYSTAME do
                if (IA:GetInventory():GetNbOf(ressource) - IA:GetNbNeededRessources(ressource)) < 0 then
                    FindRessources(ressource);
                    return NONE;
                end
            end
        end
    end
    return NONE;
end

function CreatePathSound(case)
    if case == 0 then
        Queue.pushBack(priorityQueue, "NONE");
    elseif case == 1 then
        Queue.pushBack(priorityQueue, "MOVE");
        if IA:GetSightAt(2):HasObject(FOOD) == true then
            for w = 0, (IA:GetSightAt(2):GetNbOf(FOOD) - 1) do
                Queue.pushBack(priorityQueue, "TAKE nourriture");
            end
        end
    elseif case == 2 then
        Queue.pushBack(priorityQueue, "MOVE");
        if IA:GetSightAt(2):HasObject(FOOD) == true then
            for w = 0, (IA:GetSightAt(2):GetNbOf(FOOD) - 1) do
                Queue.pushBack(priorityQueue, "TAKE nourriture");
            end
        end
    elseif case == 3 then
        Queue.pushBack(priorityQueue, "LEFT");
    elseif case == 4 then
        Queue.pushBack(priorityQueue, "LEFT");
    elseif case == 5 then
        Queue.pushBack(priorityQueue, "LEFT");
    elseif case == 6 then
        Queue.pushBack(priorityQueue, "RIGHT");
    elseif case == 7 then
        Queue.pushBack(priorityQueue, "RIGHT");
    elseif case == 8 then
        Queue.pushBack(priorityQueue, "MOVE");
        if IA:GetSightAt(2):HasObject(FOOD) == true then
            for w = 0, (IA:GetSightAt(2):GetNbOf(FOOD) - 1) do
                Queue.pushBack(priorityQueue, "TAKE nourriture");
            end
        end
    end
    return;
end

function OnReceive(request, rep)
    if request == MOVE or request == LEFT or request == RIGHT or request == TAKE or request == DROP or request == LAYEGG or request == EXPULSE then
        if request == EXPULSE and string.find(rep, "deplacement") ~= nil then
            actionList = Queue.new();
            takePriority = false;
            Queue.pushBack(priorityQueue, "MOVE");
            local ran = math.random(0, 2);
            if ran == 0 then
                Queue.pushBack(priorityQueue, "MOVE");
            elseif ran == 1 then
                Queue.pushBack(priorityQueue, "LEFT");
            else
                Queue.pushBack(priorityQueue, "RIGHT");
            end
        end
        if rep == "ok" then
            canAct = true;
        elseif rep == "ko" then
            canAct = true;
        end
        return NONE;
    end
    if request == INCANTATION then
        if rep == "ko" then
            canAct = true;
            return NONE;
        elseif rep == "elevation en cours" then
            return NONE;
        else
            canAct = true;
            return NONE;
        end
    end
    if request == BROADCAST then
        if rep == "ok" then
            canAct = true;
            return NONE;
        end
        if takePriority == true and string.find(rep, "On se regroupe!") ~= nil and rep:match("On se regroupe! Equipe (.+)!") == teamName and tonumber(rep:match("! Level ([0-9])")) == IA:GetLevel() then
            -- se diriger vers l'origine du son
            actionList = Queue.new();
            CreatePathSound(tonumber(rep:match("message (%d+),")));
            takePriority = false;
        end
    end
end
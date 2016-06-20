--
-- Created by tavern_d
-- User: tavern_d
--

Queue = {};
canAct = true;

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

actionList = Queue.new();

function OnStart()
    print("start toto");
end

function OnUpdate()
    print("update");
    if (canAct) then
        local food = IA:GetInventory():GetNbOf(FOOD);
        local lvl = IA:GetLevel();
        local i = 3;
        for n = 2, lvl + 1 do
            i = i + (n * 2 + 1);
        end

        -- vider la queue
        local action = actionList:pop();
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
            elseif string.find(action, "RIGHT") ~= nil then
                canAct = false;
                return RIGHT;
            elseif string.find(action, "INCANTATION") ~= nil then
                canAct = false;
                return INCANTATION;
            elseif string.find(action, "LAYEGG") ~= nil then
                canAct = false;
                return LAYEGG;
            elseif string.find(action, "TAKE") ~= nil then
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
                return TAKE;
            elseif string.find(action, "DROP") ~= nil then
                canAct = false;
                return DROP;
            end
        end

        if food < 7 then
            -- recherche de food
            local n = 0;
            local find = false;
            while n <= i and find == false do
                if IA:GetSightAt(n):HasObject(FOOD) == true then
                    actionList = IA:CreatePath(n);
                    return;
                end
                n = n + 1;
            end
            if n > i then
                for j = 0, lvl do
                    actionList:pushBack(MOVE);
                end
            end
            return (LAYEGG);
        end
        return NONE;
    end
end

function OnReceive(request, rep)
    if request == MOVE or request == LEFT or request == RIGHT or request == TAKE or request == DROP or request == ForK or request == STOCK then
        canAct = true;
        if rep == "ko" then
            actionList = Queue.new();
        end
        return;
    end
end

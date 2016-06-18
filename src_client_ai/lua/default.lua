--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 6/8/16
-- Time: 3:39 PM
-- To change this template use File | Settings | File Templates.
--

IA = {}

received = true;

function OnStart()
    print("start");
end

function OnUpdate()
    if (received) then
        received = false;
        return MOVE;
    end
    return NONE;
end

function OnReceive()
    received = true;
end

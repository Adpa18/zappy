--
-- Created by IntelliJ IDEA.
-- User: gouet_v
-- Date: 6/8/16
-- Time: 12:50 PM
-- To change this template use File | Settings | File Templates.
--

canAct = true
serverAnswer = {}

function OnStart()
   serverAnswer[MOVE] = onCallMove
   serverAnswer[LEFT] = onCallMove
   serverAnswer[RIGHT] = onCallMove
   serverAnswer[TAKE] = nil
   serverAnswer[DROP] = nil
   serverAnswer[LAYEGG] = nil
   serverAnswer[BROADCAST] = onReceiveBroadCast
end

function onReceiveBroadCast(requestCode, responseServer)
   print(responseServer)
   if (responseServer == "ok") then
      canAct = true
   else
      local str = responseServer.split(" ")
      for i, v in pairs(str) do
	 print(i, v)
      end
   end
end

function onCallMove(requestCode, responseServer)
   canAct = true
end

function OnUpdate()

   if canAct == false then
      return NONE
   end

   canAct = false
   --IA:SetParameter("toto")
   return BROADCAST;
end

function OnReceive(requestCode, responseServer)
   if (serverAnswer[requestCode]) then
      serverAnswer[requestCode](requestCode, responseServer)
   else
      canAct = true
      print(requestCode)
      print(responseServer)
   end
   --print(requestCode)
   --print(responseServer)
end

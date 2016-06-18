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
      local idx1, idx2 = string.find(responseServer, "message ")
      if (idx1 and idx2) then
	 local substr = string.sub(responseServer, idx2 + 1, idx2 + 1)
	 if (substr == "1") then
	    print("AVANCE")
	 end
	 print(substr)
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
--   IA:SetParameter("toto")
   return BROADCAST;
end

function OnReceive(requestCode, responseServer)
   print(responseServer, requestCode)

   if (serverAnswer[requestCode]) then
      serverAnswer[requestCode](requestCode, responseServer)
   else
   --   canAct = true
      print(requestCode)
      print(responseServer)
   end
   --print(requestCode)
   --print(responseServer)
end

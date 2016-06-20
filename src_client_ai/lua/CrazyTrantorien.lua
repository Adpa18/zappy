--
-- Created by IntelliJ IDEA.
-- User: gouet_v
-- Date: 6/8/16
-- Time: 12:50 PM
-- To change this template use File | Settings | File Templates.
--

canAct = true
serverAnswer = {}
msg = nil

local path = "src_client_ai/lua/"

queue = require (path.."Queue")

function OnStart()
   serverAnswer[MOVE] = onCallMove
   serverAnswer[LEFT] = onCallMove
   serverAnswer[RIGHT] = onCallMove
   serverAnswer[TAKE] = onTakeObj
   serverAnswer[DROP] = onDropObj
   serverAnswer[LAYEGG] = nil
   serverAnswer[4] = onCallSee
   serverAnswer[BROADCAST] = onReceiveBroadCast
   queue.new()
end

function onReceiveBroadCast(requestCode, responseServer)

   if (responseServer == "ok") then
      canAct = true
   else
      local idx1, idx2 = string.find(responseServer, "message ")
      if (idx1 and idx2) then
	 local substr = string.sub(responseServer, idx2 + 1, idx2 + 1)
	 if (substr == prevBroadCast) then
	    msg = MOVE
	    return
	 end

	 if (substr == "1") then
	  --  print("AVANCE")
	  --  msg = MOVE
	    return
	   -- msgNext = BROADCAST
	   -- msgNext = BROADCAST
	 elseif (substr == "6" or substr == "7" or substr == "8" or substr == "5") then
	 --   msg = RIGHT
	 --   print("RIGHT")
	 else
	 --   print("GO BACK")
	 --   msg = LEFT
	 end

      end
   end
end

function onCallMove(requestCode, responseServer)
   canAct = true
end

function onCallSee(requestCode, responseServer)
   canAct = true
end

function onTakeObj(requestCode, responseServer)
   canAct = true
end

function onDropObj(requestCode, responseServer)
   canAct = true
end

function OnUpdate()

   if canAct == false then
      return NONE
   end

   if (IA:GetSightAt(0)) then
      print("TOTO")
      print(IA:GetSightAt(0))
      -- print(IA:GetSightAt(0):HasObject(FOOD))
   else
      canAct = false
      return MOVE
   end

   return (NONE)
   --IA:SetParameter("toto")
   --return msg;
end

function OnReceive(requestCode, responseServer)
   if (serverAnswer[requestCode]) then
      serverAnswer[requestCode](requestCode, responseServer)
   else
      print(requestCode)
      print(responseServer)
   end
end

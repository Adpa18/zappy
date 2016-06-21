--
-- Created by IntelliJ IDEA.
-- User: gouet_v
-- Date: 6/8/16
-- Time: 12:50 PM
-- To change this template use File | Settings | File Templates.
--

serverAnswer = {}
canAct = true

function onCallMove(requestCode, responseServer)
   canAct = true
end

function onCallExpulse(requestCode, responseServer)
   canAct = true
end

function OnStart()
   serverAnswer[MOVE] = onCallMove
   serverAnswer[LEFT] = onCallMove
   serverAnswer[RIGHT] = onCallMove
   serverAnswer[TAKE] = nil
   serverAnswer[DROP] = nil
   serverAnswer[LAYEGG] = nil
   serverAnswer[BROADCAST] = nil
   serverAnswer[EXPULSE] = onCallExpulse
end

function OnUpdate()

   if canAct == false then
      return NONE
   end

   canAct = false
   local i = 0
   while (IA:GetSightAt(i)) do
      if (IA:GetSightAt(i):GetNbOf(PLAYER) > 1) then
	 print("ENTER")
      end
      i = i + 1
   end
   --if (IA:GetSightAt(0):GetNbOf(FOOD) == 0 
   return EXPULSE
end

function OnReceive(requestCode, responseServer)
   if (serverAnswer[requestCode]) then
      serverAnswer[requestCode](requestCode, responseServer)
   else
      print(requestCode)
      print(responseServer)
   end
end


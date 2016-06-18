--
-- Created by a genious
-- User: tavern_d
--

Queue = {};
actionList = Queue.new()
canAct = true;
teamName = GetTeamName();

function Queue.new()
   return {first = 0, last = -1};
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

function CreatePath(case)
   local path = Queue.new();
   local n = 1;
   local i = 1;
   local y = 0;
   if case == 0 then
      return path;
   end
   while n <= 7 do
      if i <= case && case <= i + n * 2 then
	 for j = 0, n , +1 do
	    path:pushBack("MOVE");
	    y = y + (j + 1) * 2;
	    if GetSightAt(y):HasObject(FOOD) == true then
	       path:pushBack("TAKE nourriture");
	    end
	 end
	 if case == (i + (i + n * 2)) / 2 then
	    return path;
	 elseif case < (i + (i + n * 2)) / 2 then
	    path:pushBack("LEFT");
	    for j = 0, (i + (i + n * 2)) / 2 - case, +1 do
	       path:pushBack("MOVE");
	       y = y - 1;
	       if GetSightAt(y):HasObject(FOOD) == true then
		  path:pushBack("TAKE nourriture");
	    end
	 else
	    path:pushBack("RIGHT")
	    for j = 0, case - (i + (i + n * 2)) / 2, +1 do
	       path:pushBack("MOVE");
	       y = y + 1;
	       if GetSightAt(y):HasObject(FOOD) == true then
		  path:pushBack("TAKE nourriture");
	    end
	 end
	 return path;
      end
      n = n + 1;
   end
end

function OnStart()
end

function OnUpdate()
   if (canAct) then
      local food = GetInventory():GetNbOf(FOOD);
      local lvl = GetLevel();
      local i = 3;
      for n = 2, lvl + 1, +1 do
	 i = i + (n * 2 + 1);
      end
      
      -- vider la queue
      local action = actionList:pop();
      if action != nil then
	 if string.find(action, "MOVE") != nil then
	    canAct = false;
	    return MOVE;
	 elseif string.find(action, "RIGHT") != nil then
	    canAct = false;
	    return RIGHT;
	 elseif string.find(action, "LEFT") != nil then
	    canAct = false;
	    return LEFT;
	 elseif string.find(action, "RIGHT") != nil then
	    canAct = false;
	    return RIGHT;
	 elseif string.find(action, "SEE") != nil then
	    canAct = false;
	    return SEE;
	 elseif string.find(action, "INCANTATION") != nil then
	    canAct = false;
	    return INCANTATION;
	 elseif string.find(action, "LAYEGG") != nil then
	    canAct = false;
	    return LAYEGG;
	 elseif string.find(action, "TAKE") != nil then
	    if string.find(action, "nourriture") != nil then
	       SetParameter("nourriture");
	    elseif string.find(action, "linemate") != nil then
	       SetParameter("linemate");
	    elseif string.find(action, "deraumere") != nil then
	       SetParameter("deraumere");
	    elseif string.find(action, "sibur") != nil then
	       SetParameter("sibur");
	    elseif string.find(action, "mendiane") != nil then
	       SetParameter("mendiane");
	    elseif string.find(action, "phiras") != nil then
	       SetParameter("phiras");
	    elseif string.find(action, "thystame") != nil then
	       SetParameter("thystame");
	    end
	    canAct = false;
	    return TAKE;
	 elseif string.find(action, "DROP") != nil then
	    canAct = false;
	    return DROP;
	 end
      end
      
      if food < 7 then
	 -- recherche de food
	 local n = 0;
	 local find = false;
	 while n <= i && find == false do
	    if GetSightAt(n) == nil then
	       canAct = false;
	       return SEE;
	    end
	    if GetSightAt(n):HasObject(FOOD) == true then
	       actionList = CreatePath(n);
	       return ;
	    end
	    n = n + 1;
	 end
	 if n > i then
	    for j = 0, lvl, +1 do
	       actionList:pushBack(MOVE);
	    end
	 end
      end
      if -- jai les ressources pour mélever
      then
	 -- envoie message de regroupement
      else
	 --recherche des ressources nécessaires
      end
   end
   return NONE;
end

function OnReceive(request, rep)
   if request == MOVE || request == LEFT || request == RIGHT || request == TAKE || request == DROP || request == FORK || request == SEE || request == STOCK then
      canAct = true;
      if rep == "ko" then
	 actionList = Queue.new();
      end
      return ;
   end
   if request == INCANTATION then
      if rep == "ko" then
	 canAct = true;
	 actionList = Queue.new();
	 return ;
      elseif rep == "elevation en cours" then
	 return ;
      else
	 canAct = true;
	 return ;
      end
   end
   if request == BROADCAST then
      if string.find(rep, "On fait l'appel!") != nil then
	 -- message de présence
      end
      if -- message de présence
      then
	 -- ajout de l'id dans le tableau d'équipe si id pas présente dedans
      end
      if -- message de regroupement && lvl requis
      then
      -- se diriger vers l'origine du son
      end
   end
end

-- BROADCAST --
-- On se regroupe! Equipe nom_de_team! Level lvl_ia

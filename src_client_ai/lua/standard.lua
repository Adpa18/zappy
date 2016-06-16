--
-- Created by a genious
-- User: tavern_d
--

-- GetInventory renvoie l'inventaire (classe)
-- GetSightAt renvoie la liste dobjet sur la case envoyée en paramètre
-- SetParameter ???

-- WHAT I NEED
-- savoir ce que je vois
-- mon niveau

id = math.random(0, 2000000000)
Queue = {};
actionList = Queue.new()

function Queue.new()
   return {first = 0, last = -1};
end

function Queue.push(list, value)
   local topush = list.first - 1;
   list.first = topush;
   list[topush] = value;
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
	    path.push(MOVE);
	    y = y + (j + 1) * 2;
	    if GetSightAt(y):HasObject(FOOD) == true then
	       path.push(TAKE FOOD);
	    end
	 end
	 if case == (i + (i + n * 2)) / 2 then
	    return path;
	 elseif case < (i + (i + n * 2)) / 2 then
	    path.push(LEFT);
	    for j = 0, (i + (i + n * 2)) / 2 - case, +1 do
	       path.push(MOVE);
	       y = y - 1;
	       if GetSightAt(y):HasObject(FOOD) == true then
		  path.push(TAKE FOOD);
	    end
	 else
	    path.push(RIGHT)
	    for j = 0, case - (i + (i + n * 2)) / 2, +1 do
	       path.push(MOVE);
	       y = y + 1;
	       if GetSightAt(y):HasObject(FOOD) == true then
		  path.push(TAKE FOOD);
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
   local food = GetInventory():GetNbOf(FOOD);
   local lvl = GetLevel();
   local i = 3;
   for n = 2, lvl + 1, +1 do
      i += n * 2 + 1;
   end
   if food < 7 then
      -- recherche de food
      local n = 0;
      local find = false;
      while n <= i && find == false do
	 if GetSightAt(n):HasObject(FOOD) == true then
	    -- chemin pour atteindre la case --
	    actionList = CreatePath(n);
	 end
      end
   end
   if -- assez de joueur dans mon équipe pour mélever
   then
      if -- jai les ressources pour mélever
      then
	 -- envoie message de regroupement
      else
	 --recherche des ressources nécessaires
      end
   else
      -- ponte d'un oeuf
   end
end

function OnReceive()
   if -- message dappel
   then
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

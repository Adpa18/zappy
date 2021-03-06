--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 6/16/16
-- Time: 7:28 PM
-- To change this template use File | Settings | File Templates.
--

local Queue = {};

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

function Queue.empty(list)
   local last = list.last;
   if list.first > last then
      return true;
   end
   local value = list[last];
   if value then
      return false
   end
   return true
end

function Queue.clear(list)
   while (Queue.pop(list)) do
   end
end

function Queue.front(list)
    return list[list.last];
end

return Queue;

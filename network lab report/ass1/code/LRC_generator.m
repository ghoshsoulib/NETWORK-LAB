function [data] = LRC_generator(data)
if mod(sum(data),2) ~= 0
    data = [data 1];
else
    data = [data 0];
end
end


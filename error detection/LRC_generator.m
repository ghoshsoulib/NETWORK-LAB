function [data] = LRC_generator(data)
%UNTITLED9 Summary of this function goes here
%   Detailed explanation goes here
if mod(sum(data),2) ~= 0
    data = [data 1];
else
    data = [data 0];
end

end


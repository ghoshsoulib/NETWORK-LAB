function [error] = LRC_detector(data)
%UNTITLED10 Summary of this function goes here
%   Detailed explanation goes here

ss = mod(sum(data(1:(length(data)-1))),2);
error = 0;
if (ss == 1 && data(length(data)) == 0) || (ss == 0 && data(length(data)) == 1)
    error = 1;
end

end


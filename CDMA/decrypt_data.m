function [data] = decrypt_data(channel_data,code)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

data = sum((channel_data.*code))/length(code);
end


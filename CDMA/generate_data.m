function [data_out] = generate_data(code_list,data)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
len = length(data);
for i = 1:len
    code_list(i,:) = code_list(i,:)*data(i);
end
data_out = sum(code_list);
end


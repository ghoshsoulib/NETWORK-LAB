function [code_word] = error_geenerat(arr, code_word)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

l = length(arr);

for i = 1:l
    code_word(arr(i)) = ~code_word(arr(i));
end

end


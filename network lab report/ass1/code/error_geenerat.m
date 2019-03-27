function [code_word] = error_geenerat(arr, code_word)
l = length(arr);
for i = 1:l
    code_word(arr(i)) = ~code_word(arr(i));
end
end


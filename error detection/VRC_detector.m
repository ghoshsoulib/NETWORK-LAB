function [matt,error] = VRC_detector(code_word, frame_size)
%UNTITLED13 Summary of this function goes here
%   Detailed explanation goes here

l = length(code_word);
r = l/frame_size;

matt = [];
for i = 1:r
    x = frame_size*(i-1) + 1;
    y = frame_size*i;
    matt = [matt; code_word(x:y)];
end

[r,c] = size(matt);
error = 0;
for i = 1:c
    ss = sum(matt(:,i)) - matt(r,i);
    
    if mod(ss,2) == 1 && matt(r,i) == 0
        error = 1;
    end
    
    if mod(ss,2) == 0 && matt(r,i) == 1
        error = 1;
    end
end

end


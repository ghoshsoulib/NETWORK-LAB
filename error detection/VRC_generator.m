function [final, code_word] = VRC_generator(data, frame_size)
%UNTITLED12 Summary of this function goes here
%   Detailed explanation goes here

final = data_to_mat(data,frame_size);

[r,c] = size(final);

for i = 1:c
    ss = sum(final(:,i));
    
    if mod(ss,2) == 1
        final(r+1,i) = 1;
    else 
        final(r+1,i) = 0;
    end
end

code_word = [];
for i = 1:(r+1)
    code_word = [code_word final(i,:)];
end

end


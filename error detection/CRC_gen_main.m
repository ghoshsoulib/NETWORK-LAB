function [fin,cw] = CRC_gen_main(data, frame_size, G)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

[final] = data_to_mat(data,frame_size);
[r,~] = size(final);
fin = [];
cw = [];
%G = [1 0 1 1];
for i = 1:r
    c = final(i,:);
    msg_tx = CRC_generator(G,c);
    fin = [fin; msg_tx];
end

[r,~] = size(fin);

for i = 1:r
    cw = [cw fin(i,:)];
end
    
end
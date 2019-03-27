function [fin,cw] = CRC_gen_main(data, frame_size, G)
[final] = data_to_mat(data,frame_size);
[r,~] = size(final);
fin = [];
cw = [];
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
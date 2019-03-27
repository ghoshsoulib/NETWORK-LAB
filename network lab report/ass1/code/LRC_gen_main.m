function [fin,cw] = LRC_gen_main(data, frame_size)
[final] = data_to_mat(data,frame_size);
[r,~] = size(final);
fin = [];
cw = [];
for i = 1:r
    c = final(i,:);
    x = LRC_generator(c);
    fin = [fin; x];
end
[r,~] = size(fin);
for i = 1:r
    cw = [cw fin(i,:)];
end
end


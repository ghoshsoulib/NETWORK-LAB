function [final] = data_to_mat(data,frame_size)
%UNTITLED11 Summary of this function goes here
%   Detailed explanation goes here

l = length(data);
res = mod(l,frame_size);

if res ~= 0
    x = zeros([1 (frame_size-res)]);
    data = [x data];
end
l = length(data);
num_frames = l/frame_size;

final = [];

for i = 1:num_frames
    x = frame_size*(i-1) + 1;
    y = frame_size*i;
    final = [final; data(x:y)];
end

end


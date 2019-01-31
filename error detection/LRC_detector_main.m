function [error] = LRC_detector_main(data, frame_size)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

[final] = data_to_mat(data,frame_size+1);

[r,~] = size(final);
error = 0;
for i = 1:r
    c = final(i,:);
    err = LRC_detector(data);
    if err ~= 0
        error = 1;
        break;
    end
end


end


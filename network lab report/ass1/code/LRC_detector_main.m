function [error] = LRC_detector_main(data, frame_size)
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


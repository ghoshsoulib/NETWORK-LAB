function [error] = CRC_detector_main(data, frame_size, G)
[final] = data_to_mat(data,frame_size+length(G)-1);
[r,~] = size(final);
error = 0;
for i = 1:r
    c = final(i,:);
    err = CRC_detector(G,c);
    if err ~= 0    
        error = 1;       
        break;
    end
end
end

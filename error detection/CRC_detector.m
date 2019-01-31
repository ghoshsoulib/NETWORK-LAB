function [final] = CRC_detector(G,input_codeword)
%UNTITLED7 Summary of this function goes here
%   Detailed explanation goes here
checks = 1;
count_noerror=0;count_error=0;
len_msg = length(input_codeword) - length(G) + 1;
len_G = length(G);
for p=1:checks
    msg=input_codeword;
    for k=1:len_msg
        if G(1)==msg(1)
            for m=1:len_G
                msg(m)=xor(msg(m),G(m));           
            end
        end
        msg=circshift(msg,[0 -1]);
       
    end
    rem=msg;
   
    if rem==0
        count_noerror=count_noerror+1;              
    else
        count_error=count_error+1;
    end
end

final = count_error;
end


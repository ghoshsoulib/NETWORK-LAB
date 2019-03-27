function [msg_tx] = CRC_generator(G,data)
len_G=length(G);                                            
frame = length(data);
checks = 1;                 
msg_bits=frame/checks;                        
y=msg_bits;
z=1;
for p=1:checks
    msg_in=data(z:y);                              
    len_msg=length(msg_in);
    for k=1:len_G-1
        msg_in(len_msg+k)=0;                      
    end
    msg=msg_in;
    check=zeros;
    for k=1:len_msg
        if G(1)==msg(1)
            for m=1:len_G
                msg(m)=xor(msg(m),G(m));            
            end
        end
        msg=circshift(msg,[0 -1]);
    end
    msg_in(len_msg+1:end)=msg(1:len_G-1);        
    msg_tx=msg_in;
end
end


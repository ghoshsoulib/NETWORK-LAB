function [s] = cs_detector(wordSize,code_word)
Din = code_word;
[m, n]=size(Din);
N=n/wordSize;
copy=zeros(N,wordSize);
for i=0:N-1
    for j=1:wordSize
     copy(i+1,j)=Din(wordSize*i+j);
    end
end
checksum=0;
for k=1:N
    checksum=checksum+bin2dec(num2str(copy(k,:)));
end
d=checksum;
re=zeros(1,N*wordSize);
for i=1:N*wordSize    
    re(i)=mod(d,2);
    d=d-re(i);
    d=d/2; 
end
 re=fliplr(re);
 wrap=zeros(N,wordSize);
for i=0:N-1
    for j=1:wordSize
     wrap(i+1,j)=re(wordSize*i+j);
    end
end
checksumm=0;
for k=1:N
    checksumm=checksumm+bin2dec(num2str(wrap(k,:)));
end
d=checksumm;
re=zeros(1,wordSize);
for i=1:wordSize
    re(i)=mod(d,2);
    d=d-re(i);
    d=d/2; 
end
 re=fliplr(re);
 CheckSumToBeTransmitted=~re;
 ss = sum(CheckSumToBeTransmitted);
 if ss == 0
     s = 0;
 else
     s = 1;
 end
end



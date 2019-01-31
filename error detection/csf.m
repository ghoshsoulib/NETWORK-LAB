function [CheckSumToBeTransmitted] = csf(wordSize,Din)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

%wordSize=4;
%Din=input('Input the data string of lenght multiple of 16 bit:');
%Din = [1 0 0 1 1 1 0 0];
[m, n]=size(Din);
% Making block of data
N=n/wordSize;
copy=zeros(N,wordSize);
for i=0:N-1
    for j=1:wordSize
     copy(i+1,j)=Din(wordSize*i+j);
    end
end
% Finding Sum
checksum=0;
for k=1:N
    checksum=checksum+bin2dec(num2str(copy(k,:)));
end
%Decimal to binary
d=checksum;
re=zeros(1,N*wordSize);
for i=1:N*wordSize    
    re(i)=mod(d,2);
    d=d-re(i);
    d=d/2; 
end
 re=fliplr(re);
 % Wrap around
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
% Decimal to binary
d=checksumm;
re=zeros(1,wordSize);
for i=1:wordSize
    re(i)=mod(d,2);
    d=d-re(i);
    d=d/2; 
end
 re=fliplr(re);
 CheckSumToBeTransmitted=~re;
 
end


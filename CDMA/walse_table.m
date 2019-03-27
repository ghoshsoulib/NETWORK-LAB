function [out]=walse_table(codeSize)
siz = codeSize;
codeSize = pow2(ceil(log2(codeSize)));
N=2;
H=[0 0 ; 0 1];
while(N~=codeSize)
    N=N*2;
    H=repmat(H,[2,2]);
    [m,n]=size(H);
    for i=m/2+1:m
        for j=n/2+1:n
            H(i,j)=~H(i,j);
        end
    end
end
[r,c] = size(H);
for i = 1:r
    for j = 1:c
        if H(i,j) == 0
            H(i,j) = 1;
        else
            H(i,j) = -1;
        end
    end
end
out = [];
for i = 1:siz
    out = [out; H(i,:)];
end
end

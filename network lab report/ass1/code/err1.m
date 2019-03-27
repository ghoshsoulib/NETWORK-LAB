function [code_word_LRC,code_word_VRC,code_word_CS, code_word_CRC ] = err1(code_word_LRC,code_word_VRC,code_word_CS, code_word_CRC )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

% no LRC

% code_word_LRC(1) = ~code_word_LRC(1);
% code_word_LRC(2) = ~code_word_LRC(2);
% 
% code_word_VRC(1) = ~code_word_VRC(1);
% code_word_VRC(2) = ~code_word_VRC(2);
% 
% code_word_CS(1) = ~code_word_CS(1);
% code_word_CS(2) = ~code_word_CS(2);
% 
% code_word_CRC(1) = ~code_word_CRC(1);
% code_word_CRC(2) = ~code_word_CRC(2);


% detect by all
code_word_LRC(1) = ~code_word_LRC(1);
code_word_VRC(1) = ~code_word_VRC(1);
code_word_CS(1) = ~code_word_CS(1);
code_word_CRC(1) = ~code_word_CRC(1);



end


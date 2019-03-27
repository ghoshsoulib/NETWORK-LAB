% code_word_LRC = csvread('LRC.csv');
% code_word_VRC = csvread('VRC.csv');
% code_word_CS = csvread('CS.csv');
% code_word_CRC = csvread('CRC.csv');
[~,error_VRC] = VRC_detector(code_word_VRC, vrc_size);
[error_CS] = cs_detector(cs_size,code_word_CS);
[error_LRC] = LRC_detector_main(code_word_LRC,lrc_size);
[error_CRC] = CRC_detector_main(code_word_CRC, crc_size, G);
error = 0;
if error_VRC ~= 0
    fprintf("Error in VRC\n");
    error = 1;
end
if error_LRC ~= 0
    fprintf("Error in LRC\n");
    error = 1;
end
if error_CRC ~= 0
    fprintf("Error in CRC\n");
    error = 1;
end
if error_CS ~= 0
    fprintf("Error in CS\n");
    error = 1;
end
if error == 0
    fprintf("No Error Detected\n");
end


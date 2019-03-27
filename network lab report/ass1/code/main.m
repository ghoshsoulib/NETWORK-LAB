data = csvread('data.csv');
cs_size = 9;
data = pad_data(data,cs_size);
%checksum
cs_size = 9;
final = data_to_mat(data,cs_size);
CSdata = pad_data(data,cs_size);
[CheckSumToBeTransmitted] = csf(cs_size,CSdata);
mat_CS = [final; CheckSumToBeTransmitted];
code_word_CS = [CSdata CheckSumToBeTransmitted];
%VRC
vrc_size = 9;
[mat_VRC, code_word_VRC] = VRC_generator(data, vrc_size);
%LRC
lrc_size = 1;
[mat_LRC,code_word_LRC] = LRC_gen_main(data, lrc_size);
%CRC
G = [1 0 1 1];
crc_size = 3;
[mat_CRC,code_word_CRC] = CRC_gen_main(data, crc_size, G);
% codeword
csvwrite('LRC.csv',code_word_LRC);
csvwrite('VRC.csv',code_word_VRC);
csvwrite('CRC.csv',code_word_CRC);
csvwrite('CS.csv',code_word_CS);
fprintf("The send code word is generated. Code word is stored in the CSV.\n");


% arr = [3 5 6 9 11 12 15 17 18];
% [code_word_CRC] = error_geenerat(arr, code_word_CRC);
% [code_word_LRC] = error_geenerat(arr, code_word_LRC);
% [code_word_VRC] = error_geenerat(arr, code_word_VRC);
% [code_word_CS] = error_geenerat(arr, code_word_CS);

code_word_LRC(1) = ~code_word_LRC(1);
code_word_VRC(1) = ~code_word_VRC(1);
code_word_CS(1) = ~code_word_CS(1);
code_word_CRC(1) = ~code_word_CRC(1);

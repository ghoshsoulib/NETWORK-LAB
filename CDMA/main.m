numberofuser = 4;
[waltable]=walse_table(4);

data = [-1 0 0 1];
[channel_data] = generate_data(waltable,data);
[data_recieved] = decrypt_data(channel_data,waltable(1,:));
#include "protocol.h"
#ifndef CHANNEL_H
#define CHANNEL_H
void delay(int milli_seonds);
void channel_send_1(frame *s);
void channel_recieve_1(frame *r);
void channel_send_2(frame *s);
void channel_recieve_2(frame *r);
void insert_errors(frame *f);
void insert_delay(frame *f);
void to_reciever();
void to_sender();
#endif
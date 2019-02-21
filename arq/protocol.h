#include<sys/types.h>
#include<sys/msg.h>
#include<thread>
#include<condition_variable>
#include<bits/stdc++.h>
#ifndef PROTOCOL_H
#define PROTOCOL_H
#define MSGKEY1 75
#define MSGKEY2 76
#define MSGKEY3 77
#define MSGKEY4 78	
#define MAX_PKT 8
#define CRC_SIZE 4
#define uchar  unsigned char
#define ulong unsigned long
using namespace std;
typedef enum{data=1,ack=2,nak=3} frame_kind;

typedef enum{frame_arrival,send_request,time_out,no_event} event_type;

typedef struct {
	char data[MAX_PKT];
} packet;

typedef long seq_nr;
typedef struct {
	long source_id;
	long dest_id;
	seq_nr frame_no;
	frame_kind type;
	packet info;
	char CRC[CRC_SIZE];
	}frame;

typedef struct{
	long mtype;
	char mtext[256];
}msgform; 
extern int msgId1,msgId2,msgId3,msgId4,len,cur;
extern ifstream fin;
extern string CRC4;
//void setupMessageQueue();
//void sendMessage(string);
//string recieveMessage();
void to_char_array(char * arr,long l);
long to_long(char *arr);
void wait_for_event(event_type *ev);
void frame_to_msgform(frame *f,msgform *buf);
void msgform_to_frame(frame *f,msgform *buf);
void from_physical_layer_sender(frame *r);
void to_physical_layer_sender(frame *s);
void from_physical_layer_reciever(frame *r);
void to_physical_layer_reciever(frame *s);
void channel_recieve(frame* f);
void channel_send(frame* f);
void to_network_layer(packet *p);
void from_network_layer(packet *q);
//void start_timer(seq_nr k); 
//void stop_timer(seq_nr k);
void enable_network_layer();
void disable_network_layer();
#define inc(k) if(k < MAX_SEQ) k =k+1 ; else k=0


#endif

#include "protocol.h"
#include "encoder.h"
event_type event;
std::mutex ostream_lock,l1,l2,l3,l4;
ifstream fin("packets_goback.txt");
int len,cur;
queue<msgform> acks;
msgform ackbuf;
bool timer_running=false;
bool  cond2,cond3;
std::condition_variable cd;
std::mutex mu;
bool request_to_send=true,repeat_flag;
condition_variable cond;
int run_c;
void enable_network_layer(){
	fin.seekg(0,ios::end);
	len=fin.tellg();
	fin.seekg(0,ios::beg);
	return;
}
void from_network_layer(packet *p){
	fin.read((char*)&(p->data),sizeof(p->data));
	cur=fin.tellg();

	return ;
	}
void make_frame(frame *s,packet* buf,seq_nr sn){
	string CRC_codeword;
	s->source_id=3;
	s->dest_id=4;
	s->type=data;
	s->frame_no=sn;
	s->info=*buf;
	CRC_codeword=encodeCRC(string(s->info.data),MAX_PKT);
	memcpy(s->CRC,CRC_codeword.substr(MAX_PKT,CRC_codeword.length()-MAX_PKT).c_str(),sizeof(CRC_SIZE));  

	return;
}
void start_timer(){

	clock_t start_time = clock();
    while (true){
    			l2.lock();
    			
    			if(!(clock() < start_time + 100000) || run_c==0) break;
    			l3.unlock();
    		}
	if(clock()>=start_time+100000){
		event=time_out;
		ostream_lock.lock();
		cout<<"TIME OUT!"<<endl;
   		cout<<"================================================="<<endl;
		ostream_lock.unlock();
		l3.unlock();
	}
	else if(run_c==0){
		timer_running=false;
		l4.unlock();
		}    
    return; 	
}
void is_packet_available(){
   //coord=true;;
  
   while(true){
   		//cout<<"packet"<<endl;
		//if(!timer_running){
			l1.lock();
			//cout<<"packet lock"<<endl;
			//cout.flush();
			if(cur!=len-1) event=send_request;
			else event=no_event;
			if(timer_running){
					//cout<<"timer present"<<endl;
					l2.unlock();
				}
			else{
				l3.unlock();
				//cout<<"no timer "<<endl;	
			}

	}	 
}	
void ack_arrival_notification(){
	while(true){
			l3.lock();
		bool run=run_c;
			if(msgrcv(msgId4,&ackbuf,sizeof(ackbuf.mtext),4,IPC_NOWAIT) != -1){
				if(run)run_c=true;
				event=frame_arrival;
			}
			l4.unlock();
	}
	return;
}
void from_physical_layer_sender(frame *f){
	msgform buf;
	msgform_to_frame(f,&ackbuf);
	return;
}
void to_physical_layer_sender(frame *f){
	msgform buf;
	frame_to_msgform(f,&buf);
	msgsnd(msgId1,&buf,sizeof(buf.mtext),0);
	return;
}



void print_sent_frame(frame *f){
	ostream_lock.lock();
	cout<<"----------------------------------------------------"<<endl;
	cout<<"FRAME SENT"<<endl;
	cout<<"Sender:   "<<f->source_id<<endl;
	cout<<"Type :    "<<f->type<<endl;
	cout<<"Number:   "<<f->frame_no<<endl;
	for(int i=0;i<MAX_PKT;i++) cout<<f->info.data[i];
	cout<<endl;
	cout<<"----------------------------------------------------"<<endl;
	ostream_lock.unlock();
}
void print_resent_frame(frame *f){
	ostream_lock.lock();
	cout<<"----------------------------------------------------"<<endl;
	cout<<"FRAME RESENT"<<endl;
	cout<<"Sender:   "<<f->source_id<<endl;
	cout<<"Type :    "<<f->type<<endl;
	cout<<"Number:   "<<f->frame_no<<endl;
	for(int i=0;i<MAX_PKT;i++) cout<<f->info.data[i];
	cout<<endl;
	cout<<"----------------------------------------------------"<<endl;
	ostream_lock.unlock();
}
void print_acknowledgement(seq_nr SN){
	ostream_lock.lock();
	cout<<"ACK RECIEVED FOR FRAME "<<SN<<endl;
	cout<<"===================================================="<<endl;
	ostream_lock.unlock();
}
void send(){
	frame s,r;
	packet buffer;
	seq_nr Sn=0;
	seq_nr Sf=0;
	seq_nr Sw=7;
	map<seq_nr,frame> outstanding;
	bool timer_start=false;
	l2.lock();
	l3.lock();
	
	l4.lock();
	
	enable_network_layer();
	
	std::thread request_sender(is_packet_available);
	request_sender.detach();
	std::thread ack_notif(ack_arrival_notification);
	ack_notif.detach();
	
	while(true){
		l4.lock();
		if(event== send_request ){
			if(Sn-Sf < Sw){
				from_network_layer(&buffer);
							
				make_frame(&s,&buffer,Sn);			
			
				outstanding[Sn]=s;
				to_physical_layer_sender(&s);
				print_sent_frame(&s);
				Sn=Sn+1;

				if(!run_c){
				run_c=true;
				timer_running=true;
				std::thread timer(start_timer);
				timer.detach();
				}
			}
		}
		else if(event == frame_arrival){
			event=no_event;
			from_physical_layer_sender(&r);
			seq_nr ack_no=r.frame_no;
			if(ack_no>=Sf && ack_no<=Sn){
				print_acknowledgement(ack_no);
				Sf=ack_no;
				if(ack_no ==Sn){
					run_c=false;
					}

			}

		}
		else if(event== time_out){
			run_c=true;
			timer_running=true;
			event=no_event;
			std::thread timer(start_timer);
			timer.detach();
			seq_nr temp=Sf;
			while(temp<Sn){
					frame to_resend=outstanding[temp];
					to_physical_layer_sender(&to_resend);
					print_resent_frame(&to_resend);
					temp=temp+1;

			}
		}		
	l1.unlock();
	}
}
int main(){
	send();
	return 0;
}
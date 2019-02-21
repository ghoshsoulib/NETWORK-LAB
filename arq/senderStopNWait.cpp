#include "protocol.h"
#include "encoder.h"

event_type event;				
msgform ackbuf;
std:: mutex frame_lock,ack_lock,main_lock,timer_lock,ostream_lock;
ifstream fin("packets.txt");					
int len,cur,ack_count=0;
bool timer_running=false;

void enable_network_layer(){      						 
	fin.seekg(0,ios::end);
	len=fin.tellg();
	fin.seekg(0,ios::beg);
	return;
}

void from_network_layer(packet *p){					    
	fin.read((char*)&(p->data),sizeof(p->data));
	cur=fin.tellg();
	cout.flush();
	return ;
	}
void make_frame(frame *s,packet* buf,seq_nr sn){
	
	string CRC_codeword;
	
	s->source_id=1;
	s->dest_id=2;
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
    			timer_lock.lock();
    	//		cout<<"timer_running :"<< clock()-start_time<<endl;
    			if(!(clock() < start_time + 100000) || !timer_running) break;
    			ack_lock.unlock();
    		}
	if(clock()>=start_time+100000){
		event=time_out;
		ostream_lock.lock();
		cout<<"TIME OUT!"<<endl;
   		cout<<"================================================="<<endl;
		ostream_lock.unlock();
		main_lock.unlock();
	}
	else if(!timer_running) ack_lock.unlock();     
    return; 
}
void is_packet_available(){
     while(true){
     		//cout<<"hi";
			frame_lock.lock();
		//	cout<<cur<<" "<<len<<endl;
			if(cur!=len-1) event=send_request;
			else event=no_event;
			//cout<<"packet unloked"<<endl;
			if(timer_running){
					timer_lock.unlock();
			//		cout<<"unlocking timer"<<endl;
					}
			else{
				ack_lock.unlock();
			//	cout<<"unlocking ack"<<endl;
			}
	}
}
void ack_arrival_notification(){
	while(true){
	ack_lock.lock();
	//cout<<"u"<<endl;
	if(msgrcv(msgId4,&ackbuf,sizeof(ackbuf.mtext),2,IPC_NOWAIT) !=-1){
			event=frame_arrival;
		}
	//cout<<"ack unlock"<<endl;
	main_lock.unlock();
	}

	return;
}
void from_physical_layer_sender(frame *f){
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
	cout<<"Type :    ";
	if(f->type==1) cout<<"Data";
	else if(f->type==2) cout<<" Ack";
	else cout<<" Nak";
	cout<<endl;
	cout<<"Number:   "<<f->frame_no<<endl;
	cout<<"Content:  ";
	for(int i=0;i<MAX_PKT;i++) cout<<f->info.data[i];
	cout<<endl;
	cout<<"----------------------------------------------------"<<endl;
	ostream_lock.unlock();
	return;
}

void print_resent_frame(frame *f){
	ostream_lock.lock();
	cout<<"----------------------------------------------------"<<endl;
	cout<<"FRAME RESENT"<<endl;
	cout<<"Sender:   "<<f->source_id<<endl;
	cout<<"Type :    ";
	if(f->type==1) cout<<"Data";
	else if(f->type==2) cout<<" Ack";
	else cout<<" Nak";
	cout<<endl;
	cout<<"Number:   "<<f->frame_no<<endl;
	cout<<"Content:  ";
	for(int i=0;i<MAX_PKT;i++) cout<<f->info.data[i];
	cout<<endl;
	cout<<"----------------------------------------------------"<<endl;
	ostream_lock.unlock();
	return;
}
void print_acknowledgement(seq_nr SN){
	ostream_lock.lock();
	cout<<"ACK RECIEVED FOR FRAME "<<(SN+1)%2<<endl;
	cout<<"===================================================="<<endl;
	ostream_lock.unlock();
	return;
}
void send(){
	frame s,s_copy,r;
	seq_nr sn=0;
	packet buffer;
	bool can_send=true;
	enable_network_layer();
	main_lock.lock();
	ack_lock.lock();
	timer_lock.lock();
	std::thread request_sender(is_packet_available);
	request_sender.detach();
	std::thread ack_notif(ack_arrival_notification);
	ack_notif.detach();

	while(true){
		main_lock.lock();
		//cout<<event<<endl;
		if(event==send_request && can_send){
			//cout<<"Sending"<<endl;
			from_network_layer(&buffer);
			make_frame(&s,&buffer,sn);
			s_copy=s;
			to_physical_layer_sender(&s);
			print_sent_frame(&s);
			timer_running=true;
			std::thread timer(start_timer);
			timer.detach();
			sn=(sn+1)%2;
			can_send=false;		
		}

		if(event==frame_arrival){
			from_physical_layer_sender(&r);
			if(r.frame_no==sn){
				timer_running=false;
				can_send=true;
				print_acknowledgement(sn);
				ack_count++;
				//if(ack_count==len/8) break;   			
			}
		}
		if(event==time_out){
			
			std::thread timer(start_timer);
			timer.detach();
			to_physical_layer_sender(&s);
			print_resent_frame(&s);			
	
		}
		
		frame_lock.unlock();
		
	}
	return;
}

int main(){
	send();
	return 0;
}                  
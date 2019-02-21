#include "protocol.h"
#include "decoder.h"
event_type event=time_out;
msgform framebuf;
bool cond;
std:: mutex ofstream_lock,mu;
void frame_arrival_notification(){
	while(true){
	msgrcv(msgId2,&framebuf,sizeof(framebuf.mtext),3,0);
	//ofstream_lock.lock();
	//cout<<"FRAME HAS ARRIVED!!"<<endl;
	//ofstream_lock.unlock();
	event=frame_arrival;
	}
	return;
}
bool is_corrupted(frame *f){
	string codeword="";
	bool is_corrupt;
	for(int i=0;i<MAX_PKT;i++) codeword.push_back(f->info.data[i]);
	for(int i=0;i<CRC_SIZE;i++) codeword.push_back(f->CRC[i]);

	if(decodeCRC(codeword,MAX_PKT+CRC_SIZE)){
			is_corrupt=true;
			ofstream_lock.lock();
			cout<<"CORRUPT FRAME!!"<<endl;
			cout<<"============================================================"<<endl<<endl;
			ofstream_lock.unlock();
		}
	else {
			is_corrupt=false;
			ofstream_lock.lock();
			//cout<<"				CLEAN FRAME!!					  "<<endl;
			//cout<<"-----------------------------------------------"<<endl;
			ofstream_lock.unlock();
	}
	return is_corrupt;
}
void from_physical_layer_reciever(frame *f){
	//cout<<"channel to reciever"<<endl;
	msgform buf;
	//msgrcv(msgId2,&buf,sizeof(buf),1,0);tingg
	msgform_to_frame(f,&framebuf);
	ofstream_lock.lock();
	cout<<"----------------------------------------------------"<<endl;
	cout<<"FRAME ARRIVED"<<endl;
	cout<<"Sender:   "<<f->source_id<<endl;
	cout<<"Type :    "<<f->type<<endl;
	cout<<"Number:   "<<f->frame_no<<endl;
	cout<<"Content:  ";
	for(int i=0;i<MAX_PKT;i++) cout<<f->info.data[i];
	cout<<endl;
	cout<<"----------------------------------------------------"<<endl;
	//cout<<"frame recieved from physical layer"<<endl;
	//cout.flush();
	ofstream_lock.unlock();
	return;
}
void to_physical_layer_reciever(frame *f){
	msgform buf;
	frame_to_msgform(f,&buf);
	msgsnd(msgId3,&buf,sizeof(buf.mtext),0);
	ofstream_lock.lock();
	cout<<"CLEAN FRAME ,ACK SENT"<<endl;
	cout<<"====================================================="<<endl;
	ofstream_lock.unlock();
}
void make_ack(frame *f,seq_nr Rn){
	f->source_id=4;
	f->dest_id=3;
	f->type=ack;
	f->frame_no=Rn;
	return;
}
void print_recieved_frame(frame *f){

	return;
}
void recieve(){
	frame r,s;
	//event_type event;
	seq_nr Rn=0;
	std::thread frame_arriv(frame_arrival_notification);
	frame_arriv.detach();
	while(true){
		//wait_for_event(&event);
		if(event == frame_arrival){
			event=time_out;
			from_physical_layer_reciever(&r);
			if(is_corrupted(&r)) continue;
			if(r.frame_no == Rn){
					Rn=Rn+1;
					//print_recieved_frame(&r);
					make_ack(&s,Rn);
					to_physical_layer_reciever(&s);				
				}

		}
	}
	return;
}
int main(){
	recieve();
	return 0;
}

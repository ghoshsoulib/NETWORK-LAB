#include "protocol.h"
#include "decoder.h"
event_type event;
msgform framebuf;
std:: mutex arrv_lock,main_lock,ostream_lock;
void frame_arrival_notification(){
	while(true){
	arrv_lock.lock();	
	if(msgrcv(msgId2,&framebuf,sizeof(framebuf.mtext),1,IPC_NOWAIT)!=-1){
		event=frame_arrival;
		}
	else event=no_event;
	main_lock.unlock();
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
			ostream_lock.lock();
			cout<<"CORRUPT FRAME!!					  "<<endl;
			cout<<"============================================================"<<endl<<endl;
			ostream_lock.unlock();
		}
	else is_corrupt=false;
	return is_corrupt;
}
void print_recieved_frame(frame *f){
	ostream_lock.lock();
	cout<<"----------------------------------------------------"<<endl;
	cout<<"FRAME RECIEVED:"<<endl;
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
void from_physical_layer_reciever(frame *f){
	msgform buf;
	msgform_to_frame(f,&framebuf);
	return;
}
void to_physical_layer_reciever(frame *f){
	msgform buf;
	frame_to_msgform(f,&buf);
	msgsnd(msgId3,&buf,sizeof(buf.mtext),0);
	ostream_lock.lock();
	cout<<"CLEAN FRAME ,ACK SENT"<<endl;
	cout<<"====================================================="<<endl;
	ostream_lock.unlock();
}
void make_ack(frame *f,seq_nr Rn){
	f->source_id=2;
	f->dest_id=1;
	f->type=ack;
	f->frame_no=Rn;
	return;
}

void recieve(){
	frame r,s;
	seq_nr Rn=0;
	main_lock.lock();
	std::thread frame_arriv(frame_arrival_notification);
	frame_arriv.detach();
	while(true){
		main_lock.lock();
		if(event==frame_arrival){
			from_physical_layer_reciever(&r);
			print_recieved_frame(&r);
			if(is_corrupted(&r)) goto label;
			if(r.frame_no == Rn) Rn=(Rn+1)%2;
			make_ack(&s,Rn);
			to_physical_layer_reciever(&s);
		}
		label : arrv_lock.unlock();
	}
	return;
}
int main(){
	recieve();
	return 0;
}

#include "channel.h"
std:: mutex ofstream_lock;
int min_delay;
int max_delay;
int error_percent;
void channel_recieve_1(frame *r){
	//cout<<"recieving from sender"<<endl;
	msgform buf;
	msgrcv(msgId1,&buf,sizeof(buf.mtext),0,0);
	//cout<<buf.mtype<<endl;
	msgform_to_frame(r,&buf);
	ofstream_lock.lock();
	cout<<"----------------------------------------------------"<<endl;
	cout<<"FROM SENDER"<<endl;
	cout<<"Sender:   "<<r->source_id<<endl;
		cout<<"Type :    ";
	if(r->type==1) cout<<"Data";
	else if(r->type==2) cout<<" Ack";
	else cout<<" Nak";
	cout<<endl;
	cout<<"Number:   "<<r->frame_no<<endl;
	cout<<"Content:  ";
	for(int i=0;i<MAX_PKT;i++) cout<<r->info.data[i];
	cout<<endl;
	cout<<"----------------------------------------------------"<<endl;
	ofstream_lock.unlock();
	//for(int i=0;i<MAX_PKT;i++)cout<<r->info.data[i];
	return;
}
void channel_send_1(frame *s){
	//cout<<"sending to sender"<<endl;
	msgform buf;
	frame_to_msgform(s,&buf);
	ofstream_lock.lock();
	cout<<"----------------------------------------------------"<<endl;
	cout<<"TO SENDER"<<endl;
	cout<<"Sender:   "<<s->source_id<<endl;
		cout<<"Type :    ";
	if(s->type==1) cout<<"Data";
	else if(s->type==2) cout<<" Ack";
	else cout<<" Nak";
	cout<<endl;
	cout<<"Number:   "<<s->frame_no<<endl;
	cout<<"----------------------------------------------------"<<endl;
	ofstream_lock.unlock();
	msgsnd(msgId4,&buf,sizeof(buf.mtext),0);
	return;
}
void channel_send_2(frame *s){
	//cout<<"sending to reciever"<<endl;
	msgform buf;
	frame_to_msgform(s,&buf);
	ofstream_lock.lock();
	cout<<"----------------------------------------------------"<<endl;
	cout<<"TO RECIEVER"<<endl;
	cout<<"Sender:   "<<s->source_id<<endl;
		cout<<"Type :    ";
	if(s->type==1) cout<<"Data";
	else if(s->type==2) cout<<" Ack";
	else cout<<" Nak";
	cout<<endl;
	cout<<"Number:   "<<s->frame_no<<endl;
	cout<<"Content:  ";
	for(int i=0;i<MAX_PKT;i++) cout<<s->info.data[i];
	cout<<endl;
	cout<<"----------------------------------------------------"<<endl;
	ofstream_lock.unlock();
	msgsnd(msgId2,&buf,sizeof(buf.mtext),0);
	return ;
}
void channel_recieve_2(frame *r){
	//cout<<"recieve from reciever"<<endl;
	msgform buf;
	msgrcv(msgId3,&buf,sizeof(buf.mtext),0,0);
	msgform_to_frame(r,&buf);
	ofstream_lock.lock();
	cout<<"----------------------------------------------------"<<endl;
	cout<<"FROM RECIEVER"<<endl;
	cout<<"Sender:   "<<r->source_id<<endl;
	cout<<"Type :    ";
	if(r->type==1) cout<<"Data";
	else if(r->type==2) cout<<" Ack";
	else cout<<" Nak";
	cout<<endl;
	cout<<"Number:   "<<r->frame_no<<endl;
	cout<<"----------------------------------------------------"<<endl;
	ofstream_lock.unlock();
	return;
}
void insert_error(frame *f){
	bool error;
	for(int i=0;i<MAX_PKT;i++){
		error= (rand()%100 < error_percent);
		if(error) f->info.data[i]=(f->info.data[i]) ^ 1;  	 
	}
	return;
}
void delay(int milli_seconds) 
{ 
  clock_t start_time = clock(); 
    while (clock() < start_time + milli_seconds) ;
    return; 
} 
void insert_delay(){
	int random=rand()%(max_delay-min_delay)+min_delay;
	delay(random);
	return ;
}
void to_reciever(){
	//std::thread t(to_reciever); 
	//t.detach();
	frame s;                                              
	channel_recieve_1(&s);
	std::thread t(to_reciever); 
	t.detach();
	insert_delay();
	insert_error(&s);
	channel_send_2(&s);
	//t.join();
	//std::terminate();
	return ;
}
void to_sender(){
	//std::thread t(to_sender); 
	frame s;
	channel_recieve_2(&s);
	std::thread t(to_sender); 
	t.detach();
	insert_delay();
	channel_send_1(&s);
	//t.join();//std::terminate();
	return;
}

int main(){
	cout<<"minimum delay in channel(micro_secs):";
	cin>>min_delay;
	cout<<"maximum delay in channel(micro_secs):";
	cin>>max_delay;
	cout<<"error rate(percent) of channel";
	cin>>error_percent;
	frame f;
	srand(100);
		 std::thread s_to_r_thread(to_reciever);
		 s_to_r_thread.detach();
		  std:: thread r_to_s_thread(to_sender);
		r_to_s_thread.detach();
		  //s_to_r_thread.join();
		  //r_to_s_thread.join();
	while(true);
	//	cout<< f.source_id<<endl;;
	//cout<<f.dest_id<<endl;;
	//cout<<f.frame_no<<endl;
	//cout<<f.type<<endl;
}
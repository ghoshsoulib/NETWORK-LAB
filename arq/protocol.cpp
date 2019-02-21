#include "protocol.h"
int msgId1=msgget(MSGKEY1,0777|IPC_CREAT);
int msgId2=msgget(MSGKEY2,0777|IPC_CREAT);
int msgId3=msgget(MSGKEY3,0777|IPC_CREAT);
int msgId4=msgget(MSGKEY4,0777|IPC_CREAT);

void frame_to_msgform(frame *f,msgform *buf){
	buf->mtype=f->source_id;
	memcpy(buf->mtext,f,sizeof(*f));
	//buf=(msgform*)f;
	return;
}
void msgform_to_frame(frame *f,msgform *buf){
	f->source_id=buf->mtype; 
	memcpy(f,buf->mtext,sizeof(*f));
	//f=(frame *)(buf->mtext);
	//for(int i=0;i<MAX_PKT;i++)cout<<f->info.data[i];
	
	return;
}


/*void from_physical_layer_sender(frame *f){
	cout<<"channel to sender"<<endl;
	msgform buf;
	msgrcv(msgId4,&buf,sizeof(buf),2,0);
	msgform_to_frame(f,&buf);
	return;
}*/

/*void from_physical_layer_reciever(frame *f){
	cout<<"channel to reciever"<<endl;
	msgform buf;
	msgrcv(msgId2,&buf,sizeof(buf),1,0);
	msgform_to_frame(f,&buf);
	return;
}*/
/*svoid wait_for_event_sender(event_type *ev){
	//std::thread t(from_physical_layer_sender);
	//t.join(); 
	return;																					
}
void wait_for_event_reciever(event_type *ev){
	//std::thread t(from_physical_layer_sender);
	//t.join();
	return;	
}*/

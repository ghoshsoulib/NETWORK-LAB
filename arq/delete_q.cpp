#include "protocol.h"
int main(){
	msgctl(msgId1,IPC_RMID,0);
	msgctl(msgId2,IPC_RMID,0);
	msgctl(msgId3,IPC_RMID,0);
	msgctl(msgId4,IPC_RMID,0);
}
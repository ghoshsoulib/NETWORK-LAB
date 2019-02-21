#include<bits/stdc++.h>
#include "decoder.h"
using namespace std;
string CRC4="10011";
int bin2dec(string dataword){
	int dec=0;
	for(int i=0;i<dataword.length();i++){
		dec=dec*2+(dataword[i]-48);
	}
	return dec;
}
	
/*void  getChecksum(string bitStream,int segSize){
	cout<<"-----CheckSum-------"<<endl;
	cout<<"===================="<<endl<<"  CODEWORD     SUM"<<endl<<"===================="<<endl;
	int sum=0,wrap;
	string dataword,checkSum;
	for(int i=0;i<bitStream.length();i+=segSize){
		dataword=bitStream.substr(i,segSize);
		sum+=bin2dec(dataword);
		cout<<"  "<<dataword<<"    "<<bin2dec(dataword)<<endl;
		}
	while(sum >=(1<<segSize)){
			wrap= sum >>segSize;
			sum=sum & ((1<<segSize)-1);
			sum+=wrap;
			}
	sum=((~sum) & ((1 <<segSize)-1));
	cout<<"--------------------"<<endl<<"  Checksum =  "<<sum<<endl;
	if(sum) cout<<"  ERROR!";
	else cout<<"  NO ERROR";
	cout<<endl<<"--------------------"<<endl<<endl;
	return;		
	}*/
	
int generateCRCcodeword(const string& dataword){
        string zeroes="",augword=dataword,dividend,divisor;
        for(int i=0;i<CRC4.length();i++){
                zeroes.append("0");
                }
        dividend=augword.substr(0,CRC4.length());
        int pos=CRC4.length()-1;
        while(pos<augword.length()){
                if(dividend[0]=='0') divisor=zeroes;
                else divisor=CRC4;
                for(int i=0;i<CRC4.length();i++){
                        dividend[i]=(char)((dividend[i]-48)^(divisor[i]-48)+48);
                        }
                pos++;
                if(pos<augword.length()){
                        dividend.erase(0,1);
                        dividend.push_back(augword[pos]);
                        }

                }
     
        return bin2dec(dividend);
        }
bool decodeCRC(string bitStream,int segSize){
      //  cout<<"------------CRC decoding-------------"<<endl<<"====================================="<<endl<<"  FRAME         SYNDROME    COMMENT  "<<endl;
	//cout<<"====================================="<<endl;
	string codeword=bitStream,streamCRC="";
	int syndrome;
	bool corrupt;
        //for(int i=0;i<bitStream.length();i+=segSize){
                //codeword=bitStream.substr(i,segSize);
                syndrome=generateCRCcodeword(codeword);
           //    	cout<<"  "<<codeword<<"    "<<syndrome<<"\t     ";
		//if(syndrome==0) cout<<"NO ERROR";
		//else cout<<"ERROR!";
		//cout<<endl;
          //      }
	//cout<<"-------------------------------------"<<endl<<endl;
        if(syndrome == 0) return false;
        else return true;        
        //return ;
        }

/*void decodeVRC(const string & bitStream,int segSize){
          string dataword,codeword="",streamVRC="";
          int onecount;
	  cout<<"-----------VRC decoding-----------"<<endl<<"=================================="<<endl;
	  cout<<"  FRAME      PARITY     COMMENT"<<endl<<"=================================="<<endl;
          for(int i=0;i<bitStream.length();i+=segSize){
                codeword=bitStream.substr(i,segSize);
		cout<<"  "<<codeword<<"\t  ";
                onecount=0;
                for(int k=0;k<segSize;k++){
                        if(codeword[k]=='1') onecount++;
                        }
                if(onecount%2) cout<<1<<"   ERROR";
                else cout<<0<<"   NO ERROR";
                cout<<endl;
                }
	cout<<"----------------------------------"<<endl<<endl;
        return ;
        }

void  decodeLRC(const string & bitStream,int segSize){
          string streamLRC=bitStream;
          string evenParity="";
          string codeword;
	  cout<<"----LRC decoding----"<<endl<<"===================="<<endl<<"  PARITY    COMMENT"<<endl<<"===================="<<endl;
          for(int i=0;i<segSize;i++) evenParity.push_back('0');
          for(int i=0;i<bitStream.length();i+=segSize){
                codeword=bitStream.substr(i,segSize);
                for(int k=0;k<segSize;k++){
                        if(codeword[k]=='1'){
                                if(evenParity[k]=='0') evenParity[k]='1';
                                else evenParity[k]='0';
                        }
                }
		}
	cout<<"  "<<evenParity;
	if(bin2dec(evenParity)) cout<<"   ERROR";
	else cout<<"    NO ERROR";
	cout<<endl;	
        cout<<"--------------------"<<endl<<endl;
         return ;
        }

void getDescriptor(){
	if((msgId=msgget(MSGKEY,0777))==-1){
		perror("msgID");
		exit(1);
		}
	return;
	}
void printRecievedFrames(string streamChecksum,string streamCRC,string streamLRC,string streamVRC,int k){
        //coord.X=0;
        //coord.Y=10;
        //SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
        cout<<"================="<<endl<<"CHECKSUM ENCODING"<<endl<<"================= "<<endl;
        for(int i=0;i<streamChecksum.length();i+=k) cout<<"    "<<streamChecksum.substr(i,k)<<endl;
        cout<<"----------------"<<endl;
        cout<<"================="<<endl<<"   CRC ENCODING"<<endl<<"================="<<endl;
        for(int i=0;i<streamCRC.length();i+=(k+CRC4.length()-1)) cout<<"   "<<streamCRC.substr(i,k+CRC4.length()-1)<<endl;
        cout<<"-----------------"<<endl;

        cout<<"================="<<endl<<"   LRC ENCODING"<<endl<<"================="<<endl;
        for(int i=0;i<streamLRC.length();i+=k) cout<<"    "<<streamLRC.substr(i,k)<<endl;
        cout<<"-----------------"<<endl;

        cout<<"================="<<endl<<"   VRC ENCODING"<<endl<<"================="<<endl;
        for(int i=0;i<streamVRC.length();i+=k+1) cout<<"    "<<streamVRC.substr(i,k+1)<<endl;
        cout<<"-----------------"<<endl;
      	}*/

/*int main(){
	ack.mtype=2;
	char skip;
	int k=8;
	string streamChecksum,streamCRC,streamLRC,streamVRC;
	getDescriptor();
	for(int i=1;i<=5;i++){
		cout<<endl<<endl<<"RECIEVE FRAMES-";
		cin.get(skip);
		streamChecksum=recieveMessage();
		streamCRC=recieveMessage();
		streamLRC=recieveMessage();
		streamVRC=recieveMessage();
	
		msgsnd(msgId,&ack,sizeof(int),0);

		printRecievedFrames(streamChecksum,streamCRC,streamLRC,streamVRC,k);   
		cout<<endl<<endl<<"SHOW RESULTS-";
		cin.get(skip);
		//msgsnd(msgId,&ack,sizeof(int),0);

		getChecksum(streamChecksum,k);
		decodeCRC(streamCRC,k+CRC4.length()-1);
		decodeLRC(streamLRC,k);
		decodeVRC(streamVRC,k+1);
		
		}
	
	return 0;
	
 	}*/


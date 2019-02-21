#include "channel.h"
#include "protocol.h"
#include<bits/stdc++.h>
#include<fstream>
#define MSGKEY 75
using namespace std;
string CRC4="10011";
//COORD coord={0,0}
int bin2dec(string dataword){
	int dec=0;
	for(int i=0;i<dataword.length();i++){
		dec=dec*2+(dataword[i]-48);
	}
	return dec;
}

string dec2bin(int num,int k){
	string checkSum="";
	int bit;
	for(int i=0;i<k;i++){
		bit=num & 1;
		checkSum=(char)(bit+48)+checkSum;
		num=num>>1;
		}
	
	for(int i=0;i<k;i++){
		if(checkSum[i]=='0') checkSum[i]='1';
		else checkSum[i]='0';
	}
	return checkSum;
}

string addChecksum(const string &bitStream,int segSize){
	int sum=0,wrap;
	string dataword,checkSum,streamChecksum=bitStream;
	for(int i=0;i<bitStream.length();i+=segSize){
		dataword=bitStream.substr(i,segSize);
		sum+=bin2dec(dataword);
		}
	
	while(sum >=(1<<segSize)){
			wrap= sum >>segSize;
			sum=sum & ((1<<segSize)-1);
			sum+=wrap;
			}
	
	checkSum=dec2bin(sum,segSize);
	streamChecksum.append(checkSum);
	return streamChecksum;		
}

void addPadding(string & bitStream,int segSize){
	int excessBits=bitStream.length()%segSize;
	if(excessBits==0) return ;
	while(excessBits!=segSize){
		bitStream.append("0");
		excessBits++;
		}
	}

string generateCRCcodeword(const string& dataword){
	string zeroes="",augword=dataword,dividend,divisor;
	for(int i=0;i<CRC4.length();i++){
		zeroes.append("0");
		}
	for(int i=0;i<CRC4.length()-1;i++){
		augword.append("0");
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
	int i=0;
	while(i<CRC4.length()-1){
		augword[augword.length()-1-i]=dividend[dividend.length()-1-i];
		i++;
		}
	return augword;
	}

string encodeCRC(string bitStream,int segSize){
	string dataword,codeword,streamCRC="";
	for(int i=0;i<bitStream.length();i+=segSize){
		dataword=bitStream.substr(i,segSize);
		codeword=generateCRCcodeword(dataword);
		streamCRC.append(codeword);
		}
	return streamCRC;
	}	

string encodeVRC(const string & bitStream,int segSize){
	  string dataword,codeword="",streamVRC="";
	  int onecount;
	  for(int i=0;i<bitStream.length();i+=segSize){
		dataword=bitStream.substr(i,segSize);
		codeword=dataword;
		onecount=0;
		for(int k=0;k<segSize;k++){
			if(dataword[k]=='1') onecount++;
			}
		if(onecount%2) codeword.push_back('1');
		else codeword.push_back('0');
		streamVRC.append(codeword);
		}
	return streamVRC;
	}

string encodeLRC(const string & bitStream,int segSize){
	  string streamLRC=bitStream;
	  string evenParity="";
	  string dataword;
	  for(int i=0;i<segSize;i++) evenParity.push_back('0');
	  for(int i=0;i<bitStream.length();i+=segSize){
		dataword=bitStream.substr(i,segSize);
		for(int k=0;k<segSize;k++){
			if(dataword[k]=='1'){
				if(evenParity[k]=='0') evenParity[k]='1';
				else evenParity[k]='0';
			}
		}
	}
	 streamLRC.append(evenParity);
	 return streamLRC;
	}
	



void printSentFrames(string streamChecksum,string streamCRC,string streamLRC,string streamVRC,int k){
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
        }

/*int main(int argc,char ** argv){
	string  inputStream;
	vector<int> errorPos;
	ifstream input(argv[1]);
	string streamChecksum,streamCRC,streamVRC,streamLRC;
	int k=8;
	setupMessageQueue();
	input>>inputStream;
	
	cout<<endl<<"================="<<endl<<"     INPUT STREAM   "<<endl<<"================="<<endl;
	for(int i=0;i<inputStream.length();i+=k) cout<<"     "<<inputStream.substr(i,k)<<endl;
	cout<<"-----------------"<<endl;
	
	addPadding(inputStream,k);
	
	streamChecksum=addChecksum(inputStream,k);
	
	streamCRC=encodeCRC(inputStream,k);


	
	streamLRC=encodeLRC(inputStream,k);
	
	streamVRC=encodeVRC(inputStream,k);
	
	printSentFrames(streamChecksum,streamCRC,streamLRC,streamVRC,k);
	errorPos.clear();
	errorPos={0,8,16,25};
	transmit(streamChecksum,streamCRC,streamLRC,streamVRC,errorPos,k);
	
	errorPos.clear();
	errorPos={3,6,7};
	transmit(streamChecksum,streamCRC,streamLRC,streamVRC,errorPos,k);

	errorPos.clear();
        errorPos={0,8};
        transmit(streamChecksum,streamCRC,streamLRC,streamVRC,errorPos,k);
	
	errorPos.clear();
	errorPos={4,5};
	transmit(streamChecksum,streamCRC,streamLRC,streamVRC,errorPos,k);
	
	errorPos.clear();
	errorPos={7,15};
	//errorPos={16,24};

	transmit(streamChecksum,streamCRC,streamLRC,streamVRC,errorPos,k);
	msgctl(msgId,IPC_RMID,0);
	return 0;
	}*/
	

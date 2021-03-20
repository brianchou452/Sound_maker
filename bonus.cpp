#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "wav.h"

#include <windows.h>
#include<Mmsystem.h>
#pragma comment(lib, "Winmm.lib")

using namespace std;
WAVHeader header;			// wav �����Y�A�ɮפ����q���ѧO�ɮ�����������
short data[MAXFILESIZE];	// �n��X������I��o
double frequency[MAXNOTE]={};
double frequencyForData[50][MAXNOTE]={};//�ǰechoose() �{��²�� �qmusicData.txtŪ�쪺�W�v
//=========��ƩR�W�� ================
int readNotes(double frequency[MAXNOTE]);
int readWAVdata(short **data_ptr, std::string fn);
void writeWAVfile(short *data, int n, std::string fn);
int genData(double frequency[], int noteNum, short source[], int sourceNum);
void TestPrint(double array[MAXNOTE],int PrintNum);
void TestPrint(int array[MAXNOTE],int PrintNum);
void TestPrint(char array[MAXNOTE],int PrintNum);
void help();
void  choose(char tmp[]);//��J 1 �ϥβ{��²��; ��J 2 �ۤv��J²��
void loading( int i);
//====================================


int main(){




	cout<<"�n���s�y��" << endl<< endl;
	cout<<"�o�O�@�ӥi�H�Φۤv���n���M²�СA����wav�ɪ��{���C"<<endl;
	cout<<"��Jhelp �i�H��o�ϥΤ覡��"<<endl<<endl;
	cout<<"�}�l�s�y�n��: ��J 1 �ϥβ{��²��"<<endl;
	cout<<"              ��J 2 �ۤv��J²��"<<endl;
	char tmp[10]={};
	loading(1);
	cout<<endl;
	cout<<"�� :";
	cin>>tmp;
	choose(tmp);//244 ��

	cout<<"�w����"<<endl;
	loading(0);

	//PlaySound("mySong", NULL, SND_FILENAME | SND_ASYNC);
    //system("PAUSE");
    return 0;


	//TestPrint(frequency,noteNum);



	return 0;
}



// �� cin Ū²�СA�ç�C�ӹ������W�v�g�� frequency[]
// �^�ǭ��ż�
int readNotes(double frequency[MAXNOTE]){
	/* TODO �ȨѰѦ�
	while(cin >> note)
		frequency[???] = ???;
		return numberOfNotes;
		B=493.88Hz 7
		A=440.00Hz 6
		G=392.00Hz 5
		F=349.23Hz 4
		E=329.63Hz 3
		D=293.66Hz 2
		C=261.63Hz 1
	*/
	int numberOfNotes=0;
	int note;
	frequency[MAXNOTE]={};
	cout<<"�}�l��J²�� �� ctrl+z ������J��"<<endl;
	loading(1);
	cout<<endl;
	while(cin >> note){
		double tmp;//�N�Ʀr�s�Jfrequency[numberOfNotes]��
		if(note==0){
			tmp=0;
		}
		if(note==1){
			tmp=261.63;
		}
		if(note==2){
			tmp=293.66;
		}
		if(note==3){
			tmp=329.63;
		}
		if(note==4){
			tmp=349.23;
		}
		if(note==5){
			tmp=392.01;
		}
		if(note==6){
			tmp=440.01;
		}
		if(note==7){
			tmp=493.88;
		}
		frequency[numberOfNotes] =tmp;
		numberOfNotes++;

	}
	return numberOfNotes+1;


	//return -1;
}



// �}�ҦW�� fn �� .wav �ɡA���ɮ׸�T��� header
// �� *data_ptr �ܦ� fn �̭�����ơA�^�Ǹ���I��
int readWAVdata(short **data_ptr, std::string fn){
	std::ifstream file(fn, std::ios::in | std::ios::binary);
	file.read((char *)&header, sizeof(header));

	int sampleNum = header.dataSize / 2;
	*data_ptr = new short[sampleNum];
	file.read((char *)(*data_ptr), sampleNum*sizeof(short));

	file.close();
	return sampleNum;
}



// �N data ���e n �Ӹ���I�g���@�ӦW�� fn �� .wav ��
// �����мg�A���|���b�᭱!
void writeWAVfile(short *data, int n, std::string fn){
	cout<<"�g�Jwavfile��"<<endl;
	WAVheader outHeader = header;
	outHeader.chunkSize = n*16+36;
	outHeader.dataSize = n*16;

	std::ofstream file(fn, std::ios::out | std::ios::binary);
	file.write((char *)&outHeader, sizeof(header));
	file.write((char *)data, sizeof(short)*n);

	file.close();
}


// �ǥ��W�v�M�u���p��n��X�� data ����I
// �^�ǭn��X������I��
int genData(double frequency[], int noteNum, short source[], int sourceNum){
	/* TODO �ȨѰѦ�     int sampleNum = genData(frequency, noteNum, myVoice, myVoiceNum);
	for(int i=0; i<noteNum; i++)
		for(int j=0; j<sourceNum; j++)
			data[i*sourceNum+j] = source[j];
	*/
	cout<<"���ͭ��W��"<<endl;
	int i=1;
	double numpa=(double)i/(double)noteNum;
	cout<<"�V�O�p�⤤"<<setprecision(1)<<numpa*100<<"%";

	for(i=0; i<noteNum; i++){

		double a =frequency[i]/MYFREQ;
		for( int j=0; j<sourceNum; j++){
			int b=(int)(a*j+0.5);
			if(b>sourceNum){
				b=b-sourceNum;
				if(b>sourceNum){
					b=b-sourceNum;
				}
				if(b>sourceNum){
					b=b-sourceNum;
				}
			}
			data[i*sourceNum+j] = source[b];

		}
		numpa=(double)i/(double)noteNum;
		cout << "\r" ;  //clear cout<<"�V�O�p�⤤"<<i/noteNum*100<<"%";
		//system("cls");
		cout<<"�V�O�p�⤤"<<setprecision(3)<<numpa*100<<"%";
		Sleep(30);


	}
	cout << "\r" ;  //clear cout<<"�V�O�p�⤤"<<i/noteNum*100<<"%";
	cout<<"�V�O�p�⤤"<<"100"<<"% !!!";
	cout<<endl;


	return sourceNum * noteNum;
}




void TestPrint(double array[MAXNOTE],int PrintNum){
	for(int i=0;i<=PrintNum;i++){
		cout<<"double array["<<i<<"]="<<array[i]<<endl;
	}
}
void TestPrint(int array[MAXNOTE],int PrintNum){
	for(int i=0;i<=PrintNum;i++){
		cout<<"int array["<<i<<"]="<<array[i]<<endl;
	}
}
void TestPrint(char array[MAXNOTE],int PrintNum){
	for(int i=0;i<=PrintNum;i++){
		cout<<"char array["<<i<<"]="<<array[i]<<endl;
	}
}
void help(){
	cout<< endl<< endl;
	cout<<"�o�O�@�ӥi�H�Φۤv���n���M²�СA����wav�ɪ��{���C"<<endl<<
	"bee.txt:"<<endl<<
	"	�p�e����²�� ������"<<endl<<
	"myVoice.wav:"<<endl<<
	"	�W�v�T�w(�HMYFREQ�w�q�bwav.h)�����n�D���T��"<<endl<<
	"singer.cpp:"<<endl<<
	"	�sĶ�Უ�Ͱ����ɡA���J��²�СA��X�����n�D���T�� mySong.wav"<<endl<<
	"wav.h:"<<endl<<
	"	�� wav.cpp �Ϊ����Y�ɡA�w�q .wav �ɪ��榡"<<endl<<
	"MusicData:"<<endl<<
	"	���֮w�ɮ� ��321��"<<endl<<
	"�]���H�{���\�O�ʲL   ���{���ȭ�windows !!!"<<endl<<
	"�p�Gı�o  �V�O�p�⤤ xx% �ܰQ���i�� 186��R��"<<endl<<
	"�֦����֮w!!! �i�s�W����!!"<<endl<< endl<< endl;
}



void choose(char tmp[]){
	if(strcmp(tmp,"1")==0){
		ifstream music;
		music.open("MusicData.txt");
		stringstream readmusic;
		cout<<"�ϥβ{��²�� ==> ��J 1 ���²��"<<endl;
		cout<<"                 ��J 2 �s�W²��"<<endl;
		loading(1);
		cout<<endl;
		cout<<"�� :";
		int choose;
		cin>>choose;//���²�� or �s�W²��
		string SongName;
		int NumOfSong,NumOfSong2,NumTrash;
		char trash;
		while(music>>NumOfSong){// "�ثe��"<<NumOfSong2<<"���q"
			//cout<<"while"<<NumOfSong<<endl;
			NumOfSong2=NumOfSong;

		}

		cout<<"�ثe��"<<NumOfSong2<<"���q"<<endl;
		music.close();
		if(choose==1){//��J 1 ���²��
			ifstream music;
			music.open("MusicData.txt",ios::out);
			string TMPData;
			string SongName;
			int NoteNum[50];


			int count=0;//Ū�ɲĴX��
			int count2=1;//count2<<". "<<SongName<<endl;
			while(getline(music,TMPData)){
				//cout<<"while"<<count<<endl;
				if(count==0){//�ثe��"<<NumOfSong2<<"���q"
					count++;
					continue;
				}
				if(count%3==1){//song name
					SongName=TMPData;
					cout<<count2<<". "<<SongName<<endl;
				}
				if(count%3==2){//num of note
					istringstream ss(TMPData);
					ss>>NoteNum[count2];
				}
				if(count%3==0){//frequency Data
					char trash='-';
					stringstream ss;
					ss<<TMPData;
					for(int i=0;i<=NoteNum[count2];i++){
						ss>>frequencyForData[count2][i]>>trash;
					}
					count2++;
				}

				count++;
			}

			music.close();
			loading(1);
			cout<<endl;
			cout<<"��J�q���N��:";
			int cintmp=0;
			cin>>cintmp;




			//==============
			short *myVoice;
			int myVoiceNum = readWAVdata(&myVoice, "myVoice.wav");
			// ���� myVoice[i] �i���o myVoice.wav ����i�Ӹ���I

			int sampleNum = genData(frequencyForData[cintmp], NoteNum[cintmp], myVoice, myVoiceNum);

			//TestPrint(myVoice,myVoiceNum);
			for(int i=0;i<=myVoiceNum;i++){
				//cout<<"myVoice["<<i<<"]="<<myVoice[i]<<endl;
			}

			delete [] myVoice;
			writeWAVfile(data, sampleNum, "mySong.wav");
			//=============

			/*/=========test======
			for(int i=0;i<=NoteNum[cintmp];i++){
				cout<<"double array["<<i<<"]="<<frequencyForData[cintmp][i]<<endl;
			}*/



		}
		if(choose==2){//��J 2 �s�W²��
			cout<<"�q���W:";
			cin>>SongName;
			fstream music;
			music.open("MusicData.txt");

			NumOfSong2+=1;
			music<<" "<<NumOfSong2<<endl;
			music.close();
			int notenum=readNotes(frequency);
			if(0==0){
				fstream music("MusicData.txt",ios::app);

				music<<SongName<<endl;
				music<<notenum<<endl;
				for(int i=0;i<=notenum;i++){
					music<<frequency[i]<<"-";
				}
				music<<endl;
				music.close();
			}


		}

	}
	if(strcmp(tmp,"2")==0){
		int noteNum = readNotes(frequency);
		short *myVoice;
		int myVoiceNum = readWAVdata(&myVoice, "myVoice.wav");
		// ���� myVoice[i] �i���o myVoice.wav ����i�Ӹ���I

		int sampleNum = genData(frequency, noteNum, myVoice, myVoiceNum);

		//TestPrint(myVoice,myVoiceNum);
		for(int i=0;i<=myVoiceNum;i++){
			//cout<<"myVoice["<<i<<"]="<<myVoice[i]<<endl;
		}

		delete [] myVoice;
		writeWAVfile(data, sampleNum, "mySong.wav");
	}
	if(strcmp(tmp,"help")==0){
		help();
		loading(1);
		cout<<"�~���誺��J"<<endl;
		cin>>tmp;
		return choose(tmp);
	}
}

void loading(int i){
	if(i==0){
		while(0==0){
			cout<<".     ";
			Sleep(60);
			cout << "\r";
			cout<<"..    ";
			Sleep(60);
			cout << "\r";
			cout<<"...   ";
			Sleep(60);
			cout << "\r" ;
			cout<<" ...  ";
			Sleep(60);
			cout << "\r";
			cout<<"  ... ";
			Sleep(60);
			cout << "\r";
			cout<<"   .. ";
			Sleep(60);
			cout << "\r";
			cout<<"    . ";
			Sleep(60);
			cout << "\r";
			cout<<"      ";
			Sleep(60);

			cout << "\r";
			cout<<".     ";
			Sleep(60);
			cout << "\r";
			cout<<"..    ";
			Sleep(60);
			cout << "\r";
			cout<<"..:   ";
			Sleep(60);
			cout << "\r" ;
			cout<<" .:.  ";
			Sleep(60);
			cout << "\r";
			cout<<"  :.. ";
			Sleep(60);
			cout << "\r";
			cout<<"  ....";
			Sleep(60);
			cout << "\r";
			cout<<"   ...";
			Sleep(60);
			cout << "\r";
			cout<<"    ..";
			Sleep(60);
			cout << "\r";
			cout<<"     .";
			Sleep(60);
			cout << "\r";

		}
	}
	else{
		while(i>=0){
			cout<<".     ";
			Sleep(60);
			cout << "\r";
			cout<<"..    ";
			Sleep(60);
			cout << "\r";
			cout<<"...   ";
			Sleep(60);
			cout << "\r" ;
			cout<<" ...  ";
			Sleep(60);
			cout << "\r";
			cout<<"  ... ";
			Sleep(60);
			cout << "\r";
			cout<<"   .. ";
			Sleep(60);
			cout << "\r";
			cout<<"    . ";
			Sleep(60);
			cout << "\r";
			cout<<"      ";
			Sleep(60);


			i--;

		}
	}


}

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
WAVHeader header;			// wav 的檔頭，檔案中讓電腦識別檔案類型的部份
short data[MAXFILESIZE];	// 要輸出的資料點放這
double frequency[MAXNOTE]={};
double frequencyForData[50][MAXNOTE]={};//傳送choose() 現成簡譜 從musicData.txt讀到的頻率
//=========函數命名區 ================
int readNotes(double frequency[MAXNOTE]);
int readWAVdata(short **data_ptr, std::string fn);
void writeWAVfile(short *data, int n, std::string fn);
int genData(double frequency[], int noteNum, short source[], int sourceNum);
void TestPrint(double array[MAXNOTE],int PrintNum);
void TestPrint(int array[MAXNOTE],int PrintNum);
void TestPrint(char array[MAXNOTE],int PrintNum);
void help();
void  choose(char tmp[]);//輸入 1 使用現成簡譜; 輸入 2 自己輸入簡譜
void loading( int i);
//====================================


int main(){




	cout<<"聲音製造機" << endl<< endl;
	cout<<"這是一個可以用自己的聲音和簡譜，產生wav檔的程式。"<<endl;
	cout<<"輸入help 可以獲得使用方式喔"<<endl<<endl;
	cout<<"開始製造聲音: 輸入 1 使用現成簡譜"<<endl;
	cout<<"              輸入 2 自己輸入簡譜"<<endl;
	char tmp[10]={};
	loading(1);
	cout<<endl;
	cout<<"選 :";
	cin>>tmp;
	choose(tmp);//244 行

	cout<<"已完成"<<endl;
	loading(0);

	//PlaySound("mySong", NULL, SND_FILENAME | SND_ASYNC);
    //system("PAUSE");
    return 0;


	//TestPrint(frequency,noteNum);



	return 0;
}



// 用 cin 讀簡譜，並把每個對應的頻率寫到 frequency[]
// 回傳音符數
int readNotes(double frequency[MAXNOTE]){
	/* TODO 僅供參考
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
	cout<<"開始輸入簡譜 按 ctrl+z 結束輸入喔"<<endl;
	loading(1);
	cout<<endl;
	while(cin >> note){
		double tmp;//將數字存入frequency[numberOfNotes]用
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



// 開啟名為 fn 的 .wav 檔，把檔案資訊放到 header
// 讓 *data_ptr 變成 fn 裡面的資料，回傳資料點數
int readWAVdata(short **data_ptr, std::string fn){
	std::ifstream file(fn, std::ios::in | std::ios::binary);
	file.read((char *)&header, sizeof(header));

	int sampleNum = header.dataSize / 2;
	*data_ptr = new short[sampleNum];
	file.read((char *)(*data_ptr), sampleNum*sizeof(short));

	file.close();
	return sampleNum;
}



// 將 data 的前 n 個資料點寫成一個名為 fn 的 .wav 檔
// 直接覆寫，不會接在後面!
void writeWAVfile(short *data, int n, std::string fn){
	cout<<"寫入wavfile中"<<endl;
	WAVheader outHeader = header;
	outHeader.chunkSize = n*16+36;
	outHeader.dataSize = n*16;

	std::ofstream file(fn, std::ios::out | std::ios::binary);
	file.write((char *)&outHeader, sizeof(header));
	file.write((char *)data, sizeof(short)*n);

	file.close();
}


// 藉由頻率和短音計算要輸出的 data 資料點
// 回傳要輸出的資料點數
int genData(double frequency[], int noteNum, short source[], int sourceNum){
	/* TODO 僅供參考     int sampleNum = genData(frequency, noteNum, myVoice, myVoiceNum);
	for(int i=0; i<noteNum; i++)
		for(int j=0; j<sourceNum; j++)
			data[i*sourceNum+j] = source[j];
	*/
	cout<<"產生音頻中"<<endl;
	int i=1;
	double numpa=(double)i/(double)noteNum;
	cout<<"努力計算中"<<setprecision(1)<<numpa*100<<"%";

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
		cout << "\r" ;  //clear cout<<"努力計算中"<<i/noteNum*100<<"%";
		//system("cls");
		cout<<"努力計算中"<<setprecision(3)<<numpa*100<<"%";
		Sleep(30);


	}
	cout << "\r" ;  //clear cout<<"努力計算中"<<i/noteNum*100<<"%";
	cout<<"努力計算中"<<"100"<<"% !!!";
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
	cout<<"這是一個可以用自己的聲音和簡譜，產生wav檔的程式。"<<endl<<
	"bee.txt:"<<endl<<
	"	小蜜蜂的簡譜 有內建"<<endl<<
	"myVoice.wav:"<<endl<<
	"	頻率固定(以MYFREQ定義在wav.h)的單聲道音訊檔"<<endl<<
	"singer.cpp:"<<endl<<
	"	編譯後產生執行檔，其輸入為簡譜，輸出為單聲道音訊檔 mySong.wav"<<endl<<
	"wav.h:"<<endl<<
	"	給 wav.cpp 用的標頭檔，定義 .wav 檔的格式"<<endl<<
	"MusicData:"<<endl<<
	"	音樂庫檔案 第321行"<<endl<<
	"因本人程式功力粗淺   本程式僅限windows !!!"<<endl<<
	"如果覺得  努力計算中 xx% 很討厭可至 186行刪除"<<endl<<
	"擁有音樂庫!!! 可新增音樂!!"<<endl<< endl<< endl;
}



void choose(char tmp[]){
	if(strcmp(tmp,"1")==0){
		ifstream music;
		music.open("MusicData.txt");
		stringstream readmusic;
		cout<<"使用現成簡譜 ==> 輸入 1 選擇簡譜"<<endl;
		cout<<"                 輸入 2 新增簡譜"<<endl;
		loading(1);
		cout<<endl;
		cout<<"選 :";
		int choose;
		cin>>choose;//選擇簡譜 or 新增簡譜
		string SongName;
		int NumOfSong,NumOfSong2,NumTrash;
		char trash;
		while(music>>NumOfSong){// "目前有"<<NumOfSong2<<"首歌"
			//cout<<"while"<<NumOfSong<<endl;
			NumOfSong2=NumOfSong;

		}

		cout<<"目前有"<<NumOfSong2<<"首歌"<<endl;
		music.close();
		if(choose==1){//輸入 1 選擇簡譜
			ifstream music;
			music.open("MusicData.txt",ios::out);
			string TMPData;
			string SongName;
			int NoteNum[50];


			int count=0;//讀檔第幾行
			int count2=1;//count2<<". "<<SongName<<endl;
			while(getline(music,TMPData)){
				//cout<<"while"<<count<<endl;
				if(count==0){//目前有"<<NumOfSong2<<"首歌"
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
			cout<<"輸入歌曲代號:";
			int cintmp=0;
			cin>>cintmp;




			//==============
			short *myVoice;
			int myVoiceNum = readWAVdata(&myVoice, "myVoice.wav");
			// 此後 myVoice[i] 可取得 myVoice.wav 的第i個資料點

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
		if(choose==2){//輸入 2 新增簡譜
			cout<<"歌曲名:";
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
		// 此後 myVoice[i] 可取得 myVoice.wav 的第i個資料點

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
		cout<<"繼續剛剛的輸入"<<endl;
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

#define MYFREQ 216	// myVoice.wav 的頻率

#define MAXNOTE 65536	// 音符個數限制
#define MAXFILESIZE 1<<28	// 輸出檔案大小限制 512MB

typedef struct WAVheader{
	char RIFF[4];
	int chunkSize;
	char wave[4];
	char format[4];
	int subChunkSize;
	short audioFormat;
	short numChannel;
	int sampleRate;
	int byteRate;
	short blockAlign;
	short bitsPerSample;
	char data[4];
	int dataSize;
} WAVHeader;

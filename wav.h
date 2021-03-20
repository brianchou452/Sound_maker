#define MYFREQ 216	// myVoice.wav ���W�v

#define MAXNOTE 65536	// ���ŭӼƭ���
#define MAXFILESIZE 1<<28	// ��X�ɮפj�p���� 512MB

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

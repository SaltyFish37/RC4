#include "speed.h" 

void test_speed(void){
	printf("���ڿ�ʼ����RC4�㷨���ٶ�...");
	printf("����������ļ���(�粻�ڵ�ǰ�ļ���������������·��):\n"); 
	
	FILE *text;
	FILE *key;	
	unsigned char *K;
	unsigned char S[256];
	unsigned char R[256];
	char KeyStream[256];
	char *CriperText;
	char *PlainText;
	char *DeCriperText;
	
	char buff1[filesize]; 
	fgets(buff1, filesize, stdin);
	if(strlen(buff1) < (filesize - 1)){
		buff1[strlen(buff1) - 1] = '\0';
	}
	
	text = fopen(buff1, "rb");
	long int text_len = 0;
	if(text == NULL){
		printf("file cannot open \n");
		exit(1);
	}else{
    	text_len = get_len(text);//��ȡ�ļ����� 
    	
    	PlainText = (char *)malloc((text_len + 1) * sizeof(char));
    	CriperText = (char *)malloc((text_len + 1) * sizeof(char));
    	DeCriperText = (char *)malloc((text_len + 1) * sizeof(char));
    	
    	PlainText = (char *)memset(PlainText, 0, text_len + 1);
    	CriperText = (char *)memset(CriperText, 0, text_len + 1);
    	DeCriperText = (char *)memset(DeCriperText, 0, text_len + 1);
    	
    	fread(PlainText, sizeof(char), text_len, text);
	}
	fclose(text);
	
	char buff2[filesize];
	printf("��������Կ�ļ���(�粻�ڵ�ǰ�ļ���������������·��):\n");
	fgets(buff2, filesize, stdin);
	if(strlen(buff2) < (filesize - 1)){
		buff2[strlen(buff2) - 1] = '\0';
	}
	key = fopen(buff2, "rb");
	long int key_len = 0;
	if(key == NULL){
		printf("file cannot open \n");
		exit(1);
	}else{
    	key_len = get_len(key);//��ȡ��Կ���� 
    	
    	K = (unsigned char *)malloc((key_len + 1) * sizeof(char));
    	K = (unsigned char *)memset(K, 0, key_len + 1);
    	
    	fread(K, sizeof(char), key_len, key);
	}
	fclose(key);
	
	int i = 0;
	unsigned char *K1;
	unsigned char S1[256];
	unsigned char R1[256];
	char KeyStream1[256];
	char *CriperText1;
	char *PlainText1;
	char *DeCriperText1;
	
	time_t start;
	time_t end;
	time(&start);
	
	for(i = 0; i < cnt; i++){
		printf("����ִ�е�%d�β���\n", i + 1);
		PlainText1 = (char *)malloc((text_len + 1) * sizeof(char));
    	CriperText1 = (char *)malloc((text_len + 1) * sizeof(char));
    	DeCriperText1 = (char *)malloc((text_len + 1) * sizeof(char));
    	
    	PlainText1 = (char *)memset(PlainText1, 0, text_len + 1);
    	CriperText1 = (char *)memset(CriperText1, 0, text_len + 1);
    	DeCriperText1 = (char *)memset(DeCriperText1, 0, text_len + 1);
    	
    	K1 = (unsigned char *)malloc((key_len + 1) * sizeof(char));
    	K1 = (unsigned char *)memset(K1, 0, key_len + 1);
    	
    	cp(K1, K, key_len + 1);
    	cp(PlainText1, PlainText, text_len + 1);
    	cp(CriperText1, CriperText, text_len + 1);
    	cp(DeCriperText1, DeCriperText, text_len + 1);
    	cp(S1, S, 256);
    	cp(R1, R, 256);
    	
    	
    	
    	rc4_ini(K1, S1, R1, key_len); 
	    CriperText1 = rc4_crypt(S1, KeyStream1, PlainText1, text_len + 1);
	    rc4_ini(K1, S1, R1, key_len);
    	DeCriperText1 = rc4_crypt(S1, KeyStream1, CriperText1, text_len + 1);
    	
    	free(K1);
    	free(DeCriperText1);
    	free(CriperText1);
    	free(PlainText1);
	}
	
	
	time(&end);
	
	float speed = end - start;
	printf("\n�ļ���С��%ld �ֽ�\n\nִ�д�����%d\n\nƽ�����ܽ���ʱ��ԼΪ��%#fs.\n", text_len, cnt, speed/cnt);
	
	free(K);
	free(DeCriperText);
	free(CriperText);
	free(PlainText);
	
}

void cp(char *des, char *sce, long int size){
	long int j = 0;
	for(j = 0; j < size; j++){
		des[j] = sce[j];
	}
}

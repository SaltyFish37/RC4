#include "rc4.h"

void encrypted(int *arg){
    char *suffix = (char *)malloc(sizeof(char) * sufsize);
	char *key_suf = (char *)malloc(sizeof(char) * sufsize);	
	unsigned char *K;
	unsigned char S[256];
	unsigned char R[256];
	char KeyStream[256];
	char *CriperText;
	char *PlainText;
	
	
	char buff[filesize];
	clean_buff(buff);
	info(arg[0]);
	fgets(buff, filesize, stdin);
	long int *text_len = (long int *)malloc(sizeof(long int));
	if(strlen(buff) < (filesize - 1)){
		buff[strlen(buff) - 1] = '\0';
	}
	PlainText = get_file(buff, suffix, text_len);
	
	
	clean_buff(buff);
	info(arg[1]);
	fgets(buff, filesize, stdin);
	long int *key_len = (long int *)malloc(sizeof(long int));
	if(strlen(buff) < (filesize - 1)){
		buff[strlen(buff) - 1] = '\0';
	}
	K = get_file(buff, key_suf, key_len);

	

	long int size = *key_len;
	rc4_ini(K, S, R, size); 
	size = *text_len;
	CriperText = rc4_crypt(S, KeyStream, PlainText, size + 1);
    printf("--------------\n");
	info(arg[2]);
	printf("--------------\n");
	
	char *enc;
	if(arg[0] == 0){
	    char str[] = "CriperFile";
	    enc = (char*)malloc(sizeof(char) * strlen(str));
	    enc = (char*)memset(enc, 0, strlen(str));
	    strcpy(enc, str);
	} else {
	    char str[] = "DeCriperFile";
	    enc = (char*)malloc(sizeof(char) * strlen(str));
	    enc = (char*)memset(enc, 0, strlen(str));
	    strcpy(enc, str);
	}
	
	save_file(CriperText, suffix, enc, *text_len);
	
	free(enc);
	free(suffix);
	free(key_suf);
	free(K);
	free(PlainText);
	free(CriperText);
}

void rc4_ini(unsigned char *K, unsigned char *S, unsigned char *R, long int N){
/*
    RC4��ʼ��
	K���洢������Կ�ı�����ΪN���ֽ� 
	S��256���ֽڵ�0-255������,256
	R��Ϊʵ��S���ʼ���ĸ�����,256
	N��K�ĳ��� 
*/
	int i = 0, len = 0;
	for(i = 0; i < 256; i++){
		S[i] = i;
	}

	
	for(i = 0; i < 256; i++){
		len = i % N; 
		R[i] = K[len];
		//printf("%c", R[i]);
	}
	char j = 0;
	
	char tmp;
	for(i = 0; i <256; i++){
		j = (j + S[i] + R[i]) % 256;
		tmp = S[i];
		S[i] = S[j];
		S[j] = tmp;
	}
	printf("--------------\n");
	printf("RC4��ʼ������!\n");
	printf("--------------\n");
}

char* rc4_crypt(unsigned char *S, char *KeyStream, char *PlainText, long int size){ 
/*
    ����256���ֽڵ���Կ���в�����size�������ֽ�
	S��256���ֽڵ�0-255������(�ѳ�ʼ��)
	KeyStream����Կ����,256
	CriperText�����ܺ�����ı� 
	PlainText��δ���ܵ����ı� 
	size�����ı�ĳ��� 
	�ٴ����㼴�ɽ��� 
*/
	long int i = 0;
	char j = 0, h = 0;
	char tmp;
	char *CriperText = (char*)malloc(sizeof(char)*(size+1));
	
	while(i < size){
		j = (j + S[i%256]) % 256;
		tmp = S[j];
		S[j] = S[i%256];
		S[i%256] = tmp;
		h = (S[i%256] + S[j]) % 256;
		KeyStream[i%256] = S[h];
		CriperText[i] = (char)(PlainText[i] ^ KeyStream[i%256]); //����
		i = i + 1; 
	}
	CriperText[i] = '\0';
	return CriperText;
}

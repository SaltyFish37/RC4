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
    RC4初始化
	K：存储种子密钥的表，长度为N个字节 
	S：256个字节的0-255的排列,256
	R：为实现S表初始化的辅助表,256
	N：K的长度 
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
	printf("RC4初始化结束!\n");
	printf("--------------\n");
}

char* rc4_crypt(unsigned char *S, char *KeyStream, char *PlainText, long int size){ 
/*
    产生256个字节的密钥序列并加密size个明文字节
	S：256个字节的0-255的排列(已初始化)
	KeyStream：密钥序列,256
	CriperText：加密后的密文表 
	PlainText：未加密的明文表 
	size：明文表的长度 
	再次运算即可解密 
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
		CriperText[i] = (char)(PlainText[i] ^ KeyStream[i%256]); //加密
		i = i + 1; 
	}
	CriperText[i] = '\0';
	return CriperText;
}

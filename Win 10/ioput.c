#include "ioput.h"

void clean_buff(char *buff){
    int i = 0;
    for(i = 0; i < filesize; i++){
        buff[i] = 0;
    }
}

long int get_len(FILE *fp){
/*
    ���ܣ���ȡ�ļ�����
	������fp-�ļ�ָ��-��Ӧ���ļ���
	������ļ��ĳ��ȣ�һ��intֵ 
*/
	fseek(fp, 0, SEEK_END);
	long int offset = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return offset;
}

int get_suffix_num(char *text){
/*
  �����ļ���׺����ʼλ�õ��±�
  ���룺text-�ļ���(a.txt) 
  �����.��Ӧ���±� 
*/
	long int a = strlen(text);
	long int i = 0;
	for(i = a - 1; i >= 0; i--){
		if(text[i] == '.'){
			break;
		}
	}
	return i;
}

char* get_suffix(char *buff){
/*
  �����ļ���׺��
  ������suffix-����ļ���׺����ָ��
        buff-������ļ���
  �������
*/
    char *suffix;
    int p1 = get_suffix_num(buff);
	int p2 = strlen(buff);
	suffix = (char*)malloc(sizeof(char)*(p2 - p1 + 1));
	int t = 0;
	for(t = p1; t < p2; t++){
		suffix[t - p1] = buff[t];
	}
	suffix[p2 - p1] = '\0';
	printf("file type��%s\n", suffix);
	return suffix;
}

char* get_file(char *buff, char *suffix, long int *size){
	char *des;
    FILE *text = fopen(buff, "rb");
	if(text == NULL){
		printf("file cannot open \n");
		exit(1);
	}else{
    	printf("file opened for loading \n");
    	
    	char* suf = get_suffix(buff);
    	strcpy(suffix, suf);
    	
    	long int a = get_len(text);//��ȡ��С 
    	*size = a;
    	printf("file size:%ld B\n\n", *size);
    	
    	des = (char *)malloc((a + 1) * sizeof(char));
    	des = (char *)memset(des, 0, a + 1);

    	fread(des, sizeof(char), *size, text);
    	
	}
    fclose(text);
    return des;
}

void save_file(char *content, char *suffix, char *argu, long int text_len){
    FILE *fp;
    char *des;
    int len1 = strlen(suffix);
    int len2 = strlen(argu);
    
	des = (char*)malloc(sizeof(char) * (len1 + len2));
	des[0] = '\0';
	
	strcat(des, argu);
	strcat(des, suffix);

	
	fp = fopen(des, "wb");
	if(fp == NULL){
		printf("error in save the file\n");
		exit(1);
	}else{
		fwrite(content, sizeof(char), text_len, fp);
	}
	printf("�ļ��ѱ���Ϊ%s\n", des);
	fclose(fp);
}

void info(int n){
    switch(n){
        case 0: printf("����������ܵ��ļ���(�粻�ڵ�ǰ�ļ���������������·��):\n"); break;
        case 1: printf("��������Կ�ļ���(�粻�ڵ�ǰ�ļ���������������·��):\n"); break;
        case 2: printf("RC4�������!\n"); break;
        case 3: printf("����������ܵ��ļ���(�粻�ڵ�ǰ�ļ���������������·��):\n"); break;
        case 4: printf("RC4�������!\n"); break;
        default : printf("error"); break;
    }
}

void help(void){
	printf("-----------------------------------");
	printf("\n\n");
	printf("This is an application that can be used to encrypt/decrypt files\n\n");
	printf("Developer: Han Xiao\n\n");
	printf("Its algorithm is RC4.\n\n");
	printf("optional arguments:\n\n");
	printf("\t-e\t to encrypt a file\n");
	printf("\t-d\t to decrypt a file\n");
	printf("\t-t\t to test the average speed of the RC4 algorithm when encrypting and decrypting files\n\n");
}







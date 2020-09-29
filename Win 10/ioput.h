#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define filesize 256//文件名及路径的最大长度为filesize-1 
#define sufsize 10


void clean_buff(char *buff);
long int get_len(FILE *fp);
char* get_suffix(char *buff);
int get_suffix_num(char *text);
char* get_file(char *buff, char *suffix, long int *text_len);
void save_file(char *content, char *suffix, char *argu, long int text_len);
void info(int n);
void help(void);

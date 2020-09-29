#include "rc4.h"
#include "speed.h"

int main(int argc, char *argv[]){
    char en[] = "-e";
    char de[] = "-d";
    char te[] = "-t";
    
    if(argc == 2 && strcmp(argv[1], en) == 0){
    	
    	int arg[] = {0, 1, 2};
    	
    	encrypted(arg);
    	
	} else if(argc == 2 && strcmp(argv[1], de) == 0) {
		
		int arg[] = {3, 1, 4};

	    encrypted(arg);
	    
	} else if(argc == 2 && strcmp(argv[1], te) == 0) {
		
		test_speed();
		
	} else {
		printf("Please check your order!\n");
		help();
	}		
	
    return 0;
}











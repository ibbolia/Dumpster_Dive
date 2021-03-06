/* Mark Fitzgibbon
	Code for WPI CS4513 Project 1
	
	
*/
#include <stdio.h>
#include <string.h> //strcpy
#include <stdlib.h>		
#include <sys/types.h>
#include <sys/stat.h>		
#include <unistd.h>
#include <libgen.h> //Basename & dirname
#include <utime.h>		
#include <dirent.h>

#include "scruffy.h"



void printUseMessage(){
	printf("Usage: rm (-f:-h:-r) <filename>\n");
}

int main(int argc, char* argv[]){
	int c;
	int fcounter = 0, hcounter = 0, rcounter = 0;
	
	
	//get all options
	while((c = getopt(argc, argv, ":fhr")) != -1){
		switch(c) {
			case 'f' :
				printf("Force is set.\n");
				fcounter = 1;
				break;
			case 'h' :
				hcounter = 1;
				break;
			case 'r' :
				printf("Recursive is set\n");
				rcounter = 1;
				break;
			case '?' :
				perror("Getopt error.");
				break;
			
		}
	}
	printf("%s\n", argv[optind]);
	
	int fileArgPos = optind;

	if(argc < 2 ){
		printUseMessage();
		exit(1);
	}
	else{
		if(hcounter){
			printUseMessage();
		}
		
		while(fileArgPos < argc){
		char* filename = argv[fileArgPos];
		struct stat  buf;
		
		struct utimbuf  puttime;
		char* bin = getTrash(); 	//Confirm TRASH variable is set, and place it in a string
			if(access(bin, F_OK)){		//Confirm TRASH variable doesn't point to nothing
				mkdir(bin, 0777);
			}
		/*
		
		*/
		//confirm file exists
		moveFile(filename, bin, fcounter, rcounter);
		fileArgPos++;
		memset(bin, 0, sizeof(bin));
		}
	}

}
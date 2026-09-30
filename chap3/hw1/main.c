#include <stdio.h>
#include <string.h>
#include "copy.h"
char line[MAXLINE];
char longest[MAXLINE];
void copy(char from[], char to[]);
char strings[5][MAXLINE];
char temp[MAXLINE];


int main()
{
   int len = 0;	
   int i, j;
   for(i=0; i<5; i++){
	   fgets(line,MAXLINE,stdin);
         copy(line, strings[i]);
      }

	for(i=0; i<4; i++){
		for(j=i+1; j<5; j++){
			if(strlen(strings[i]) < strlen(strings[j])){
				copy(strings[i], temp);
				copy(strings[j], strings[i]);
				copy(temp, strings[j]);
			}
		}
	}

	
	for(i=0; i<5; i++){
		printf("%s", strings[i]);
	}

	return 0;
}

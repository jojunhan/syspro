#include <stdio.h>
#define MAXLINE 80

int main(int argc, char *argv[]){
	FILE *fp1,*fp2;
	int line = 0;
	char buffer[MAXLINE];

	char c;
	if (argc !=3){
		fprintf(stderr, "How to use: %s File1 Fiel2\n", argv[0]);
		return 1;
	}

	
	else{
		fp1 = fopen(argv[1],"r");
	c = getc(fp1);
	while (fgets(buffer,MAXLINE,fp1)!=NULL){
		line++;
		printf("%3d %s", line, buffer);
	}
		fp2 = fopen(argv[2],"r");
	c = getc(fp2);
	while (fgets(buffer,MAXLINE,fp2)!=NULL){
		line++;
		printf("%3d %s", line, buffer);
	}
	}

	fclose(fp1);
	fclose(fp2);
	return 0;
}

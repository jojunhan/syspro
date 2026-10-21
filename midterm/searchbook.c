#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX 24
#define START_BOOKNAME 1984

struct book{
	int id;
	char bookname[10];
	char author[10];
	int year;
	int numOfBorrow;
	int borrow;
};

int main(int argc, char *argv[]){
	int fd;
	char c;
	char *booknm[10];
	struct book record;
	if(argc < 2){
		exit(1);
	}
	if((fd = open(argv[1], O_RDONLY)) == -1){
		perror(argv[1]);
		exit(2);
	}

	do{
		printf("input name of book ) ");
		if (scanf("%s", booknm) == 1){
			lseek(fd, 1L, SEEK_SET);
			if((read(fd, (char *) &record, sizeof(record)) > 0) && (record.bookname != NULL)){
					printf("%3s %10s %10s %5s %11s %7s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
					printf("%3d %10s %10s %5d %11d %7d\n\n", record.id, record.bookname, record.author, record.year, record.numOfBorrow, record.borrow);
					}
			else printf("Record %s Null\n", booknm);
		} else printf("Input Error");
		printf("Continue?(Y/N)");
		scanf(" %c", &c);
	}while(c=='Y');
	close(fd);
	exit(0);
}
			

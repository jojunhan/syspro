#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

struct book{
	int id;
	char bookname[10];
	char author[10];
	int year;
	int numOfBorrow;
	int borrow;
};

int main(int argc, char *argv[]){
	int fd, id;
	char c;
	struct book rec;
	FILE *fp;
	if(argc < 2){
		exit(1);
	}
	
	if((fd = open(argv[1], O_RDONLY)) == -1){
		perror(argv[1]);
		exit(2);
	}
	fp = fopen(argv[1], "wb");

	do{
		printf("0: list of all books, 1: list of available books )");
		scanf("%d", &id);
		if(id == 0){
			printf("%-3s %-10s %-10s %-5s %-11s %-7s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
			while(fread(&rec, sizeof(rec), 1, fp) > 0){
				if (rec.id != 0){
					printf("%3d %10s %10s %5d %11d %7d\n", rec.id, rec.bookname, rec.author, rec.year, rec.numOfBorrow, rec.borrow);
				}}}
			else if(id == 1){
				lseek(fp, sizeof(rec), SEEK_END);
				if(read(fd, (char *) &rec, sizeof(rec)) == 1){
					printf("%-3s %-10s %-10s %-5s %-11s %-7s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
					printf("%-3d %-10s %-10s %-5d %-11d %-7d\n", rec.id, rec.bookname, rec.author, rec.year, rec.numOfBorrow, rec.borrow);
			}
		else printf("Record %d None\n", id);
		}	
		printf("Continue? (Y/N)");
		scanf(" %c", &c);
	} while(c == 'Y');
	fclose(fd);
	fclose(fp);
	exit(0);
}

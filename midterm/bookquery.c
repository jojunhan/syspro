#include <stdio.h>
#include <stdlib.h>
struct book{
	int id;
	char bookname[10];
	char author[10];
	int year;
	int numOfBorrow;
	int borrow;
};

int main(int argc, char *argv[]){
	struct book rec;
	char c;
	int id;
	FILE *fp;
	if(argc != 2){
		exit(1);
	}
	
	if((fp = fopen(argv[1], "rb")) == NULL){
		exit(2);
	}
	
	do{
		printf("0: list of all books, 1: list of available books )");
		if(scanf("%d", &id) == 0){
			printf("%-3s %-10s %-10s %-5s %-11s %-7s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
			while(fread(&rec, sizeof(rec), 1, fp) > 0)
				if (rec.id != 0)
					printf("%3d %10s %10s %5d %11d %7d", rec.id, rec.bookname, rec.author, rec.year, rec.numOfBorrow, rec.borrow);
		}
		if(scanf("%d", &id) == 1){
			printf("%-3s %-10s %-10s %-5s %-11s %-7s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
			printf("%-3d %-10s %-10s %-5d %-11d %-7d\n", rec.id, rec.bookname, rec.author, rec.year, rec.numOfBorrow, rec.borrow);
		}
		else printf("Record %d None\n", id);
			
		printf("Continue? (Y/N)");
		scanf(" %c", &c);
	} while(c == 'Y');

	fclose(fp);
	exit(0);
}

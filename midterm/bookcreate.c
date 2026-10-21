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

int main(int argc, char* argv[]){
	struct book rec;
	FILE *fp;
	if(argc != 2){
		exit(1);
	}

	fp = fopen(argv[1], "wb");
	printf("%-3s %-10s %-10s %-5s %-11s %-7s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
	while(scanf("%d %s %s %d %d %d", &rec.id, rec.bookname, rec.author, &rec.year, &rec.numOfBorrow, &rec.borrow) == 6)
		fwrite(&rec, sizeof(rec), 1, fp);
	fclose(fp);
	exit(0);
}


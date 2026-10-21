#include<stdio.h>

struct book{
	int id;
	char bookname[10];
	char author[10];
	int year;
	int numOfBorrow;
	int borrow;
};

int main(int argc, char * argv[]){
	struct book rec;
	FILE *fp;
	if (argc !=2){
		return 1;
	}
	if((fp = fopen(argv[1], "rb")) ==NULL){
		return 2;
	}
	printf("%-3s %-10s %-10s %-5s %-11s %-7s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
	while(fread(&rec,sizeof(rec),1,fp)>0)
		if(rec.id != 0)
			printf("%3d %10s %10s %5d %11d %7d\n", rec.id, rec.bookname, rec.author, rec.year, rec.numOfBorrow, rec.borrow);
	fclose(fp);
	return 0;
}

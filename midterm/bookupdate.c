#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX 24
#define START_ID 1

struct book{
	int id;
	char bookname[10];
	char author[10];
	int year;
	int numofborrow;
	int borrow;
};

int main(int argc, char *argv[]){
	int fd, id;
	char c;
	struct book rec;
	if (argc < 2)
		exit(1);
	
	if((fd = open(argv[1], O_RDWR)) == -1){
		perror(argv[1]);
		exit(2);
	}

	do{
		printf("0 bookId: borrow book, 1 bookId: return book ) ");
		if(scanf("%d %d", &rec.numofborrow &id) == 1){
			lseek(fd, (long) (id-START_ID)*sizeof(rec), SEEK_SET);if ((read(fd, (char *) &record, sizeof(record)) > 0) && (record.id != 0)) {
            scanf("%d", &record.numoborrow);
            lseek(fd, (long) -sizeof(record), SEEK_CUR);
            write(fd, (char *) &record, sizeof(record));
			printf("%-3s %-10s %-10s %-5s %-11s %-7s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
         } else printf("Record %d Null\n", id);
      } else printf("Insert Error\n");
      printf("Continue?(Y/N)");
      scanf(" %c",&c);
   } while (c == 'Y');
   close(fd);
   exit(0);
}

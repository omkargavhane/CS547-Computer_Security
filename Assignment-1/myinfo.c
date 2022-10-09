#include<stdio.h>
#include<time.h>
#include <gnu/stubs-32.h>
int  main(){
	time_t tm;
	time(&tm);
	printf("Name:Omkar Santosh Gavhane,MTech(M&C)\nRoll No:2111MC08\nClass:CS547");
	printf("\nCurrent Date/Time:%s", ctime(&tm));
	return(0);
}

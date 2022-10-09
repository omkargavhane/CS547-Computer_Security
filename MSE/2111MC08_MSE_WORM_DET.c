//Part C
#include<stdio.h>
#include <dirent.h>
int main ()
{
	printf("Worm Detector Written in C by Omkar Gavhane\n");
 	DIR *d;
	FILE *fp;
	char signatures[]={'M','Z','P','E','%','C','L','\0'};
    	struct dirent *dir;
	char c;
    	int flag=0,ptr=0;
    	d = opendir(".");
    	if(d)
    	{
        	while ((dir = readdir(d)) != NULL)
        	{
        	char *filename=dir->d_name;
            	printf("%s\n", filename);
            	fp=fopen(filename,"r");
		flag=0;
            	do
    		{
       			c=getc(fp);
			ptr=0;
       			while(signatures[ptr]!='\0'){
       				if(signatures[ptr]==c){
					flag=1;
       					printf("%s file is may be infected with worm\n",filename);
       					break;
       				}
       				ptr+=1;
       			}
			if(flag)
				break;
    		}while(c!=EOF);
        	}
        	closedir(d);
    	}
    	return(0);
}	



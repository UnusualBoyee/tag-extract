#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
char *file_buffer;
int main(int argv,char *argc[]){
	if(argv==1){exit(44);}
	int mustHave=0;
	char *tag=argc[1];
	char *mustH=argc[2];
	char firstTag[15]="";
	char firstTagS[15]="";
	char all[15]="";
	char oTag[3]="<";
	char oSTag[3]="</";
	char cTag[2]=">";
	char spa[2]=" ";
	char fount[15]="";
	char mustHave_array[5]="";

	char tagName[20]="";
	char stng[10];
//	printf("TGN: ");
//	scanf("%9s",stng);
	sprintf(firstTag,"%s%s%s",oTag,tag,cTag);
	sprintf(firstTagS,"%s%s%s",oTag,tag,spa);
	sprintf(all,"%s%s%s",oSTag,argc[1],cTag);
	printf("%s\n",all);
//	exit(1);

	printf("%s--\n",all);
	printf("%s--",firstTag);
	printf("\n");

	FILE *file=fopen("extra","r");
	fseek(file,0L,SEEK_END);
	int size=ftell(file);
	rewind(file);
	file_buffer=malloc(size+1);
	fread(file_buffer,1,size,file);
	fclose(file);
	char * tagBuffer;
	if(access("result",F_OK)==0){
		remove("result");
	}
	FILE *RESULT=fopen("result","w");

	if(argv==3){
		mustHave=1;
	}
int open;
int close;
int space;
int nextTag;
int spaceTrig=0;
int closeTrig=0;
int spaceTrig1=0;
int mustHaveTrig=0;
	for(int i=0;i<size;i++){
		if(file_buffer[i]=='<'){
			printf("OPEN TAG FOUND ON %d:\n",i);
			open=i;
			for(int j=open;j<=size;j++){
				if(file_buffer[j]==' ' && spaceTrig==0){
					printf("SPACE FOUND ON %d:\n",j);
					space=j;
					spaceTrig=1;
					spaceTrig1=1;
				}
				if(file_buffer[j]=='>'){
					printf("CLOSING TAG FOUND ON %d:\n",j);
					close=j;
					spaceTrig=0;
					if(spaceTrig1==0)
					closeTrig=1;
					break;
				}
			}
			i=close;
		}
		int l=open;
		memset(&fount[0],0,sizeof(fount));
		memset(&mustHave_array[0],0,sizeof(mustHave_array));
		printf("UPDATING CHARS\n");
		if(spaceTrig1){
		printf("space; %d\n",space);
			for(int k=0;k<=(space-open);k++){
			
				fount[k]=file_buffer[l];
				l+=1;
			}
			spaceTrig1=0;
		}else if (closeTrig){
		printf("%d\n",close);
			for(int k=0;k<=(close-open);k++){
	
				fount[k]=file_buffer[l];
				l+=1;
			}
			closeTrig=0;
		}
		//sleep(1.5);
		printf("%s\n",fount);
		printf("%d\n",strcmp(fount,firstTag));
		printf("%d\n",strcasecmp(fount,firstTag));
		printf("MH%d\n",mustHave);
		/*
		if(mustHave){
			int p=0;
			for(int o=open;o<=close;o++){
				mustHave_array[p]=file_buffer[o];
				p++;
			}
			
			if(strcasecmp(mustHave_array,mustH)==0)mustHaveTrig=1;
			else mustHaveTrig=0;
			printf("%s :: %d :: \n",mustHave_array,strcasecmp(mustHave_array,mustH));
		}
		*/

		if(strcasecmp(fount,firstTag)==0 || strcasecmp(fount,firstTagS)==0 /*&& mustHaveTrig==1*/ ){
			for(int m=close;m<=size;m++){
				if(file_buffer[m]=='<'){
					nextTag=m;
					break;
				}
			}
			for(int n=close+1;n<=nextTag-1;n++){
				putc(file_buffer[n],RESULT);
				printf("%c",file_buffer[n]);
			}
			fputs("\n",RESULT);
			printf("\n");
		}
//		fclose(RESULT);
	
	}
	fclose(RESULT);
}

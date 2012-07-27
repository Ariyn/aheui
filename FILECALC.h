/*
 *  FILECALC.h
 *  aheui
 *
 *  Created by 민욱 황 on 12. 7. 15..
 *  Copyright 2012 창원대학교. All rights reserved.
 *
 */

typedef struct cmd
{
	int command;
	struct cmd* upCmd;
	struct cmd* downCmd;
	struct cmd* rightCmd;
	struct cmd* leftCmd;
}cmd;


long sizeofFile(FILE *);
int** fileOpen(unsigned char*,int*,int**);

long sizeofFile(FILE * filePointer)
{
	fseek(filePointer, 0, SEEK_END );
	long size = ftell( filePointer );
	//printf("사이즈 = %ld\n",size);
	fseek(filePointer, 0, SEEK_SET );
	return size;
}

int** fileOpen(unsigned char*cmdInput,int* rows,int** cols)
{
	int **cmds;
	FILE *fp;
	fp=fopen((char*)cmdInput, "r");
	if(fp==NULL)
	{
		printf("%s라는",cmdInput);
		puts("파일을 불러올수 없습니다.");
		exit(0);
	}
	else // \n의 갯수 = 라인수
	{
		int tempChar[4];
		int *closs=(int*)malloc(sizeof(int));
		int a;
		int temp=0;
		
		for(int i=1;;i++)
			for(int e=0;;e++)
			{
				a=fgetc(fp);
				if(a=='\n')
				{
					if(e>=temp)
						temp=e;
					closs[i]=e/3;
					closs=(int*)realloc(closs,(i+2)*sizeof(int));
					break;
				}
				else if(a==EOF)
				{
					tempChar[0]='\0';
					*rows=i+1;
					closs[i]=e/3;
					closs[0]=temp/3;
					goto gotoBreak1;
				}
			}
	gotoBreak1:;
		if(*rows==0)
		{
			puts("명령이 없습니다");
			exit(0);
		}
		
		sizeofFile(fp);
		
		cmds=(int **)malloc(sizeof(int*)*(*rows));
		for(int i=1;i<(*rows);i++)
		{
			cmds[i]=(int *)malloc(sizeof(int)*(closs[i]));
			for(int e=0;e<(closs[i]*3);e++)
			{
				tempChar[0]=fgetc(fp);
				
				if(tempChar[0]=='\n' || !tempChar[0])
				{
					tempChar[0]='\0';
					break;
				}
				
				tempChar[1]=fgetc(fp);
				tempChar[2]=fgetc(fp);
				tempChar[3]='\0';
				//printf("%s",(char *)tempChar);
				cmds[i][e]=UTF2UNICODE(tempChar);
			}
			//printf("\n");
		}
	gotoBreak:;
		*cols=closs;
	}
	return cmds;
}
/*
 *  aheui.h
 *  aheui
 *
 *  Created by 민욱 황 on 12. 7. 10..
 *  Copyright 2012 창원대학교. All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "UNICODE.h"
#include "FILECALC.h"

#define QUE 21

void enQue(int);
void pushStack(int ,int);
void inInfo(int info,int);

double deQue();
double popStack(int);
int outInfo(int);

void aheuiiInit();

void chosungAction(int*);
void jungsungAction(int);
void hanbun(int);

typedef struct Node
{
	int info;
	struct Node* nextNode;
}Node;

struct
{
	int number;
	struct Node* firstQue;
	struct Node* lastQue;
} que;

struct// stack
{
	int number;
	struct Node* upStack;
}stack[28];

struct 
{	
	int steps;
	
	int x;
	int y;
	int moveType[2];
	
	int* col;
	int row;
	int mostLong;

	int** cmds;
	char *printStr;
	char *printNum;

	int selectedStack;
}aheui;



//void returnCmdPointer();


char testChar[]="aheui.number=%d,	aheui.y=%d,aheui.x=%d   명령어=%s\n";
void aheuiMain(char cmdInput[])
{
	

	char options[3]={0,};
	aheuiiInit(options);
	
	aheui.cmds=fileOpen((unsigned char*)cmdInput, &aheui.row, &aheui.col);
	
	//aheui.col[0]= 가장 긴 글자 갯수.
	//그러므로 aheui.y는 0으로 가면 안됨.
	printf("\n\n이상 %dx%d자의 ",aheui.row-1,aheui.col[0]);
	printf("아희 명령어\n\n");
	
	
	while(1)
	{

		hanbun(1);	
	}
}

void hanbun(int debug)
{
	int numberTemp[3]={0,};

	UNICODE2DIV(aheui.cmds[aheui.y][aheui.x],numberTemp);

	aheui.moveType[1]=aheui.moveType[0];
	aheui.moveType[0]=KOREAN2NUMBER(numberTemp[1],jungsung);
	if(aheui.moveType[0]==noChange)
		aheui.moveType[0]=aheui.moveType[1];
	
	chosungAction(numberTemp);
	jungsungAction(aheui.moveType[0]);
	aheui.steps++;
	if(debug==10)printf("%d회 루틴",aheui.steps);
}

void inInfo(int infos,int stackNum)
{
	if(stackNum==QUE)
		enQue(infos);
	else
		pushStack(infos,stackNum);
	
}

void pushStack(int infos,int stackNum)
{
	Node* stacks=(Node*)malloc(sizeof(Node));
	stacks->info=infos;
	stacks->nextNode=stack[stackNum].upStack;
	stack[stackNum].upStack=stacks;
	stack[stackNum].number++;
}

void enQue(int info)
{
	Node* newQue=(Node*)malloc(sizeof(Node));
	newQue->info=(double)info;
	newQue->nextNode=NULL;
	que.number++;
	if(que.firstQue==NULL)
	{
		que.firstQue=newQue;
		que.lastQue=newQue;
	}
	else
	{
		que.lastQue->nextNode=newQue;
		que.lastQue=newQue;
	}
}

int outInfo(int stackNum)
{
	double returnVar=0;
	if(stackNum==QUE)
		returnVar=deQue();
	else
		returnVar=popStack(stackNum);
	return (int)returnVar;
}
double popStack(int stackNum)
{	
	if(stack[stackNum].number==0)
		return 0;
	double returnTemp=stack[stackNum].upStack->info;
	Node* stacks=NULL;
	stacks=stack[stackNum].upStack->nextNode;
	free(stack[stackNum].upStack);
	stack[stackNum].upStack=stacks;
	stack[stackNum].number--;
	return returnTemp;
}

double deQue()
{
	if(que.number==0)
		return 0;
	que.number--;
	double returnVar=que.firstQue->info;
	Node* Ques;
	Ques=que.firstQue->nextNode;
	free(que.firstQue);
	
	if(Ques==NULL)
		que.lastQue==NULL;
	
	que.firstQue=Ques;
	
	return returnVar;
}

void aheuiiInit(char options[])
{
	aheui.selectedStack=0;
	aheui.steps=0;
	aheui.row=0;
	aheui.col=0;
	aheui.x=0;
	aheui.y=1;
	aheui.moveType[0]=0;
	aheui.moveType[1]=0;
	
	if(options[1]==1)
	{
		aheui.printStr="%s,";
		aheui.printNum="%d,";
	}
	else if(options[1]==2)
	{
		aheui.printNum="%d\n";
		aheui.printStr="%s\n";
	}
	else
	{
		aheui.printStr="%s";
		aheui.printNum="%d";
	}
	
	
	for(int i=0;i<29;i++)
	{
		stack[i].number=0;
		stack[i].upStack=NULL;
	}
	que.number=0;
	que.firstQue=NULL;
	que.lastQue=NULL;
}
void chosungAction(int* info)
{
	int selectStack=aheui.selectedStack;
	int a=0,b=0;
	int stackTemp=0;
	switch (info[0])
	{
		case 0://ㄱ
			break;
		case 1://ㄲ
			break;
		case 2://ㄴ
			if((selectStack==QUE&&que.number<2)||(selectStack!=QUE&&stack[selectStack].number<2))
			{
				aheui.moveType[0]=(-aheui.moveType[0]);
				break;
			}
			a=outInfo(selectStack); b=outInfo(selectStack); inInfo((b/a),selectStack); 
			break;
		case 3://ㄷ
			if((selectStack==QUE&&que.number<2)||(selectStack!=QUE&&stack[selectStack].number<2))
			{
				aheui.moveType[0]=(-aheui.moveType[0]);
				break;
			}
			a=outInfo(selectStack); b=outInfo(selectStack); inInfo((b+a),selectStack); 
			break;
		case 4://ㄸ
			if((selectStack==QUE&&que.number<2)||(selectStack!=QUE&&stack[selectStack].number<2))
			{
				aheui.moveType[0]=(-aheui.moveType[0]);
				break;
			}
			a=outInfo(selectStack); b=outInfo(selectStack); inInfo((b*a),selectStack); 
			break;
		case 5://ㄹ
			if((selectStack==QUE&&que.number<2)||(selectStack!=QUE&&stack[selectStack].number<2))
			{
				aheui.moveType[0]=(-aheui.moveType[0]);
				break;
			}
			a=outInfo(selectStack); b=outInfo(selectStack); inInfo((b%a),selectStack); 
			break;
		case 6://ㅁ
			if((selectStack==QUE&&que.number<=0)||(selectStack!=QUE&&stack[selectStack].number<=0))
			{
				aheui.moveType[0]=(-aheui.moveType[0]);
				break;
			}
			stackTemp=outInfo(selectStack);
			if(info[2]==27)
			{	
				char stringTempsss[4];
				UNICODE2UTF(stackTemp, stringTempsss);
				
				printf(aheui.printStr,stringTempsss);
			}
			else if(info[2]==21)
				printf(aheui.printNum,outInfo(selectStack));
			break;
		case 7://ㅂ 
			if(info[2]==27)
			{
				printf("아직 구현 안됨");
				//글자 입력.
			}
			else if(info[2]==21)
			{
				int inputNumber;
				printf("숫자를 입력하세요");
				scanf("%d",&inputNumber);
				inInfo(inputNumber, selectStack);
			}
			else
				inInfo(KOREAN2NUMBER(info[2], jongsung),selectStack);
			break;
		case 8://ㅃ
			if((selectStack==QUE&&que.number<1)||(selectStack!=QUE&&stack[selectStack].number<1))
			{
				aheui.moveType[0]=(-aheui.moveType[0]);
				break;
			}
			a=outInfo(selectStack); inInfo(a,selectStack); inInfo(a,selectStack); 
			break;
		case 9://ㅅ
				//if(aheui.steps>=55169)printf("%d스택 선택됨.\n",info[2]);
				aheui.selectedStack=info[2];
			break;
		case 10://ㅆ
			if((selectStack==QUE&&que.number<1)||(selectStack!=QUE&&stack[selectStack].number<1))
			{
				//printf("que.number=%d\n",que.number);
				aheui.moveType[0]=(-aheui.moveType[0]);
				break;
			}
			a=outInfo(selectStack); inInfo(a,info[2]); 
			break;
		case 11://ㅇ
			//아무것도 하지 않음.
			break;
		case 12://ㅈ
			if((selectStack==QUE&&que.number<2)||(selectStack!=QUE&&stack[selectStack].number<2))
			{
				aheui.moveType[0]=(-aheui.moveType[0]);
				break;
			}
			a=outInfo(selectStack); b=outInfo(selectStack);
				if(a<=b)
					inInfo(1,selectStack);
				else
					inInfo(0,selectStack);	
			break;
		case 14://ㅊ
			if((selectStack==QUE&&que.number<1)||(selectStack!=QUE&&stack[selectStack].number<1))
			{
				aheui.moveType[0]=(-aheui.moveType[0]);
				break;
			}
			a=outInfo(selectStack);
			if(a==0)
				aheui.moveType[0]=(-aheui.moveType[0]);
			else
				aheui.moveType[0]=(aheui.moveType[0]);
			break;
		case 16://ㅌ
			if((selectStack==QUE&&que.number<2)||(selectStack!=QUE&&stack[selectStack].number<2))
			{
				aheui.moveType[0]=(-aheui.moveType[0]);
				break;
			}
			a=outInfo(selectStack); b=outInfo(selectStack); inInfo((b-a),selectStack);
			break;
		case 17://ㅍ
			//printf("stack[selectStack].number=%d\n",stack[selectStack].number);
			if((selectStack==QUE&&que.number<2)||(selectStack!=QUE&&stack[selectStack].number<2))
			{
				aheui.moveType[0]=(-aheui.moveType[0]);
				break;
			}
			a=outInfo(selectStack); b=outInfo(selectStack); inInfo(a, selectStack); inInfo(b, selectStack); 
			break;
		case 18://ㅎ
			exit(outInfo(selectStack));
			break;
		default:
			aheui.steps--;
			//아무것도 하지 않음.
			break;
	}
}
void jungsungAction(int info)
{
	switch (info)
	{
		case right1:
			if(++aheui.x>=aheui.col[aheui.y])
				aheui.x=0;
			break;
		case right2:
			if((aheui.x+=2)>=aheui.col[aheui.y])
				aheui.x=0;
			break;
		case left1:
			if(--aheui.x<0)
				aheui.x=aheui.col[aheui.y]-1;
			break;
		case left2:
			if((aheui.x-=2)<0)
				aheui.x=aheui.col[aheui.y]-1;
			break;
		case up1:
			if(--aheui.y<1)
				aheui.y=aheui.row;
			if(aheui.x>=aheui.col[aheui.y])
				while(aheui.x>aheui.col[aheui.y])
					if(aheui.y--<1)
						aheui.y=aheui.row;
			break;
		case up2:
			if((aheui.y-=2)<1)
				aheui.y=aheui.row;
			if(aheui.x>=aheui.col[aheui.y])
				while(aheui.x>aheui.col[aheui.y])
					if((aheui.y-=2)<1)
						aheui.y=aheui.row;
			break;
		case down1:
			if(++aheui.y>aheui.row)
				aheui.y=1;
			if(aheui.x>=aheui.col[aheui.y+1])
			{
				while(aheui.x>aheui.col[aheui.y])
					if(++aheui.y>aheui.row)
						aheui.y=1;
			}
			break;
		case down2:
			if((aheui.y+=2)>aheui.row)
				aheui.y=1;
			if(aheui.x>=aheui.col[aheui.y])
				while(aheui.x>aheui.col[aheui.y])
					if((aheui.y+=2)>aheui.row)
						aheui.y=1;
			break;
		case chaeVer:
			{
			int movement=0;
			if(aheui.moveType[1]==right1||aheui.moveType[1]==right2||
			   aheui.moveType[1]==left1||aheui.moveType[1]==left2)
				movement=aheui.moveType[1];
				
			else if(aheui.moveType[1]==up1||aheui.moveType[1]==up2
					||aheui.moveType[1]==down1||aheui.moveType[1]==down2)
				movement=(-aheui.moveType[1]);
				
			jungsungAction(movement);
			}
			break;
		case chaeHori:
		{
			int movement=0;
			if(aheui.moveType[1]==up1||aheui.moveType[1]==up2||
			   aheui.moveType[1]==down1||aheui.moveType[1]==down2)
				movement=aheui.moveType[1];
			
			else if(aheui.moveType[1]==right1||aheui.moveType[1]==right2||
					aheui.moveType[1]==left1||aheui.moveType[1]==left2)
				movement=(-aheui.moveType[1]);
			
			jungsungAction(movement);
		}
			break;
		case chaeAll:
			jungsungAction((-aheui.moveType[1]));
			break;
	}
}

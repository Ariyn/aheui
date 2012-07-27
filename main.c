
#include "aheui.h"
#include <string.h>
//#include <stdio.h>


int main(int avr, char *avgs[])
{
	//-v 아희 코드를 보여준다. >> 기본 안보여줌.
	//-d 한줄씩 실행시킨다. >> 스택 같은거라던가. 디버그 모드.
	//-c 한글자 프린트 할때 ,를 찍어서 보여준다.
	//-n 한글자 프린트 할때 개행해서 보여준다.
	//number2aheui 만들어 볼것.
	//자바스크립트 인터프리터 같이 만들어 볼것.
	//1429 듀 명령에서 0번째 스택의 마지막이 사라짐.
	//popOut로 뺐을때 stack.arrayNum이 줄어들지 않음
	//파일의 내용에 따라 cmd 크기 결정해주기
	//밑의 파일 읽는것. 따로 분리해 줄것.
	
	//가 = EA B0 80
	int temps[3]={0xEA,0xB0,0x80};
	
	temps[0] &= 0xf;
	temps[0] = temps[0]<< 12;
	temps[0] |=((temps[1]&0x3f)<<6);
	temps[0] |=(temps[2]&0x3f);
	
	printf("%d",temps[0]);
	
	char tempsds[3];
	tempsds[0]=(((temps[0]&0xF000)>>12)|0xE0);
	tempsds[1]=((temps[0]&0xfc0)>>6)|0x80;
	tempsds[2]=(temps[0]&0x3f)|0x80;
	printf("%s",tempsds);
	
	if(avr==1)
		avgs[1]="aheuiSource";
	
/*
 char option[3]={0,};
	
	for(int i=2;i<(avr-1);i++)
	{
		if(!strcmp(avgs[i],"-v"))
			option[0]++;
		else if(!strcmp(avgs[i],"-c"))
			option[1]++;
		else if(!strcmp(avgs[i],"-n"))
			option[2]++;
	}
	if(option[0]!=(avr-2))
		option[0]=0;
	if(option[1]!=(avr-2))
		option[1]=0;
	if(option[2]!=(avr-2))
		option[2]=0;
	printf("%s,\n",avgs[1]);
 */

	aheuiMain(avgs[1]);
	//number2korean(0);

	return 0;
}
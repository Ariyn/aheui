/*
 *  UNICODE.h
 *  aheui
 *
 *  Created by 민욱 황 on 12. 7. 10..
 *  Copyright 2012 창원대학교. All rights reserved.
 *
 */

#define chosung 1
#define jungsung 2
#define jongsung 3

#define right1 1//ㅏ
#define right2 2//ㅑ
#define left1 -1 //ㅓ
#define left2 -2 //ㅕ
#define up1 3//ㅗ
#define up2 4//ㅛ
#define down1 -3//ㅜ
#define down2 -4//ㅠ
#define chaeVer 9 //ㅡ
#define chaeAll 10 //ㅢ
#define chaeHori 11 //ㅣ
#define noChange 12 //변화 없음

int UNICODE2DIV(int number, int* returnInt);
int UTF2UNICODE(int* chara);
int UNICODE2UTF(int number,char* returnInt);
int KOREAN2NUMBER(int number,int cases);

int jongVal[]={0,2,4,4,2,5,5,3,5,7,9,9,7,9,9,8,4,4,6,2,4,1,3,4,3,4,3};

int UNICODE2UTF(int number,char* returnInt)
{
	if(number<0xAC00)
	{
		returnInt[0]=number;
		returnInt[1]='\0';
		return 0;
	}
	returnInt[0]=(((number&0xF000)>>12)|0xE0);
	returnInt[1]=((number&0xfc0)>>6)|0x80;
	returnInt[2]=(number&0x3f)|0x80;
	returnInt[3]='\0';
	//printf("%s",tempsds);
	
	return 0;
}

int UNICODE2DIV(int number, int* returnInt)
{
	//int hangul[3];
	number-=0xAC00;
	returnInt[0]=number/21/28;
	returnInt[1]=((number%(21*28))/28);
	returnInt[2]=number%28;
	//returnInt=hangul;
	return 0;
}

int UTF2UNICODE(int chara[])
{
	int number=(chara[0]&0xf)<<12;
	number|=((chara[1]&0x3f)<<6);
	number|=(chara[2]&0x3f);
	return number;
}

int KOREAN2NUMBER(int number,int cases)
{
	int returnVal=0;
	if(cases==jongsung)
		returnVal=jongVal[number];

	else if(cases==jungsung)
	{
		switch(number)
		{
			case 0://ㅏ
				returnVal=right1;
				break;
//			case 1://ㅐ
//				break;
			case 2://ㅑ
				returnVal=right2;
				break;
//			case 3://ㅒ
//				break;
			case 4://ㅓ
				returnVal=left1;
				break;
//			case 5://ㅔ
//				break;
			case 6://ㅕ
				returnVal=left2;
				break;
//			case 7://ㅖ
//				break;
			case 8://ㅗ
				returnVal=up1;
				break;
//			case 9://ㅘ
//				break;
//			case 10://ㅙ
//				break;
//			case 11://ㅚ
//				break;
			case 12://ㅛ
				returnVal=up2;
				break;
			case 13://ㅜ
				returnVal=down1;
				break;
//			case 14://ㅝ
//				break;
//			case 15://ㅞ
//				break;
//			case 16://ㅟ
//				break;
			case 17://ㅠ
				returnVal=down2;
				break;
			case 18://ㅡ
				returnVal=chaeVer;
				break;
			case 19://ㅢ
				returnVal=chaeAll;
				break;
			case 20://ㅣ
				returnVal=chaeHori;
				break;
			default :
				returnVal=noChange;
		}
	}
	return returnVal;	
}

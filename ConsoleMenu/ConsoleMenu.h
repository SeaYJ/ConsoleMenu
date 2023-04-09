#ifndef _CONSOLEMENU_H_
#define _CONSOLEMENU_H_

// ��Щ�����Ҫʹ�� 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> 

// �˵�����Ķ��� 
typedef struct _MENU_ {
	unsigned int MenuStrMaxLength;			// �˵������Ƶ���󳤶ȣ�Ĭ��255�� 
	unsigned int MenuListMaxNum;			// �˵�������ɶ��ٸ��˵��� ��Ĭ��50�� 
	unsigned int MenuListNum;				// �˵���ǰӵ�еĲ˵�����������ʼΪ0�� 
	unsigned int MenuIndex;					// ��ѡ�в˵��������ֵ 
	char** MenuContent;						// �ڲ��ö�ά����洢�˵������Ϣ������ᱻ0��ʼ��
											// ���Ҽ�ʹɾ��Ҳ���ɾ����Ϣ0ֵ�� 
	int (*AddMenuList)(const char*);		// ���һ���˵��� 
	int (*InsertMenuList)(const char*, int);// ����һ���˵��� 
	int (*DelMenuList)(int);				// ɾ��һ���˵��� 
	int (*SwapMenuList)(int, int);			// ���������˵����λ�� 
}MENU;
MENU root_menu;								// ��δ�뵽�õĽ���취�����Բ�֧�ֶ����˵�
											// ���ȫ�ֱ������Ժ��� 

// ���崰����ɫֵ 
typedef enum _MENUCOLOR_ {
//    ������ֱ��ʹ��intֵ���������Ķ�����ԭ���Ͽ���ʹ��intֵ 
//	  0 = ��ɫ       8 = ��ɫ
//    1 = ��ɫ       9 = ����ɫ
//    2 = ��ɫ       A = ����ɫ
//    3 = ǳ��ɫ     B = ��ǳ��ɫ
//    4 = ��ɫ       C = ����ɫ
//    5 = ��ɫ       D = ����ɫ
//    6 = ��ɫ       E = ����ɫ
//    7 = ��ɫ       F = ����ɫ
	BLACK 	=	0x0,	GREY 		= 0x8,
	BLUE 	= 	0x1,	LIGHTBLUE 	= 0x9,
	GREEN 	= 	0x2,	LIGHTGREEN 	= 0xA,
	ONDINE 	= 	0x3,	LIGHTONDINE = 0xB,
	RED 	= 	0x4,	LIGHTRED 	= 0xC,
	PURPLE 	= 	0x5,	LIGHTPURPLE = 0xD,
	YELLOW 	= 	0x6,	LIGHTYELLOW = 0xE,
	WHITE 	= 	0x7,	LIGHTWHITE 	= 0xF
} MENUCOLOR;

// ����̨�˵�����Ķ��� 
typedef struct _CONSOLE_MENU_ {
	MENU* Menu;									// �˵�����ָ��	
	int (*Refresh)(void);						// ˢ�¿���̨��Ϣ 
												// ���ÿ���̨��� 
	int (*SetConsoleMenuWnd)(const unsigned int,// �� 
							const unsigned int, // �� 
							const char*, 		// ���� 
							MENUCOLOR, 			// ������ɫ 
							MENUCOLOR); 		// ������ɫ 
	void (*PrintMenu)(MENU*);					// ��ӡ�˵� 
}CONSOLEMENU;

// Ĭ��ֵ
//	Width=80 Height=25 
//	ConsoleForegroundColor=GREEN ConsoleBackgroundColor=BLACK
unsigned int ConsoleWidth;						// ����̨��ȣ�ֻ��¼������ͨ���˴��޸ģ� 
unsigned int ConsoleHeight;						// ����̨�߶ȣ�ֻ��¼������ͨ���˴��޸ģ�
MENUCOLOR ConsoleForegroundColor;				// ����̨������ɫ��ֻ��¼������ͨ���˴��޸ģ� 
MENUCOLOR ConsoleBackgroundColor;				// ����̨������ɫ��ֻ��¼������ͨ���˴��޸ģ� 

int Init(CONSOLEMENU* console_menu);			// ��ʼ������̨�˵����� 
void RunKeyEvent(CONSOLEMENU* console_menu);	// �����¼����� 

HANDLE CONSOLE_STD_INPUT_HANDLE;				// ����̨��׼������ 
HANDLE CONSOLE_STD_OUTPUT_HANDLE;				// ����̨��׼������ 

//����̨��궨λ����
void SetConsoleCursor(int x, int y);			// ���ÿ���̨���
												// ����x������y
												// ���ַ�Ϊ��λ 

#endif

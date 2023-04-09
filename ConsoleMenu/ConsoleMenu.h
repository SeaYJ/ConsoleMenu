#ifndef _CONSOLEMENU_H_
#define _CONSOLEMENU_H_

// 这些库必须要使用 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> 

// 菜单对象的定义 
typedef struct _MENU_ {
	unsigned int MenuStrMaxLength;			// 菜单项名称的最大长度（默认255） 
	unsigned int MenuListMaxNum;			// 菜单最多容纳多少个菜单项 （默认50） 
	unsigned int MenuListNum;				// 菜单当前拥有的菜单项总数（初始为0） 
	unsigned int MenuIndex;					// 被选中菜单项的索引值 
	char** MenuContent;						// 内部用二维数组存储菜单项的信息，数组会被0初始化
											// 并且即使删除也会把删除信息0值化 
	int (*AddMenuList)(const char*);		// 添加一个菜单项 
	int (*InsertMenuList)(const char*, int);// 插入一个菜单项 
	int (*DelMenuList)(int);				// 删除一个菜单项 
	int (*SwapMenuList)(int, int);			// 交换两个菜单项的位置 
}MENU;
MENU root_menu;								// 暂未想到好的解决办法，所以不支持二级菜单
											// 这个全局变量可以忽略 

// 整体窗口颜色值 
typedef enum _MENUCOLOR_ {
//    不建议直接使用int值，不利于阅读，但原理上可以使用int值 
//	  0 = 黑色       8 = 灰色
//    1 = 蓝色       9 = 淡蓝色
//    2 = 绿色       A = 淡绿色
//    3 = 浅绿色     B = 淡浅绿色
//    4 = 红色       C = 淡红色
//    5 = 紫色       D = 淡紫色
//    6 = 黄色       E = 淡黄色
//    7 = 白色       F = 亮白色
	BLACK 	=	0x0,	GREY 		= 0x8,
	BLUE 	= 	0x1,	LIGHTBLUE 	= 0x9,
	GREEN 	= 	0x2,	LIGHTGREEN 	= 0xA,
	ONDINE 	= 	0x3,	LIGHTONDINE = 0xB,
	RED 	= 	0x4,	LIGHTRED 	= 0xC,
	PURPLE 	= 	0x5,	LIGHTPURPLE = 0xD,
	YELLOW 	= 	0x6,	LIGHTYELLOW = 0xE,
	WHITE 	= 	0x7,	LIGHTWHITE 	= 0xF
} MENUCOLOR;

// 控制台菜单对象的定义 
typedef struct _CONSOLE_MENU_ {
	MENU* Menu;									// 菜单对象指针	
	int (*Refresh)(void);						// 刷新控制台信息 
												// 设置控制台规格 
	int (*SetConsoleMenuWnd)(const unsigned int,// 宽 
							const unsigned int, // 高 
							const char*, 		// 标题 
							MENUCOLOR, 			// 文字颜色 
							MENUCOLOR); 		// 背景颜色 
	void (*PrintMenu)(MENU*);					// 打印菜单 
}CONSOLEMENU;

// 默认值
//	Width=80 Height=25 
//	ConsoleForegroundColor=GREEN ConsoleBackgroundColor=BLACK
unsigned int ConsoleWidth;						// 控制台宽度（只记录，不可通过此处修改） 
unsigned int ConsoleHeight;						// 控制台高度（只记录，不可通过此处修改）
MENUCOLOR ConsoleForegroundColor;				// 控制台文字颜色（只记录，不可通过此处修改） 
MENUCOLOR ConsoleBackgroundColor;				// 控制台背景颜色（只记录，不可通过此处修改） 

int Init(CONSOLEMENU* console_menu);			// 初始化控制台菜单对象 
void RunKeyEvent(CONSOLEMENU* console_menu);	// 键盘事件监听 

HANDLE CONSOLE_STD_INPUT_HANDLE;				// 控制台标准输入句柄 
HANDLE CONSOLE_STD_OUTPUT_HANDLE;				// 控制台标准输出句柄 

//控制台光标定位函数
void SetConsoleCursor(int x, int y);			// 设置控制台光标
												// 横向x，竖向y
												// 以字符为单位 

#endif

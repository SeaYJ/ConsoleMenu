#include "main.h"

// 添加菜单项 
int _AddMenuList_(const char* menu_list_content) {
	// 字符串超出长度 
	if (strlen(menu_list_content) > root_menu.MenuStrMaxLength) return 1;
	// 菜单List已满 
	if (root_menu.MenuListNum >= root_menu.MenuListMaxNum) return 1;
	strcpy(root_menu.MenuContent[root_menu.MenuListNum], menu_list_content);
	root_menu.MenuListNum += 1;
	
	return 0;
}

// 插入菜单项 
int _InsertMenuList_(const char* menu_list_content, int index) {
	int i;
	// 字符串超出长度 
	if (strlen(menu_list_content) > root_menu.MenuStrMaxLength) return 1;
	// 菜单List已满 
	if (root_menu.MenuListNum >= root_menu.MenuListMaxNum) return 1;
	// 索引越界 
	if (index < 0 || index > root_menu.MenuListNum) return 1;
	for (i = root_menu.MenuListNum; i > index; i--) {
		strcpy(root_menu.MenuContent[i], root_menu.MenuContent[i-1]);
	}
	strcpy(root_menu.MenuContent[index], menu_list_content);
	root_menu.MenuListNum += 1;
	
	return 0;
}

// 删除菜单项 
int _DelMenuList_(int index) {
	int i;
	// 索引越界 
	if (index < 0 || index >= root_menu.MenuListNum) return 1;
	// List已空
	if (root_menu.MenuListNum <= 0) return 1;
	for (i = index; i < root_menu.MenuListNum - 1; i++) {
		strcpy(root_menu.MenuContent[i], root_menu.MenuContent[i+1]);
	}
	// 把最后一个原来的值赋0覆盖，防止残留数据影响操作 
	memset(root_menu.MenuContent[i], '\0', root_menu.MenuStrMaxLength * sizeof(char));
	root_menu.MenuListNum -= 1; 
	return 0;
}

// 交换两个菜单项 
int _SwapMenuList_(int list_1_index, int list_2_index) {
	if (list_1_index < 0 || list_1_index > root_menu.MenuListNum) return 1;
	if (list_2_index < 0 || list_2_index > root_menu.MenuListNum) return 1;
	if (list_1_index == list_2_index) return 0;
	
	char temp[root_menu.MenuStrMaxLength];
	memset(temp, '\0', root_menu.MenuStrMaxLength * sizeof(char));
	
	strcpy(temp, root_menu.MenuContent[list_1_index]);
	strcpy(root_menu.MenuContent[list_1_index], root_menu.MenuContent[list_2_index]);
	strcpy(root_menu.MenuContent[list_2_index], temp);
	
	return 0;
}

// 刷新菜单 
int _Refresh_() {
	return system("cls");
}

// 设置窗口时会自动清除之前的旧内容 
int _SetConsoleMenuWnd_(const unsigned int width, 
						const unsigned int height, 
						const char* wnd_title, 
						MENUCOLOR text_color, 
						MENUCOLOR bg_color) {
	int i;
	int wnd_title_len = strlen(wnd_title);
	const unsigned int
		min_width = 15,		// 系统决定的最小值为 15
		min_height = 1,		// 系统决定的最小值为 1
		min_color_val = 0x0,// 防止恶意代码
		max_width = 256,	// 系统决定的最大值似乎是 211，这可能和屏幕大小及分辨率有关 （超过也没事，会被系统舍弃。这里防止恶意代码！） 
		max_height = 64,	// 系统.决定的最大值似乎是 62 ，也与字体大小有关 
		max_title_len = 128,// 最大字符串长度，防止恶意代码 
		max_color_val = 0xF;// 防止恶意代码
	
	// 检测宽高 
	if (width < min_width ||
		width > max_width ||
		height < min_height ||
		height > max_height) return 1;
	// 检测标题字串 
	if (wnd_title_len < 0 ||
		wnd_title_len > max_title_len) return 1;
	// 检测颜色值 
	if (text_color < min_color_val ||
		text_color > max_color_val ||
		bg_color < min_color_val ||
		bg_color > max_color_val) return 1;
	
	char cmd_para[max_title_len + 128];
	memset(cmd_para, '\0', (max_title_len + 128) * sizeof(char));
	
	// title "标题" && mode con cols=50 lines=5 && color 0a
	// title 最危险,最有可能出现恶意字串 
	for (i = 0; i < strlen(wnd_title); i++) {
		if (wnd_title[i] == '&') return 2;// 系统本身也不支持&字符作为标题，同时可以用来检测恶意字串 
	}
	sprintf(cmd_para, 
			"title %s && mode con cols=%d lines=%d && color %X%X && echo off", 
			wnd_title, width, height, bg_color, text_color);
	system(cmd_para);
	
	// 更新新的数值（记录） 
	ConsoleWidth = width;
	ConsoleHeight = height;
	ConsoleForegroundColor = text_color;
	ConsoleBackgroundColor = bg_color;
	
	return 0;	
}

__attribute__((weak)) void OnKeyPressed(KEY_EVENT_RECORD KeyEvent, CONSOLEMENU* console_menu) {
	printf("请具体实现操作函数，并绑定关系！\n");
}

void RunKeyEvent(CONSOLEMENU* console_menu) {
	INPUT_RECORD keyrec;
	DWORD res;
	
	while (1) {
		ReadConsoleInput(CONSOLE_STD_INPUT_HANDLE, &keyrec, 1, &res);	//读取输入事件
		if (keyrec.EventType == KEY_EVENT)      						//如果当前事件是键盘事件
        {
        	OnKeyPressed(keyrec.Event.KeyEvent, console_menu);
        }
    }
}

// 打印菜单 
void _PrintMenu_(MENU* menu) {
	int i;
	
	system("cls");
	SetConsoleCursor(0, 0);
	
	for (i = 0; i < (menu->MenuListNum); i++) {
		printf("  %s\n",(menu->MenuContent)[i]);
	}
	
	SetConsoleCursor(0, menu->MenuIndex);
	printf("* %s", menu->MenuContent[menu->MenuIndex]);
}

// 初始化 
int Init(CONSOLEMENU* console_menu) {
	int i;
	
	// 初始化菜单（动态数组）
	root_menu.MenuListMaxNum = 50;
	root_menu.MenuStrMaxLength = 255;
	root_menu.MenuListNum = 0;
	root_menu.MenuIndex = 0;
	root_menu.AddMenuList = _AddMenuList_;
	root_menu.InsertMenuList = _InsertMenuList_;
	root_menu.DelMenuList = _DelMenuList_;
	root_menu.SwapMenuList = _SwapMenuList_;
	
	root_menu.MenuContent = (char**)malloc(root_menu.MenuListMaxNum * sizeof(char*));
	for (i = 0; i < root_menu.MenuListMaxNum; i++) {
		(root_menu.MenuContent)[i] = (char*)malloc(root_menu.MenuStrMaxLength * sizeof(char));
		memset((root_menu.MenuContent)[i], '\0', root_menu.MenuStrMaxLength * sizeof(char));
	}
	if (!root_menu.MenuContent) return 1;
	console_menu->Menu = &root_menu;
	
	// 初始化函数
	console_menu->Refresh = _Refresh_;
	console_menu->SetConsoleMenuWnd = _SetConsoleMenuWnd_;
	console_menu->PrintMenu = _PrintMenu_;
	
	// 初始化控制台默认参数
	system("mode con cols=80 lines=25 && color 0a && cls && echo off");
	ConsoleWidth = 80;
	ConsoleHeight = 25;
	ConsoleForegroundColor = GREEN;
	ConsoleForegroundColor = BLACK;
	
	// 获取当前控制台窗口的句柄 
	CONSOLE_STD_INPUT_HANDLE = GetStdHandle(STD_INPUT_HANDLE);
	CONSOLE_STD_OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
	return 0;
}

//控制台光标定位函数
void SetConsoleCursor(int x, int y) {
    COORD pos = { x,y };// 是表示 pos 坐标位置为参数对应的(x，y)
    SetConsoleCursorPosition(CONSOLE_STD_OUTPUT_HANDLE, pos);// 该函数设置控制台(cmd)光标位置
}

#include "main.h"

// ��Ӳ˵��� 
int _AddMenuList_(const char* menu_list_content) {
	// �ַ����������� 
	if (strlen(menu_list_content) > root_menu.MenuStrMaxLength) return 1;
	// �˵�List���� 
	if (root_menu.MenuListNum >= root_menu.MenuListMaxNum) return 1;
	strcpy(root_menu.MenuContent[root_menu.MenuListNum], menu_list_content);
	root_menu.MenuListNum += 1;
	
	return 0;
}

// ����˵��� 
int _InsertMenuList_(const char* menu_list_content, int index) {
	int i;
	// �ַ����������� 
	if (strlen(menu_list_content) > root_menu.MenuStrMaxLength) return 1;
	// �˵�List���� 
	if (root_menu.MenuListNum >= root_menu.MenuListMaxNum) return 1;
	// ����Խ�� 
	if (index < 0 || index > root_menu.MenuListNum) return 1;
	for (i = root_menu.MenuListNum; i > index; i--) {
		strcpy(root_menu.MenuContent[i], root_menu.MenuContent[i-1]);
	}
	strcpy(root_menu.MenuContent[index], menu_list_content);
	root_menu.MenuListNum += 1;
	
	return 0;
}

// ɾ���˵��� 
int _DelMenuList_(int index) {
	int i;
	// ����Խ�� 
	if (index < 0 || index >= root_menu.MenuListNum) return 1;
	// List�ѿ�
	if (root_menu.MenuListNum <= 0) return 1;
	for (i = index; i < root_menu.MenuListNum - 1; i++) {
		strcpy(root_menu.MenuContent[i], root_menu.MenuContent[i+1]);
	}
	// �����һ��ԭ����ֵ��0���ǣ���ֹ��������Ӱ����� 
	memset(root_menu.MenuContent[i], '\0', root_menu.MenuStrMaxLength * sizeof(char));
	root_menu.MenuListNum -= 1; 
	return 0;
}

// ���������˵��� 
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

// ˢ�²˵� 
int _Refresh_() {
	return system("cls");
}

// ���ô���ʱ���Զ����֮ǰ�ľ����� 
int _SetConsoleMenuWnd_(const unsigned int width, 
						const unsigned int height, 
						const char* wnd_title, 
						MENUCOLOR text_color, 
						MENUCOLOR bg_color) {
	int i;
	int wnd_title_len = strlen(wnd_title);
	const unsigned int
		min_width = 15,		// ϵͳ��������СֵΪ 15
		min_height = 1,		// ϵͳ��������СֵΪ 1
		min_color_val = 0x0,// ��ֹ�������
		max_width = 256,	// ϵͳ���������ֵ�ƺ��� 211������ܺ���Ļ��С���ֱ����й� ������Ҳû�£��ᱻϵͳ�����������ֹ������룡�� 
		max_height = 64,	// ϵͳ.���������ֵ�ƺ��� 62 ��Ҳ�������С�й� 
		max_title_len = 128,// ����ַ������ȣ���ֹ������� 
		max_color_val = 0xF;// ��ֹ�������
	
	// ����� 
	if (width < min_width ||
		width > max_width ||
		height < min_height ||
		height > max_height) return 1;
	// �������ִ� 
	if (wnd_title_len < 0 ||
		wnd_title_len > max_title_len) return 1;
	// �����ɫֵ 
	if (text_color < min_color_val ||
		text_color > max_color_val ||
		bg_color < min_color_val ||
		bg_color > max_color_val) return 1;
	
	char cmd_para[max_title_len + 128];
	memset(cmd_para, '\0', (max_title_len + 128) * sizeof(char));
	
	// title "����" && mode con cols=50 lines=5 && color 0a
	// title ��Σ��,���п��ܳ��ֶ����ִ� 
	for (i = 0; i < strlen(wnd_title); i++) {
		if (wnd_title[i] == '&') return 2;// ϵͳ����Ҳ��֧��&�ַ���Ϊ���⣬ͬʱ���������������ִ� 
	}
	sprintf(cmd_para, 
			"title %s && mode con cols=%d lines=%d && color %X%X && echo off", 
			wnd_title, width, height, bg_color, text_color);
	system(cmd_para);
	
	// �����µ���ֵ����¼�� 
	ConsoleWidth = width;
	ConsoleHeight = height;
	ConsoleForegroundColor = text_color;
	ConsoleBackgroundColor = bg_color;
	
	return 0;	
}

__attribute__((weak)) void OnKeyPressed(KEY_EVENT_RECORD KeyEvent, CONSOLEMENU* console_menu) {
	printf("�����ʵ�ֲ������������󶨹�ϵ��\n");
}

void RunKeyEvent(CONSOLEMENU* console_menu) {
	INPUT_RECORD keyrec;
	DWORD res;
	
	while (1) {
		ReadConsoleInput(CONSOLE_STD_INPUT_HANDLE, &keyrec, 1, &res);	//��ȡ�����¼�
		if (keyrec.EventType == KEY_EVENT)      						//�����ǰ�¼��Ǽ����¼�
        {
        	OnKeyPressed(keyrec.Event.KeyEvent, console_menu);
        }
    }
}

// ��ӡ�˵� 
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

// ��ʼ�� 
int Init(CONSOLEMENU* console_menu) {
	int i;
	
	// ��ʼ���˵�����̬���飩
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
	
	// ��ʼ������
	console_menu->Refresh = _Refresh_;
	console_menu->SetConsoleMenuWnd = _SetConsoleMenuWnd_;
	console_menu->PrintMenu = _PrintMenu_;
	
	// ��ʼ������̨Ĭ�ϲ���
	system("mode con cols=80 lines=25 && color 0a && cls && echo off");
	ConsoleWidth = 80;
	ConsoleHeight = 25;
	ConsoleForegroundColor = GREEN;
	ConsoleForegroundColor = BLACK;
	
	// ��ȡ��ǰ����̨���ڵľ�� 
	CONSOLE_STD_INPUT_HANDLE = GetStdHandle(STD_INPUT_HANDLE);
	CONSOLE_STD_OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
	return 0;
}

//����̨��궨λ����
void SetConsoleCursor(int x, int y) {
    COORD pos = { x,y };// �Ǳ�ʾ pos ����λ��Ϊ������Ӧ��(x��y)
    SetConsoleCursorPosition(CONSOLE_STD_OUTPUT_HANDLE, pos);// �ú������ÿ���̨(cmd)���λ��
}

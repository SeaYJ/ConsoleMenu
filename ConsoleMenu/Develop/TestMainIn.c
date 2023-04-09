#include "main.h"

// 键盘事件处理函数
// 参数：
// 		- 键盘事件对象
// 		- 控制台菜单对象
// 返回值：无
// 注意：
//		键盘事件对象的定义(仅*号表示重要|仅供参考)： 
//		typedef struct _KEY_EVENT_RECORD//键盘事件结构体 
//		{
//		    BOOL  bKeyDown;             //按键状态，true代表键按下，false代表键释放（*） 
//		    WORD  wRepeatCount;         //按键次数（*） 
//		    WORD  wVirtualKeyCode;      //虚拟键（*） 
//		    WORD  wVirtualScanCode;     //虚拟键扫描码
//		    union
//		    {
//		        WCHAR UnicodeChar;      //解释成Unicode宽字符
//		        CHAR  AsciiChar;        //解释成ASCII码字符
//		    } uChar;
//		    DWORD dwControlKeyState;    //控制键状态
//		} KEY_EVENT_RECORD;
void OnKeyPressed(KEY_EVENT_RECORD KeyEvent, CONSOLEMENU* cmenu) {
	
	// 利用 KeyEvent.wVirtualKeyCode 判断按键值（具体参考常用虚拟键代码表） 
	if (KeyEvent.wVirtualKeyCode == VK_UP && // 按下↑键 
		// 注意：一般按下一个按键后会接收到两次该按键的事件，分别为该按键的按下事件和释放事件。
		// 下面的判断：
		// 为1表示当前为键按下而不是键释放 
		KeyEvent.bKeyDown == 1) {
		
		// MenuIndex 表示为被选中的菜单项的索引，所以只要索引在总量的模下减1即可表示选中上移 
		// MenuListNum 表示当前总共拥有的菜单项总数 
		cmenu->Menu->MenuIndex = (cmenu->Menu->MenuIndex-1)%cmenu->Menu->MenuListNum;
		
		//重新打印菜单 
		cmenu->PrintMenu(cmenu->Menu);
		
	} else if (KeyEvent.wVirtualKeyCode == VK_DOWN && 	// 按下↓键 
		KeyEvent.bKeyDown == 1) {
		
		// 选择菜单项的索引+1表示选中上移 
		cmenu->Menu->MenuIndex = (cmenu->Menu->MenuIndex+1)%cmenu->Menu->MenuListNum;
		
		// 重新打印菜单 
		cmenu->PrintMenu(cmenu->Menu);
		
	} else if (KeyEvent.wVirtualKeyCode == VK_ESCAPE && // 按下ESC键 
		KeyEvent.bKeyDown == 1) {
		
		// 刷新控制台信息 
		cmenu->Refresh();
		// 退出程序，参数为退出码
		// 一般 0 表示正常退出 
		exit(0);
		
	} else if (KeyEvent.wVirtualKeyCode == VK_RETURN &&	// 按下回车键 
		KeyEvent.bKeyDown == 1) {
		
		// 刷新控制台信息 
		cmenu->Refresh();
		
		// 通过 if 判断按下回车键(确定选中)时索引的值，从而实现不同菜单项的功能 
		if (cmenu->Menu->MenuIndex == 3) {	// 当选中第4个菜单项时，执行对应操作！
			// 这里对应[退出游戏]
			exit(0);
		} else {							// 不具体一一实现了，可以运行查看这里的功能 
			printf("进入[%s]\n", cmenu->Menu->MenuContent[cmenu->Menu->MenuIndex]); 
		}
		
	} else if (KeyEvent.wVirtualKeyCode == VK_BACK &&
		KeyEvent.bKeyDown == 1) {
		
		// 程序打印菜单 
		cmenu->PrintMenu(cmenu->Menu);
		
	}
}

int main() {
	int i;
	// 开始吧~Hello World！ 
	printf("Hello World!\n");
	
	// 使用方法介绍
	// 创建控制台菜单对象 
	CONSOLEMENU a;
	
	// 初始化对象
	// 参数： 控制台菜单对象的指针
	// 返回值： 成功初始化返回0，失败则返回非0值 
	Init(&a);
	
	// 刷新控制台上的所有信息
	// 参数：无
	// 返回值：无 
	a.Refresh();
	
	// 设置控制台规格
	// 参数：
	// 		- 控制台的宽（以一个英文字符的宽为基本单位）
	// 		- 控制台的高（以一个英文字符的高为基本单位） 
	// 		- 控制台标题（最长 128） 
	// 		- 控制台文字颜色（具体可以查表） 
	// 		- 控制台背景颜色（具体可以查表） 
	// 返回值：成功返回0，失败则返回非0值 
	a.SetConsoleMenuWnd(50, 20, "Demo", GREEN, BLACK);
	
	// 添加一个菜单项
	// 参数：新添加菜单项的名称
	// 返回值：成功返回0，失败则返回非0值  
	a.Menu->AddMenuList("开始游戏");
	a.Menu->AddMenuList("查看排行");
	a.Menu->AddMenuList("规则说明");
	a.Menu->AddMenuList("退出游戏");
	a.Menu->AddMenuList("待测试项[2]"); 
	
	// 插入一个菜单项
	// 参数：
	// 		- 待插入菜单项的名称 
	//      - 待插入位置的索引（从0开始） 
	// 返回值：成功返回0，失败则返回非0值
	// 注意：这里的菜单项的索引是从0开始计算的！第一个菜单项的名称应该是0，第二个是1，后面以此类推！ 
	a.Menu->InsertMenuList("待测试项[1]", 4); 
	
	// 交换两个菜单项的位置
	// 参数：
	// 		- 待交换菜单项的索引（从0开始）
	// 		- 待交换菜单项的索引（从0开始） 
	// 返回值：成功返回0，失败则返回非0值 
	a.Menu->SwapMenuList(4, 5);
	
	// 删除一个菜单项
	// 参数：待删除菜单项的索引（从0开始）
	// 返回值：成功返回0，失败则返回非0值 
	a.Menu->DelMenuList(4);
	a.Menu->DelMenuList(4);

//  // 这是一个例子关于“如何访问菜单项具体的内容？”
//  // 很明显，菜单是以数组的方式存储的，但是并不完全是数组 
//	for (i = 0; i < a.Menu->MenuListNum; i++) {
//		// 通过数组索引访问菜单中的菜单项 
//		printf("a.Menu.MenuContent[%d]=%s\n", i, a.Menu->MenuContent[i]);
//	}

	// 打印菜单
	// 参数：菜单对象
	// 返回值：无 
	a.PrintMenu(a.Menu);
	
	// 运行键盘事件监听，从而实现键盘控制功能
	// 参数：控制台菜单对象
	// 返回值：无 
	// 注意：这里需要重新编写  OnKeyPressed 函数，从而实现自己的功能 
	RunKeyEvent(&a);
	
	return 0;
}

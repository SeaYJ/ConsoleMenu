#include "main.h"

// �����¼�������
// ������
// 		- �����¼�����
// 		- ����̨�˵�����
// ����ֵ����
// ע�⣺
//		�����¼�����Ķ���(��*�ű�ʾ��Ҫ|�����ο�)�� 
//		typedef struct _KEY_EVENT_RECORD//�����¼��ṹ�� 
//		{
//		    BOOL  bKeyDown;             //����״̬��true��������£�false������ͷţ�*�� 
//		    WORD  wRepeatCount;         //����������*�� 
//		    WORD  wVirtualKeyCode;      //�������*�� 
//		    WORD  wVirtualScanCode;     //�����ɨ����
//		    union
//		    {
//		        WCHAR UnicodeChar;      //���ͳ�Unicode���ַ�
//		        CHAR  AsciiChar;        //���ͳ�ASCII���ַ�
//		    } uChar;
//		    DWORD dwControlKeyState;    //���Ƽ�״̬
//		} KEY_EVENT_RECORD;
void OnKeyPressed(KEY_EVENT_RECORD KeyEvent, CONSOLEMENU* cmenu) {
	
	// ���� KeyEvent.wVirtualKeyCode �жϰ���ֵ������ο��������������� 
	if (KeyEvent.wVirtualKeyCode == VK_UP && // ���¡��� 
		// ע�⣺һ�㰴��һ�����������յ����θð������¼����ֱ�Ϊ�ð����İ����¼����ͷ��¼���
		// ������жϣ�
		// Ϊ1��ʾ��ǰΪ�����¶����Ǽ��ͷ� 
		KeyEvent.bKeyDown == 1) {
		
		// MenuIndex ��ʾΪ��ѡ�еĲ˵��������������ֻҪ������������ģ�¼�1���ɱ�ʾѡ������ 
		// MenuListNum ��ʾ��ǰ�ܹ�ӵ�еĲ˵������� 
		cmenu->Menu->MenuIndex = (cmenu->Menu->MenuIndex-1)%cmenu->Menu->MenuListNum;
		
		//���´�ӡ�˵� 
		cmenu->PrintMenu(cmenu->Menu);
		
	} else if (KeyEvent.wVirtualKeyCode == VK_DOWN && 	// ���¡��� 
		KeyEvent.bKeyDown == 1) {
		
		// ѡ��˵��������+1��ʾѡ������ 
		cmenu->Menu->MenuIndex = (cmenu->Menu->MenuIndex+1)%cmenu->Menu->MenuListNum;
		
		// ���´�ӡ�˵� 
		cmenu->PrintMenu(cmenu->Menu);
		
	} else if (KeyEvent.wVirtualKeyCode == VK_ESCAPE && // ����ESC�� 
		KeyEvent.bKeyDown == 1) {
		
		// ˢ�¿���̨��Ϣ 
		cmenu->Refresh();
		// �˳����򣬲���Ϊ�˳���
		// һ�� 0 ��ʾ�����˳� 
		exit(0);
		
	} else if (KeyEvent.wVirtualKeyCode == VK_RETURN &&	// ���»س��� 
		KeyEvent.bKeyDown == 1) {
		
		// ˢ�¿���̨��Ϣ 
		cmenu->Refresh();
		
		// ͨ�� if �жϰ��»س���(ȷ��ѡ��)ʱ������ֵ���Ӷ�ʵ�ֲ�ͬ�˵���Ĺ��� 
		if (cmenu->Menu->MenuIndex == 3) {	// ��ѡ�е�4���˵���ʱ��ִ�ж�Ӧ������
			// �����Ӧ[�˳���Ϸ]
			exit(0);
		} else {							// ������һһʵ���ˣ��������в鿴����Ĺ��� 
			printf("����[%s]\n", cmenu->Menu->MenuContent[cmenu->Menu->MenuIndex]); 
		}
		
	} else if (KeyEvent.wVirtualKeyCode == VK_BACK &&
		KeyEvent.bKeyDown == 1) {
		
		// �����ӡ�˵� 
		cmenu->PrintMenu(cmenu->Menu);
		
	}
}

int main() {
	int i;
	// ��ʼ��~Hello World�� 
	printf("Hello World!\n");
	
	// ʹ�÷�������
	// ��������̨�˵����� 
	CONSOLEMENU a;
	
	// ��ʼ������
	// ������ ����̨�˵������ָ��
	// ����ֵ�� �ɹ���ʼ������0��ʧ���򷵻ط�0ֵ 
	Init(&a);
	
	// ˢ�¿���̨�ϵ�������Ϣ
	// ��������
	// ����ֵ���� 
	a.Refresh();
	
	// ���ÿ���̨���
	// ������
	// 		- ����̨�Ŀ���һ��Ӣ���ַ��Ŀ�Ϊ������λ��
	// 		- ����̨�ĸߣ���һ��Ӣ���ַ��ĸ�Ϊ������λ�� 
	// 		- ����̨���⣨� 128�� 
	// 		- ����̨������ɫ��������Բ�� 
	// 		- ����̨������ɫ��������Բ�� 
	// ����ֵ���ɹ�����0��ʧ���򷵻ط�0ֵ 
	a.SetConsoleMenuWnd(50, 20, "Demo", GREEN, BLACK);
	
	// ���һ���˵���
	// ����������Ӳ˵��������
	// ����ֵ���ɹ�����0��ʧ���򷵻ط�0ֵ  
	a.Menu->AddMenuList("��ʼ��Ϸ");
	a.Menu->AddMenuList("�鿴����");
	a.Menu->AddMenuList("����˵��");
	a.Menu->AddMenuList("�˳���Ϸ");
	a.Menu->AddMenuList("��������[2]"); 
	
	// ����һ���˵���
	// ������
	// 		- ������˵�������� 
	//      - ������λ�õ���������0��ʼ�� 
	// ����ֵ���ɹ�����0��ʧ���򷵻ط�0ֵ
	// ע�⣺����Ĳ˵���������Ǵ�0��ʼ����ģ���һ���˵��������Ӧ����0���ڶ�����1�������Դ����ƣ� 
	a.Menu->InsertMenuList("��������[1]", 4); 
	
	// ���������˵����λ��
	// ������
	// 		- �������˵������������0��ʼ��
	// 		- �������˵������������0��ʼ�� 
	// ����ֵ���ɹ�����0��ʧ���򷵻ط�0ֵ 
	a.Menu->SwapMenuList(4, 5);
	
	// ɾ��һ���˵���
	// ��������ɾ���˵������������0��ʼ��
	// ����ֵ���ɹ�����0��ʧ���򷵻ط�0ֵ 
	a.Menu->DelMenuList(4);
	a.Menu->DelMenuList(4);

//  // ����һ�����ӹ��ڡ���η��ʲ˵����������ݣ���
//  // �����ԣ��˵���������ķ�ʽ�洢�ģ����ǲ�����ȫ������ 
//	for (i = 0; i < a.Menu->MenuListNum; i++) {
//		// ͨ�������������ʲ˵��еĲ˵��� 
//		printf("a.Menu.MenuContent[%d]=%s\n", i, a.Menu->MenuContent[i]);
//	}

	// ��ӡ�˵�
	// �������˵�����
	// ����ֵ���� 
	a.PrintMenu(a.Menu);
	
	// ���м����¼��������Ӷ�ʵ�ּ��̿��ƹ���
	// ����������̨�˵�����
	// ����ֵ���� 
	// ע�⣺������Ҫ���±�д  OnKeyPressed �������Ӷ�ʵ���Լ��Ĺ��� 
	RunKeyEvent(&a);
	
	return 0;
}

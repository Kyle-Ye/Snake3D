#include "../Head/MainWindow.h"
int main()
{
	MainWindow mWindow;
	if (mWindow.success) 
	{
		mWindow.MainLoop();
	}
	else
	{
		std::cout << "��������ʧ��" << std::endl;
	}
	return 0;
}

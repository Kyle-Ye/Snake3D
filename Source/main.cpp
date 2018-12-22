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
		std::cout << "´´½¨´°¿ÚÊ§°Ü" << std::endl;
	}
	return 0;
}

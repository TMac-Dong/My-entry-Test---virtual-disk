// CConsole.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MyString.h"
#include "VirtualDisk.h"
#include "CControl.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Microsoft Windows [版本 1.1.1]" << std::endl;
	std::cout << "版本所有 <c> 2015 Microsoft Corporation 保留所有权利。" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	char *pChar = new char[512];
	CControl *CmdConrol = new CControl();

	while(1)
	{
		CmdConrol->DisplayCurPath();
		std::cin.getline(pChar,512);

		if (strcmp(pChar,"exit") != 0)
		{		
			MyString pStr(pChar);
			pStr.DivideStringToCmd();
			CmdConrol->SetCommand(pStr);
			CmdConrol->StartCommand();
			//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
		}
		else
		{
			break;
		}
	}

	if(pChar)
	{
		delete []pChar;
		pChar = NULL;
	}
 	if (CmdConrol)
 	{
 		delete CmdConrol;
 		CmdConrol = NULL;
 	}
	return 0;
}
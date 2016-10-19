// CConsole.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MyString.h"
#include "VirtualDisk.h"
#include "CControl.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Microsoft Windows [�汾 1.1.1]" << std::endl;
	std::cout << "�汾���� <c> 2015 Microsoft Corporation ��������Ȩ����" << std::endl;
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
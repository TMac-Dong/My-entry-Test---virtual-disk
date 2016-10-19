//////////////////////////////////////////////////
//FileName	: CControl.cpp
//Author	: zhangyandong
//Date		: 2015/3/27
//Describe	: 命令对象处理控制
///////////////////////////////////////////
#include "stdafx.h"
#include "CControl.h"
#include "MyString.h"
#include "VirtualDisk.h"
#include "MakedirCommand.h"
#include "DirCommand.h"
#include "CDCommand.h"
#include "DelCommand.h"
#include "RmdirCommand.h"
#include "CopyCommand.h"
#include "CompareCommand.h"
#include <iostream>

CControl::CControl()
: pString(NULL)
, pDisk(new CVirtualDisk())
{

}

CControl::~CControl()
{
	if (pString)
	{
		delete pString;
		pString = NULL;
	}
	if (pDisk)
	{
		delete pDisk;
		pDisk = NULL;
	}
}

const MyString* CControl::GetCommand() const
{
	return pString;
}

void CControl::SetCommand(const MyString String)
{
	pString = new MyString(String);
}

void CControl::StartCommand()
{
	if(!pString->IsDivideCmd())
	{
		std::cout<<"您的命令字符串还没有分割处理，请先执行处理！"<< std::endl;
		return ;
	}
	
	if(strcmp(pString->GetDividedCmdByType(MyString::CMDTYPE_MAINCMD),"mkdir") == 0)
	{
// 		CMakedirCommand* cmd = new CMakedirCommand(pDisk, pString ,pString->GetCmdType());
// 		cmd->Excute();
		mType = Factory::TypeMakedir;
	}
	else if(strcmp(pString->GetDividedCmdByType(MyString::CMDTYPE_MAINCMD),"dir") == 0)
	{
// 		CDirCommand* cmd = new CDirCommand(pDisk, pString ,pString->GetCmdType());
// 		cmd->Excute();
		mType = Factory::TypeDir;
	}
	else if(strcmp(pString->GetDividedCmdByType(MyString::CMDTYPE_MAINCMD),"cd") == 0)
	{
// 		CDCommand* cmd = new CDCommand(pDisk, pString ,pString->GetCmdType);
// 		cmd->Excute();
		mType = Factory::TypeCD;
	}
	else if(strcmp(pString->GetDividedCmdByType(MyString::CMDTYPE_MAINCMD),"del") == 0)
	{
// 		CDelCommand* cmd = new CDelCommand(pDisk, pString ,pString->GetCmdType());
// 		cmd->Excute();
		mType = Factory::TypeDel;
	}
	else if(strcmp(pString->GetDividedCmdByType(MyString::CMDTYPE_MAINCMD),"rmdir") == 0)
	{
		//CRmdirCommand* cmd = new CRmdirCommand(pDisk, pString ,pString->GetCmdType());
		//cmd->Excute();
		mType = Factory::TypeRmdir;
	}
	else if(strcmp(pString->GetDividedCmdByType(MyString::CMDTYPE_MAINCMD),"copy") == 0)
	{
		//CCopyCommand* cmd = new CCopyCommand(pDisk, pString ,pString->GetCmdType());
		//cmd->Excute();
		mType = Factory::TypeCopy;
	}
	else if(strcmp(pString->GetDividedCmdByType(MyString::CMDTYPE_MAINCMD),"compare") == 0)
	{
		//CCompareCommand* cmd = new CCompareCommand(pDisk, pString ,pString->GetCmdType());
		//cmd->Excute();
		mType = Factory::TypeCompare;
	}
	else
	{
		std::cout << "输入无效的命令" << std::endl;
		return;
	}

	Command* cmd = CreateProduct(mType,pDisk,pString,pString->GetCmdType());
	if (cmd != NULL)
	{
		cmd->Excute();
		delete cmd;
		cmd = NULL;
	}
}

void CControl::DisplayCurPath()
{
	if (CVirtualDisk::GetSingletonPtr())
	{
		CVirtualDisk::GetSingletonPtr()->PrintCurrentPath();
	}
}
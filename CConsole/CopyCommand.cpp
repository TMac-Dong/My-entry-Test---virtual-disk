//////////////////////////////////////////////////
//FileName	: CopyCommand.hcpp
//Author	: zhangyandong
//Date		: 2015/3/30
//Describe	: 虚拟磁盘文件操作
///////////////////////////////////////////
#include "stdafx.h"
#include "Command.h"
#include "MyString.h"
#include "CopyCommand.h"
#include <string>
#include <assert.h>
#include "VirtualDisk.h"
#include <iostream>

CCopyCommand::CCopyCommand()
: SimpleCommand(&CCopyCommand::Invoke)
, m_pStrCmd(NULL)
, m_nType(-1)
{

}

CCopyCommand::CCopyCommand(CVirtualDisk *dis,MyString* pname,int type)
: SimpleCommand(&CCopyCommand::Invoke)
{
	m_pStrCmd = pname;
	assert(m_pStrCmd);
	m_nType = type;
}

CCopyCommand::~CCopyCommand()
{
 	if (m_pStrCmd)
 	{
 		delete m_pStrCmd;
 		m_pStrCmd = NULL;
 	}
	m_pStrCmd = NULL;
	m_nType = -1;
}

void CCopyCommand::Invoke()
{
	if (CVirtualDisk::GetSingletonPtr())
	{
		if (m_nType == MyString::CMDTYPE_DOUBPARA)
		{
			//CVirtualDisk::GetSingletonPtr()->_CopyFromInside(m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_DOUBPARA),m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_ONEPARA));
			
			CVirtualDisk::GetSingletonPtr()->
				ExcuteCopy(m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_DOUBPARA),m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_ONEPARA));

		}
		else if (m_nType == MyString::CMDTYPE_ONEPARA)
		{
			CVirtualDisk::GetSingletonPtr()->
				ExcuteCopy(NULL,m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_ONEPARA));
		}
		else
		{
			std::cout << "输入的格式不对" << std::endl;
		}
	}
}
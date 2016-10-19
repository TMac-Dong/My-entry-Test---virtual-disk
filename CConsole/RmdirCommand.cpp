//////////////////////////////////////////////////
//FileName	: RmdirCommand.hcpp
//Author	: zhangyandong
//Date		: 2015/3/30
//Describe	: 虚拟磁盘文件操作
///////////////////////////////////////////
#include "stdafx.h"
#include "Command.h"
#include "MyString.h"
#include "RmdirCommand.h"
#include <string>
#include <assert.h>
#include "VirtualDisk.h"
#include <iostream>

CRmdirCommand::CRmdirCommand()
: SimpleCommand(&CRmdirCommand::Invoke)
, m_pStrCmd(NULL)
, m_nType(-1)
{

}

CRmdirCommand::CRmdirCommand(CVirtualDisk *dis,MyString* pname,int type)
: SimpleCommand(&CRmdirCommand::Invoke)
{
	m_pStrCmd = pname;
	assert(m_pStrCmd);
	m_nType = type;
}

CRmdirCommand::~CRmdirCommand()
{
	if (m_pStrCmd)
	{
		delete m_pStrCmd;
		m_pStrCmd = NULL;
	}
	m_nType = -1;
}

void CRmdirCommand::Invoke()
{
	if (CVirtualDisk::GetSingletonPtr())
	{
		if (m_nType == MyString::CMDTYPE_ONEPARA)
		{
			CVirtualDisk::GetSingletonPtr()->DelPath(m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_ONEPARA));
		}
		else if (m_nType == MyString::CMDTYPE_DOUBPARA)
		{
			if (strcmp(m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_ONEPARA),"/s") == 0)
			{
				CVirtualDisk::GetSingletonPtr()->DelPath(m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_DOUBPARA),true);
			}
			else
			{
				std::cout << "输入格式不对" << std::endl;
			}
		}
	}
}
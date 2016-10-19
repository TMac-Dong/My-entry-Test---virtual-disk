//////////////////////////////////////////////////
//FileName	: DirCommand.hcpp
//Author	: zhangyandong
//Date		: 2015/3/30
//Describe	: ÐéÄâ´ÅÅÌÎÄ¼þ²Ù×÷
///////////////////////////////////////////
#include "stdafx.h"
#include "Command.h"
#include "MyString.h"
#include "DirCommand.h"
#include <string>
#include <assert.h>
#include "VirtualDisk.h"
#include <iostream>

CDirCommand::CDirCommand()
: SimpleCommand(&CDirCommand::Invoke)
, m_pStrCmd(NULL)
, m_nType(-1)
{

}

CDirCommand::CDirCommand(CVirtualDisk *dis,MyString* pname,int type)
: SimpleCommand(&CDirCommand::Invoke)
{
	m_pStrCmd = pname;
	assert(m_pStrCmd);
	m_nType = type;
}

CDirCommand::~CDirCommand()
{
	if (m_pStrCmd)
	{
		delete m_pStrCmd;
		m_pStrCmd = NULL;
	}
	m_nType = -1;
}

void CDirCommand::Invoke()
{
	if (CVirtualDisk::GetSingletonPtr())
	{
		if (m_nType == MyString::CMDTYPE_MAINCMD)
		{
			CVirtualDisk::GetSingletonPtr()->Display(CVirtualDisk::ALL_FILEDIR,NULL,false);
		}
		else if (m_nType == MyString::CMDTYPE_ONEPARA)
		{
			if (strcmp(m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_ONEPARA),"/s") == 0)
			{
				CVirtualDisk::GetSingletonPtr()->Display(CVirtualDisk::ONLY_FILE,NULL,true);
			}
			else if (strcmp(m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_ONEPARA),"/ad") == 0)
			{
				CVirtualDisk::GetSingletonPtr()->Display(CVirtualDisk::ONLY_DIR,NULL,true);
			}
			else
			{
				CVirtualDisk::GetSingletonPtr()->Display(CVirtualDisk::ALL_FILEDIR, m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_ONEPARA));
			}
		}
		else if (m_nType == MyString::CMDTYPE_DOUBPARA)
		{
			if (strcmp(m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_ONEPARA),"/s") == 0)
			{
				CVirtualDisk::GetSingletonPtr()->Display(CVirtualDisk::ONLY_FILE,m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_DOUBPARA),true);
			}
			else if (strcmp(m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_ONEPARA),"/ad") == 0)
			{
				CVirtualDisk::GetSingletonPtr()->Display(CVirtualDisk::ONLY_DIR,m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_DOUBPARA),true);
			}
			else
			{
				CVirtualDisk::GetSingletonPtr()->Display(CVirtualDisk::ALL_FILEDIR,m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_ONEPARA));
			}
		}
	}
}
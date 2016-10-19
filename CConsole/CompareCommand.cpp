//////////////////////////////////////////////////
//FileName	: CompareCommand.cpp
//Author	: zhangyandong
//Date		: 2015/3/30
//Describe	: ÐéÄâ´ÅÅÌÎÄ¼þ²Ù×÷
///////////////////////////////////////////
#include "stdafx.h"
#include "Command.h"
#include "MyString.h"
#include "CompareCommand.h"
#include <string>
#include <assert.h>
#include "VirtualDisk.h"
#include <iostream>

CCompareCommand::CCompareCommand()
: SimpleCommand(&CCompareCommand::Invoke)
, m_pStrCmd(NULL)
, m_nType(-1)
{

}

CCompareCommand::CCompareCommand(CVirtualDisk *dis,MyString* pname,int type)
: SimpleCommand(&CCompareCommand::Invoke)
{
	m_pStrCmd = pname;
	assert(m_pStrCmd);
	m_nType = type;
}

CCompareCommand::~CCompareCommand()
{
	if (m_pStrCmd)
	{
		delete m_pStrCmd;
		m_pStrCmd = NULL;
	}
	m_nType = -1;
}

void CCompareCommand::Invoke()
{
	if (CVirtualDisk::GetSingletonPtr())
	{
		if (m_nType == MyString::CMDTYPE_DOUBPARA)
		{
			CVirtualDisk::GetSingletonPtr()->Compare(m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_DOUBPARA),m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_ONEPARA));
		}
	}
}
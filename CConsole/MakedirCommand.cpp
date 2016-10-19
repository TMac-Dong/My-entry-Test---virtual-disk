//////////////////////////////////////////////////
//FileName	: MakedirCommand.cpp
//Author	: zhangyandong
//Date		: 2015/3/30
//Describe	: ÐéÄâ´ÅÅÌÎÄ¼þ²Ù×÷
///////////////////////////////////////////
#include "stdafx.h"
#include "Command.h"
#include "MyString.h"
#include "MakedirCommand.h"
#include <string>
#include <assert.h>
#include "VirtualDisk.h"
#include <iostream>

CMakedirCommand::CMakedirCommand()
: SimpleCommand(&CMakedirCommand::Invoke)
, m_pStrCmd(NULL)
, m_nType(-1)
{

}

CMakedirCommand::CMakedirCommand(CVirtualDisk *dis,MyString* pname,int type)
: SimpleCommand(&CMakedirCommand::Invoke)
{
	m_pStrCmd = pname;
	assert(m_pStrCmd);
	m_nType = type;
}

CMakedirCommand::~CMakedirCommand()
{
	if (m_pStrCmd)
	{
		delete m_pStrCmd;
		m_pStrCmd = NULL;
	}
	m_nType = -1;
}

void CMakedirCommand::Invoke()
{
	if (CVirtualDisk::GetSingletonPtr())
	{
		CVirtualDisk::GetSingletonPtr()->Mkdir(m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_ONEPARA));
	}
}
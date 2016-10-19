//////////////////////////////////////////////////
//FileName	: CDCommand.cpp 
//Author	: zhangyandong
//Date		: 2015/3/30
//Describe	: ÐéÄâ´ÅÅÌÎÄ¼þ²Ù×÷cd
///////////////////////////////////////////
#include "stdafx.h"
#include "Command.h"
#include "MyString.h"
#include "CDCommand.h"
#include <string>
#include <assert.h>
#include "VirtualDisk.h"
#include <iostream>

CDCommand::CDCommand()
	: SimpleCommand(&CDCommand::Invoke)
	, m_pStrCmd(NULL)
	, m_nType(-1)
{

}

CDCommand::CDCommand(CVirtualDisk *dis,MyString* pname,int type)
: SimpleCommand(&CDCommand::Invoke)
{
	m_pStrCmd = pname;
	assert(m_pStrCmd);
	m_nType = type;
}

CDCommand::~CDCommand()
{
	if (m_pStrCmd)
	{
		delete m_pStrCmd;
		m_pStrCmd = NULL;
	}
	m_nType = -1;
}

void CDCommand::Invoke()
{
	if (CVirtualDisk::GetSingletonPtr())
	{
		CVirtualDisk::GetSingletonPtr()->CDPath(m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_ONEPARA));
	}
}
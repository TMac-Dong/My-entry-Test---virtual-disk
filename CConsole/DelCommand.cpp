//////////////////////////////////////////////////
//FileName	: DelCommand.cpp 
//Author	: zhangyandong
//Date		: 2015/3/30
//Describe	: ÐéÄâ´ÅÅÌÎÄ¼þ²Ù×÷Del
///////////////////////////////////////////
#include "stdafx.h"
#include "Command.h"
#include "MyString.h"
#include "DelCommand.h"
#include <string>
#include <assert.h>
#include "VirtualDisk.h"
#include <iostream>

CDelCommand::CDelCommand()
: SimpleCommand(&CDelCommand::Invoke)
, m_pStrCmd(NULL)
, m_nType(-1)
{

}

CDelCommand::CDelCommand(CVirtualDisk *dis,MyString* pname,int type)
: SimpleCommand(&CDelCommand::Invoke)
{
	m_pStrCmd = pname;
	assert(m_pStrCmd);
	m_nType = type;
}

CDelCommand::~CDelCommand()
{
	if (m_pStrCmd)
	{
		delete m_pStrCmd;
		m_pStrCmd = NULL;
	}
	m_nType = -1;
}

void CDelCommand::Invoke()
{
	if (CVirtualDisk::GetSingletonPtr())
	{
		CVirtualDisk::GetSingletonPtr()->DelFile(m_pStrCmd->GetDividedCmdByType(MyString::CMDTYPE_ONEPARA));
	}
}
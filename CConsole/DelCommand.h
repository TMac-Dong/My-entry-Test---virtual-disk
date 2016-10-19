//////////////////////////////////////////////////
//FileName	: DelCommand.h 
//Author	: zhangyandong
//Date		: 2015/3/30
//Describe	: ÐéÄâ´ÅÅÌÎÄ¼þ²Ù×÷Del
///////////////////////////////////////////
#pragma once

#include "Command.h"
#include "VirtualDisk.h"

class MyString;
class CDelCommand: public SimpleCommand<CDelCommand>
{
public:
	CDelCommand();
	CDelCommand(CVirtualDisk *dis,MyString* pname,int type);
	~CDelCommand();
	void Invoke();

public:
	MyString*	m_pStrCmd;
	int			m_nType;
};
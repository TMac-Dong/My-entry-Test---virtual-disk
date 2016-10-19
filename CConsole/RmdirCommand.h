//////////////////////////////////////////////////
//FileName	: RmdirCommand.h 
//Author	: zhangyandong
//Date		: 2015/3/30
//Describe	: ÐéÄâ´ÅÅÌÎÄ¼þ²Ù×÷Rmdir
///////////////////////////////////////////
#pragma once

#include "Command.h"
#include "VirtualDisk.h"

class MyString;
class CRmdirCommand: public SimpleCommand<CRmdirCommand>
{
public:
	CRmdirCommand();
	CRmdirCommand(CVirtualDisk *dis,MyString* pname,int type);
	~CRmdirCommand();
	void Invoke();

public:
	MyString*	m_pStrCmd;
	int			m_nType;
};
//////////////////////////////////////////////////
//FileName	: DirCommand.h 
//Author	: zhangyandong
//Date		: 2015/3/30
//Describe	: ÐéÄâ´ÅÅÌÎÄ¼þ²Ù×÷
///////////////////////////////////////////
#pragma once

#include "Command.h"
#include "VirtualDisk.h"

class MyString;
class CDirCommand: public SimpleCommand<CDirCommand>
{
public:
	CDirCommand();
	CDirCommand(CVirtualDisk *dis,MyString* pname,int type);
	~CDirCommand();
	void Invoke();

public:
	MyString*	m_pStrCmd;
	int			m_nType;
};
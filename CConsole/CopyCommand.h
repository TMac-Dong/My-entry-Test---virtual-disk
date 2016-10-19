//////////////////////////////////////////////////
//FileName	: CopyCommand.h 
//Author	: zhangyandong
//Date		: 2015/3/30
//Describe	: ÐéÄâ´ÅÅÌÎÄ¼þ²Ù×÷Copy
///////////////////////////////////////////
#pragma once
#include "Command.h"
#include "VirtualDisk.h"

class MyString;
class CCopyCommand: public SimpleCommand<CCopyCommand>
{
public:
	CCopyCommand();
	CCopyCommand(CVirtualDisk *dis,MyString* pname,int type);
	~CCopyCommand();
	void Invoke();

public:
	MyString*	m_pStrCmd;
	int			m_nType;
};
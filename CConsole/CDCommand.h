//////////////////////////////////////////////////
//FileName	: CDCommand.h .h
//Author	: zhangyandong
//Date		: 2015/3/30
//Describe	: ÃüÁî²Ù×÷cd
///////////////////////////////////////////
#pragma once
#include "Command.h"
#include "VirtualDisk.h"

class MyString;
class CDCommand : public SimpleCommand<CDCommand>
{
public:
	CDCommand();
	CDCommand(CVirtualDisk *dis,MyString* pname,int type);
	~CDCommand();
	void Invoke();

public:
	MyString*	m_pStrCmd;
	int		m_nType;
};
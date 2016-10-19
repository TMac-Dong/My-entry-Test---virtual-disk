//////////////////////////////////////////////////
//FileName	: CompareCommand.h 
//Author	: zhangyandong
//Date		: 2015/3/30
//Describe	: ��������ļ�����Copy
///////////////////////////////////////////
#pragma once
#include "Command.h"
#include "VirtualDisk.h"

class MyString;
class CCompareCommand: public SimpleCommand<CCompareCommand>
{
public:
	CCompareCommand();
	CCompareCommand(CVirtualDisk *dis,MyString* pname,int type);
	~CCompareCommand();
	void Invoke();

public:
	MyString*	m_pStrCmd;
	int			m_nType;
};
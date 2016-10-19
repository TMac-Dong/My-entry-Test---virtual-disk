//////////////////////////////////////////////////
//FileName	: MakedirCommand.h 
//Author	: zhangyandong
//Date		: 2015/3/30
//Describe	: ÐéÄâ´ÅÅÌÎÄ¼þ²Ù×÷
///////////////////////////////////////////
#pragma  once
#include "Command.h"
#include "VirtualDisk.h"

class MyString;
class CMakedirCommand : public SimpleCommand<CMakedirCommand>
{
public:
	CMakedirCommand();
	CMakedirCommand(CVirtualDisk *dis,MyString* pname,int type);
	~CMakedirCommand();
	void Invoke();

public:
	MyString*	m_pStrCmd;
	int		m_nType;
};
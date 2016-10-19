//////////////////////////////////////////////////
//FileName	: CControl.h
//Author	: zhangyandong
//Date		: 2015/3/27
//Describe	: 命令对象处理控制
///////////////////////////////////////////
#pragma  once
#include "Factory.h"
#include "SingleTon.h"
#include "Command.h"

class MyString;
class CVirtualDisk;
class CControl : public Factory, public CSingleton<CControl>
{
public:
	CControl();
	~CControl();

	const MyString* GetCommand() const;
	void SetCommand(const MyString String);
	void StartCommand();
	void DisplayCurPath();

protected:
	MyString* pString;
	CVirtualDisk* pDisk;
};
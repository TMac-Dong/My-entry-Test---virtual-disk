//////////////////////////////////////////////////
//FileName	: Command.h
//Author	: zhangyandong
//Date		: 2015/3/27
//Describe	: commandģʽ
///////////////////////////////////////////
#pragma  once

class Command
{
public:
	virtual ~Command() {};
	virtual void Excute() = 0;

protected:
	Command() {};
};

template <typename T>
class SimpleCommand:public Command
{
public:
	typedef void (T::* Action)();
	SimpleCommand() {}
	SimpleCommand(T* rev,Action act)
	{
		_rev = rev;
		_act = act;
	}
	virtual void Excute()
	{
		(_rev->* _act)();
	}
	virtual ~SimpleCommand()
	{
		delete _rev;
		_rev = NULL;
	}

private:
	T* _rev;
	Action _act;
};
//////////////////////////////////////////////////
//FileName	: Command.h
//Author	: zhangyandong
//Date		: 2015/3/27
//Describe	: commandģʽ
///////////////////////////////////////////
#pragma  once

#if			defined(ASSERT)
#define		CMD_ASSERT ASSERT
#else
#define		CMD_ASSERT(val)
#endif

class Command
{
public:
	virtual ~Command() {};
	virtual void Excute() = 0;

protected:
	Command() {};
};

template <typename T>
class SimpleCommand : public Command
{
public:
	typedef T ThisClass;

protected:
	static T* m_pCommand;

public:
	typedef void (T::* Action)();
	SimpleCommand() 
	{
			CMD_ASSERT( !m_pCommand );
#if defined( _MSC_VER ) && _MSC_VER < 1200	 
			int offset = (int)(T*)1 - (int)(SimpleCommand <T>*)(T*)1;
			m_pCommand = (T*)((int)this + offset);
#else
			m_pCommand = static_cast< T* >( this );
#endif
	}

	SimpleCommand(Action act)
	{
		CMD_ASSERT( !m_pCommand );
#if defined( _MSC_VER ) && _MSC_VER < 1200	 
		int offset = (int)(T*)1 - (int)(SimpleCommand <T>*)(T*)1;
		m_pCommand = (T*)((int)this + offset);
#else
		m_pCommand = static_cast< T* >( this );
#endif

		_act = act;
	}
	virtual void Excute()
	{
		(m_pCommand->* _act)();
	}
	~SimpleCommand()
	{
		if (m_pCommand != NULL)
		{
			//delete m_pCommand;
			m_pCommand = NULL;
		}
	}

private:
	Action _act;
};

template <typename T >  T* SimpleCommand<T>::m_pCommand=NULL ;
//////////////////////////////////////////////////
//FileName	: MyString.h
//Author	: zhangyandong
//Date		: 2015/3/25
//Describe	: ×Ö·û´®Àà
///////////////////////////////////////////
#pragma  once

class MyString
{
public:
	enum COMMANDTYPE
	{
		CMDTYPE_INVALID = -1,
		CMDTYPE_MAINCMD = 0,
		CMDTYPE_ONEPARA = 1,
		CMDTYPE_DOUBPARA = 2,
		CMDTYPE_ALLCMD	= 3
	};

public:
	MyString();
	MyString(const char* strData);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	~MyString();

public:
	void AddString(char* data);
	bool IsEmpty();
	bool IsDivideCmd();
	const char* GetDividedCmdByType(COMMANDTYPE nType);
	void DivideStringToCmd();
	const COMMANDTYPE GetCmdType();

private:
	COMMANDTYPE m_nCmdType;
	char* m_pData;
	bool m_bDivided;

	char* m_pStrMainCmd;
	char* m_pStrFirstPara;
	char* m_pStrSecondPara;
};
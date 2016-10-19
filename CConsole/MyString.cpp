//////////////////////////////////////////////////
//FileName	: MyString.cpp
//Author	: zhangyandong
//Date		: 2015/3/25
//Describe	: ×Ö·û´®Àà
///////////////////////////////////////////
#include "stdafx.h"
#include <assert.h>
#include <string.h>
#include <iostream>
#include "MyString.h"
#include <Windows.h>

MyString::MyString()
: m_nCmdType(CMDTYPE_INVALID)
, m_pData(NULL)
, m_bDivided(false)
{
	m_pStrMainCmd = new char[UCHAR_MAX];
	m_pStrFirstPara = new char[UCHAR_MAX];
	m_pStrSecondPara = new char[UCHAR_MAX];

	memset(m_pStrMainCmd,0,UCHAR_MAX);
	memset(m_pStrFirstPara,0,UCHAR_MAX);
	memset(m_pStrSecondPara,0,UCHAR_MAX);

	*m_pStrMainCmd = '\0';
	*m_pStrFirstPara ='\0';
	*m_pStrSecondPara ='\0';
}

MyString::MyString(const char* strData)
: m_nCmdType(CMDTYPE_INVALID)
{
	if (strData == NULL)
	{
		m_pData = new char[256];
		assert(m_pData);
		*m_pData = '\0';
	}
	else
	{
		m_pData = new char[256];
		assert(m_pData);
		strcpy_s(m_pData,strlen(strData) + 1,strData);
	}
	m_bDivided = false;


	m_pStrMainCmd = new char[UCHAR_MAX];
	m_pStrFirstPara = new char[UCHAR_MAX];
	m_pStrSecondPara = new char[UCHAR_MAX];

	memset(m_pStrMainCmd,0,UCHAR_MAX);
	memset(m_pStrFirstPara,0,UCHAR_MAX);
	memset(m_pStrSecondPara,0,UCHAR_MAX);

	*m_pStrMainCmd = '\0';
	*m_pStrFirstPara ='\0';
	*m_pStrSecondPara ='\0';
}

MyString::MyString(const MyString& other)
{
	if (other.m_pData)
	{
		m_pData = new char[256];
		assert(m_pData);
		strcpy_s(m_pData,strlen(other.m_pData) + 1, other.m_pData);
	}
	else
	{
		m_pData = new char[256];
		assert(m_pData);
		*m_pData = '\0';
	}
	m_bDivided = other.m_bDivided;


	m_pStrMainCmd = new char[UCHAR_MAX];
	m_pStrFirstPara = new char[UCHAR_MAX];
	m_pStrSecondPara = new char[UCHAR_MAX];
	m_nCmdType = other.m_nCmdType; 

	memset(m_pStrMainCmd,0,UCHAR_MAX);
	memset(m_pStrFirstPara,0,UCHAR_MAX);
	memset(m_pStrSecondPara,0,UCHAR_MAX);

	strcpy_s(m_pStrMainCmd,strlen(other.m_pStrMainCmd)+ 1,other.m_pStrMainCmd);
	strcpy_s(m_pStrFirstPara,strlen(other.m_pStrFirstPara)+ 1,other.m_pStrFirstPara);
	strcpy_s(m_pStrSecondPara,strlen(other.m_pStrSecondPara)+ 1,other.m_pStrSecondPara);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this == &other)
	{
		return *this;
	}
	else
	{
		if (m_pData)
		{
			delete []m_pData;
			m_pData = NULL;
		}

		int nLength = strlen(other.m_pData);
		m_pData = new char[256];
		assert(m_pData);
		memset(m_pData,0,256);
		strcpy_s(m_pData,strlen(other.m_pData) + 1, other.m_pData);


		nLength = strlen(other.m_pStrFirstPara);
		m_pStrFirstPara = new char[nLength + 1];
		assert(m_pStrFirstPara);
		memset(m_pStrFirstPara,0,sizeof(char) * (nLength + 1));
		strcpy_s(m_pStrFirstPara,sizeof(char) * (nLength + 1), other.m_pStrFirstPara);


		nLength = strlen(other.m_pStrMainCmd);
		m_pStrMainCmd = new char[nLength + 1];
		assert(m_pStrMainCmd);
		memset(m_pStrMainCmd,0,sizeof(char) * (nLength + 1));
		strcpy_s(m_pStrMainCmd,sizeof(char) * (nLength + 1), other.m_pStrMainCmd);

		nLength = strlen(other.m_pStrSecondPara);
		m_pStrSecondPara = new char[nLength + 1];
		assert(m_pStrSecondPara);
		memset(m_pStrSecondPara,0,sizeof(char) * (nLength + 1));
		strcpy_s(m_pStrSecondPara,sizeof(char) * (nLength + 1), other.m_pStrSecondPara);

		m_nCmdType = other.m_nCmdType;
		m_bDivided = other.m_bDivided;
		return *this;
	}
}

MyString::~MyString()
{
	if (m_nCmdType = CMDTYPE_MAINCMD)
	{
		delete []m_pData;
		m_pData = NULL;
		m_pStrMainCmd = NULL;
	}

 	if (m_pData)
 	{
 		delete []m_pData;
 		m_pData = NULL;
 	}

	if (m_pStrMainCmd)
	{
		delete []m_pStrMainCmd;
		m_pStrMainCmd = NULL;
	}
	if (m_pStrFirstPara)
	{
		delete []m_pStrFirstPara;
		m_pStrFirstPara = NULL;
	}
	if (m_pStrSecondPara)
	{
		delete []m_pStrSecondPara;
		m_pStrSecondPara = NULL;
	}


	m_nCmdType = CMDTYPE_INVALID;
	m_bDivided = false;
}

void MyString::AddString(char* strSrc)
{
	if (strSrc == NULL)
	{
		m_pData = new char[256];
		assert(m_pData);
		*m_pData = '\0';
	}
	else
	{
		m_pData = new char[256];
		assert(m_pData);
		//strcpy_s(m_pData,strlen(strSrc) + 1,strSrc);
		ZeroMemory(m_pData, strlen(strSrc) + 1);
		memcpy(m_pData, strSrc, strlen(strSrc));
	}
}

bool MyString::IsEmpty()
{
	if (m_pData == NULL || *m_pData == '\0')
		return true;
	return false;
}

bool MyString::IsDivideCmd()
{
	return m_bDivided ? true : false;
}

const char* MyString::GetDividedCmdByType(COMMANDTYPE nType)
{
	if (m_bDivided)
	{
		if (nType == CMDTYPE_MAINCMD)
		{
			return m_pStrMainCmd;
		}
		else if (nType == CMDTYPE_ONEPARA)
		{
			return m_pStrFirstPara;
		}
		else if (nType == CMDTYPE_DOUBPARA)
		{
			return m_pStrSecondPara;
		}
		else if (nType == CMDTYPE_ALLCMD)
		{
			return m_pData;
		}
		else 
		{
			return NULL;
		}
	}
	else
	{
		assert(false);
		return m_pData;
	}
}

void MyString::DivideStringToCmd()
{
	char* p_strCmd = new char[strlen(m_pData) + 1];
	char* p_tmp = p_strCmd;
	strcpy_s(p_strCmd,strlen(m_pData) + 1,m_pData);

	if (p_strCmd == NULL)
	{
		std::cout << "ÄãÃ»ÓÐÊäÈëÃüÁî" << std::endl;
		return;
	}

	int nCount = 0;
	m_nCmdType = CMDTYPE_MAINCMD;
	while (*p_tmp != '\0')
	{
		if (*p_tmp != ' ') 
		{
			if (m_nCmdType == CMDTYPE_MAINCMD)
			{
				*(m_pStrMainCmd + nCount) = *p_tmp;
			}
			else if (m_nCmdType == CMDTYPE_ONEPARA)
			{
				*(m_pStrFirstPara + nCount) = *p_tmp;
			}
			else if (m_nCmdType == CMDTYPE_DOUBPARA)
			{
				*(m_pStrSecondPara + nCount) = *p_tmp;
			}

			p_tmp++;
			nCount++;
		}
		else
		{
			*p_tmp = '\0';
			p_tmp++;	
			if (nCount > 0)
				m_nCmdType = (COMMANDTYPE)((int)m_nCmdType + 1);
			nCount = 0;
		}
	}
	m_bDivided = true;

	delete []p_strCmd;
	p_strCmd = NULL;
}


const MyString::COMMANDTYPE MyString::GetCmdType()
{
	return m_nCmdType;
}

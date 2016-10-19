//////////////////////////////////////////////////
//FileName	: VitualDisk.h
//Author	: zhangyandong
//Date		: 2015/3/27
//Describe	: ��������ļ�����
///////////////////////////////////////////

#pragma once
#include <limits.h>
#include "SingleTon.h"

struct TNode;
struct File;
struct TNode  
{  
	char name[UCHAR_MAX];   
	TNode* pFather;  
	TNode* pSon;  
	TNode* pBrother;
	File* pFile;   
	int nodeDepth;
};

struct File
{  
	TNode* pFather; 
	char* pBinFile;
	File* pBrother;
	char name[UCHAR_MAX]; 
	int fileLen;  
};  

class CVirtualDisk : public  CSingleton<CVirtualDisk>
{
public:
	typedef enum
	{
		ALL_FILEDIR = 0,
		ONLY_FILE,
		ONLY_DIR
	} DISPLAYTYPE;

public:
	CVirtualDisk();
	~CVirtualDisk();

public:
	// ��ӡ��ǰ·��
	void PrintCurrentPath();
	// ��ȡ��ǰ·��ָ��
	const TNode* GetCurrentPathPtr()const;
	// ��ȡ��Ŀ¼ָ��
	const TNode* GetRootPathPtr()const;
	// �ڵ�ǰ·������һ����·��   
	int Mkdir(const char* pName);
	// ��ʾ·�����ļ����ļ���
	void Display(DISPLAYTYPE nType = ALL_FILEDIR,const char* path = NULL,bool bIsRecur = false);   
	// ִ��ѭ��Copy
	void ExcuteCopy(const char* pPath,const char* pFileName);
	// ��תָ��·�� 
	void CDPath(const char* pPath);  
	// ɾ��·����·���µ������ļ����ļ�   
	void DelPath(const char* pPath, bool bClear = false);
	// ɾ���ļ�  
	void DelFile(const char* pChar); 
	// ��ȡ��ǰ·���ַ��� 
	const char* GetPathCharByPath(TNode* pPath);
	// �Ա�������̺�Ӳ���е��ļ�
	bool Compare(const char* pPath,const char* pFileName);

private:  
	int _CheckPath(TNode* pcon,const char* p);  
	int _CheckFile(TNode* pcon,const char* p); 

	TNode* _FindPath(const char* pPath);  
	File* _FindFilePath(const char* pPath);  

	void _DelFile(TNode* pcon);  
	void _Clear(TNode* p);  
	void _DelEmptyPath(TNode* pTmp);

	bool _CreateMyFile(TNode* pcon, const char* pname);
	bool _CreatePath(TNode* pcon, const char* pname);

	const char* _GetPathName(const char* pname, int nDepth , int& isFile);
	const char* _GetPathName(const char* pName);

	int _GetPathDepth(const char* pname);
	const char* _GetFileName(const char* pName);
	
	TNode* _GetPathNodeFromRelative(const char* pName,char* &abPath);
	const char* _GetPathFromRelative(const char* pName);

	// �ӱ��ش����ж�ȡ�ļ��������ļ�ϵͳ   
	int _CopyFromOutside(const char* pPath,const char* pFilePath,const char* pFileName);

	void _Display(const char* path,TNode* pTmp, int nType);

private:
	TNode*	m_pCurPath;
	TNode*	m_pRootPath;
	char*	m_pPathName;
};
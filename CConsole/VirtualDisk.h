//////////////////////////////////////////////////
//FileName	: VitualDisk.h
//Author	: zhangyandong
//Date		: 2015/3/27
//Describe	: 虚拟磁盘文件操作
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
	// 打印当前路径
	void PrintCurrentPath();
	// 获取当前路径指针
	const TNode* GetCurrentPathPtr()const;
	// 获取根目录指针
	const TNode* GetRootPathPtr()const;
	// 在当前路径创建一个新路径   
	int Mkdir(const char* pName);
	// 显示路径中文件和文件夹
	void Display(DISPLAYTYPE nType = ALL_FILEDIR,const char* path = NULL,bool bIsRecur = false);   
	// 执行循环Copy
	void ExcuteCopy(const char* pPath,const char* pFileName);
	// 跳转指定路径 
	void CDPath(const char* pPath);  
	// 删除路径及路径下的所有文件和文件   
	void DelPath(const char* pPath, bool bClear = false);
	// 删除文件  
	void DelFile(const char* pChar); 
	// 获取当前路径字符串 
	const char* GetPathCharByPath(TNode* pPath);
	// 对比虚拟磁盘和硬盘中的文件
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

	// 从本地磁盘中读取文件到虚拟文件系统   
	int _CopyFromOutside(const char* pPath,const char* pFilePath,const char* pFileName);

	void _Display(const char* path,TNode* pTmp, int nType);

private:
	TNode*	m_pCurPath;
	TNode*	m_pRootPath;
	char*	m_pPathName;
};
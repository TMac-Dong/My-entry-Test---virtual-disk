//////////////////////////////////////////////////
//FileName	: VitualDisk.cpp
//Author	: zhangyandong
//Date		: 2015/3/27
//Describe	: 虚拟磁盘文件操作
///////////////////////////////////////////
#include "stdafx.h"
#include "VirtualDisk.h"
#include <Windows.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <io.h>
#include <direct.h>

CVirtualDisk::CVirtualDisk()
{
	m_pRootPath = new TNode();   
	m_pPathName = new char[UCHAR_MAX];
	memset(m_pRootPath, 0, sizeof(TNode));
	memset(m_pPathName, 0, UCHAR_MAX);

	char str[2] = "C";
	strcpy_s(m_pRootPath->name,strlen(str) + 1,str); 
	m_pRootPath->pFather = NULL;  
	m_pRootPath->pSon = NULL;  
	m_pRootPath->pBrother = NULL;
	m_pRootPath->pFile = NULL;  
	m_pRootPath->nodeDepth = 1;
	m_pCurPath = m_pRootPath;
}

CVirtualDisk::~CVirtualDisk()
{
	if (m_pRootPath == m_pCurPath)
	{
		delete m_pCurPath;
		m_pCurPath = NULL;
		m_pRootPath = NULL;
	}
	if (m_pCurPath)
	{
		delete []m_pCurPath;
		m_pCurPath = NULL;
	}
	if (m_pRootPath)
	{
		delete []m_pRootPath;
		m_pRootPath = NULL;
	}

	if (m_pPathName)
	{
		delete []m_pPathName;
		m_pPathName = NULL;
	}
}

////////////////////////////////////public部分//////////////////////////////////////////
void CVirtualDisk::PrintCurrentPath()
{
	const char* tmp = NULL;
	if (m_pCurPath == m_pRootPath)
	{
		tmp = GetPathCharByPath(m_pRootPath);
	}
	else
	{
		tmp = GetPathCharByPath(m_pCurPath);
	}
	if (m_pCurPath == m_pRootPath)
		std::cout << tmp << ":\\";
	else
		std::cout << tmp << "\\";
}

const TNode* CVirtualDisk::GetCurrentPathPtr() const
{
	return m_pCurPath;
}

const TNode* CVirtualDisk::GetRootPathPtr() const
{
	return m_pRootPath;
}

int CVirtualDisk::Mkdir(const char* pName)
{	
	//C:\12\1.txt  \123  123
	char* pathName = new char[256];
	memset(pathName,0,256);
	int j = 0;
	TNode* tmpNode = NULL;
	
	if (tmpNode == NULL)
		tmpNode = m_pRootPath;

	const char* pname = _GetPathFromRelative(pName);
	strcpy_s(pathName,strlen(pname) + 1,pname);
// 	strcat(pathName,_GetFileName(pName));
	int nDepth = _GetPathDepth(pathName);
	for (int i = 0 ; i <= nDepth; ++i)
	{
		int isFile;
		const char * p = _GetPathName(pathName,i,isFile);
		//p = _GetPathName(pathName,i,isFile);
		while (1)
		{
			if (strcmp(tmpNode->name,p) == 0)
			{
				//tmpNode = tmpNode->pSon;
				break;
			}
			else
			{
				if (tmpNode->pBrother != NULL)
				{
					tmpNode = tmpNode->pBrother;
				}
				else 
				{
					if (isFile == 1)
					{
						p = _GetFileName(pName);
						if (!_CreateMyFile(tmpNode,p))
						{
							std::cout << "创建文件失败" << std::endl;
						}
					}
					else
					{
						_CreatePath(tmpNode,p);
						
						if (tmpNode->pSon)
							tmpNode = tmpNode->pSon;
					}
					break;
				}
			}
		}
	}
	
	if (pathName)
	{
		delete []pathName;
		pathName = NULL;
	}
	return 0;
}
  
void CVirtualDisk::Display(DISPLAYTYPE nType,const char* path, bool bIsRecur)
{
	TNode* pTmp = NULL;

	if(path == NULL || strcmp(path,"") == 0)  
	{  
		pTmp = m_pCurPath;
	}  
	else
	{
		const char *p = _GetPathFromRelative(path);
		char* tmpPath = new char[strlen(p) + 1];
		strcpy_s(tmpPath, strlen(p) + 1, p);
		pTmp = _FindPath(tmpPath);

		if (tmpPath)
		{
			delete []tmpPath;
			tmpPath = NULL;
		}
		if (pTmp == NULL)
			return;
	}
	
	if (!bIsRecur)
	{
		path = GetPathCharByPath(pTmp);
		_Display(path, pTmp , nType);
	}
	else
	{
		while (pTmp != NULL)
		{
			path = GetPathCharByPath(pTmp);
			_Display(path, pTmp , nType);
			pTmp = pTmp->pSon;
		}
	}
}

void CVirtualDisk::ExcuteCopy(const char* pPath,const char* pFileName)
{
	char* TmpPath = new char[256];
	strcpy_s(TmpPath, strlen(pPath) + 1, pPath);
	if (TmpPath == NULL|| strcmp(TmpPath, "") == 0)
	{
		const char* tmp = GetPathCharByPath(m_pCurPath);
		strcpy_s(TmpPath, strlen(tmp) + 1, tmp);
		if (m_pCurPath == m_pRootPath)
		{
			strcat(TmpPath,":\\");
		}
	}

	char *pDiskPath = new char[256];
	const char* tmpFile = pFileName;
	strcpy_s(pDiskPath,strlen(pFileName) + 1,pFileName);
	int j = 0;
	while (*tmpFile != '\0')
	{
		tmpFile++;
		j++;
	}

	while (*tmpFile != '\\')
	{
		tmpFile--;
		j--;
	}
	tmpFile++;

	*(pDiskPath + j + 1) = '\0';

	char* dir = pDiskPath;
	const char* filespec = tmpFile;
	// 更改当前工作路径
	_chdir(dir); 

	//首先查找dir中符合要求的文件
	long hFile;
	_finddata_t fileinfo;
	if ((hFile = _findfirst(filespec,&fileinfo)) != -1)
	{
		do
		{
			//检查是不是目录
			//如果不是,则进行处理
			if (!(fileinfo.attrib & _A_SUBDIR))
			{
				char filename[_MAX_PATH];
				strcpy(filename,dir);
				//strcat(filename,"\\");
				strcat(filename,fileinfo.name);
				//std::cout << filename << std::endl;
				//strcpy_s(pDiskPath,strlen(filename) + 1,filename);
				if (_CopyFromOutside(TmpPath,filename,fileinfo.name) == 1)
					std::cout << "拷贝成功" << std::endl;
				//memset(pDiskPath,0,256);
			}
		} while (_findnext(hFile,&fileinfo) == 0);
		_findclose(hFile);
	}

	if (pDiskPath)
	{
		delete []pDiskPath;
		pDiskPath = NULL;
	}

	if (TmpPath)
	{
		delete []TmpPath;
		TmpPath = NULL;
	}
}

int CVirtualDisk::_CopyFromOutside(const char* pPath,const char* pFilePath,const char* pFileName)
{
	std::fstream  f(pFilePath,std::ios::in|std::ios::binary);  
	if(!(f.is_open()))  
	{  
		std::cout<<"拷贝文件失败"<<std::endl;  
		f.close();  
		f.clear();

		return 0;  
	}  

	int fileLen = 0;  
	f.seekg(0,std::ios::end);  
	fileLen = f.tellg();  
	f.seekg(0); 
	File* pfile = (File*)malloc(sizeof(File));
	pfile->pBinFile = NULL;  
	pfile->pBrother = NULL;  
	pfile->pFather = NULL;  
	pfile->fileLen = 0;  
	
	pfile->pBinFile = (char*)malloc(fileLen + 1);  
	memset(pfile->pBinFile,0,sizeof(pfile->pBinFile) / sizeof(char));
	if(!f.read(pfile->pBinFile,fileLen))  
	{  
		std::cout << "拷贝失败" <<  std::endl;
		if (pfile->pBinFile)
		{
			free(pfile->pBinFile);  
			pfile->pBinFile = NULL;
		}
	
		if (pfile)
		{
			free(pfile);  
			pfile = NULL;	
		}
		f.close();  
		f.clear();
		return 0;
	}  
	
	pfile->pBinFile[fileLen] = '\0';
	const char *p = _GetFileName(pPath);
	if (strcmp(p,"") == 0)
		strcpy_s(pfile->name,strlen(pFileName) + 1,pFileName);  
	else
		strcpy_s(pfile->name,strlen(p) + 1,p);

	pfile->fileLen = fileLen;  
	TNode *conTmp=NULL;  
	char *tmp = new char[256];
	conTmp = _GetPathNodeFromRelative(pPath,tmp);  
	
	TNode* RootTmp = m_pRootPath;
	int j = 0;
	while(RootTmp->pSon != NULL)
	{
		RootTmp = RootTmp->pSon;
		j++;
	}

	if (strcmp(conTmp->name,_GetPathName(tmp)) != 0 && _CheckPath(conTmp,tmp) == 0)
	{
		std::cout << "路径不存在" << std::endl;
		f.close(); 
		f.clear();

		if (pfile->pBinFile)
		{
			free(pfile->pBinFile);  
			pfile->pBinFile = NULL;
		}

		if (pfile)
		{
			free(pfile);  
			pfile = NULL;	
		}

		if (tmp)
		{
			delete []tmp;
			tmp = NULL;
		}
		return 0;
	}

	if (conTmp->pFile == NULL)
	{
		conTmp->pFile = pfile; 
		pfile->pFather = conTmp;  
	}
	else
	{

		File* fileTmp = conTmp->pFile;
		while(fileTmp->pBrother != NULL)
		{
			fileTmp = fileTmp->pBrother;
		}

		fileTmp->pBrother = pfile;
		pfile->pFather = conTmp;  
	}

	f.close(); 
	f.clear();
	if (tmp)
	{
		delete []tmp;
		tmp = NULL;
	}
	return 1;  
}

void CVirtualDisk::CDPath(const char* pPath)
{
	char* tmp = new char[256];
	memset(tmp ,0, 256);
	if(*pPath == NULL)  
	{  
		std::cout << "输入路径有误" << std::endl;  
		return;  
	}  

	if (_GetPathNodeFromRelative(pPath,tmp) == NULL)
	{
		strcpy_s(tmp, strlen(pPath) + 1,pPath); 
	}
	if (_FindPath(tmp)== NULL)
		std::cout << "未找到你输入的路径" << std::endl;
	else
		m_pCurPath = _FindPath(tmp);   

	if (tmp)
	{
		delete []tmp;
		tmp = NULL;
	}
}

void CVirtualDisk::DelPath(const char* pPath,  bool bClear)
{
	char* tmp = new char[256];
	memset(tmp ,0, 256);

	if(pPath == NULL)  
	{  
		std::cout<< "您输入的路径有误" << std::endl;  
		if (tmp)
		{
			delete []tmp;
			tmp = NULL;
		}
		return;  
	}  

	TNode* pTmp = _GetPathNodeFromRelative(pPath,tmp);

	//TNode* pTmp = _FindPath(tmp);
	if (pTmp == NULL)
	{
		//std::cout << "你输入的路径可能不存在" << std::endl;
		DelFile(tmp);
		if (tmp)
		{
			delete []tmp;
			tmp = NULL;
		}
		return;
	}
	if (m_pCurPath == pTmp && pTmp != m_pRootPath)
	{
		std::cout << "正在使用或者不存在" << std::endl;
		//m_pCurPath = m_pCurPath->pFather;
	}
	else
	{
		if (bClear)
		{
			if (pTmp->pSon == NULL && pTmp->pFile == NULL)
			{
				DelFile(tmp);
				if (pTmp != m_pRootPath)
				{
					const char* OriginalName = tmp;
					const char* CurName = tmp;
					while (*CurName != '\0')
					{
						CurName++;
					}
					while(*CurName != '\\' && CurName != OriginalName)
					{
						CurName--;
					}
					if (CurName != OriginalName)
						CurName++;

					if (strcmp(CurName, pTmp->name) == 0)
						_DelEmptyPath(pTmp);
				}
			}
			else
			{ 
				const char* OriginalName = tmp;
				const char* CurName = tmp;
				while (*CurName != '\0')
				{
					CurName++;
				}
				while(*CurName != '\\' && CurName != OriginalName)
				{
					CurName--;
				}
				if (CurName != OriginalName)
					CurName++;

				if (strcmp(CurName, pTmp->name) == 0)
					_Clear(pTmp);
			}
		}
		else
		{
			DelFile(tmp);
			if (pTmp != m_pRootPath)
				_DelEmptyPath(pTmp);
		}
	}

	if (tmp)
	{
		delete []tmp;
		tmp = NULL;
	}

}

void CVirtualDisk::DelFile(const char* pChar)
{
	if(pChar == NULL)  
	{  
		//std::cout << "您输入的路径有误" << std::endl;  
		return;  
	}  
	File* pfile = NULL; 

	char* tmp = new char[256];
	memset(tmp, 0,256);
	TNode* pCurPath = _GetPathNodeFromRelative(pChar,tmp);
	if (pCurPath == NULL || !(pCurPath->pFile) || _GetFileName(pChar) == NULL)
	{
		//std:: cout << "没找到该文件" << std::endl; 
		if (tmp)
		{
			delete []tmp;
			tmp = NULL;
		}
		return;
	}

	bool match(const char *pattern,const char *content);
	pfile = pCurPath->pFile;

	TNode* pTmp = pCurPath;
	while (pfile != NULL)
	{
		if (strcmp(pfile->name,"") == 0)
		{
			std::cout <<  "文件名称为空" << std::endl;

			if (tmp)
			{
				delete []tmp;
				tmp = NULL;
			}
			return;
		}

		const char *p = _GetPathFromRelative(pChar);
		strcpy_s(tmp,strlen(p) + 1, p);
		const char* q = _GetFileName(tmp);
		if (match(q, pfile->name) )
		{
			if (pfile == pfile->pFather->pFile)
			{
				pfile->pFather->pFile = pfile->pBrother;
			}
			else
			{
				// 按顺序删除
				File* tmpFile = pfile->pFather->pFile;
				File* tmpLastFile = tmpFile;
				while(tmpFile != pfile)
				{
					tmpFile = tmpFile->pBrother;

					if (tmpFile != pfile)
						tmpLastFile = tmpFile;
				}
				tmpLastFile->pBrother = tmpFile->pBrother;
			}

			if (pfile->pBinFile)
			{
				free(pfile->pBinFile); 
				pfile->pBinFile = NULL;
			}	
		}

		pfile = pfile->pBrother;
	}
	
	if (tmp)
	{
		delete []tmp;
		tmp = NULL;
	}
}

const char* CVirtualDisk::GetPathCharByPath(TNode* pPath)
{
	char* pStr = new char[UCHAR_MAX];
	TNode* pTmp = NULL;
	char* pStr1 = new char[UCHAR_MAX];

	memset(pStr,0, UCHAR_MAX);
	memset(pStr1,0, UCHAR_MAX);

	if (pPath != m_pRootPath )
	{
		pTmp = pPath;
		while (1)
		{
			if (pTmp->pFather != m_pRootPath)
			{
				strcpy_s(pStr,strlen("\\") + 1,"\\");
				strcat(pStr, pTmp->name);
				strcat(pStr, pStr1);
				memset(pStr1,0,UCHAR_MAX);
				strcpy_s(pStr1, strlen(pStr) + 1,pStr);
				memset(pStr,0,UCHAR_MAX);
				pTmp = pTmp->pFather;
			}
			else
			{
				strcpy_s(pStr, strlen(m_pRootPath->name) + 1,m_pRootPath->name);
				strcat(pStr,":\\");
				strcat(pStr, pTmp->name);
				strcat(pStr, pStr1);
				memset(pStr1,0,UCHAR_MAX);
				strcpy_s(pStr1, strlen(pStr) + 1,pStr);
				break;
			}
		}
	}
	else if (pPath == m_pRootPath)
	{
		strcpy_s(pStr1, strlen("C") + 1,"C");
		//strcat(pStr1,":");
	}

	strcpy_s(m_pPathName, strlen(pStr1) + 1,pStr1);
	//strcat(m_pPathName,"\\");

	if (pStr)
	{
		delete []pStr;
		pStr = NULL;
	}
	if (pStr1)
	{
		delete []pStr1;
		pStr1 = NULL;
	}
	return m_pPathName;
}

bool CVirtualDisk::Compare(const char* pPath,const char* pFileName)
{
	std::ifstream in(pFileName,std::ios::in | std::ios::binary);//创建输入流
	if(!in)
	{
		std::cout<< "打开文件失败！\n" << std::endl;
		in.close();
		in.clear(); 
		return false;
	}

	char* AbsolutePath = new char[256];
	memset(AbsolutePath,0,256);
	const char *p = _GetPathFromRelative(pPath);
	strcpy_s(AbsolutePath, strlen(p) + 1,p);
	//p = _GetFileName(pPath);
	//strcat(AbsolutePath,p);


	File* pTmp = _FindFilePath(AbsolutePath);
	if (pTmp == NULL || pTmp->pBinFile == NULL)
	{
		std::cout << pPath << "文件为空" << std::endl; 
		in.close();
		in.clear(); 

		if (AbsolutePath)
		{
			delete []AbsolutePath;
			AbsolutePath = NULL;

		}
		return false;
	}
	int i = 0;
	bool bSame = false;
	while(!in.eof())//读文件
	{
		char tmp;
		in.read(&tmp,1);
		if (in.fail())
		{
			break;
		}
		char c = *(pTmp->pBinFile + i);
		if (strncmp(&tmp,pTmp->pBinFile + i,1) != 0)
		{
			char str[20];
			//printf_s("%x",str,*(pTmp->pBinFile + i));

			sprintf(str,"%X", *(pTmp->pBinFile + i));
			std::cout<< "bin - " << str << std::endl;
			std::cout<< "str - " << tmp << std::endl;
			
			std::cout << "不一样的字符串为:";
			for (int loop = i; loop < i + 16 ; loop++)
			{
				if (*(pTmp->pBinFile + loop) != '\0')
					std::cout << *(pTmp->pBinFile + loop);
				else
					break;
			}
			std::cout<< std::endl;

			bSame = true;
			break;
		}
		i++;
	}
	if (bSame == false)
	{
		std::cout << "内容比较一致" << std::endl;
	}
	in.close();
	in.clear(); 

	if (AbsolutePath)
	{
		delete []AbsolutePath;
		AbsolutePath = NULL;

	}
	return true;
}

////////////////////////////////////private部分//////////////////////////////////////////
void CVirtualDisk::_DelFile(TNode* pNode)
{
	if(pNode == NULL)  
	{  
		std::cout<<"输入路径有误"<< std::endl;  
		return;  
	}  
	if(pNode->pFile == NULL)  
	{  
		return;  
	}  
	else  
	{  
		File* pfileTmp = pNode->pFile;  
		File* pfileTmp2 = pfileTmp;  
		while(pfileTmp->pBrother != NULL)  
		{  
			pfileTmp2 = pfileTmp->pBrother;  
			pfileTmp->pBrother = pfileTmp2->pBrother;  
			
			if (pfileTmp2->pBinFile)
			{
				free(pfileTmp2->pBinFile);  
				pfileTmp2->pBinFile = NULL;
			}
			if (pfileTmp2)
			{
				free(pfileTmp2);  
				pfileTmp2 = NULL;
			}
		}  
		if (pNode->pFile->pBinFile)
		{
			free(pNode->pFile->pBinFile);  
			pNode->pFile->pBinFile=NULL;  
		}

		if (pNode->pFile)
		{
			free(pNode->pFile);  
			pNode->pFile = NULL;  
		}
		return;  
	}  
}

TNode* CVirtualDisk::_FindPath(const char* pPath)
{
	if(pPath == NULL)  
	{  
		return NULL;  
	}  

	TNode* pconTmp = m_pRootPath; 
	int len =  _GetPathDepth(pPath);  
	for(int i = 0;i <= len;i++)  
	{  
		int IsFile = 0;
		const char* pathName = _GetPathName(pPath,i,IsFile);

		if(strcmp(pconTmp->name,pathName) == 0)  
		{  
			if(i < len)  
			{  
				if(pconTmp->pSon == NULL)  
				{  
					//std::cout << "你要找的目录不存在" << std::endl;
					return pconTmp;  
					//return NULL;
				}  
				pconTmp = pconTmp->pSon;  
			} 
			if (i == len)  
			{  
				return pconTmp;  
			}  
		}  
		else  
		{  
			if(pconTmp->pBrother == NULL)  
			{  
				return pconTmp->pFather; ;
			}  
			while(pconTmp->pBrother != NULL)  
			{  
				if (IsFile == 1)
				{
					return pconTmp->pFather;
				}
				if(strcmp(pconTmp->pBrother->name,pathName) == 0)  
				{  
					if(i < len) 
					{  
						pconTmp = pconTmp->pBrother;
						if (pconTmp->pSon == NULL)
						{
							//std::cout << "你找的路径不存在" << std::endl;
							return pconTmp;
						}
						
						pconTmp = pconTmp->pSon;
						break;
					}  
					else
					{  
						return pconTmp->pBrother;  
					}  
				}  
				pconTmp = pconTmp->pBrother;  
			}  
		}  
	}  

	return pconTmp; 
}

File* CVirtualDisk::_FindFilePath(const char* pPath)
{
	if(pPath == NULL)  
    {  
        return NULL;  
    }  
    //将文件名和文件路径区分获得文件名    
    const char* tmp = pPath;  
    while('\0'!= *tmp)  
    {  
       tmp++;  
    }  
    while(1)  
    {  
		if (tmp == "")
			break;
		if ('\\'== *tmp)
		{
			tmp++;
			break;
		}
		tmp--;  
    }  

    char pathName[256];  
    strcpy_s(pathName,strlen(pPath) + 1,pPath);  
    pathName[tmp- pPath]='\0';

    TNode* conTmp = _FindPath(pathName);  
    strcpy_s(pathName,tmp);  
    if(conTmp == NULL)  
    {  
        return NULL;  
    }  
    File* fileTmp = NULL;  
	fileTmp = conTmp->pFile;  
	if(fileTmp == NULL)  
	{  
		return NULL;  
	}  

    while(fileTmp != NULL  && pathName != "")  
    {  
        if(0 == strcmp(fileTmp->name,pathName))  
        {  
            return fileTmp;  
        }  
		fileTmp = fileTmp->pBrother;
    }  
	std::cout << "_FindFilePath:不存在" << std::endl;  
    return NULL;  
}

int CVirtualDisk::_CheckPath(TNode* pcon,const char* p)
{
	if(pcon == NULL)  
	{  
		return 0;  
	}  
	TNode* pconTmp = pcon;  

	if(pconTmp->pSon == NULL)  
	{  
		return 0;  
	}  
	else   
	{  
		pconTmp = pconTmp->pSon;  
		if(strcmp(pconTmp->name,p) == 0)  
		{  
			//std::cout << "该路径中已经存在" << p << std::endl;  
			return 1;  
		}  
		while(pconTmp->pBrother != NULL )  
		{  
			if(strcmp(pconTmp->pBrother->name,p) == 0)  
			{  
				//std::cout << "该路径中已经存在" << p << std::endl;  
				return 1;  
			}  
			pconTmp = pconTmp->pBrother;  
		}  
		return 0;  
	}  
}

int CVirtualDisk::_CheckFile(TNode* pcon,const char* p)
{
	if(pcon == NULL)  
	{  
		return -1;  
	}  
	File* pfile = NULL;  
	//如果该路径下不存在子文件则不进行搜索   
	if(pcon->pFile == NULL)  
	{  
		return 0;  
	}  
	//如果该路径下存在子文件则进行搜索   
	else   
	{  
		pfile = pcon->pFile;  
		if(strcmp(pfile->name,p)==0)  
		{  
			std::cout << "该路径中已经存在" << p << std::endl;  
			return 1;  
		}  
		while(pfile->pBrother != NULL )  
		{  
			if(strcmp(pfile->pBrother->name,p)==0)  
			{  
				std::cout << "该路径中已经存在" << p << std::endl;  
				return 1;  
			}  
			pfile = pfile->pBrother;  
		}  
		return 0;  
	}
}

void CVirtualDisk::_Clear(TNode* p)
{
	if(p->pSon != NULL)  
	{  
		_Clear(p->pSon);  
		if(p->pBrother != NULL)  
		{  
			_Clear(p->pSon->pBrother);  
		}
	}    
	else  
	{  
		TNode* pTmp = p;  
		if(pTmp->pFather != NULL && strcmp(p->name,pTmp->pFather->pSon->name) == 0)  
		{  
			_DelFile(p);  
			p->pFather->pSon = NULL;  
			if (p)
			{
				free(p);  
				p = NULL;  
			}
			return;  
		}  
		else  
		{  
			while(pTmp->pBrother != NULL)  
			{  
				if(strcmp(pTmp->pBrother->name,p->name) == 0)  
				{  
					_DelFile(p);  
					pTmp->pBrother = NULL;  
					if (p)
					{
						free(p);  
						p = NULL;
					}
					return;  
				}  
				pTmp = pTmp->pBrother;  
			}  
		}  
	} 
	if (p->pFile != NULL)
	{
		if (p->pFile->pBinFile != NULL)
		{
			free(p->pFile->pBinFile);
			p->pFile->pBinFile = NULL;
		}
		delete []p->pFile;
		p->pFile = NULL;
	}
	_DelEmptyPath(p);
}

void CVirtualDisk::_DelEmptyPath(TNode* pTmp)
{
	if (pTmp->pFather == NULL)
	{
		std::cout << "不能删除根目录" << std::endl;
		return;
	}

	if (pTmp->pSon != NULL || pTmp->pFile != NULL)
	{
		std::cout << "不是空文件" << std::endl;
		return;
	}

	TNode* tmp = pTmp->pFather->pSon;
	TNode* pLastTmp = tmp;
	while (tmp != pTmp)
	{
		if (tmp != pTmp)
		{
			pLastTmp = tmp;
			tmp = tmp->pBrother;
		}
	}

	if (tmp == pLastTmp)
	{
		tmp->pFather->pSon = tmp->pBrother;
	}
	else
	{
		pLastTmp->pBrother = tmp->pBrother;
	}
}
bool CVirtualDisk::_CreatePath(TNode* pcon, const char* pname)
{
	// 创建一个文件夹  
	if(_CheckPath(pcon,pname) == 1)  
	{  
		return false;  
	}  
	if(pcon->pSon == NULL) 
	{  
		pcon->pSon = (TNode*)malloc(sizeof(TNode));  
		pcon->pSon->pFather = pcon;  
		pcon->pSon->pBrother = NULL;  
		pcon->pSon->pSon = NULL;  
		pcon->pSon->pFile = NULL;  
		pcon->pSon->nodeDepth = pcon->nodeDepth + 1;
		strcpy(pcon->pSon->name,pname);  
		return true;
	}  
	else   
	{  
		pcon = pcon->pSon;  
		while(pcon->pBrother!=NULL)  
		{  
			pcon = pcon->pBrother;  
		}  
		pcon->pBrother = (TNode*)malloc(sizeof(TNode));  
		pcon->pBrother->pFather = pcon->pFather;  
		pcon->pBrother->pBrother = NULL;  
		pcon->pBrother->pSon = NULL;  
		pcon->pBrother->pFile = NULL;
		pcon->pBrother->nodeDepth = pcon->nodeDepth;
		strcpy_s(pcon->pBrother->name, strlen(pname) + 1, pname); 
		return true;
	}  
	return false;
}

bool CVirtualDisk::_CreateMyFile(TNode* pcon, const char* pname)
{
	//创建一个空文件  
	if(_CheckFile(pcon,pname) == 1)  
	{  
		return true;  
	}  
	//如果该路径下没有新文件，则创建一个新文件  
	if(pcon->pFile == NULL)  
	{  
		pcon->pFile =( File*)malloc(sizeof(File));  
		pcon->pFile->fileLen = 0;  
		pcon->pFile->pBinFile = NULL;  
		pcon->pFile->pBrother = NULL;  
		strcpy_s(pcon->pFile->name,strlen(pname) + 1,pname);
		pcon->pFile->pFather = pcon;  
		return true;
	}  
	else  
	{  
		File* pfileTmp = pcon->pFile;  
		while(pfileTmp->pBrother!= NULL)  
		{  
			pfileTmp = pfileTmp->pBrother;  
		}  
		pfileTmp->pBrother = (File*)malloc(sizeof(File));  
		pfileTmp->pBrother->fileLen = 0;  
		pfileTmp->pBrother->pBinFile = NULL;  
		pfileTmp->pBrother->pBrother = NULL;  
		pfileTmp->pBrother->pFather = pcon;  
		strcpy_s(pfileTmp->pBrother->name, strlen(pname) + 1, pname);  
		return true;
	} 
	return false;
}

const char* CVirtualDisk::_GetPathName(const char* pname,int nDepth,int& isFile )
{
	//char pathName[256];
	isFile = 0;
	int j = 0;
	const char* pStart = pname;
	for (int i = 0; i <= nDepth; i++)
	{
		j = 0;
		memset(m_pPathName, 0 ,strlen(m_pPathName) + 1);
		while (*pname != '\0')
		{
			if (*pname == '.')
			{
				if (pname != pStart && *(pname - 1) != '.' && *(pname - 1) != '\\' && *(pname + 1) != '\0' &&  *(pname + 1) != '\\')
					isFile = 1;
			}
			
			if (*pname == ':' && *(pname+1) == '\0')
			{
				*(m_pPathName + j) = '\0';
				pname++;
				break;
			}

			if (*pname != '\\')
			{
				*(m_pPathName +j ) = *pname;
			}
			else
			{
				if (*(m_pPathName + j - 1) == ':')
				{
					*(m_pPathName + j - 1) = '\0';
					pname++;
					break;
				}
				else
				{
					*(m_pPathName + j) = '\0';
					pname++;
					break;
				}
			}
			pname++;
			j++;
		}
	}
	return m_pPathName;
}

const char* CVirtualDisk::_GetPathName(const char* pName)
{
	char *TmpName = new char[strlen(pName) + 1];
	char *pname= TmpName; 
	strcpy_s(pname,strlen(pName) + 1,pName);
	bool bFile(false);
	if (pname == NULL)
	{
		std::cout << "文件名获取失败" << std::endl;
		return NULL;
	}

	const char* OriginalName = pname;
	while (*pname != '\0')
	{
		pname++;
	}
	while(*pname != '\\' && pname != OriginalName)
	{
		pname--;
		if (*(pname) == '\\' && *(pname + 1) == '\0')
		{
			*(pname) = '\0';
			pname--;
		}
	}
	if (pname != OriginalName)
		pname++;

	memset(m_pPathName,0,strlen(m_pPathName) + 1);
	
	strcpy_s(m_pPathName,strlen(pname) + 1,pname);
	
	if (strcmp(m_pPathName,"C:") == 0)
	{
		strcpy_s(m_pPathName,strlen("C") + 1,"C");
	}
	if (pname)
	{
		delete []TmpName;
		TmpName = NULL;
	}
	//strcpy_s(m_pPathName,strlen(pname) + 1,pname);

	return m_pPathName;
}

int CVirtualDisk::_GetPathDepth(const char* pname)
{
	int nDepth = 0;
	while (*pname != '\0')
	{
		if (*pname == '\\' && *(pname + 1) != '\0')
			nDepth++;
		pname++;
		//if (pname == '\0' && pname != '\\')
		//	pname++;
	}
	return nDepth;
}

TNode* CVirtualDisk::_GetPathNodeFromRelative(const char* pName, char* &abPath)
{
	//_GetPathFromRelative(pName);
	const char* pname = pName;
	char* pathName = new char[256];
	memset(pathName,0,256);
	TNode* pTmpNode = NULL;

	/*if (*pname == '\\')
	{
	strcpy_s(pathName, strlen(GetPathCharByPath(m_pCurPath)) + 1, GetPathCharByPath(m_pCurPath));
	if (m_pCurPath == m_pRootPath)
	{
	strcat(pathName,":\\");
	}
	strcat(pathName,pname);
	pTmpNode = _FindPath(pathName);

	}
	else if ( *pname == '.')
	{
	strcpy_s(pathName, strlen(GetPathCharByPath(m_pCurPath)) + 1, GetPathCharByPath(m_pCurPath));

	if (*(++pname) == '.')
	{
	strcpy_s(pathName, strlen(GetPathCharByPath(m_pCurPath->pFather)) + 1, GetPathCharByPath(m_pCurPath->pFather));
	pname++;
	}

	if (pname != '\0')
	strcat(pathName,pname);
	pTmpNode = _FindPath(pathName);

	}
	else if (*pname != 'C')
	{
	strcpy_s(pathName, strlen(GetPathCharByPath(m_pCurPath)) + 1, GetPathCharByPath(m_pCurPath));
	if (m_pCurPath == m_pRootPath)
	{
	strcat(pathName,":\\");
	}
	strcat(pathName,pname);
	pTmpNode = _FindPath(pathName);
	}*/


	strcpy_s(pathName ,strlen(_GetPathFromRelative(pName)) + 1, _GetPathFromRelative(pName));
	pTmpNode = _FindPath(pathName);

	strcpy_s(abPath, strlen(pathName) + 1, pathName);
	if (pathName)
	{
		delete []pathName;
		pathName = NULL;
	}

	return pTmpNode;
}

const char* CVirtualDisk::_GetFileName(const char* pName)
{
	char *TmpName = new char[strlen(pName) + 1];
	char *pname= TmpName; 
	strcpy_s(pname,strlen(pName) + 1,pName);
	bool bFile(false);
	if (pname == NULL)
	{
		std::cout << "文件名获取失败" << std::endl;
		return NULL;
	}
	
	const char* OriginalName = pname;
	while (*pname != '\0')
	{
		pname++;
	}
	while(*pname != '\\' && pname != OriginalName)
	{
 		if (*pname == '.')
 		{
			if (pname != OriginalName && *(pname - 1) != '.' && *(pname - 1) != '\\' && *(pname + 1) != '\0' &&  *(pname + 1) != '\\')
				bFile = true;
		}

		pname--;
		if (*(pname) == '\\' && *(pname + 1) == '\0')
		{
			*(pname) = '\0';
			pname--;
		}
	}
	if (pname != OriginalName)
		pname++;

	memset(m_pPathName,0,strlen(m_pPathName) + 1);
 	
	if (bFile)
 	{
		strcpy_s(m_pPathName,strlen(pname) + 1,pname);
 	}

	if (pname)
	{
		delete []TmpName;
		TmpName = NULL;
	}
	//strcpy_s(m_pPathName,strlen(pname) + 1,pname);

	return m_pPathName;
}

const char* CVirtualDisk::_GetPathFromRelative(const char* pName)
{
	char* pathName = new char[256];
	char* name = new char[256];
	memset(pathName,0,256);
	memset(name,0,256);
	*name  = '\0';
	TNode* pCurPath = m_pCurPath;

	const char* OrignalName = pName;
	char* OrignalName1 = name;
	// ..\..\.\
	
	bool bOption(false);
	bool bHaveRelativePoint(false);
	int nDoublePoint = 0;

	bool bFirst(true);
	while (*pName != '\0')
	{
		if (*pName == '.')
		{
			if (nDoublePoint == 0 && *OrignalName == '.')
			{
				nDoublePoint++;
				bOption = true;
				bHaveRelativePoint = true;
				static TNode* pTmpPath = pCurPath;
				char* pFatherName = new char[256];
				while (1)
				{
					if (pCurPath == m_pRootPath)
					{
						strcpy_s(pFatherName, strlen(pCurPath->name) + 1, pCurPath->name);
						strcat(pFatherName, ":\\");
					}
					else
					{
						strcpy_s(pFatherName, strlen(pCurPath->name) + 1,pCurPath->name);
						//if (!bFirst)
						strcat(pFatherName,"\\");
						bFirst = false;
					}

					strcat(pFatherName,pathName);
					memset(pathName,0,strlen(pathName) + 1);
					strcpy_s(pathName, strlen(pFatherName) + 1,pFatherName);
					pCurPath = pCurPath->pFather; 

					if (pCurPath == NULL)
					{
						break;
					}
				}

				pCurPath = pTmpPath;
				if (pFatherName)
				{
					delete []pFatherName;
					pFatherName = NULL;
				}
				//pName++;
			}

			pName++;
			if (*(pName) == '.')
			{	
				//strcat(pathName, pCurPath->pFather->name);
				bHaveRelativePoint = true;

				char* point = pathName;
				//两个小点点找老爸
				while (*point != '\0')
				{
					point++;
				}
				int j = 0;
				while(1)  
				{  
					if ('\\'== *point)
					{
						//if (j == 0)
						//	*point = '\0';
						if (j > 1)
						{
							//if (*point == ':')
							//	point++;
							//else
							point++;
							break;
						}
					}
					point--;  
					j++;
				}  

				char path[256];  
				strcpy_s(path,strlen(pathName) + 1,pathName);  
				path[point- pathName] = '\0';
				strcpy_s(pathName,strlen(path) + 1,path);
				if (pCurPath == m_pRootPath)
					pCurPath = m_pRootPath;
				else
					pCurPath = pCurPath->pFather;
				pName++;
				nDoublePoint++;  // 两个点点加加加
				//strcat(pathName, pCurPath->name);
			}

			//strcat(pathName,"\\");

		}
		else if(*pName == '\\' && OrignalName == pName)
		{
			bOption = true;

			strcpy_s(pathName, strlen(GetPathCharByPath(m_pCurPath)) + 1, GetPathCharByPath(m_pCurPath));
			if (m_pCurPath == m_pRootPath)
			{
				strcat(pathName,":\\");
			}
			strcat(pathName,pName);
		}
		else if (*pName != 'C' && OrignalName == pName)
		{
			bOption = true;

			strcpy_s(pathName, strlen(GetPathCharByPath(m_pCurPath)) + 1, GetPathCharByPath(m_pCurPath));
			if (m_pCurPath == m_pRootPath)
			{
				strcat(pathName,":");
			}
			strcat(pathName,"\\");
			strcat(pathName,pName);
		}
		//else
		//{
		//	*OrignalName1 = *pName;
		//	OrignalName1++;
		//}
		
		pName++;
	}

	if (!bOption)
		strcpy_s(pathName,strlen(OrignalName) + 1,OrignalName);

	memset(m_pPathName,0,strlen(m_pPathName) + 1);
	strcpy_s(m_pPathName,strlen(pathName) + 1,pathName);


	if (bHaveRelativePoint)
	{
		while(pName != OrignalName)
		{
			if (pName - 1 == OrignalName && (*(pName - 1) == '.' || *(pName - 1) == '\\'))
			{
				pName++;
				break;				
			}
			if (*(pName - 1) == '.' && (*(pName - 2) == '.' || *(pName - 2) == '\\' || pName - 2 == OrignalName))
			{
				pName++;
				break;
			}
			pName--;
		}
		if (strcmp(m_pPathName,"C:\\\\") == 0)
			strcpy_s(m_pPathName,strlen("C:\\") + 1,"C:\\");
		strcat(m_pPathName,pName);
	}

	if (pathName)
	{
		delete []pathName;
		pathName = NULL;
	}
	if (name)
	{
		delete []name;
		name = NULL;
	}
	if (strcmp(m_pPathName,"C:\\\\") == 0)
		strcpy_s(m_pPathName,strlen("C:\\") + 1,"C:\\");

	return m_pPathName;
}

void CVirtualDisk::_Display(const char* path,TNode* pTmp, int nType)
{
	if(pTmp == NULL)  
	{  
		std::cout<<"您输入的路径有误"<<std::endl;  
		return;  
	}  

	//if(pTmp->pSon == NULL && pTmp->pFile == NULL)  
	//{  
	//	std::cout << "目录"<< path << "下没有其他文件和文件夹" << std::endl;  
	//	return;  
	//}  
	// 搜索路径下的所有文件夹   
	if(pTmp->pSon != NULL)  
	{  
		pTmp = pTmp->pSon;  
		if (nType == ALL_FILEDIR || nType == ONLY_DIR)
		{
			std::cout << std::endl;
			std::cout << path << "目录下的目录：" << std::endl;

			std::cout << "<DIR>    " << pTmp->name << std::endl;  
		}
		while(pTmp->pBrother != NULL)  
		{  
			pTmp=pTmp->pBrother;  
			if (nType == ALL_FILEDIR || nType == ONLY_DIR)
				std::cout <<"<DIR>    " << pTmp->name << std::endl;  
		}  
		pTmp = pTmp->pFather;  
	}  
	// 搜索路径下的所有文件   
	if(pTmp->pFile != NULL)  
	{  
		File* pfileTmp = NULL;  
		pfileTmp = pTmp->pFile;  
		if (nType == ALL_FILEDIR || nType == ONLY_FILE)
		{
			std::cout << std::endl;
			std::cout << path << "目录下的文件：" << std::endl;
			std::cout << "<FILE>   " << pfileTmp->name << std::endl;
		}
		while(pfileTmp->pBrother!=NULL)  
		{  
			pfileTmp = pfileTmp->pBrother; 
			if (nType == ALL_FILEDIR || nType == ONLY_FILE)
				std::cout << "<FILE>   " << pfileTmp->name << std::endl;  
		}  
	}  
	return; 
}

bool match(const char *pattern,const char *content)
{ 
	if ('\0' == *pattern && '\0' == *content) 
		return true; 
	if ('*' == *pattern && '\0' != *(pattern + 1) && '\0' == *content) 
		return false; 
	if ('?' == *pattern || *pattern == *content) 
		return match(pattern + 1, content + 1); 
	if ('*' == *pattern) 
		return match(pattern + 1, content) || match(pattern, content + 1); 
	return false; 
}
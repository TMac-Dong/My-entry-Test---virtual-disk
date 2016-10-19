//////////////////////////////////////////////////
//FileName	: Factory.h 
//Author	: zhangyandong
//Date		: 2015/3/27
//Describe	: Builderģʽ
///////////////////////////////////////////
#pragma once
#include <string>

#include "MakedirCommand.h"
#include "DirCommand.h"
#include "CDCommand.h"
#include "DelCommand.h"
#include "RmdirCommand.h"
#include "CopyCommand.h"
#include "CompareCommand.h"

class Factory
{
public:
	typedef enum PRODUCTTYPE
	{
		TypeMakedir = 0,
		TypeDir,
		TypeCD,
		TypeDel,
		TypeRmdir,
		TypeCopy,
		TypeCompare,

		TypeNUM
	};
public:
	Command* CreateProduct(PRODUCTTYPE mType,CVirtualDisk *pDisk,MyString* pString,int nType)
	{
		switch (mType)
		{
		case TypeMakedir:
			return new CMakedirCommand(pDisk, pString ,nType);

		case TypeDir:
			return new CDirCommand(pDisk, pString ,nType);

		case TypeCD:
			return new CDCommand(pDisk, pString ,nType);

		case TypeDel:
			return new CDelCommand(pDisk, pString ,nType);

		case TypeRmdir:
			return new CRmdirCommand(pDisk, pString ,nType);

		case TypeCopy:
			return new CCopyCommand(pDisk, pString ,nType);

		case TypeCompare:
			return new CCompareCommand(pDisk, pString ,nType);

		default:
			return NULL;
		}
	}

public:
	PRODUCTTYPE mType;
};
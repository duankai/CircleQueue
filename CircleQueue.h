/////////////////////////////////////////////////////////////////////////
//																	   //
//																	   //
// COPYRIGHT NOTICE                                                    //
// Copyright (c) 2014                                                  //
//                                                                     //
// @File Name:     CircleQueue.h                                       //
// @File Function: Circle queue for store data 		                   //
//																	   //
// @Version 1.0 													   //
// @Author  Duan Kai            									   //
// @Date    2014-06-25												   //
//																	   //
/////////////////////////////////////////////////////////////////////////

#ifndef _CIRCLE_QUEUE_H_
#define _CIRCLE_QUEUE_H_

#include <string>

/************************************************************************/
/*
/* @STRUCT: Circle queue node
/*
/************************************************************************/
template<typename AnyData>
struct DATA_NODE_T
{
	int                    index;
	AnyData              * paDataNode;
	DATA_NODE_T<AnyData> * pstNext;
};

/************************************************************************/
/*
/* @CLASS: Declaration of CircleQueue class
/*
/************************************************************************/
template<typename AnyData>
class CircleQueue
{
public :
	CircleQueue(int iSize);
	int       GetCircleQueueLength();
	bool      AddData(AnyData data);
	bool      AllDataLarger(AnyData data, bool (* comparePf)(AnyData d1, AnyData d2));  //All data in this queue are larger than data
	bool      AllDataSmaller(AnyData data, bool (* comparePf)(AnyData d1, AnyData d2)); //All data in this queue are smaller than dada
	bool      DelData();
	bool      FullQueue();
	bool      GetInstanceStatus();
	AnyData * GetDataByIndex(int index);
	~CircleQueue();

private:
	void InitData();
private:
	int                    m_iSize;
	void                 * m_pdData;
	bool                   m_bInitRst;
	DATA_NODE_T<AnyData> * paHead;
	DATA_NODE_T<AnyData> * paTail;
};

/************************************************************************/
/*
/* @Function: Constructor of CircleQueue class
/* @Parameters: 
/*  1. name: iSize, type: int. The length of CircleQueue;
/* @Return: None.
/*-----------------------------------------------------------------------
/* @Author: Duan Kai
/* @Create Date: 2014-06-25
/* @Modify Date:
/*
/************************************************************************/
template<typename AnyData>
CircleQueue<AnyData>::CircleQueue(int iSize)
{
	InitData();
	if (iSize <= 0)
	{
		m_bInitRst = false;
		return;
	}
	m_iSize = iSize;

	m_pdData = (void *)malloc(sizeof(AnyData));
	if (!m_pdData)
	{
		m_bInitRst = false;
		return;
	}

	memset(m_pdData, 0, sizeof(AnyData));

	for(int i = 0; i < iSize; i++)
	{
		DATA_NODE_T<AnyData> * pstNewNode = (DATA_NODE_T<AnyData> *)malloc(sizeof(DATA_NODE_T<AnyData>));
		if (!pstNewNode)
		{
			m_bInitRst = false;
			return;
		}
		memset(pstNewNode, 0, sizeof(DATA_NODE_T<AnyData>));

		pstNewNode->index = i;

		pstNewNode->paDataNode = (AnyData *)malloc(sizeof(AnyData));
		if (!pstNewNode->paDataNode)
		{
			m_bInitRst = false;
			return;
		}
		memset(pstNewNode->paDataNode, 0, sizeof(AnyData));

		if (0 == i)
		{
			paHead = pstNewNode;
			paTail = pstNewNode;
		}
		else
		{
			paTail->pstNext = pstNewNode;
			paTail = paTail->pstNext;
		}
		
	}
	paTail->pstNext = paHead;
	paTail = paHead;
}

/************************************************************************/
/*
/* @Function: Initialize private data of CircleQueue
/* @Parameters: void
/* @Return: void.
/*-----------------------------------------------------------------------
/* @Author: Duan Kai
/* @Create Date: 2014-06-25
/* @Modify Date:
/*
/************************************************************************/
template<typename AnyData>
void CircleQueue<AnyData>::InitData()
{
	m_iSize    = 0;
	paHead     = NULL;
	paTail     = NULL;
	m_pdData   = NULL;
	m_bInitRst = true;
}

/************************************************************************/
/*
/* @Function: All data in CircleQueue are larger than the data which is given 
/* @Parameters: 
/* 1. name: data, type: AnyData. The given data;
/* 2. name: comparePf, type:bool (* comparePf)(AnyData d1, AnyData d2);
/*    This is the pointer function, which is declared by user. It is used
/*    to compare AnyData d1 and d2.
/* @Return: bool.
/*-----------------------------------------------------------------------
/* @Author: Duan Kai
/* @Create Date: 2014-06-25
/* @Modify Date:
/*
/************************************************************************/
template<typename AnyData>
bool CircleQueue<AnyData>::AllDataLarger(
	AnyData data, 
	bool (* comparePf)(AnyData d1, AnyData d2)
	)// if d1 > d2 return true;else return fasle; 
{
	DATA_NODE_T<AnyData> * pstTmp = paHead;
	if (!pstTmp)
	{
		return false;
	}
	do
	{
		if (!comparePf(*pstTmp->paDataNode, data))
		{
			return false;
		}
		pstTmp = pstTmp ->pstNext;
	}while(pstTmp != paTail);
	
	return true;

}

/************************************************************************/
/*
/* @Function: All data in CircleQueue are smaller than the data which is given 
/* @Parameters: 
/* 1. name: data, type: AnyData. The given data;
/* 2. name: comparePf, type:bool (* comparePf)(AnyData d1, AnyData d2);
/*    This is the pointer function, which is declared by user. It is used
/*    to compare AnyData d1 and d2.
/* @Return: bool.
/*-----------------------------------------------------------------------
/* @Author: Duan Kai
/* @Create Date: 2014-06-25
/* @Modify Date:
/*
/************************************************************************/
template<typename AnyData>
bool CircleQueue<AnyData>::AllDataSmaller(
	AnyData data, 
	bool (* comparePf)(AnyData d1, AnyData d2)
	)
{
	DATA_NODE_T<AnyData> * pstTmp = paHead;
	if (!pstTmp)
	{
		return false;
	}
	do
	{
		if (comparePf(*pstTmp->paDataNode, data))
		{
			return false;
		}
		pstTmp = pstTmp ->pstNext;
	}while(pstTmp != paTail);
	
	return true;
}

/************************************************************************/
/*
/* @Function: Deconstructor of CircleQueue
/* @Parameters: void
/* @Return: void.
/*-----------------------------------------------------------------------
/* @Author: Duan Kai
/* @Create Date: 2014-06-25
/* @Modify Date:
/*
/************************************************************************/
template<typename AnyData>
CircleQueue<AnyData>::~CircleQueue()
{
	DATA_NODE_T<AnyData> * pstTmp = paHead;
	DATA_NODE_T<AnyData> * currNode = NULL;

	if (!pstTmp)
	{
		return;
	}
	if (m_pdData)
	{
		free(m_pdData);
		m_pdData = NULL;
	}

	for(pstTmp = paHead; pstTmp->pstNext != paHead; pstTmp = currNode)
	{
		if (pstTmp)
		{
			currNode = pstTmp->pstNext;
			free(pstTmp);
			pstTmp = NULL;
		}
	}
	if (pstTmp)
	{
		free(pstTmp);
		pstTmp = NULL;
	}
}

/************************************************************************/
/*
/* @Function: Add data to CircleQueue
/* @Parameters: 
/* 1.name:data, type:AnyData
/* @Return: bool.
/*-----------------------------------------------------------------------
/* @Author: Duan Kai
/* @Create Date: 2014-06-25
/* @Modify Date:
/*
/************************************************************************/
template<typename AnyData>
bool CircleQueue<AnyData>::AddData(AnyData data)
{
	if (paTail->paDataNode)
	{
		memcpy(paTail->paDataNode, &data, sizeof(AnyData));
	}

	paTail = paTail->pstNext;
	return true;
}


/************************************************************************/
/*
/* @Function: Delete current data from CircleQueue
/* @Parameters: void
/* @Return: bool.
/*-----------------------------------------------------------------------
/* @Author: Duan Kai
/* @Create Date: 2014-06-25
/* @Modify Date:
/*
/************************************************************************/
template<typename AnyData>
bool CircleQueue<AnyData>::DelData()
{
	if (paTail->paDataNode)
	{
		AnyData * delNode = paTail->paDataNode;
		memset(delNode, 0, sizeof(AnyData));
		return true;
	}
	return false;
}

/************************************************************************/
/*
/* @Function: If the CircleQueue is full or not
/* @Parameters: void
/* @Return: bool.
/*-----------------------------------------------------------------------
/* @Author: Duan Kai
/* @Create Date: 2014-06-25
/* @Modify Date:
/*
/************************************************************************/
template<typename AnyData>
bool CircleQueue<AnyData>::FullQueue()
{
	DATA_NODE_T<AnyData> * pstTmp = paTail;
	do
	{
		if (!memcmp(m_pdData, pstTmp->paDataNode, sizeof(AnyData)))
		{
			return false;
		}
		pstTmp = pstTmp->pstNext;
	}while(pstTmp != paHead);

	return true;
}

/************************************************************************/
/*
/* @Function: Get AnyData * from CircleQueue by the given index
/* @Parameters: 
/* 1.name: index; type: int
/* @Return: AnyData *.
/*-----------------------------------------------------------------------
/* @Author: Duan Kai
/* @Create Date: 2014-06-25
/* @Modify Date:
/*
/************************************************************************/
template<typename AnyData>
AnyData * CircleQueue<AnyData>::GetDataByIndex(int index)
{
	DATA_NODE_T<AnyData> * pstTmp = paHead;
	do
	{
		if (pstTmp->index == index)
		{
			return pstTmp->paDataNode;
		}
		pstTmp = pstTmp->pstNext;
	}while(pstTmp != paHead);
	return NULL;
}

/************************************************************************/
/*
/* @Function: Get the size of CircleQueue
/* @Parameters: void
/* @Return: bool.
/*-----------------------------------------------------------------------
/* @Author: Duan Kai
/* @Create Date: 2014-06-25
/* @Modify Date:
/*
/************************************************************************/
template<typename AnyData>
int CircleQueue<AnyData>::GetCircleQueueLength()
{
	return m_iSize;
}

/************************************************************************/
/*
/* @Function: The CircleQueue initialize successful or not
/* @Parameters: void
/* @Return: bool.
/*-----------------------------------------------------------------------
/* @Author: Duan Kai
/* @Create Date: 2014-06-25
/* @Modify Date:
/*
/************************************************************************/
template<typename AnyData>
bool CircleQueue<AnyData>::GetInstanceStatus()
{
	return m_bInitRst;
}
#endif 
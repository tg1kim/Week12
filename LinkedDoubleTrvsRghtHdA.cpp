#include <stdio.h>
#include <stdlib.h>

#define DebugON
#pragma warning (disable: 4302 4311 4326 4996 6001)

typedef struct node {
	int nData;
	struct node *llink;
	struct node *rlink;
}	Node, *NodePtr;

#include "CmdListDRH.h"

void main()		// ��� ��带 ������ ���� ���� ���� ����Ʈ
{
	int InsertNode(NodePtr& pList, int nData);
	int DeleteNode(NodePtr& pList);
	int MoveRight(NodePtr& pList);
	int MoveLeft(NodePtr& pList);
	int MoveRepeatedly(NodePtr& pList, int nCtr);
	int OutputData(NodePtr& pList, int nCtr);
	void PrintList(NodePtr pList, const char *pCmnd);

	int nNdx = 0;
	int isGo = true;
	int bSuccess = true;
	NodePtr pList = new Node;						// head node for double linked list
	if (pList == NULL)
		return;
	pList->nData = -1;
	pList->llink = pList->rlink = pList;
	char sMsg[100], *pMsg = sMsg;
	while (isGo) {
		int nData;
		const char *pCmnd = sCmnds[nNdx++];		// ��ɾ �ϳ��� �����´�.
		switch (pCmnd[0] | 0x20) {			// �ҹ��ڷ�
		case 'i':							// ���ο� ��带 �����ʿ� ����
			nData = atoi(pCmnd + 1);
			bSuccess = InsertNode(pList, nData);
			break;
		case 'd':							// ��带 ����
			bSuccess = DeleteNode(pList);
			break;
		case 'l':							// �������� �ѹ� �̵�
			bSuccess = MoveLeft(pList);
			break;
		case 'r':							// ���������� �ѹ� �̵�
			bSuccess = MoveRight(pList);
			break;
		case 'm':							// ����(+)/��(-)������ n�� �̵�
			nData = atoi(pCmnd+1);
			bSuccess = MoveRepeatedly(pList, nData);
			break;
		case 'o':							// n�� �̵� �� ����� data�� ���
			nData = atoi(pCmnd+1);
			if ((nData = OutputData(pList, nData)) >= 0)
				*pMsg++ = nData;
			else
				bSuccess = false;
			break;
		case 'e':							// ��
			bSuccess = true;
			isGo = false;
			break;
		default:
			bSuccess = false;
		}
		if (bSuccess == false)
			printf("---> %d-th command(%s) error, ....\n", nNdx, pCmnd);
#ifdef  DebugON
		PrintList(pList, pCmnd);
#endif
	}
	*pMsg = NULL;
	printf("%s\n\n", sMsg);
}

int MoveRight(NodePtr& pList)
{	// ���� ���� ���� ����Ʈ pList �����͸� ���������� �ѹ� �̵��Ѵ�.
	// ����(����)�ϸ� true(false)�� return�Ѵ�.
	if (pList->rlink == pList)		// head node only
		return false;
	pList = pList->rlink;
	return true;
}

int MoveLeft(NodePtr& pList)
{	// ���� ���� ���� ����Ʈ pList �����͸� �������� �ѹ� �̵��Ѵ�.
	// ����(����)�ϸ� true(false)�� return�Ѵ�.
	if (pList->rlink == pList)		// head node only
		return false;
	pList = pList->llink;
	return true;
}

int InsertNode(NodePtr& pList, int nData)
{	// ���� ���� ����Ʈ pList ���ʿ� nData�� ������ ��带 �����ϰ� pList�� ���ο� ��带 ����Ų��.
	// ����(����)�ϸ� true(false)�� return�Ѵ�.
	NodePtr pNew = new Node;
	if (pNew) {
		pNew->nData = nData;
		NodePtr pRght = pList;
		NodePtr pLeft = pList->llink;
		pNew->rlink = pRght;
		pNew->llink = pLeft;
		pList =  pRght->llink = pLeft->rlink = pNew;
	}
	return (int)pNew;
}

int DeleteNode(NodePtr& pList)
{	// ���� ���� ����Ʈ pList�� ����Ű ��带 �����ϰ� pList�� �� ������ ��带 ����Ų��.
	// ����(����)�ϸ� true(false)�� return�Ѵ�.
	NodePtr pDel = NULL;
	if (pList->rlink != pList) {	// head node only
		pDel = pList;
		NodePtr pLeft = pDel->llink;
		NodePtr pRght = pDel->rlink;
		pRght->llink = pLeft;
		pLeft->rlink = pRght;
		pList = pRght;
		free(pDel);
	}
	return (int)pDel;
}

int MoveRepeatedly(NodePtr& pList, int nCtr)
{	// ����(+)/��(-)������ nCtr�� �̵��Ѵ�.
	// ����(����)�ϸ� true(false)�� return�Ѵ�.
	typedef int (*MoveFtnPtr)(NodePtr& pList);
	MoveFtnPtr pMoveFtn = MoveRight;
	if (nCtr < 0) {
		nCtr = -nCtr;
		pMoveFtn = MoveLeft;
	}
	for (int i = 0; i < nCtr; i++)
		if ((*pMoveFtn)(pList) == false)
			return false;
	return true;
}

int OutputData(NodePtr& pList, int nCtr)
{	// ����(+)/��(-)������ nCtr�� �̵��Ͽ� �ش� ����� �����͸� ��ȯ�Ѵ�.
	// �����ϸ� -1�� ��ȯ�Ѵ�.
	return MoveRepeatedly(pList, nCtr) ? pList->nData : -1;
}

void PrintList(NodePtr pList, const char *pCmnd)
{	// �����Ͱ� ���� ���� ������ ����Ѵ�.
	printf("%s: ", pCmnd);
	if (pList) {
		NodePtr pHead = pList;
		while (pHead->nData != -1)		// head ��带 ã�´�
			pHead = pHead->rlink;
		NodePtr pNode, pBgn;
		pBgn = pNode = pHead;
		do {							// ù ������ ����Ѵ�
			if (pNode == pList)
				putchar('<');
			if (pNode->nData > 0)		// head ���
				printf("%d", pNode->nData);
			else
				putchar('-');
			if (pNode == pList)
				putchar('>');
			putchar(0x20);
			pNode = pNode->rlink;
		} while (pNode != pBgn);
	}
	putchar('\n');
}

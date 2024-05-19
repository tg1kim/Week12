#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4302 4311 4326 6001)

#define DebugON
#pragma warning (disable: 4996)

typedef struct node {
	int nData;
	struct node *link;
}	Node, *NodePtr;

typedef struct {			// �������� �̵��ϱ� ���Ͽ� ���� 2���� �ʿ��մϴ�.
	Node *pLeft;			// left�� ���˴ϴ�.
	Node *pRght;			// rght�� ���˴ϴ�.
}	TwoWay, *TwoWayPtr;		// �� ������ �ϳ��� ��� ����Ϸ��� �մϴ�.

#include "CmdListRL.h"

void main()
{
	int InsertNode(TwoWayPtr pTwo, int nData);
	int DeleteNode(TwoWayPtr pTwo, int *pnData);
	int MoveRight(TwoWayPtr pTwo);
	int MoveLeft(TwoWayPtr pTwo);
	int MoveRepeatedly(TwoWayPtr pTwo, int nCtr);
	int OutputData(TwoWayPtr pTwo, int nCtr);
	void PrintList(TwoWayPtr pTwo, const char *pCmnd);

	int nNdx = 0;
	int bSuccess = true;
	TwoWay lnkdList;
	lnkdList.pLeft = lnkdList.pRght = NULL;	// ����� linked list�� �ʱ�ȭ
	int bDoing = true;
	char sMsg[100], *pMsg = sMsg;
	while (bDoing) {
		int nData;
		const char *pCmnd = sCmnds[nNdx++];		// ��ɾ �ϳ��� �����´�.
		switch (pCmnd[0] | 0x20) {
		case 'i':			// ���ʿ� ���ο� ��带 ����
			nData = atoi(pCmnd + 1);
			bSuccess = InsertNode(&lnkdList, nData);
			break;
		case 'd':			// ������ ù ��带 ����
			bSuccess = DeleteNode(&lnkdList, &nData);
			break;
		case 'l':			// �������� �ѹ� �̵�
			bSuccess = MoveLeft(&lnkdList);
			break;
		case 'r':			// ���������� �ѹ� �̵�
			bSuccess = MoveRight(&lnkdList);
			break;
		case 'm':			// ����(+)/��(-)������ n�� �̵�
			nData = atoi(pCmnd+1);
			bSuccess = MoveRepeatedly(&lnkdList, nData);
			break;
		case 'o':			// n�� �̵� �� ���� ����� data�� ��ȯ
			nData = atoi(pCmnd+1);
			if ((nData = OutputData(&lnkdList, nData)) >= 0)
				*pMsg++ = nData;
			else
				bSuccess = false;
			break;
		case 'e':			// ��
			bSuccess = true;
			bDoing = false;
			break;
		default:			// Error Message
			bSuccess = false;
		}
		if (bSuccess == false)
			printf("---> %d-th command(%s) error, ....\n", nNdx, pCmnd);
#ifdef	DebugON
		PrintList(&lnkdList, pCmnd);
#endif
	}
	*pMsg = NULL;
	printf("%s\n\n", sMsg);
}

int MoveRight(TwoWayPtr pTwo)
{	// ���������� �ѹ� �̵��Ѵ�.
	// �����ϸ� true�� return�ϰ�, �̵��� �� ������ false�� return�Ѵ�.
	return true;
}

int MoveLeft(TwoWayPtr pTwo)
{	// �������� �ѹ� �̵��Ѵ�.
	// �����ϸ� true�� return�ϰ�, �̵��� �� ������ false�� return�Ѵ�.
	return true;
}

int InsertNode(TwoWay *pTwo, int nData)
{	// ���� ����Ʈ�� �տ� nData�� ������ ��带 �����Ѵ�.
	// �����ϸ� true, �����ϸ� false�� return�Ѵ�.
	return true;
}

int DeleteNode(TwoWayPtr pTwo, int *pnData)
{	// ���� ����Ʈ�� ù ����� ����Ÿ�� pnData�� �����ϰ�
	// �� ù ��带 �����Ѵ�.
	// �����ϸ� true, �����ϸ� false�� return�Ѵ�.
	return true;
}

int MoveRepeatedly(TwoWayPtr pTwo, int nCtr)
{	// ����(+)/��(-)������ nCtr�� �̵��ϰ�
	// ����(����)�ϸ� true(false)�� return�Ѵ�.
	return true;
}

int OutputData(TwoWayPtr pTwo, int nCtr)
{	// ����(+)/��(-)������ nCtr�� �̵��Ͽ� ���� ����� �����͸� ��ȯ�Ѵ�.
	// ����(����)�ϸ� ���� ����� nData(-1)�� return�Ѵ�.
	return -1;
}

void PrintList(TwoWayPtr pTwo, const char *pCmnd)
{
	// ��ü �����͸� %d�� ����ϴµ� 
	// ������ �������� ����ϰ� 
	// �������� ������� ����Ѵ�.
	void PrintForward(NodePtr pNode);
	void PrintBackward(NodePtr pNode);

	printf("%s: ", pCmnd);
	PrintBackward(pTwo->pLeft);
	printf("<--+--> ");
	PrintForward(pTwo->pRght);
	putchar('\n');
}

void PrintForward(NodePtr pNode)
{
	if (pNode) {
		printf("%d ", pNode->nData);
		PrintForward(pNode->link);
	}
}

void PrintBackward(NodePtr pNode)
{
	if (pNode) {
		PrintBackward(pNode->link);
		printf("%d ", pNode->nData);
	}
}

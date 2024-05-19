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

void main()		// 헤드 노드를 가지는 원형 이중 연결 리스트
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
		const char *pCmnd = sCmnds[nNdx++];		// 명령어를 하나씩 가져온다.
		switch (pCmnd[0] | 0x20) {			// 소문자로
		case 'i':							// 새로운 노드를 오른쪽에 삽입
			nData = atoi(pCmnd + 1);
			bSuccess = InsertNode(pList, nData);
			break;
		case 'd':							// 노드를 삭제
			bSuccess = DeleteNode(pList);
			break;
		case 'l':							// 왼쪽으로 한번 이동
			bSuccess = MoveLeft(pList);
			break;
		case 'r':							// 오른쪽으로 한번 이동
			bSuccess = MoveRight(pList);
			break;
		case 'm':							// 오른(+)/왼(-)쪽으로 n번 이동
			nData = atoi(pCmnd+1);
			bSuccess = MoveRepeatedly(pList, nData);
			break;
		case 'o':							// n번 이동 후 노드의 data를 출력
			nData = atoi(pCmnd+1);
			if ((nData = OutputData(pList, nData)) >= 0)
				*pMsg++ = nData;
			else
				bSuccess = false;
			break;
		case 'e':							// 끝
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
{	// 원형 이중 연결 리스트 pList 포인터를 오른쪽으로 한번 이동한다.
	// 성공(실패)하면 true(false)를 return한다.
	if (pList->rlink == pList)		// head node only
		return false;
	pList = pList->rlink;
	return true;
}

int MoveLeft(NodePtr& pList)
{	// 원형 이중 연결 리스트 pList 포인터를 왼쪽으로 한번 이동한다.
	// 성공(실패)하면 true(false)를 return한다.
	if (pList->rlink == pList)		// head node only
		return false;
	pList = pList->llink;
	return true;
}

int InsertNode(NodePtr& pList, int nData)
{	// 원형 연결 리스트 pList 왼쪽에 nData를 가지는 노드를 삽입하고 pList는 새로운 노드를 가리킨다.
	// 성공(실패)하면 true(false)를 return한다.
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
{	// 원형 연결 리스트 pList가 가리키 노드를 삭제하고 pList는 그 오른쪽 노드를 가리킨다.
	// 성공(실패)하면 true(false)를 return한다.
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
{	// 오른(+)/왼(-)쪽으로 nCtr번 이동한다.
	// 성공(실패)하면 true(false)를 return한다.
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
{	// 오른(+)/왼(-)쪽으로 nCtr번 이동하여 해당 노드의 데이터를 반환한다.
	// 실패하면 -1을 반환한다.
	return MoveRepeatedly(pList, nCtr) ? pList->nData : -1;
}

void PrintList(NodePtr pList, const char *pCmnd)
{	// 데이터가 제일 작은 노드부터 출력한다.
	printf("%s: ", pCmnd);
	if (pList) {
		NodePtr pHead = pList;
		while (pHead->nData != -1)		// head 노드를 찾는다
			pHead = pHead->rlink;
		NodePtr pNode, pBgn;
		pBgn = pNode = pHead;
		do {							// 첫 노드부터 출력한다
			if (pNode == pList)
				putchar('<');
			if (pNode->nData > 0)		// head 노드
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

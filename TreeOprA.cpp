#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWAP(x, y)	x = (TreePtr)((unsigned long long)x ^ (unsigned long long)y);	\
					y = (TreePtr)((unsigned long long)x ^ (unsigned long long)y);	\
					x = (TreePtr)((unsigned long long)x ^ (unsigned long long)y);

#pragma warning (disable: 4326 4554 4996)

typedef struct node1 {			// 트리에서 노드
	char sData[5];
	struct node1 *lChild;
	struct node1 *rChild;
}	Node1, *Node1Ptr, Tree, *TreePtr;

typedef struct node2 {			// 스택, 큐에서 노드
	TreePtr pData;
	struct node2 *link;
}	Node2, *Node2Ptr, Stack, *StackPtr, Queue, *QueuePtr;

int InsertNode(TreePtr& pTree, const char *sData);
void Inorder(TreePtr pTree);
void Preorder(TreePtr pTree);
void Postorder(TreePtr pTree);
void IterativeInorder(TreePtr pTree);
void IterativePreorder(TreePtr pTree);
void LevelOrder(TreePtr pTree);
TreePtr CopyTree(TreePtr pTree);
int EqualTree(TreePtr pTree, TreePtr pTree1);
void SwapTree(TreePtr pTree);
void FreeTree(TreePtr pTree);

void main()
{
	const char *sMonth[] =  {"July", "Feb", "Aug", "May", "Oct", "Nov", "Dec", "Mar", "Sept", "Jan", "June", "Apr"};
	TreePtr pTree0 = NULL;
	for (int i = 0; i < sizeof(sMonth) / sizeof(sMonth[0]); i++)
		InsertNode(pTree0, sMonth[i]);
	char sCmnd[10];
	TreePtr pTree1 = NULL;
	while (1) {
		printf("\n[i nrotulcqsx e] ? ");
		gets_s(sCmnd);
		switch (*sCmnd | 0x20) {
		case 'i':
			printf("Data ? ");
			gets_s(sCmnd);
			if (InsertNode(pTree0, sCmnd))
				printf("Inserted ...\n");
			break;
		case 'n':
			printf("     Inorder Trav:");
			Inorder(pTree0);
			printf("\n");
			break;
		case 'r':
			printf("    Preorder Trav:");
			Preorder(pTree0);
			printf("\n");
			break;
		case 'o':
			printf("   Postorder Trav:");
			Postorder(pTree0);
			printf("\n");
			break;
		case 't':
			printf("Iter inorder Trav:");
			IterativeInorder(pTree0);
			printf("\n");
			break;
		case 'u':
			printf("Ite Preorder Trav:");
			IterativePreorder(pTree0);
			printf("\n");
			break;
		case 'l':
			printf(" Level order Trav:");
			LevelOrder(pTree0);
			printf("\n");
			break;
		case 'c':
			if (pTree1)
				FreeTree(pTree1);
			pTree1 = CopyTree(pTree0);
			printf("Copyed ...\n");
			break;
		case 'q':
			if (EqualTree(pTree0, pTree1))
				printf("Yes\n");
			else
				printf("No\n");
			break;
		case 's':
			SwapTree(pTree0);
			printf("Swapped ...\n");
			break;
		case 'x':
			printf("Exchanged ...\n");
			SWAP(pTree0, pTree1);
			break;
		case 'e':
			if (pTree0)
				FreeTree(pTree0);
			if (pTree1)
				FreeTree(pTree1);
			printf("Freed ...\n");
			return;
		default:
			printf("Invalid command ....\n");
		}
	}
}

int InsertNode(TreePtr& pTree, const char *sData)
{	// return true for success
	if (pTree == NULL) {
		pTree = (TreePtr)malloc(sizeof(Node1));
		if (pTree) {
			pTree->lChild = pTree->rChild = NULL;
			strcpy(pTree->sData, sData);
		}
		return pTree != NULL;
	}
	int nCond = strcmp(sData, pTree->sData);
	if (nCond < 0)
		return InsertNode(pTree->lChild, sData);
	if (nCond > 0)
		return InsertNode(pTree->rChild, sData);
	return false;
}

void Inorder(TreePtr pTree)
{
	if (pTree) {
		Inorder(pTree->lChild);			// L
		printf(" %s", pTree->sData);	// D
		Inorder(pTree->rChild);			// R
	}
} 

void Preorder(TreePtr pTree)
{
	if (pTree) {
		printf(" %s", pTree->sData);	// D
		Preorder(pTree->lChild);		// L
		Preorder(pTree->rChild);		// R
	}
}

void Postorder(TreePtr pTree)
{
	if (pTree) {
		Postorder(pTree->lChild);		// L
		Postorder(pTree->rChild);		// R
		printf(" %s", pTree->sData);	// D
	}
}

void Push(StackPtr& pStack, TreePtr pTree)
{	// 첫 노드로 삽입
	Node2Ptr pNew = (Node2Ptr)malloc(sizeof(Node2));
	if (pNew) {
		pNew->pData = pTree;
		pNew->link = pStack;
		pStack = pNew;
	}
}

TreePtr Pop(StackPtr& pStack)
{	// 첫 노드를 삭제
	if (pStack == NULL)
		return NULL;
	Node2Ptr pDel = pStack;
	TreePtr pData = pDel->pData;
	pStack = pDel->link;
	free(pDel);
	return pData;
}

// 큐를 마지막 노드를 가리키는 원형 연결 리스트로 표현
void AddQ(QueuePtr& pQueue, TreePtr pTree)
{	// 마지막 노드로 삽입
	Node2Ptr pNew = (Node2Ptr)malloc(sizeof(Node2));
	if (pNew) {
		pNew->pData = pTree;
		if (pQueue) {
			pNew->link = pQueue->link;
			pQueue->link = pNew;
		}
		else
			pNew->link = pNew;
		pQueue = pNew;
	}
}

TreePtr DeleteQ(QueuePtr& pQueue)
{	// 첫 노드를 삭제
	if (pQueue == NULL)
		return NULL;
	Node2Ptr pDel = pQueue->link;
	TreePtr pData = pDel->pData;
	if (pQueue == pDel)
		pQueue = NULL;
	else
		pQueue->link = pDel->link;
	free(pDel);
	return pData;
}

void IterativeInorder(TreePtr pTree)
{
	StackPtr pStack = NULL;
	while (1) {
		while (pTree) {
			Push(pStack, pTree);
			pTree = pTree->lChild;
		}
		pTree = Pop(pStack);
		if (pTree == NULL)
			return;
		printf(" %s", pTree->sData);
		pTree = pTree->rChild;
	}
}

void IterativePreorder(TreePtr pTree)
{
	StackPtr pStack = NULL;
	while (1) {
		while (pTree) {
			Push(pStack, pTree);
			printf(" %s", pTree->sData);
			pTree = pTree->lChild;
		}
		pTree = Pop(pStack);
		if (pTree == NULL)
			return;
		pTree = pTree->rChild;
	}
}

void LevelOrder(TreePtr pTree)
{
	QueuePtr pQueue = NULL;
	if (pTree) {
		AddQ(pQueue, pTree);
		while (1) {
			if ((pTree = DeleteQ(pQueue)) == NULL)
				break;
			printf(" %s", pTree->sData);
			if (pTree->lChild)
				AddQ(pQueue, pTree->lChild);
			if (pTree->rChild)
				AddQ(pQueue, pTree->rChild);
		}
	}
}

TreePtr CopyTree(TreePtr pTree)
{
	TreePtr pTree1 = NULL;
	if (pTree) {
		pTree1 = (TreePtr)malloc(sizeof(Tree));
		if (pTree1) {
			strcpy(pTree1->sData, pTree->sData);
			pTree1->lChild = CopyTree(pTree->lChild);
			pTree1->rChild = CopyTree(pTree->rChild);
		}
	}
	return pTree1;
}

int EqualTree(TreePtr pTree1, TreePtr pTree2)
{
	if (pTree1 == NULL && pTree2 == NULL)
		return true;
	if (pTree1 == NULL || pTree2 == NULL)
		return false;
	return strcmp(pTree1->sData, pTree2->sData) == 0 &
		EqualTree(pTree1->lChild, pTree2->lChild) &
		EqualTree(pTree1->rChild, pTree2->rChild);
}

void SwapTree(TreePtr pTree)
{
	if (pTree) {
		SwapTree(pTree->lChild);
		SwapTree(pTree->rChild);
		SWAP(pTree->lChild, pTree->rChild);
	}
}

void FreeTree(TreePtr pTree)
{
	if (pTree) {
		FreeTree(pTree->lChild);
		FreeTree(pTree->rChild);
		free(pTree);
	}
}


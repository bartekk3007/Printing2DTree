#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct TreeNode 
{
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};

struct TreeNode** impC(struct TreeNode** head, int n)
{
	if (n <= (*head)->val)
	{
		return &(*head)->right;
	}
	else
	{
		return &(*head)->left;
	}
}

struct TreeNode** pC(struct TreeNode** head, int n)
{
	if (n <= (*head)->val)
	{
		return &(*head)->left;
	}
	else
	{
		return &(*head)->right;
	}
}

void rotateLeft(struct TreeNode** head)
{
	struct TreeNode* temp = (*head)->right;
	struct TreeNode* tempLeft = (*head);
	struct TreeNode* tempLeftRight = (*head)->right->left;

	temp->left = tempLeft;
	temp->left->right = tempLeftRight;
	//tempLeft->right = tempLeftRight;

	*head = temp;
}

void rotateRight(struct TreeNode** head)
{
	struct TreeNode* temp = (*head)->left;
	struct TreeNode* tempRight = (*head);
	struct TreeNode* tempRightLeft = (*head)->left->right;

	temp->right = tempRight;
	temp->right->left = tempRightLeft;
	//tempRight->left = tempRightLeft;

	*head = temp;
}

int returnLowerPow(int n)
{
	return (int)pow((double)2, (double)n - 2);
}

int returnHeight(struct TreeNode* head)
{
	if (head == NULL)
	{
		return 0;
	}
	else
	{
		int lDepth = returnHeight(head->left);
		int rDepth = returnHeight(head->right);

		if (lDepth > rDepth)
		{
			return (lDepth + 1);
		}
		else
		{
			return (rDepth + 1);
		}
	}
}

int returnWidth(struct TreeNode* head)
{
	int n = returnHeight(head);
	return (int)pow((double)2, (double)n) - 1;
}

void insertToArray(struct TreeNode* head, struct TreeNode** dataArr, int height, int width, int l, int d)
{
	if (head == NULL)
	{
		return;
	}
	else
	{
		dataArr[l * width + d] = head;
		insertToArray(head->left, dataArr, height, width, l + 1, d - returnLowerPow(height - l));
		insertToArray(head->right, dataArr, height, width, l + 1, d + returnLowerPow(height - l));
	}
}

void print2DTree(struct TreeNode* head)
{
	int height = returnHeight(head);
	int width = returnWidth(head);
	struct TreeNode** dataArr = (struct TreeNode**)calloc(height * width, sizeof(struct TreeNode*));

	if (dataArr)
	{
		insertToArray(head, dataArr, height, width, 0, width / 2);

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (dataArr[i * width + j] == NULL)
				{
					printf("\t");
				}
				else
				{
					printf("%d\t", dataArr[i * width + j]->val);
				}
			}
			printf("|\n");
		}
		printf("\n");
	}
}

void deleteZeroChildren(struct TreeNode** head, int n)
{
	if (n <= (*head)->val)
	{
		free(*pC(head, n));
		(*head)->left = NULL;
	}
	else
	{
		free(*pC(head, n));
		(*head)->right = NULL;
	}
}

void deleteOneChildren(struct TreeNode** head, struct TreeNode** grandChild, int n)
{
	struct TreeNode* temp = *grandChild;
	if (n <= (*head)->val)
	{
		free((*head)->left);
		(*head)->left = temp;
	}
	else
	{
		free((*head)->right);
		(*head)->right = temp;
	}
}

void deleteTwoChildren(struct TreeNode** head, int n)
{
	struct TreeNode* parentSuccessor = *pC(head, n);
	struct TreeNode* successor = (*pC(head, n))->right;
	while (successor->left != NULL)
	{
		parentSuccessor = successor;
		successor = successor->left;
	}
	(*pC(head, n))->val = successor->val;
	if ((*pC(head, n))->right == successor)
	{
		if (successor->right != NULL)
		{
			parentSuccessor->right = successor->right;
		}
		else
		{
			parentSuccessor->right = NULL;
		}
	}
	else
	{
		if (successor->right != NULL)
		{
			parentSuccessor->left = successor->right;
		}
		else
		{
			parentSuccessor->left = NULL;
		}
	}
	free(successor);
}

void delete(struct TreeNode** head, int n)
{
	if (*head == NULL)
	{
		return;
	}
	else if ((*head)->val == n && *pC(head, n) == NULL)
	{
		free(*head);
		head = NULL;
	}
	else if ((*pC(head, n))->val == n && *pC(pC(head, n), n) == NULL && *impC(pC(head, n), n) == NULL)
	{
		deleteZeroChildren(head, n);
	}
	else if ((*pC(head, n))->val == n && *impC(pC(head, n), n) == NULL)
	{
		deleteOneChildren(head, pC(pC(head, n), n), n);
	}
	else if ((*pC(head, n))->val == n && *pC(pC(head, n), n) == NULL)
	{
		deleteOneChildren(head, impC(pC(head, n), n), n);
	}
	else if ((*pC(head, n))->val == n)
	{
		deleteTwoChildren(head, n);
	}
	else
	{
		delete(pC(head, n), n);
	}
}

void insert(struct TreeNode** head, int n)
{
	struct TreeNode* vertex = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	if (vertex)
	{
		vertex->val = n;
		vertex->left = NULL;
		vertex->right = NULL;

		if (*head == NULL)
		{
			*head = vertex;
		}
		else
		{
			if (n <= (*head)->val)
			{
				insert(&(*head)->left, n);
			}
			else
			{
				insert(&(*head)->right, n);
			}
		}
	}
}

int main(void)
{
	struct TreeNode* head = NULL;
	
	/*
	insert(&head, 100);
	insert(&head, 50);
	insert(&head, 80);
	insert(&head, 200);

	print2DTree(head);
	
	rotateLeft(&(head)->left);

	print2DTree(head);
	*/

	insert(&head, 100);
	insert(&head, 200);
	insert(&head, 300);
	insert(&head, 150);
	insert(&head, 50);
	insert(&head, 30);
	insert(&head, 70);

	print2DTree(head);

	delete(&head, 200);

	print2DTree(head);

	delete(&head, 50);

	print2DTree(head);

	return 0;
}

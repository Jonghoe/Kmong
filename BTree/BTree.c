#include<stdio.h>
#include<stdlib.h>
#include "BTree.h" 

void Make_BTree(BTree** NEW){
	*NEW = (BTree*)malloc(sizeof(BTree));
	(*NEW)->root = NULL;
	(*NEW)->m = MAX + 1;
	(*NEW)->self = *NEW;
}

void Delete_BTree(BTree** Del){
	free(*Del);
}

element SearchTree(BTree* self, const int x){
	element element;
	int pos ;
	TreeNode *node = Search(self,x, self->root, &pos);
	if (!node)
	{
		element.i = 0;
		element.r = self->root;
		element.tag = 1;
	}
	else
	{
		element.i = pos;
		element.r = node;
		element.tag = 0;
	}
	return element;
}

TreeNode *Search(BTree* self,const int x, TreeNode *current, int *pos)
{
	if (!current)
		return NULL;
	if (SearchNode(self,x, current, pos))
		return current;
	else return Search(self,x, current->ptr[*pos], *pos);
}



BOOL SearchNode(BTree* self,const int x, TreeNode *current, int *pos)
{
	if (x<current->key[1])
	{
		*pos = 0;
		return FALSE;
	}
	else
	{
		for (*pos = (current->count); (x<current->key[*pos]) && (*pos>1); (*pos)--);
		return x == current->key[*pos];
	}
}

TreeNode *Insert(BTree* self,const int x)
{
	int midNode;
	TreeNode *midright = NULL;
	TreeNode *newroot;
	element loc = SearchTree(self, &x);
	

	if (PushDown(self,x, self->root, &midNode, &midright))
	{
		//newroot = new   TreeNode;
		newroot = (TreeNode*)malloc(sizeof(TreeNode));
		newroot->count = 1;
		newroot->key[1] = midNode;
		newroot->ptr[0] = self->root;
		newroot->ptr[1] = midright;
		newroot->parent = NULL;
		if (self->root != NULL)
		{
			self->root->parent = newroot;
			midright->parent = self->root->parent;
		}
		self->root = newroot;
	}
	return self->root;
}


BOOL PushDown(BTree* self,int x, TreeNode *current, int *midNode, TreeNode **midright)
{
	int pos;
	if (current == NULL)
	{
		*midNode = x;
		*midright = NULL;
		return TRUE;
	}
	else
	{
		if (SearchNode(self,x, current, &pos))
		{
			return FALSE;
		}
		if (PushDown(self,x, current->ptr[pos], midNode, midright))
		{
			if (current->count<MAX)
			{
				PushIn(self,*midNode, *midright, current, pos);

				return FALSE;
			}
			else
			{
				Split(self,*midNode, *midright, current, pos, midNode, midright);

				return TRUE;
			}
		}
		return FALSE;
	}
}


void PushIn(BTree*self ,int midNode, TreeNode *midright, TreeNode *current, int pos)
{
	int i;
	for (i = current->count; i>pos; i--)
	{
		current->key[i + 1] = current->key[i];
		current->ptr[i + 1] = current->ptr[i];
	}
	current->key[pos + 1] = midNode;
	current->ptr[pos + 1] = midright;
	current->count++;
}

// 일반적인 노드 내 키 삽입    
void Split(BTree* self,int midNode, TreeNode *midright, TreeNode *current, int pos, int *newNode, TreeNode **newright)
{
	int i;
	int median;
	if (pos <= MIN)
		median = MIN;
	else median = MIN + 1;

	*newright = (TreeNode *)malloc(sizeof(TreeNode));
	for (i = median + 1; i <= MAX; i++)
	{
		(*newright)->key[i - median] = current->key[i];
		(*newright)->ptr[i - median] = current->ptr[i];
	}
	(*newright)->count = MAX - median;
	(*newright)->parent = current->parent;
	current->count = median;
	if (pos <= MIN)
		PushIn(self,midNode, midright, current, pos);
	else PushIn(self,midNode, midright, *newright, pos - median);
	*newNode = current->key[current->count];
	(*newright)->ptr[0] = current->ptr[current->count];
	current->count--;
}

// 노드 분할작업    

BOOL Delete(BTree* self,const int *x)
{
	element loc = SearchTree(self,*x);
	int d;
	TreeNode *p = loc.r, *q, *s;
	int j = loc.i;
	if (loc.tag) {

		return FALSE;
	}

	
	if (p->ptr[j] != NULL)
	{
		s = p->ptr[j];
		q = p;
		while (s != NULL)
		{
			q = s; s = s->ptr[0];
		}
		p->key[j] = q->key[1];
		compress(self,q, 1);
		p = q;
	}
	else compress(self,p, j);


	d = (self->m + 1) / 2;
	while (1)
	{
		if (p->count<d - 1)
		{
			j = 0;
			q = p->parent;
			while (j <= q->count&&q->ptr[j] != p)
				j++;
			if (!j) LeftAdjust(self,p, q, d, j);
			else RightAdjust(self,p, q, d, j);
			p = q;
			if (p == self->root) break;
		}
		else break;
	}
	if (!self->root->count)
	{
		p = self->root->ptr[0];
		free(self->root);
		self->root = p;
		self->root->parent = NULL;
	}

	return TRUE;
}


// 좌로 병합

void LeftAdjust(BTree*self,TreeNode *p, TreeNode *q, int d, int j)
{
	TreeNode *p1 = q->ptr[1];
	if (p1->count>(d - 1))
	{
		(p->count)++;
		p->key[p->count] = q->key[1];
		q->key[1] = p1->key[1];
		p->ptr[p->count] = p1->ptr[0];
		p1->ptr[0] = p1->ptr[1];
		compress(self,p1, 1);
	}
	else merge(self,p, q, p1, 1);
}


void RightAdjust(BTree* self,TreeNode *p, TreeNode *q, int d, int j)
{
	TreeNode *p1 = q->ptr[j - 1];
	int i;
	if (p1->count>(d - 1))
	{
		(p->count)++;
		for (i = p->count; i>1; i--)
		{
			p->ptr[i] = p->ptr[i - 1];
			p->key[i] = p->key[i - 1];
		}
		i = 1;
		p->ptr[i] = p->ptr[i - 1];
		p->key[1] = q->key[j];
		p->ptr[0] = p1->ptr[p1->count];
		q->key[j] = p1->key[p1->count];
		(p1->count)--;
	}
	else
	{
		p1->key[(p1->count) + 1] = q->key[j];
		p1->ptr[(p1->count) + 1] = p->ptr[0];
		for (i = 1; i <= p->count; i++)
		{
			p1->key[(p1->count) + i + 1] = p->key[i];
			p1->ptr[(p1->count) + i + 1] = p->ptr[i];
		}
		compress(self,q, j);
		p1->count = p1->count + p->count + 1;
		free(p);
	}
}



void compress(BTree* self,TreeNode *p, int j)
{
	for (int i = j; i<p->count; i++)
	{
		p->key[i] = p->key[i + 1];
		p->ptr[i] = p->ptr[i + 1];
	}
	(p->count)--;
}


void merge(BTree* self,TreeNode *p, TreeNode *q, TreeNode *p1, int j)
{
	p->key[(p->count) + 1] = q->key[1];
	p->ptr[(p->count) + 1] = q->ptr[0];
	for (j = 1; j <= p1->count; j++)
	{
		p->key[(p->count) + j + 1] = p1->key[j];
		p->ptr[(p->count) + j + 1] = p1->ptr[j];
	}
	compress(self,q, 1);
	p->count = (p->count) + (p1->count) + 1;
	free( p1);
}

// 트리의 키 출력 private
void Inorder(BTree* self,TreeNode *current)
{
	int j = 0,i;
	for (i = 0; i < current->count + 1; i++) {
		if (current->ptr[i])
			Inorder(self,current->ptr[i]);
		if (j <= i && current->key[i] >0)
			printf("< %d, %p, (%d, %p)>\n", current->count, &(current->ptr[i]), current->key[i], &(current->key[i]));
	}
}

void inoder(BTree* self) {
	printf("중위순회 \n");
	Inorder(self, self->root);
	//printf(">\n");
}
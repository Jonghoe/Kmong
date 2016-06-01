#ifndef BTREE_H
#define BTREE_H
#define MAX		2
#define MIN     1   
#define TRUE	1   
#define FALSE	0

typedef int BOOL;


typedef struct tag_treenode TreeNode;
struct tag_treenode {
	int count;
	int key[MAX + 1];
	//TreeNode*
	TreeNode* parent;
	void* ptr[MAX + 1];
};

typedef struct{
	int i;
	int tag;
	TreeNode *r;
}element;
typedef struct tag_BTree BTree;
struct tag_BTree{
	int m;
	TreeNode *root;
	BTree* self;
};

void Make_BTree(BTree** NEW);
void Delete_BTree(BTree** Del);
element SearchTree(BTree* self,const int x);
TreeNode *Insert(BTree* self, const int x);
BOOL Delete(BTree* self, const int *x);
BOOL SearchNode(BTree* self, const int x, TreeNode *current, int *pos);
BOOL PushDown(BTree* self, int newentry, TreeNode *current, int *midNode, TreeNode **midright);
void PushIn(BTree* self, int midNode, TreeNode *midright, TreeNode *current, int pos);
void Split(BTree* self, int midNode, TreeNode *midright, TreeNode *current, int pos, int *newmedian, TreeNode **newright);
void LeftAdjust(BTree* self, TreeNode *p, TreeNode *q, int d, int j);
void RightAdjust(BTree* self, TreeNode *p, TreeNode *q, int d, int j);
void compress(BTree* self, TreeNode *p, int j);
void merge(BTree* self, TreeNode *p, TreeNode *q, TreeNode *p1, int j);
TreeNode *Search(BTree* self, const int x, TreeNode *current, int *pos);
void Inorder(BTree* self,TreeNode *current);
void inoder(BTree* self);

#endif
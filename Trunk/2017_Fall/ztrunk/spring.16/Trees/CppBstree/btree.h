#include <iostream>
#include <time.h>
#include <string>

using namespace std;

struct TreeNode{
	int value;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
	int AvlValue;
};

class BTree{

private:
	TreeNode *root;
	bool RightHeavy(TreeNode *nodePtr);
	bool LeftHeavy(TreeNode *nodePtr);
	void insert(TreeNode *&, TreeNode *&);
	void inorder(TreeNode *nodePtr);
	void preorder(TreeNode *nodePtr);
	void postorder(TreeNode *nodePtr);
	void deleteNode(int ,TreeNode *&);
	void makeDeletion(TreeNode *&nodePtr);
	int  Height(TreeNode *nodePtr);
	void ComputeAvlValues(TreeNode *&nodePtr);
	void RotateLeft(TreeNode *&nodePtr);
	void RotateRight(TreeNode *&nodePtr);
	int  AvlValue(TreeNode *nodePtr);

public:
	BTree();
	~BTree();
	void DoDumpTree(TreeNode *nodePtr);
	void DumpTree(){cout<<"---------------------------------"<<endl;
	                cout<<"Root:   "<<root<<"\n";
					DoDumpTree(root);
	};
	void insertNode(int);
	void ShowInorder(){inorder(root);};
	void ShowPreorder(){preorder(root);};
	void ShowPostorder(){postorder(root);};
	bool SearchNode(int);
	void remove(int num){deleteNode(num,root);};
	int  TreeHeight();
    void GraphVizGetIds(TreeNode *nodePtr,ofstream &VizOut);
	void GraphVizMakeConnections(TreeNode *nodePtr,ofstream &VizOut);
	void GraphVizOut(string filename,int);
};


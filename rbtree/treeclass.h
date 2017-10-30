#ifndef __TREECLASS__H__
#define __TREECLASS__H__
#include<iostream>
using namespace std;
#include<list>
#include<vector>
enum COLOR{
	RED=0,
	BLACK = 1
};

class TreeNode
{
public:
	TreeNode():m_pParent(NULL), m_pLeftChild(NULL), m_pRightChild(NULL), m_nData(0), m_nColor(RED){}
	TreeNode(const TreeNode & tree){
		this->m_nData = tree.m_nData;
		this->m_pParent = NULL;
		this->m_pLeftChild = NULL;
		this->m_pRightChild = NULL;
		m_nColor = tree.m_nColor;
	}

	TreeNode(int data):m_nData(data), m_pRightChild(NULL), m_pLeftChild(NULL), m_pParent(NULL),m_nColor(RED){}
	~TreeNode(){ 
		this->m_nData = 0;
		this->m_pLeftChild = NULL;
		this->m_pParent = NULL;
		this->m_pRightChild = NULL;
	}

	TreeNode& operator =(const TreeNode& treeNode)//赋值运算符
	{
		
		if (this != &treeNode)
		{
			this->m_pParent = treeNode.m_pParent;
			this->m_pLeftChild = treeNode.m_pLeftChild;
			this->m_pRightChild = treeNode.m_pRightChild;
			this->m_nData = treeNode.m_nData;
			this->m_nColor = treeNode.m_nColor;
		}
		return *this;
	} 

	
		
	friend ostream & operator<<(ostream &out, TreeNode &obj)
	{
		out <<  " " << obj.m_nData <<" ";
		return out;
	}


	TreeNode * m_pParent;
	TreeNode * m_pLeftChild;
	TreeNode * m_pRightChild;
	int m_nData;	
	int m_nColor;
};



class TreeClass
{
public:
	TreeClass():m_pRoot(NULL){}
	~TreeClass(){
		
		if(!m_pRoot)
		{
			return;
		}

		//找到树的最小节点

		TreeNode * treeNodeTemp = findMinNode(m_pRoot);
		vector<TreeNode *> treenodeVec;
		while(treeNodeTemp)
		{
			treenodeVec.push_back(treeNodeTemp);
			treeNodeTemp = findNextNode(treeNodeTemp);
			
		}

		for(int i = 0; i < treenodeVec.size(); i++)
		{
			delete(treenodeVec[i]);
		}

		treenodeVec.clear();
		m_pRoot = NULL;
	}
	
	void initial(   list<int>& data);

	void visitTree();

	//搜索前继节点
	TreeNode *findPreNode(TreeNode * treeNode);

	//搜索后继节点
	TreeNode * findNextNode(TreeNode * treeNode);

	//寻找一个子树最小节点
	TreeNode * findMinNode(TreeNode * root);
	//寻找一个子树最大节点
	TreeNode * findMaxNode(TreeNode * root);
	
	void eraseNode(int i);

	TreeNode * findTreeNode(int i);
	//节点X左旋
	void leftRotate(TreeNode * x);
	//节点Y左旋
	void rightRotate(TreeNode * y);
	//插入节点
	void rbInsertNode(TreeNode * z);
	//旋转和着色
	void rbInsertFixUp(TreeNode * z);
	//删除节点
	TreeNode *  rbDeleteNode(TreeNode * z);
	//删除后旋转和调颜色
	void rbDeleteFixUp(TreeNode * z);

	
	
	TreeNode * m_pRoot;
};





#endif


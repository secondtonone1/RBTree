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

	TreeNode& operator =(const TreeNode& treeNode)//��ֵ�����
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

		//�ҵ�������С�ڵ�

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

	//����ǰ�̽ڵ�
	TreeNode *findPreNode(TreeNode * treeNode);

	//������̽ڵ�
	TreeNode * findNextNode(TreeNode * treeNode);

	//Ѱ��һ��������С�ڵ�
	TreeNode * findMinNode(TreeNode * root);
	//Ѱ��һ���������ڵ�
	TreeNode * findMaxNode(TreeNode * root);
	
	void eraseNode(int i);

	TreeNode * findTreeNode(int i);
	//�ڵ�X����
	void leftRotate(TreeNode * x);
	//�ڵ�Y����
	void rightRotate(TreeNode * y);
	//����ڵ�
	void rbInsertNode(TreeNode * z);
	//��ת����ɫ
	void rbInsertFixUp(TreeNode * z);
	//ɾ���ڵ�
	TreeNode *  rbDeleteNode(TreeNode * z);
	//ɾ������ת�͵���ɫ
	void rbDeleteFixUp(TreeNode * z);

	
	
	TreeNode * m_pRoot;
};





#endif


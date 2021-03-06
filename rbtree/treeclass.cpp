#include "treeclass.h"

void TreeClass::initial(   list<int>& data)
{
	for(   list<int>::iterator   listIter = data.begin(); listIter != data.end();
		listIter++)
	{
		TreeNode * treeNode = m_pRoot;
		if(!treeNode)
		{
			m_pRoot = new TreeNode(*listIter);
			continue;
		}

		TreeNode * nodeParent = NULL;
		bool findflag = true;
		while(treeNode)
		{
			if(treeNode->m_nData < *listIter)
			{
				nodeParent = treeNode;
				treeNode = treeNode->m_pRightChild;
			}
			else if(treeNode->m_nData >  *listIter)
			{
				nodeParent = treeNode;
				treeNode = treeNode->m_pLeftChild;
			}
			else
			{
				//找到树中有相等的节点，那么不插入，也可以完善为次数+1
				findflag = false;
				break;
			}
		}

		if(findflag)
		{
			if(nodeParent->m_nData <*listIter )
			{
				TreeNode * treeNodeTemp =new TreeNode(*listIter);

				nodeParent->m_pRightChild = treeNodeTemp;
				treeNodeTemp->m_pParent = nodeParent;
			}
			else
			{
				TreeNode * treeNodeTemp =new TreeNode(*listIter);
				nodeParent->m_pLeftChild = treeNodeTemp;
				treeNodeTemp->m_pParent = nodeParent;
			}
		}

	}


}

//中序遍历
void TreeClass::visitTree()
{
	if(!m_pRoot)
	{
		cout << "empty tree!!!";
	}

	//找到树的最小节点
	
	TreeNode * treeNodeTemp = findMinNode(m_pRoot);
	
	while(treeNodeTemp)
	{
		cout << (*treeNodeTemp);
		treeNodeTemp = findNextNode(treeNodeTemp);
	}
	
}

//寻找一个子树最小节点
TreeNode * TreeClass::findMinNode(TreeNode * root)
{
	if(!root)
	{
		return NULL;
	}
	TreeNode * treeNode = root;
	while(treeNode->m_pLeftChild)
	{
		treeNode = treeNode->m_pLeftChild;
	}

	return treeNode;
}

//寻找一个子树最大节点
TreeNode * TreeClass::findMaxNode(TreeNode * root)
{
	if(!root)
	{
		return NULL;
	}
	TreeNode * treeNode = root;
	while(treeNode->m_pRightChild)
	{
		treeNode = treeNode->m_pRightChild;
	}

	return treeNode;
}


//搜索前驱节点
TreeNode* TreeClass::findPreNode(TreeNode * treeNode)
{
	//左子树不为空，找到左子树中最大节点
	if( treeNode->m_pLeftChild )
	{
		TreeNode * treeNodeTemp = findMaxNode( treeNode->m_pLeftChild); 
		return treeNodeTemp;
	}

	//左子树为空
	//找到父节点，如果该节点是父节点的右孩子，那么父节点为前驱节点。
	//如果不满足，则将父节点设为该节点，继续向上找，知道满足条件或者父节点为空
	
	TreeNode * treeNodeTemp = treeNode->m_pParent;

	while(treeNodeTemp && treeNode != treeNodeTemp->m_pRightChild)
	{
		treeNode = treeNodeTemp;
		treeNodeTemp = treeNodeTemp ->m_pParent;
	}

	return treeNodeTemp;

}

//搜索后继节点
TreeNode * TreeClass::findNextNode(TreeNode * treeNode)
{

	//右子树不为空，找到右子树中最小节点
	if( treeNode->m_pRightChild )
	{
		TreeNode * treeNodeTemp = findMinNode( treeNode->m_pRightChild); 
		return treeNodeTemp;
	}

	//右子树为空
	//找到父节点，如果该节点是父节点的左孩子，那么父节点为后继节点。
	//如果不满足，则将父节点设为该节点，继续向上找，直到满足条件或者父节点为空

	TreeNode * treeNodeTemp = treeNode->m_pParent;

	while(treeNodeTemp && treeNode != treeNodeTemp->m_pLeftChild)
	{
		treeNode = treeNodeTemp;
		treeNodeTemp = treeNodeTemp ->m_pParent;
		
	}

	return treeNodeTemp;

}

void TreeClass::eraseNode(int i)
{
	TreeNode * treeNode = findTreeNode(i);
	//deleteTreeNode(treeNode);
}

TreeNode * TreeClass::findTreeNode(int i)
{
	TreeNode *treeNode = m_pRoot;
	while(treeNode)
	{
		if(treeNode->m_nData > i)
		{
			treeNode = treeNode->m_pLeftChild;
		}
		else if(treeNode->m_nData < i)
		{
			treeNode = treeNode->m_pRightChild;
		}
		else
		{
			return treeNode;
		}
	}

	return treeNode;
}

//节点X左旋
/**************

	    x                        y
	   / \                      / \
     m   y  ===>       x    z
	      / \                / \
		 h   z             m  h
****************/
void TreeClass::leftRotate(TreeNode * x)
{
	if(x->m_pRightChild == NULL)
	{
		return;
	}

	//取X的右孩子为y
	TreeNode * y = x->m_pRightChild; 
	//判断y是否有左孩子
	if(y->m_pLeftChild)
	{
		x->m_pRightChild = y->m_pLeftChild;
		y->m_pLeftChild->m_pParent = x;
	}
	else
	{
		x->m_pRightChild = NULL;
	}

	//x的父节点赋值为y的父节点
	y->m_pParent = x->m_pParent;

	if(x->m_pParent == NULL)
	{
		//X为root节点，将y设置为root节点
		m_pRoot = y; 
	}
	else if(x == x->m_pParent->m_pLeftChild)
	{
		//X为其父节点的左孩子，将y设置为其父节点的左孩子
		x->m_pParent->m_pLeftChild = y;
	}
	else
	{
		//X为其父节点的右孩子，将y设置为其父节点的右孩子
		x->m_pParent->m_pRightChild = y;
	}
	//将X设置为y的左孩子
	y->m_pLeftChild = x;
	x->m_pParent = y;


}

/**************

		y                        x
	   / \                      / \
      x    m  ===>      z   y
	 / \                           / \
	z   h                        h   m
****************/

void TreeClass::rightRotate(TreeNode * y)
{
	TreeNode * x = y->m_pLeftChild;
	if(x == NULL)
	{
		return;
	}

	if(x->m_pRightChild)
	{
		 // 将 “y” 设为 “x的右孩子的父亲”
		x->m_pRightChild->m_pParent = y;
		// 将 “x的右孩子” 设为 “y的左孩子”
		y->m_pLeftChild = x->m_pRightChild;
	}
	else
	{
		y->m_pLeftChild = NULL;
	}

	x->m_pParent = y->m_pParent ;
	if(y->m_pParent == NULL)
	{
		 // 情况1：如果 “y的父亲” 是空节点，则将x设为根节点
		m_pRoot = x;
	}
	else if(y == y->m_pParent->m_pRightChild)
	{
		//如果 y是它父节点的右孩子，则将x设为“y的父节点的左孩子”
		y->m_pParent->m_pRightChild = x;
	}
	else
	{
		//(y是它父节点的左孩子) 将x设为“y的父节点的左孩子”
		y->m_pParent->m_pLeftChild = x;
	}

	//y设置为x的右孩子
	x->m_pRightChild = y;
	y->m_pParent = x;
	
}

void TreeClass::rbInsertNode(TreeNode * z)
{
	//定义一个节点的指针
	TreeNode * y = NULL;
	TreeNode * x = m_pRoot;
	//循环查找节点z插入的位置，指导找到叶子结点
	while(x)
	{
		y = x;
		if(z->m_nData < x->m_nData)
		{
			x = x->m_pLeftChild;
		}
		else
		{
			x = x->m_pRightChild;
		}
	}

	//循环结束时，x指向某个叶子结点，y指向x的父亲
	//设置z的父节点为y
	z->m_pParent = y;
	//如果y为NULL，设置z为root节点
	if(y == NULL)
	{
		m_pRoot = z;
	}
	else if(z->m_nData < y->m_nData)
	{
		y->m_pLeftChild = z;
	}
	else
	{
		y->m_pRightChild = z;
	}

	// z的左孩子设为空
	z->m_pLeftChild = NULL;
	 // z的右孩子设为空
	z->m_pRightChild = NULL;
	// 将z着色为“红色”
	z->m_nColor = RED;
	//通过rbInsertFixUp(z)对红黑树的节点进行颜色修改以及旋转，让树T仍然是一颗红黑树
	rbInsertFixUp(z);				
}
/*
RB-INSERT-FIXUP(T, z)
01 while color[p[z]] = RED                                                  // 若“当前节点(z)的父节点是红色”，则进行以下处理。
02     do if p[z] = left[p[p[z]]]                                           // 若“z的父节点”是“z的祖父节点的左孩子”，则进行以下处理。
03           then y ← right[p[p[z]]]                                        // 将y设置为“z的叔叔节点(z的祖父节点的右孩子)”
04                if color[y] = RED                                         // Case 1条件：叔叔是红色
05                   then color[p[z]] ← BLACK                    ▹ Case 1   //  (01) 将“父节点”设为黑色。
06                        color[y] ← BLACK                       ▹ Case 1   //  (02) 将“叔叔节点”设为黑色。
07                        color[p[p[z]]] ← RED                   ▹ Case 1   //  (03) 将“祖父节点”设为“红色”。
08                        z ← p[p[z]]                            ▹ Case 1   //  (04) 将“祖父节点”设为“当前节点”(红色节点)
09                   else if z = right[p[z]]                                // Case 2条件：叔叔是黑色，且当前节点是右孩子
10                           then z ← p[z]                       ▹ Case 2   //  (01) 将“父节点”作为“新的当前节点”。
11                                LEFT-ROTATE(T, z)              ▹ Case 2   //  (02) 以“新的当前节点”为支点进行左旋。
12                           color[p[z]] ← BLACK                 ▹ Case 3   // Case 3条件：叔叔是黑色，且当前节点是左孩子。(01) 将“父节点”设为“黑色”。
13                           color[p[p[z]]] ← RED                ▹ Case 3   //  (02) 将“祖父节点”设为“红色”。
14                           RIGHT-ROTATE(T, p[p[z]])            ▹ Case 3   //  (03) 以“祖父节点”为支点进行右旋。
15        else (same as then clause with "right" and "left" exchanged)      // 若“z的父节点”是“z的祖父节点的右孩子”，将上面的操作中“right”和“left”交换位置，然后依次执行。
16 color[root[T]] ← BLACK 
*/
//重新着色和旋转
void TreeClass::rbInsertFixUp(TreeNode * z)
{
	//z为root节点，那么只需要设置z颜色为黑色即可。
	if(z->m_pParent == NULL)
	{
		m_pRoot->m_nColor = BLACK;
		return ;
	}

	//若当前节点z的父节点为红色，需要一直调色和旋转，直到z为黑色为止
	while(z->m_pParent->m_nColor == RED)
	{
		// 若“z的父节点”是“z的祖父节点的左孩子”，则进行以下处理。
		if(z->m_pParent->m_pParent->m_pLeftChild == z->m_pParent)
		{
			// 将y设置为“z的叔叔节点(z的祖父节点的右孩子)”
			TreeNode * y = z->m_pParent->m_pParent->m_pRightChild;
			 // Case 1条件：叔叔是红色
			if(y->m_nColor == RED)
			{
				 //  (01) 将“父节点”设为黑色
				z->m_pParent->m_nColor = BLACK;
				 //  (02) 将“叔叔节点”设为黑色
				y->m_nColor = BLACK;
				// (03)将“祖父节点”设为“红色”
				z->m_pParent->m_pParent->m_nColor = RED;
				//  (04) 将“祖父节点”设为“当前节点”(红色节点)
				z = z->m_pParent->m_pParent;
			}//if(y->m_nColor == RED)
			else 
			{
				 // Case 2条件：叔叔是黑色，且当前节点是右孩子
				if(z == z->m_pParent->m_pRightChild)
				{
					//  (01) 将“父节点”作为“新的当前节点”
					z = z->m_pParent;
					//  (02) 以“新的当前节点”为支点进行左旋
					leftRotate(z);
				}
				// Case 3条件：叔叔是黑色，且当前节点是左孩子。(01) 将“父节点”设为“黑色”。
				z->m_pParent->m_nColor = BLACK;
				//  (02) 将“祖父节点”设为“红色”。
				z->m_pParent->m_pParent->m_nColor = RED;
				//  (03) 以“祖父节点”为支点进行右旋。
				rightRotate(z->m_pParent->m_pParent);
			}
		}//if(z->m_pParent->m_pParent->m_pLeftChild == z->m_pParent)
		else
		{
			// 若“z的父节点”是“z的祖父节点的右孩子”，将上面的操作中“right”和“left”交换位置，然后依次执行。
			TreeNode * y = z->m_pParent->m_pParent->m_pLeftChild;
			// Case 1条件：叔叔是红色
			if(y->m_nColor == RED)
			{
				//  (01) 将“父节点”设为黑色
				z->m_pParent->m_nColor = BLACK;
				//  (02) 将“叔叔节点”设为黑色
				y->m_nColor = BLACK;
				// (03)将“祖父节点”设为“红色”
				z->m_pParent->m_pParent->m_nColor = RED;
				//  (04) 将“祖父节点”设为“当前节点”(红色节点)
				z = z->m_pParent->m_pParent;
			}//if(y->m_nColor == RED)
			else 
			{
				// Case 2条件：叔叔是黑色，且当前节点是左孩子
				if(z == z->m_pParent->m_pLeftChild)
				{
					//  (01) 将“父节点”作为“新的当前节点”
					z = z->m_pParent;
					//  (02) 以“新的当前节点”为支点进行右旋
					rightRotate(z);
				}
				// Case 3条件：叔叔是黑色，且当前节点是右孩子。(01) 将“父节点”设为“黑色”。
				z->m_pParent->m_nColor = BLACK;
				//  (02) 将“祖父节点”设为“红色”。
				z->m_pParent->m_pParent->m_nColor = RED;
				//  (03) 以“祖父节点”为支点进行右旋。
				leftRotate(z->m_pParent->m_pParent);
			}

		}
	
	}
	//最后将root节点设置为黑色
	m_pRoot->m_nColor = BLACK;
}

/************************
RB-DELETE(T, z)
01 if left[z] = nil[T] or right[z] = nil[T]         
02    then y ← z                                  // 若“z的左孩子” 或 “z的右孩子”为空，则将“z”赋值给 “y”；
03    else y ← TREE-SUCCESSOR(z)                  // 否则，将“z的后继节点”赋值给 “y”。
04 if left[y] ≠ nil[T]
05    then x ← left[y]                            // 若“y的左孩子” 不为空，则将“y的左孩子” 赋值给 “x”；
06    else x ← right[y]                           // 否则，“y的右孩子” 赋值给 “x”。
07 p[x] ← p[y]                                    // 将“y的父节点” 设置为 “x的父节点”
08 if p[y] = nil[T]                               
09    then root[T] ← x                            // 情况1：若“y的父节点” 为空，则设置“x” 为 “根节点”。
10    else if y = left[p[y]]                    
11            then left[p[y]] ← x                 // 情况2：若“y是它父节点的左孩子”，则设置“x” 为 “y的父节点的左孩子”
12            else right[p[y]] ← x                // 情况3：若“y是它父节点的右孩子”，则设置“x” 为 “y的父节点的右孩子”
13 if y ≠ z                                    
14    then key[z] ← key[y]                        // 若“y的值” 赋值给 “z”。注意：这里只拷贝z的值给y，而没有拷贝z的颜色！！！
15         copy y's satellite data into z         
16 if color[y] = BLACK                            
17    then RB-DELETE-FIXUP(T, x)                  // 若“y为黑节点”，则调用
18 return y 
*/////////////////////

TreeNode *  TreeClass::rbDeleteNode(TreeNode * z)
{
	TreeNode * y = NULL;
	TreeNode * x = NULL;
	//z只有一个孩子或者没有孩子，那么删除z，将孩子连接到父节点即可
	if(z->m_pLeftChild == NULL || z->m_pRightChild == NULL)
	{
		 y = z;
	}
	else
	{
		//z有两个孩子，那么将z的后继节点替换z的数值，删除后继节点即可。
		y = findNextNode(z);
	}
	
	//找到节点y的子树，节点y的子树为空或者只有一支，不存在双子树情况。
	//因为如果z只有一个孩子或者没有孩子，那么y==z，如果z有两个孩子，那么y==z的后继节点，
	//z的后继节点一定只有一个孩子或者没有孩子。
	if(y->m_pLeftChild)
	{
		x = y->m_pLeftChild;
	}
	else
	{
		x = y->m_pRightChild;
	}

	if(x)
	{
		x->m_pParent = y->m_pParent;
	}

	if(y->m_pParent == NULL)
	{
		m_pRoot = x;
	}
	else if(y == y->m_pParent->m_pLeftChild)
	{
		y->m_pParent->m_pLeftChild = x;
	}
	else
	{
		y->m_pParent->m_pRightChild = x;
	}

	 if(y != z)
	 {
		 // 若“y的值” 赋值给 “z”。注意：这里只拷贝z的值给y，而没有拷贝z的颜色
		 z->m_nData = y->m_nData;
	 }
	
	 if(y->m_nColor == BLACK)
	 {
		rbDeleteFixUp(x);
	 }
	 return y;
	 
}
/********************
RB-DELETE-FIXUP(T, x)
01 while x ≠ root[T] and color[x] = BLACK  
02     do if x = left[p[x]]      
03           then w ← right[p[x]]                                             // 若 “x”是“它父节点的左孩子”，则设置 “w”为“x的叔叔”(即x为它父节点的右孩子)                                          
04                if color[w] = RED                                           // Case 1: x是“黑+黑”节点，x的兄弟节点是红色。(此时x的父节点和x的兄弟节点的子节点都是黑节点)。
05                   then color[w] ← BLACK                        ▹  Case 1   //   (01) 将x的兄弟节点设为“黑色”。
06                        color[p[x]] ← RED                       ▹  Case 1   //   (02) 将x的父节点设为“红色”。
07                        LEFT-ROTATE(T, p[x])                    ▹  Case 1   //   (03) 对x的父节点进行左旋。
08                        w ← right[p[x]]                         ▹  Case 1   //   (04) 左旋后，重新设置x的兄弟节点。
09                if color[left[w]] = BLACK and color[right[w]] = BLACK       // Case 2: x是“黑+黑”节点，x的兄弟节点是黑色，x的兄弟节点的两个孩子都是黑色。
10                   then color[w] ← RED                          ▹  Case 2   //   (01) 将x的兄弟节点设为“红色”。
11                        x ←  p[x]                               ▹  Case 2   //   (02) 设置“x的父节点”为“新的x节点”。
12                   else if color[right[w]] = BLACK                          // Case 3: x是“黑+黑”节点，x的兄弟节点是黑色；x的兄弟节点的左孩子是红色，右孩子是黑色的。
13                           then color[left[w]] ← BLACK          ▹  Case 3   //   (01) 将x兄弟节点的左孩子设为“黑色”。
14                                color[w] ← RED                  ▹  Case 3   //   (02) 将x兄弟节点设为“红色”。
15                                RIGHT-ROTATE(T, w)              ▹  Case 3   //   (03) 对x的兄弟节点进行右旋。
16                                w ← right[p[x]]                 ▹  Case 3   //   (04) 右旋后，重新设置x的兄弟节点。
17                         color[w] ← color[p[x]]                 ▹  Case 4   // Case 4: x是“黑+黑”节点，x的兄弟节点是黑色；x的兄弟节点的右孩子是红色的。(01) 将x父节点颜色 赋值给 x的兄弟节点。
18                         color[p[x]] ← BLACK                    ▹  Case 4   //   (02) 将x父节点设为“黑色”。
19                         color[right[w]] ← BLACK                ▹  Case 4   //   (03) 将x兄弟节点的右子节设为“黑色”。
20                         LEFT-ROTATE(T, p[x])                   ▹  Case 4   //   (04) 对x的父节点进行左旋。
21                         x ← root[T]                            ▹  Case 4   //   (05) 设置“x”为“根节点”。
22        else (same as then clause with "right" and "left" exchanged)        // 若 “x”是“它父节点的右孩子”，将上面的操作中“right”和“left”交换位置，然后依次执行。
23 color[x] ← BLACK   
************/
void TreeClass::rbDeleteFixUp(TreeNode * x)
{
	while(x != m_pRoot && x->m_nColor == BLACK)
	{
		if(x->m_pParent->m_pLeftChild == x)
		{
			TreeNode * w = x->m_pParent->m_pRightChild;
			// Case 1: x是黑节点，x的兄弟节点是红色。
			if(w->m_nColor == RED)
			{
				//   (01) 将x的兄弟节点设为“黑色”。
				w->m_nColor = BLACK;
				//   (02) 将x的父节点设为“红色”。
				x->m_pParent->m_nColor = RED;
				//   (03) 对x的父节点进行左旋。
				leftRotate(x->m_pParent);
				//   (04) 左旋后，重新设置x的兄弟节点。
				w = x->m_pParent->m_pRightChild;
			}
			
			// Case 2: x是黑节点，x的兄弟节点是黑色，x的兄弟节点的两个孩子都是黑色。
			if(w->m_pLeftChild->m_nColor == BLACK && w->m_pRightChild->m_nColor == BLACK)
			{
				 //   (01) 将x的兄弟节点设为“红色”
				w->m_nColor = RED;
				//   (02) 设置“x的父节点”为“新的x节点”。
				x = x->m_pParent;
			}
			else 
			{
				 // Case 3: x是黑节点，x的兄弟节点是黑色；x的兄弟节点的左孩子是红色，右孩子是黑色的
				if(w->m_pRightChild->m_nColor == BLACK)
				{
					//   (01) 将x兄弟节点的左孩子设为“黑色”
					w->m_pLeftChild->m_nColor = BLACK;
					//   (02) 将x兄弟节点设为“红色”
					w->m_nColor = RED;
					//   (03) 对x的兄弟节点进行右旋
					rightRotate(w);
					 //   (04) 右旋后，重新设置x的兄弟节点。
					w = x->m_pParent->m_pRightChild;
				}

				// Case 4: x是黑节点，x的兄弟节点是黑色；x的兄弟节点的右孩子是红色的。
				//(01) 将x父节点颜色 赋值给 x的兄弟节点。
				w->m_nColor = x->m_pParent->m_nColor;
				 //   (02) 将x父节点设为“黑色”
				x->m_pParent->m_nColor = BLACK;
				 //   (03) 将x兄弟节点的右子节设为“黑色”。
				x->m_pRightChild->m_nColor = BLACK;
				//  (04) 对x的父节点进行左旋。
				leftRotate(x->m_pParent);
				x = m_pRoot;
					
			}

		}//if(x->m_pParent->m_pLeftChild == x)
		else
		{
			// 若 “x”是“它父节点的右孩子”，将上面的操作中“right”和“left”交换位置，然后依次执行
			TreeNode * w = x->m_pParent->m_pLeftChild;
			// Case 1: x是黑节点，x的兄弟节点是红色。
			if(w->m_nColor == RED)
			{
				//   (01) 将x的兄弟节点设为“黑色”。
				w->m_nColor = BLACK;
				//   (02) 将x的父节点设为“红色”。
				x->m_pParent->m_nColor = RED;
				//   (03) 对x的父节点进行右旋。
				rightRotate(x->m_pParent);
				//   (04) 右旋后，重新设置x的兄弟节点。
				w = x->m_pParent->m_pLeftChild;
			}

			// Case 2: x是黑节点，x的兄弟节点是黑色，x的兄弟节点的两个孩子都是黑色。
			if(w->m_pLeftChild->m_nColor == BLACK && w->m_pRightChild->m_nColor == BLACK)
			{
				//   (01) 将x的兄弟节点设为“红色”
				w->m_nColor = RED;
				//   (02) 设置“x的父节点”为“新的x节点”。
				x = x->m_pParent;
			}
			else 
			{
				// Case 3: x是黑节点，x的兄弟节点是黑色；x的兄弟节点的左孩子是黑色，右孩子是红色的
				if(w->m_pLeftChild->m_nColor == BLACK)
				{
					//   (01) 将x兄弟节点的右孩子设为“黑色”
					w->m_pRightChild->m_nColor = BLACK;
					//   (02) 将x兄弟节点设为“红色”
					w->m_nColor = RED;
					//   (03) 对x的兄弟节点进行左旋
					leftRotate(w);
					//   (04) 左旋后，重新设置x的兄弟节点。
					w = x->m_pParent->m_pLeftChild;
				}

				// Case 4: x是黑节点，x的兄弟节点是黑色；x的兄弟节点的左孩子是红色的。
				//(01) 将x父节点颜色 赋值给 x的兄弟节点。
				w->m_nColor = x->m_pParent->m_nColor;
				//   (02) 将x父节点设为“黑色”
				x->m_pParent->m_nColor = BLACK;
				//   (03) 将x兄弟节点的左子节设为“黑色”。
				x->m_pLeftChild->m_nColor = BLACK;
				//  (04) 对x的父节点进行右旋。
				rightRotate(x->m_pParent);
				x = m_pRoot;

			}
		} //else
	}

	x->m_nColor = BLACK;
}
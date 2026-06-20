#include<stdio.h>
#include<stdlib.h>
typedef struct SortTree {
	int data;//存放数据的数据域
	struct SortTree* left;//指针域 左指针
	struct SortTree* right;//指针域 右指针
}Node;
/*全局变量*/
Node* root;//根节点

void Init(int);//初始化操作
void insert(int);//插入操作
void show(Node*);
int delete_node(Node*, int);
Node* prev_node(Node*, Node*, int);
bool search(Node* root, int key);
int main()
{
	Init(8);
	insert(4);
	insert(2);
	insert(5);
	insert(10);
	insert(9);
	insert(13);
	show(root);
	delete_node(root, 8);
	delete_node(root, 13);
	printf("\n");
	show(root);
}

/*初始化根节点
int key : 根节点的值
*/
void Init(int key)
{
	root = (Node*)malloc(sizeof(Node));
	root->data = key;
	root->left = NULL;
	root->right = NULL;
}

void insert(int key)
{
	//定义一个临时指针 用于移动
	Node* temp = root;//方便移动 以及 跳出循环
	Node* prev = NULL;//定位到待插入位置的前一个结点
	while (temp != NULL)
	{
		prev = temp;
		if (key < temp->data)
		{
			temp = temp->left;
		}
		else if (key > temp->data)
		{
			temp = temp->right;
		}
		else
		{
			return;
		}
	}

	if (key < prev->data)
	{
		prev->left = (Node*)malloc(sizeof(Node));
		prev->left->data = key;
		prev->left->left = NULL;
		prev->left->right = NULL;
	}
	else
	{
		prev->right = (Node*)malloc(sizeof(Node));
		prev->right->data = key;
		prev->right->left = NULL;
		prev->right->right = NULL;
	}
}

void show(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	show(root->left);
	printf("%d ", root->data);
	show(root->right);
}
/*查找元素key*/
bool search(Node* root, int key)
{
	while (root != NULL)
	{
		if (key == root->data)
			return true;
		else if (key < root->data)
			root = root->left;
		else
			root = root->right;
	}
	return false;
}
int delete_node(Node* node, int key)
{
	if (node == NULL)
	{
		return -1;
	}
	else
	{
		if (node->data == key)
		{
			//当我执行删除操作 需要先定位到前一个结点
			Node* tempNode = prev_node(root, node, key);
			Node* temp = NULL;
			/*
			如果右子树为空 只需要重新连接结点
			叶子的情况也包含进去了 直接删除
			*/
			if (node->right == NULL)
			{
				temp = node;
				node = node->left;
				/*为了判断 待删除结点是前一个结点的左边还是右边*/
				if (tempNode->left->data == temp->data)
				{
					Node* free_node = temp;//释放用的指针
					tempNode->left = node;
					free(free_node);
					free_node = NULL;
				}
				else
				{
					Node* free_node = temp;//释放用的指针
					tempNode->right = node;
					free(free_node);
					free_node = NULL;
				}
			}
			else if (node->left == NULL)
			{
				temp = node;
				node = node->right;
				if (tempNode->left->data == temp->data)
				{
					Node* free_node = temp;//释放用的指针
					tempNode->left = node;
					free(free_node);
					free_node = NULL;
				}
				else
				{
					Node* free_node = temp;//释放用的指针
					tempNode->right = node;
					free(free_node);
					free_node = NULL;
				}
			}
			else//左右子树都不为空
			{
				temp = node;
				/*往左子树 找最大值*/
				Node* left_max = node;//找最大值的临时指针
				left_max = left_max->left;//先到左孩子结点
				while (left_max->right != NULL)
				{
					temp = left_max;
					left_max = left_max->right;
				}
				node->data = left_max->data;
				if (temp != node)
				{
					temp->right = left_max->left;
					free(left_max);
					left_max = NULL;
				}
				else
				{
					temp->left = left_max->left;
					free(left_max);
					left_max = NULL;
				}
			}

		}
		else if (key < node->data)
		{
			delete_node(node->left, key);
		}
		else if (key > node->data)
		{
			delete_node(node->right, key);
		}
	}
}
/*定位到待删除节点的前一个结点
Node* root 从根节点开始
Node* node 待删除的结点
int key 待删除数据
*/
Node* prev_node(Node* root, Node* node, int key)
{
	if (root == NULL || node == root)
	{
		return node;
	}
	else
	{
		if (root->left != NULL && root->left->data == key)
		{
			return root;
		}
		else if (root->right != NULL && root->right->data == key)
		{
			return root;
		}
		else if (key < root->data)
		{
			return prev_node(root->left, node, key);
		}
		else
		{
			return prev_node(root->right, node, key);
		}
	}
}
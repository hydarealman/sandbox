#include<vector>
#include<stack>
#include<iostream>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0),left(nullptr),right(nullptr){}
	TreeNode(int val) : val(val),left(nullptr),right(nullptr){}
	TreeNode(int val,TreeNode* left,TreeNode right) : val(val),left(nullptr),right(nullptr){}
};
//class solution {
//public:
//	vector<int> preorderTraversal(TreeNode* root) {
//		stack<TreeNode*> st;
//		vector<int> result;
//		if (root == NULL) return result;
//		while (!st.empty() ){
//			TreeNode* node = st.top();
//			st.pop();
//			result.push_back(node->val);
//			if (node->right) st.push(node->right);
//			if (node->left) st.push(node->left);
//		}
//		return result;
//	}
//	
//	
//}; 
//int main() {
//
//	
//}


//class solution {
// public:
//	vector<int> inorderrTraversal(TreeNode* root) {
//		vector<int> result;
//		stack<TreeNode*> st;
//		if (root != NULL) st.push(root);
//		while (!st.empty()) {
//			TreeNode* node = st.top();
//			if (node != NULL) {
//				st.pop();
//				if (node->right) st.push(node->right);
//
//				st.push(node);
//				st.push(NULL);
//
//				if (node->left) st.push(node->left);
//			}
//			else {
//				st.pop();
//				node = st.top();
//				st.pop();
//				result.push_back(node->val);
//			}
//		}
//		return result;
//	}
//};
//int main() {
//
//}

//class solution {
//public:
//	vector<int> preorderTraversal(TreeNode* root) {
//		vector<int> result;
//		stack<TreeNode*> st;
//		if (root != NULL) st.push(root);
//		while (!st.empty()) {
//			TreeNode* node = st.top();
//			if (node != NULL) {
//				st.pop();
//				if (node->right) st.push(node->right);
//				if (node->left) st.push(node->left);
//				st.push(node);
//				st.push(NULL);
//			}
//			else {
//				st.pop();
//				node = st.top();
//				st.pop();
//				result.push_back(node->val);
//			}
//		}
//		return result;
//	}
//};
//int main() {
//
//}

class Solution {
public:
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> result;
		stack<TreeNode*> st;
		if (root != NULL) st.push(root);
		while (!st.empty()) {
			TreeNode* node = st.top();
			if (node != NULL) {
				st.pop();
				st.push(node);
				st.push(NULL); 
			}
		}
	}
	

};
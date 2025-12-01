// g++ -o main main.cpp
#include <iostream>
#include <set>
#include <vector>
#include <queue>
using namespace std;

class TreeNode{
    public:
    int val;
    set<TreeNode*> children;
    TreeNode(int v) : val(v) {}
};

void modify(TreeNode* root, TreeNode* parent, vector<int> &value){
    vector<TreeNode*> toDelete;

    for(auto child : root->children){
        modify(child, root, value);
        if(child->children.size() == 0 && value[child->val] == -1) {
            toDelete.push_back(child);
        }
    }
    for(auto node : toDelete){
        root->children.erase(node);
    }
}

TreeNode* solution(TreeNode* root, vector<int>& val){
    modify(root, NULL, val);
    if(root->children.size() == 0 && val[root->val] == -1) return NULL;
    return root;
}

void printTreeNode(TreeNode* root){
    if(!root) return;
    queue<TreeNode*> q;
    q.push(root);
    cout << root->val << endl;
    while(!q.empty()){
        int sz = q.size();
        for(int i=0; i<sz; i++){
            auto it = q.front();
            q.pop();
            for(auto child : it->children){
                q.push(child);
                cout << child->val << " ";
            }
        }
        cout << endl;
    }
    return;
}

int main(){
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(4);
    TreeNode* node5 = new TreeNode(5);
    TreeNode* node6 = new TreeNode(6);
    node1->children = {node2, node3};
    node2->children = {node4, node5};
    vector<int> values = {0, -1, -1, -1, -1, -1, -1};
    TreeNode* modifyedNode = solution(node1, values);
    printTreeNode(node1);
    cout << endl;
    cout << (node1->val) << endl;
    cout << endl;
    return 0;
}

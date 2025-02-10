#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};
Node*BinaryTree(){
    int root;
    cin>>root;
    if(root==-1){
        return NULL;
    }
    Node*temp=new Node(root);
    cout<<"left child "<< root<<" :";
    temp->left=BinaryTree(); //lest child
    cout<<"right child "<< root<<" :";
    temp->right=BinaryTree(); //right child
    return temp;
}
void inorder(Node* root){
    if (root ==NULL)
    return ;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
void preorder(Node* root){
    if (root==NULL) 
    return ;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}
void postorder(Node* root){
    if (root==NULL) 
    return ;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}
vector<int> levelorder(Node*root){
    queue<Node*>q;
    q.push(root);
    vector<int>ans;
    Node*temp;
    while (!q.empty())
    {
        temp=q.front();
        q.pop();
        ans.push_back(temp->data);
        if(temp->left)
        q.push(temp->left);
        if(temp->right)
        q.push(temp->right);
    }
    return ans;
}
class tree{
    public:
    tree* root1;
    tree(){
        root1= NULL;
    }
    Node* treeclone(Node* root1){
        if(root1==NULL){
            return 0;
        }
        Node*newnode=new Node(root1->data);
        newnode->left=treeclone(root1->left);
        newnode->right=treeclone(root1->right);
        return newnode;
    }
    void printtree(Node* root1){
        preorder(root1);
    }
    int height(Node* root) {
        if (root == NULL) {
            return 0; // height of empty tree is 0
        }
        // Calculate the height of left and right subtrees and return the maximum
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        return max(leftHeight, rightHeight) + 1;
    }
    
};


int main() {
    cout<<"Enter the root value: ";
    Node* root=BinaryTree();
    tree t;
    Node* clonedRoot = t.treeclone(root);
    int choice;
    while (true) {
        cout << "1. Inorder\n2. Preorder\n3. Postorder\n4. Levelorder\n5. Tree clone\n6. Height of tree\n7.Exit\n";
        cout << "Enter your choice : ";
        cin >> choice;

        while(true) {
        if(choice==1){
            cout << "\nInorder: ";
            inorder(root);
            cout << endl;
            break;
        }
        else if(choice==2){
            cout << "\nPreorder: ";
            preorder(root);
            cout << endl;
            break;
        }
        else if(choice==3){
            cout << "\nPostorder: ";
            postorder(root);
            cout << endl;
            break;
        }
        else if(choice==4){
            cout << "\nLevelorder: ";
            vector<int> ans = levelorder(root);
            for (auto a : ans) {
                cout << a << " ";
            }
            cout << endl;
            break;
        }
        else if(choice==5){
            cout << "\nTree clone (Preorder of cloned tree): ";
            t.printtree(clonedRoot);
            cout<<endl;
            break;
        }
        else if (choice == 6) {
                int treeHeight = t.height(root);
                cout << "\nHeight of the tree: " << treeHeight << endl;
                break;
        }
        else if(choice==7){
            cout << "Exiting program." << endl;
            return 0; 
            break;
        }
        else{
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
    }
    return 0;
}
#include <iostream>
using namespace std;

class Node{
public:
    int data;
    Node* parent;
    Node* left;
    Node* right;
    Node(int e){
        this->data = e;
        this->parent = NULL;
        this->left = NULL;
        this->right = NULL;
    }
    void insertleft(Node* n){
        n->parent = this;
        this->left = n;
    }
    void insertright(Node* n){
        n->parent = this;
        this->right = n;
    }
};
class BST{
private:
    Node* root;
    int height;
public:
    BST(){
        this->root = NULL;
        this->height = 0;
    }
    ~BST(){
        treeDestructor(root);
    }
    Node* findNode(int e){
        Node* cur = root;
        while(cur != NULL){
            if(cur->data > e){
                cur = cur->left;
            }
            else if(cur->data < e){
                cur = cur->right;
            }
            else if(cur->data == e){
                return cur;
            }
        }
        return NULL;
    }
    void insert(int e){
        Node* cur = root;
        Node* child = new Node(e);
        Node* p = NULL;
        int depth = 0;
        if(cur == NULL){
            root = child;
        }
        else{
            while(cur != NULL){
                p = cur;
                if(cur->data > e){
                    cur = cur->left;
                }
                else if(cur->data <= e){
                    cur = cur->right;
                }
                depth ++;
            }
            if(p->data > e){
                p->insertleft(child);
            }
            else{
                p->insertright(child);
            }
            if(depth > height){
                height = depth;
            }
        }
    }
    void deleteNode(int e){
        Node* cur = findNode(e);
        if(cur->left == NULL){
            transplant(cur, cur->right);
        }
        else if(cur->right == NULL){
            transplant(cur, cur->left);
        }
        else{
            Node* last = findminimum(cur->right);
            if(last->parent != cur){
                transplant(last, last->right);
                last->right = cur->right;
                last->right->parent = last;
            }
            transplant(cur, last);
            last->left = cur->left;
            last->left->parent = last;
        }
        delete cur;
    }
    void transplant(Node* par, Node* chi){
        if(par->parent == NULL){
            root = chi;
        }
        else if(par == par->parent->left){
            par->parent->left = chi;
        }
        else{
            par->parent->right = chi;
        }
        if(chi != NULL){
            chi->parent = par->parent;
        }
    }
    Node* findminimum(Node* n){ // 후임자 successor 탐색
        Node* cur = n;
        if(cur != NULL){
            while(cur->left != NULL){
                cur = cur->left;
            }
            return cur;
        }
        return NULL;
    }
    void printheight(){
        cout << this->height << endl;
    }
    void print(){
        preorder(this->root);
    }
    void preorder(Node* n){
        Node* cur = n;
        if(cur == NULL){
            cout << '0' << endl;
        }
        else{
            cout << cur->data << ' ';
            if(cur->left != NULL){
                preorder(cur->left);
            }
            if(cur->right != NULL){
                preorder(cur->right);
            }
        }
    }

    void treeDestructor(Node* n){
        if(n->left != NULL){
            treeDestructor(n->left);
        }
        if(n->right != NULL){
            treeDestructor(n->right);
        }
        delete (n);
    }
};
int main(){
    int m, x;
    cin >> m;
    while(m--){
        BST b;
        int n;
        cin >> n;
        for(int i = 0; i<n; i++){
            cin >> x;
            b.insert(x);
        }
        int k;
        cin >> k;
        for(int i = 0; i < k; i++){
            cin >> x;
            b.deleteNode(x);
        }
        b.print();
        cout << endl;
    }
    return 0;
}
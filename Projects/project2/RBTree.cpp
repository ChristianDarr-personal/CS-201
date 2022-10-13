#include <iostream>
using namespace std;

template <class keytype, class valuetype>
class node{
    public:
        keytype key;
        valuetype value;
        bool color; // red = true, black = false
        node *parent;
        node *left;
        node *right;
        node(){
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            color = false;
            key = (keytype) 0;
            value = (valuetype) 0;
        }
        node(keytype k, valuetype v){
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            color = false;
            key = k;
            value = v;
        }
};

template <class keytype, class valuetype>
class RBTree{
    private:
        node<keytype, valuetype> *head;
        node<keytype, valuetype> *nullNode;

        void fixup(node* n){
            while(n->parent.color){ // while color == true(red)
                if(n->parent == n->parent->parent->left){
                    y = n->parent->parent->right;
                    if(y.color){ // if color == true(red)
                        n->parent.color = false;
                        y.color = false;
                        n->parent->parent.color = true;
                        n = n->parent->parent;
                    } else if(n == n->parent->right){
                        n = n->parent;
                        leftRotate(n);
                    } else{
                        n->parent.color = false;
                        n->parent>parent.color = true;
                        rightRotate(n->parent->parent);
                    }
                } else{
                    y = n->parent->parent->left;
                    if(y.color){ // if color == true(red)
                        n->parent.color = false;
                        y.color = false;
                        n->parent->parent.color = true;
                        n = n->parent->parent;
                    } else if(n == n->parent->left){
                        n = n->parent;
                        rightRotate(n);
                    } else{
                        n->parent.color = false;
                        n->parent>parent.color = true;
                        leftRotate(n->parent->parent);
                    }
                }
            }
        }

        void leftRotate(node* n){
            y = n->right;
            n->right = y->left;
            if(y->left != nullNode){
                y->left->parent = n;
            }
            y->parent = n->parent;
            if(n->parent == nullNode){
                head = y;
            } else if(n == n->parent->left){
                n->parent->left = y;
            } else {
                n->parent->right = y;
            }
            y->left = n;
            n->parent = y;
        }

        void rightRotate(node* n){
            y = n->left;
            n->left = y->right;
            if(y->right != nullNode){
                y->right->parent = n;
            }
            y->parent = n->parent;
            if(n->parent == nullNode){
                head = y;
            } else if(n == n->parent->right){
                n->parent->right = y;
            } else {
                n->parent->left = y;
            }
            y->right = n;
            n->parent = y;
        }

    public:
        RBTree(){}

        RBTree(keytype k[], valuetype v[], int s){
            nullNode = new node<keytype, valuetype>();
            head = nullNode;
            for(int i = 0; i < s; i ++){
                insert(k[i], v[i])
            }
        }

        // Traditional search. Should return a pointer to the valuetype stored with the key. If the key is not 
        // stored in the tree then the function should return NULL.
        valuetype* search(keytype k){

        }

        //Inserts the node with key k and value v into the tree.
        void insert(keytype k, valuetype v){
            n = new node<keytype, valuetype>(k, v);
            y = nullNode;
            x = head;
            while(x != nullNode){
                y = x;
                if(n.key < x.key){
                    x = x->left;
                } else {
                    x = x->right;
                }
            }
            n->parent = y;
            if(y == nullNode){
                head = n;
            } else if(n.key < y.key){
                y->left = n;
            } else {
                y->right = n;
            }
            n->left = nullnode;
            n->rigth = nullnode;
            n.color = true;
            fixup()
        }

        // Removes the node with key k and returns 1. If key k is not found then remove should return 0. If 
        // the node with key k is not a leaf then replace k by its predecessor.
        int remove(keytype k){
            
        }

        // Returns the rank of the key k in the tree. Returns 
        // 0 if the key k is not found. The smallest item in the tree is rank 1
        int rank(keytype k){

        }

        // Order Statistics. Returns the key of the node at position pos in the tree. Calling with pos = 1 
        // should return the smallest key in the tree, pos = n should return the largest.
        keytype select(int pos){

        }

        // Returns a pointer to the key after k in the tree. 
        // Should return NULL if no successor exists
        keytype* successor(keytype k){

        }

        // Returns a pointer to the key before k in the tree. 
        // Should return NULL if no predecessor exists
        keytype* predeccessor(keytype k){
            
        }

        // Returns the number of node in the tree
        int size(){

        }

        // Prints the keys of the tree in a preorder traversal.
        // The list of keys are separated by a single space and terminated with a newline
        void preorder(){

        }

        // Prints the keys of the tree in an inorder traversal.
        // The list of keys are separated by a single space and terminated with a newline.
        void inorder(){

        }
        // Prints the keys of the tree in a postorder 
        // traversal. The list of keys are separated by a single space and terminated with a newline.
        void postorder(){

        }


        // Prints the smallest k keys in the tree. The list of 
        // keys are separated by a single space and terminated with a newline
        void printk(int k){

        }

};
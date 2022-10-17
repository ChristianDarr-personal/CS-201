#include <iostream>
using namespace std;

template <class keytype, class valuetype>
struct node;

template <class keytype, class valuetype>
class RBTree{
    private:
        struct node{
            keytype key;
            valuetype value;
            bool color; // red = true, black = false
            node *parent;
            node *left;
            node *right;
        };

        node *head;
        node *nullNode;

        void fixup(node *n){
            node *y;
            while(n->parent->color){ // while color == true(red)
                if(n->parent == n->parent->parent->left){
                    y = n->parent->parent->right;
                    if(y->color){ // if color == true(red)
                        n->parent->color = false;
                        y->color = false;
                        n->parent->parent->color = true;
                        n = n->parent->parent;
                    } else if(n == n->parent->right){
                        n = n->parent;
                        leftRotate(n);
                    } else{
                        n->parent->color = false;
                        n->parent->parent->color = true;
                        rightRotate(n->parent->parent);
                    }
                } else{
                    y = n->parent->parent->left;
                    if(y->color){ // if color == true(red)
                        n->parent->color = false;
                        y->color = false;
                        n->parent->parent->color = true;
                        n = n->parent->parent;
                    } else if(n == n->parent->left){
                        n = n->parent;
                        rightRotate(n);
                    } else{
                        n->parent->color = false;
                        n->parent->parent->color = true;
                        leftRotate(n->parent->parent);
                    }
                }
            }
            head->color = false;
        }

        void leftRotate(node *n){
            node *y = n->right;
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

        void rightRotate(node *n){
            node *y = n->left;
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

        void printInorder(node *n){
            if(n == nullNode){
                return;
            }
            printInorder(n->left);
            cout << n->key << " ";   
            printInorder(n->right);
        }

        void printInorderk(node *n, int k){
            if(n == nullNode){
                return;
            }
            
            printInorder(n->left);
            cout << n->key << " ";
            if(k = 1 ){
                return;
            }   
            printInorder(n->right);
        }

        void printPreorder(node *n){
            if(n == nullNode){
                return;
            }
            cout << n->key << " "; 
            printPreorder(n->left);
            printPreorder(n->right);
            cout << endl;    
        }

        void printPostorder(node *n){
            if(n == nullNode){
                return;
            }
            
            printPostorder(n->left);
            printPostorder(n->right);
            cout << n->key << " "; 
        }

    public:
        
        
        RBTree(){}

        RBTree(keytype k[], valuetype v[], int s){
            nullNode = new node();
            nullNode->key = (keytype) 0;
            nullNode->value = (valuetype) 0;
            nullNode->color = false;
            nullNode->parent = nullNode;
            nullNode->left = nullNode;
            nullNode->right = nullNode;

            head = new node();
            head->key = k[0];
            head->value = v[0];
            head->color = false;
            head->parent = nullNode;
            head->left = nullNode;
            head->right = nullNode;

            for(int i = 1; i < s; i++){
                insert(k[i], v[i]);
                postorder();
            }
            int a = 10;
        }

        // Traditional search-> Should return a pointer to the valuetype stored with the key-> If the key is not 
        // stored in the tree then the function should return NULL->
        valuetype* search(keytype k){
            node *searchNode = head;
            while(searchNode->key != k){
                if(searchNode->key < k){
                    searchNode = searchNode->left;
                } else{
                    searchNode = searchNode->right;
                }
                if(searchNode->key == k){
                    return *searchNode->value;
                }
            }
            return NULL;
        }

        //Inserts the node with key k and value v into the tree->
        void insert(keytype k, valuetype v){
                  node *n = new node();
            n->key = k;
            n->value = v;
            n->color = true;
            n->parent = nullNode;
            n->left = nullNode;
            n->right = nullNode;
            node* y = nullNode;
            node* x = head;
            while(x != nullNode){
                y = x;
                if(n->key < x->key){
                    x = x->left;
                } else {
                    x = x->right;
                }
            }
            n->parent = y;
            if(y == nullNode){
                head = n;
            } else if(n->key < y->key){
                y->left = n;
            } else {
                y->right = n;
            }
            n->left = nullNode;
            n->right = nullNode;
            n->color = true;
            fixup(n);
        }

        // Removes the node with key k and returns 1-> If key k is not found then remove should return 0-> If 
        // the node with key k is not a leaf then replace k by its predecessor->
        int remove(keytype k){
            return 0;
        }

        // Returns the rank of the key k in the tree-> Returns 
        // 0 if the key k is not found-> The smallest item in the tree is rank 1
        int rank(keytype k){
            return 0;
        }

        // Order Statistics-> Returns the key of the node at position pos in the tree-> Calling with pos = 1 
        // should return the smallest key in the tree, pos = n should return the largest->
        keytype select(int pos){
        }

        // Returns a pointer to the key after k in the tree-> 
        // Should return NULL if no successor exists
        keytype* successor(keytype k){

        }

        // Returns a pointer to the key before k in the tree-> 
        // Should return NULL if no predecessor exists
        keytype* predeccessor(keytype k){
            
        }

        // Returns the number of node in the tree
        int size(){
            return size;
        }

        // Prints the keys of the tree in a preorder traversal->
        // The list of keys are separated by a single space and terminated with a newline
        void preorder(){
            printPreorder(head);
            cout << endl;
        }

        // Prints the keys of the tree in an inorder traversal->
        // The list of keys are separated by a single space and terminated with a newline->
        void inorder(){
            printInorder(head);
            cout << endl;
        }
        // Prints the keys of the tree in a postorder 
        // traversal-> The list of keys are separated by a single space and terminated with a newline->
        void postorder(){
            printPostorder(head);
            cout << endl;
        }


        // Prints the smallest k keys in the tree-> The list of 
        // keys are separated by a single space and terminated with a newline
        void printk(int k){
            printInorderk(head, k);
            cout << endl;
        }

};
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
            int size;
        };

        node *head;
        node *nullNode;
        int treeSize;

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

        void deleteFixup(node *n){
            node *w;
            while(n != head && n->color == false){
                if(n == n->parent->left){
                    w = n->parent->right;
                    if(w->color){
                        w->color = false;
                        n->parent->color = true;
                        leftRotate(n->parent);
                        w = n->parent->right;
                    }
                    if(w->left->color == false && w->right->color == false){
                        w->color = true;
                        n = n->parent;
                    } else if(w->right->color == false){
                        w->left->color = false;
                        w->color = true;
                        rightRotate(w);
                        w = n->parent->right;
                    } else{
                        w->color = n->parent->color;
                        n->parent->color = false;
                        w->right->color = false;
                        leftRotate(n->parent);
                        n = head;
                    }
                } else{
                    w = n->parent->left;
                    if(w->color){
                        w->color = false;
                        n->parent->color = true;
                        rightRotate(n->parent);
                        w = n->parent->left;
                    }
                    if(w->right->color == false && w->left->color == false){
                        w->color = true;
                        n = n->parent;
                    } else if(w->left->color == false){
                        w->right->color = false;
                        w->color = true;
                        leftRotate(w);
                        w = n->parent->left;
                    } else{
                        w->color = n->parent->color;
                        n->parent->color = false;
                        w->left->color = false;
                        rightRotate(n->parent);
                        n = head;
                    }
                }
            }
            n->color = false;
        }

        node* treeMin(node* n){
            while(n->left != nullNode){
                n = n->left;
            }
            return n;
        }

        node* treeMax(node* n){
            while(n->right != nullNode){
                n = n->right;
            }
            return n;
        }

        void deleteNode(node* n){
            node *y, *x, *orig;
            orig = n;
            y = n;
            bool yOrigColor = y->color;
            if(n->left == nullNode){
                x = n->right;
                transplant(n, n->right);
            } else if(n->right == nullNode){
                x = n->left;
                transplant(n, n->left);
            } else {
                y = treeMax(n->left);
                yOrigColor = y->color;
                x = y->left;
                if(y->parent == n){
                    x->parent = y;
                } else {
                    transplant(y, y->left);
                    y->left = n->left;
                    y->left->parent = y;
                }
                transplant(n, y);
                y->right = n->right;
                y->left->parent = y;
                y->color = n->color;
            }
            while(orig != nullNode){
                orig->size = orig->size -1;
                orig = orig->parent;
            }
            y->size = y->left->size + y->right->size +1;
            if(yOrigColor == false){
                deleteFixup(x);
            }
            int z = 0;
        }

        void transplant(node *u, node *v){
            if(u->parent == nullNode){
                head = v;
            } else if(u == u->parent->left){
                u->parent->left = v;
            } else{
                u->parent->right = v;
            }
            v->parent = u->parent;
        }

        node* searchNode(keytype k){
            node *n = head;
            while(n->key != k && n != nullNode){
                if(n->key > k){
                    n = n->left;
                }else{
                    n = n->right;
                }
            }
            return n;
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
            y->size = n->size;
            n->size = n->left->size + n->right->size + 1;
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
            y->size = n->size;
            n->size = n->left->size + n->right->size + 1;
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
        }

        void printPostorder(node *n){
            if(n == nullNode){
                return;
            }
            
            printPostorder(n->left);
            printPostorder(n->right);
            cout << n->key << " "; 
        }

        node* selectRecurse(node* n, int i){
            int r = n->left->size + 1;
            if(i == r){
                return n;
            } else if(i < r){
                return selectRecurse(n->left, i);
            } else {
                return selectRecurse(n->right, i - r);
            }
        }

    public: 
        RBTree(){
            nullNode = new node();
            nullNode->color = false;
            nullNode->parent = nullNode;
            nullNode->left = nullNode;
            nullNode->right = nullNode;
            nullNode->size = 0;

            head = nullNode;

            treeSize = 0;
        }

        RBTree(keytype k[], valuetype v[], int s){
            nullNode = new node();
            nullNode->color = false;
            nullNode->parent = nullNode;
            nullNode->left = nullNode;
            nullNode->right = nullNode;
            nullNode->size = 0;

            head = new node();
            head->key = k[0];
            head->value = v[0];
            head->color = false;
            head->parent = nullNode;
            head->left = nullNode;
            head->right = nullNode;
            head->size = 1;
            
            treeSize = 1;
            for(int i = 1; i < s; i++){
                insert(k[i], v[i]);
            }
        }

        // Traditional search-> Should return a pointer to the valuetype stored with the key-> If the key is not 
        // stored in the tree then the function should return NULL->
        valuetype* search(keytype k){
            node *n = head;
            while(n->key != k && n != nullNode){
                if(n->key > k){
                    n = n->left;
                }else{
                    n = n->right;
                }
            }
            return &n->value;
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
            n->size = 1;
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
            treeSize++;
        }

        // Removes the node with key k and returns 1-> If key k is not found then remove should return 0-> If 
        // the node with key k is not a leaf then replace k by its predecessor->
        int remove(keytype k){
            node *n = searchNode(k);
            if(n == nullNode){
                return 0;
            } else {
                deleteNode(n);
                return 1;
            }
            treeSize--;
        }

        // Returns the rank of the key k in the tree-> Returns 
        // 0 if the key k is not found-> The smallest item in the tree is rank 1
        int rank(keytype k){
            node* n = searchNode(k);
            int r = n->left->size + 1;
            node* y = n;
            while(y != head){
                if(y == y->parent->right){
                    r = r + y->parent->left->size + 1;
                }
                y = y->parent;
            }
            return r;
        }

        // Order Statistics-> Returns the key of the node at position pos in the tree-> Calling with pos = 1 
        // should return the smallest key in the tree, pos = n should return the largest->
        keytype select(int pos){
            node *n = selectRecurse(head, pos);
            return n->key;
        }

        // Returns a pointer to the key after k in the tree-> 
        // Should return NULL if no successor exists
        keytype* successor(keytype k){
            node* n = searchNode(k);
            node* y;
            if(n->right != nullNode){
                y = treeMin(n->right);
                return &y->key;
            }
            y = n->parent;
            while(y != nullNode && n == y->right){
                n = y;
                y = y->parent;
            }
            return &y->key; //must return Null
        }

        // Returns a pointer to the key before k in the tree-> 
        // Should return NULL if no predecessor exists
        keytype* predecessor(keytype k){
            node* n = searchNode(k);
            node* y;
            if(n->left != nullNode){
                y = treeMax(n->left);
                return &y->key;
            }
            y = n->parent;
            while(y != nullNode && n == y->left){
                n = y;
                y = y->parent;
            }
            return &y->key; //must return NULL
        }

        // Returns the number of node in the tree
        int size(){
            return treeSize;
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
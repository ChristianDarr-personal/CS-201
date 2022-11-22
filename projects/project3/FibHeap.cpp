#include <iostream>
#include <cstdlib>
#include <math.h>
#include "CircularDynamicArray.cpp"
using namespace std;

template <class keytype>
struct FibHeapNode {
    keytype key;
    bool marked;
    FibHeapNode<keytype> *parent;
    FibHeapNode<keytype> *left;
    FibHeapNode<keytype> *right;
    FibHeapNode<keytype> *child;
    int degree;
};

template<class keytype>
class FibHeap{
    private:
        FibHeapNode<keytype> *min;
        FibHeapNode<keytype> *head;
        FibHeapNode<keytype> *nullNode;
        int size;
        int n;

        void heapLink(FibHeapNode<keytype> *y, FibHeapNode<keytype> *x){
            if(y == head){
                head = y->right;
            }
            y->right->left = y->left;
            y->left->right = y->right;
            y->left = y;
            y->right = y;
            size--;
            y->parent = x;

            if(x->child != nullNode){ // x->child != nullNode
                x->child->left->right = y;
                y->right = x->child;
                y->left = x->child->left;
                x->child->left = y;
                x->child = y;
            } else {
                x->child = y;
                y->right = y;
                y->left = y;
            }
            x->degree++;
            y->marked = false;
        }   

        void consolidate(){
            if(size == 1){
                return;
            }
            float ph = 1.618;
            int dn = ceil(log(n)/log(ph))+1;
            FibHeapNode<keytype>* A[dn+1];
            for(int i = 0; i < dn+1; i++){
                A[i] = nullNode;
            }
            int loopFlag = 0;
            bool done = false;
            FibHeapNode<keytype>* current = head;
            while(current != head || loopFlag == 0){
                if(done == true){ break;}
                // printKey();
                loopFlag = 1;
                FibHeapNode<keytype>* x = current;
                if(current == head->left){
                    done = true;
                }
                current = current->right;
                
                int d = x->degree;
                while(A[d] != nullNode && d < dn){
                    FibHeapNode<keytype>* y = A[d];
                    if(y == current && current != head->left){
                        current = current->right;
                    }
                    if(x->key > y->key){
                        FibHeapNode<keytype>* temp = x;
                        x = y;
                        y = temp;
                    }
                    heapLink(y, x);
                    A[d] = nullNode;
                    d++;
                }
                A[d] = x;
            }
            min = nullNode;
            head = nullNode;
            size = 0;
            for(int i = 0; i <dn +1; i++){
                if(A[i] != nullNode){
                    A[i]->left = nullNode;
                    A[i]->right = nullNode;
                    if(head == nullNode){
                        head = A[i];
                        head->left = head;
                        head->right = head;
                        min = A[i];
                        size++;
                    } else {
                        head->left->right = A[i];
                        A[i]->right = head;
                        A[i]->left = head->left;
                        head->left = A[i];
                         // TODO: just insert it
                        if(A[i]->key < min->key){
                            min = A[i];
                        }
                        size++;
                    }
                }
            }
        }

        void printTree(FibHeapNode<keytype>* n){
            if(n == nullNode){
                return;
            }
            int loopFlag = 0;
            FibHeapNode<keytype>* current = n;
            while(current != n || loopFlag == 0){
                cout << current->key << " ";
                loopFlag = 1;
                printTree(current->child);
                current = current->right;
            }
        }

    public:
        

        // Default Constructor. The Heap should be empty O(1)
        FibHeap(){
            nullNode = nullptr;
            min = nullNode;
            head = nullNode;
            size = 0;
        }

        // The heap should be built using the array k containing s items of keytype. Once all the data
        // is in the heap, a single call of consolidate should be used to form the binomial trees. The handles
        // for the keys should be added to the end of circular dynamic array named handle. O(s)
        FibHeap(keytype k[], int s, CircularDynamicArray<FibHeapNode<keytype> *>&handle){
            nullNode = nullptr;
            // nullNode->marked = false;
            // nullNode->parent = nullNode;
            // nullNode->left = nullNode;
            // nullNode->right = nullNode;
            // nullNode->child = nullNode;
            // nullNode->degree = -1;
            min = nullNode;
            head = nullNode;
            size = 0;
            for(int i = 0; i < s; i++){
                FibHeapNode<keytype>* newNode = new FibHeapNode<keytype>();
                newNode->key = k[i];
                newNode->degree = 0;
                newNode->marked = false;
                newNode->child = nullNode;
                newNode->parent = nullNode;
                newNode->left = nullNode;
                newNode->left - nullNode;
                if(head == nullNode){
                    head = newNode;
                    head->left = newNode;
                    head->right = newNode;
                    min = newNode;
                } else {
                    head->left->right = newNode;
                    newNode->right = head;
                    newNode->left = head->left;
                    head->left = newNode;
                    if(newNode->key < min->key){
                        min = newNode;
                    }
                }
                size++;
                handle.addEnd(newNode);
            }
            consolidate();
        }

        // Destructor for the class. O(n) 
        ~FibHeap(){}

        // Returns the minimum key in the heap without modifying the heap. O(1)
        keytype peekKey(){
            return min->key;
        }
        
        // Removes the minimum key in the heap and returns the key. O(lg n)
        keytype extractMin(){
            keytype x =  min->key;
            FibHeapNode<keytype>* z = min;
            
            if(z != nullNode){
                int loopFlag = 0;
                FibHeapNode<keytype>* current = z->child;
                if(z->child == nullNode){
                    head = z->right;
                    min = z->right;
                    z->right->left = z->left;
                    z->left->right = z->right;
                    size -= 1;
                    int flag = 0;
                    FibHeapNode<keytype>* findMin = head;
                    while(findMin != head || flag == 0){
                        flag = 1;
                        if(findMin->key < min->key){
                            min = findMin;
                        }
                        findMin = findMin->right;
                    }
                    
                    if(z == z->right){
                        min = nullNode;
                        head = nullNode;
                        size = 0;
                    } else {
                        if(min == head){
                            head = z->right;
                        }
                        min = z->right;
                        printKey();
                        consolidate();
                    }
                    return x;
                }
                while(current != z->child || loopFlag == 0){
                    loopFlag = 1;
                    current->parent = nullNode;
                    current = current->right;
                    size++;
                }
                
                head->left->right = z->child;
                head->left = z->child->left;
                z->child->left = head->left;
                z->child->left->right = head;
                z->child = nullNode;
                z->right->left = z->left;
                z->left->right = z->right;
                size -= 1;
                
                if(z == z->right){
                    min = nullNode;
                    head = nullNode;
                    size = 0;
                } else {
                    if(min == head){
                        head = z->right;
                    }
                    min = z->right;
                    printKey();
                    consolidate();
                }
                
            }
            
            n--;    
            return x;
        }

        // Inserts the key k into the heap, returning an pointer “handle” for direct access to the key for decrease-key.
        FibHeapNode<keytype>* insert(keytype k){
            FibHeapNode<keytype>* newNode = new FibHeapNode<keytype>();
            newNode->key = k;
            newNode->degree = 0;
            newNode->marked = false;
            newNode->child = nullNode;
            newNode->parent = nullNode;
            newNode->left = nullNode;
            newNode->left - nullNode;
            if(head == nullNode){
                head = newNode;
                head->left = newNode;
                head->right = newNode;
                min = newNode;
            } else {
                head->left->right = newNode;
                newNode->right = head;
                newNode->left = head->left;
                head->left = newNode;
                if(newNode->key < min->key){
                    min = newNode;
                }
            }
            size++;
            n++;
            return newNode;
        }

        // Decrease the key of the node stored at the address h to the value k. You can assume that
        // the node stored at this address does belong to this FibHeap instance. If k is not less than the
        // current key, do nothing and return False. Return True otherwise.
        bool decreaseKey(FibHeapNode<keytype> *x, keytype k){
            if(k > x->key){
                return false;
            }
            x->key = k;
            FibHeapNode<keytype>* y = x->parent;
            if(y!= nullNode && x->key < y->key){
                cut(x, y);
                cascadingCut(y);
            }
            if(x->key < min->key){
                min = x;
            }
            return true;
        }

        void cut(FibHeapNode<keytype>* x, FibHeapNode<keytype>* y){
            if(x == y->child){
                if(y->degree == 1){
                    y->child = nullNode;
                } else {
                    y->child = x->right;
                }
                y->degree--;
            }
            x->right->left = x->left;
            x->left->right = x->right;
            head->left->right = x;
            x->right = head;
            x->left = head->left;
            head->left = x;
            if(x->key < min->key){
                min = x;
            }

            x->parent = nullNode;
            x->marked = false;
        }

        void cascadingCut(FibHeapNode<keytype>* y){
            FibHeapNode<keytype>* z = y->parent;
            if(z != nullNode){
                if(!y->marked){
                    y->marked = true;
                } else {
                    cut(y, z);
                    cascadingCut(z);
                }
            }
        }

        // Merges the heap H2 into the current heap. Consumes H2.
        void merge(FibHeap<keytype>&H2){            
            head->left->right = H2.head;
            head->left = H2.head->left;
            H2.head->left = head->left;
            H2.head->left->right = head;
            if(min == nullNode || ((H2.min != nullptr) && (min->key > H2.min->key))){
                min = H2.min;
            }
            size += H2.size;
        }


        // Writes the keys stored in the heap, starting at the head of the list. When printing a binomial
        // tree, print the size of tree first and then use a modified preorder traversal of the tree.
        void printKey(){
            cout << "PrintKey!" << endl;
            int loopFlag = 0;
            FibHeapNode<keytype>* current = head;
            if(current != nullNode){
                while(current != head || loopFlag == 0){
                    loopFlag = 1;
                    cout << "Rank " << current->degree << endl;
                    cout << current->key << " ";
                    printTree(current->child);
                    current = current->right;
                    cout << endl << endl;
                }
            }
        }

        

};
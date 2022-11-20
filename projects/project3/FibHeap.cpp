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

        void heapLink(FibHeapNode<keytype> *y, FibHeapNode<keytype> *x){
            y->right->left = y->left;
            y->left->right = y->right;
            
            if(x->child != nullNode){
                x->child->left->right = y;
                y->right = x->child;
                y->left = x->child->left;
                x->child->left = y;
                x->child = y;
            } else {
                x->child = y;
                y->parent = x;
                y->right = y;
                y->left = y;
            }
            x->degree++;
            y->marked = false;
        }   

        void consolidate(){
            float ph = 1.618;
            int dn = ceil(log(size)/log(ph));
            FibHeapNode<keytype>* A[dn];
            for(int i = 0; i < dn; i++){
                A[i] = nullNode;
            }
            int loopFlag = 0;
            FibHeapNode<keytype>* current = head;
            while(current != head || loopFlag == 0){
                loopFlag = 1;
                FibHeapNode<keytype>* x = current;
                current = current->right;
                int d = x->degree;
                while(A[d] != nullNode){
                    FibHeapNode<keytype>* y = A[d];
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
            for(int i = 0; i <dn; i++){
                if(A[i] != nullNode){
                    if(min == nullNode){
                        head = A[i];
                        min = A[i];
                        size = 1;
                    } else {
                        min->left->right = A[i];
                        A[i]->right = min;
                        A[i]->left = min->left;
                        min->left = A[i];
                         // TODO: just insert it
                        if(A[i]->key < min->key){
                            min = A[i];
                        }
                    }
                }
            }
        }

    public:
        

        // Default Constructor. The Heap should be empty O(1)
        FibHeap(){
            nullNode = new FibHeapNode<keytype>();
            nullNode->marked = false;
            nullNode->parent = nullNode;
            nullNode->left = nullNode;
            nullNode->right = nullNode;
            nullNode->child = nullNode;
            nullNode->degree = -1;
            min = nullNode;
            head = nullNode;
            size = 0;
        }

        // The heap should be built using the array k containing s items of keytype. Once all the data
        // is in the heap, a single call of consolidate should be used to form the binomial trees. The handles
        // for the keys should be added to the end of circular dynamic array named handle. O(s)
        FibHeap(keytype k[], int s, CircularDynamicArray<FibHeapNode<keytype> *>&handle){
            nullNode = new FibHeapNode<keytype>();
            nullNode->marked = false;
            nullNode->parent = nullNode;
            nullNode->left = nullNode;
            nullNode->right = nullNode;
            nullNode->child = nullNode;
            nullNode->degree = -1;
            min = nullNode;
            head = nullNode;
            size = 0;
            for(int i = 0; i < s; i++){
                insert(k[i]);
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
            return newNode;
        }

        // Decrease the key of the node stored at the address h to the value k. You can assume that
        // the node stored at this address does belong to this FibHeap instance. If k is not less than the
        // current key, do nothing and return False. Return True otherwise.
        bool decreaseKey(FibHeapNode<keytype> *h, keytype k){}

        // Merges the heap H2 into the current heap. Consumes H2.
        void merge(FibHeap<keytype>&H2){            
            head->left->right = H2.head;
            head->left = H2.head->left;
            H2.head->left = head->left;
            H2.head->left->right = head;
            if(min == nullNode || (H2.min != H2.nullNode && min > H2.min)){
                min = H2.min;
            }
            size += H2.size;
        }


        // Writes the keys stored in the heap, starting at the head of the list. When printing a binomial
        // tree, print the size of tree first and then use a modified preorder traversal of the tree.
        void printKey(){
            int loopFlag = 0;
            FibHeapNode<keytype>* current = head;
            while(current != head || loopFlag == 0){
                loopFlag = 1;
                printTree(current);
                current = current->right;
            }
        }

        void printTree(FibHeapNode<keytype>* n){
            if(n == nullNode){
                return;
            }
            cout << n->key << " ";
            int loopFlag = 0;
            FibHeapNode<keytype>* current = n;
            while(current != n || loopFlag == 0){
                loopFlag = 1;
                printTree(current->child);
                current = current->right;
            }
        }

};
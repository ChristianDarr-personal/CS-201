#include <iostream>
#include <cstdlib>
#include "CircularDynamicArray.cpp"
using namespace std;

template<class keytype>
class Heap{
    private:
        CircularDynamicArray<keytype> heap;

        void buildHeap(){
            int startIndex = (heap.length()/2) - 1;
            for(int i = startIndex; i >= 0; i--){
                heapify(i);
            }
        }
        void heapify(int index){
            int smallest = index;
            if(leftChild(index) < heap.length() && heap[leftChild(index)] < heap[smallest])
                smallest = leftChild(index);
    
            if (rightChild(index) < heap.length() && heap[rightChild(index)] < heap[smallest])
                smallest = rightChild(index);
        
            if (smallest != index) {
                keytype temp = heap[index];
                heap[index] = heap[smallest];
                heap[smallest] = temp;

                heapify(smallest);
            }
        }

        int parent(int i){
            return (i-1)/2;
        }

        int leftChild(int i){
            return (2*i+1);
        }

        int rightChild(int i){
            return (2*i +2);
        }

        void deepCopy(const Heap &h){
            this->heap = h.heap;
        }

    public:
        Heap(){
            heap = CircularDynamicArray<keytype>();
        }

        Heap(keytype k[], int s){
            heap = CircularDynamicArray<keytype>(s);
            for(int i = 0; i < s; i++){
                heap[i] = k[i];
            }
            buildHeap();
        }

        ~Heap(){
        }

        Heap(const Heap& h){
            deepCopy(h);
        }

        Heap& operator=(const Heap& h){
            if(this != &h){
                deepCopy(h);
            }
            return *this;
        }

        // Returns the minimum key in the heap without modifiying the heap
        keytype peekKey(){
            return heap[0];
        } 

        // Removes the minimum key in the heap and returns the key
        keytype extractMin(){
            keytype min = heap[0];
            heap[0] = heap[heap.length() - 1];
            heap.delEnd();
            heapify(0);
            return min;
        }

        // Inserts the key k into the heap
        void insert(keytype k){
            heap.addEnd(k);
            int current = heap.length() - 1;
            while(current > 0 && heap[parent(current)] > heap[current]){
                keytype temp = heap[parent(current)];
                heap[parent(current)] = heap[current];
                heap[current] = temp;
                current = parent(current);
            }
        }

        // Writes the keys stored in the array, starting at the root
        void printKey(){
            for(int i = 0; i < heap.length(); i++){
                cout << heap[i] << " ";
            }
            cout << endl;
        }

};
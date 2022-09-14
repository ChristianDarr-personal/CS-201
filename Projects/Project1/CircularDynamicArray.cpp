#include <iostream>
using namespace std;


template <class elmtype>
class CircularDynamicArray{
    private:
        int size;
        int capacity;
        int front;
        int end;
        elmtype *array;
        void grow();
        void shrink();
    public:
        CircularDynamicArray();
        CircularDynamicArray(int s);
        ~CircularDynamicArray();

        elmtype& operator[](int i);

        void AddFront(elmtype v);
        void AddEnd(elmtype v);

        void DelFront();
        void DelEnd();

        int Length();
        int Capacity();

        void Clear();
        
        elmtype QuickSelect(int k);
        elmtype WCSelect(int k);

        void StableSort();
        int Search(elmtype v);
        int BinSearch(elmtype v);
};

template <class elmtype>
CircularDynamicArray<elmtype>::CircularDynamicArray(){
    size = 0;
    capacity = 2;
    end = 0;
    front = 0;
    array = new elmtype[this->size];
}

template <class elmtype>
CircularDynamicArray<elmtype>::CircularDynamicArray(int s){
    size = s;
    capacity = s;
    front = 0;
    end = this->size - 1;
    array = new elmtype[this->size];
}

template <class elmtype>
CircularDynamicArray<elmtype>::~CircularDynamicArray(){
}


template <class elmtype>
elmtype& CircularDynamicArray<elmtype>:: operator[](int i){
    if(i > size || i < 0) {
        cout << "Array index is out of bounds";
    } else {
        return array[(front + i)%(size+1)];
    }
}

template <class elmtype>
void CircularDynamicArray<elmtype>::AddFront(elmtype v){
    size += 1;
    front = (front - 1)%(size+1);
    array[front] = v;
}

template <class elmtype>
void CircularDynamicArray<elmtype>::AddEnd(elmtype v){
    size += 1;
    if(size > capacity) {
        capacity
    }
    end = (end + 1)%(size+1);
    array[end] = v;
}

template <class elmtype>
void CircularDynamicArray<elmtype>::DelFront(){
    front = (front + 1)%(size+1);
    size -= 1;
}

template <class elmtype>
void CircularDynamicArray<elmtype>::DelEnd(){
    end = (end - 1)%(size+1);
    size -= 1;
}

template <class elmtype>
int CircularDynamicArray<elmtype>::Length(){
    return size;
}

template <class elmtype>
int CircularDynamicArray<elmtype>::Capacity(){
    return capacity;
}

template <class elmtype>
void CircularDynamicArray<elmtype>::Clear(){

}

template <class elmtype>
elmtype CircularDynamicArray<elmtype>::QuickSelect(int k){

}

template <class elmtype>
elmtype CircularDynamicArray<elmtype>::WCSelect(int k){

}

template <class elmtype>
void CircularDynamicArray<elmtype>::StableSort(){

}

template <class elmtype>
int CircularDynamicArray<elmtype>::Search(elmtype v){
    for(int i = 0; i < size; i++){
        if(array[i] == v){
            return i;
        }
    }
}

template <class elmtype>
int CircularDynamicArray<elmtype>::BinSearch(elmtype v){
    int left = 0, right = size, center;   
    while (left <= right) {
        center = (left + right) / 2;
        if(array[center] == v) {
            return center;
        }
        if(array[center] < v) {
            left = center + 1;
        } else {
            right = center -1;
        }
        return -1;
    }
}

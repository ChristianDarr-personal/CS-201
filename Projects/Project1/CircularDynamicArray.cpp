#include <iostream>
using namespace std;


template <class elmtype>
class CircularDynamicArray{
    private:
        elmtype data;
        int size;
        int capacity;
        int front;
        int end;
        elmtype array[];
    public:
        CircularDynamicArray(int s);
        ~CircularDynamicArray();

        void AddFront(elmtype v){};
        void AddEnd(elmtype v){};

        void DelFront(){};
        void DelEnd(){};

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
CircularDynamicArray<elmtype>::CircularDynamicArray(int s){
}

template <class elmtype>
CircularDynamicArray<elmtype>::~CircularDynamicArray(){
}

template <class elmtype>
void CircularDynamicArray<elmtype>::AddFront(elmtype v){

}

template <class elmtype>
void CircularDynamicArray<elmtype>::AddEnd(elmtype v){

}

template <class elmtype>
void CircularDynamicArray<elmtype>::DelFront(){

}

template <class elmtype>
void CircularDynamicArray<elmtype>::DelEnd(){

}

template <class elmtype>
int CircularDynamicArray<elmtype>::Length(){

}

template <class elmtype>
int CircularDynamicArray<elmtype>::Capacity(){

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

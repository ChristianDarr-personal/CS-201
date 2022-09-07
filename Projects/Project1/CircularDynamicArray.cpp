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

        void addFront(elmtype v){};
        void addEnd(elmtype v){};

        void delFront(){};
        void delEnd(){};

        int length();
        int capacity();

        void clear();
        
        elmtype QuickSelect(int k);
        elmtype WCSelect(int k);

        void stableSort();
        int linearSearch(elmtype v);
        int binSearch(elmtype v);
};

template <class elmtype>
CircularDynamicArray<elmtype>::CircularDynamicArray(int s){
}

template <class elmtype>
CircularDynamicArray<elmtype>::~CircularDynamicArray(){
}

template <class elmtype>
void CircularDynamicArray<elmtype>::addFront(elmtype v){

}

template <class elmtype>
void CircularDynamicArray<elmtype>::addEnd(elmtype v){

}

template <class elmtype>
void CircularDynamicArray<elmtype>::delFront(){

}

template <class elmtype>
void CircularDynamicArray<elmtype>::delEnd(){

}

template <class elmtype>
int CircularDynamicArray<elmtype>::length(){

}

template <class elmtype>
int CircularDynamicArray<elmtype>::capacity(){

}

template <class elmtype>
void CircularDynamicArray<elmtype>::clear(){

}

template <class elmtype>
elmtype CircularDynamicArray<elmtype>::QuickSelect(int k){

}

template <class elmtype>
elmtype CircularDynamicArray<elmtype>::WCSelect(int k){

}

template <class elmtype>
void CircularDynamicArray<elmtype>::stableSort(){

}

template <class elmtype>
int CircularDynamicArray<elmtype>::linearSearch(elmtype v){
    for(int i = 0; i < size; i++){
        if(array[i] == v){
            return i;
        }
    }
}

template <class elmtype>
int CircularDynamicArray<elmtype>::binSearch(elmtype v){
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

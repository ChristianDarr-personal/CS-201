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
        void print();
    public:
        CircularDynamicArray();
        CircularDynamicArray(int s);
        ~CircularDynamicArray();

        CircularDynamicArray(const CircularDynamicArray& c);
        CircularDynamicArray& operator=(const CircularDynamicArray& c){
            this->size = c.size;
            this->capacity = c.capacity;
            this->front = c.front;
            this->end = c.end;
            elmtype *b = new elmtype[capacity];
            for(int i = 0; i < size; i++){
                b[i] = c[i];
            }
            this->array = b;
            cout << "Copy operator Called" << endl;
        }

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
void CircularDynamicArray<elmtype>::grow(){
    capacity *= 2;
    elmtype *b;
    b = new elmtype[size];
    b = array;
    array = new elmtype[capacity];
    for(int i = 0; i < size - 1; i++)
    {
        array[i] = b[i];
    }
    delete[] b;
}

template <class elmtype>
void CircularDynamicArray<elmtype>::print(){
    for (int i=0; i< size;i++) cout << array[i] << endl;
}
template <class elmtype>
void CircularDynamicArray<elmtype>::shrink(){

}
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
    delete[] array;
    cout << "Destructor Called" << endl;
}


template <class elmtype>
elmtype& CircularDynamicArray<elmtype>:: operator[](int i){
    if(i > size || i < 0) {
        cout << "Array index is out of bounds";
    } else {
        return array[(front + i)%capacity];
    }
}

template <class elmtype>
void CircularDynamicArray<elmtype>::AddFront(elmtype v){
    size += 1;
    if(size > capacity){
        grow();
    }
    front = (front - 1)%(capacity);
    array[front] = v;
}

template <class elmtype>
void CircularDynamicArray<elmtype>::AddEnd(elmtype v){
    size += 1;
    if(size > capacity) {
        capacity;
    }
    end = (end + 1)%(capacity);
    array[end] = v;
}

template <class elmtype>
void CircularDynamicArray<elmtype>::DelFront(){
    front = (front + 1)%(capacity);
    size -= 1;
}

template <class elmtype>
void CircularDynamicArray<elmtype>::DelEnd(){
    end = (end - 1)%(capacity);
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

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
        elmtype *bad;

        void grow(){
            capacity *= 2;
            elmtype* temp = new elmtype[capacity];
            for(int j = 0; j < size; j++)
            {
                temp[j] = array[(front + j)%capacity];
                // cout << temp[j] << endl;
            }
            delete[] array;
            array = temp;
            // new elmtype[capacity];
            // for(int i = 0; i < size; i++)
            // {
            //     array[i] = temp[i];
            // }
            delete[] temp;
            front = 0;
            end = size -1;
            cout << "Doubling to: " << capacity << endl;
        }

        void shrink();
        void print(){
            for (int i=0; i< size;i++) cout << array[i] << endl;        
        }

        void deepCopy(const CircularDynamicArray& c){
            size = c.size;
            capacity = c.capacity;
            front = c.front;
            end = c.end;
            array = new elmtype[capacity];
            for(int i = 0; i < size; i++){
                array[i] = c[i];
            }
            cout << "deepCopy called" << endl << flush;
        }

    public:
        CircularDynamicArray(){
            size = 0;
            capacity = 2;
            end = 0;
            front = 0;
            array = new elmtype[capacity];
        }

        CircularDynamicArray(int s){
            size = s;
            capacity = s;
            front = 0;
            end = this->size - 1;
            array = new elmtype[capacity];
        }

        ~CircularDynamicArray(){
            cout << "Destructor Called" << flush << endl;
            delete[] array;
        }

        CircularDynamicArray(const CircularDynamicArray& c){
            deepCopy(c);
        }

        CircularDynamicArray& operator=(const CircularDynamicArray& c){
            if(this != &c){
                delete[] array;
                deepCopy(c);
            }
            cout << "copy called" << flush << endl;
            return *this;
        }

        elmtype& operator[](int i){
            if(i > size || i < 0) {
                cout << "Array index is out of bounds" << endl;
                return *bad;
            } else {
                return array[(front + i)%capacity];
            }
        }

        void AddFront(elmtype v){
            size += 1;
            if(size > capacity){
                grow();
            }
            front = (front - 1)%(capacity);
            array[front] = v;
        }


        void AddEnd(elmtype v){
            size += 1;
            if(size > capacity) {
                capacity;
            }
            end = (end + 1)%(capacity);
            array[end] = v;
        }

        void DelFront(){
            front = (front + 1)%(capacity);
            size -= 1;      
        }
        void DelEnd(){
            end = (end - 1)%(capacity);
            size -= 1;
        }

        int Length(){
            return size;
        }

        int Capacity(){
            return capacity;
        }

        void Clear(){
            delete[] array;
            array = new elmtype[2];
            size = 0;
            capacity = 2;
            front = 0;
            end = 0;
            cout << "clear" << flush << endl;
        }
        
        elmtype QuickSelect(int k);
        elmtype WCSelect(int k);

        void StableSort();
        int Search(elmtype v){
            for(int i = 0; i < size; i++){
                if(array[i] == v){
                    return i;
                }
            }
        }
        int BinSearch(elmtype v){
            int left = 0, right = size, center;   
            while (left <= right) {
                center = (left + right) / 2;
                if(array[(front + center)%capacity] == v) {
                    return center;
                }
                if(array[(front + center)%capacity] > v) {
                    left = center + 1;
                } else {
                    right = center -1;
                }
            }
            return -1;
        }
};


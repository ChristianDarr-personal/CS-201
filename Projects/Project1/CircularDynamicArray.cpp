#include <iostream>
using namespace std;


template <class elmtype>
class CircularDynamicArray{
    private:
        int size;
        int cap;
        int front;
        int end;
        elmtype *array;
        elmtype *bad;

        void grow(){
            elmtype* temp = new elmtype[cap*2];
            for(int j = 0; j < size; j++){
                temp[j] = array[(front + j)%cap];
            }
            delete[] array;
            array = temp;
            cap *=2;
            front = 0;
            end = size - 1;
        }

        void shrink(){
            elmtype* temp = new elmtype[cap/2];
            for(int j = 0; j < size; j++)
            {
                temp[j] = array[(front + j)%cap];
            }
            delete[] array;
            array = temp;
            cap /=2;
            front = 0;
        }

        void deepCopy(const CircularDynamicArray &c){
            this->size = c.size;
            this->cap = c.cap;
            this->front = c.front;
            this->array = new elmtype[cap];
            for(int i = 0; i < size; i++){
                array[i] = c.array[i];
            }
            cout << "deepCopy called" << endl << flush;
        }

        void mergeSort(elmtype* arr, int n){
            if(n <= 1){
                return;
            }
            elmtype* left = new elmtype[n/2];
            elmtype* right = new elmtype[n - n/2];
            for(int i = 0; i < n/2; i++){
                if(&arr == &array) {
                    left[i] = arr[(front + i)%cap];
                } else {
                    left[i] = arr[i];
                }
            }
            for(int i = n/2; i < n; i++){
                if(&arr == &array) {
                    right[i-n/2] = arr[(front + i)%cap];
                } else {
                    right[i-n/2] = arr[i];
                }
            }
            mergeSort(left, n/2);
            mergeSort(right, n-n/2);
            merge(arr, left, right, n);
        }

        void merge(elmtype* arr, elmtype* left, elmtype* right, int n){
            int leftSize = n/2;
            int rightSize = n - n/2;
            int leftPos = 0;
            int rightPos = 0;
            int mergePos = 0;
            while(leftPos < leftSize && rightPos < rightSize){
                if(left[leftPos] < right[rightPos]){
                    arr[mergePos++] = left[leftPos++];
                } else {
                    arr[mergePos++] = right[rightPos++];
                }
            }
            while(leftPos < leftSize){
                arr[mergePos++] = left[leftPos++];
            }
            while(rightPos < rightSize){
                arr[mergePos++] = right[rightPos++];
            }
        }

    public:
        CircularDynamicArray(){
            size = 0;
            cap = 2;
            front = 0;
            end = 0;
            array = new elmtype[cap];
        }

        CircularDynamicArray(int s){
            size = s;
            cap = s;
            front = 0;
            end = 0;
            array = new elmtype[cap];
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
            return *this;
        }

        elmtype& operator[](int i){
            if(i > size || i < 0) {
                cout << "Array index is out of bounds" << endl;
                return *bad;
            } else {
                return array[(front + i)%cap];
            }
        }

        void addFront(elmtype v){
            if(size + 1 > cap){
                grow();
            }
            size += 1;
            front -= 1;
            if(front < 0){
                front = cap - 1;
            }
            array[front] = v;
        }

        void addEnd(elmtype v){
            if(size + 1 > cap) {
                grow();
            }
            size += 1;
            end += 1;
            array[end] = v;
        }

        void delFront(){
            if(size - 1 < cap/4) {
                shrink();
            }
            size -= 1;
            front = (front + 1)%(cap);
        }

        void delEnd(){
            if(size - 1 < cap/4) {
                shrink();
            }
            size -= 1;
        }

        int length(){
            return size;
        }

        int capacity(){
            return cap;
        }

        void clear(){
            delete[] array;
            array = new elmtype[2];
            size = 0;
            cap = 2;
            front = 0;
            end = 0;
            cout << "clear" << flush << endl;
        }
        
        // elmtype QuickSelect(int k){
        //     int pivot = array[(front + 5)%(cap)];
        //     int l, e, g;
        //     for(int i = 0; i < size; i++){
        //         int x = array[(front + i)%(cap)];
        //         if (x<pivot){
        //             l++;
        //         } else if (x==pivot){
        //             e++;
        //         } else{
        //             g++;
        //         }
        //     }
        //     if (k <= l){
        //         return Select (k);
        //     }
        //     else if (k <= l + e){
        //         return pivot; 
        //     } else {
        //         return Select (k - l - e);
        //     }
        // }

        elmtype WCSelect(int k);

        void stableSort(){
            mergeSort(array, size);
            front = 0;
            end = size - 1;
        }

        int linearSearch(elmtype v){
            for(int i = 0; i < size; i++){
                if(array[(front + i)%cap] == v){
                    return i;
                }
            }
        }

        int binSearch(elmtype v){
            return search(v, 0, size - 1);
        }

        int search(elmtype x, int l, int r){
            int c;
            c = (l + r) / 2;
            
            if (l > r) {
                return -1;
            }
            if(array[(front + c)%cap] == x) {
                return c;
            } else if(x < array[(front + c)%cap]) {
                search(x, l, c - 1);
            } else if(x > array[(front + c)%cap]){
                search(x, c + 1, r);
            }
        }
};


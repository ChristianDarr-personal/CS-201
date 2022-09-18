#include <iostream>
using namespace std;


template <class elmtype>
class CircularDynamicArray{
    private:
        int size;
        int cap;
        int front;
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
            this->bad = c.bad;
            this->array = new elmtype[cap];
            for(int i = 0; i < size; i++){
                array[(front + i)%cap] = c.array[(c.front + i)%c.cap];
            }
        }

        void mergeSort(elmtype* arr, int n, bool pass){
            if(n <= 1){
                return;
            }
            elmtype* left = new elmtype[n/2];
            elmtype* right = new elmtype[n - n/2];
            for(int i = 0; i < n/2; i++){
                if(pass){
                    left[i] = arr[(i + front)%cap];
                } else{
                    left[i] = arr[i];
                }
            }
            for(int i = n/2; i < n; i++){
                if(pass){
                    right[i-n/2] = arr[(i + front)%cap];
                } else{
                    right[i-n/2] = arr[i];
                }
                
            }
            mergeSort(left, n/2, false);
            mergeSort(right, n-n/2, false);
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

        // elmtype selectWC(elmtype* arr, int k, int s){
        //     int g = 5;

        //     int l = 0, e = 0, g = 0;
        //     elmtype* less = new elmtype[s];
        //     elmtype* greater = new elmtype[s];
        //     for(int i = 0; i < s; i++){
        //         elmtype x;
        //         x = arr[i];
        //         if (x<pivot){
        //                 less[l++] = x;
        //         } else if (x == pivot){
        //             e++;
        //         } else{
        //             greater[g++] = x;
        //         }
        //     }
        //     if (k <= l){
        //         return selectNormal(less, k, l, wc);
        //     }
        //     else if (k <= l + e){
        //         return pivot; 
        //     } else {
        //         return selectNormal(greater, k - l - e, g);
        //     }
        // }

        elmtype selectNormal(elmtype* arr, int k, int s, bool pass){
            int pivot = arr[rand() % s];
            int l = 0, e = 0, g = 0;
            elmtype x;
            elmtype* less = new elmtype[s];
            elmtype* greater = new elmtype[s];
            for(int i = 0; i < s; i++){
                if(pass){
                    x = arr[(i + front)%cap];
                }else {
                    x = arr[i];
                }
                if (x<pivot){
                    less[l++] = x;
                } else if (x == pivot){
                    e++;
                } else{
                    greater[g++] = x;
                }
            }
            if (k <= l){
                return selectNormal(less, k, l, false);
            }
            else if (k <= l + e){
                return pivot; 
            } else {
                return selectNormal(greater, k - l - e, g, false);
            }
        }

        int search(elmtype x, int l, int r){
            int c = (l + r) / 2;
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

    public:
        CircularDynamicArray(){
            size = 0;
            cap = 2;
            front = 0;
            array = new elmtype[cap];
        }

        CircularDynamicArray(int s){
            size = s;
            cap = s;
            front = 0;
            array = new elmtype[cap];
        }

        ~CircularDynamicArray(){
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
            array[((front + (size - 1))%cap)] = v;
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
            cout << "clear" << flush << endl;
        }

        elmtype QuickSelect(int k){
            return selectNormal(array, k, size, true);
        }

        // elmtype WCSelect(int k){
        //     return selectWC(array, k, size);
        // }

        void stableSort(){
            mergeSort(array, size, true);
            front = 0;
        }

        int linearSearch(elmtype v){
            for(int i = 0; i < size; i++){
                if(array[(front + i)%cap] == v){
                    return i;
                }
            }
            return -1;
        }

        int binSearch(elmtype v){
            return search(v, 0, size - 1);
        }
};

#include <iostream>
#include <cstdlib>
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

        elmtype medianArray(elmtype* arr, int off, int s, bool pass){
            int minIndex;
            elmtype temp;
            elmtype x;
            if(pass){
                for (int i = off; i < s + off; i++){
                    minIndex = i;
                    for (int j = i + 1; j < off + s; j++){
                        if (arr[(j+front)%cap] < arr[(front + minIndex)%cap]){
                            minIndex = j;
                        }
                    }
                    temp = arr[(front + minIndex)%cap];
                    arr[(front + minIndex)%cap] = arr[(i + front)%cap];
                    arr[(i + front)%cap] = temp;
                }
                x = arr[(front + off + (s/2))%cap];
            } else{
                for (int i = off; i < s + off; i++){
                    minIndex = i;
                    for (int j = i + 1; j < off + s; j++){
                        if (arr[j] < arr[minIndex]){
                            minIndex = j;
                        }
                    }
                    temp = arr[minIndex];
                    arr[minIndex] = arr[i];
                    arr[i] = temp;
                }
                x = arr[off + (s/2)];

            }
            return x;
        }

        // elmtype selectWC(elmtype arr[], int l, int r, int k){
        //     if (k > 0 && k <= r - l + 1){
        //         int n = r - l + 1; 
        //         int i;
        //         elmtype medianArr[(n+4)/5];
        //         for (i = 0; i < n/5; i++){
        //             medianArr[i] = medianArray(arr,i*5, 5);
        //         }
        //         if (i*5 < n){
        //             medianArr[i] = medianArray(arr, i*5, n%5);
        //             i++;
        //         }
        //         elmtype pivot;
        //         if(i == 1){
        //             pivot = medianArr[i - 1];
        //         } else {
        //             selectWC(medianArr, 0, i-1, i/2);
        //         }
                
        //         int pos;
        //         pos = partition(arr, l, r, pivot);
        //         if (pos-l == k - 1){
        //             return arr[pos];
        //         }
        //         if (pos-l > k-1){
        //             return selectWC(arr, l, pos-1, k);
        //         }
        //         return selectWC(arr, pos+1, r, k-pos+l-1);
        //     }
        //     return 0;
        // }

        // void swap(elmtype *a, elmtype *b)
        // {
        //     elmtype temp = *a;
        //     *a = *b;
        //     *b = temp;
        // }


        // int partition(elmtype arr[], int l, int r, elmtype x)
        // {
        //     elmtype temp;
        //     int i;
        //     for (i=l; i<r; i++){
        //         if (arr[i] == x){
        //             break;
        //         }
        //     }
        //     temp = arr[r];
        //     arr[r] = arr[i];
        //     arr[i] = temp;
        //     i = l;
        //     for (int j = l; j <= r - 1; j++)
        //     {
        //         if (arr[j] <= x)
        //         {
        //             temp = arr[j];
        //             arr[j] = arr[i];
        //             arr[i] = temp;
        //             i++;
        //         }
        //     }
        //     temp = arr[r];
        //     arr[r] = arr[i];
        //     arr[i] = temp;
           
        //     return i;
        // }   

    elmtype findPivot(elmtype* arr, int k, int s, bool pass){
            int p = 5;
            int i = 0;
            int n = (s+(p-1))/p;
            elmtype medianArr[n];
            for (i = 0; i < s/5; i++){
                medianArr[i] = medianArray(arr,i*5, 5, pass);
            }
            if (i*5 < s){
                medianArr[i] = medianArray(arr, i*5, s%5, pass);
                i++;
            }

            // cout << "arr: " << endl;
            // if(pass){
            // for(int j = 0; j < s; j++){
            //     cout << arr[(j + front)%cap] << " ";
            // }
            // }else{
            //     for(int j = 0; j < s; j++){
            //         cout << arr[j] << " ";
            //         }
            // }
            // cout << endl;


            // cout << "medianArr: " << endl;
            // for(int i = 0; i < n; i++){
            //     cout  << medianArr[i] << " ";
            // }
            // cout << endl;
            // cout << "size: " << s << endl << endl;

            if(n < 15){
                return medianArr[n/2];
            }
            else{
                return findPivot(medianArr, s/2, n, false);
            }
    }

    elmtype selectWC(elmtype* arr, int k, int s, bool pass) {
            elmtype pivot = findPivot(arr, k, s, pass);
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
                return selectWC(less, k, l, false);
            }
            else if (k <= l + e){
                return pivot; 
            } else {
                return selectWC(greater, k - l - e, g, false);
            }
        }   

        elmtype selectNormal(elmtype* arr, int k, int s, bool pass){
            elmtype pivot = arr[(rand() % s)];
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
        }

        elmtype QuickSelect(int k){
            return selectNormal(array, k, size, true);
        }

        elmtype WCSelect(int k){
            // elmtype temp[size];
            // for(int i = 0; i < size; i++){
            //     temp[i] = array[(front + i)%cap];
            // }
            return selectWC(array, k, size, true);
        }

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

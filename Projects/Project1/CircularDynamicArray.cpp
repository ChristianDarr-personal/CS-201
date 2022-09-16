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
            for(int j = 0; j < size; j++)
            {
                temp[j] = array[(front + j)%cap];
                // cout << temp[j] << endl;
            }
            
            this->array = temp;
            cap *=2;
            front = 0;
            end = size -1;
            cout << "Doubling to: " << cap << endl;
            // delete[] ptDelete;
        }

        void shrink();
        void print(){
            for (int i=0; i< size;i++) cout << array[i] << endl;        
        }

        void deepCopy(const CircularDynamicArray &c){
            this->size = c.size;
            this->cap = c.cap;
            this->front = c.front;
            this->end = c.end;
            this->array = new elmtype[cap];
            for(int i = 0; i < size; i++){
                array[i] = c.array[i];
            }
            cout << "deepCopy called" << endl << flush;
        }
        void select()

    public:
        CircularDynamicArray(){
            size = 0;
            cap = 2;
            end = 0;
            front = 0;
            array = new elmtype[cap];
        }

        CircularDynamicArray(int s){
            size = s;
            cap = s;
            front = 0;
            end = this->size - 1;
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
            cout << "copy called" << flush << endl;
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
            size += 1;
            if(size > cap){
                grow();
            }
            front = (front - 1)%(cap);
            array[front] = v;
        }


        void addEnd(elmtype v){
            size += 1;
            if(size > cap) {
                cap;
            }
            end = (end + 1)%(cap);
            array[end] = v;
        }

        void delFront(){
            front = (front + 1)%(cap);
            size -= 1;      
        }
        void delEnd(){
            end = (end - 1)%(cap);
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
        
        elmtype QuickSelect(int k){
          
        }

        elmtype WCSelect(int k);

        void stableSort();

        int linearSearch(elmtype v){
            for(int i = 0; i < size; i++){
                if(array[array[(front + i)%cap] == v){
                    return i;
                }
            }
        }

        int binSearch(elmtype v){
            int left = 0, right = size, center;   
            while (left <= right) {
                center = (left + right) / 2;
                if(array[(front + center)%cap] == v) {
                    return center;
                }
                if(array[(front + center)%cap] > v) {
                    left = center + 1;
                } else {
                    right = center -1;
                }
            }
            return -1;
        }
};


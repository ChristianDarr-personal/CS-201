#include "CircularDynamicArray.cpp"
#include <iostream>
#include <cstdlib>
using namespace std;

void testConstructors();
void testIndexOperator();
void testAddDelete();
void testClear();
void testQuickSelect();
void testWCQuickSelect();
void testStableSort();
void testSearches();

template <typename T>
T linearSearch(CircularDynamicArray<T> &arr, T e);
template <typename T>
void print(T arr[], int s);
template <typename T>
void print(CircularDynamicArray<T> &arr);
CircularDynamicArray<int>* randomArray(int size, int range);
CircularDynamicArray<float>* randomArrayFloat(int size, int range);
template <typename T>
CircularDynamicArray<T> insertionSort(CircularDynamicArray<T> arr);

//-----------------------------------------------------------------------------------------

void testConstructors() {
    cout << "+-------------------------------------------+" << endl;
    cout << "Testing default constructor" << endl;
    CircularDynamicArray<int> arr1;
    if (arr1.length() == 0 && arr1.capacity() == 2) cout << "Constructed properly" << endl;
    if (arr1.length() != 0) cout << "ERROR incorrect size: expected 0, got " << arr1.length() << endl;
    if (arr1.capacity() != 2) cout << "ERROR incorrect capacity: expected 2, got " << arr1.capacity() << endl;
    cout << endl;

    cout << "Testing second constructor" << endl;
    CircularDynamicArray<int> arr2(5);
    if (arr1.length() == 0 && arr1.capacity() == 2) cout << "Constructed properly" << endl;
    if (arr1.length() != 0) cout << "ERROR incorrect size: expected 5, got " << arr1.length() << endl;
    if (arr1.capacity() != 2) cout << "ERROR incorrect capacity: expected 5, got " << arr1.capacity() << endl;
    cout << "+-------------------------------------------+" << endl << endl << endl;
}

void testAddDelete() {
    cout << "+-------------------------------------------+" << endl;
    cout << "Testing add end" << endl;
    CircularDynamicArray<int> arr1;
    int compare1[50];
    int value;
    bool success = true;
    for (int i = 0; i < 50; i++) {
        value = rand() % 100;
        arr1.addEnd(value);
        compare1[i] = value;
    }
    cout << "ARRAY:" << endl;
    print(arr1);
    for (int i = 0; i < 50; i++)
        success &= (arr1[i] == compare1[i]);
    if (success) cout << "Add end working correctly" << endl;
    else {
        cout << "ERROR: add end not working correctly. Expected:" << endl;
        print(compare1, 50);
        cout << "but got:" << endl;
        print(arr1);
    }
    cout << endl;

    cout << "Testing add front" << endl;
    CircularDynamicArray<int> arr2;
    int compare2[50];
    success = true;
    for (int i = 0; i < 50; i++) {
        value = rand() % 100;
        arr2.addFront(value);
        compare2[49 - i] = value;
    }
    cout << "ARRAY:" << endl;
    print(arr2);
    for (int i = 0; i < 50; i++)
        success &= (arr2[i] == compare2[i]);
    if (success) cout << "Add front working correctly" << endl;
    else {
        cout << "ERROR: add front not working correctly. Expected:" << endl;
        print(compare2, 50);
        cout << "but got:" << endl;
        print(arr2);
    }
    cout << endl;

    cout << "Testing delete end" << endl;
    success = true;
    for (int i = 0; i < 10; i++)
        arr1.delEnd();
    cout << "ARRAY:" << endl;
    print(arr1);
    for (int i = 0; i < 40; i++)
        success &= (arr1[i] == compare1[i]);
    if (success) cout << "Delete end working correctly" << endl;
    else {
        cout << "ERROR: delete end not working correctly. Expected:" << endl;
        print(compare1, 40);
        cout << "but got:" << endl;
        print(arr1);
    }
    cout << endl;

    cout << "Testing delete front" << endl;
    success = true;
    for (int i = 0; i < 10; i++)
        arr2.delFront();
    cout << "ARRAY:" << endl;
    print(arr2);
    for (int i = 0; i < 40; i++)
        success &= (arr2[i] == compare2[i + 10]);
    if (success) cout << "Delete front working correctly" << endl;
    else {
        cout << "ERROR: delete front not working correctly. Expected:" << endl;
        for (int i = 10; i < 50; i++)
            cout << compare2[i] << " ";
        cout << endl;
        cout << "but got:" << endl;
        print(arr2);
    }
    cout << "+-------------------------------------------+" << endl << endl << endl;
}

void testClear() {
    cout << "+-------------------------------------------+" << endl;
    cout << "Testing clear" << endl;
    CircularDynamicArray<int> arr = *(randomArray(50, 100));
    cout << "Created array with " << arr.length() << " random values" << endl;
    arr.clear();
    if (arr.length() == 0 && arr.capacity() == 2) cout << "Array cleared successfully" << endl;
    else {
        cout << "ERROR: array not cleared, printing array:" << endl;
        print(arr);
    }
    cout << "+-------------------------------------------+" << endl << endl << endl;
}

void testQuickSelect() {
    cout << "+-------------------------------------------+" << endl;
    cout << "Testing quick select with ints" << endl;
    CircularDynamicArray<int> arr;
    bool success;
    int successes = 0;
    int k;
    int range = 100;
    int size = 50;
    int trials = 100;
    int select;
    for (int i = 0; i < trials; i++) {
        arr = *(randomArray(size, range));
        k = (rand() % (size - 1)) + 1;
        select = arr.QuickSelect(k);
        arr.stableSort();
        success = select == arr[k - 1];
        if (!success) {
            cout << "ERROR: quickselect did not match up with expected value";
            cout << "Expected " << arr[k - 1] << " but got " << select << endl << endl;
        }
        successes += success ? 1 : 0;
    }
    cout << successes << " successes out of " << trials << " trials" << endl;
    cout << endl;

    cout << "Testing quick select with floats" << endl;
    CircularDynamicArray<float> arr2;
    float select2;
    successes = 0;
    for (int i = 0; i < trials; i++) {
        arr2 = *(randomArrayFloat(size, range));
        k = (rand() % (size - 1)) + 1;
        select2 = arr2.QuickSelect(k);
        arr2.stableSort();
        success = select2 == arr2[k - 1];
        if (!success) {
            cout << "ERROR: quickselect did not match up with expected value";
            cout << "Expected " << arr2[k - 1] << " but got " << select2 << endl << endl;
        }
        successes += success ? 1 : 0;
    }
    cout << successes << " successes out of " << trials << " trials" << endl;
    cout << "+-------------------------------------------+" << endl << endl << endl;
}

void testWCQuickSelect() {
    cout << "+-------------------------------------------+" << endl;
    cout << "Testing worst case quick select with ints" << endl;
    CircularDynamicArray<int> arr;
    bool success;
    int successes = 0;
    int k;
    int range = 100;
    int size = 50;
    int trials = 100;
    int select;
    for (int i = 0; i < trials; i++) {
        arr = *(randomArray(size, range));
        k = (rand() % (size - 1)) + 1;
        select = arr.WCSelect(k);
        arr.stableSort();
        success = select == arr[k - 1];
        // if (!success) {
        //     cout << "ERROR: quickselect did not match up with expected value";
        //     cout << "Expected " << arr[k - 1] << " but got " << select << endl << endl;
        // }
        successes += success ? 1 : 0;
    }
    cout << successes << " successes out of " << trials << " trials" << endl;
    cout << endl;

    cout << "Testing worst case quick select with floats" << endl;
    CircularDynamicArray<float> arr2;
    float select2;
    successes = 0;
    for (int i = 0; i < trials; i++) {
        arr2 = *(randomArrayFloat(size, range));
        k = (rand() % (size - 1)) + 1;
        select2 = arr2.WCSelect(k);
        arr2.stableSort();
        success = select2 == arr2[k - 1];
        // if (!success) {
        //     cout << "ERROR: quickselect did not match up with expected value";
        //     cout << "Expected " << arr2[k - 1] << " but got " << select2 << endl << endl;
        // }
        successes += success ? 1 : 0;
    }
    cout << successes << " successes out of " << trials << " trials" << endl;
    cout << "+-------------------------------------------+" << endl << endl << endl;
}

void testStableSort() {
    cout << "+-------------------------------------------+" << endl;
    cout << "Testing sort with integers" << endl;
    CircularDynamicArray<int> arr1;
    CircularDynamicArray<int> compare1;
    int trials = 100;
    bool success;
    int successes = 0;
    int size = 50;
    int range = 100;
    for (int i = 0; i < trials; i++) {
        success = true;
        arr1 = *(randomArray(size, range));
        compare1 = arr1;
        compare1 = insertionSort(compare1);
        arr1.stableSort();
        for (int j = 0; j < arr1.length(); j++)
            success &= (arr1[j] == compare1[j]);
        if (!success) {
            cout << "ERROR: sort did not match up with expected output." << endl;
            cout << "Expected:" << endl;
            print(compare1);
            cout << "But got:" << endl;
            print(arr1);
            cout << endl;
        }
        successes += success ? 1 : 0;
    }
    cout << successes << " successes out of " << trials << " trials" << endl;
    cout << endl;

    cout << "Testing sort with floats" << endl;
    CircularDynamicArray<float> arr2;
    CircularDynamicArray<float> compare2;
    successes = 0;
    for (int i = 0; i < trials; i++) {
        success = true;
        arr2 = *(randomArrayFloat(size, range));
        compare2 = arr2;
        compare2 = insertionSort(compare2);
        arr2.stableSort();
        for (int j = 0; j < arr2.length(); j++)
            success &= (arr2[j] == compare2[j]);
        if (!success) {
            cout << "ERROR: sort did not match up with expected output." << endl;
            cout << "Expected:" << endl;
            print(compare2);
            cout << "But got:" << endl;
            print(arr2);
            cout << endl;
        }
        successes += success ? 1 : 0;
    }
    cout << successes << " successes out of " << trials << " trials" << endl;
    cout << "+-------------------------------------------+" << endl << endl << endl;
}

void testSearches() {
    cout << "+-------------------------------------------+" << endl;
    cout << "Testing linear search" << endl;
    CircularDynamicArray<int> arr;
    int trials = 100;
    int size = 50;
    int range = 100;
    int value;
    int output;
    int successes = 0;
    for (int i = 0; i < trials; i++) {
        arr = *(randomArray(size, range));
        value = rand() % range;
        output = arr.linearSearch(value);
        if (output != linearSearch<int>(arr, value)) {
            cout << "ERROR: search did not match expected value" << endl;
            cout << "Expected " << linearSearch<int>(arr, value) << " but got " << output << endl;
            cout << "ARRAY:" << endl;
            print(arr);
        }
        else successes++;
    }
    cout << successes << " successes out of " << trials << " trials" << endl;
    cout << endl;

    cout << "Testing binary search" << endl;
    successes = 0;
    for (int i = 0; i < trials; i++) {
        arr = *(randomArray(20, 20));
        value = rand() % 20;
        arr.stableSort();
        output = arr.binSearch(value);
        if (output == arr.linearSearch(value)) successes++;
        else {
            if (arr[output] == arr[arr.linearSearch(value)]) successes++;
            else {
                cout << "ERROR: expected " << arr.linearSearch(value) << " but got " << output << endl;
                cout << "ARRAY:" << endl;
                print(arr);
            }
        }
    }
    cout << successes << " successes out of " << trials << " trials" << endl;
    cout << "+-------------------------------------------+" << endl << endl << endl;
}

template <typename T>
T linearSearch(CircularDynamicArray<T> &arr, T e) {
    for (int i = 0; i < arr.length(); i++)
        if (arr[i] == e) return i;
    return -1;
}

template <typename T>
void print(T arr[], int s) {
    for (int i = 0; i < s; i++)
        cout << arr[i] << " ";
    cout << endl;
}

template <typename T>
void print(CircularDynamicArray<T> &arr) {
    for (int i = 0; i < arr.length(); i++)
        cout << arr[i] << " ";
    cout << endl;
}

CircularDynamicArray<int>* randomArray(int size, int range) {
    CircularDynamicArray<int> *arr = new CircularDynamicArray<int>(size);
    for (int i = 0; i < size; i++)
        (*arr)[i] = rand() % range;
    return arr;
}

CircularDynamicArray<float>* randomArrayFloat(int size, int range) {
    CircularDynamicArray<float> *arr = new CircularDynamicArray<float>(size);
    for (int i = 0; i < size; i++)
        (*arr)[i] = (float) rand() / ((float) RAND_MAX/range);
    return arr;
}

template <typename T>
CircularDynamicArray<T> insertionSort(CircularDynamicArray<T> arr) {
    T temp;
    int min_index;
    for (int i = 0; i < arr.length(); i++) {
        min_index = i;
        for (int j = i; j < arr.length(); j++)
            if (arr[j] < arr[min_index]) min_index = j;
        temp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = temp;
    }
    return arr;
}

int main() {
    testConstructors();
    testAddDelete();
    testClear();
    testQuickSelect();
    testWCQuickSelect();
    testStableSort();
    testSearches();
}

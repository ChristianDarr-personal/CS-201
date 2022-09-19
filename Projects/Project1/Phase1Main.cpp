#include <iostream>
using namespace std;
#include "CircularDynamicArray.cpp"

void foo(CircularDynamicArray<int> x) {
	for (int i=0; i<x.length()/2; i++)
		x[i] = x[x.length()/2+i];
	// X => "6 7 8 9 10 15 19 6 7 8 9 10 15 19 11"	
	for (int i=0; i< x.length();i++) cout << x[i] << " ";  cout << endl;
}

int main(){

	cout << __cplusplus << endl;
	CircularDynamicArray<float> C(10);
	for (int i=0; i< C.length();i++) C[i] = i;
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// C => "0 1 2 3 4 5 6 7 8 9"
	C.delFront();
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 9"
	C.delEnd();
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8"
	C.addEnd(100.0); //error here
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 100"
	C.delFront();
	C.addEnd(200.0);
	// C => "2 3 4 5 6 7 8 100 200"	

	C.addEnd(300.0);
	C.addEnd(400.0);
	// C => "2 3 4 5 6 7 8 100 200 300 400"	

	CircularDynamicArray<int> A,B;
	for(int i=0; i<10;i++) A.addEnd(i);
	B = A;
	A.addEnd(15); A.addEnd(19);
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" 
    for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;

	cout << "Select is " << A.linearSearch(5) << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" Search => 5
	cout << "Select is " << A.binSearch(12) << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" Search => -1
	cout << "Select is " << A.binSearch(15) << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" Search => 10	
	A.addFront(10); 
    for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;

	// A => "10 0 1 2 3 4 5 6 7 8 9 15 19"
	cout << "Select is " << A.linearSearch(5) << endl;
	// A => "10 0 1 2 3 4 5 6 7 8 9 15 19" Search => 6
    for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;
	cout << "Select is " << A.QuickSelect(3) << endl;
    for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;

    // Select => 2	
	cout << "Select is " << A.WCSelect(5) << endl;
	// Select => 15
	A.stableSort();
	// A => "0 1 2 3 4 5 6 7 8 9 10 15 19"
    cout << "problem area" << endl;
    for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;

	A.addEnd(11);
    for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;

    A.addFront(1); 
    for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;

    A.addFront(2); 
    for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;


    A.addFront(3);
    for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;

	cout << "capacity is " << A.capacity() << endl;
	// A => "3 2 1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"	  capacity => 32
    for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;

	A.delFront(); A.delFront();
	// A => "1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"	  capacity => 32
    for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;

	foo(A);
	for (int i=0; i< A.length();i++) cout << A[i] << " ";  cout << endl;
	// A => "1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"
	for (int i=0; i< B.length();i++) cout << B[i] << " ";  cout << endl;
	// B => "0 1 2 3 4 5 6 7 8 9"
}
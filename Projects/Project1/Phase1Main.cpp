#include <iostream>
using namespace std;
#include "CircularDynamicArray.cpp"

void foo(CircularDynamicArray<int> x) {
	for (int i=0; i<x.Length()/2; i++)
		x[i] = x[x.Length()/2+i];
	// X => "5 4 3 2 0 5 5 4 3 2 0 5"	
	for (int i=0; i< X.Length();i++) cout << X[i] << " ";  cout << endl;
}

int main(){
	CircularDynamicArray<float> C(10);
	for (int i=0; i< C.Length();i++) C[i] = i;
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "0 1 2 3 4 5 6 7 8 9"
	C.DelFront();
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 9"
	C.DelEnd();
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8"
	C.AddEnd(100.0);
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 100"


	CircularDynamicArray<int> A,B;
	for(int i=0; i<10;i++) A.AddEnd(i);
	B = A;
	A.AddEnd(15); A.AddEnd(19);
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" 
	cout << "Select is " << A.Select(3) << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" Select => 2
	cout << "Select is " << A.Search(5) << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" Search => 5
	cout << "Select is " << A.BinSearch(12) << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" Search => -11
	A.AddFront(10); 
	// A => "10 0 1 2 3 4 5 6 7 8 9 15 19"
	cout << "Select is " << A.Select(3) << endl;
	// A => "10 0 1 2 3 4 5 6 7 8 9 15 19" Select => 2
	cout << "Select is " << A.Search(5) << endl;
	// A => "10 0 1 2 3 4 5 6 7 8 9 15 19" Search => 6
	A.Sort();
	// A => "0 1 2 3 4 5 6 7 8 9 10 15 19"
	A.AddEnd(11); A.AddFront(1); A.AddFront(2); A.AddFront(3);
	cout << "Capacity is " << A.Capacity() << endl;
	// A => "3 2 1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"	  Capacity => 32
	A.DelFront(); A.DelFront();
	// A => "1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"	  Capacity => 32

	foo(A);
	for (int i=0; i< A.Length();i++) cout << A[i] << " ";  cout << endl;
	// A => "1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"
	for (int i=0; i< B.Length();i++) cout << B[i] << " ";  cout << endl;
	// B => "0 1 2 3 4 5 6 7 8 9"
}
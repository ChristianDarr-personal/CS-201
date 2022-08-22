using namespace std;
#include <iostream>
#include <cstdlib>

template <class T>
T binSearch(T a[], T x, int l, int r)
{
    int c;
    c = (l + r) / 2;
    
    if (l > r) {
        return -1;
    }
    if(a[c] == x) {
        return c;
    } else if(x < a[c]) {
        binSearch(a, x, l, c - 1);
    } else if(x > a[c]){
        binSearch(a, x, c + 1, r);
    }
}

int main(int argc, char *argv[])
{
	#define MAX 100000
	int a[MAX];
	int prev = 0;
	for (int i=0; i<MAX; i++) prev = a[i] = prev + rand()%5;
	int x = atoi(argv[1]);
	int result = binSearch<int>(a, x, 0, MAX-1);
	(result == -1)
		? cout << "Element "<< x <<" is not present in array \n"
		: cout << "Element is present at index " << result << endl;
		
    float b[MAX];
	float p = 0;
	for (int i=0; i<MAX; i++) p = b[i] = p + rand()%5;
	float x2 = atoi(argv[2]);
	result = binSearch<float>(b, x2, 0, MAX-1);
	(result == -1)
		? cout << "Element "<< x2 <<" is not present in array \n"
		: cout << "Element is present at index " << result << endl;	
	return 0;
}
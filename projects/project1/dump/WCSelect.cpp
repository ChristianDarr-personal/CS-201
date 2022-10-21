// C++ implementation of worst case linear time algorithm
// to find k'th smallest element
#include<iostream>
#include<algorithm>
#include<climits>

using namespace std;

int partition(int arr[], int l, int r, int k);

// A simple function to find median of arr[]. This is called
// only for an array of size 5 in this program.
int findMedian(int arr[], int n)
{
	sort(arr, arr+n); // Sort the array
	return arr[n/2]; // Return middle element
}

// Returns k'th smallest element in arr[l..r] in worst case
// linear time. ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT
int selectWC(elmtype* arr, int l, int r, int k){
	if (k > 0 && k <= r - l + 1){
		int n = r-l+1; 
		int i, medianArr[(n+4)/5];
		for (i=0; i<n/5; i++){
			medianArr[i] = findMedian(arr+l+i*5, 5);
        }
		if (i*5 < n){
			medianArr[i] = findMedian(arr+l+i*5, n%5);
			i++;
		}

		if(i == 1){
            medOfMed = median[i - 1];
        } else {
            selectWC(median, 0, i-1, i/2)
        }
		int pos = partition(arr, l, r, medOfMed);

		// If position is same as k
		if (pos-l == k-1){
			return arr[pos];
        }
		if (pos-l > k-1){
			return selectWC(arr, l, pos-1, k);
        }
		return selectWC(arr, pos+1, r, k-pos+l-1);
	}
	return INT_MAX;
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


int partition(elmtype arr, int l, int r, int x)
{
	int i;
	for (i=l; i<r; i++)
		if (arr[i] == x)
		break;
	swap(&arr[i], &arr[r]);

	i = l;
	for (int j = l; j <= r - 1; j++)
	{
		if (arr[j] <= x)
		{
			swap(&arr[i], &arr[j]);
			i++;
		}
	}
	swap(&arr[i], &arr[r]);
	return i;
}

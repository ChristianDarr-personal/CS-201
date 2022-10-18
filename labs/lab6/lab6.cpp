#include <iostream>
#include <cmath>
using namespace std;
#define MAX 50000

int main(){
    double d[MAX], log2 = log(2);
    d[0] = 0;
    d[1] = 1;
    for(int i = 2; i < MAX + 1; i++){
        double sum = 0;
        for(int j = 0; j < i; j++){
            if(d[j] > d[i-(j+1)]){
                sum = sum + d[j] + 1;
            } else{
                sum = sum +d[i-(j+1)] + 1;
            }
        }
        d[i] = sum/i;
        cout << "d[" << i << "] = " << d[i] << "    d[i]/lg i = " << d[i] * log2/log(i) << endl;
    }
}
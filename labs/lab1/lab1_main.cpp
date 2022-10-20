using namespace std;
#include <iostream>

int main(int argc, char *argv[]) {
    
    int n = atoi(argv[1]);
    int z = 0;
    for(int q = 0; q < 7; q++) {
        for (int k=1; k<=n; k+=k) z++;
    std::cout << z << endl;
}
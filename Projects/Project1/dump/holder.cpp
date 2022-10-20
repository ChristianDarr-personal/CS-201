
        // int partition(elmtype* arr, int l, int r, elmtype x){
        //     elmtype temp;
        //     for (int i=l; i < r; i++){
        //         if (arr[i] == x){
        //             break;
        //         }
        //     }
        //     temp = arr[i];
        //     arr[i] = arr[r];
        //     arr[r] = temp;        
        //     i = l;
        //     for (int j = l; j <= r - 1; j++)
        //     {
        //         if (arr[j] <= x)
        //         {
        //             temp = arr[i];
        //             arr[i] = arr[j];
        //             arr[j] = temp;   
        //             i++;
        //         }
        //     }
        //     temp = arr[i];
        //     arr[i] = arr[r];
        //     arr[r] = temp;   
        //     return i;
        // }

        // elmtype selectWC(elmtype* arr, int k, int s, bool pass){
        //     elmtype* medianArr = new elmtype[(s+4)/5];
        //     elmtype pivot;
        //     elmtype medianMed;
        //     int q;
        //     for(q = 0; q < (s/5);q++){
        //         if(pass){
        //             medianArr[q] = medianArrayPass(q*5, 5);
        //         } else {
        //             medianArr[q] = medianArray(arr, q*5, 5);
        //         }
                
        //     }
        //     if(q*5 < s){
        //         if(pass){
        //             medianArr[q] = medianArrayPass(q*5, s%5);
        //         } else {
        //             medianArr[q] = medianArray(arr, q*5, s%5);
        //         }
        //     }
        //     if(s == 1){
        //         pivot = medianArr[0];
        //     } else{
        //         pivot = selectWC(medianArr, (((s+4)/5)/2), ((s+4)/5), false);
        //     }
        //     // cout << "Pivot: " << pivot << endl;
        //     // int pivot = partition(arr, )
        //     elmtype x;
        //     int l = 0, e = 0, g = 0;
        //     elmtype* less = new elmtype[s];
        //     elmtype* greater = new elmtype[s];
        //     for(int i = 0; i < s; i++){
        //         if(pass){
        //             x = arr[(i + front)%cap];
        //         }else {
        //             x = arr[i];
        //         }
        //         if (x<pivot){
        //                 less[l++] = x;
        //         } else if (x == pivot){
        //             e++;
        //         } else{
        //             greater[g++] = x;
        //         }
        //     }
        //     if (k <= l){
        //         return selectWC(less, k, l, false);
        //     }
        //     else if (k <= l + e){
        //         return pivot; 
        //     } else {
        //         return selectWC(greater, k - l - e, g, false);
        //     }
        //     delete[] medianArr;
        // }
        
        // elmtype medianArrayPass(int mod, int s){
        //     int minIndex;
        //     int max = 2147483647;
        //     int count = 0;
        //     elmtype temp;
        //     elmtype* arr = new elmtype[s];
        //     for(int i = 0; i < s; i++){
        //         if((mod + i) >= size){
        //             arr[i] = max;
        //             count++;
        //         }else{
        //             arr[i] = array[(front + mod + i)%cap];
        //         }
        //     }
        //     for (int i = 0; i < s; i++){
        //         minIndex = i;
        //         for (int j = i + 1; j < s; j++){
        //             if (arr[j] < arr[minIndex]){
        //                 minIndex = j;
        //             }
        //         }
        //         temp = arr[minIndex];
        //         arr[minIndex] = arr[i];
        //         arr[i] = temp;
        //     }
        //     elmtype x = arr[s/2];
        //     delete[] arr; 
        //     return x;
        // }
#include<iostream>
#include<omp.h>
#include<ctime>
#include<algorithm>
#include<vector>

using namespace std;

void sequentialBubbleSort(vector<int> &arr){
    int n = arr.size();
    for(int i=0; i<n; i++){
        for(int j=0; j<n-i-1; j++){
            if(arr[j]> arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void parallelBubbleSort(vector<int> & arr){
    int n = arr.size();
    for(int i=0; i<n; i++){
        int swapped=0;
        #pragma omp parallel for
        for(int j=0;j< n-i-1; j++){
            if(arr[j]> arr[j+1]){
                swap(arr[j],arr[j+1]);
                swapped =1;
            }
        }
        if(swapped==0){
            break;
        }
    }
}

int main(){
    int const size = 10000;
    vector<int> data(size);

    srand(time(0));
    for(int i=0; i<size; i++){
        data[i]= rand();
    }

    vector<int> sequentialData = data;
    vector<int> parallelData = data;

    clock_t startSeq = clock();
    sequentialBubbleSort(sequentialData);
    clock_t endSeq = clock();

    double sequentialTime = double(endSeq-startSeq)/ CLOCKS_PER_SEC;

    clock_t startPar = clock();
    parallelBubbleSort(parallelData);
    clock_t endPar = clock();
    double parallelTime = double(endPar- startPar)/CLOCKS_PER_SEC;

    bool ans = is_sorted(sequentialData.begin(), sequentialData.end());

    cout<<"Sequential Bubble sort time: "<<sequentialTime<<endl;
    cout<<"Parallel Bubble sort time: "<<parallelTime<<endl;
    cout<<"Sorting correctly: "<<(ans? "YES": "NO");
}
#include<iostream>
#include<ctime>
#include<vector>
#include<algorithm>
#include<omp.h>
using namespace std;

void merge(vector<int> &arr, int start, int mid, int end){
    int n1= mid-start+1;
    int n2= end-mid;
    vector<int>l(n1),r(n2);
    for(int i=0;i<n1; i++){
        l[i]= arr[start+i];
    }
    for(int j=0; j<n2; j++){
        r[j]= arr[mid+1+j]; 
    }

    int i=0, j=0, k=start;
    while(i<n1 && j<n2){
        if(l[i]<=r[j]){
            arr[k]= l[i];
            i++;
            k++;
        }else{
            arr[k]=r[j];
            j++;
            k++;
        }
    }

    while(i<n1){
        arr[k]=l[i];
        i++;
        k++;
    }
    while(j<n2){
        arr[k]=r[j];
        j++;
        k++;
    }
}

void sequentialMergeSort(vector<int> &arr, int start, int end){
    if(start>=end){
        return;
    }
    int mid = start+ (end-start)/2;

    sequentialMergeSort(arr,start,mid);
    sequentialMergeSort(arr,mid+1,end);
    merge(arr,start,mid,end);
}

void parallelMergeSort(vector<int> &arr, int start, int end ) {
    if(start>=end){
        return;
    }
    int mid = start+(end-start)/2;

    #pragma omp parallel sections
    {
        #pragma omp section
        parallelMergeSort(arr,start,mid);
        #pragma omp section
        parallelMergeSort(arr,mid+1,end);
    }

    merge(arr,start,mid,end);
}

int main(){
    const int size = 1000000;
    vector<int> data(size);
    srand(time(0));
    for(int i=0;i<size; i++){
        data[i] = rand();
    }

    vector<int> sequentialData = data;
    vector<int> parallelData = data;

    clock_t startSeq = clock();
    sequentialMergeSort(sequentialData, 0 , size-1);
    clock_t endSeq = clock();
    double sequentialTime = double(endSeq-startSeq)/CLOCKS_PER_SEC;

    clock_t startPar = clock();
    parallelMergeSort(parallelData,0,size-1);
    clock_t endPar = clock();
    double parallelTime = double(endPar-startPar)/CLOCKS_PER_SEC;

    bool sorted = is_sorted(parallelData.begin(), parallelData.end());

    cout<<"Sequential Merge Sort time: "<< sequentialTime<<endl;
    cout<<"Parallel Merge Sort time: "<< parallelTime<<endl;
    cout<<"Sorted Correctly: "<<(sorted?"Yes":"No");

}
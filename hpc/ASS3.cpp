#include<iostream>
#include<omp.h>
#include <bits/stdc++.h>

using namespace std;

int minVal(int arr[], int n){
    int ans=arr[0];
    #pragma omp parallel for reduction(min: minVal)
    for(int i=0; i<n; i++){
        if(arr[i]<ans) ans= arr[i];
    }
    return ans;
}

int maxVal(int arr[], int n){
    int ans = arr[0];
    #pragma omp parallel for reduction(max: maxVal)
    for(int i=0; i<n; i++){
       if(arr[i]>ans) ans= arr[i];
    }
    return ans;
}

int sum(int arr[], int n){
    int ans = 0;
    #pragma omp parallel for reduction(+: sum)
    for(int i=0; i<n; i++){
        ans+=arr[i];
    }
    return ans;
}

int avg(int sum, int n){
    return sum/n;
}


int main(){
    int n;
    cout<<"Enter the size : ";
    cin>>n;

    int* arr = new int[n];
    cout<<"Enter elements: ";
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }

    cout<<"Minimum value is: "<<minVal(arr,n)<<endl;
    cout<<"Maximum value is: "<<maxVal(arr,n)<<endl;
    int addition =sum(arr,n);
    cout<<"Sumation value is: "<<addition<<endl;
    cout<<"Average value is: "<<avg(addition,n);
}
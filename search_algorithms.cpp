#include <iostream>
#include <vector>
#include <string>
using namespace std;
// this runs in O(n) time complexity because we have a for loop that iterates n times and we have a constant operation inside the for loop
int linear_search(const vector<int> &v, int target){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == target){
            return i;
        }
    }
    return -1;
}

//this function runs in O(log n) time complexity because we divide the vector in half in each iteration
int binary_search(const vector<int> &v, int target){
    int left = 0;
    int right = v.size() -1; // we add the -1 because the size of the vector is 1 more than the last index
    while(left <= right){
        int mid = (left + right) / 2;
        if(v[mid] == target){
            return mid;
        }else if(v[mid] < target){
            left = mid + 1;
        }else{
            right = mid - 1;
        }
    }
    return -1;
}

//well this function is basically the same as the binary search function, but we use recursion instead of a while loop to find the target. 
//This make our function more efficient because we don't have to use a while loop to find the target, we just use a recursive function that calls itself until we find the target
//this function runs in O(log n) time complexity because we divide the vector in half in each recursive call
int recursive_binary_Search(const vector<int> &v, int target, int left, int right){

    if(left > right){
        return -1;
    }
    int mid = (left + right) / 2;
    if(v[mid] == target){
        return mid;
    }else if(v[mid] < target){
        return recursive_binary_Search(v, target, mid + 1, right);
    }else{
        return recursive_binary_Search(v, target, left, mid - 1);
    }
}




int main(){
    vector<int> v = {1, 2, 3, 4, 5};
    int target = 3;
    cout << "Using Linear Search our target is at the index : " << linear_search(v, target) << endl;
    cout << "Using binary Search our target is at the index: " <<binary_search(v, target) << endl;
    cout << "Using recursive binary Search our target is at the index: " << recursive_binary_Search(v, target, 0, v.size() - 1) << endl;
  
    return 0;
}
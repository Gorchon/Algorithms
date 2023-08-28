#include <iostream>
#include <string>
//  Jose María Soto  Vzla A01254831
// we impot the libraries iostream and string to use the functions cout, 
//cin and string and we use the namespace std in order 
using namespace std;

//we define the first function that will return the sum of the numbers from 0 to n iteratively
int sum_iterative(int n){
    int sum = 0;   //we define the variable sum that will be the result of the sum         
    for(int i = 0; i <= n; i++){ //we use a for loop to iterate from 0 to n and add the value of i to the sum, we start with a i value of 0 and we add 1 to i in each iteration
        sum += i; // we add the value of i to the sum
    } // we close the for loop
    return sum; //we return the value of sum
}
//the complex analysis of the iterative function is O(n) because we have a for loop that iterates n times and we have a constant operation inside the for loop
int recursive_sum(int n){ //we define the second function that will return the sum of the numbers from 0 to n recursively
    if(n == 0){ //we define the base case, if n is equal to 0, we return 0 in order to stop the recursion and don't get an infinite loop
        return 0; // here if we return 1 we will get the sum of the numbers from 1 to n, and that is not what we want 
    }else{ //if n is not equal to 0, we return the value of n plus the recursive function with the value of n-1 
        return n + recursive_sum(n-1); // we return the value of n plus the recursive function with the value of n-1
    } // we close the else statement and we go back to the previous recursive function call checking if n is equal to 0
}
//the complex analysis of the recursive function is O(n) because we have a recursive function that calls itself n times and we have a constant operation inside the function
int mathematical_sum(int n){
    return n*(n+1)/2;
}
//the complex analysis of the mathematical function is O(1) because we have a constant operation inside the function
int main() {
    int case_1 = 1;
    int case_2 = 100;
    int case_3 = 1000;
    int case_4 = 7;

    cout << "Testing case 1:" << endl;
    cout << "Iterative sum: " << sum_iterative(case_1) << endl;
    cout << "Recursive sum: " << recursive_sum(case_1) << endl;
    cout << "Mathematical sum: " << mathematical_sum(case_1) << endl;
    cout << endl;

    cout << "Testing case 2:" << endl;
    cout << "Iterative sum: " << sum_iterative(case_2) << endl;
    cout << "Recursive sum: " << recursive_sum(case_2) << endl;
    cout << "Mathematical sum: " << mathematical_sum(case_2) << endl;
    cout << endl;

    cout << "Testing case 3:" << endl;
    cout << "Iterative sum: " << sum_iterative(case_3) << endl;
    cout << "Recursive sum: " << recursive_sum(case_3) << endl;
    cout << "Mathematical sum: " << mathematical_sum(case_3) << endl;
    cout << endl;

    cout << "Testing case 4:" << endl;
    cout << "Iterative sum: " << sum_iterative(case_4) << endl;
    cout << "Recursive sum: " << recursive_sum(case_4) << endl;
    cout << "Mathematical sum: " << mathematical_sum(case_4) << endl;

    return 0;
}
//Jose Maria Soto Vzla August 2023 A01254831
//Sort the data in ascending order with the Insertion method
#include <iostream>
#include <vector>

using namespace std;    

//function to print the vector+
void printVector(vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << "\t";
    }
    cout << endl;
}

//function to sort the vector with the insertion method
/* analysis: basically what we do in the insertion method is 
to compare the value of the take a value in each iteration and 
compare it with the previous value, if the value of the vector 
is greater than the value of the aux variable, we store the value 
of the vector in the next position of the vector in the j variable, 
if the value of the vector is less than the value of the aux variable, 
we store the value of the aux variable in the next position of the vector
 in the j variable. */
// Function to sort the vector with the insertion method
vector<int> insertionSort(const vector<int> &v)
{
    vector<int> sortedVector = v; // Create a copy of the input vector
    int auxiliar_value, j;
    for (int i = 0; i < sortedVector.size(); i++)
    {
        auxiliar_value = sortedVector[i];
        j = i - 1;
        while (j >= 0 && sortedVector[j] > auxiliar_value)
        {
            sortedVector[j + 1] = sortedVector[j];
            j--; // We decrease the value of j by 1 to compare the value of the auxiliar_value with the previous value
        }
        sortedVector[j + 1] = auxiliar_value;   // We store the value of the auxiliar_value in the next position of the vector
    }
    return sortedVector; // Return the sorted vector
}
/* Bassically, what bubleSort does is to check if the first element in the array is less than the second bigger, than the element next to it
if it is the selected element goes to the auxiliar_value, and then changes position with the value next to it. And basically do that until our array 
is totally sorted*/

vector<int> bubleSort(const vector<int> &v)
{
    vector<int> sortedVector = v; // Create a copy of the input vector
    int auxiliar_value, j;
    int n = sortedVector.size();
    for (int i = 0; i < sortedVector.size(); i++) // We start with the first element in the array and compare it with the second element in the array, 
    {
        for (int j = 0; j < n - i - 1; j++)  // here we use j intead of i because we want to compare the first element with the second, and we subtract 1 because we want to compare the last element with the previous one
        {
            if (sortedVector[j] > sortedVector[j + 1]) // If the first element is bigger than the second, we switch them around
            {
                auxiliar_value = sortedVector[j]; // We store the value of the first element in the auxiliar_value
                sortedVector[j] = sortedVector[j + 1]; // We switch the value of the first element with the second
                sortedVector[j + 1] = auxiliar_value; // We switch the value of the second element with the auxiliar_value
            } // We repeat this process until the array is sorted
        } // We repeat this process until the array is sorted
    }
    return sortedVector; // Return the sorted vector
}

//we use the merge function to merge the left and right vectors in order to sort the vector v and return the sorted vector, we use this function in the mergeSort function to sort the vector
void merge(vector<int> & left, vector<int> & right, vector<int> & v)
{
    int leftSize = v.size() / 2;
    int rightSize = v.size() - leftSize;
    int i = 0, l = 0, r = 0;
    while(l < leftSize && r < rightSize) //we use a while loop to compare the values of the left and right vectors and store them in the vector v, we do this in order to check if the values of the left vector are less than the values of the right vector, we meet this condition when the value of the left vector is less than the value of the right vector, if this condition is true, we store the value of the left vector in the vector v, if the condition is false, we store the value of the right vector in the vector v
    {
        if(left[l] < right[r])
        {
            v[i++] = left[l++];
        }
        else
        {
            v[i++] = right[r++];
        }
    }
    while(l < leftSize)
    {
        v[i++] = left[l++];
    }
    while (r < rightSize)
    {
        v[i++] = right[r++];
    }

}
/* Basically what mergesort does is take an unsorted array and using DC sort it. We do this dividing our array into two equal parts each iteration. And we do 
that until we have a remaining of one, once we meet this condition, we use the function "merge()" to merge and sort correctly our array */
void mergeSort(vector<int> & v)
{
    if (v.size() < 2) //base case, BASSICALLY WE CHECK IF THE SIZE OF THE VECTOR IS LESS THAN 2, BECAUSE IF IT IS LESS THAN 2, WE DON'T NEED TO SORT IT, BECAUSE IT IS ALREADY SORTED
    {
        return; 
    }
    int mid = v.size() / 2; //we divide the vector in two equal parts
    vector<int> left(mid); // we create a vector called left that stores the values of the left part of the vector v
    vector<int> right(v.size() - mid); // we create a vector called right that stores the values of the right part of the vector v
    for (int i = 0; i < mid; i++) // we use a for loop to store the values of the left part of the vector v in the vector left
    {
        left[i] = v[i]; // we store the values of the left part of the vector v in the vector left
    }
    for (int i = mid; i < v.size(); i++) // we use a for loop to store the values of the right part of the vector v in the vector right
    {
        right[i - mid] = v[i]; // we store the values of the right part of the vector v in the vector right
    }
    mergeSort(left); // we use recursion to divide the vector left in two equal parts
    mergeSort(right);
    merge(left, right, v);
}
//main function
int main()
{
    vector<int> v1 = { 2, 5, 93, 4, 6, 1, 3};
    vector<int> v2 = {1, 2, 3, 4, 5, 6, 7};
    vector<int> v3 = {7, 6, 5, 4, 3, 2, 1};
    vector<int> v4 = {212, 1, 3, 2, 4, 5, 7, 6};
    cout << "Original vectors, without any modification: \n" << endl;
    printVector(v1);
    printVector(v2);
    printVector(v3);
    printVector(v4);
    
    vector<int> sortedV1 = insertionSort(v1); // Get a sorted copy of v1
    vector<int> sortedV2 = insertionSort(v2); // Get a sorted copy of v2
    vector<int> sortedV3 = insertionSort(v3); // Get a sorted copy of v3
    vector<int> sortedV4 = insertionSort(v4); // Get a sorted copy of v4
    
    cout << "vectors after the insertion Sort Method: \n" << endl;
    printVector(sortedV1);
    printVector(sortedV2);
    printVector(sortedV3);
    printVector(sortedV4);
    cout << "\nInsertion sort runs in O(n) in its best case and runs O(n²)\n in its worst and average cases. The formula is Average-case \ntime complexity = (n - 1)^2 / (2 * n)\n " << endl;
    
    cout << "Buble Sort Method:\n" << endl;
    vector<int> BsortedV1 = bubleSort(v1); // Get a sorted copy of v1
    vector<int> BsortedV2 = bubleSort(v2); // Get a sorted copy of v2
    vector<int> BsortedV3 = bubleSort(v3); // Get a sorted copy of v3
    vector<int> BsortedV4 = bubleSort(v4); // Get a sorted copy of v4
    printVector(BsortedV1);
    printVector(BsortedV2);
    printVector(BsortedV3);
    printVector(BsortedV4);
    cout << "\nBuble sort runs in O(n) in its best case and runs O(n²)\n in its worst and average cases. The formula is Average-case \n " << endl;
    
    cout << "merge Sort Method:\n" << endl;
    mergeSort(v1);
    mergeSort(v2);
    mergeSort(v3);
    mergeSort(v4);
    printVector(v1);
    printVector(v2);
    printVector(v3);
    printVector(v4);
    cout << "\nMerge sort runs in O(n log n) in its best, worst and average cases.\n recursively divide array in 2, sort it, and re-combine it\n Basically it takes this time because in each step the array is divided into two halves, this division takes o(log n), and the merge part takes o(n), so this algorithm takes o(n log n)\n" << endl;
    //end of the program, we return 0 to indicate that the program ended successfully
    return 0;
}


// Path: Class_algorithms /sort_algorithms.cpp              
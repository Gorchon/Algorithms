// Purpose: To sort the binnacle file by the month number including the day number and the hour number
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <string> 
#include <map> 

using namespace std;

// Struct to hold the original string and its month number
struct combined {
    string original; // we need original to hold the original string, because we need to print the original string in the output file 
    int monthNum;
    int dayNum;
    int hourNum;
};
 // // // Function to sort the vector with the quicksort method
// void quicksort(vector<combined>& a, int l, int r) {
//     if (l < r) {
//         int pivot = a[r].monthNum;
//         int i = l - 1;
//         for (int j = l; j < r; j++) {
//             if (a[j].monthNum < pivot || (a[j].monthNum == pivot && a[j].dayNum <= a[r].dayNum)) {
//                 i++;
//                 swap(a[i], a[j]);
//             }
//         }
//         swap(a[i + 1], a[r]);
//         int p = i + 1;
//         quicksort(a, l, p - 1);
//         quicksort(a, p + 1, r);
//     }
// 
// this "||" is the or operator, so if the month number is the same, it will compare the day number, and if the day number is the same, it will compare the hour number if we use && instead of || it will only compare the month number and the day number, and if we use || instead of && it will only compare the month number and the hour number to compare the day number and the hour number we need to use && because we want to compare the day number and the hour number at the same time, if we use || it will only compare the day number and the hour number if the month number is the same, but we want to compare the day number and the hour number even if the month number is different, so we need to use && instead of ||
// now we create a quicksort funtion that will sort the vector of structs by the month number including the day number and the hour number
// to ensure that the hour number is included in the sorting we need to add a new variable to the struct that will hold the hour number, and we need to add a new condition to the if statement that will compare the hour number if the month number and the day number are the same, we can do it like this 
// if (a[j].monthNum < pivot || (a[j].monthNum == pivot && a[j].dayNum <= a[r].dayNum) || (a[j].monthNum == pivot && a[j].dayNum == a[r].dayNum && a[j].hourNum <= a[r].hourNum)) {

void quicksort(vector<combined>& a, int l, int r) {
    if (l < r) {
        int pivot = a[r].monthNum;
        int i = l - 1;
        for (int j = l; j < r; j++) {
            if (a[j].monthNum < pivot || (a[j].monthNum == pivot && a[j].dayNum <= a[r].dayNum) || (a[j].monthNum == pivot && a[j].dayNum == a[r].dayNum && a[j].hourNum <= a[r].hourNum)) {
                i++;
                //here we swap the original string, the month number, the day number and the hour number
                swap(a[i], a[j]);  
            }
        }
        swap(a[i + 1], a[r]);
        int p = i + 1;
        quicksort(a, l, p - 1);
        quicksort(a, p + 1, r);
    }
}




int main() {
    
    vector<string> v;

    ifstream inputfile("bitacora.txt");

    if (!inputfile) {
        cerr << "Error opening the file " << endl;
        return 0;
    }

    string entry;
    while (getline(inputfile, entry)) { // the syntax is getline(file, string) it will read the file line by line and it will store the line in the string
        v.push_back(entry);
    }

    inputfile.close();

    map<string, int> monthToNum;
    monthToNum["Jan"] = 1;
    monthToNum["Feb"] = 2;
    monthToNum["Mar"] = 3;
    monthToNum["Apr"] = 4;
    monthToNum["May"] = 5;
    monthToNum["Jun"] = 6;
    monthToNum["Jul"] = 7;
    monthToNum["Aug"] = 8;
    monthToNum["Sep"] = 9;
    monthToNum["Oct"] = 10;
    monthToNum["Nov"] = 11;
    monthToNum["Dec"] = 12;



    vector<combined> stringsWithMonths;

    for (int i = 0; i < v.size(); i++) { // this loop will go through the vector of strings and will create a new vector of structs
        string str = v[i];

        string month, dayy, hour ;

        stringstream SS(str); // we create a stringstream called SS and we store the string str in it, we call it ss because it is a convention to call stringstreams ss
        SS >> month >> dayy >> hour; // we use the stringstream to separate the month and the day from the rest of the string, if we want to do it with the hour we can use the monthme method like this SS >> month >> dayy >> hour;

        int monthNumber = monthToNum[month]; // we use the map to convert the month to a number
        int dayNumber = atoi(dayy.c_str()); // the .c_str() that we are using here is for example we have day = "12:" and we want to convert it to an int, we can't use atoi(day) because atoi only works with c strings, so we need to convert the string to a c string, and we can do it with the .c_str() method, so we use atoi(day.c_str()) and it will convert the string to a c string and then it will convert the c string to an int the c string would look like this {'1', '2', ':', '\0'} the '\0' is the null character and it is used to indicate the end of the string, so if we want to convert a string to a c string we need to add the null character at the end of the string, but we don't need to do it manually because the .c_str() method does it automatically
        //now we do it for the hour in the hour we only want the first two numbers so we use the substr method, but wee nee it as a int so we use the atoi method to convert it to int 
        string hourNumberString = hour.substr(0, 2); // we get the first two numbers of the hour string the syntax is string.substr(starting index, number of characters to get, so for example if the hour string is 12:34:56 and we want to get the first two numbers we use hour.substr(0, 2) and it will return 12
        int hourNumber = atoi(hourNumberString.c_str()); //atoi means ascii to integer bassically it converts a string to an int, is say ascii because it was used to convert ascii characters to integers so that they could be used in arithmetic operations, and .c_str() means convert the string to a c string, a c string is a string that is stored as an array of characters, so for example if we have the string "hello" and we convert it to a c string it will be stored as an array of characters like this {'h', 'e', 'l', 'l', 'o', '\0'} the '\0' is the null character and it is used to indicate the end of the string, so if we want to convert a string to a c string we need to add the null character at the end of the string, but we don't need to do it manually because the .c_str() method does it automatically


        combined stringWithMonth; // create a new struct to hold the original string and its month number
        stringWithMonth.original = str; //str here represents the original string that we are reading from the fil, so for example if we are reading the first line of the file, str will be equal to "Jan  1 00:00:00 localhost sshd[1789]: Failed password for root from
        stringWithMonth.monthNum = monthNumber;
        stringWithMonth.dayNum = dayNumber;
        stringWithMonth.hourNum = hourNumber;

        stringsWithMonths.push_back(stringWithMonth);

        //we do all of this in order to sort the vector of strings by the month number, so we need to create a new vector of structs that will hold the original string and its month number, and then we can sort the vector of structs by the month number, and then we can create a new file with the sorted data
    }

    //now we want to use quicksort to sort the vector of structs by the month number including the day number and the hour number
    quicksort(stringsWithMonths, 0, stringsWithMonths.size() - 1); // we use the quicksort function to sort the vector of structs by the month number including the day number and the hour number

    //generate a new file with the sorted data
    ofstream outputfile("sorted_bitacora.txt");
    for (int i = 0; i < stringsWithMonths.size(); i++) {
        outputfile << stringsWithMonths[i].original << endl;
    }
    outputfile.close(); // we close it in order to save the changes



    return 0;
}



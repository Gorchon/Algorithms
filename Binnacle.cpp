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
    string original;
    int monthNum;
    int dayNum;
    int hourNum;
};
// // Function to sort the vector with the quicksort method
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
// this "||" is the or operator, so if the month number is the same, it will compare the day number, and if the day number is the same, it will compare the hour number
// now we create a quicksort funtion that will sort the vector of structs by the month number including the day number and the hour number
void quicksort(vector<combined>& a, int l, int r) {
    if (l < r) {
        int pivot = a[r].monthNum;
        int i = l - 1;
        for (int j = l; j < r; j++) {
            if (a[j].monthNum < pivot || (a[j].monthNum == pivot && a[j].dayNum <= a[r].dayNum) || (a[j].monthNum == pivot && a[j].dayNum == a[r].dayNum && a[j].hourNum <= a[r].hourNum)) {
                i++;
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
    while (getline(inputfile, entry)) {
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

        stringstream SS(str);
        SS >> month >> dayy >> hour; // we use the stringstream to separate the month and the day from the rest of the string, if we want to do it with the hour we can use the monthme method like this SS >> month >> dayy >> hour;

        int monthNumber = monthToNum[month];
        int dayNumber = atoi(dayy.c_str());
        //now we do it for the hour in the hour we only want the first two numbers so we use the substr method, but wee nee it as a int so we use the atoi method to convert it to int 
        string hourNumberString = hour.substr(0, 2);
        int hourNumber = atoi(hourNumberString.c_str()); //atoi means ascii to integer bassically it converts a string to an int, is say ascii because it was used to convert ascii characters to integers so that they could be used in arithmetic operations


        combined stringWithMonth; // create a new struct to hold the original string and its month number
        stringWithMonth.original = str;
        stringWithMonth.monthNum = monthNumber;
        stringWithMonth.dayNum = dayNumber;
        stringWithMonth.hourNum = hourNumber;

        stringsWithMonths.push_back(stringWithMonth);
    }

    //now we want to use quicksort to sort the vector of structs by the month number including the day number and the hour number
    quicksort(stringsWithMonths, 0, stringsWithMonths.size() - 1); // we use the quicksort function to sort the vector of structs by the month number including the day number and the hour number

    //generate a new file with the sorted data
    ofstream outputfile("sortedBitacora.txt");
    for (int i = 0; i < stringsWithMonths.size(); i++) {
        outputfile << stringsWithMonths[i].original << endl;
    }
    outputfile.close();



    return 0;
}



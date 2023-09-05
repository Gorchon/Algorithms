#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <string> 
#include <map> 
#include <unordered_map>

using namespace std;

struct MergedInfo {
    string original;
    int monthNum;
    int dayNum;
    int hourNum;
};

// this "||" is the or operator, so if the month number is the same, it will compare the day number, and if the day number is the same, it will compare the hour number if we use && instead of || it will only compare the month number and the day number, and if we use || instead of && it will only compare the month number and the hour number to compare the day number and the hour number we need to use && because we want to compare the day number and the hour number at the same time, if we use || it will only compare the day number and the hour number if the month number is the same, but we want to compare the day number and the hour number even if the month number is different, so we need to use && instead of ||
// now we create a quicksort funtion that will sort the vector of structs by the month number including the day number and the hour number
// to ensure that the hour number is included in the sorting we need to add a new variable to the struct that will hold the hour number, and we need to add a new condition to the if statement that will compare the hour number if the month number and the day number are the same, we can do it like this 
// if (a[j].monthNum < pivot || (a[j].monthNum == pivot && a[j].dayNum <= a[r].dayNum) || (a[j].monthNum == pivot && a[j].dayNum == a[r].dayNum && a[j].hourNum <= a[r].hourNum)) {

void quicksort(vector<MergedInfo>& a, int l, int r) {
    if (l < r) {
        int pivotMonth = a[r].monthNum;
        int pivotDay = a[r].dayNum;
        int pivotHour = a[r].hourNum;
        int i = l - 1;
        for (int j = l; j < r; j++) {
            if (a[j].monthNum < pivotMonth || 
                (a[j].monthNum == pivotMonth && a[j].dayNum < pivotDay) || 
                (a[j].monthNum == pivotMonth && a[j].dayNum == pivotDay && a[j].hourNum < pivotHour)) {

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

int binarySearch(const vector<MergedInfo>& a, int l, int r, int targetMonth, int targetDay) {
    while (l <= r) {
        int mid = l + (r - l) / 2; // Calculate the middle index.
        
        // Compare the middle element with the target.
        if (a[mid].monthNum == targetMonth && a[mid].dayNum == targetDay) {
            return mid; // Found a match.
        } else if (a[mid].monthNum < targetMonth || (a[mid].monthNum == targetMonth && a[mid].dayNum < targetDay)) {
            // If the target is greater than the middle element, search in the right half.
            l = mid + 1;
        } else {
            // Otherwise, search in the left half.
            r = mid - 1;
        }
    }
    
    return -1; // Element not found.
}


    int main() {
        // we create a hash table in order to assign a number to each month and then we can compare and sort 
        unordered_map<string, int> months_map;
        months_map["Jan"] = 1;
        months_map["Feb"] = 2;
        months_map["Mar"] = 3;
        months_map["Apr"] = 4;
        months_map["May"] = 5;
        months_map["Jun"] = 6;
        months_map["Jul"] = 7;
        months_map["Aug"] = 8;
        months_map["Sep"] = 9;
        months_map["Oct"] = 10;
        months_map["Nov"] = 11;
        months_map["Dec"] = 12;

        vector<string> data;
        ifstream inputfile("bitacora.txt"); // if we want to open a file we use ifstream, if we want to write in a file we use ofstream
        if (!inputfile) {
            cerr << "Error opening the file " << endl;
            return 0;
        }
        string line; // we create a string called line to store the lines of the file
        while(getline(inputfile, line)){ // we use inputfile to read the file line by line and we store the line in the string line
            data.push_back(line);
        }
        inputfile.close(); // we close the file

        vector<MergedInfo> sorted_data; // we create a vector of structs called data2

        for (int i = 0; i < data.size(); i++){
            string original_line = data[i];  // we create a string called original_line to store the original line of the file
            string month, day, hour; // we create some strings to strore the month, day and hour of the line
            stringstream SS(data[i]); // we create a stringstream called ss to store the line of the file   
            SS >> month >> day >> hour; // we use the stringstream to store the month, day and hour of the line

            int month_num = months_map[month]; // we create an int called month_num to store the number of the month
            int day_num = atoi(day.c_str()); // we create an int called day_num to store the number of the day
            //we want to get the numbers without the ":" so we need to use atoi to convert the string to an int and we need to use c_str() to convert the string to a char, we need to ignore the ":" because we want to compare the numbers and if we don't ignore the ":" it will compare the numbers with the ":" and it will not work
            //no we get the numbers that we want ignoring the ":" and we store them in an int called hour_num, to do this we need to multiply the hours 60*60 times and the minutes 60 times and then we add them together
            int hour_num = atoi(hour.substr(0, 2).c_str()) * 60 * 60 + atoi(hour.substr(3, 2).c_str()) * 60 + atoi(hour.substr(6, 2).c_str());
            MergedInfo c; // we create a struct called c
            c.original = original_line; // we store the original line in the struct
            c.monthNum = month_num; // we store the number of the month in the struct
            c.dayNum = day_num; // we store the number of the day in the struct
            c.hourNum = hour_num; // we store the number of the hour in the struct

            sorted_data.push_back(c); // we push back the struct in the vector of structs
        }
        quicksort(sorted_data, 0, sorted_data.size() - 1); // we call the quicksort function to sort the vector of structs
        //we print the first 10 lines of the sorted vector of structs
        ofstream outputfile("sorted_bitacora.txt"); // we create an ofstream called outputfile to write in the file 
        for (int i = 0; i < sorted_data.size(); i++) {
            outputfile << sorted_data[i].original << endl;
        }
        outputfile.close(); // we close it in order to save the changes

        int targetMonth, targetDay;
        cout << "Enter the month (1-12): ";
        cin >> targetMonth;
        cout << "Enter the day: ";
        cin >> targetDay;

        // Perform binary search to find the entries.
        int resultIndex = binarySearch(sorted_data, 0, sorted_data.size() - 1, targetMonth, targetDay);
        //to cout all the results that match the target we need to use a while loop, but with and if to check if the result is -1, if it is -1 it means that there are no results that match the target
        if (resultIndex == -1) {
            cout << "I cant´t find what you are searching" << endl;
        } else {
            while (resultIndex >= 0 && sorted_data[resultIndex].monthNum == targetMonth && sorted_data[resultIndex].dayNum == targetDay) {
                cout << sorted_data[resultIndex].original << endl;
                resultIndex--;
            }
        }
        return 0;

    }

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

//lee el archivo bitacora.txt y lo guarda en un vector para despues imprimir lsa primeras 10 lineas
int main()
{
    string line;
    vector<string> lines;
    ifstream myfile("bitacora.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))//here getline reads the file line by line, the syntax is getline(file, variable) where file is the file to be read and variable is the variable where the line will be stored and line is the variable where the line will be stored. It works while the file is open and it returns false when the file is over.
        {
            lines.push_back(line); //here we push the line into the vector lines, we push it in a new position each time the loop runs
        }
        myfile.close(); // when the file is over we close it. The file is over when getline returns false
    }
    else
        cout << "Unable to open file \n";
    for (int i = 0; i < 10; i++)
    {
        cout << lines[i] << '\n'; // If we dont put the '\n' the lines will be printed one after the other without spaces because the lines dont have spaces between them but the '\n' adds a new line after each line because it knows that the line is over. Basically it knows when the line is over in the vector lines because the lines are stored in the vector line by line. but we need to add the '\n' to print the lines with spaces between them because if we dont the vector will print the lines one after the other without spaces, it will print them as if they were one line.
    }// now i want to make a new file sorting the lines by date and time
    
    return 0;
}   
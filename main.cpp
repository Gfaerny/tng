#include <fstream>
#include <iostream>
using namespace std;

int main(){
    
    ofstream file;
    file.open("test.txt");

     
    if (!file.is_open())
    {
        cout << "Error in creating file!" << endl;
        return 1;
    }
    cout << "File created successfully." << endl;
    file.close();
    return 0;
}
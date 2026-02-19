#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

// reading a csv file 
void read()
{
    string line;
    ifstream hospital("Hospital data report.csv");
    cout << "\n-----------Patient Details------------" << endl;
    if(hospital.is_open())
    {
        getline(hospital, line);
        while(getline(hospital, line))
        {
            stringstream ss(line);
            string value;
            vector<string> row;
            
            while(getline(ss, value, ','))
            {
                row.push_back(value);
            }

            if(!row.empty())
            {
                cout << "Patient ID :" << row[0] << endl;
                cout << "Patient Name :" << row[1] << endl;
                cout << "Gender :" << row[3] << endl;
                cout << "Current Medication :" << row[7] << endl;
                cout << "Status:" << row[8] << endl;
                cout << "Payment Status:" << row[9] << endl;
            }
        }
        hospital.close();
    }
    else
        cout << "The file is not open." << endl;
    cout << "The file is read successfully." << endl;
}

int main()
{

    // Creating a csv file 
   /*ofstream hospital("Hospital data report.csv");

    if(hospital.is_open())
    {
        hospital << "Patient ID, Patient Name, DOB, Gender, Blood Type, Emergency contact, Admission Date, Current medication, Stauts, Payment Status" << endl;
        hospital.close();
        cout << "The file is created." << endl;
    }
    else
        cout << "The csv file cannot be open" << endl;
        
    */
    read();
}
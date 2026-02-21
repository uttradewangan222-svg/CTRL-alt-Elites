#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

class patient
{
    private :
        string name;
        string bt;
        string contact;
        string medication;

    public :
        string id;
        string dob;
        string gender;
        string admit;
        string status;
        string payment;

        // A Destructor which destroys the Object when it goes out of scope.
        ~patient()
        {
            cout << "The object is destroyed. " << endl;
        }

        // Take all info from user and stores it in csv file.
        void info()
        {
            cout << "-----------Please enter the INFO of patient.--------------" << endl;
            cout << "Patient ID : " ;
            getline(cin, id);
            cout << "Patient Name : " ;
            getline(cin, name);
            cout << "Date of Birth : " ;
            getline(cin, dob);
            cout << "Sex : " ;
            getline(cin, gender);
            cout << "Blood Type  : " ;
            getline(cin, bt);
            cout << "Current Medication : " ;
            getline(cin, medication);
            cout << "Admission Date : " ;
            getline(cin, admit);
            cout << "Contact Details : " ;
            getline(cin, contact);
            cout << "Status : ";
            getline(cin, status);
            cout << "Payment Status : " ;
            getline(cin, payment);

            ofstream inputs("Hospital data report.csv", ios::app);

            if(inputs.is_open())
            {
                inputs << id<<", "<<name<<", "<<dob<<", "<<gender<<", "<<bt<<", "<<medication<<", "<<admit<<", "<<contact<<", "<<status<<", "<<payment << endl;
                inputs.close();
                cout << "The information is saved." <<endl;
            }
            else
                cout << "The file is not open." << endl;

        }

};

// creating a csv file
void create()
{
    ofstream hospital("Hospital data report.csv");

    if(hospital.is_open())
    {
        hospital << "Patient ID, Patient Name, DOB, Gender, Blood Type, Emergency contact, Admission Date, Current medication, Stauts, Payment Status" << endl;
        hospital.close();
        cout << "The file is created." << endl;
    }
    else
        cout << "The csv file cannot be open" << endl;

}

// reading a csv file
void read(string patient_id)
{
    patient p;
    string line;
    bool found = false;


    ifstream hospital("Hospital data report.csv");
    cout << "\n-----------Patient Details------------" << endl;
    if(hospital.is_open())
    {
        while(getline(hospital, line))
        {
            stringstream ss(line);  // getline se hospital me jo data hai uske 1 line ko line variable me store karega. while loop end of file tak chalega.
            string value;                   // ss variable me vo line variable store hoga
            vector<string> row;

            while(getline(ss, value,','))
            {
                row.push_back(value);  // iss while loop me ss string variable se comma seperated strings ko value variable me store karega .
                                                        // loop ends when ss string ends
            }
            if(patient_id==row[0])   // check  id required
            {
                    if(!row.empty())
                    {
                        cout << "Patient ID :" << row[0] << endl;       // prints all info
                        cout << "Patient Name :" << row[1] << endl;
                        cout << "Gender :" << row[3] << endl;
                        cout << "Current Medication :" << row[7] << endl;
                        cout << "Status:" << row[8] << endl;
                        cout << "Payment Status:" << row[9] << endl;
                    }
                    found=true;  // mila to yahi se loop break karke bahar ayega nhi to end tak chalega
                    break;
            }
        }
        if(found=false)
        {
                cout << "Patient not found." << endl;
        }
        hospital.close();
        cout << "The file is read successfully." << endl;
    }
    else
        cout << "The file is not open." << endl;
}

// creating object to store data in csv table
void  patient_entry()
{
    patient p1;
    p1.info();
}

int main()
{
    //create();
    patient_entry();
   // cout << user1.payment << endl;
    //read("sds");
}

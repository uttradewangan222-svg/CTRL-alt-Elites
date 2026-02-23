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
        if(found==false)
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

void updatePatient(string patient_id)
{
    ifstream file("Hospital data report.csv");
    ofstream temp("temp.csv");

    string line;
    bool updated = false;

    if (!file.is_open() || !temp.is_open())
    {
        cout << "Error opening file.\n";
        return;
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        vector<string> row;
        string value;

        while (getline(ss, value, ','))
            row.push_back(value);

        if (row.size() < 10)
        {
            temp << line << endl;
            continue;
        }

        if (row[0] == patient_id)
        {
            cout << "Updating Patient ID: " << patient_id << endl;

            cout << "Enter new Status: ";
            getline(cin, row[8]);

            cout << "Enter new Payment Status: ";
            getline(cin, row[9]);

            updated = true;
        }

        temp << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << ","
             << row[4] << "," << row[5] << "," << row[6] << "," << row[7] << ","
             << row[8] << "," << row[9] << endl;
    }

    file.close();
    temp.close();

    remove("Hospital data report.csv");
    rename("temp.csv", "Hospital data report.csv");

    if (updated)
        cout << "Record updated successfully.\n";
    else
        cout << "Patient ID not found.\n";
}

void deletePatient(string patient_id)
{
    ifstream file("Hospital data report.csv");
    ofstream temp("temp.csv");

    string line;
    bool deleted = false;

    if (!file.is_open() || !temp.is_open())
    {
        cout << "Error opening file.\n";
        return;
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        string id;
        getline(ss, id, ',');

        if (id == patient_id)
        {
            deleted = true;
            continue; // Skip this row → deletes it
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    remove("Hospital data report.csv");
    rename("temp.csv", "Hospital data report.csv");

    if (deleted)
        cout << "Record deleted successfully.\n";
    else
        cout << "Patient ID not found.\n";
}

int main()
{
    //create();
    patient_entry();
   // cout << user1.payment << endl;
    //read("sds");
    int choice;
    string pid;

    while (true)
    {
        cout << "1. New Patient Entry\n";
        cout << "2. Read/Search Patient\n";
        cout << "3. Update Patient Record\n";
        cout << "4. Delete Patient Record\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();  // required for getline()

        switch (choice)
        {
            case 1:
                patient_entry();
                break;

            case 2:
                cout << "Enter Patient ID: ";
                getline(cin, pid);
                read(pid);
                break;

            case 3:
                cout << "Enter Patient ID to update: ";
                getline(cin, pid);
                updatePatient(pid);
                break;

            case 4:
                cout << "Enter Patient ID to delete: ";
                getline(cin, pid);
                deletePatient(pid);
                break;

            case 5:
                cout << "Exiting program...\n";
                return 0;   // exits the menu() function

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}


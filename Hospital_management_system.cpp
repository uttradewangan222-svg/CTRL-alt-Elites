#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class patient
{
private:
    string name;
    string bt;
    string contact;
    string medication;

public:
    string id;
    string dob;
    string gender;
    string admit;
    string status;
    string payment;

    void info()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "-----------Please enter the INFO of patient--------------\n";
        cout << "Patient ID: ";
        getline(cin, id);
        cout << "Patient Name: ";
        getline(cin, name);
        cout << "Date of Birth: ";
        getline(cin, dob);
        cout << "Sex: ";
        getline(cin, gender);
        cout << "Blood Type: ";
        getline(cin, bt);
        cout << "Current Medication: ";
        getline(cin, medication);
        cout << "Admission Date: ";
        getline(cin, admit);
        cout << "Contact Details: ";
        getline(cin, contact);
        cout << "Status: ";
        getline(cin, status);
        cout << "Payment Status: ";
        getline(cin, payment);

        ofstream inputs("Hospital data report.csv", ios::app);
        if (inputs.is_open())
        {
            inputs << id << "," << name << "," << dob << "," << gender << ","
                   << bt << "," << medication << "," << admit << ","
                   << contact << "," << status << "," << payment << "\n";

            inputs.close();
            cout << "The information is saved.\n";
        }
        else
        {
            cout << "The file is not open.\n";
        }
    }
};

// Create CSV File
void create()
{
    ofstream hospital("Hospital data report.csv");
    if (hospital.is_open())
    {
        hospital << "PatientID,Name,DOB,Gender,BloodType,Medication,Admission,Contact,Status,Payment\n";
        cout << "The file is created.\n";
    }
    else
        cout << "The csv file cannot be opened\n";
}

// READ PATIENT
void read(string patient_id)
{
    ifstream hospital("Hospital data report.csv");
    string line;
    bool found = false;

    if (!hospital.is_open())
    {
        cout << "File not open.\n";
        return;
    }

    getline(hospital, line); // skip header

    while (getline(hospital, line))
    {
        stringstream ss(line);
        vector<string> row;
        string value;

        while (getline(ss, value, ','))
            row.push_back(value);

        if (row.size() < 10) continue;

        if (row[0] == patient_id)
        {
            cout << "\n---------- Patient Details ----------\n";
            cout << "Patient ID: " << row[0] << endl;
            cout << "Patient Name: " << row[1] << endl;
            cout << "Gender: " << row[3] << endl;
            cout << "Current Medication: " << row[5] << endl;
            cout << "Status: " << row[8] << endl;
            cout << "Payment Status: " << row[9] << endl;

            found = true;
            break;
        }
    }

    if (!found)
        cout << "Patient not found.\n";
}

// UPDATE PATIENT
void updatePatient(string patient_id)
{
    ifstream file("Hospital data report.csv");
    ofstream temp("temp.csv");

    string line;
    bool updated = false;

    if (!file.is_open() || !temp.is_open())
    {
        cout << "Error opening files.\n";
        return;
    }

    getline(file, line);
    temp << line << endl; // copy header

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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

// DELETE PATIENT
void deletePatient(string patient_id)
{
    ifstream file("Hospital data report.csv");
    ofstream temp("temp.csv");

    string line;
    bool deleted = false;

    if (!file.is_open() || !temp.is_open())
    {
        cout << "File error.\n";
        return;
    }

    getline(file, line); // header
    temp << line << endl;

    while (getline(file, line))
    {
        stringstream ss(line);
        string id;
        getline(ss, id, ',');

        if (id == patient_id)
        {
            deleted = true;
            continue;
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
    int choice;
    string pid;
    string pass;
    cout << "\n\n\t\tHOSPITAL MANAGEMENT SYSTEM LOGIN\n";
    cout << "\t\tEnter Password: ";
    cin >> pass;

    if (pass == "12345")
    {
       cout << "\nAccess Granted!\n";
        while (true)
    {
        cout << "\n1. New Patient Entry\n";
        cout << "2. Read/Search Patient\n";
        cout << "3. Update Patient Record\n";
        cout << "4. Delete Patient Record\n";
        cout << "5. Create File\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            patient p;
            p.info();
            break;
        }
        case 2:
            cin.ignore();
            cout << "Enter Patient ID: ";
            getline(cin, pid);
            read(pid);
            break;

        case 3:
            cin.ignore();
            cout << "Enter Patient ID to update: ";
            getline(cin, pid);
            updatePatient(pid);
            break;

        case 4:
            cin.ignore();
            cout << "Enter Patient ID to delete: ";
            getline(cin, pid);
            deletePatient(pid);
            break;

        case 5:
            create();
            break;

        case 6:
            cout << "Exiting program...\n";
            return 0;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
    }    
    else
    {
        cout << "\nWrong Password!\n";
        exit(0);
    }


   
}

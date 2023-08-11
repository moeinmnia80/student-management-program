
#include <iostream>
#include <conio.h> // for : getch
#include <fstream> // for : file
// #include <stdlib.h>
// #include <sstream> 
#include <ctime> // for : time
#include <algorithm> // for std::sort
#include <vector> //for : vector

using namespace std;

class student
{
private:
    string name, last_name, student_number, entring_year, Field_of_Study, date, ttime, Date, Time;
    long long int contact_no;
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";

    
public:
    void menu();
    void insert();
    void displaylastname();
    void displaydate_time();
    void modify();
    void search();
    void deleted();
    void displaytype();
};
// Project Menu
void student::menu()
{
menustart:
    int choice;
    char x;
    system("cls");
    cout << "\t\t\t-----------------------------" << endl;
    cout << "\t\t\t| STUDENT MANAGEMENT SYSTEM |" << endl;
    cout << "\t\t\t-----------------------------" << endl;
    cout << "\t\t\t 1. Add" << endl;
    cout << "\t\t\t 2. Delete" << endl;
    cout << "\t\t\t 3. Search" << endl;
    cout << "\t\t\t 4. Edit" << endl;
    cout << "\t\t\t 5. Print All" << endl;
    cout << "\t\t\t 6. Exit\n"
        << endl;
    cout << "\t\t\t............................" << endl;
    cout << "\t\t\tChoose Options:[1/2/3/4/5/6]" << endl;
    cout << "\t\t\t............................" << endl;
    cout << YELLOW << " Enter Your Choose: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        do
        {
            insert();
            cout << "\n\n\t\t\t Add Another Student Record (Y, N) : ";
            cin >> x;
        } while (x == 'y' || x == 'Y');
        break;
    case 2:
        deleted();
        break;
    case 3:
        search();
        break;
    case 4:
        modify();
        break;
    case 5:
        displaytype();
        break;
    case 6:
        cout << "\n\t\t\t Program Is Exit";
        exit(0);
    default:
        cout << "\n\n\t\t\t Invalid Choice... Please Try Again...";
    }
    cout <<  "\n Press Enter for Exit ...";
    getch();
    goto menustart;
}
void student::insert() // Add student details
{
    int student_no = 0;
    system("cls");
    fstream file("studentRecord.txt");
    vector<vector<string>> studentRecords;
    string line;

    while (getline(file, line)) {
        vector<string> parts;
        size_t startPos = 0;
        size_t endPos = line.find(' ');
        while (endPos != string::npos) {
            parts.push_back(line.substr(startPos, endPos - startPos));
            startPos = endPos + 1;
            endPos = line.find(' ', startPos);
        }
        parts.push_back(line.substr(startPos)); 
        studentRecords.push_back(parts);
    }
    
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Add Student Details ---------------------------------------------" << endl;
    cout << "\n\t\t\tEnter Name: ";
    cin >> name;
    cout << "\t\t\tEnter Last Name: ";
    cin >> last_name;
    cout << "\t\t\tEnter Student Number: ";
    student_number_again:
        cin >> student_number;
        for (const vector<string>& record : studentRecords) {
            if(student_number == record[3]){
                cout << RED << "\t\t\t" << "This  " << student_number << "  Student Number before has taken !!!";
            }else{
                goto student_number_again;
            }
        }
        
    cout << "\t\t\tEntering Year: ";
    cin >> entring_year;
    cout << "\t\t\tField of Study: ";
    cin >> Field_of_Study;
    contact:
        cout << "\t\t\tEnter Contact No(9639xxxxxx): ";
        cin >> contact_no;
        if (contact_no < 1000000000 || contact_no > 9999999999)
        {
            cout << RED << "\t\t\t Please Enter Only 10 Digits..." << endl;
            goto contact;
        }

    time_t now;
    struct tm nowLocal;
    now = time(NULL); // get the the time of os
    nowLocal=*localtime(&now);

    cin.get();

    int dd = nowLocal.tm_mday;
    int mm = nowLocal.tm_mon+1;
    int yy = nowLocal.tm_year+1900;
    int hour = nowLocal.tm_hour;
    int min = nowLocal.tm_min;
    int sec = nowLocal.tm_sec;
    
    string date = std::to_string(dd) + '/' + std::to_string(mm) + '/' + std::to_string(yy);
    string ttime = std::to_string(hour) + ':' + std::to_string(min) + ':' + std::to_string(sec);
    string Date = "Date:";
    string Time = "Time:";

    cout << "\t\t\t" << Date << date << std::endl;
    cout << "\t\t\t" << Time << ttime << std::endl;


    file.open("studentRecord.txt", ios::app | ios::out);
    file << " " << name << " " << last_name << " " << student_number << " " << entring_year << " " << Field_of_Study << " " << contact_no << " " << 
    Date << " " << date << " " << Time << " " << ttime << " " << student_no + 1 << "\n";
    file.close();
    
}
void student::displaytype(){
    system("cls");
    int choice;
    char x;
    system("cls");
    cout << "\t\t\t-----------------------------" << endl;
    cout << "\t\t\t| SORT WITH ... |" << endl;
    cout << "\t\t\t-----------------------------" << endl;
    cout << "\t\t\t 1. Last Name" << endl;
    cout << "\t\t\t 2. Date & Time" << endl;
    cout << "\t\t\t 3. Exit\n"
         << endl;

    cout << "\t\t\t............................" << endl;
    cout << "\t\t\tChoose Options:[1/2/3]" << endl;
    cout << "\t\t\t............................" << endl;
    cout << YELLOW << " Enter Your Choose: ";
    cin >> choice;
    switch (choice)
    {
        case 1:
            displaylastname();
            break;
        case 2:
            displaydate_time();
            break;
        case 3: 
            menu();
            break;
    }
}
bool compareByLastName(const vector<string>& record1, const vector<string>& record2) {
    return record1[2] < record2[2];
}
void student::displaylastname() // Display data of students sorted by last name
{
    system("cls");
    cout << "\n-----------------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------------ Student Record Table -------------------------------------------------" << endl;
    vector<vector<string>> studentRecords;
    ifstream file("studentRecord.txt");
    string line;

    while (getline(file, line)) {
        vector<string> parts;
        size_t startPos = 0;
        size_t endPos = line.find(' ');
        while (endPos != string::npos) {
            parts.push_back(line.substr(startPos, endPos - startPos));
            startPos = endPos + 1;
            endPos = line.find(' ', startPos);
        }
        parts.push_back(line.substr(startPos)); 
        studentRecords.push_back(parts);
    }
    sort(studentRecords.begin(), studentRecords.end(), compareByLastName);
    for (const vector<string>& record : studentRecords) {
        cout << "\t\t\t" << "Student No: " << record[11] << endl;
        cout << "\t\t\t" << "Name: " << record[1] << endl;
        cout << "\t\t\t" << "Last Name: " << record[2] << endl;
        cout << "\t\t\t" << "Student Number: " << record[3] << endl;
        cout << "\t\t\t" << "Entering Year: " << record[4] << endl;
        cout << "\t\t\t" << "Field of Study: " << record[5] << endl;
        cout << "\t\t\t" << "Date: " << record[8] << endl;
        cout << "\t\t\t" << "Time: " << record[10] << endl;
        cout << "\t\t\t" << "Contact No: " << record[6] << endl;
        cout << endl << "-----------------------------------------------------------------------";
        cout << endl << endl;
    }
}
bool compareByDateTime(const vector<string>& record1, const vector<string>& record2) {
    // مقایسه تاریخ
    if (record1[8] != record2[8]) {
        return record1[8] < record2[8];
    }

    // در صورت برابری تاریخ، مقایسه ساعت
    if (record1[10] != record2[10]) {
        return record1[10] < record2[10];
    }

    // در صورت برابری تاریخ و ساعت، مقایسه شماره ثبت نامی
    return stoi(record1[11]) < stoi(record2[11]);
}
void student::displaydate_time() // Display data of student
{
    system("cls");
    vector<vector<string>> studentRecords;
    ifstream file("studentRecord.txt");
    string line;

    while (getline(file, line)) {
        vector<string> parts;
        size_t startPos = 0;
        size_t endPos = line.find(' ');
        while (endPos != string::npos) {
            parts.push_back(line.substr(startPos, endPos - startPos));
            startPos = endPos + 1;
            endPos = line.find(' ', startPos);
        }
        parts.push_back(line.substr(startPos));

        studentRecords.push_back(parts);
    }

    // مرتب‌سازی رکوردها بر اساس تاریخ، ساعت، و شماره ثبت نامی
    sort(studentRecords.begin(), studentRecords.end(), compareByDateTime);

    // چاپ رکوردها بعد از مرتب‌سازی، همراه با شماره ثبت نامی
    for (int i = 0; i < studentRecords.size(); ++i) {
        const vector<string>& record = studentRecords[i];
        cout << "Student No: " << record[11] << endl;  // نمایش شماره‌ی ثبت نامی (بعد از مرتب‌سازی)
        cout << "Name: " << record[1] << endl;
        cout << "Last Name: " << record[2] << endl;
        cout << "Student Number: " << record[3] << endl;
        cout << "Entering Year: " << record[4] << endl;
        cout << "Field of Study: " << record[5] << endl;
        cout << "Date: " << record[8] << endl;
        cout << "Time: " << record[10] << endl;
        cout << "Contact No: " << record[6] << endl;
        cout << endl << "-----------------------------------------------------------------------";
        cout << endl << endl;
    }

}
void student::modify() // Modify details of student
{
    system("cls");
    fstream file, file1;
    string studentnumber;
    int found = 0;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Student Modify Details ------------------------------------------" << endl;
    file.open("studentRecord.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\t\tNo Data is Present..";
        file.close();
    }
    else
    {
        cout << "\nEnter Student Number of Students which you want to Modify: ";
        cin >> studentnumber;
        file1.open("record.txt", ios::app | ios::out);
        file >> name >> last_name >> student_number >> entring_year >> Field_of_Study >> contact_no >> Date >> date >> Time >> ttime;
        while (!file.eof())
        {
            if (studentnumber != student_number)
                file1 << " " << name << " " << last_name << " " << student_number << " " << entring_year << " " << Field_of_Study << " " << contact_no << " " << 
                Date << " " << date << " " << Time << " " << ttime << "\n";
            else
            {
                cout << "\n\t\t\tEnter Name: ";
                cin >> name;
                cout << "\t\t\tEnter Last Name: ";
                cin >> last_name;
                cout << "\t\t\tEnter Student Number: ";
                cin >> student_number;
                cout << "\t\t\tEnter Entering Year: ";
                cin >> entring_year;
                cout << "\t\t\tField of Study: ";
                cin >> Field_of_Study;
            contact:
                cout << "\t\t\tEnter Contact No(9639xxxxxx): ";
                cin >> contact_no;
                if (contact_no < 1000000000 || contact_no > 9999999999)
                {
                    cout << "\t\t\t Please Enter Only 10 Digits..." << endl;
                    goto contact;
                }
                cout << "\t\t\tRegestered : " << date << "\n";
                cout << "\t\t\tRegestered Time: " << ttime << "\n";
                file1 << " " << name << " " << last_name << " " << student_number << " " << entring_year << " " << Field_of_Study << " " << contact_no << " " << 
                Date << " " << date << " " << Time << " " << ttime << "\n";
                found++;
            }
            file >> name >> last_name >> student_number >> entring_year >> Field_of_Study >> contact_no >> Date >> date >> Time >> ttime;
        }
        if (found == 0)
        {
            cout << "\n\n\t\t\t Student Student Number Not Found....";
        }
        file1.close();
        file.close();
        remove("studentRecord.txt");
        rename("record.txt", "studentRecord.txt");
    }
}
void student::search() // search data of student
{
    system("cls");
    fstream file;
    int found = 0;
    file.open("studentRecord.txt", ios::in);
    if (!file)
    {
        cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
        cout << "------------------------------------- Student Search Data --------------------------------------------" << endl;
        cout << "\n\t\t\tNo Data is Present... " << endl;
    }
    else
    {
        string studentnumber;
        cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
        cout << "------------------------------------- Student Search Table --------------------------------------------" << endl;
        cout << "\nEnter Student Number of Student which you want to search: ";
        cin >> studentnumber;
        file >> name >> last_name >> student_number >> entring_year >> Field_of_Study >> contact_no >> Date >> date >> Time >> ttime;
        while (!file.eof())
        {
            if (studentnumber == student_number)
            {
                cout << YELLOW << "\n\n\t\t\tName: " << name << "\n";
                cout << YELLOW << "\t\t\tLast Name: " << last_name << "\n";
                cout << YELLOW << "\t\t\tStudent Number: " << student_number << "\n";
                cout << YELLOW << "\t\t\tEntering Year: " << entring_year << "\n";
                cout << YELLOW << "\t\t\tField of Study: " << Field_of_Study << "\n";
                cout << YELLOW << "\t\t\tContact No.: " << contact_no << "\n";
                cout << YELLOW << "\t\t\tRegestered : " << date << "\n";
                cout << YELLOW << "\t\t\tRegestered Time: " << ttime << "\n";
                cout << "\n---------------------------------------------------\n";
                found++;
            }
            file >> name >> last_name >> student_number >> entring_year >> Field_of_Study >> contact_no >> Date >> date >> Time >> ttime;
        }
        if(found == 0){
                cout << "\n\t\t\t Student with Student Number Not Found...." << "\n---------------------------------------------------\n" ;
        }
        file.close();
    }
}
void student::deleted() // ddeleted data of student
{
    system("cls");
    fstream file, file1;
    int found = 0;
    string student_n;
    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Delete Student Details ------------------------------------------" << endl;
    file.open("studentRecord.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\t\tNo Data is Present..";
        file.close();
    }
    else
    {
        cout << "\nEnter Student Number of Student which you want Delete Data: ";
        cin >> student_n;
        file1.open("record.txt", ios::app | ios::out);
        file >> name >> last_name >> student_number >> entring_year >> Field_of_Study >> contact_no >> Date >> date >> Time >> ttime;
        while (!file.eof())
        {
            if (student_n != student_number)
            {
                file1 << " " << name << " " << last_name << " " << student_number << " " << entring_year << " " << Field_of_Study << " " << contact_no << " " << 
                Date << " " << date << " " << Time << " " << ttime << "\n";
            }
            else
            {
                found++;
                cout << YELLOW << "\n\t\t\tSuccessfully Delete Data";
            }
            file >> name >> last_name >> student_number >> entring_year >> Field_of_Study >> contact_no >> Date >> date >> Time >> ttime;
        }
        if (found == 0)
        {
            cout << YELLOW << "\n\t\t\t Student Student Number Not Found....";
        }
        file1.close();
        file.close();
        remove("studentRecord.txt");
        rename("record.txt", "studentRecord.txt");
    }
}
int main()
{
    student project; // object
    project.menu();  //object calling
    return 0;
}





// // مسیر کامل (مسیر مطلق) برای ذخیره فایل
// string filePath = "/home/user/data.txt"
// // ایجاد یک شیء از جنس ofstream برای نوشتن فایل
// ofstream outputFile(filePath)
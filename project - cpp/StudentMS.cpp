
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
    string name, last_name, student_number, entring_year, student_n, Field_of_Study, date, ttime, Date, Time, modified_Field_of_Study
    , modified_last_name, modified_name;
    long long int contact_no;
    int lastStudentNumber;
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";
    const string RESET = "\033[0m";

    
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
void student::menu()
{
    while (true) {
        system("cls"); // Clear the console screen
        int choice;
        char x;
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
        cout << " Enter Your Choose: ";
        cin >> choice;

        switch (choice) {
            case 1:
                do {
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

        cout <<  "\n Press Enter to Continue ...";
        cin.ignore(); // Clear the newline character from the previous input
        cin.get(); // Wait for the user to press Enter
    }
}
bool isValidContactNumber(long long number) {
    return (number >= 1000000000 && number <= 9999999999);
}
void student::insert() // Add student details
{
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

    int maxStudentNumber = 0;
    for (const vector<string>& record : studentRecords) {
        int studentNumber = stoi(record[11]);
        if (studentNumber > maxStudentNumber) {
            maxStudentNumber = studentNumber;
        }
    }

    lastStudentNumber = maxStudentNumber + 1; // Increment to get the next student number
    student_n = to_string(lastStudentNumber);


    cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
    cout << "------------------------------------- Add Student Details ---------------------------------------------" << endl;
    cin.ignore();
    cout << "\n\t\t\tEnter Name: ";
    std::getline(std::cin, modified_name);
    name = modified_name;
    replace(name.begin(), name.end(), ' ', '|');
    cout << "\t\t\tEnter Last Name: ";
    cin.ignore(); // تخلیه newline character از ورودی قبلی
    std::getline(std::cin, modified_last_name);
    last_name = modified_last_name;
    replace(last_name.begin(), last_name.end(), ' ', '|');
    cout << "\t\t\tEnter Student Number: ";
    cin >> student_number;
    for (const vector<string>& record : studentRecords) {
        if(student_number == record[3]){
            cout << RED << "\t\t\t" << "This  " << student_number << "  Student Number before has taken !!!" << RESET << endl;
            cout << "\t\t\tplease enter a new student number: ";
            cin >> student_number;
        }
    }
    cout << GREEN << "\t\t\tValid Student Number" << RESET << endl;
    cout << "\t\t\tEntering Year: ";
    cin >> entring_year;
    cout << "\t\t\tField of Study: ";
    // cin >> Field_of_Study;
    cin.ignore(); // تخلیه newline character از ورودی قبلی
    std::getline(std::cin, modified_Field_of_Study);
    Field_of_Study = modified_Field_of_Study;
    replace(Field_of_Study.begin(), Field_of_Study.end(), ' ', '|');
    do {
        cout << "\t\t\tEnter Contact No(9639xxxxxx): ";
        cin >> contact_no;
        if (!isValidContactNumber(contact_no)) {
            cout << RED << "\t\t\t Please Enter Only 10 Digits..." << RESET <<endl;
        }
    } while (!isValidContactNumber(contact_no));

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
        
    ofstream output("studentRecord.txt", ios::app);

    if (!output.is_open()) {
        cout << RED << "Error opening file for writing!" << RESET << endl;
        return;
    }
    output << " " << name << " " << last_name << " " << student_number << " " << entring_year << " " << Field_of_Study << " " << contact_no << " " << 
    Date << " " << date << " " << Time << " " << ttime << " " << student_n << "\n";
    file.close();
    output.close();
    
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
    cout << " Enter Your Choose: ";
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
        replace(parts[1].begin(), parts[1].end(), '|', ' ');
        replace(parts[2].begin(), parts[2].end(), '|', ' ');
        replace(parts[5].begin(), parts[5].end(), '|', ' ');
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
        replace(parts[1].begin(), parts[1].end(), '|', ' ');
        replace(parts[2].begin(), parts[2].end(), '|', ' ');
        replace(parts[5].begin(), parts[5].end(), '|', ' ');
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
bool isValidContactNumber(const std::string &contact_no) {
    if (contact_no.length() != 10) {
        return false;
    }
    for (char c : contact_no) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}
void student::modify() // modify data of student
{
    system("cls");
    cout << "\n----------------------------------------------------" << endl;
    cout << "------------------ Modify Student -------------------" << endl;

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

    string studentNumber;
    cout << "\n\t\t\tEnter Student Number to Modify: ";
    cin >> studentNumber;

    bool found = false;
    for (vector<string>& record : studentRecords) {
        if (record[3] == studentNumber) {
            found = true;
            cout << "\n\t\t\tStudent No: " << record[11] << endl;
            cin.ignore();
            cout << "\t\t\tEnter new Name: ";
            std::getline(std::cin, record[1]);
            name = record[1];
            replace(record[1].begin(), record[1].end(), ' ', '|');
            cout << "\t\t\tEnter new Last Name: ";
            std::getline(std::cin, record[2]);
            last_name = record[2];
            replace(record[2].begin(), record[2].end(), ' ', '|');
            // cout << "\t\t\tEnter new Student Number: ";
            // cin >> record[3];
            // cin.ignore();
            do {
                cout << "\t\t\tEnter new Student Number: ";
                string paststn = record[3];
                cin >> record[3];
                cin.ignore();

                bool isDuplicate = false;

                // Check for past student number duplication
                for (const vector<string>& record : studentRecords) {
                    if (record[3] == paststn) {
                        isDuplicate = false;
                        cout << YELLOW << "\t\t\tThis Student Number " << record[3] << " is a Repetitious" << RESET << endl;
                        string response;
                        cout << "\t\t\tDo you want to enter a different student number? (yes/no): ";
                        cin >> response;
                        if (response == "no" || "No") {
                            break; // Exit the loop if the user doesn't want to enter a different student number
                        }
                        break;
                    }
                    else if (!isDuplicate)
                    {
                        for (const vector<string>& parts : studentRecords) {
                            if (parts[3] == record[3]) {
                                isDuplicate = true;
                                cout << RED << "\t\t\tThis student number is already in use. Please enter a unique student number." << RESET << endl;
                                break;
                            }
                        }
                    }   
                }

                if (!isDuplicate) {
                    // Continue with the modification process
                    // ... (rest of the code for modifying student information)
                    break; // Exit the loop if the student number is unique
                }
            } while (true);
            cout << "\t\t\tEnter new Entering Year: ";
            cin >> record[4];
            cin.ignore();
            cout << "\t\t\tEnter new Field of Study: ";
            std::getline(std::cin, record[5]);
            Field_of_Study = record[5];
            replace(record[5].begin(), record[5].end(), ' ', '|');
            do {
                std::cout << "\t\t\tEnter new Contact No(9639xxxxxx): ";
                std::cin >> contact_no;

                if (!isValidContactNumber(contact_no)) {
                    std::cout << "\t\t\t Please Enter Only 10 Digits..." << std::endl;
                }
            } while (!isValidContactNumber(contact_no));

            cout << "\t\t\tRegestered : " << record[8] << "\n";
            cout << "\t\t\tRegestered Time: " << record[10] << "\n";

            cout << "\t\t\tModification Successful!" << endl;
            break;
        }
    }

    if (!found) {
        cout << "\t\t\tStudent with Student Number " << studentNumber << " not found!" << endl;
    }

    file.close();

    // Rewrite the modified records back to the file
    ofstream outFile("studentRecord.txt", ios::trunc);
    for (const vector<string>& record : studentRecords) {
        for (const string& field : record) {
            outFile << field << " ";
        }
        outFile << "\n";
    }
    outFile.close();
}
void student::search() // search data of student
{
    system("cls");
    fstream file;
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
        vector<vector<string>> studentRecords;
        string line;
        cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
        cout << "------------------------------------- Student Search Table --------------------------------------------" << endl;
        cout << "\nEnter Student Number of Student which you want to search: ";
        cin >> studentnumber;
        while (getline(file, line)) {
            vector<string> part_s;
            size_t startPos = 0;
            size_t endPos = line.find(' ');
            while (endPos != string::npos) {
                part_s.push_back(line.substr(startPos, endPos - startPos));
                startPos = endPos + 1;
                endPos = line.find(' ', startPos);
            }
            part_s.push_back(line.substr(startPos)); 
            studentRecords.push_back(part_s);
        }

        bool found = false;

        for (const vector<string>& record : studentRecords) {
            if (record[3] == studentnumber) {
                cout << "\n\n\t\t\tStudent No: " << record[11] << "\n";
                cout << "\t\t\tName: " << record[1] << "\n";
                cout << "\t\t\tLast Name: " << record[2] << "\n";
                cout << "\t\t\tStudent Number: " << record[3] << "\n";
                cout << "\t\t\tEntering Year: " << record[4] << "\n";
                cout << "\t\t\tField of Study: " << record[5] << "\n";
                cout << "\t\t\tContact No.: " << record[6] << "\n";
                cout << "\t\t\tRegistered : " << record[8] << "\n";
                cout << "\t\t\tRegistered Time: " << record[10] << "\n";
                cout << "\n---------------------------------------------------\n";
                found = true;
                break; // برای خروج از حلقه بعد از یافتن مورد
            }
        }

        if (!found) {
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
    string studentNumberToDelete;
    vector<vector<string>> studentRecords;
    string line;

    file.open("studentRecord.txt", ios::in);
    if (!file)
    {
        cout << "\n\t\t\tNo Data is Present..";
        file.close();
    }
    else
    {
        cout << "\n-------------------------------------------------------------------------------------------------------" << endl;
        cout << "------------------------------------- Delete Student Details ------------------------------------------" << endl;
        cout << "Enter Student Number of Student which you want to Delete Data: ";
        cin >> student_n;
        
        // Read the existing student records into the vector studentRecords
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
        int maxStudentNumber = 0;
        for (const vector<string>& record : studentRecords) {
            int studentNumber = stoi(record[11]);
            if (studentNumber > maxStudentNumber) {
                maxStudentNumber = studentNumber;
            }
        }

        file1.open("record.txt", ios::app | ios::out);

        // Iterate through the student records and write them to the new file
        for (const vector<string>& record : studentRecords) {
            if (record[3] != student_n) {
                file1 << " " << record[1] << " " << record[2] << " " << record[3] << " " << record[4] << " " << record[5] << " " << record[6] << " " << 
                record[7] << " " << record[8] << " " << record[9] << " " << record[10] << " " << record[11] << "\n";
            } else {
                found++;
                cout << "\n\t\t\tSuccessfully Delete Data";
                int studentNumber = stoi(record[11]);
                for (vector<string>& rec : studentRecords) {
                    int currentStudentNumber = stoi(rec[11]);
                    if (currentStudentNumber > studentNumber) {
                        rec[11] = to_string(currentStudentNumber - 1);
                    }
                }
            }
        }

        if (found == 0) {
            cout << "\n\t\t\tStudent Student Number Not Found....";
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
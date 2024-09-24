#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct STUDENT_DATA
{
	string firstName;
	string lastName;

#ifdef _PRE_RELEASE
	string email;
#endif
};

int main()
{
	// print state 
#ifdef _DEBUG
	cout << "DEBUG MODE" << endl;
#endif

#ifdef _PRE_RELEASE
	cout << "PRE-RELEASE MODE" << endl;
#endif

#ifdef NDEBUG // RELEASE MODE
	cout << "RELEASE MODE" << endl;
#endif
	cout << "===================================" << endl;


	vector <STUDENT_DATA> studentData;

	// Read student data file and store it in a vector

	ifstream file("StudentData.txt");
	if (file.is_open())
	{
		string line;

		while (getline(file, line))
		{
			// parse line string and store it in STUDENT_DATA
			STUDENT_DATA student;
			int pos = line.find(",");
			student.lastName = line.substr(0, pos);
			student.firstName = line.substr(pos + 2); // +2 to skip the space after the coma

			// push back parsed STUDENT_DATA to vector
			studentData.push_back(student);
		}

		file.close();
	}
	else
	{
		cout << "ERROR: cannot open StudentData.txt" << endl;
	}

#ifdef _PRE_RELEASE
	// read from new data file and add info to the student data vector
	ifstream emailFile("StudentData_Emails.txt");
	if (emailFile.is_open())
	{
		string line;
		int i = 0;

		while (getline(emailFile, line))
		{

			STUDENT_DATA tempStudent;
			int pos = line.find(",");
			tempStudent.lastName = line.substr(0, pos);
			int pos2 = line.find(",", pos + 2); // +2 to skip the space after the coma
			tempStudent.firstName = line.substr(pos + 2, pos2 - pos - 2);
			tempStudent.email = line.substr(pos2 + 1); // +1 to skip the coma

			// find the student in the vector and update the email
			for (int i = 0; i < studentData.size(); i++)
			{
				if (studentData[i].firstName == tempStudent.firstName && studentData[i].lastName == tempStudent.lastName)
				{
					studentData[i].email = tempStudent.email;
					break;
				}
			}
		}

		emailFile.close();
	}
	else
	{
		cout << "ERROR: cannot open StudentData_Emails.txt" << endl;
	}
#endif

#ifdef _DEBUG
	// Display student data
	for (int i = 0; i < studentData.size(); i++)
	{
		cout << studentData[i].firstName << " " << studentData[i].lastName;

#ifdef _PRE_RELEASE
		// Only print the email if in pre-release mode
		cout << " " << studentData[i].email;
#endif
		cout << endl;
	}
#endif


	return 1;
}
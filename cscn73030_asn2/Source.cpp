#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct STUDENT_DATA
{
	string firstName;
	string lastName;
};

int main()
{
	// Read student data file and store it in a vector
	vector <STUDENT_DATA> studentData;

	ifstream file("StudentData.txt");
	if (file.is_open())
	{
		string line;

		while (getline(file, line))
		{
			// parse line string and store it in STUDENT_DATA
			STUDENT_DATA student;
			int pos = line.find(",");
			student.firstName = line.substr(0, pos);
			student.lastName = line.substr(pos + 2); // +2 to skip the space after the coma

			// push back parsed STUDENT_DATA to vector
			studentData.push_back(student);
		}

		file.close();
	}
	else
	{
		cout << "ERROR: cannot open file" << endl;
	}

#ifdef _DEBUG
	// Display student data
	for (int i = 0; i < studentData.size(); i++)
	{
		cout << studentData[i].firstName << " " << studentData[i].lastName << endl;
	}
#endif

	return 1;
}
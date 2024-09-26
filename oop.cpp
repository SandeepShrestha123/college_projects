#include<iostream>
#include<fstream>
#define N 2
using namespace std;

class Student{
	private:
		int sid;
		char name[100];
	public:
		void read()
		{
			cout<<"Enter the student's ID: ";
			cin>>sid;
			cout<<"Enter the student's name: ";
			cin>>name;
		}
		int getSid() { return sid; }
		char* getName() { return name; }
};

class Subject: public Student{
	private:
		int ds, oop, mp, maths, stats;

		// Helper function to take marks input in range 0-100
		int inputMarks(const char* subjectName) 
		{
			int marks;
			do {
				cout << "Enter the marks in " << subjectName << " (0 to 100): ";
				cin >> marks;
				if (marks < 0 || marks > 100)
					cout << "Invalid input! Marks should be between 0 and 100.\n";
			} while (marks < 0 || marks > 100);
			return marks;
		}
		
	public:
		void read()
		{
			Student::read();
			ds = inputMarks("Discrete Structure");
			oop = inputMarks("Object Oriented Programming");
			mp = inputMarks("Microprocessor");
			maths = inputMarks("Mathematics");
			stats = inputMarks("Statistics");
		}
		
		// Function to write data to file in text format
		void writeToFile(ofstream &fout)
		{
			fout << "Student ID: " << getSid() << endl;
			fout << "Name: " << getName() << endl;
			fout << "Marks in Discrete Structure: " << ds << endl;
			fout << "Marks in Object Oriented Programming: " << oop << endl;
			fout << "Marks in Microprocessor: " << mp << endl;
			fout << "Marks in Mathematics: " << maths << endl;
			fout << "Marks in Statistics: " << stats << endl;
			fout << "------------------------" << endl;
		}
};

int main()
{
	int n;
	cout<<"1. Add student\n";
	cout<<"Enter your choice: ";
	cin>>n;

	switch(n)
	{
		case 1:
		{
			system("cls");
			ofstream fout("Student.txt", ios::out);  // Open in text mode
			if(fout.is_open())
			{
				for(int i=0;i<N;i++)
				{
					Subject sub;
					cout<<"\nEnter the data for student "<<i+1<<endl;
					sub.read();
					sub.writeToFile(fout);  // Write the data in text format
				}
				fout.close();
				cout<<"Student's data recorded successfully!"<<endl;
			}
			else
			{
				cout<<"Unable to open the file!"<<endl;
			}
			break;
		}
		default:
		{
			cout<<"Invalid choice!!"<<endl;
		}
	}
	return 0;
}

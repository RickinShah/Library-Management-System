
using namespace std;

class Student
{
protected:
	string enroll_no;
	string password;

public:
	void s_login();
	int s_menu();
	void s_issued();
};

int Student::s_menu()
{
	int choice;
loop:
	system("clear");
	cout << "\t\t-------------------\n"
		 << "\t\t YOU ARE LOGGED IN\n"
		 << "\t\t-------------------\n\n";

	cout << "Enter your choice\n\n"
		 << "1. Book List\n"
		 << "2. Search Book\n"
		 << "3. Issued Books\n"
		 << "4. Due Books\n"
		 << "5. Log Out\n\n";
	cout << "Your input: ";
	cin >> choice;
	if (choice > 5)
	{
		cout << "\nPlease enter a valid number.\n";
		system("read");
		goto loop;
	}
	return choice;
}

void Student::s_login()
{
	cout << "\t********** LOGIN **********\n\n";
	cout << "Enrollment No.: ";
	cin >> enroll_no;
	cout << "Password: ";
	cin >> password;
	Loading();

	ifstream r_file;
	string line;
	r_file.open("Student.csv");
	if (!r_file.is_open())
	{
		cerr << "\n\nError while Login to your account.\nPlease try again later\n";
		system("read");
		system("clear");
		exit(0);
	}
	while (getline(r_file, line))
	{
		stringstream s(line);
		getline(s, line, ',');
		if (enroll_no == line)
		{
			getline(s, line, ',');
			if (password == line)
			{
				return;
			}
		}
	}
	cout << "\nUsername and Password combination doesn't match.\nPlease try again.\n";
	system("read");
	system("clear");
	exit(0);
}

void Student::s_issued()
{
	ifstream r_issue, r_student;
	string line, read;

	cout << "\t\t--------------\n"
		 << "\t\t Issued Books\n"
		 << "\t\t--------------\n";

	r_issue.open("Issue.csv");

	string issue;
	if (!r_issue.is_open())
	{
		cerr << "\nUnable to fetch data.\n Please try again later.\n";
		system("read");
		return;
	}

	while (getline(r_issue, issue))
	{
		stringstream s(issue);
		getline(s, issue, ',');
		{
			if (issue == enroll_no)
			{
				getline(s, issue, ',');
				cout << "Book ID: " << issue << "\n";
				getline(s, issue, ',');
				cout << "Book Name: " << issue << "\n";
				getline(s, issue, ',');
				cout << "Book Author: " << issue << "\n";
				getline(s, issue, ',');
				cout << "Issue Date: " << issue << "\n\n";
			}
		}
	}
	system("read");
	system("clear");
	return;
}

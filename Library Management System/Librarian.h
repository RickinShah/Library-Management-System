using namespace std;

class Librarian
{
private:
	string name;
	string ID;
	string password;

public:
	void l_login();
	int l_menu();
};

void Librarian::l_login()
{
	cout << "\t********** LOGIN **********\n\n";
	cout << "Librarian ID: ";
	cin >> ID;
	cout << "Password: ";
	cin >> password;
	Loading();

	ifstream r_file;
	string line;
	r_file.open("Librarian.csv");
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
		if (ID == line)
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

int Librarian::l_menu()
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
		 << "3. Add Book\n"
		 << "4. Remove Book\n"
		 << "5. Issue Book\n"
		 << "6. Return Book\n"
		 << "7. Log Out\n";
	cout << "\nYour input: ";
	cin >> choice;
	if (choice > 7)
	{
		cout << "\nPlease enter a valid number.\n";
		system("read");
		goto loop;
	}
	return choice;
}

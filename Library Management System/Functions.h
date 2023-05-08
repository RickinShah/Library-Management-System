using namespace std;

int main_menu()
{
loop:
	cout << "\t*************** LIBRARY MANAGEMENT SYSTEM ***************\n\n";
	int choice;
	cout << "Choose your option:\n\n";
	cout << "1. Student\n"
		 << "2. Librarian\n"
		 << "3. Close Application\n"
		 << "\nYour input: ";
	cin >> choice;
	if (choice > 3)
	{
		cout << "\nChoose a valid option.\n";
		system("read");
		system("clear");
		goto loop;
	}
	return choice;
}

void Loading()
{
	int i = 0;
	cout << "\n Loading";
	while (i++ < 3)
	{
		cout << "." << flush;
		usleep(300 * 1000);
	}
	system("clear");
}
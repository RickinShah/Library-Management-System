
using namespace std;

class Book : protected Student
{
private:
	string name;
	int ID;
	string author;

public:
	void book_list();
	void add_book();
	void remove_book();
	void search_book();
	void Issue();
	void return_book();
};

void Book::book_list()
{
	cout << "\t\t-------------------------\n"
		 << "\t\t\tBOOK LIST\n"
		 << "\t\t-------------------------\n\n\n";
	ifstream r_file;
	string r_details;
	r_file.open("Books.csv");
	if (!r_file.is_open())
	{
		cerr << "\nUnable to list the books.\nPlease try again later.\n";
		system("read");
		return;
	}
	while (getline(r_file, r_details))
	{
		stringstream s(r_details);
		getline(s, r_details, ',');
		cout << "Book ID: " << r_details << "\n";
		getline(s, r_details, ',');
		cout << "Book Name: " << r_details << "\n";
		getline(s, r_details, ',');
		cout << "Book Author: " << r_details << "\n\n";
	}
	r_file.close();
	system("read");
	system("clear");
}

void Book::search_book()
{
	int choice;
loop:
	cout << "Search book by:\n"
		 << "1. Book ID\n"
		 << "2. Book name and Author name\n"
		 << "3. Go Back\n"
		 << "\nYour input: ";
	cin >> choice;
	Loading();
	system("clear");
	ifstream r_file;
	string line;
	r_file.open("Books.csv");
	if (!r_file.is_open())
	{
		cerr << "\nUnable to search for books.\nPlease try again later.\n";
		system("read");
		return;
	}
	if (choice == 1)
	{
		cout << "Enter the Book ID: ";
		cin >> ID;

		while (getline(r_file, line))
		{
			stringstream s(line);
			getline(s, line, ',');
			if (line == to_string(ID))
			{
				cout << "\nBook is available.\n";
				system("read");
				return;
			}
		}
		cout << "\nBook is unavailable.\n";
		system("read");
		r_file.close();
		return;
	}
	else if (choice == 2)
	{
		cout << "Enter the name of the book: ";
		getline(cin >> ws, name);
		cout << "Enter the name of the author: ";
		getline(cin >> ws, author);

		while (getline(r_file, line))
		{
			stringstream s(line);
			getline(s, line, ',');
			getline(s, line, ',');
			if (line == name)
			{
				getline(s, line, ',');
				if (line == author)
				{
					cout << "\nBook is available.\n";
					system("read");
					return;
				}
			}
		}
		cout << "\nBook is unavailable.\n";
		system("read");
		r_file.close();
		return;
	}
	else if (choice == 3)
		return;
	else
	{
		cerr << "\nEnter a valid option.";
		system("read");
		system("clear");
		goto loop;
	}
}

void Book::add_book()
{
	ofstream w_file;
	w_file.open("Books.csv", ios::app);
	if (!w_file.is_open())
	{
		cerr << "\nSomething went wrong!\nPlease try again later.\n";
		system("read");
		return;
	}

	cout << "Book ID: ";
	cin >> ID;
	cout << "Book Name: ";
	getline(cin >> ws, name);
	cout << "Author: ";
	getline(cin >> ws, author);

	w_file << ID << "," << name << "," << author << "\n";
	Loading();
	w_file.close();
	cout << "Book has been successfully added."
		 << "\n"
		 << "Press Enter to go back.\n";

	system("read");
	system("clear");
}

void Book::remove_book()
{
	cout << "\t\t-------------\n"
		 << "\t\t REMOVE BOOK\n"
		 << "\t\t-------------\n";

	cout << "Book ID: ";
	cin >> ID;
	cout << "\nPress Enter to remove the book\n";
	system("read");
	string line;
	ifstream r_file;
	ofstream w_file;
	r_file.open("Books.csv");
	w_file.open("temp.csv");
	if (!r_file.is_open() || !w_file.is_open())
	{
		cerr << "\nUnable to remove the book.\nPlease try again later.\n";
		system("read");
		return;
	}
	while (getline(r_file, line))
	{
		stringstream s(line);
		getline(s, line, ',');
		if (line != to_string(ID))
		{
			w_file << line << ",";
			getline(s, line, ',');
			w_file << line << ",";
			getline(s, line, ',');
			w_file << line << "\n";
		}
	}
	r_file.close();
	w_file.close();
	remove("Books.csv");
	rename("temp.csv", "Books.csv");
}

void Book::Issue()
{

	cout << "\t\t------------\n"
		 << "\t\t ISSUE BOOK \n"
		 << "\t\t------------\n\n";

	cout << "Enter the Enrollment No.: ";
	cin >> enroll_no;
	cout << "Enter the Book ID: ";
	cin >> ID;

	bool check = false, check1 = false;
	ifstream r_file, r_student;
	ofstream w_file;
	r_file.open("Books.csv");
	r_student.open("Student.csv");
	string line, student;
	w_file.open("Issue.csv", ios::app);
	if (!w_file.is_open() || !r_file.is_open() || !r_student.is_open())
	{
		cerr << "\nUnable to issue book.\nPlease try again.\n";
		system("read");
		return;
	}
	while (getline(r_student, student))
	{
		stringstream ss(student);
		getline(ss, student, ',');
		if (student == enroll_no)
		{
			check1 = true;
			break;
		}
	}
	if (!check1)
	{
		cerr << "\nThe entered Enrollment No. doesn't exist.\nEnter a valid Enrollment No.\n";
		system("read");
		return;
	}

	w_file << enroll_no << ",";
	while (getline(r_file, line))
	{
		stringstream s(line);
		getline(s, line, ',');
		if (line == to_string(ID))
		{
			w_file << line << ",";
			getline(s, line, ',');
			w_file << line << ",";
			getline(s, line, ',');
			w_file << line << ",";
			check = true;
			break;
		}
	}
	if (!check)
	{
		cerr << "\nThe entered Book ID is not available.\n";
		system("read");
		return;
	}

	time_t now = time(0);
	tm *ltm = localtime(&now);
	string yr = to_string(1900 + ltm->tm_year);
	string mn = to_string(1 + ltm->tm_mon);
	string dt = to_string(ltm->tm_mday);

	w_file << dt << "-" << mn << "-" << yr << "\n";

	r_file.close();
	w_file.close();
	r_student.close();

	ifstream r_book;
	ofstream w_temp;
	r_book.open("Books.csv");
	w_temp.open("temp.csv");
	string books;
	if (!r_book.is_open() || !w_temp.is_open())
	{
		cerr << "\nUnable to issue book.\nPlease try again later.\n";
		system("read");
		return;
	}
	while (getline(r_book, books))
	{
		stringstream s1(books);
		getline(s1, books, ',');
		if (books != to_string(ID))
		{
			w_temp << books << ",";
			getline(s1, books, ',');
			w_temp << books << ",";
			getline(s1, books, ',');
			w_temp << books << "\n";
		}
	}
	r_book.close();
	w_temp.close();
	remove("Books.csv");
	rename("temp.csv", "Books.csv");

	cout << "\nBook Issued successfully.\n";
	system("read");
}

void Book::return_book()
{
	cout << "\t\t-------------\n"
		 << "\t\t RETURN BOOK \n"
		 << "\t\t-------------\n\n";

	cout << "Enter your Enrollment No.: ";
	cin >> enroll_no;
	cout << "Enter the Book ID: ";
	cin >> ID;

	bool check = false, check1 = false;
	ifstream r_file, r_student;
	ofstream w_file, w_return;
	string line, student;
	r_file.open("Issue.csv");
	w_file.open("Books.csv", ios::app);
	w_return.open("Return.csv", ios::app);
	r_student.open("Student.csv");
	if (!r_file.is_open() || !w_file.is_open() || !r_student.is_open() || !w_return.is_open())
	{
		cerr << "\nUnable to return book.\nPlease try again later.\n";
		system("read");
		return;
	}

	while (getline(r_student, student))
	{
		stringstream ss(student);
		getline(ss, student, ',');
		if (student == enroll_no)
		{
			check1 = true;
			break;
		}
	}
	if (!check1)
	{
		cerr << "\nThe entered Enrollment No. doesn't exist.\nEnter a valid Enrollment No.\n";
		system("read");
		return;
	}

	while (getline(r_file, line))
	{
		stringstream s(line);
		getline(s, line, ',');
		getline(s, line, ',');
		if (line == to_string(ID))
		{
			w_file << line << ",";
			w_return << line << ",";
			getline(s, line, ',');
			w_file << line << ",";
			w_return << line << ",";
			getline(s, line, ',');
			w_file << line << "\n";
			w_return << line << ",";
			check = true;
		}
	}
	if (!check)
	{
		cerr << "\nThe entered Book ID is not available.\n";
		system("read");
		return;
	}

	time_t now = time(0);
	tm *ltm = localtime(&now);
	string yr = to_string(1900 + ltm->tm_year);
	string mn = to_string(1 + ltm->tm_mon);
	string dt = to_string(ltm->tm_mday);

	w_return << dt << "-" << mn << "-" << yr << "\n";

	r_file.close();
	w_file.close();
	r_student.close();
}

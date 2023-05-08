#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <stdlib.h>
#include <ctime>
#include "Functions.h"
#include "Student.h"
#include "Librarian.h"
#include "Books.h"

using namespace std;

int main()
{
	Student S;
	Librarian L;
	Book B;
	system("clear");
menu:
	switch (main_menu())
	{
	case 1:
		Loading();
		S.s_login();
		goto smenu;
	case 2:
		Loading();
		L.l_login();
		goto lmenu;
	case 3:
		Loading();
		exit(0);
	}
smenu:
	switch (S.s_menu())
	{
	case 1:
		Loading();
		B.book_list();
		goto smenu;
	case 2:
		Loading();
		B.search_book();
		goto smenu;
	case 3:
	case 4:
		Loading();
		S.s_issued();
		goto smenu;
	case 5:
		Loading();
		goto menu;
	}
lmenu:
	switch (L.l_menu())
	{
	case 1:
		Loading();
		B.book_list();
		goto lmenu;
	case 2:
		Loading();
		B.search_book();
		goto lmenu;
	case 3:
		Loading();
		B.add_book();
		goto lmenu;
	case 4:
		Loading();
		B.remove_book();
		goto lmenu;
	case 5:
		Loading();
		B.Issue();
		goto lmenu;
	case 6:
		Loading();
		B.return_book();
		goto lmenu;
	case 7:
		Loading();
		goto menu;
	}
}

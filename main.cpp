#include <iostream>
#include <fstream>
using namespace std;

class person
{
protected:
    int id;
    string name;

public:
    person()
    {
        id = 0;
        name = "";
    }

    person(int i, string n)
    {
        id = i;
        name = n;
    }

    void displayperson()
    {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
    }

    int getID()
    {
        return id;
    }

    string getName()
    {
        return name;
    }
};

class student : public person
{
private:
    int issuedBookID;

public:
    student()
    {
        issuedBookID = 0;
    }

    student(int i, string n) : person(i, n)
    {
        issuedBookID = 0;
    }
    void issuebook(int bookID)
    {
        issuedBookID = bookID;
    }

    void returnbook()
    {
        issuedBookID = 0;
    }

    bool hasbook()
    {
        return issuedBookID != 0;
    }

    int getissuedbookid()
    {
        return issuedBookID;
    }

    void displaystudent()
    {
        displayperson();
        if (issuedBookID == 0)
        {
            cout << "Issued Book: None" << endl;
        }
        else
        {
            cout << "Issued Book ID: " << issuedBookID << endl;
        }
    }
};

class Librarian : public person
{
public:
    Librarian()
    {
    }

    Librarian(int i, string n) : person(i, n)
    {
    }

    void displaylibrarian()
    {
        displayperson();
    }
};

class Book
{
private:
    int bookID;
    string title;
    string author;
    bool available;

public:
    Book()
    {
        bookID = 0;
        title = "";
        author = "";
        available = true;
    }
    Book(int id, string t, string a)
    {
        bookID = id;
        title = t;
        author = a;
        available = true;
    }

    int getbookid()
    {
        return bookID;
    }

    string getTitle()
    {
        return title;
    }

    string getAuthor()
    {
        return author;
    }

    void setbookid(int id)
    {
        bookID = id;
    }

    bool isAvailable()
    {
        return available;
    }

    void setavailability(bool status)
    {
        available = status;
    }

    void bookdisplay()
    {
        cout << "Book ID: " << bookID << endl;
        cout << "Book Title: " << title << endl;
        cout << "Book Author: " << author << endl;
        cout << "Status: " << (available ? "Available" : "Not Available") << endl;
    }
};

class Library
{
private:
    Book books[100];
    int BookCount;
    student students[100];
    int studentCount;

public:
    Library()
    {
        BookCount = 0;
        studentCount = 0;
    }
    void addbook(Book b)
    {
        books[BookCount] = b;
        BookCount++;
        cout << "Book Added Succesfully!" << endl;
    }
    void displaybooks()
    {
        if (BookCount == 0)
        {
            cout << "No books Available!" << endl;
            return;
        }
        else
        {
            for (int i = 0; i < BookCount; i++)
            {
                cout << "\nBook " << 1 + i << endl;
                books[i].bookdisplay();
            }
        }
    }
    void searchBook(int id)
    {
        for (int i = 0; i < BookCount; i++)
        {
            if (books[i].getbookid() == id)
            {
                cout << "\nBook Found!" << endl;
                books[i].bookdisplay();
                return;
            }
        }
        cout << "Book not Found." << endl;
    }
    void searchBook(string title)
    {
        for (int i = 0; i < BookCount; i++)
        {
            if (books[i].getTitle() == title)
            {
                cout << "\nBook Found!" << endl;
                books[i].bookdisplay();
                return;
            }
        }
        cout << "Book not Found" << endl;
    }

    void addstudent(student s)
    {
        students[studentCount] = s;
        studentCount++;

        cout << "Student Added Successfully!" << endl;
    }

    void displaystudents()
    {
        if (studentCount == 0)
        {
            cout << "No Student Available." << endl;
            return;
        }
        for (int i = 0; i < studentCount; i++)
        {
            cout << "\nStudent " << i + 1 << endl;
            students[i].displaystudent();
        }
    }

    void searchstudent(int id)
    {
        for (int i = 0; i < studentCount; i++)
        {
            if (students[i].getID() == id)
            {
                cout << "\nStudent Found!" << endl;
                students[i].displaystudent();
                return;
            }
        }
        cout << "Student Not Found." << endl;
    }

    void issuebook(int studentID, int bookID)
    {
        bool studentfound = false;
        int studentindex = -1;

        for (int i = 0; i < studentCount; i++)
        {
            if (students[i].getID() == studentID)
            {

                cout << "Student Found!" << endl;
                studentfound = true;
                studentindex = i;
                if (students[i].hasbook())
                {
                    cout << "Student already has a Book!" << endl;
                    return;
                }
            }
        }

        if (!studentfound)
        {
            cout << " Student Not Found!" << endl;
            return;
        }

        bool bookfound = false;

        for (int i = 0; i < BookCount; i++)
        {
            if (books[i].getbookid() == bookID)
            {
                cout << "Book Found!" << endl;
                bookfound = true;
                if (!books[i].isAvailable())
                {
                    cout << "Book is already Issued!" << endl;
                    return;
                }
                books[i].setavailability(false);
                students[studentindex].issuebook(bookID);
            }
        }

        if (!bookfound)
        {
            cout << "Book Not Found!" << endl;
            return;
        }
        savebook();
        saveStudents();
    }

    void returnbook(int studentID)
    {
        int bookID;
        for (int i = 0; i < studentCount; i++)
        {
            if (students[i].getID() == studentID)
            {
                cout << "Student had a book issued! Now returning it." << endl;
                bookID = students[i].getissuedbookid();
                students[i].returnbook();
            }
            for (int j = 0; j < BookCount; j++)
            {
                if (books[j].getbookid() == bookID)
                {
                    cout << "Book is returned!" << endl;
                    books[j].setavailability(true);
                    savebook();
                    saveStudents();
                }
            }
        }
    }
    void savebook()
    {
        ofstream file("books.dat", ios::trunc);

        for (int i = 0; i < BookCount; i++)
        {
            file << books[i].getbookid() << endl;
            file << books[i].getTitle() << endl;
            file << books[i].getAuthor() << endl;
            file << books[i].isAvailable() << endl;
        }
        file.close();
    }

    void saveStudents()
    {
        ofstream file("Students.dat", ios::trunc);

        for (int i = 0; i < studentCount; i++)
        {
            file << students[i].getID() << endl;
            file << students[i].getName() << endl;
            file << students[i].getissuedbookid() << endl;
        }
        file.close();
    }

    void loadstudents()
    {
        ifstream file("Students.dat");

        int id;
        string name;
        int issuedbookid;

        while (file >> id)
        {
            file.ignore();
            getline(file, name);
            file >> issuedbookid;
            file.ignore();

            student s(id, name);
            if (issuedbookid != 0)
            {
                s.issuebook(issuedbookid);
            }

            students[studentCount] = s;
            studentCount++;
        }
        file.close();
    }

    void loadbooks()
    {
        ifstream file("books.dat");

        int id;
        string title;
        string author;
        bool available;

        while (file >> id)
        {
            file.ignore();
            getline(file, title);
            getline(file, author);
            file >> available;
            file.ignore();

            Book b(id, title, author);
            b.setavailability(available);

            books[BookCount] = b;
            BookCount++;
        }
        file.close();
    }
};

int main()
{

    Library library;
    library.loadbooks();
    library.loadstudents();
    int cho;
    while (true)
    {
        cout << "===========================================================================" << endl;
        cout << "======================== LIBRARY MANAGEMENT SYSTEM ========================" << endl;
        cout << "===========================================================================" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display Books" << endl;
        cout << "3. Search Book" << endl;
        cout << "4. Add Student" << endl;
        cout << "5. Display Students" << endl;
        cout << "6. Search Student" << endl;
        cout << "7. Issue Book" << endl;
        cout << "8. Return Book" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> cho;

        switch (cho)
        {
        case 1:
        {
            int id;
            string title;
            string author;
            cout << "Enter Book ID: ";
            cin >> id;
            cout << "Enter Book Title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter Book Author: ";
            getline(cin, author);
            Book b(id, title, author);
            library.addbook(b);
            library.savebook();
            break;
        }
        case 2:
        {
            library.displaybooks();
            break;
        }
        case 3:
        {
            int choice;

            cout << "1.Search By Book ID" << endl;
            cout << "2.Search By Book Title" << endl;
            cout << "Enter Your Choice : " << endl;
            cin >> choice;

            if (choice == 1)
            {
                int id;
                cout << "Enter Book ID to Search: ";
                cin >> id;
                library.searchBook(id);
            }
            else if (choice == 2)
            {
                string title;
                cin.ignore();

                cout << "Enter Book Title to Search: " << endl;
                getline(cin, title);

                library.searchBook(title);
            }
            else
            {
                cout << "Invalid Choice!" << endl;
            }
            break;
        }
        case 4:
        {
            int id;
            string name;
            cout << "Enter Student ID: ";
            cin >> id;
            cout << "Enter Student Name: ";
            cin.ignore();
            getline(cin, name);
            student s(id, name);
            library.addstudent(s);
            library.saveStudents();
            break;
        }
        case 5:
        {
            library.displaystudents();
            break;
        }
        case 6:
        {
            int id;
            cout << "Enter Student ID to Search: ";
            cin >> id;
            library.searchstudent(id);
            break;
        }
        case 7:
        {
            int studentID, bookID;
            cout << "Enter Student ID: ";
            cin >> studentID;
            cout << "Enter Book ID: ";
            cin >> bookID;
            library.issuebook(studentID, bookID);
            break;
        }
        case 8:
        {
            int studentID;
            cout << "Enter Student ID: ";
            cin >> studentID;
            library.returnbook(studentID);
            break;
        }
        case 9:
        {
            cout << "THANK YOU FOR USING THE LIBRARY MANAGEMENT SYSTEM!" << endl;
            return 0;
        }
        default:
        {
            cout << "Invalid Choice!" << endl;
            break;
        }
            return 0;
        }
    }
}
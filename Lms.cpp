
//***********Library Management System*************//



#include<iostream>
#include<vector>
#include<string>

using namespace std;


//------Class BOOK-------//
class Book{
    public:
        int id;
        string title;
        string author;
        bool isIssued;

        Book(int id, string title, string author){
            this->id=id;
            this->title=title;
            this->author=author;
            isIssued=false;
        }
};




//------Class LIBRARY------//

class Library{
private:
    vector<Book> books;
    vector<pair<int, string>> issuedBooks; // pair of Book ID and Student Name

public:
    void addBook(int id, string title, string author) {
        for(auto& issuedBook : issuedBooks) {
            if(issuedBook.first == id) {
                cout<<"\nThis book is currently issued and cannot be added again."<<endl;
                return;
            }
        }
        for(auto& book : books) {
            if(book.id == id) {
                cout<<"\nBook ID already exists. Please use a unique ID."<<endl;
                return;
            }
        }
        books.push_back(Book(id, title, author));
        cout<<"\nBook added successfully."<<endl;
    }

    void displayBooks() {
        cout<<"\nAvailable Books:\n";
        for(auto &book : books) {
            if(!book.isIssued) {
                cout<<"ID: "<<book.id<<", Title: "<<book.title<<", Author: "<<book.author<<endl;
            }
        }
    }

    void issueBook(int id, string studentName) {
        for(auto &book : books) {
            if(book.id == id && !book.isIssued) {
                book.isIssued = true;
                issuedBooks.push_back(make_pair(id, studentName));
                cout<<"\nBook issued successfully to "<<studentName<<"."<<endl;
                return;
            }
        }
        cout<<"\nBook not available for issue."<<endl;
    }

    void returnBook(int id) {
        for(auto &book : books) {
            if(book.id == id && book.isIssued) {
                book.isIssued = false;
                for(auto it = issuedBooks.begin(); it != issuedBooks.end(); it++) {
                    if (it->first == id) {
                        issuedBooks.erase(it);
                        break;
                    }
                }
                cout<<"\nBook returned successfully."<<endl;
                return;
            }
        }
        cout<<"\nBook not found or not issued."<<endl;
    }

    void displayIssuedBooks() {
        cout<<"\nIssued Books:\n";
        for(auto &pr : issuedBooks) {
            int id = pr.first;
            string studentName = pr.second;
            for(auto &book : books) {
                if(book.id == id) {
                    cout<<"ID: "<<book.id<<", Title: "<<book.title<<", Author: "<<book.author<<", Issued to: "<<studentName<<endl;
                    break;
                }
            }
        }
    }
};







//------Main fnc-------//

int main() {
    Library library;
    int choice, id;
    string title, author, studentName;

    while(true) {
        cout<<"\nLibrary Management System";
        cout<<"\n1. Add Book";
        cout<<"\n2. Display Books";
        cout<<"\n3. Issue Book";
        cout<<"\n4. Return Book";
        cout<<"\n5. Display Issued Books";
        cout<<"\n6. Exit";
        cout<<"\nEnter your choice: ";
        cin>>choice;

        switch(choice) {
            case 1:
                cout<<"Enter Book ID: ";
                cin>>id;
                cin.ignore(); // to clear the newline character from the input buffer
                cout<<"Enter Book Title: ";
                getline(cin, title);
                cout<<"Enter Book Author: ";
                getline(cin, author);
                library.addBook(id, title, author);
                break;

            case 2:
                library.displayBooks();
                break;

            case 3:
                cout<<"Enter Book ID to issue: ";
                cin>>id;
                cin.ignore();
                cout<<"Enter Student Name: ";
                getline(cin, studentName);
                library.issueBook(id, studentName);
                break;

            case 4:
                cout<<"Enter Book ID to return: ";
                cin>>id;
                library.returnBook(id);
                break;

            case 5:
                library.displayIssuedBooks();
                break;

            case 6:
                return 0;

            default:
                cout<<"\nInvalid choice. Please try again."<<endl<<endl;
        }
    }
}
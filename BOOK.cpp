#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Data structure to represent a book
struct Book {
    string title;
    string author;
    string ISBN;
    int quantity;
    double price;
};

// Function prototypes
void addBook(Book books[], int& numBooks);
void displayBooks(const Book books[], int numBooks);
void prepareQuotation(const Book books[], int numBooks);
void saveToFile(const Book books[], int numBooks);

bool login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Basic hardcoded authentication (replace with secure authentication methods)
    return (username == "admin" && password == "admin123");
}

int main() {
    bool isLoggedIn = login();
    if (!isLoggedIn) {
        cout << "Login failed. Exiting program.\n";
        return 1; // Exit with an error code
    }

    const int MAX_BOOKS = 100;
    Book books[MAX_BOOKS];
    int numBooks = 0;

    int choice;
    do {
        cout << "\n1. Add Book\n2. Display Books\n3. Prepare Quotation\n4. Logout\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(books, numBooks);
                break;
            case 2:
                displayBooks(books, numBooks);
                break;
            case 3:
                prepareQuotation(books, numBooks);
                break;
            case 4:
                if (isLoggedIn) {
                    isLoggedIn = false;
                    cout << "Logout successful. You are now logged out.\n";
                    login();
                } else {
                    cout << "You are not logged in.\n";
                }
                break;
            case 5:
                saveToFile(books, numBooks);
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

// Function to add a new book to the system
void addBook(Book books[], int& numBooks) {
    cout << "Enter book details:\n";
    cout << "Title: ";
    cin.ignore(); // Ignore newline character from previous input
    getline(cin, books[numBooks].title);
    cout << "Author: ";
    getline(cin, books[numBooks].author);
    cout << "ISBN: ";
    cin >> books[numBooks].ISBN;
    cout << "Quantity: ";
    cin >> books[numBooks].quantity;
    cout << "Price: $";
    cin >> books[numBooks].price;

    cout << "Book added successfully!\n";
    numBooks++;
}

// Function to display existing books
void displayBooks(const Book books[], int numBooks) {
    if (numBooks == 0) {
        cout << "No books available.\n";
        return;
    }

    cout << setw(20) << "Title" << setw(20) << "Author" << setw(15) << "ISBN"
         << setw(10) << "Quantity" << setw(10) << "Price" << endl;
    cout << setfill('-') << setw(75) << "-" << setfill(' ') << endl;

    for (int i = 0; i < numBooks; ++i) {
        cout << setw(20) << books[i].title << setw(20) << books[i].author
             << setw(15) << books[i].ISBN << setw(10) << books[i].quantity
             << setw(10) << "$" << fixed << setprecision(2) << books[i].price << endl;
    }
}

// Function to prepare a quotation for orders
void prepareQuotation(const Book books[], int numBooks) {
    if (numBooks == 0) {
        cout << "No books available to prepare a quotation.\n";
        return;
    }

    cout << "Enter order details:\n";
    // Assuming one book per order for simplicity
    int orderIndex;
    cout << "Enter the index of the book for the order: ";
    cin >> orderIndex;

    if (orderIndex < 0 || orderIndex >= numBooks) {
        cout << "Invalid book index.\n";
        return;
    }

    int quantity;
    cout << "Enter the quantity: ";
    cin >> quantity;

    double total = books[orderIndex].price * quantity;
    double discount = 0.1 * total;  // Assuming a 10% discount for simplicity
    double discountedTotal = total - discount;

    cout << "Quotation:\n";
    cout << "Book: " << books[orderIndex].title << " (" << quantity << " copies)\n";
    cout << "Total: $" << total << "\n";
    cout << "Discount: $" << discount << "\n";
    cout << "Discounted Total: $" << discountedTotal << "\n";
}

// Function to save book information to a text file
void saveToFile(const Book books[], int numBooks) {
    ofstream outFile("book_data.txt");
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    for (int i = 0; i < numBooks; ++i) {
        outFile << books[i].title << ',' << books[i].author << ',' << books[i].ISBN
                << ',' << books[i].quantity << ',' << books[i].price << '\n';
    }

    outFile.close();
    cout << "Book data saved to file.\n";
}
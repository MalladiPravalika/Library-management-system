# Library-management-system
# Library Management System

## Overview
This is a simple command-line-based Library Management System written in C. It allows users to perform essential library operations such as adding books, displaying available books, deleting books, issuing books to students, and displaying issued books.

## Features
1. **Add Book**: Add a new book to the library.
2. **Display Books**: View all available books in the library.
3. **Delete Book**: Remove a book from the library by its ID.
4. **Issue Book**: Issue a book to a student by providing their details.
5. **Display Issued Books**: View all books that have been issued to students.

## File Structure
- `books.txt`: Stores information about all books in the library.
- `issuedBooks.txt`: Stores information about all issued books.

## How to Use
### Prerequisites
- A C compiler (e.g., GCC).
- Basic knowledge of how to run C programs.

### Steps to Run
1. Clone the repository or copy the source code to your local machine.
2. Compile the `library_management_system.c` file using a C compiler:
   ```
   gcc library_management_system.c -o library_management_system
   ```
3. Run the compiled program:
   ```
   ./library_management_system
   ```
4. Follow the on-screen menu to perform various operations.

### Menu Options
1. Add Book: Add a new book by entering the book ID, name, and author.
2. Display Books: View the list of all available books.
3. Delete Book: Remove a book by entering its ID.
4. Issue Book: Issue a book to a student by entering the student details and book ID.
5. Display Issued Books: View the list of all issued books with student details.
6. Exit: Exit the application.

## Example Output
```
<== Library Management System ==>
1. Add Book
2. Display Books
3. Delete Book
4. Issue Book
5. Display Issued Books
0. Exit

Enter your choice: 1
Enter Book ID: 101
Enter Book Name: C Programming
Enter Author Name: Dennis Ritchie
Book added successfully!

Press any key to continue...
```

## Limitations
- Basic input validation is performed, but further enhancements can be made.
- File handling is limited to `books.txt` and `issuedBooks.txt` for simplicity.

## Contributing
Feel free to contribute to this project by submitting issues or pull requests. Any suggestions for improvement are welcome!

## License
This project is licensed under the MIT License.

## Acknowledgments
Special thanks to the creators of the C programming language and everyone who contributes to open-source projects.

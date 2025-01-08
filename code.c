#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Book {
    int id;
    char name[50];
    char author[50];
    char addedDate[12];
};

struct IssuedBook {
    int id;
    char studentName[50];
    char studentClass[50];
    int studentRoll;
    char bookName[50];
    char issueDate[12];
};

void addBook();
void displayBooks();
void deleteBook();
void issueBook();
void displayIssuedBooks();

int main() {
    int choice;

    while (1) {
        system("cls");
        printf("<== Library Management System ==>\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Delete Book\n");
        printf("4. Issue Book\n");
        printf("5. Display Issued Books\n");
        printf("0. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                deleteBook();
                break;
            case 4:
                issueBook();
                break;
            case 5:
                displayIssuedBooks();
                break;
            case 0:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }

        printf("\nPress any key to continue...");
        getchar();
        getchar();
    }

    return 0;
}

void addBook() {
    struct Book book;
    char currentDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(currentDate, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    FILE *file = fopen("books.txt", "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Book ID: ");
    scanf("%d", &book.id);
    getchar(); // Consume leftover newline
    printf("Enter Book Name: ");
    fgets(book.name, sizeof(book.name), stdin);
    book.name[strcspn(book.name, "\n")] = 0; // Remove trailing newline
    printf("Enter Author Name: ");
    fgets(book.author, sizeof(book.author), stdin);
    book.author[strcspn(book.author, "\n")] = 0; // Remove trailing newline
    strcpy(book.addedDate, currentDate);

    fprintf(file, "%d|%s|%s|%s\n", book.id, book.name, book.author, book.addedDate);
    fclose(file);

    printf("Book added successfully!\n");
}

void displayBooks() {
    struct Book book;
    FILE *file = fopen("books.txt", "r");
    if (!file) {
        printf("No books available!\n");
        return;
    }

    printf("\n<== Available Books ==>\n\n");
    printf("%-10s %-30s %-30s %s\n", "Book ID", "Book Name", "Author", "Added Date");
    printf("-------------------------------------------------------------------------\n");

    while (fscanf(file, "%d|%49[^|]|%49[^|]|%11[^\n]\n", &book.id, book.name, book.author, book.addedDate) == 4) {
        printf("%-10d %-30s %-30s %s\n", book.id, book.name, book.author, book.addedDate);
    }

    fclose(file);
}

void deleteBook() {
    int id, found = 0;
    struct Book book;
    FILE *file = fopen("books.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!file || !tempFile) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    while (fscanf(file, "%d|%49[^|]|%49[^|]|%11[^\n]\n", &book.id, book.name, book.author, book.addedDate) == 4) {
        if (book.id == id) {
            found = 1;
        } else {
            fprintf(tempFile, "%d|%s|%s|%s\n", book.id, book.name, book.author, book.addedDate);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found) {
        printf("Book deleted successfully!\n");
    } else {
        printf("Book not found!\n");
    }
}

void issueBook() {
    struct IssuedBook issuedBook;
    struct Book book;
    char currentDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(currentDate, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    int id, found = 0;

    printf("Enter Book ID to issue: ");
    scanf("%d", &id);

    FILE *booksFile = fopen("books.txt", "r");
    FILE *issuedFile = fopen("issuedBooks.txt", "a");
    if (!booksFile || !issuedFile) {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(booksFile, "%d|%49[^|]|%49[^|]|%11[^\n]\n", &book.id, book.name, book.author, book.addedDate) == 4) {
        if (book.id == id) {
            strcpy(issuedBook.bookName, book.name);
            issuedBook.id = book.id;
            found = 1;
            break;
        }
    }

    fclose(booksFile);

    if (!found) {
        printf("Book not found!\n");
        fclose(issuedFile);
        return;
    }

    getchar(); // Consume leftover newline
    printf("Enter Student Name: ");
    fgets(issuedBook.studentName, sizeof(issuedBook.studentName), stdin);
    issuedBook.studentName[strcspn(issuedBook.studentName, "\n")] = 0; // Remove trailing newline
    printf("Enter Student Class: ");
    fgets(issuedBook.studentClass, sizeof(issuedBook.studentClass), stdin);
    issuedBook.studentClass[strcspn(issuedBook.studentClass, "\n")] = 0; // Remove trailing newline
    printf("Enter Student Roll: ");
    scanf("%d", &issuedBook.studentRoll);
    strcpy(issuedBook.issueDate, currentDate);

    fprintf(issuedFile, "%d|%s|%s|%d|%s|%s\n", issuedBook.id, issuedBook.studentName, issuedBook.studentClass,
            issuedBook.studentRoll, issuedBook.bookName, issuedBook.issueDate);
    fclose(issuedFile);

    printf("Book issued successfully!\n");
}

void displayIssuedBooks() {
    struct IssuedBook issuedBook;
    FILE *file = fopen("issuedBooks.txt", "r");
    if (!file) {
        printf("No issued books available!\n");
        return;
    }

    printf("\n<== Issued Books List ==>\n\n");
    printf("%-10s %-30s %-20s %-10s %-30s %s\n", "Book ID", "Student Name", "Class", "Roll", "Book Name", "Issue Date");
    printf("-------------------------------------------------------------------------------------------\n");

    while (fscanf(file, "%d|%49[^|]|%49[^|]|%d|%49[^|]|%11[^\n]\n", &issuedBook.id, issuedBook.studentName,
                  issuedBook.studentClass, &issuedBook.studentRoll, issuedBook.bookName, issuedBook.issueDate) == 6) {
        printf("%-10d %-30s %-20s %-10d %-30s %s\n", issuedBook.id, issuedBook.studentName,
               issuedBook.studentClass, issuedBook.studentRoll, issuedBook.bookName, issuedBook.issueDate);
    }

    fclose(file);
}

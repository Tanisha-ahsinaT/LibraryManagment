#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
struct books
{
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
} b;

struct student
{
    int id;
    char sName[50];
    char sClass[50];
    int sRoll;
    char bookName[50];
    char date[12];
} s;

FILE *fp;

void addBook()
{
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(b.date, myDate);

    fp = fopen("books.txt", "ab");

    printf("Enter book id: ");
    scanf("%d", &b.id);
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    //fflush(stdin);

    printf("Enter book name: ");
    fflush(stdin);
    fgets(b.bookName, 20, stdin);

    printf("Enter author name: ");
    fflush(stdin);
    fgets(b.authorName, 20, stdin);

    printf("\nBook Added Successfully\n\n");

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}

void booksList()
{

    system("clear");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");

    fp = fopen("books.txt", "rb");
    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        b.bookName[strcspn(b.bookName, "\n")] = 0;
        b.authorName[strcspn(b.authorName, "\n")] = 0;
        b.date[strcspn(b.date, "\n")] = 0;
        printf("%-10d %-30s %-20s %s\n", b.id, b.bookName, b.authorName, b.date);
    }

    fclose(fp);
}

void del()
{
    int id, f = 0;
    system("clear");
    printf("<== Remove Books ==>\n\n");
    printf("Enter Book id to remove: ");
    scanf("%d", &id);
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    FILE *ft;

    fp = fopen("books.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        if (id == b.id)
        {
            f = 1;
        }
        else
        {
            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    if (f == 1)
    {
        printf("\nDeleted Successfully.\n");
    }
    else
    {
        printf("\nRecord Not Found !\n");
    }

    fclose(fp);
    fclose(ft);

    remove("books.txt");
    rename("temp.txt", "books.txt");
}

void issueBook()
{

    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(s.date, myDate);

    int f = 0;

    system("clear");
    printf("<== Issue Books ==>\n\n");

    printf("Enter Book id to issue: ");
    scanf("%d", &s.id);
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    // Check if we have book of given id
    fp = fopen("books.txt", "rb");

    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        if (b.id == s.id)
        {
            strcpy(s.bookName, b.bookName);
            f = 1;
            break;
        }
    }

    if (f == 0)
    {
        printf("\nNo book found with this id\n");
        printf("\nPlease try again...\n");
        return;
    }

    fp = fopen("issue.txt", "ab");

    printf("Enter Student Name: ");
    fflush(stdin);
    fgets(s.sName, 20, stdin);

    printf("Enter Student Class: ");
    fflush(stdin);
    fgets(s.sClass, 20, stdin);

    printf("Enter Student Roll: ");
    scanf("%d", &s.sRoll);
    while ((c = getchar()) != '\n' && c != EOF)
        ;

    printf("\nBook Issued Successfully\n");

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}

void issueList()
{
    system("clear");
    printf("<== Book Issue List ==>\n\n");

    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "S.id", "Name", "Class", "Roll", "Book Name", "Date");

    fp = fopen("issue.txt", "rb");
    while ((fread(&s, sizeof(s), 1, fp)==1))
    {   
        s.sName[strcspn(s.sName, "\n")] = 0;
        s.sClass[strcspn(s.sClass, "\n")] = 0;
        s.bookName[strcspn(s.bookName, "\n")] = 0;
        s.date[strcspn(s.date, "\n")] = 0;
        printf("%-10d %-30s %-20s %-10d %-30s %s\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.date);
    }

    fclose(fp);
}
int main()
{

    int ch;

    while (1)
    {
        system("clear");
        printf("<== Library Management System ==>\n");
        printf("1.Add Book\n");
        printf("2.Books List\n");
        printf("3.Remove Book\n");
        printf("4.Issue Book\n");
        printf("5.Issued Book List\n");
        printf("0.Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        char c;
        while ((c = getchar()) != '\n')
            ;

        switch (ch)
        {
        case 0:
            exit(0);

        case 1:
            addBook();
            break;

        case 2:
            booksList();
            break;

        case 3:
            del();
            break;

        case 4:
            issueBook();
            break;

        case 5:
            issueList();
            break;

        default:
            printf("\n\nInvalid Choice...\n\n");
        }

        printf("\nPress Enter Key To Continue...\n");
        getc(stdin);
    }

    return 0;
}
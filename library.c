#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
struct books
{
    int id;
    char bookname[50];
    char author[50];
    char date[12];

} b;
struct student
{
    int id;
    char sname[50];
    char sclass[50];
    int sroll;
    char bookname[50];
    char date[12];

} s;

FILE *fp;

int main()

{
    int ch;
    while (1)
    {
        system("cls");

        printf("<===Library Management System===>\n");
        printf("1) Add Book\n");
        printf("2) View Booklist\n");
        printf("3) Remove Book\n");
        printf("4) Issue Book\n");
        printf("5) View issued Books list\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {

        case 0:
            exit(0);

        case 1:
            addBook();
            break;

        case 2:
            
            booklist();
            break;

        case 3:
            removeBook();
            break;

        case 4 :
            issueBook();
            break;

        case 5 : 
            viewissuebook();
            break;

        default:
            printf("Invalid Choice!\n");
        }
        printf("Press any key to continue\n");
        getch();
    }

    return 0;
}

void addBook()
{
    char mydate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(mydate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(b.date, mydate);

    fp = fopen("books.txt", "ab");

    printf("Enter the books Id\n");
    scanf("%d", &b.id);

    printf("Enter Book name\n");
    fflush(stdin);
    gets(b.bookname);

    printf("Enter Author name\n");
    fflush(stdin);
    gets(b.author);

    printf("<====Book Added successfully====>\n");

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}
void booklist(){

    system("cls");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");

    fp = fopen("books.txt", "rb");
    while(fread(&b, sizeof(b), 1, fp) == 1){
        printf("%-10d %-30s %-20s %s\n", b.id, b.bookname, b.author, b.date);
    }

    fclose(fp);
}
void removeBook(){
    int id,f = 0;
    system("cls");
    printf("<===Remove Book===>\n\n");
    printf("Enter id of book to remove\n");
    scanf("%d", &id);
    FILE *ft;

    fp = fopen("books.txt", "rb");
    ft = fopen("temp.txt", "wb");
    while (fread(&b, sizeof(b), 1, fp)==1)
    {
        if(id == b.id){
            f = 1;
        }
        else{
            fwrite(&b, sizeof(b), 1, ft);
        }
    }
    if (f == 1)
    {
        printf("\n\nBook deleted succefully");

    }
    else{
        printf("\n\nBook not found");
    }
    
    fclose(fp);
    fclose(ft);
    remove("books.txt");
    rename("temp.txt","books.txt");
}
void issueBook(){
    char mydate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(mydate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(s.date, mydate);

    int f = 0;
    system("cls");
    printf("<===Issue Book===>\n\n");
    printf("Enter Book Id to issue\n");
    scanf("%d",&s.id);

    fp = fopen("books.txt","rb");
    while (fread(&b, sizeof(b), 1, fp)==1)
    {
        if(b.id == s.id){
            strcpy(s.bookname,b.bookname);
            f = 1;
            break;
        }
    }
    if (f == 0)
    {
        printf("No book found of this id\n");
        printf("Please try again\n");
        return;
    }
    fp = fopen("issue.txt","ab");

    printf("Enter student Name: ");
    fflush(stdin);
    gets(s.sname);

    printf("Enter student Class: ");
    fflush(stdin);
    gets(s.sclass);

    printf("Enter student roll no(only numbers): ");
    scanf("%d",&s.sclass);

    fwrite(&s, sizeof(s),1,fp);
    fclose(fp);
    
}
void viewissuebook(){
    system("cls");
    printf("<== Issued Books list ==>\n\n");
    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "S.id", "Name", "Class", "Roll","Book name","Date");

    fp = fopen("issue.txt", "rb");
    while(fread(&s, sizeof(s), 1, fp) == 1){
        printf("%-10d %-30s %-20s %-10d %-30s %s\n\n", s.id,s.sname,s.sclass,s.sroll,s.bookname,s.date);
    }

    fclose(fp);
}
//project on the topic of "Library Management System"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_TITLE 100
#define MAX_AUTHOR 100
#define MAX_NAME 100

void addBook();
void newbook();
void existingbook();
void displayBooks();
void BorrowBook();
void displayBorrowers();
void returnBook();
int checkuser(char[50]);
typedef struct
{
    int book_id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int copies;
} Book;

typedef struct {
    char userName[MAX_NAME];
    char bookTitle[MAX_TITLE];
    int copiesBorrowed;
} BorrowRecord;

void main()
{
    char  cont;
    int choice;
    do
    {
        system("cls");
        printf("\n\t\t\t\t==============================Library Management System========================\n");
        printf("\t\t\t\t\t\t\t\t1. Add Books\t\t\t \n");
        printf("\t\t\t\t\t\t\t\t2. Display Books       \t\t\t\n");
        printf("\t\t\t\t\t\t\t\t3. Borrow Books       \t\t\t\n");
        printf("\t\t\t\t\t\t\t\t4. Displaying Borrower Details       \t\t\t\n");
        printf("\t\t\t\t\t\t\t\t5. Return Book       \t\t\t\n");
        printf("\t\t\t\t==============================================================================\n");
        printf("\nEnter your choice:");
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            displayBooks();
            break;
        case 3:
        	BorrowBook();
        	break;
        case 4:
        	displayBorrowers();
        	break;
        case 5:
        	returnBook();
        	break;
        	
        default:
            printf("Invalid choice. Please try again.\n");
        }
        printf("\nDo you want to continue(Y/N):");
        fflush(stdin);
        scanf(" %c", &cont);
    } while(cont=='Y' || cont=='y');
}


void newbook()
{
	system("cls");
	FILE *fp;
	Book book;
	fp=fopen("book.txt", "a+");
    if(fp==NULL)
	{	
        printf("Error opening file!\n");
        return;
    }
	printf("\nEnter book ID: ");
	    scanf("%d",&book.book_id);
	    int temp=book.book_id;
	    while (fread(&book,sizeof(Book),1,fp))
		{	
			if(temp==book.book_id)
			{
			
	        	printf("Book with this id already exists, please try again with another id");
	        	
	        	return;
	        }
	    }
	    book.book_id=temp;
	    printf("\nEnter book title: ");
	    fflush(stdin);  
	    gets(book.title);
	    printf("\nEnter author name: ");
	    gets(book.author);
	    printf("\nEnter number of copies: ");
	    scanf("%d",&book.copies);
		//fprintf(fp,"%5d%15s%26s%15d\n",book.book_id,book.title,book.author,book.copies);
	    fwrite(&book,sizeof(Book),1,fp);
	    
	    printf("\nBook added successfully!\n");
	    fclose(fp);
}

void existingbook()
{
	system("cls");
	FILE *fp;
    FILE *temp;
    int id,bookfound=0,choose1,copy;
    Book book;
    fp=fopen("book.txt", "r");
	temp = fopen("temp.txt", "w");
	if (fp==NULL || temp==NULL) {
	        printf("Error opening file!\n");
	        return;
	    }
    	printf("Enter id of the book you want to add: ");
    	scanf("%d",&id);
    	bookfound=0;
    	while (fread(&book,sizeof(Book),1,fp))
    	{
    		
    		if(book.book_id==id)
    		{
    			bookfound=1;
    			printf("Is %s by %s the book you are going to add?\n\t1. Yes\t\t2. No\n",book.title,book.author);
    			scanf("%d",&choose1);
    			if(choose1 !=1)
    			{
    				fclose(fp);
    				return;
    				
				}
    				
    			printf("Enter the number of copies that is to be added: ");
    			scanf("%d",&copy);
    			book.copies += copy;
    			
    			printf("Books successfuly added!"); 
			}
			fwrite(&book, sizeof(Book), 1, temp);
		}
		if(bookfound != 1)
			printf("Book id not identified! ");
		
		fclose(fp);
 		fclose(temp);
 		remove("book.txt");
		rename("temp.txt", "book.txt");
}

void addBook() {
	 char  cont;
	 int choose;
    
    do
    {
	 system("cls");
    printf("Do you want to add:\n");
    printf("\t1. New book\n");
    printf("\t2. Existing book\n\nEnter your choice: ");
    scanf("%d",&choose);
    switch (choose)
    {
	case 1:
	    newbook();
	    break;
    
    case 2:
    	existingbook();
		break;
		
	default:
         printf("Invalid choice. Please try again.\n");
    }
    printf("\nDo you want to continue adding books?(Y/N):");
    fflush(stdin);
    scanf(" %c", &cont);
}while(cont=='Y' || cont=='y');
    	
 	
 
}

void displayBooks()
{
    FILE *fp;
    Book book;
	fp=fopen("book.txt","r");
    if (fp==NULL)
	{
        printf("Error opening file!\n");
        return;
    }
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("%-15s%-25s%-26s%15s\n","Book_ID","Title","Author","Copies");
    printf("-----------------------------------------------------------------------------------------------------\n");
    
    while (fread(&book,sizeof(Book),1,fp))
	{	
        printf("%-15d%-25s%-26s%15d\n",book.book_id, book.title, book.author, book.copies);
    }
    fclose(fp);
    printf("-----------------------------------------------------------------------------------------------------\n");
}

int checkuser(char userName[50])
{
	FILE *fp;
	BorrowRecord record;
	fp= fopen("borrowers.txt", "r");
	while (fread(&record, sizeof(BorrowRecord), 1, fp)) {
        if(strcmp(record.userName,userName)==0)
        {
        	
        	return 1;
        }
        
    }
    
    fclose(fp);
}

void BorrowBook()
	{
		FILE *fp = fopen("book.txt", "r");
	    FILE *temp = fopen("temp.txt", "w");
	    FILE *borrowFile = fopen("borrowers.txt", "ab");
	    char title[MAX_TITLE];
	    char userName[MAX_NAME];
	    int copies;
	   
	    if (fp==NULL || temp==NULL || borrowFile==NULL) {
	        printf("Error opening file!\n");
	    }
	    
	    printf("Enter your name: ");
	    getchar();  // to consume the newline character left by previous input
	    gets(userName);
	    
	    if(checkuser(userName)==1)
	    {
	    	printf("Please return the the book borrowed previously first!");
	    	return;
		}
	    	
		
	    if (userName[strlen(userName) - 1] == '\n')
	        userName[strlen(userName) - 1] = '\0';
	
	    printf("Enter book title to borrow: ");
	    fgets(title, MAX_TITLE, stdin);
	    if (title[strlen(title) - 1] == '\n')
	        title[strlen(title) - 1] = '\0';
	
	    printf("Enter number of copies to borrow: ");
	    scanf("%d", &copies);
	
	    Book book;
	    int bookFound = 0;
	
	    while (fread(&book, sizeof(Book), 1, fp)) {
	        if (strcmp(book.title, title) == 0) {
	            bookFound = 1;
	            if (book.copies >= copies) {
	                book.copies = book.copies-copies;
	                printf("You have successfully borrowed %d copies of '%s'.\n", copies, book.title);
	
	                // Record the borrowing information
	                BorrowRecord record;
	                strcpy(record.userName, userName);
	                strcpy(record.bookTitle, book.title);
	                record.copiesBorrowed = copies;
	                fwrite(&record, sizeof(BorrowRecord), 1, borrowFile);
	            } else {
	                printf("Only %d copies of '%s' are available. Borrowing failed.\n", book.copies, book.title);
	            }
	        }
	        fwrite(&book, sizeof(Book), 1, temp);  // Write the (possibly updated) book record to the temporary file
	    }
	
	    if (!bookFound) {
	        printf("No book found with the title '%s'.\n", title);
	    }
	
	    fclose(fp);
	    fclose(temp);
	    fclose(borrowFile);
	
	    remove("book.txt");
	    rename("temp.txt", "book.txt");
}

void displayBorrowers() {
    system("cls");
	FILE *borrowFile = fopen("borrowers.txt", "r");
    if (borrowFile==NULL) {
        printf("Error opening file!\n");
        return;
    }

    BorrowRecord record;
    printf("\n\t\t\t\t\t\tDisplaying the details of the user who borrowed books from library:\n");
    printf("\n\t\t\t\t\t\t=========================================================================\n");
    printf("\t\t\t\t\t\t %-30s  %-30s  %-6s \n", "User Name", "Book Title", "Copies");
    printf("\t\t\t\t\t\t=========================================================================\n");
    while (fread(&record, sizeof(BorrowRecord), 1, borrowFile)) {
        printf("\t\t\t\t\t\t %-30s  %-30s  %-6d \n", record.userName, record.bookTitle, record.copiesBorrowed);
    }
    printf("\t\t\t\t\t\t==========================================================================\n");
    fclose(borrowFile);
}

void returnBook()
{
        
	FILE *fp, *temp, *bookFile;
    BorrowRecord record;
    Book book;
    char userName[MAX_NAME];
    int found = 0;

    printf("Enter your name: ");
    getchar();
    gets(userName);

    fp = fopen("borrowers.txt", "r");
    temp = fopen("temp.txt", "w");
    bookFile = fopen("book.txt", "r+");

    if (fp == NULL || temp == NULL || bookFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&record, sizeof(BorrowRecord), 1, fp)) {
        if (strcmp(record.userName, userName) == 0) {
            found = 1;
            printf("%d copies of %s book was successfuly returned by %s",record.copiesBorrowed,record.bookTitle,record.userName);
            // Return the book to inventory
            while (fread(&book, sizeof(Book), 1, bookFile)) {
                if (strcmp(book.title, record.bookTitle) == 0) {
                    book.copies += record.copiesBorrowed;
                    fseek(bookFile, -sizeof(Book), SEEK_CUR);
                    fwrite(&book, sizeof(Book), 1, bookFile);
                    break;
                }
            }
            fseek(bookFile, 0, SEEK_SET);
        } else {
            fwrite(&record, sizeof(BorrowRecord), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);
    fclose(bookFile);

    remove("borrowers.txt");
    rename("temp.txt", "borrowers.txt");

    if (found) {
        printf("\n");
    } else {
        printf("No records found for the user '%s'.\n", userName);
    }
}




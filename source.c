#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

//Structure for user info
struct user_info{
    char user_name[20];
    char password[20];
    char role[20];
};

//Structure for book info
struct book_info{
    char book_name[20];
    char author[20];
    int edition;
    char available[10];
};

struct user_info user;

struct book_info book;

void login(); //Login function

void create_user(char []); //Creates a new user

void user_menu(); //Menu for user

void admin_menu(); //Menu for admin

void view_books(); //View books

void borrow_books(); //Borrow books

void remove_books(); //Remove books

void return_books(); //Return books

void add_books(); //Add books

void show_users(); //Show users

void remove_user(); //Remove user

void wait(); //Freeze screen 

FILE *user_data, *book_data;
char username[20];
char password[20];
char role[20];
bool byAdmin;

int main(){
    login();
}

void login(){
    user_data = fopen("user_data.txt", "rb+");
    bool user_exists = false;
    bool password_match = false;
    char choice;
    printf("\n\t\tLogin\n");
    printf("Username : ");
    scanf("%s", username);
    printf("Password : ");
    scanf("%s", password);
    while(fread(&user, sizeof(user), 1, user_data)==1){
        if(strcmp(username, user.user_name) == 0){
            user_exists = true;
            strcpy(role, user.role);
            if(strcmp(password, user.password) == 0){
                password_match = true;
            }
        }
    }
    fclose(user_data);
    if(user_exists){
        if(password_match){
            printf("Logged-in successfully");
            if(strcmp(role, "admin") == 0){
                admin_menu();
            }else{
                user_menu();
            }
        }else{
            printf("Invalid password");
            login();
        }
    }else{
        printf("User does not exist");
        ask:
        printf("\nCreate User? (y/n) ");
        fflush(stdin);
        scanf(" %c", &choice);
        if(choice == 'y' || choice == 'Y'){
            create_user("user");
        }else if(choice == 'n' || choice == 'N'){
            login();
        }else{
            printf("Invalid choice");
            goto ask;
        }
    }
}

void create_user(char r[]){
    user_data = fopen("user_data.txt", "ab+");
    struct user_info User;
    printf("\nEnter username: ");
    scanf("%s", user.user_name);
    printf("Enter password: ");
    scanf("%s", user.password);
    strcpy(user.role, r);
    while(fread(&User, sizeof(User), 1, user_data) == 1){
        if(strcmp(User.user_name, user.user_name) == 0){
            printf("Username already exists");
            create_user(r);
        }
    }
    fwrite(&user, sizeof(user), 1, user_data);
    fclose(user_data);
    printf("User created succesfully");
    wait();
    if(byAdmin){
        admin_menu();
    }else{
        user_menu();
    }
}

void user_menu(){
    char choice;
    printf("\n\n\t\tMenu\n");
    printf("\nV - View books");
    printf("\nB - Borrow books");
    printf("\nR - Return books");
    printf("\nQ - Quit\n");
    choice:
    fflush(stdin);
    scanf(" %c", &choice);
    switch(choice){
        case 'V':
            view_books();
            break;
        case 'B':
            borrow_books();
            break;
        case 'R':
            return_books();
            break;
        case 'Q':
            login();
            break;
        default:
            printf("Invalid choice\n");
            goto choice;
    }
}

void admin_menu(){
    char choice;
    printf("\n\n\t\tMenu\n");
    printf("\nV - View books");
    printf("\nA - Add books");
    printf("\nR - Remove books");
    printf("\nS - View users");
    printf("\nC - Add superuser");
    printf("\nU - Add user");
    printf("\nD - Remove user");
    printf("\nQ - Quit\n");
    choice:
    fflush(stdin);
    scanf(" %c", &choice);
    switch(choice){
        case 'V':
            view_books();
            break;
        case 'R':
            remove_books();
            break;
        case 'A':
            add_books();
            break;
        case 'C':
            create_user("admin");
            break;
        case 'U':
            byAdmin = true;
            create_user("user");
            break;
        case 'S':
            show_users();
            break;
        case 'D':
            remove_user();
            break;
        case 'Q':
            login();
            break;
        default:
            printf("Invalid choice\n");
            goto choice;
    }
}

void view_books(){
    book_data = fopen("book_data.txt", "rb");
    rewind(book_data);
    printf("Book\tAuthor\tEdition\tAvailable\n");
    while(fread(&book, sizeof(book), 1, book_data) == 1){
        if(book.edition){
            printf("%s\t%s\t%d\t%s\n", book.book_name, book.author, book.edition, book.available);
        }
    }
    fclose(book_data);
    wait();
    if(strcmp(role, "user") == 0){
        user_menu();
    }else{
        admin_menu();
    }
}

void borrow_books(){
    char bookName[20];
    bool found = false;
    book_data = fopen("book_data.txt", "rb+");
    printf("Enter book name: ");
    scanf("%s", bookName);
    while(fread(&book, sizeof(book), 1, book_data) == 1){
        if(strcmp(bookName, book.book_name) == 0){
            printf("Book\tAuthor\tEdition\tAvailable\n");
            printf("%s\t%s\t%d\t%s\n", book.book_name, book.author, book.edition, book.available);
            found = true;
            if(strcmp(book.available, "yes") == 0){
                printf("Book borrowed successfully\n");
                fseek(book_data, -(long)sizeof(book), SEEK_CUR);
                strcpy(book.available, "no");
                fwrite(&book, sizeof(book), 1, book_data);
            }else{
                printf("Book is already borrowed\n");
            }
            break;
        }
    }
    if(!found){
        printf("Book not found");
    }
    fclose(book_data);
    wait();
    if(strcmp(role, "user") == 0){
        user_menu();
    }else{
        admin_menu();
    }
}

void return_books(){
    char bookName[20];
    book_data = fopen("book_data.txt", "rb+");
    printf("Enter book name: ");
    scanf("%s", bookName);
    while(fread(&book, sizeof(book), 1, book_data) == 1){
        if(strcmp(bookName, book.book_name) == 0){
            printf("Book\tAuthor\tEdition\tAvailable\n");
            printf("%s\t%s\t%d\t%s\n", book.book_name, book.author, book.edition, book.available);
            if(strcmp(book.available, "no") == 0){
                printf("Book returned successfully\n");
                fseek(book_data, -(long)sizeof(book), SEEK_CUR);
                strcpy(book.available, "yes");
                fwrite(&book, sizeof(book), 1, book_data);
            }else{
                printf("Book not borrowed\n");
            }
            break;
        }
    }
    fclose(book_data);
    wait();
    if(strcmp(role, "user") == 0){
        user_menu();
    }else{
        admin_menu();
    }
}

void remove_books(){
    char bookName[20];
    bool rm = false;
    book_data = fopen("book_data.txt", "rb");
    FILE *temp = fopen("temp.txt", "wb");
    printf("Enter name of book to delete: ");
    scanf("%s", bookName);
    while(fread(&book, sizeof(book), 1, book_data) == 1){
        if(strcmp(book.book_name, bookName) == 0){
            rm = true;
        }else{
            fwrite(&book, sizeof(book), 1, temp);
        }
    }
    fclose(book_data);
    fclose(temp);
    remove("book_data.txt");
    rename("temp.txt", "book_data.txt");
    if(rm){
        printf("Book removed succesfully");
    }else{
        printf("Book not found");
    }
    wait();
    admin_menu();
}

void show_users(){
    user_data = fopen("user_data.txt", "rb");
    printf("Username\tPassword\tRole\n");
    while(fread(&user, sizeof(user), 1, user_data) == 1){
        printf("%s\t\t%s\t\t%s\n", user.user_name, user.password, user.role);
    }
    fclose(user_data);
    wait();
    admin_menu();
}

void add_books(){
    book_data = fopen("book_data.txt", "ab");
    printf("\nEnter book name: ");
    scanf("%s", book.book_name);
    printf("Enter author: ");
    scanf("%s", book.author);
    fflush(stdin);
    printf("Enter edition: ");
    scanf("%d", &book.edition);
    strcpy(book.available, "yes");
    fwrite(&book, sizeof(book), 1, book_data);
    printf("Book added successfully");
    fclose(book_data);
    wait();
    admin_menu();
}

void remove_user(){
    char userName[20];
    bool rm = false;
    user_data = fopen("user_data.txt", "rb");
    FILE *temp = fopen("temp.txt", "wb");
    printf("Enter username to delete: ");
    scanf("%s", userName);
    while(fread(&user, sizeof(user), 1, user_data) == 1){
        if(strcmp(user.user_name, userName) == 0){
            rm = true;
        }else{
            fwrite(&user, sizeof(user), 1, temp);
        }
    }
    fclose(user_data);
    fclose(temp);
    remove("user_data.txt");
    rename("temp.txt", "user_data.txt");
    if(rm){
        printf("User removed succesfully");
    }else{
        printf("User not found");
    }
    wait();
    admin_menu();
}

void wait(){
    printf("\nEnter any character to continue ");
    getch();
}
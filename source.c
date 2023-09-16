#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
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

void login(); //Login function



FILE *user_data, *book_data;

int main(){
    user_data = fopen("user_data.txt", "ab+");
    book_data = fopen("book_data.txt", "ab+");
    int i;
    struct book_info user;
    struct user_info us;
    // for(i = 0; i < 5; i++){
    //     printf("Enter username: ");
    //     scanf("%s", us.user_name);
    //     printf("Enter password: ");
    //     scanf("%s", us.password);
    //     printf("Enter role: ");
    //     scanf("%s", us.role);
    //     fwrite(&us, sizeof(us), 1, user_data);
    // }
    // for(i = 0; i < 5; i++){
    //     printf("Enter bookname: ");
    //     scanf("%s", user.book_name);
    //     printf("Enter author: ");
    //     scanf("%s", user.author);
    //     fflush(stdin);
    //     printf("Enter edition: ");
    //     scanf("%d", &user.edition);
    //     printf("Available: ");
    //     fflush(stdin);
    //     scanf("%s", user.available);
    //     fwrite(&user, sizeof(user), 1, book_data);
    // }
    rewind(book_data);
    rewind(user_data);
    while(fread(&user, sizeof(user), 1, book_data)==1){
        printf("%s\t%s\t%d\t%s\n", user.book_name, user.author, user.edition, user.available);
    }
    fclose(user_data);
    fclose(book_data);
}



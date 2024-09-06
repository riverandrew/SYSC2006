/********* main.c ********
    Student Name 	= Andrew Rivera
    Student Number	= 101192264
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h> 
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE 
       AND GENERATE THE STARTING LINKED LIST.
    */
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    
    /* IMPORTANT: You must use the users linked list created in the code above. 
                  Any new users should be added to that linked list.
    */

    // Your solution goes here

    printf ("***********************************************\n");
    printf ("Welcome to Text-Based Facebook\n");
    printf ("***********************************************\n");
    printf ("\n");

    print_menu();

    unsigned int choice = 0;

    printf ("\nEnter your choice: ");
    scanf ("%d", &choice);

    while (choice > 6 || choice <= 0){

        printf ("Invalid choice. Please try again\n");
        printf ("\n");

        print_menu();

        printf ("\nEnter your choice: ");
        scanf ("%d", &choice);

    }

    char username[30];
    char password[15];
    
    while (choice > 0 && choice < 6){
    
        if (choice == 1){ //Register a new user

            printf ("Enter a username: ");
            scanf ("%s", &username);

            printf ("Enter an upto 15 characters password: ");
            scanf ("%s", &password);
    
            while (strlen(password) > 15){
                printf ("Enter an upto 15 characters password: ");
                scanf ("%s", &password);
            }
        
            add_user(users, username, password);

            printf ("\n");
            printf ("**** User Added! ****\n");
            printf ("\n");

            print_menu();
            printf ("\nEnter your choice: ");
            scanf ("%d", &choice);

            while (choice > 6 || choice <= 0){
                printf ("Invalid choice. Please try again\n");
                printf ("\n");
                print_menu();

                printf ("\nEnter your choice: ");
                scanf ("%d", &choice);
            }
        }
        if (choice == 2){//Manage a user's profile
            printf ("Enter a username to update their password: ");
            scanf ("%s", &username);
            user_t *temp = users;
            temp = find_user(users, username);

            if (temp == NULL){
            printf ("\n-----------------------------------------------\n");
            printf ("User not found\n");
            printf ("-----------------------------------------------\n");
            }
            
            if (temp != NULL){
                char newpassword[15];
                printf ("Enter a new password that is upto 15 characters password: ");
                scanf ("%s", &newpassword);
    
                while (strlen(password) > 15){
                    printf ("Enter a new password that is upto 15 characters password: ");
                    scanf ("%s", &newpassword);
                }
                strcpy (temp->password, newpassword);
                printf ("\n**** Password changed! ****\n");
            }

            print_menu();
            printf ("\nEnter your choice: ");
            scanf ("%d", &choice);

            while (choice > 6 || choice <= 0){
                printf ("Invalid choice. Please try again\n");
                printf ("\n");
                print_menu();

                printf ("\nEnter your choice: ");
                scanf ("%d", &choice);
            }

        }
        if (choice == 3){//Manage a user's posts
            printf ("Enter a username to manage their posts: ");
            scanf ("%s", &username);
            user_t *temp = users;
            temp = find_user(users, username);

            if (temp == NULL){ //User not in list
                printf ("-----------------------------------------------\n");
                printf ("User not found\n");
                printf ("-----------------------------------------------\n");
            }

            while (temp != NULL){//User in list

                display_user_posts (temp);
                unsigned int postChoice = 0;

                printf ("1. Add a new user post\n");
                printf ("2. Remove a users post\n");
                printf ("3. Return to main menu\n");

                printf ("Your choice: ");
                scanf ("%d", &postChoice);

                while (postChoice > 3 || postChoice <= 0){
                    printf ("Invalid choice. Please try again\n");
                    printf ("\n");

                    printf ("Enter your choice: ");
                    scanf ("%d", &postChoice);
                }

                if (postChoice == 1){//add post
                    const char postcontents [250];
                    printf("Enter your post content: ");
                    scanf (" %[^\n]s", &postcontents);
                    post_t *newpost = create_post (postcontents);
                    add_post(temp, newpost->content);
                    printf("Post added to your profile.\n");
                }

                if (postChoice == 2){//delete post
                    int delpost = 0;
                    printf("Which post do you want to delete? ");
                    scanf ("%d", &delpost);
                    delete_post(temp, delpost);
                }
                if (postChoice == 3){//return to main menu
                    break;
                }
            }

            print_menu();
            printf ("\nEnter your choice: ");
            scanf ("%d", &choice);//update user input

            while (choice > 6 || choice <= 0){
                printf ("Invalid choice. Please try again\n");
                printf ("\n");
                print_menu();

                printf ("\nEnter your choice: ");
                scanf ("%d", &choice);
            }
        }
        if (choice == 4){//Manage friends
            
            printf ("Enter a username to manage their friends: ");
            scanf ("%s", &username);
            user_t *temp = users;
            temp = find_user(users, username);
            if (temp == NULL){//User not in list
                printf ("-----------------------------------------------\n");
                printf ("User not found\n");
                printf ("-----------------------------------------------\n");
            }

            user_t *newfriend = users;
        
            while (temp != NULL){ //User in list

                unsigned int friendChoice = 0;
                printf ("-----------------------------------------------\n");
                printf ("%s's friends \n", temp->username);
                printf ("-----------------------------------------------\n");

                printf ("1. Display all user's friends\n");
                printf ("2. Add a new friend\n");
                printf ("3. Delete friend\n");
                printf ("4. Return to main menu\n");
                printf ("\n");

                printf ("Your choice: ");
                scanf ("%d", &friendChoice);

                while (friendChoice > 4 || friendChoice <= 0){
                    printf ("Invalid choice. Please try again\n");
                    printf ("\n");

                    printf ("\nEnter your choice: ");
                    scanf ("%d", &friendChoice);
                }
                if (friendChoice == 1){ //Display friends
                    display_user_friends(temp);
                }

                if (friendChoice == 2){//Add new friend
                    printf ("Enter a new friends name: ");
                    scanf ("%s", &username);
                    add_friend(temp, username);
                    printf ("Friend added to the list.\n");

                }
                if (friendChoice == 3){//Delete friend
                    printf ("Enter a friend's name to delete: ");
                    scanf ("%s", &username);
                    delete_friend(temp,username);
                }

                if (friendChoice == 4){//Return to main menu
                    break;
                }
            }


            print_menu();
            printf ("\nEnter your choice: ");
            scanf ("%d", &choice);
        
        }

        if (choice == 5){
        
            
            user_t *view = users;

            if (view != NULL){ 
                display_all_posts(view);
            }

            char nextposts;
            printf ("\nDo you want to display next 2 users posts? (Y/N): ");
            scanf ("%s", &nextposts);

            while (nextposts != 'Y' && nextposts != 'y' && nextposts != 'N' && nextposts != 'n'){
                printf("Invalid input. (Y/N):");
                scanf ("%s", &nextposts);
            }

            while (nextposts == 'Y' || nextposts == 'y'){
                
                if (view == NULL){
                    break;
                }

                view = view->next->next;
                display_all_posts(view);
                printf ("\nDo you want to display next 2 users posts? (Y/N): ");
                scanf ("%s", &nextposts);

                if (nextposts == 'N' || nextposts == 'n'){
                    break;
                }
            }
            
            print_menu();
            printf ("\nEnter your choice: ");
            scanf ("%d", &choice);

            while (choice > 6 || choice <= 0){
                printf ("Invalid choice. Please try again\n");
                printf ("\n");
                print_menu();

                printf ("\nEnter your choice: ");
                scanf ("%d", &choice);
            }
        }

        if (choice == 6){
            printf("***********************************************\n");
            printf ("Thank you for using Text-Based Facebook\n");
            printf ("GoodBye!\n");
            printf("***********************************************\n");

        }
    }

    user_t *temp = malloc (sizeof(user_t));
    strcpy (temp->username, users->username);
    //print_list (users);
    //printf ("->%s", users->posts);
    teardown (users);
    if (strcmp (temp->username,users->username) != 0){
        printf ("\nList of Users are freed from database"); 
    }


return 0;
    
}
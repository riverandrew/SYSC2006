/********* definitions.c ********
    Student Name 	= Andrew Rivera
    Student Number	= 101192264
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h> 
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here

void print_list(user_t *user)
{
   if (user == NULL) {
      printf("empty list");
   }

   
   user_t *current;
   for (current = user; current->next != NULL; current = current->next) {
   printf("%s -> ", current->username);
   }
   printf("%s", current->username);
   
}

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.

   Done
*/

user_t *add_user(user_t *users, const char *username, const char *password) 
{
   // Finds a user of the same username, to prevent duplicate users.
   user_t *find = users;

   int compare = -1;

   while (compare != 0 && find!=NULL){

      compare = strcmp (find->username, username);
      if (compare == 0){
      return find;
      }

      find = find->next;
   }

   // Create new node for the new user

   user_t *newuser = malloc(sizeof(user_t));
   assert (newuser != NULL);

   strcpy (newuser->username, username);
   strcpy (newuser->password, password);

   newuser -> friends = NULL;
   newuser -> posts = NULL;
   newuser -> next = NULL;


   if (users == NULL || strcmp (newuser->username, users->username) < 0){ //If linked list is empty, the new user will be the first user.
      newuser -> next = users;
      users = newuser;
      return newuser;
   }
   
   else{
      user_t *temp = users;

      while (temp->next != NULL && strcmp (newuser->username, temp->next->username) > 0){
         temp = temp->next;
      }
      newuser->next = temp->next;
      temp->next = newuser;
   }

   return users;
}
/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.

   Done
*/
user_t *find_user(user_t *users, const char *username)
{
   user_t *find = users;

   int compare = -1;

   while (compare != 0 && find!=NULL){

      compare = strcmp (find->username, username);
      if (compare == 0){
      return find;
      }

      find = find->next;

   }
   find = NULL;
   return find;
}
/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
   

   friend_t *temp = malloc(sizeof(friend_t));
   strcpy(temp->username, username);
   temp->next = NULL;
   
   return temp;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
   friend_t *newfriend = create_friend (friend);
   assert (newfriend != NULL);
   
   if (strcmp (user->username, friend) == 0){ //Exits the function if the friend that is being added shares the same username.
      return;
   }

   if (user->friends == NULL || strcmp (newfriend->username, user->username) < 0){ //If linked list is empty, the new user will be the first user.
      newfriend -> next = user->friends;
      user->friends= newfriend;
   }
   
   else{
      friend_t *temp = user->friends;
      while (temp->next != NULL && strcmp (newfriend->username, temp->next->username) > 0){
         temp = temp -> next;
      }

      newfriend->next = temp->next;
      temp->next = newfriend;
   }
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
   if (user->friends == NULL){ // If friend list is empty
      printf ("Invalid friend's name\n");
      display_user_friends (user);
      return 0;
   }

   assert (user != NULL);
   friend_t *friendlist = user->friends;

   if (strcmp (friendlist->username, friend_name) == 0){ //Deletes the first
      friend_t *del = friendlist;
      user->friends = friendlist->next;
      free(del);
      return 1;
   }
   

   while (friendlist->next != NULL){ //Deletes the rest
      if (strcmp (friendlist->next->username, friend_name) == 0){
         friend_t *del = friendlist->next;
         friendlist->next = friendlist->next->next;
         free (del);
         return 1;
      }

   friendlist = friendlist->next;
   }

   printf ("Invalid friend's name\n"); //If enetered username does not exist in friendlist
   display_user_friends (user);
   return 0;
}

/*
   Function that creates a new user's post.
   Return the newly created post.

   Done
*/
post_t *create_post(const char *text)
{
   post_t *newpost = malloc(sizeof(post_t));

   strcpy(newpost->content, text);
   newpost -> next = NULL;

   return newpost;
}

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).

   Done
*/
void add_post(user_t *user, const char *text)
{
   post_t *newpost = create_post (text);
   newpost-> next = user->posts;
   user->posts = newpost;
   
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.

   Done
*/
_Bool delete_post(user_t *user, int number)
{

   if (user->posts == NULL && number > 0){ // If there are no posts and user enters a post to del
      printf ("Invalid post's number\n");
      return 0;
   }

   if (number == 1) { // Deletes first post
      post_t *temp = user->posts;
      user->posts = user->posts->next;
      free(temp);
      printf ("Post %d successfully deleted!\n", number);
      return 1;
   }
   
    
   int count = 1;
   post_t *curr = user->posts;

   while (curr != NULL && curr->next !=NULL){ //Deletes the rest

      if (count + 1 == number){
         post_t *temp = curr->next;
         curr->next = curr->next->next;
         printf ("Post %d successfully deleted!\n", number);
         free(temp);         
         return 1;
      }

      curr = curr->next;
      count++;
   }

   printf ("Invalid post's number\n");
   return 0;
}

/*
   Function that  displays a specific user's posts

   Done
*/
void display_user_posts(user_t *user)
{
   post_t *temp = user->posts;

   if (temp == NULL){ //If no posts
      printf ("-----------------------------------------------\n");
      printf ("No posts available for %s. \n", user->username);
      printf ("-----------------------------------------------\n");
      return;
   }

   printf ("-----------------------------------------------\n"); //Displays all users posts
   printf ("%s's posts\n", user->username);

   int count = 1;
   while (temp != NULL){
      printf ("%d- %s: %s\n", count,user->username, temp->content);
      temp = temp->next;
      count++;
   }
   printf ("-----------------------------------------------\n");

}

/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t *user)
{
   friend_t *temp = user->friends;

   if (temp == NULL){//Empty friendlist

      printf ("List of %s's friends:\n", user->username);
      printf("No friends available for %s. \n", user->username);
      printf("\n");
      return;
   }

   else{
      printf ("-----------------------------------------------\n");
      printf ("List of %s's friends:\n", user->username);

      int count = 1;
      while (temp != NULL){
         printf ("%d- %s\n", count, temp->username);
         temp = temp->next;
         count++;
      }
   }


}
/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.

*/
void display_all_posts(user_t *users)
{
   user_t *curr = users;
   int count = 1;

   post_t *first = users->posts; //First user
   count = 1;
   while (first != NULL) {
      printf("%d- %s: %s\n", count, users->username, first->content);
      first = first->next;
      count++;
   }

   post_t *second = users->next->posts; // Second user
   count = 1;
   while (second != NULL) {
      printf("%d- %s: %s\n", count, users->next->username, second->content);
      second = second->next;
      count++;
   }
}



/*
   Fucntion that free all users from the database before quitting the application.
   Done
*/
void teardown(user_t *users)
{
   user_t *node_to_delete;

   while (users != NULL) {
      node_to_delete = users;

      friend_t *friend_to_delete = users->friends;
      while (friend_to_delete != NULL) {
         friend_t *temp = friend_to_delete;
         friend_to_delete = friend_to_delete->next;
         free(temp); //Free created friends
        }

        post_t *post_to_delete = users->posts;
        while (post_to_delete != NULL) {
            post_t *temp = post_to_delete;
            post_to_delete = post_to_delete->next;
            free(temp); //Free created posts
        }

      users = users->next;
      free(node_to_delete);
   }

   
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{

printf ("***********************************************\n");
printf ("MAIN MENU:\n");
printf ("***********************************************\n");
printf ("1. Register a new User\n");
printf ("2. Manage a user's profile (change password)\n");
printf ("3. Manage a user's posts (display/add/remove)\n");
printf ("4. Manage a user's friends (display/add/remove)\n");
printf ("5. Display All Posts\n");
printf ("6. Exit\n");

}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}

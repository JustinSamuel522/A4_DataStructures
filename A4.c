#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//initialize link list
struct node{
  int data; //will contain the window ID
  struct node *next; //will contain the location to next value (the window)
};

void open(struct node **head, int window_id);
void switcher(struct node **head, int window_id);
void closer(struct node **head, int window_id);
void printStatement(struct node *head);
void freelist(struct node **head);


int main(void){

  struct node *head = NULL;  // Initialize an empty list of windows
  char command[7]; //used to take in open, switch, and close commands
  int window_id;

  while (scanf("%s %d", command, &window_id) != EOF) {
    if (strcmp(command, "open") == 0) {
        open(&head, window_id);
    } 
    else if (strcmp(command, "switch") == 0) {
        switcher(&head, window_id);
    } 
    else if (strcmp(command, "close") == 0) {
        closer(&head, window_id);
    }

    if (head != NULL) {
        printStatement(head);  // Print the currently focused window
    } 
    else {
        break;  // Terminate when the last window is closed
    } 
  }

  freelist(&head);

  return 0;
}

void open(struct node **head, int window_id){
  struct node *newnode = (struct node*)malloc(sizeof(struct node)); //for the new node
  if (newnode == NULL) { //just in case
      exit(EXIT_FAILURE); 
  }
  newnode->data = window_id; //set the data of the new node to the window ID
  newnode->next = *head; //set the next of the new node to the head of the list
  *head = newnode; //set the head of the list to the new node
}

void switcher(struct node **head, int window_id){
  struct node *prev = NULL, 
  *current = *head; //set the current node to the head of the list

  if (current != NULL && current->data == window_id) { //if the current window id is the same as the one we want to switch
      return;
  }

  while (current != NULL && current->data != window_id) { //search for window
      prev = current;
      current = current->next;
  }

  if (current != NULL) {
    if (prev != NULL) {
        prev->next = current->next;  // Remove the window from its current position
    }
    current->next = *head;
    *head = current; // the window is now set as the head
  }

}

void closer(struct node **head, int window_id){
  struct node *prev = NULL, *current = *head;

  // Search for the window in the list
  while (current != NULL && current->data != window_id) {
      prev = current;
      current = current->next;
  }

  if (current != NULL) {
      if (prev != NULL) {
          prev->next = current->next;  // Remove from its position
      } else {
          *head = current->next;  // Update head if we're removing the first node
      }

      free(current);  // Free the node to prevent memory leaks
  }
}

void printStatement(struct node *head){
  if (head != NULL) {
    printf("%d\n", head->data);  // Focused window is the head of the list
  } else {
    // If the list is empty (after the last window is closed), terminate
    exit(0);
  }
  }

void freelist(struct node **head){
  struct node *current = *head;
  struct node *next_node;

  while (current != NULL) {
      next_node = current->next;
      free(current);  // Free each node
      current = next_node;
  }
  *head = NULL;  // Set the head to NULL after freeing all nodes
}

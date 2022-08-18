#include <stdio.h>
#include <stdlib.h>

#define LEN 20

typedef struct {

  char title[LEN];
  char author[LEN];
  int lists;
  int year;

} Book;

typedef struct node {

  Book book;
  struct node * right;
  struct node * left;

} Node;

typedef struct tree {

  Node * root;
  int size;

} Tree;


void InitializeTree (Tree * pt);
void createTree (Tree * prt, Book * pri);


int main (void) {

  Tree temp;
  Book item;

  InitializeTree (&temp);

}

void InitializeTree (Tree * prt) {

  prt->size = 0;
  prt->root = NULL;

}

void createTree (Tree * prt, Book * pri) {

  Node * newNode;
  newNode = (Node * ) malloc (sizeof (Node));

  newNode->book = * pri;
  newNode->right = NULL;
  newNode->left = NULL;
  prt->root = newNode;
  prt->size ++;

}

void AddItem (Tree * prt, Book * pri) {

  Node * newNode;
  newNode = (Node * ) malloc (sizeof (Node));

  

}

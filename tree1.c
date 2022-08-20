#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LEN 20

typedef struct {

  char title[LEN];
  char author[LEN];

} Book;

typedef struct tree {

  Book param;
  struct tree * right;
  struct tree * left;
  struct tree * parent;

} Node;


void InitializeTree (Node * pt, Book key);
Node * AddItem (Node * ptn, Book key);


int main (void) {

  Node tree;
  Book key;

  puts ("Input title of book:");
  gets (key.title);
  puts ("Input author this book:");
  gets (key.author);

  InitializeTree (&tree, key);

  puts ("Input title of book:");

  while (gets (key.title) != NULL && key.title[0] != '\0') {

    puts ("Input author this book:");
    gets (key.author);

    AddItem (&tree, key);

    puts ("Input title of book:");

  }

  Node * ptr;
  ptr = (Node * ) malloc (sizeof (Node));
  ptr = &tree;

  puts ("Left branch:");

  while (ptr != 0) {

    puts ((ptr->param).title);
    ptr = ptr->left;

  }

  putchar ('\n');
  putchar ('\n');
  puts ("Right branch:");

  while (ptr != 0) {

    puts ((ptr->param).title);
    ptr = ptr->right;

  }

}

void InitializeTree (Node * pt, Book key) {

  Node * memTree;
  memTree = (Node * ) malloc (sizeof (Node));

  pt->right = NULL;
  pt->left = NULL;
  pt->parent = NULL;
  pt->param = key;

  pt = memTree;


}

Node * AddItem (Node * ptn, Book key) {

  Node * mem, * start = ptn, * start_help;
  mem = (Node * ) malloc (sizeof (Node));

  mem->param = key;

  while (start != NULL) {

    start_help = start;

    if (strcmp (key.title, (start->param).title) > 0) {

      start = start->left;
      continue;

    }

    if (strcmp (key.title, (start->param).title) < 0) {

      start = start->right;
      continue;

    }

    else
      exit (1);

  }

  mem->parent = start_help;
  mem->left = NULL;
  mem->right = NULL;

  if (strcmp (key.title, (start_help->param).title) > 0) {

    start_help->left = mem;
    return ptn;

  }

  if (strcmp (key.title, (start_help->param).title) > 0) {

    start_help->right = mem;
    return ptn;

  }


}

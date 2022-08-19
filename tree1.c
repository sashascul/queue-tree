#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LEN 20

typedef struct tree {

  int key;
  struct tree * right;
  struct tree * left;
  struct tree * parent;

} Node;


void InitializeTree (Node * pt, int key);
Node * AddItem (Node * ptn, int key);


int main (void) {

  Node tree;
  int key;

  scanf ("%d", &key);

  InitializeTree (&tree, key);

  while (scanf ("%d", &key) == 1) {

    AddItem (&tree, key);

  }

  Node * ptr;
  ptr = (Node * ) malloc (sizeof (Node));
  ptr = &tree;

  while (ptr != 0) {

    printf ("%d\n", ptr->key);
    ptr = ptr->left;

  }



}

void InitializeTree (Node * pt, int key) {

  int numRoot;

  Node * memTree;
  memTree = (Node * ) malloc (sizeof (Node));

  pt->right = NULL;
  pt->left = NULL;
  pt->parent = NULL;
  pt->key = key;

  pt = memTree;


}

Node * AddItem (Node * ptn, int key) {

  Node * mem, * start = ptn, * start_help;
  mem = (Node * ) malloc (sizeof (Node));

  mem->key = key;

  while (start != NULL) {

    start_help = start;

    if (key <= start->key)
      start = start->left;

    else
      start = start->right;

  }

  mem->parent = start_help;
  mem->left = NULL;
  mem->right = NULL;

  if (key < start_help->key)
    start_help->left = mem;

  else
    start_help->right = mem;

  return ptn;

}

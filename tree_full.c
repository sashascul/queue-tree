#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define LEN 50

typedef struct {

  char title[LEN];
  char author[LEN];

} Object;

typedef struct tree {

  Object object;
  struct tree * left;
  struct tree * right;

} Tree;


void InitializateTree (Tree * pt, Object obj);
void AddItem (Tree * pt, Object obj);
void expAdd (Tree * save, Tree * memTree);
short ExploreNode (Tree * pt, char book[], Tree ** save);
void Explore (Tree * pt, char book[]);
void DestroyNode (Tree * pt, char book[]);
void Destroy (Tree * pt, Object obj);


int main (void) {

  Object item;
  Tree temp;

  puts ("Input title of book:");
  gets (item.title);
  puts ("Input author this book:");
  gets (item.author);

  InitializateTree (&temp, item);

  puts ("Input title next book:");

  while (gets (item.title) != NULL && item.title[0] != '\0') {

    puts ("Input author this book:");
    gets (item.author);
    AddItem (&temp, item);

    puts ("Input title next book:");


  }



  goto label;

  puts ("Left branch:");

  Tree * ptLeft;
  ptLeft = (Tree * ) malloc (sizeof (Tree));
  ptLeft = &temp;

  while (ptLeft != NULL) {

    puts ((ptLeft->object).title);
    ptLeft = ptLeft->left;

  }

  putchar ('\n');
  putchar ('\n');
  puts ("Right branch:");

  Tree * ptRight;
  ptRight = (Tree * ) malloc (sizeof (Tree));
  ptRight = &temp;

  while (ptRight != NULL) {

    puts ((ptRight->object).title);
    ptRight = ptRight->right;

  }

  label:

  /*

  char book[LEN];
  puts ("Explore of block. Input title any book:");
  gets (book);

  Explore (&temp, book);

  */


  Object object;
  puts ("Input title of book, which needing destroy:");
  gets (object.title);
  puts ("Input author this book, which needing destroy:");
  gets (object.author);

  Destroy (&temp, object);



  return 0;
}

void InitializateTree (Tree * pt, Object obj) {

  pt->object = obj;
  pt->left = NULL;
  pt->right = NULL;

}

void AddItem (Tree * pt, Object obj) {

  Tree * memTree, * save;
  memTree = (Tree * ) malloc (sizeof (Tree));

  memTree->object = obj;
  memTree->left = NULL;
  memTree->right = NULL;
  save = pt;

  expAdd (save, memTree);

}

void expAdd (Tree * save, Tree * memTree) {

  if (strcmp ((memTree->object).title, (save->object).title) < 0) {

    if (save->left == NULL) {

      save->left = memTree;
      return;

    }

    else {

      save = save->left;
      expAdd (save, memTree);

    }

  }

  if (strcmp ((memTree->object).title, (save->object).title) > 0) {

    if (save->right == NULL) {

      save->right = memTree;
      return;

    }

    else {

      save = save->right;
      expAdd (save, memTree);

    }

  }

}

void Explore (Tree * pt, char book[]) {

  Tree * mem;
  mem = (Tree * ) malloc (sizeof (Tree));
  mem = pt;

  Tree * str;

  short result = ExploreNode (mem, book, &str);

  switch (result) {

    case 0:
      puts ("This tree don't contain this book!");
      break;
    case 1:
      puts ("This tree contain this book. Adress this block: ");
      printf ("%p", str);
    default:
      break;

  }

}

short ExploreNode (Tree * pt, char book[], Tree ** save) {

  if (pt == NULL)
    return 0;

  if (strcmp ((pt->object).title, book) == 0) {

    * save = pt;
    return 1;

  }

  if (strcmp (book, (pt->object).title) < 0) {

    pt = pt->left;
    ExploreNode (pt, book, save);

  }

  if (strcmp (book, (pt->object).title) > 0) {

    pt = pt->right;
    ExploreNode (pt, book, save);

  }

}

void Destroy (Tree * pt, Object obj) {


  /*  ----------/--------
      -------node1-------
      --node2-----NULL---
      -------------------
  */

  /*  ----------/--------
      -------node1-------
      --NULL-----node2---
      -------------------
  */

  /*  ----------/--------
      -------node1-------
      --node2-----node3--
      -------------------
  */

}

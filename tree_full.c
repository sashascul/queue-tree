#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void ExploreNode (Tree * pt, char obj[]);


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

  /*

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

  */

  char book[LEN];
  puts ("Explore of block. Input title any book:");
  gets (book);

  ExploreNode (&temp, book);

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

void ExploreNode (Tree * pt, char obj[]) {

  Tree * exp;
  exp = (Tree * ) malloc (sizeof (Tree));
  exp = pt;

  if ((exp->object).title == obj) {

    puts ("This tree contain this book. Adress this block:");
    printf ("%p", exp);
    return;

  }

  if (strcmp (obj, (exp->object).title) < 0) {

    exp = exp->left;
    ExploreNode (exp, obj);

  }

  if (strcmp (obj, (exp->object).title) > 0) {

    exp = exp->right;
    ExploreNode (exp, obj);

  }

}

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
bool ExploreNode (Tree * pt, Object book, Tree ** save);
void Explore (Tree * pt, Object book);
void DestroyNode (Tree * pt, char book[]);
void Destroy (Tree * pt, Object obj);
void expDestroyBlock (Tree * pt, Tree * adr, Object obj);
void whichNode (Tree * pt);
void Right (Tree * pt, Tree * save);


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



    Object book;
    puts ("Explore of block. Input title any book:");
    gets (book.title);
    gets (book.author);

    Explore (&temp, book);


    label:

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

void Explore (Tree * pt, Object book) {

    Tree * mem;
    mem = (Tree * ) malloc (sizeof (Tree));
    mem = pt;

    Tree * str;

    bool result = ExploreNode (mem, book, &str);

    switch (result) {

        case true:
            puts ("This tree contain this book. Adress this block: ");
            printf ("%p", str);
            break;
        default:
            puts ("This tree don't contain this book!");
            break;

    }

}

bool ExploreNode (Tree * pt, Object book, Tree ** save) {

	if (pt == NULL)
		return false;

    if (strcmp (book.title, (pt->object).title) == 0) {

        * save = pt;
        return true;

    }

    if (strcmp (book.title, (pt->object).title) < 0) {

        ExploreNode (pt->left, book, save);

    }

    if (strcmp (book.title, (pt->object).title) > 0) {

        ExploreNode (pt->right, book, save);

    }

}

void Destroy (Tree * pt, Object obj) {

    Tree * adr;

    /*####################################
    node get adress of destroying block
    ####################################*/

    if (ExploreNode (pt, obj, &adr) == 1) {

        puts ("This node'll destroy. Info:");
        expDestroyBlock (pt, adr, obj);
        return;

    }

    else {

        puts ("So node not found!");
        exit (EXIT_FAILURE);

    }

}

void expDestroyBlock (Tree * pt, Tree * adr, Object obj) {

    if (pt == NULL)
        return;

    if (pt == adr) {

        printf ("title: ");
        puts ((pt->object).title);
        printf ("author: ");
        puts ((pt->object).author);

        whichNode (pt);
        return;

    }

    if (strcmp (obj.title, (pt->object).title) < 0)
        expDestroyBlock (pt->left, adr, obj);

    if (strcmp (obj.title, (pt->object).title) > 0)
        expDestroyBlock (pt->right, adr, obj);


}

void whichNode (Tree * pt) {

    /*------------/------
      -------node1-------
      --node2-----NULL---
      -------------------*/

    if (pt->right == NULL) {

        printf ("Object-title of left branch: ");
        puts (((pt->left)->object).title);
        pt = pt->left;

        return;

    }

    /*----------/--------
      -------node1-------
      --NULL-----node2---
      -------------------*/

    if (pt->left == NULL) {

      printf ("Object-title of right branch: ");
      puts (((pt->right)->object).title);
      pt = pt->right;

      return;

    }

    /*----------/--------
      -------node1-------
      --node2-----node3--
      -------------------*/

    else {

        printf ("Object-title of left branch: ");
        puts (((pt->left)->object).title);
        Tree * save = pt->right;
        Right (pt->left, save);
        return;

    }

}

void Right (Tree * pt, Tree * save) {

  if (pt->right == NULL) {

      pt->right = save;
      return;

  }

  Right (pt->right, save);


}

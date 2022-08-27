#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define FRAME "##########################################"
#define LEN 50


bool initializeFirst = 0;

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
char * input (char * str);
char menu (void);
void InputAddItem (Tree * temp);
void InputDestroyItem (Tree * temp);
void InputSeekItem (Tree * temp);
void Exit (void);


int main (void) {

    /* ##### rus-location ######*/
                               ///
    SetConsoleCP(1251);        ///
    SetConsoleOutputCP(1251);  ///
                               ///
    /*##########################*/

    Tree temp;
    char ch;

    while ((ch = menu ()) != 'q') {

      switch (ch) {

        case 'a': InputAddItem (&temp);
        case 'd': InputDestroyItem (&temp);
        case 's': InputSeekItem (&temp);
        case 'q': Exit ();

        default: break;

      }

    }

    puts ("Program finished. Good luck!");


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

    return 0;

}


/* Operation: Function for exit.                                  */
/* Predconditions: -                                              */
/* Postconditions: exit from this program.                        */
void Exit (void) {

  exit (EXIT_SUCCESS);

}


/* Operation: Function for subsequent destroy.                    */
/* Predconditions: This function gets pointer of tree.            */
/* Postconditions: To Explore ().                                 */
void InputSeekItem (Tree * temp) {

    Object book;
    puts ("Explore of block. Input title any book:");
    gets (book.title);
    gets (book.author);

    Explore (temp, book);

}


/* Operation: Function for subsequent input.                      */
/* Predconditions: This function gets pointer of tree.            */
/* Postconditions: To AddItem ().                                 */
void InputAddItem (Tree * temp) {

  Object item;

  if (initializeFirst == 0) {

    puts ("Input title of book:");
    input (item.title);
    puts ("Input author this book:");
    input (item.author);

    InitializateTree (temp, item);
    initializeFirst = 1;

  }

  puts ("Input title of book:");

  while (input (item.title) != NULL && item.title[0] != '\0') {

      puts ("Input author this book:");
      input (item.author);
      AddItem (temp, item);

      puts ("Input title next book or input [enter]:");

  }

}


/* Operation: Function for subsequent destroy.                    */
/* Predconditions: This function gets pointer of tree.            */
/* Postconditions: To Destroy ().                                 */
void InputDestroyItem (Tree * temp) {

    Object object;
    puts ("Input title of book, which needing destroy:");
    input (object.title);
    puts ("Input author this book, which needing destroy:");
    input (object.author);

    Destroy (temp, object);

}


/* Operation: This function initializes tree.                     */
/* Predconditions: This function gets pointer of tree and         */
/* compared object.                                               */
/* Postconditions: Start root of tree initializes to null-objects */
/* and recieved object: left pointer of root = null;              */
/*                      right pointer of root = null;             */
/*                      object of root tree = recieved object;    */
void InitializateTree (Tree * pt, Object obj) {

    pt->object = obj;
    pt->left = NULL;
    pt->right = NULL;

}


/* Operation: This function adds object in the tree.              */
/* Predconditions: This function gets pointer of tree and         */
/* compared object.                                               */
/* Postconditions: First, first comes memory allocation for tree  */
/* Start root of tree initializes to null-objects                 */
/* and recieved object: left pointer of root = null;              */
/*                      right pointer of root = null;             */
/*                      object of root tree = recieved object;    */
/* Further The function "expAdd" start to work.                   */
void AddItem (Tree * pt, Object obj) {

    Tree * memTree, * save;
    memTree = (Tree * ) malloc (sizeof (Tree));

    memTree->object = obj;
    memTree->left = NULL;
    memTree->right = NULL;
    save = pt;

    expAdd (save, memTree);

}


/* Operation: Search for a specific element, which need in adding.*/
/* Predconditions: This function gets pointer of tree and         */
/* pointer for previously allocated memory.                       */
/* Postconditions: there is a comparison of elements by branches. */
/* Adding element adds in the end of tree.                        */
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


/* Operation: Search for a specific element, which need in        */
/* destroying.                                                    */
/* Predconditions: This function gets pointer of tree and         */
/* compared object.                                               */
/* Postconditions: there is a comparison of elements by branches. */
/* this function allocates memory. It is needed for the           */
/* function "ExploreNode()".                                      */
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


/* Operation: Search for a specific element, which need in        */
/* destroying.                                                    */
/* Predconditions: This function gets pointer of tree,            */
/* compared object and pointer.                                   */
/* Postconditions: this function looks for an element.            */
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


/* Operation: Destroying elements in the tree.                    */
/* Predconditions: This function gets pointer of tree and         */
/* compared object.                                               */
/* Postconditions: this function destroys for an element.         */
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



/* Operation: Search for a node, which need destroying.           */
/* Predconditions: This function gets pointer of tree,            */
/* pointer of saved adress block and compared object.             */
/* Postconditions: searches for the specified block to delete     */
/* later                                                          */
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


/* Operation: Search for a node, which need connect in destroy    */
/* place.                                                         */
/* Predconditions: This function gets pointer of tree.            */
/* Postconditions: destroy node.                                  */
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


/* Operation: Attaches the node.                                  */
/* Predconditions: This function gets pointer of tree and         */
/* previously saved right node.                                   */
/* Postconditions: the right branch will be attached              */
void Right (Tree * pt, Tree * save) {

  if (pt->right == NULL) {

      pt->right = save;
      return;

  }

  printf ("It was destroy block with adress: %p\n", pt);

  Right (pt->right, save);

}


/* Operation: This function fills the string.                     */
/* Predconditions: This function gets pointer of string.          */
/* Postconditions: This function return pointer of this string    */
char * input (char * str) {

  char ch;

  while ((ch = getchar()) != EOF) {

    if (ch == '\n') {

      ch = '\0';
      * str = ch;

      return str;

    }

    * str = ch;
    str++;

  }

}

char menu () {

    char ch;

  puts (FRAME);
  puts ("                  MENU:                  ");
  putchar ('\n');
  puts ("a) Add items;                s) Seek item;");
  puts ("d) Destroy node;            q) Exit.     ");
  putchar ('\n');
  puts (FRAME);

  puts ("Please, input one of the variant menu:");

  ch = getchar ();
  while (getchar () != '\n')
    continue;

  if (strchr ("asdq", ch) == NULL) {

    puts ("This paragraph not found! Repeat again.");
    menu ();

  }

  return ch;

}

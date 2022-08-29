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

    int size;
    Object object;
    struct tree * left;
    struct tree * right;

} Tree;


void InitializateTree (Tree * pt, Object obj);
void AddItem (Tree * pt, Object obj);
void expAdd (Tree * memTree, Tree * pt);
bool ExploreNode (Tree * pt, Object book, Tree ** save);
void Explore (Tree * pt, Object book);
void Destroy (Tree * pt, Object obj);
void whichNode (Tree * pt);
void Right (Tree * pt, Tree * save);
char * input (char * str);
char menu (void);
void InputAddItem (Tree * temp);
void InputDestroyItem (Tree * temp);
void InputSeekItem (Tree * temp);
void Ignore (void);
void BeforeInitialize (Tree * pt);
bool Empty (Tree * pt);
void expDestroy (Tree * pt, Tree * adr);
void fullDestruction (Tree * pt, Tree * adr);


int main (void) {

    /* ##### rus-location ######*/
                               ///
    SetConsoleCP(1251);        ///
    SetConsoleOutputCP(1251);  ///
                               ///
    /*##########################*/

    char ch;
    Tree temp;
    BeforeInitialize (&temp);

    while ((ch = menu ()) != 'q') {

      switch (ch) {

        case 'a': InputAddItem (&temp);
                  break;
        case 'd': InputDestroyItem (&temp);
                  break;
        case 's': InputSeekItem (&temp);
                  break;
        case '0': Ignore ();
                  break;

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


/* Operation: Function for ignore.                                */
/* Predconditions: -                                              */
/* Postconditions: switch           ignore.                       */
void Ignore (void) {

    return;

}


/* Operation: Function for subsequent destroy.                    */
/* Predconditions: This function gets pointer of tree.            */
/* Postconditions: To Explore ().                                 */
void InputSeekItem (Tree * temp) {

    if (Empty (temp) == true) {

      puts ("Tree is empty.");
      return;

    }

    Object book;
    puts ("Explore of block. Input title any book:");
    gets (book.title);

    Explore (temp, book);

}


/* Operation: Function for subsequent input.                      */
/* Predconditions: This function gets pointer of tree.            */
/* Postconditions: To AddItem ().                                 */
void InputAddItem (Tree * temp) {

  Object item;

  if (initializeFirst == 0) {

    puts ("Input title of book or input [enter] to exit:");
    input (item.title);

    if (item.title[0] == '\0')
      return;

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

      puts ("Input title next book or input [enter] to exit:");

  }

}


/* Operation: Function for subsequent destroy.                    */
/* Predconditions: This function gets pointer of tree.            */
/* Postconditions: To Destroy ().                                 */
void InputDestroyItem (Tree * temp) {

    if (Empty (temp) == true) {

      puts ("Tree is empty.");
      return;

    }

    Object object;
    puts ("Input title of book, which needing destroy:");
    input (object.title);
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
    pt->size++;

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

    Tree * memTree;
    memTree = (Tree * ) malloc (sizeof (Tree));

    memTree->object = obj;
    memTree->left = NULL;
    memTree->right = NULL;

    expAdd (memTree, pt);

}


/* Operation: Search for a specific element, which need in adding.*/
/* Predconditions: This function gets pointer of tree and         */
/* pointer for previously allocated memory.                       */
/* Postconditions: there is a comparison of elements by branches. */
/* Adding element adds in the end of tree.                        */
void expAdd (Tree * memTree, Tree * pt) {

    if (strcmp ((memTree->object).title, (pt->object).title) < 0) {

        if (pt->left == NULL) {

            pt->left = memTree;
            return;

        }

        else
            expAdd (memTree, pt->left);

    }

    if (strcmp ((memTree->object).title, (pt->object).title) > 0) {

        if (pt->right == NULL) {

            pt->right = memTree;
            return;

        }

        else
            expAdd (memTree, pt->right);

    }

    else {

        puts ("Entered the same title. "
            "You can't do it this way!");

        return;

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

    if (result == true) {

        puts ("This tree contain this book. Adress this block: ");
        printf ("%p\n", str);

    }

    else
        puts ("This tree don't contain this book!");

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

    if (strcmp (book.title, (pt->object).title) < 0)
        ExploreNode (pt->left, book, save);

    if (strcmp (book.title, (pt->object).title) > 0)
        ExploreNode (pt->right, book, save);

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

        printf ("Adress block: %p\n", adr);
        printf ("Title this adress block:");
        puts ((adr->object).title);
        printf ("Author this adress block:");
        puts ((adr->object).author);
        puts ("This node'll destroy. Info:");

        expDestroy (pt, adr);

        return;

    }

    else {

        puts ("So node not found!");

        return;

    }

}


void expDestroy (Tree * pt, Tree * adr) {

    if (pt == adr) {

        puts ("This block for destroying founded.");
        fullDestruction (pt, adr);

        return;

    }

    if (strcmp ((adr->object).title, (pt->object).title) < 0)
        expDestroy (pt->left, adr);

    if (strcmp ((adr->object).title, (pt->object).title) > 0)
        expDestroy (pt->right, adr);

}


void fullDestruction (Tree * pt, Tree * adr) {

    Tree * save;

    if (pt->left == NULL) {

        save = pt;
        pt = pt->right;
        free (pt);

        return;

    }

    if (pt->right == NULL) {

        save = pt;
        pt = pt->left;
        free (pt);

        return;

    }

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
  puts ("d) Destroy node;             q) Exit.     ");
  putchar ('\n');
  puts (FRAME);
  puts ("Please, input one of the variant menu:");


  ch = getchar ();
  while (getchar () != '\n')
  	continue;

  if (strchr ("asdq", ch) == NULL) {

    puts ("This paragraph not found! Repeat again.");
    return '0';

  }

  return ch;

}

void BeforeInitialize (Tree * pt) {

  pt->size = 0;
  pt->left = NULL;
  pt->right = NULL;

}

bool Empty (Tree * pt) {

  return (pt->size == 0) ? true : false;

}

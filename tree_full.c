#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define FRAME "##########################################"
#define LEN 50


typedef struct {

    char title[LEN];
    char author[LEN];

} Object;


typedef struct node {

    Object object;
    struct node * left;
    struct node * right;

} Node;


typedef struct {

	Node * temp;
	int size;

} Tree;


char menu (Tree * pt);
char * input (char * str);
void InitializeTree (Tree * pt);
void Ignore (Tree * pt);
bool expAddItem (Node * pt, Node * mem);
void AddItem (Tree * pt);
void expItem (Tree * pt);
bool expTitleBlock (Node * expBlock, Object objExp, Node ** save);
bool Empty (Tree * pt);
void destroyItem (Tree * pt);
void destruction (Node ** ptr, Object save);
void fullDestruction (Node ** ptr);
void addRight (Node ** Right, Node ** Left);
void fullExplore (Node * x);
void dump (Tree * pt);
void dumpHelp (Node ** memNode);
void record (Node * x, FILE * fp);


int main (void) {

    /* ##### rus-location ######*/
                               ///
    SetConsoleCP(1251);        ///
    SetConsoleOutputCP(1251);  ///
                               ///
    /*##########################*/

    Tree tree;
    Node * x;

    InitializeTree (&tree);

    char ch;
    void ( * pr) (Tree * );

    while ((ch = menu (&tree)) != 'q') {

    	if (ch == 'c')
    		fullExplore (tree.temp);


    	switch (ch) {

    		case 'a': pr = AddItem;
    				  break;

    		case 's': pr = expItem;
    				  break;

    		case 'd': pr = destroyItem;
    				  break;

        	case 'f': pr = dump;
                      break;

    		default:  pr = Ignore;
					  break;

    	}

    	( * pr) (&tree);

    }

	return 0;

}


/* Operation: Devastates the tree.                                */
/* Predconditions: The function gets a pointer to the tree.       */
/* Postconditions: Tree is empty.                                 */
void dump (Tree * pt) {

    if (pt->size == 0) {

        puts ("Tree is empty.");

        return;

    }

    Node * z = pt->temp;

    while (z != NULL)
        dumpHelp (&z);

    pt->size = 0;
    pt->temp = NULL;

}


/* Operation: It helps "The dump" function empty the tree.        */
/* Predconditions: The function gets a pointer on pointer         */
/* to the main node of the tree.                                  */
/* Postconditions: Tree is empty.                                 */
void dumpHelp (Node ** memNode) {

    if (( * memNode)->left == NULL && ( * memNode)->right == NULL) {

        * memNode = NULL;

        return;

    }

    if ((* memNode)->left != NULL)
        dumpHelp (&(( * memNode)->left));

    dumpHelp (&(( * memNode)->right));

}


/* Operation: It prints all tree blocks to the console.           */
/* Predconditions: The function gets a pointer to the main node   */
/* of the tree.                                                   */
/* Postconditions: The tree is displayed.                         */
void fullExplore (Node * x) {

	if (x != NULL) {

		printf ("Title of book: ");
		puts ((x->object).title);
		printf ("Author this book: ");
		puts ((x->object).author);
		putchar ('\n');

		fullExplore (x->left);
		fullExplore (x->right);

	}

}


/* Operation: The function removes selective tree blocks.         */
/* Predconditions: The function gets a pointer of the tree.       */
/* Postconditions: Sample block removed.                          */
void destroyItem (Tree * pt) {

	if (Empty (pt) == true) {

		puts ("Tree is empty");
		return;

	}

	Object objDest;

	puts ("Input title of destroying block:");
	input (objDest.title);

	Node * save, * expBlock = pt->temp;

	if (expTitleBlock (expBlock, objDest, &save) == true) {

		puts ("This block'll destroy.");

		destruction (&(pt->temp), objDest);
		pt->size--;

		return;

	}

	else
		puts ("So block wasn't found.");


}


/* Operation: the function searches for the previously selected   */
/* block and deletes it for right branch.                         */
/* Predconditions: The function gets a pointer on pointer         */
/* of the tree and researched object (block).                     */
/* Postconditions: Sample block removed.                          */
void destruction (Node ** ptr, Object save) {

	if (strcmp (save.title, (( * ptr)->object).title) < 0)
		destruction (&(( * ptr)->left), save);

	else if (strcmp (save.title, (( * ptr)->object).title) > 0)
		destruction (&(( * ptr)->right), save);

	else {

		if (( * ptr)->left == NULL) {

			Node * z;
			z =  * ptr;
			(*ptr) = (*ptr)->right;
			free (z);

		}

		else if (( * ptr)->right == NULL) {

			Node * z;
			z =  * ptr;
			(*ptr) = (*ptr)->left;
			free (z);

		}

		else {

			Node * z;
			z = * ptr;
			addRight (&( * ptr)->right, &( * ptr)->left);
			( * ptr) = ( * ptr)->left;
			free (z);

		}

	}

}


/* Operation: The function looks for the right place to           */
/* join the branch.                                               */
/* Predconditions: The function gets a pointer on pointer         */
/* of the right-tree and pointer on pointer of the left-tree.     */
/* Postconditions: The right branch joins in the right place.     */
void addRight (Node ** Right, Node ** Left) {

	if ( ( * Left)->right == NULL)  {

		( * Left)->right = * Right;

		return;

	}

	addRight (Right, & ( * Left)->right);

}


/* Operation: Object search.                                      */
/* Predconditions: The function gets a pointer of the tree.       */
/* Postconditions: Searched object found.                         */
void expItem (Tree * pt) {

	if (Empty (pt) == true) {

		puts ("Tree is empty.");

		return;

	}

	Object objExp;

	puts ("Input title of exploring block:");
	input (objExp.title);

	Node * save;
	Node * expBlock = pt->temp;

	if (expTitleBlock (expBlock, objExp, &save) == true) {

		puts ("So block was found.");
		printf ("Adress of founded block: %p\n", save);

	}

	else
		puts ("So block wasn't found");



}


/* Operation: Direct search of the object under study.            */
/* Predconditions: The function gets a pointer of the exploring   */
/* block, exploring block and saved pointer for explore.          */ 
/* Postconditions: Searched object found.                         */
bool expTitleBlock (Node * expBlock, Object objExp, Node ** save) {

	if (expBlock == NULL)
		return false;

	if (strcmp (objExp.title, (expBlock->object).title) == 0) {

		* save = expBlock;
		return true;

	}

	if (strcmp (objExp.title, (expBlock->object).title) < 0)
		expTitleBlock (expBlock->left, objExp, save);

	else if (strcmp (objExp.title, (expBlock->object).title) > 0)
		expTitleBlock (expBlock->right, objExp, save);


}


/* Operation: Function Adds an object.                            */
/* Predconditions: The function gets a pointer of the tree.       */
/* Postconditions: Object added in the tree.                      */
void AddItem (Tree * pt) {

	Object item;

	puts ("Input title of book:");
	input (item.title);
	puts ("Input author this book:");
	input (item.author);


	Node * mem;
	mem = (Node * ) malloc (sizeof (Node));

	mem->object = item;
	mem->left = NULL;
	mem->right = NULL;

	if (pt->size == 0) {

		pt->temp = mem;
		pt->size++;

		return;

	}

	else {

		if (expAddItem (pt->temp, mem) == true)
			pt->size++;

		else
			puts ("So element was already created");

	}


}


/* Operation: the function initializes the tree at the             */
/* very beginning of the program.                                  */
/* Predconditions: The function gets a pointer of the tree.        */
/* Postconditions: The tree is initialized with a null pointer     */
/* and zero objects.                                               */
void InitializeTree (Tree * pt) {

	pt->size = 0;
	pt->temp = NULL;

}


/* Operation: The function explores for a place to add an object.  */
/* Predconditions: The function gets a pointer of the main node    */
/* and pointer of the researched object.                           */
/* Postconditions: if the location is found, then the function     */
/* returns true.                                                   */
bool expAddItem (Node * pt, Node * mem) {

	if (strcmp ((mem->object).title, (pt->object).title) < 0) {

		if (pt->left == NULL) {

			pt->left = mem;

			return true;

		}

		else
			expAddItem (pt->left, mem);

	}

	else if (strcmp ((mem->object).title, (pt->object).title) > 0) {

		if (pt->right == NULL) {

			pt->right = mem;

			return true;

		}

		else
			expAddItem (pt->right, mem);

	}

	else
		return false;

}


/* Operation: Function for ignore.                                */
/* Predconditions: The function gets a pointer of the tree.       */
/* Postconditions: switch ignore.                                 */
void Ignore (Tree * pt) {

	return;

}


/* Operation: Check for emptiness.                                */
/* Predconditions: The function gets a pointer of the tree.       */
/* Postconditions: It returns true if the tree is empty.          */
bool Empty (Tree * pt) {

	return (pt->size == 0) ? true : false;

}


/* Operation: MENU               .                                */
/* Predconditions: The function gets a pointer of the tree.       */
/* Postconditions: Launch menu.                                   */
char menu (Tree * pt) {

	char ch;

	puts (FRAME);
	puts ("                     MENU:                      ");
	putchar ('\n');
	puts ("a) Add items;                c) Check full list;");
	puts ("d) Destroy node;             f) Full cleaning;  ");
	puts ("s) Seek item;                r) Record tree;    ");
  puts ("q) QUIT.                                        ");
	putchar ('\n');
  printf ("Root adress: %p\n", pt->temp);

  /*

    printf ("left-branch adress: %p\n", (tree.temp)->left);
    printf ("right-branch adress: %p\n", (tree.temp)->right);

*/
	puts (FRAME);
	putchar ('\n');
	printf ("Amount of elements in the tree: %d\n", pt->size);
	puts ("Please, input one of the variant menu:");


	ch = getchar ();
	while (getchar () != '\n')
		continue;

	return ch;

}


/* Operation: This function fills the string.                     */
/* Predconditions: This function gets pointer of string.          */
/* Postconditions: This function return pointer of this string.   */
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

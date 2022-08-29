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


int main (void) {

    /* ##### rus-location ######*/
                               ///
    SetConsoleCP(1251);        ///
    SetConsoleOutputCP(1251);  ///
                               ///
    /*##########################*/

    Tree tree;
    
    InitializeTree (&tree);
    
    char ch;
    void ( * pr) (Tree * );
    
    while ((ch = menu (&tree)) != 'q') {
    	
    	switch (ch) {
    		
    		case 'a': pr = AddItem;
    				  break;
    		
    		case 's': pr = expItem;
    				  break;
    				  
    		case 'd': pr = destroyItem;
    				  break;
    				  
    		default:  pr = Ignore;
					  break;
    		
    	}
    	
    	( * pr) (&tree);
    	
    	printf ("Root adress: %p\n", tree.temp);
    	printf ("left-branch adress: %p\n", (tree.temp)->left);
    	
    	
    }
    
    
	return 0;
	
}


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


void destruction (Node ** ptr, Object save) {
		
	if (strcmp (save.title, (( * ptr)->object).title) < 0)
		destruction (&(( * ptr)->left), save);
	
	else if (strcmp (save.title, (( * ptr)->object).title) > 0)
		destruction (&(( * ptr)->right), save);
	
	else {
		
		if (( * ptr)->right == NULL) {
		
			Node * z;
			z =  * ptr;
			(*ptr) = (*ptr)->left;
			free (z);
		
		}
	
		else if (( * ptr)->right == NULL) {
		
			Node * z;
			z =  * ptr;
			(*ptr) = (*ptr)->left;
			free (z);
		
		}
		
		else
			exit (228);
		
	}
	
}


void fullDestruction (Node ** ptr) {
	
	Node * z;
	
	if (( * ptr)->right == NULL) {
		
		z =  * ptr;
		(*ptr) = (*ptr)->left;
		free (z);
		
	}
	
	else if (( * ptr)->left == NULL) {
		
		z =  * ptr;
		(*ptr) = (*ptr)->right;
		free (z);
		
	}
	
	
} 


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




bool expTitleBlock (Node * expBlock, Object objExp, Node ** save) {
	
	if (expBlock == NULL)
		return false;
	
	if (strcmp (objExp.title, (expBlock->object).title) == 0) {
		
		* save = expBlock;
		return true;
		
	}
	
	if (strcmp (objExp.title, (expBlock->object).title) < 0)
		expTitleBlock (expBlock->left, objExp, save);
	
	if (strcmp (objExp.title, (expBlock->object).title) > 0)
		expTitleBlock (expBlock->right, objExp, save);
	
	
}


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

void InitializeTree (Tree * pt) {
	
	pt->size = 0;
	pt->temp = NULL;
	
}


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


void Ignore (Tree * pt) {
	
	return;
	
}


bool Empty (Tree * pt) {
	
	return (pt->size == 0) ? true : false;
	
}


char menu (Tree * pt) {

	char ch;

	puts (FRAME);
	puts ("                  MENU:                  ");
	putchar ('\n');
	puts ("a) Add items;                s) Seek item;");
	puts ("d) Destroy node;             q) Exit.     ");
	putchar ('\n');
	puts (FRAME);
	putchar ('\n');
	printf ("Amount of elements in the tree: %d\n", pt->size);
	puts ("Please, input one of the variant menu:");


	ch = getchar ();
	while (getchar () != '\n')
		continue;

	return ch;

}


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

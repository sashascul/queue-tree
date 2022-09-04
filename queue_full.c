#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define LEN 50
#define FRAME "##########################################"


typedef struct {

    char title[LEN];
    char author[LEN];

} Object;


typedef struct node {

    Object object;
    struct node * next;

} Node;


typedef struct queue {

    Node * node;
    int size;

} Queue;


void InitializeQueue (Queue * pt);
char menu (Queue * pt);
char * input (char * str);
void AddItem (Queue * pt);
bool exploreQueue (Node * pt, Node * mem);
void Ignore (Queue * pt);
void list (Node * pt, int i);
void listPrint (Queue * pt);
void destroyItem (Queue * pt);
void destroyNode (Queue * pr, Node ** pt);
bool empty (Queue * pt);


int main (void) {

    Queue temp;
    char ch;

    InitializeQueue (&temp);
    void ( * pr) (Queue * );

    while ((ch = menu (&temp)) != 'q') {

        switch (ch) {

            case 'a': pr = AddItem;
                      break;
            
            case 'l': pr = listPrint;
            		  break;
            		  
            case 'd': pr = destroyItem;
            		  break;

            default:  pr = Ignore;
                      break;

        }

        ( * pr) (&temp);

    }

    puts ("Program the end!");


    return 0;

}


/* Operation: This function destroy the block.                    */
/* Predconditions: This function gets pointer of the queue.       */
/* Postconditions: This function uses other function.             */
void destroyItem (Queue * pt) {
	
	destroyNode (pt, &(pt->node));
	
}


/* Operation: This function destroy the block.                    */
/* Predconditions: This function gets pointer of the queue and    */
/* pointer on pointer of the main node.                           */ 
/* Postconditions: The queue of shifting on one cell right.       */
void destroyNode (Queue * pr, Node ** pt) {
	
	if (empty (pr) == true) {
		
		puts ("Tree is empty");
		return;
		
	}
	
	Node * save = * pt;
	* pt = ( * pt)->next;
	free (save);
	pr->size --;
	
}


/* Operation: Ignore.                                             */
/* Predconditions: This function gets pointer of the queue.       */
/* Postconditions: Output message about not finding variant.      */
void Ignore (Queue * pt) {

    puts ("So variant of menu don't found.");
    return;

}


/* Operation: This function initializes the tree.                 */
/* Predconditions: This function gets pointer of the queue.       */
/* Postconditions: NULL-initialization.                           */
void InitializeQueue (Queue * pt) {

    pt->node = NULL;
    pt->size = 0;

}


/* Operation: This function can add the block.                    */
/* Predconditions: This function gets pointer of the queue.       */
/* Postconditions: Element was add in the tree.                   */
void AddItem (Queue * pt) {

    Object object;
    puts ("Input title of book:");
    input (object.title);
    puts ("Input author this book:");
    input (object.author);


    Node * mem;
    mem = (Node * ) malloc (sizeof (Node));
    mem->object = object;
    mem->next = NULL;
    
    if (pt->size == 0) {
    	
    	pt->size ++;
    	pt->node = mem;
    	
    }

    else {
    	
    	if (exploreQueue (pt->node, mem) == true)
        	pt->size++;
    	
    }

}


/* Operation: This function can print list with all objects and   */
/* allocates memory for a list.                                   */
/* Predconditions: This function gets pointer of the queue.       */
/* Postconditions: List was print.                                */
void listPrint (Queue * pt) {
	
	if (empty (pt) == true) {
		
		puts ("Tree is empty");
		return;
		
	}
	
	Node * mem;
	mem = pt->node;
	int i = 1;
	
	list (mem, i);
	
}


/* Operation: This function print a list.                         */
/* Predconditions: This function gets pointer of the allocated    */
/* memory and integer value.                                      */
/* Postconditions: List was print.                                */
void list (Node * pt, int i) {
	
	printf ("Title %d: ", i);
	puts ((pt->object).title);
	printf ("Author %d: ", i);
	puts ((pt->object).author);
	i++;
	
	if (pt->next == NULL)
		return;
	
	list (pt->next, i);
	
}


/* Operation: This function explores the block.                   */
/* Predconditions: This function gets pointer of the tree         */
/* and pointer of the allocated memory.                           */
/* Postconditions: Desired object was found.                      */
bool exploreQueue (Node * pt, Node * mem) {

    if (strcmp ((pt->object).title, (mem->object).title) == 0) {

        puts ("So element are containing in the queue.");
        return false;

    }

    if (pt->next == NULL) {

        pt->next = mem;
        return true;

    }

    exploreQueue (pt->next, mem);

}



/* Operation: Check for emptiness.                                */
/* Predconditions: The function gets a pointer of the queue.      */
/* Postconditions: It returns true if the queue is empty.         */
bool empty (Queue * pt) {
	
	return (pt->size == 0) ? true : false;
	
}


/* Operation: MENU               .                                */
/* Predconditions: The function gets a pointer of the queue.      */
/* Postconditions: Launch menu.                                   */
char menu (Queue * pt) {

    char ch;

    puts (FRAME);
    puts ("                  MENU:                 ");
    puts ("a) Add element;      d) Destroy element;");
    puts ("l) list;             q) QUIT.           ");
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

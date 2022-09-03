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

            default:  pr = Ignore;
                      break;

        }

        ( * pr) (&temp);

    }


    puts ("Program the end!");


    return 0;

}


void destroyElement (Queue * pt) {
	
	bool flag = false;
	
	expDestroy (pt, pt->next, flag);
	
	
}


void expDestroy (Node * pt, Node * save, bool flag) {
	
	if (flag == true) {
		
		pt = save;
		free (save);
		
	}
	
	if (pt->next == NULL)
		return;
		
	save = pt;
	flag = true;
	
	expDestroy (pt->next, save, flag);
	
	
}


void Ignore (Queue * pt) {

    puts ("So variant of menu don't found.");
    return;

}


void InitializeQueue (Queue * pt) {

    pt->node = NULL;
    pt->size = 0;

}


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


void listPrint (Queue * pt) {
	
	Node * mem;
	mem = pt->node;
	int i = 1;
	
	list (mem, i);
	
}


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

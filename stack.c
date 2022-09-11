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
    struct node * next;

} Node;


typedef struct {

	Node * temp;
	int size;

} Stack;


char * input (char * str);
char menu (Stack * st);
void InitializeStack (Stack * st);
void addNode (Node * pt, Node * mem);
void AddItem (Stack * st);
void list (Node * x, Stack st);
bool destroyItem (Node ** del);
bool empty (Stack * st);
void accDestroy (Stack * st);


int main (void) {
	
	Stack stack;
	char ch;
	InitializeStack (&stack);
	
	while ((ch = menu (&stack)) != 'q') {
		
		switch (ch) {
			
			case 'a': AddItem (&stack);
					  break;
					  
			case 'd': accDestroy (&stack);
					  break;
			
			case 'l': list (stack.temp, stack);
					  break;
			
			default:  break;
			
		}
		
	}
	
	puts ("Program the end.");

	return 0;
	
}


bool empty (Stack * st) {
	
	return (st->size == 0) ? true : false;
	
}


void accDestroy (Stack * st) {
	
	if (empty (st) == true) {
		
		puts ("Tree is empty.");
		
		return;
		
	}
	
	if (destroyItem (&(st->temp)) == true)
		st->size--;
	
}


bool destroyItem (Node ** del) {
	
	if (( * del)->next == NULL) {
		
		Node * dest;
		dest = * del;
		* del = NULL;
		free (dest);
		
		return true;
		
	}
	
	destroyItem (&(( * del)->next));
	
}


void AddItem (Stack * st) {
	
	Object object;
	puts ("Input title of book:");
	input (object.title);
	puts ("Input author this book:");
	input (object.author);
	
	Node * mem;
	mem = (Node * ) malloc (sizeof (Node));
	
	mem->object = object;
	mem->next = NULL; 
	
	if (st->size == 0) {
		
		st->temp = mem;
		st->size++;
		
		return;
		
	}
	
	else {
		
		addNode (st->temp, mem);
		st->size++;
		
	}
	
}


void addNode (Node * pt, Node * mem) {
	
	
	if (pt->next == NULL) {
		
		pt->next = mem;
		
		return;
		
	}
	
	addNode (pt->next, mem);
	
}


void list (Node * x, Stack st) {
	
	if (st.size == 0) {
		
		puts ("Tree is empty.");
		
		return;
		
	}
	
	if (x != NULL) {
		
		puts ((x->object).title);
		puts ((x->object).author);
		putchar ('\n');
		list (x->next, st);
		
		return;
		
	}
		
}


void InitializeStack (Stack * st) {
	
	st->temp = NULL;
	st->size = 0;
	
}


/* Operation: MENU               .                                */
/* Predconditions: The function gets a pointer of the queue.      */
/* Postconditions: Launch menu.                                   */
char menu (Stack * st) {

    char ch;

    puts (FRAME);
    puts ("                  MENU:                 ");
    puts ("a) Add element;      d) Destroy element;");
    puts ("l) list;             q) QUIT.           ");
    puts (FRAME);
    putchar ('\n');
    printf ("Amount of elements in the stack: %d\n", st->size);
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

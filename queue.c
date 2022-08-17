#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXQUEUE 10

typedef int Item;

struct node {

  Item item;
  struct node *  next;

};

typedef struct node Node;

struct queue {

  Node * front;
  Node * rear;
  int items;

};

typedef struct queue Queue;

static void CopyToNode (Item item, Node * pn) {

  pn->item = item;

}

static void CopyToItem (Node * pn, Item * pi) {

  * pi = pn->item;

}

void InitializeQueue (Queue * pq) {

  pq->front = NULL;
  pq->rear = NULL;
  pq->items = 0;

}

bool QueueIsFull (const Queue * pq) {

  if (pq->items == MAXQUEUE)
    return true;

  return false;
}

bool QueueIsEmpty (const Queue * pq) {

  if (pq->items == 0)
    return true;

  return false;
}

int QueueItemCount (const Queue * pq) {

  return pq->items;

}

bool EnQueue (Item item, Queue * pq) {

  Node * pnew;

  if (QueueIsFull(pq))
    return false;

  pnew = (Node *) malloc (sizeof (Node));

  if (pnew == NULL) {

    puts ("Memory not found");
    exit (1);

  }

  CopyToNode (item, pnew);
  pnew->next = NULL;

  if (QueueIsEmpty (pq))
    pq->front = pnew;

  else
    pq->rear->next = pnew;

  pq->rear = pnew;
  pq->items++;

  return true;
}

bool DeQueue (Item * pitem, Queue * pq) {

  Node * pt;

  if (QueueIsEmpty (pq))
    return false;

  CopyToItem (pq->front, pitem);
  pt = pq->front;
  pq->front = pq->front->next;
  free (pt);
  pq->items--;

  if (pq->items == 0)
    pq->rear = NULL;

  return true;

}

void EmptyTheQueue (Queue * pq) {

  Item dummy;

  while (!QueueIsEmpty (pq))
    DeQueue (&dummy, pq);

}



int main (void) {

  Queue line;
  Item temp;
  char ch;

  InitializeQueue (&line);
  puts ("Input d to delete equation or input a to output from program");

  while ((ch = getchar ()) != 'q') {

    if (ch != 'a' && ch != 'd')
      continue;

    if (ch == 'a') {

      printf ("Z-number for adding: ");
      scanf ("%d", &temp);

      if (!QueueIsFull (&line)) {

        printf ("%d in queue\n", temp);
        EnQueue (temp, &line);

      }

      else
        puts ("Queue is full!");

      }

    else {

      if (QueueIsEmpty (&line))
        puts ("Not values for deleting!");

      else {

        DeQueue (&temp, &line);
        printf ("Deleting %d from queue\n", temp);

      }

    }

    printf("%d злемент(ов) в очереди\n", QueueItemCount(&line));
    puts ("Введите а, чтобы добавить, d, чтобы удадить, или q для выхода из программы:");

    }



  EmptyTheQueue(&line);
  puts("Программа завершена.");

  return 0;
}

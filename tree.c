#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

#define MAXITEMS 10
#define SLEN 30


typedef struct item {

  char petname[20];
  char petkind[20];

} Item;

typedef struct trnode {

  Item item;
  struct trnode * left;
  struct trnode * right;

} Trnode;

typedef struct free {

  Trnode * root;
  int size;

} Tree;

typedef struct pair {

  Trnode * parent;
  Trnode * child;

} Pair;


void InitializeTree (Tree * ptree);
bool TreeIsEmpty (const Tree * ptree);
bool TreeIsFull (const Tree * ptree);
int TreeItemCount (const Tree * ptree);
bool AddItem (const Item * pi, Tree * ptree);
bool InTree (const Item * pi, const Tree * ptree);
bool DeleteItem (const Item * pi, Tree * ptree);
void Traverse (const Tree * ptree, void (*pfun)(Item item));
void DeleteAll (Tree * ptree);
static Trnode * MakeNode (const Item * pi);
static bool ToLeft (const Item * i1, const Item * i2);
static bool ToRight (const Item * i1, const Item * i2);
static void AddNode (Trnode * new_node, Trnode * root);
static void InOrder (const Trnode * root, void (* pfun)(Item item));
static Pair SeekItem (const Item * pi, const Tree * ptree);
static void DeleteNode (Trnode ** ptr);
static void DeleteAllNodes (Trnode * ptr);
char menu (void);
void addpet (Tree * pt);
void droppet (Tree * pt);
void showpets (const Tree * pt);
void findpet (const Tree * pt);
void printitem (Item item);
void uppercase (char * str);
char * s_gets(char * st, int n);


int main (void) {

  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  Tree pets;
  char choise;

  InitializeTree (&pets);

  while ((choise = menu ()) != 'q') {

    switch (choise) {

      case 'a': addpet (&pets);
                break;

      case 'l': showpets (&pets);
                break;

      case 'f': findpet (&pets);
                break;

      case 'n': printf ("%d животных в клубе\n",\
                TreeItemCount (&pets));
                break;

      case 'd': droppet (&pets);
                break;

      default: puts ("Ошибка в switch!");

    }

  }

  DeleteAll (&pets);

  puts ("Программа завершена");

  return 0;

}

void InitializeTree (Tree * ptree) {

  ptree->root = NULL;
  ptree->size = 0;

}

bool TreeIsEmpty (const Tree * ptree) {

  if (ptree->root == NULL)
    return true;

  else
    return false;

}

bool TreeIsFull (const Tree * ptree) {

  if (ptree->size == MAXITEMS)
    return true;

  else
    return false;

}

int TreeItemCount (const Tree * ptree) {

  return ptree->size;

}

bool AddItem (const Item * pi, Tree * ptree) {

  Trnode * new_node; // создание узла
  if (TreeIsFull (ptree)) {

    fprintf (stderr, "Дерево переполнено\n");
    return false;

  }

  if (SeekItem (pi, ptree).child != NULL) {

    fprintf (stderr, "Дерево переполнено\n");
    return false;

  }

  new_node = MakeNode (pi);

  if (new_node == NULL) {

    fprintf (stderr, "Не удалось создать узел\n");
    return false;

  }

  if (ptree->root == NULL)
    ptree->root = new_node;

  else
    AddNode (new_node, ptree->root);

  return true;

}

bool InTree (const Item * pi, const Tree * ptree) {

  return (SeekItem (pi, ptree).child == NULL) ? false : true;

}

bool DeleteItem (const Item * pi, Tree * ptree) {

  Pair look;
  look = SeekItem (pi, ptree);

  if (look.child == NULL)
    return false;

  if (look.parent == NULL)
    DeleteNode (&ptree->root);

  else if (look.parent->left == look.child)
    DeleteNode (&look.parent->left);

  else
    DeleteNode (&look.parent->right);

  ptree->size--;

  return true;

}

void Traverse (const Tree * ptree, void (*pfun)(Item item)) {

  if (ptree != NULL)
    InOrder (ptree->root, pfun);

}

void DeleteAll (Tree * ptree) {

  if (ptree != NULL)
    DeleteAllNodes(ptree->root);

  ptree->root = NULL;
  ptree->size = 0;

}

static Trnode * MakeNode (const Item * pi) {

  Trnode * new_node;
  new_node = (Trnode * ) malloc (sizeof (Trnode));

  if (new_node != NULL) {

    new_node->item = *pi;
    new_node->left = NULL;
    new_node->right = NULL;

  }

  return new_node;

}

static bool ToLeft (const Item * i1, const Item * i2) {

  int comp1;

  if ((comp1 = strcmp (i1->petname, i2->petname)) < 0)
    return true;

  else if (comp1 == 0 && strcmp (i1->petkind, i2->petkind) < 0)
    return true;

  else
    return false;

}

static bool ToRight (const Item * i1, const Item * i2) {



}

static void AddNode (Trnode * new_node, Trnode * root) {

  if (ToLeft (&new_node->item, &root->item)) {

    if (root->left == NULL)
      root->left = new_node;

    else
      AddNode (new_node, root->left);

  }

  if (ToRight (&new_node->item, &root->item)) {

    if (root->right == NULL)
      root->right = new_node;

    else
      AddNode (new_node, root->right);

  }

  else {

    fprintf(stderr, "Ошибка\n");
    exit (1);

  }

}

static Pair SeekItem (const Item * pi, const Tree * ptree) {

  Pair look;
  look.parent = NULL;
  look.child = ptree->root;

  if (look.child == NULL)
    return look;

  while (look.child != NULL) {

    if (ToLeft (pi, &(look.child->item))) {

      look.parent = look.child;
      look.child = look.child->left;

    }

    else if (ToRight (pi, &look.child->item)) {

      look.parent = look.child;
      look.child = look.child->right;

    }

    else
      break;

  }

  return look;

}

static Pair Seekltem(const Item * pi, const Tree * ptree) {

  Pair look;
  look.parent = NULL;
  look.child = ptree->root;

  if (look.child == NULL)
    return look;

  while (look.child != NULL) {

    if (ToLeft (pi, & (look. child->item))) {

      look.parent = look.child;
      look.child = look.child->left;

    }

      else if (ToRight(pi, &(look.child->item))) {

        look.parent = look.child;
        look.child = look.child->right;

      }

      else
        break;

}

return look;

}

static void DeleteAllNodes(Trnode * root) {

  Trnode * pright;

  if (root != NULL) {

    pright = root->right;
    DeleteAllNodes(root->left);
    free(root);
    DeleteAllNodes(pright);

  }

}

static void InOrder (const Trnode * root, void (*pfun) (Item item)) {

  if (root != NULL) {

    InOrder(root->left, pfun);
    (*pfun)(root->item);
    InOrder(root->right, pfun);

  }

}

static void DeleteNode (Trnode ** ptr) {

  Trnode * temp;

  if ((*ptr)->left == NULL) {

    temp = *ptr;
    *ptr = (*ptr)->right;
    free(temp);

  }

  else if ( (*ptr)->right == NULL) {

    temp = *ptr;
    *ptr = (*ptr)->left;
    free(temp);

  }

  else {

    for (temp = (*ptr)->left; temp->right != NULL; temp = temp->right)
      continue;

  temp->right = (*ptr)->right;
  temp = *ptr;
  *ptr =(*ptr)->left;
  free (temp);

  }

}

char menu(void) {

  int ch;
  puts ("Программа членства в клубе Nerfville Pet Cli^");
  puts("Введите букву, соответствующую вашему выбору:");
  puts("а) добавление животного 1) вывод списка животных");
  puts("п) количество животных f) поиск животных");
  puts("d) удаление животного q) выход");

  while ((ch = getchar ()) != EOF) {

      while (getchar() != '\n')
        continue;

      ch = tolower (ch) ;
      if (strchr("alrfndq",ch) == NULL)
        puts("Введите букву а, 1, f, n, d или q:");

      else
        break;

  }

  if (ch == EOF)
    ch = 'q';

  return ch;

}

void addpet(Tree * pt) {

  Item temp;

  if (TreeIsFull (pt))
    puts("В клубе больше нет мест!");

  else {

    puts("Введите кличку животного:");
    s_gets(temp.petname, SLEN);
    puts ("Введите вид животного:");
    s_gets(temp.petkind, SLEN);
    uppercase(temp.petname);
    uppercase(temp.petkind);
    AddItem(&temp, pt) ;

  }

}

void showpets(const Tree * pt) {

  if (TreeIsEmpty(pt))
    puts("Записи отсутствуют!");

  else
    Traverse(pt, printitem);

}

void printitem (Item item) {

  printf ("ЖИвотное: %-19s Вид: %-19s\n", item.petname, item.petkind);

}

void findpet(const Tree * pt) {

  Item temp;

  if (TreeIsEmpty(pt)) {

    puts("Записи отсутствуют!");
    return;

  }

  puts("Введите кличку животного, которое хотите найти:");
  s_gets(temp.petname, SLEN);
  puts("Введите вид животного:");
  s_gets(temp.petkind, SLEN);
  uppercase(temp.petname);
  uppercase(temp.petkind);
  printf ("%s по имени %s ", temp.petkind, temp.petname);

  if (InTree(&temp, pt))
    printf("является членом клуба.\n");

  else
    printf("не является членом клуба.\n");

}

void droppet(Tree * pt) {

  Item temp;

  if (TreeIsEmpty (pt)) {
    puts("Записи отсутствуют!");

  return;

  puts("Введите кличку животного, которое нужно исключить из клуба:");
  s_gets(temp.petname, SLEN);
  puts ("Введите вид животного:");
  s_gets(temp.petkind, SLEN);
  uppercase(temp.petname);
  uppercase(temp.petkind);
  printf ("%s по имени %s ", temp.petkind, temp.petname);

  if (DeleteItem(&temp, pt))
    printf("исключен(а) из клуба.\n");

  else
    printf("e является членом клуба. \n");

  }

}

void uppercase (char * str) {

  while (*str) {

    *str = toupper(*str);
    str++;

  }

}

char * s_gets (char * st, int n) {

  char * ret_val;
  char * find;
  ret_val = fgets(st, n, stdin);

  if (ret_val) {

    find = strchr(st, '\n');
    if (find)
    *find = '\0';

  else
    while (getchar() != '\n')
      continue;

}

return ret_val;

}

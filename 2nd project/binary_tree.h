#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define eq(A, B) (key(A) == key(B))

/*struct*/
typedef struct product {
  unsigned long int key;
  int stock;
} * products;

typedef struct node {
  products item;
  struct node *l;
  struct node *r;
} * link;

link head;
products maxProd;

/*prototypes*/
link new (products item, link l, link r);
link search(link h, unsigned long int key);
link insert(link x, products prod);
link max(link x);
void visit(products x);
void traverse(link x);
void calc_max(link x);
link delete (link x, unsigned long int chave);
int counter(link h);
int less_key(unsigned long int a, unsigned long int b);
void clear_node(link x);

#endif
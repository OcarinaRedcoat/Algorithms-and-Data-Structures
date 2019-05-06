#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"
#include "main.h"
#include "product_lib.h"

void init() { head = NULL; }

void command_a() {
  link temp = NULL;
  unsigned long int key;
  int stock;
  scanf("%lx%d", &key, &stock);
  temp = search(head, key);
  if (temp == NULL)
    head = insert(head, newProduct(key, stock));
  else {
    if (temp->item->stock + stock > 0)
      temp->item->stock += stock;
    else
      temp->item->stock = 0;
  }
}

void command_l() { traverse(head); }

void command_m() {
  maxProd = NULL;
  calc_max(head);
  if (maxProd != NULL) visit(maxProd);
}

void command_r() {
  unsigned long int key;
  scanf("%lx", &key);
  head = delete (head, key);
}

void command_x() {
  printf("%i\n", counter(head));
  clear_node(head);
}

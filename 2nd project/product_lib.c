#include "product_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"

products newProduct(unsigned long int key, int stock) {
  products x = (products)malloc(sizeof(struct node));
  x->key = key;
  x->stock = stock;
  return x;
}

/* the difference between the newProd and the newProduct is that the
newProd has the struct of product and the new newProduct has the struct
of node */

void delProduct(products x) { free(x); }
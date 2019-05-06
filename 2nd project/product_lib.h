#ifndef PRODUCT_LIB_H
#define PRODUCT_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"

products newProduct(unsigned long int key, int stock);
void delProduct(products x);

#endif

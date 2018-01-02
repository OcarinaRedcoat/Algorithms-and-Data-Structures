#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "binary_tree.h"
#include "product_lib.h"

int maximun, count;

products newProd(unsigned long int key, int stock){
	products x=(products)malloc(sizeof(struct product));
	x->key=key; 
	x->stock=stock;
	return x;
}

/* the difference between the newProd and the newProduct is that the
newProd has the struct of product and the new newProduct has the struct
of node */

// Funcao Nova Arvore
link new(products item, link l, link r){ 
	link new=(link)malloc(sizeof(struct node)); 
	new->item=item;	
	new->l=l;
	new->r=r; 
	return new; 
} 

// Funcao Search
link search(link h, unsigned long int key) { // link search(link h, product v)
	if (h==NULL)  return NULL; 
	if (eq(key, h->item->key))	return h; 
	if (less(key, h->item->key))	return search(h->l, key); 
	else	return search(h->r, key); 
} 

// Funcao Insert
link insert(link h, products prod) { 
	products p=prod; 
	if (h==NULL){
		if (h->item->key<0)	h->item->key=0;
		return new(prod, NULL, NULL); 
	}
	if (p->key==h->item->key)	h->item->stock+=p->stock;
	else if (less(p->key, h->item->key))	h->l=insert(h->l, prod); 
	else	h->r=insert(h->r, prod); 
	return h; 
} 

//Funcao Max e Min
link max(link h) { 
	if (h==NULL || h->r==NULL) return h; 
	else	return max(h->r); 
} 

// Funcao Visit
void visit(products x) { printf("%08lx %i\n", x->key, x->stock); } //funcao que imprime um produto da arvore

void traverse(link x) {
	//funcao que ira imprimir todos os elementos da arvore ordenadamente (travessia in-order)
	if (x==NULL)	return; 
	traverse(x->l); 
	visit(x->item); 
	traverse(x->r); 
}


void calc_max(link x) {
	if (x==NULL)	return;
	
	calc_max(x->l); 
	if(maxProd==NULL) maxProd= x->item;
	if(maxProd->stock < x->item->stock) maxProd= x->item;
	calc_max(x->r); 
}


// Funcao Delete
link delete(link h, unsigned long int k) {
	//funcao que ira eliminar um produto da arvore
	if(h==NULL) return h;     
	else if (less(k, h->item->key)) h->l=delete(h->l,k); 
	else if (less(h->item->key, k)) h->r=delete(h->r,k) ; 
	else { 
		if (h->l !=NULL && h->r !=NULL){ //remocao de um node interno
            link aux=max(h->l); 
            {products x =h->item; h->item=aux->item; aux->item=x; }             
			h->l= delete(h->l, aux->item->key); 
        } 
		else { //se o node nao tiver filhos ou se tiver apenas um filho
		    link aux=h; 
			if ( h->l == NULL && h->r == NULL ) h=NULL; 
			else if (h->l==NULL) h=h->r; 
			else h=h->l; 
			delProduct(aux->item);  
			free(aux); 
        }    
    } 
	return h; 
}

// Funcao Counter
int counter(link h) { 
	if (h==NULL)	return 0; 
	else	return counter(h->r)+counter(h->l)+1; 
}


int less_key(unsigned long int x, unsigned long int y){
	if (x<y)	return 0;
	else	return 1;
}

//funcao que serve para dar free da arvore
void clear_node(link x){ 
	if (x == NULL) return; 
	
	clear_node(x->l); 
	clear_node(x->r);
	
	free(x->item);
	free(x);
	
}
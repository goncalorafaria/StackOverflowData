#include "Bloco.h"
#include <stdlib.h>
#include <string.h>
#include "date.h"

void *createPost(){
	Post x = malloc (sizeof (struct post));
	strcpy((char*)x->nome,"Nop");
  	x->id = 0;
	x->type = 0;
	x->fundador = 0;
	//x->data = malloc (sizeof(struct date));
	x->data = createDate ( 0 , 0 ,0);
	return x;
}


// create -- destroy -- getters (P e respostas)

void *createUtil(){
	Util x = malloc (sizeof (struct utilizador));
	strcpy((char*)x->nome,"Nop");
	strcpy((char*)x->bio, "Nop");
	x->Q = 0;
	x->A = 0;
	x->id = 0;
	return x;
}

void destroyUtil( void* x ){
	Util y = (Util) x;
	free(y);
}

/*
void destroyUtil_key( void* x ){
	Util y = (Util) x;
	free(y);
}
*/

void setDate ( Post x ,int d,int m ,int a){
	free_date(x->date);
	x->date = createDate(d,m,a);
}

void destroyPost( void* x ){
	Post y = (Post) x;
	free_date(y->data) ;
	free(y);
}

/*
void destroyPost_key( void* x ){
	unsigned int * y = (unsigned int *) x;
	free(y);
}
*/



/*

// Create a Util with some info

void *createUtil_p (char *n , int p , int r , int f ) {
	Util x = malloc (sizeof (struc utilizador));
	x -> nome = n;
	x -> perguntas = p;
	x -> respostas = r;
	x -> fundador = f; 
}

// Create a post with some info
void *createPost_p(int id , char* name){
	Post x = malloc (sizeof (struct post));
	x -> ID = id ; 
	x -> nome = name;
}



// GETTERS!
int getQ(Util x) {
	return ( x->perguntas );
}

int getA(Util x) {
	return ( x->respostas);
}

//SETTERS!

void setQ ( Post x , int q ) {
	x
}

*/






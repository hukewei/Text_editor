#define N 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct node {
	char data[N];
	int size;
	struct node* next;
	struct node* prev;
}node;

typedef struct text {
	node* head;
	node* tail;
	int size;
	int count;
}text;

typedef struct iter {
	node* ptr;
	int icase;
}iter;

node* create_node();
text* create_text();
void free_text(text *t);
iter *create_iter_at_begin (text *t);
void free_iter (iter *pos);
void move_foward_iter (iter *pos, int n);
void move_backward_iter (iter *pos, int n);
float evalmen_text(text* t);
int vide_text(text* t);//tester si le text est vide ou pas,si vide, retourne 1;
void ajoute_node(text* t);//ajoute une node vide dans la tete de text;
void append_text(text* t, char* s);
void push_text(text* t, char* s);
void show_text(text* t, iter* pos);
void insert_text(text* t, iter* pos, char* s);
node* trouve_piece(text* t);
int iter_pos(text* t, iter* pos);
void reset_iter(text* t, iter* pos, int n);
void shift_mot(text* t, node* p);
void shift_text(text* t, iter* pos);
void delete_text(text *t, iter *pos, int n);
void sauve_text(FILE *fp,text *t);

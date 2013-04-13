#include "tp3.h"
node* create_node()//O(1)
{
	node* p = (node*)malloc(sizeof(node));
	p->size=0;
	p->next=NULL;
	p->prev=NULL;
	return p;
}

text* create_text(){//O(1)
	text* p = (text*)malloc(sizeof(text));
	p->count = 0;
	p->size = 0;
	p->head = NULL;
	p->tail = NULL;
	return p;
}

void free_text(text *t){//O(n)
	node* p = t->head;
	node* tmp;
	while (p->next != NULL){
		tmp = p;
		p = p->next;
		free(tmp);
	}
	free(p);
	free(t);
}

iter *create_iter_at_begin (text *t){//O(1)
	iter *cursur = (iter*)malloc (sizeof(iter));
	cursur->ptr = t->head;
	cursur->icase = 0;
	return cursur;
}

void free_iter (iter *pos){//O(1)
	free (pos);
}

void move_foward_iter (iter *pos, int n){//O(n)
	int c;
	c = pos->icase;
	if (n == 0)
		return;
	if (c + n < pos->ptr->size)
		pos->icase = pos->icase + n;
	else{
		n = n-(pos->ptr->size - pos->icase);
		while (pos->ptr->next!= NULL && pos->ptr->next->size - 1 <= n ){
			pos->ptr=pos->ptr->next;
			n = n - pos->ptr->size;
		}
		if (pos->ptr->next!= NULL && n < pos->ptr->size ){
			pos->ptr=pos->ptr->next;
			pos->icase = n;
		}
		else if(pos->ptr->next == NULL && n >= pos->ptr->size)
			pos->icase = pos->ptr->size -1;
		else
			pos->icase = n;
	}
}

void move_backward_iter (iter *pos, int n){//O(n)
	int c;
	c = pos->icase;
	if (c == -1)
		return;
	if (c - n >= 0)
		pos->icase = pos->icase - n;
	else{
		n = n- (pos->icase);
		while((pos->ptr->prev!=NULL) && (n > pos->ptr->prev->size) ){
			pos->ptr = pos->ptr->prev;
			n = n - pos->ptr->size;
		}
		if ( (pos->ptr->prev!= NULL) && (n<= pos->ptr->prev->size) ){
			pos->ptr = pos->ptr->prev;
			pos->icase = (pos->ptr->size - n);
		}
		else
			pos->icase = 0;
	}
}

float evalmen_text(text* t){//O(1)
	float eff;
	if (t->head==NULL)
		return 1.0;
	if (t->count == 1 ) return 1;
	eff = (float)(t->size - t->tail->size )/((t->count - 1 )* N );
	return eff;
}

int vide_text(text* t){//O(1)
	if (t->head==NULL)
		return 1;
	return 0;
}

void ajoute_node(text* t){//O(1)
	node* p = create_node();
	p->next = t->head;
	t->head = p;
	t->count++;
	if (t->tail == NULL)
		t->tail = p;

}
void append_text(text* t, char* s){//O(m)
	int i=0;
	node* next;
	node* p;
	if (s[0]=='\0')
		return;
	if (vide_text(t))
		ajoute_node(t);
	p=t->tail;
	while(s[i]!='\0'){
		if (p->size < N){
			p->data[p->size]=s[i];
			p->size++;
			t->size++;
			i++;
		}
		else {
			next = create_node();
			p->next = next;
			next->prev = p;
			p = p->next;
			t->count++;
		}
		
	}
	t->tail = p;
}

void push_text(text* t, char* s){//O(m)
	int i=0;
	node* next;
	node* p = create_node();
	node* head = p;
	t->count++;
	while(s[i]!='\0'){
		if (p->size < N){
			p->data[p->size]=s[i];
			p->size++;
			t->size++;
			i++;
		}
		else {
			next = create_node();
			p->next = next;
			next->prev = p;
			p = p->next;
			t->count++;
		}
		
	}
	p->next = t->head;
	t->head->prev = p;
	t->head = head;
}

void show_text(text* t, iter* pos){//O(n)
	int i;
	node* p = t->head;
	if (pos->ptr == NULL)
		printf("[*]");
	if (pos == NULL || t->head == NULL)
		return;
	while (p!= pos->ptr){
		for(i=0;i<p->size;i++)
			printf("%c",p->data[i]);
		p = p->next;
		if (p == NULL)
			return;
	}
	i=0;
	while(i<=pos->icase){
		printf("%c",p->data[i]);
		i++;
	}
	printf("[*]");
	while(i<p->size){
		printf("%c",p->data[i]);
		i++;
	}
	p = p->next;
	while(p!=NULL){
		for(i=0;i<p->size;i++)
			printf("%c",p->data[i]);
		p = p->next;
	}
}

node* trouve_piece(text* t){//O(n)
	node* p = t->head;
	if (vide_text(t))
		return NULL;
	while (p->size == N){
		if (p->next == NULL)
			return NULL;
		else
			p=p->next;
	}
	if (p->next != NULL)
		return p;
	else return NULL;
}

int iter_pos(text* t, iter* pos){//O(n)
	int n=0;
	node* p = t->head;
	if (pos->ptr == NULL)
		return 0;
	while (p != pos->ptr){
		n = n + p->size;
		p = p->next;
	}
	n = n + pos->icase + 1;
	return n;
}

void reset_iter(text* t, iter* pos, int n){//O(1)
	if (n==-1){
		pos->icase = -1;
		pos->ptr = t->head;
		return;
	}
	pos->icase = 0;
	pos->ptr = t->head;
	move_foward_iter(pos,n-1);
	return;
}

void shift_mot(text* t, node* p){//O(n)
	node* tmp = p;
	node* pre;
	int i;
	if (( tmp == NULL) ||( tmp->size == N )|| (tmp->next == NULL))
		return;
	pre= tmp;
	tmp->data[tmp->size] = tmp->next->data[0];
	tmp->size++;
	tmp = tmp->next;
	while (tmp->next != NULL){
		for (i=0;i<tmp->size-1;i++)
			tmp->data[i]=tmp->data[i+1];
		tmp->data[tmp->size-1] = tmp->next->data[0];
		//pre = pre->next;
		tmp = tmp->next;
	}
	for (i=0;i<tmp->size-1;i++)
		tmp->data[i]=tmp->data[i+1];
	tmp->size--;
	if (tmp->size == 0){
		t->count--;
		t->tail = tmp->prev;
		free(tmp);
		t->tail->next = NULL;
		
	}

}
void shift_text(text* t, iter* pos){//O(n2)
	node* p;
	int i=0,n;
	if (vide_text(t))
		return;
	n = iter_pos(t,pos);
	p = trouve_piece(t);
	if ( p == NULL ){
		printf("no need to shift,done!\n");
		return;
	}
	while (p!=NULL && p->next!= NULL){
		while( p->size < N ){
			i++;
			shift_mot(t,p);
		}
		p = trouve_piece(t);
	}
	reset_iter(t,pos,n);
	printf("shift %d place(s), done!\n",i);
	return;


}

void insert_text(text *t, iter *pos, char *s){//O(m)
	int i=0,n=0;
	int po,m=0;
	node *next;
	node* tmp;
	node *p;
	char tem[N];
	if (vide_text(t)){
		ajoute_node(t);
		pos->icase = -1;
		pos->ptr = t->head;
	}
	p = pos->ptr;

	tmp = p->next;
	
	while ( pos->icase+1 < pos->ptr->size  ){
		tem[m] = p->data[pos->icase+1];
		m++;
		pos->icase++;
	}
	p->size=p->size-m;
	while (s[i]!='\0'){
		if (p->size < N){
			p->data[p->size] = s[i];
			n++;
			p->size ++;
			t->size ++;
			i++;
		}
		else{
			next = create_node();
			p->next = next;
			next->prev = p;
			p = p->next;
			t->count++;
		}
	}
	pos->ptr=p;
	pos->icase=p->size-1;
	for (i=0; i<m;){
		if (p->size < N){
			p->data[p->size] = tem[i];
			p->size ++;
			i++;
		}
		else{
			next = create_node();
			p->next = next;
			next->prev = p;
			p = p->next;
			t->count ++;
		}
	}
	p->next = tmp;
	
	if (tmp == NULL){
		t->tail = p;
	}
	else{
		tmp->prev = p;
	}
}


void delete_text(text *t, iter *pos, int n){//O(n)
	node*tmp,*tmp1,*p,* it = pos->ptr;
	int i=0,j,m=0,w=0,z=0,nb;
	m = pos->icase;
	p = pos->ptr;
	tmp = p;
	tmp1 = tmp;
	nb=iter_pos(t,pos);
	if (n >= nb){
		if(pos->icase == pos->ptr->size - 1 && pos->ptr == t->tail){
			free_text(t);
			pos->ptr = NULL;
			t=create_text();
			return;
		}

		if(pos->icase+1 < pos->ptr->size){
			j=pos->ptr->size - pos->icase - 1;
			for(i=0;i<j;i++){
				p->data[i]=p->data[m + i + 1];
			}
			t->size=t->size-pos->icase -1;
			p->size=p->size-pos->icase -1;
		}
		else{
			if (pos->ptr->next != NULL)
				pos->ptr = pos->ptr->next;
			else{
				free_text(t);
				return;
			}
		}
		tmp = pos->ptr->prev;
		while (tmp != NULL){
			tmp1 = tmp;
			t->count--;
			t->size-=tmp->size;
			tmp = tmp->prev;
			free(tmp1);
		}
		t->head=pos->ptr;
		pos->ptr->prev=NULL;
		pos->icase = -1;
		return;
	}
	move_backward_iter(pos,n);
	
	if ( n <= pos->icase + 1 && it == pos->ptr ){
		p->size = p->size-n;
		t->size = t->size - n;
		for (i = 0; i<p->size - m - 1;i++){
			p->data[i]=p->data[pos->icase +i +n];
		}
		return;
	}
	p->size = p->size - m - 1;
	if (p->size == 0 ){
		if ( p->next != NULL ){
			p = p->next;
		}
		else {
			if (p->prev == NULL){
				pos->icase = 0;
				pos->ptr = NULL;
				t->tail = t->head = NULL;
				t->size = t->count = 0;
				return;
			}
			else
			{
				w++;
				t->tail = p->prev;
				p->prev->next = NULL;
			}
			
		}
		
	}
	else{
		for(i=0;i<p->size;i++)
			p->data[i]=p->data[m + i + 1];
	}

	z = z + m +1;
	z = z + pos->ptr->size - pos->icase - 1;
	pos->ptr->size = pos->icase + 1;
	tmp = p->prev;
	while (tmp != pos->ptr){
		tmp1 = tmp;
		w++;
		z= z+ tmp->size;
		tmp = tmp->prev;
		free(tmp1);
	}
	if (p->next == NULL){
		pos->ptr->next = NULL;
		t->tail = pos->ptr;
	}
	else{
		pos->ptr->next = p;
		p->prev = pos->ptr;
	}
	t->count = t->count - w;
	t->size = t->size - z;

}

void sauve_text(FILE *fp,text *t){//O(n)
	int i;
	node* p = t->head;
	while(p!=NULL){
		for(i=0;i<p->size;i++)
			fprintf(fp,"%c",p->data[i]);
		p = p->next;
	}
}
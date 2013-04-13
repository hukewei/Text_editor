#include "tp3.h"
int main ()
{
	FILE *fp;
	char s[255];  
	char s1[255];
	iter* pos;
	text* t=create_text();
	char sel;
	float f;
	int n;
	printf("1. Lire le fichier.\n2. Sauvegarder le fichier.\n3. Afficher le texte lu.\n4. (Re)placer le curseur avant le premier caractere.\n5. Deplacer le curseur de n caracteres vers la gauche.\n6. Deplacer le curseur de n caracteres vers la droite.\n7. Supprimer n caracteres a l'emplacement indique par le curseur.\n8. Inserer une chaine de caracteres a l'emplacement indique par le curseur.\n9. Quitter.\nTapez(1~9):");
	scanf(" %c",&sel);
	while(sel!='9'){
		switch(sel){
			case '1':
				 if( (fp=fopen("c:\\source.txt","r")) == NULL )
					{
						 printf("error,file can not open");
							exit(0);
					 }
				printf("Text est bien lu!\n");
				if (!vide_text(t)){
					free_text(t);
					t=create_text();
				}
				while(!feof(fp)){
				fgets(s,255,fp);
				append_text(t,s);
				}
				fclose(fp);
				pos=create_iter_at_begin(t);
				reset_iter(t,pos,-1);
				break;
			case '2':
				if( (fp=fopen("c:\\source.txt","w")) == NULL )
					{
						 printf("error,file can not open");
							exit(0);
					 }
				sauve_text(fp,t);
				fclose(fp);
				printf("Text est bien sauvegarde!\n");
				break; 
			case '3':
				show_text(t,pos);
				f=evalmen_text(t)*100;
				printf("\nEfficacite = %4.2f%%\n",f);	
				break;
			case '4':
				reset_iter(t,pos,-1);
				break;
			case '5':
				printf("vous voulez deplacer combien de caracteres?\n");
				scanf("%d",&n);
				move_backward_iter(pos,n);
				break;
			case '6':
				printf("vous voulez deplacer combien de caracteres?\n");
				scanf("%d",&n);
				move_foward_iter(pos,n);
				break;
			case '7':
				printf("vous voulez supprimer combien de caracteres?\n");
				scanf("%d",&n);
				delete_text(t,pos,n);
				break;
			case '8':
				printf("typez les caracteres s.v.p:\n");
				scanf("%s",s1);
				if (pos->icase == -1)
					push_text(t,s1);
				
				else
					insert_text(t,pos,s1);
				shift_text(t,pos);
				break;
			case '9':
				free_text(t);
				free_iter(pos);
				fclose(fp);
				break;
		}
		getchar();
		printf("\n\n1. Lire le fichier.\n2. Sauvegarder le fichier.\n3. Afficher le texte lu.\n4. (Re)placer le curseur avant le premier caractere.\n5. Deplacer le curseur de n caracteres vers la gauche.\n6. Deplacer le curseur de n caracteres vers la droite.\n7. Supprimer n caracteres a l'emplacement indique par le curseur.\n8. Inserer une chaine de caracteres a l'emplacement indique par le curseur.\n9. Quitter.\nTapez(1~9):");
		scanf(" %c",&sel);
		system("cls");
	}
}
	
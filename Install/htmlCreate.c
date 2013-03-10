#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "htmlCreate.h"
#include <sys/dir.h>
#include <sys/stat.h>

void poeBarra(char *pal){
	int i;

	for(i=0;i<strlen(pal);i++){
		if(pal[i]==' ') pal[i]='_';
	}

}

char *trataDate(char * date, char * dest){
	int i=0, h=0, j=0;
	char hor[]="hora:";
	
	dest = malloc((strlen(date)+strlen(hor)+1)*sizeof(char ));

	for(i=0;i<strlen(date);i++){
		if(date[i]>='A' && date[i]<='Z') {
			dest[j]=' ';
			if (h==0){
				j++;
				for(h=0;h<strlen(hor);h++){
					dest[j]=hor[h];
					j++;
				}
				j--;
			}
		}
		else dest[j]=date[i];
		j++;
	}

	return dest;
}

void createFile(List lista){

	Docs doc;
		
	mode_t process_mask = umask(0);

	mkdir("Ficheiros",  S_IRWXU | S_IRWXG | S_IRWXO);

	umask(process_mask);

	char *dest;


	while(lista!=NULL){
	
		
		doc = lista->doc;


		//char caminhos[50] = "Ficheiros/";
		dest=malloc(1000*sizeof(char ));

		//strcat(caminhos,doc->titulo);	
		strcat(dest,"Ficheiros/");
		strcat(dest,doc->titulo);
		//printf("caminho= %s \n",dest);		
		strcat(dest,".html");
		//printf("html= %s \n",dest);

		poeBarra(dest);

		FILE *f = fopen(dest,"w+");

		if(f==NULL) {printf("Impossivel criar mais ficheiros na directoria\n\n");return;}

		
		//printf("depois %s \n",dest);
		

		Links link;
		//iniciar html
		fprintf(f, "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /><title>%s</title></head>",doc->titulo);
		fprintf(f, "<body background=\"http://www.acaixamagica.com/acaixamagica.com/wp-content/uploads/HLIC/92ea2b808cc0ce10df3f48ceb72b2776.jpg\"><h1 align = center style=\"font-family: Palatino;\"><a href=\"http://pt.wikipedia.org/wiki/%s\" target=\"_blank\" >%s </a></h1>", doc->titulo,doc->titulo);
		char *autLast = "Anónimo";
		if(doc->autorLastRev!=NULL) autLast = doc->autorLastRev;
		fprintf(f, "<h2 style=\"font-family: Palatino;\">Autor ultima revisao: %s </h2>", autLast);
		char *dateLast = "Indefinida";
		if(doc->dateLastRev!=NULL) dateLast = trataDate(doc->dateLastRev,dateLast);
		fprintf(f, "<h2 style=\"font-family: Palatino;\">Data ultima revisao: %s </h2>", dateLast);

		fprintf(f, "<table WIDTH=100%%><tr><td ALIGN=RIGTH, VALIGN=TOP>");
		
		//Tabela	
		fprintf(f, "<table border=\"1\" cellspacing=0 bgcolor=\"#FFFFFF\">");
		fprintf(f, "<th><font color=\"#000000\"> %d Links Internos</font></th>", doc->nInter);
		link = doc->linkInter;
		while(link!=NULL){
			fprintf(f, "<tr><td><a href=\"http://pt.wikipedia.org/wiki/%s\" target=\"_blank\" >%s </a></td></tr>\n", link->nomeLinks,link->nomeLinks);
			link=link->next;
		}
		fprintf(f, "</table>");
		//fim tabela
	
		fprintf(f, "</td><td ALIGN=CENTER, VALIGN=TOP>");

	
		//Tabela
		fprintf(f, "<table border=\"1\" cellspacing=0 bgcolor=\"#FFFFFF\">");	
		fprintf(f, "<th><font color=\"#000000\"> %d Links Externos</font></th>", doc->nExt);
		link = doc->linkExt;
		while(link!=NULL){
			//fprintf(f, "<tr><td>http://www.%s </td></tr>\n", link->nomeLinks);
			fprintf(f, "<tr><td><a href=\"http://www.%s\" target=\"_blank\" >%s </a></td></tr>\n", link->nomeLinks,link->nomeLinks);		
			link=link->next;
		}
		fprintf(f, "</table>");
		//fim tabela

		fprintf(f, "</td><td ALIGN=LEFT, VALIGN=TOP>");

		//Tabela
		fprintf(f, "<table border=\"1\" cellspacing=0 bgcolor=\"#FFFFFF\">");
		fprintf(f, "<th><font color=\"#000000\"> %d Links Secundários</font></th>", doc->nSec);
		link = doc->linkSec;
		while(link!=NULL){
			fprintf(f, "<tr><td> %s </td></tr>\n", link->nomeLinks);
			link=link->next;
		}
		fprintf(f, "</table>");
		//fim tabela	

		fprintf(f,"</td></tr></table>");
	
		//finalizar html
		fprintf(f, "</body></html>");	

		fclose(f);
		
		//free(dest);		

		lista=lista->next;
	}	

}	

void createIndex(List lista){

	Docs doc = lista->doc;

	char *dest=NULL;

	dest=malloc(10000*sizeof(char ));

	//strcat(caminhos,doc->titulo);
	strcat(dest,"Index");
	//printf("caminho= %s \n",dest);		
	strcat(dest,".html");
	//printf("html= %s \n",dest);

	FILE *f = fopen(dest,"w+");


	Links link;
	//iniciar html
	fprintf(f, "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" /><title>Indíce</title></head>");
	fprintf(f, "<body background=\"http://www.acaixamagica.com/acaixamagica.com/wp-content/uploads/HLIC/92ea2b808cc0ce10df3f48ceb72b2776.jpg\"><h1 align=CENTER>Indíce</h1>");
		
	//Tabela	
	fprintf(f, "<table align=CENTER border=\"1\" cellspacing=0 bgcolor=\"#FFFFFF\">");

	char endereco[100];

	while(lista!=NULL){
		strcpy(endereco,lista->doc->titulo);
		poeBarra(endereco);
		fprintf(f, "<tr><td><a href=Ficheiros/%s.html target=\"_blank\" >%s </a></td></tr>\n",endereco, lista->doc->titulo);
		lista=lista->next;
	}
	fprintf(f, "</table>");
	//fim tabela
	
	//finalizar html
	fprintf(f, "</body></html>");	

	fclose(f);
}



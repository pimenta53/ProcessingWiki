%{
#include "TrabInputs.h"
#include "htmlCreate.h"

List lista = NULL;
Docs doc;
%}

%x page
%x title_sc
%x revision
%x time
%x author
%x ext
%x section
%x intern
%option yylineno
%option noyywrap

anything .|[\n\t\r]


%%

"<page>"	{BEGIN(page);doc=initDocument();}


<page>{
	
	"<title>" 	{BEGIN(title_sc);}
	"<revision>"	BEGIN(revision);
	{anything}      {;}	
	"</page>"	BEGIN(INITIAL);	
	}
<title_sc>{	
	.*:.*		BEGIN(page);	
	[^<]+		{doc = inserTitulo(yytext,doc);lista = guardaDoc(doc,lista);}
	"</title>"	BEGIN(page);
	}
<revision>{
	"<timestamp>"	BEGIN(time);
	"<username>"	BEGIN(author);	
	^[=]{2}		BEGIN(section);
	[w]{3}\.	BEGIN(ext);
	[[]{2}		BEGIN(intern);
	{anything}           {;} /* do nothing*/		
	"</revision>"	BEGIN(page);	
	}
<author>{
	[^<]+		{doc = inserAutorLastRec(yytext, doc);}
	"</username>"	BEGIN(revision);
	}
<time>{
	[^<]+		{doc = inserDateLastRec(yytext, doc);}
	"</timestamp>"	BEGIN(revision);
	}
<section>{			
	[^=]+		{doc = inserLinkSec(yytext, doc);}
	[=]+		BEGIN(revision);
	}
<ext>{
	[a-zA-Z0-9_\.-]+\.[a-zA-Z]+	{doc = inserLinkExt(yytext, doc);}	
	{anything}			BEGIN(revision);
	}
<intern>{	
	[^]:]+/"|" 	{doc = inserLinkInter(yytext, doc);}	
	[^]:|]+/]] 	{doc = inserLinkInter(yytext, doc);}	
	{anything}	{BEGIN(revision);}	
	}
<*>	{fprintf(stderr,"ERRO no formato: %d - Linha\n", yylineno);}
{anything}           {;} /* do nothing*/
<<EOF>>	{return 1;}

%%

int main(int argc, char *argv[]){
	int i=1;

	if(argc<2) {
		printf("\nFalta introduzir ficheiro!\n\n");
		return 1;
	}

	for(i=1;i<argc;i++){
		yyin = fopen(argv[i], "r");
		if(yyin==NULL){
			printf("\nFicheiro '%s' não se encontra na directoria!\n\n", argv[i]);
			return 1;
			}
		yylex();
		fclose(yyin);
	}
	printf("\nA criar ficheiros...\n\n");
	createFile(lista);
	printf("\nA criar index...\n\n");
	createIndex(lista);

	printf("\nFicheiro convertido com sucesso!\n\n");
	
	return 0;
	
}

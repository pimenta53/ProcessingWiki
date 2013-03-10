typedef struct links{
	char* nomeLinks;
	struct links *next;
}*Links;


typedef struct Document{
	char* titulo;
	char* autorLastRev;
	char* dateLastRev;
	int nInter;
	Links linkInter;
	int nExt;
	Links linkExt;
	int nSec;
	Links linkSec;
}*Docs, DOC;

typedef struct listDocs{
	Docs doc;
	struct listDocs *next;
}*List;

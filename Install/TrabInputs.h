#ifndef _H_ESTRUTRA
#define _H_ESTRUTRA
#include "estrutura.h"
#endif

List guardaDoc(Docs doc, List lista);
int ordAlf(char *nova, char *existe);
Docs initDocument();
Docs inserLinkInter(char* link, Docs doc);
Docs inserLinkExt(char* link, Docs doc);
Docs inserLinkSec(char* link, Docs doc);
Docs inserTitulo(char* titulo, Docs doc);
Docs inserAutorLastRec(char* autor, Docs doc);
Docs inserDateLastRec(char* date, Docs doc);

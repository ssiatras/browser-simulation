/*************************************************************************
Header File   : session.h
Author - Date : Efstathios Siatras - 30/04/2017
Purpose       : Header file of ADT Session
*************************************************************************/
#ifndef SESSION_H
#define SESSION_H

#include "typedefs.h"
#include "tab.h"
#include "site.h"

InfoSessionPtr SessionMalloc();
void SessionFree(InfoSessionPtr);
void SessionSetFirstTab(InfoSessionPtr, TabNodePtr);
void SessionSetLastTab(InfoSessionPtr, TabNodePtr);
void SessionSetCurrTab(InfoSessionPtr, TabNodePtr);
void SessionSetOpeningAddress(InfoSessionPtr, char *, int *);
TabNodePtr SessionReturnFirstTab(InfoSessionPtr);
TabNodePtr SessionReturnLastTab(InfoSessionPtr);
TabNodePtr SessionReturnCurrTab(InfoSessionPtr);
char *SessionReturnOpeningAddress(InfoSessionPtr);

InfoSessionPtr SessionNew(char *, int *);
void SessionNewTab(InfoSessionPtr, int *);
void SessionAddressShow(InfoSessionPtr, int *);
void SessionTabNext(InfoSessionPtr, int *);
void SessionTabPrev(InfoSessionPtr, int *);
void SessionTabMoveLeft(InfoSessionPtr, int *);
void SessionTabMoveRight(InfoSessionPtr, int *);
void SessionShowOpeningAddress(InfoSessionPtr, int *);
void SessionSiteNext(InfoSessionPtr, int *);
void SessionSitePrev(InfoSessionPtr, int *);
void SessionTabClose(InfoSessionPtr, int *);
void SessionClose(InfoSessionPtr, int *);
void SessionNewAddress(InfoSessionPtr, char *, int *);

#endif
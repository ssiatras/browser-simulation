/*************************************************************************
Header File   : tab.h
Author - Date : Efstathios Siatras - 30/04/2017
Purpose       : Header file of ADT Tab
*************************************************************************/
#ifndef TAB_H
#define TAB_H

#include "typedefs.h"

TabNodePtr TabMalloc(void);
void TabFree(TabNodePtr);
void TabSetPrevTab(TabNodePtr, TabNodePtr);
void TabSetNextTab(TabNodePtr, TabNodePtr);
void TabSetParentTab(TabNodePtr, TabNodePtr);
void TabSetFirstSite(TabNodePtr, SiteNodePtr);
void TabSetCurrSite(TabNodePtr, SiteNodePtr);
TabNodePtr TabReturnPrevTab(TabNodePtr);
TabNodePtr TabReturnNextTab(TabNodePtr);
TabNodePtr TabReturnParentTab(TabNodePtr);
SiteNodePtr TabReturnFirstSite(TabNodePtr);
SiteNodePtr TabReturnCurrSite(TabNodePtr);

#endif
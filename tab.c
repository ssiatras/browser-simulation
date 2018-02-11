/*************************************************************************
Implementation File : tab.c
Author - Date       : Efstathios Siatras - 30/04/2017
Purpose             : Implementation file of ADT Tab
*************************************************************************/
#include <stdlib.h>

#include "tab.h"

struct TabNode { /* Definition of TabNode */
	TabNodePtr PrevTab, NextTab;
	SiteNodePtr FirstSite;
	SiteNodePtr CurrSite;
};



TabNodePtr TabMalloc(void) { /* Mallocs a tab */
	TabNodePtr tab;
	tab = malloc(sizeof(struct TabNode));
	if (tab == NULL) { /* Checks malloc failure */
		return NULL;
	}

	tab->PrevTab = NULL;
	tab->NextTab = NULL;
	tab->FirstSite = NULL;
	tab->CurrSite = NULL;

	return tab;
}

void TabFree(TabNodePtr tab) { /* Frees a tab */
	free(tab);
}

void TabSetPrevTab(TabNodePtr tab, TabNodePtr previous) { /* Sets previous tab of a tab */
	tab->PrevTab = previous;
}

void TabSetNextTab(TabNodePtr tab, TabNodePtr next) { /* Sets next tab of a tab */
	tab->NextTab = next;
}

void TabSetFirstSite(TabNodePtr tab, SiteNodePtr first) { /* Sets first site of a tab */
	tab->FirstSite = first;
}

void TabSetCurrSite(TabNodePtr tab, SiteNodePtr curr) { /* Sets current site of a tab */
	tab->CurrSite = curr;
}

TabNodePtr TabReturnPrevTab(TabNodePtr tab) { /* Returns previous tab of a tab */
	return tab->PrevTab;
}

TabNodePtr TabReturnNextTab(TabNodePtr tab) { /* Returns next tab of a tab */
	return tab->NextTab;
}

SiteNodePtr TabReturnFirstSite(TabNodePtr tab) { /* Returns first site of a tab */
	return tab->FirstSite;
}

SiteNodePtr TabReturnCurrSite(TabNodePtr tab) { /* Returns current site of a tab */
	return tab->CurrSite;
}
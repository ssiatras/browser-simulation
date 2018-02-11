/*************************************************************************
Implementation File : session.c
Author - Date       : Efstathios Siatras - 30/04/2017
Purpose             : Implementation file of ADT Session
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "session.h"

struct InfoSession { /* Definition of InfoSession */
	TabNodePtr FirstTab;
	TabNodePtr LastTab;
	TabNodePtr CurrTab;

	char *OpeningAddress;
};



InfoSessionPtr SessionMalloc() { /* Mallocs a session */
	InfoSessionPtr session;
	session = malloc(sizeof(struct InfoSession));
	if (session == NULL) { /* Checks malloc failure */
		return NULL;
	}

	session->FirstTab = NULL;
	session->LastTab = NULL;
	session->CurrTab = NULL;
	session->OpeningAddress = NULL;

	return session;
}

void SessionFree(InfoSessionPtr session) { /* Frees a session */
	if (session->OpeningAddress != NULL) {
		free(session->OpeningAddress);

		session->OpeningAddress = NULL;
	}

	free(session);
}

void SessionSetFirstTab(InfoSessionPtr session, TabNodePtr tab) { /* Sets first tab of a session */
	session->FirstTab = tab;
}

void SessionSetLastTab(InfoSessionPtr session, TabNodePtr tab) { /* Sets last tab of a session */
	session->LastTab = tab;
}

void SessionSetCurrTab(InfoSessionPtr session, TabNodePtr tab) { /* Sets current tab of a session */
	session->CurrTab = tab;
}

void SessionSetOpeningAddress(InfoSessionPtr session, char *address, int *error) { /* Sets opening address of a site */
	if (address == NULL) { /* If the address we want to set is NULL */
		if (session->OpeningAddress != NULL) { /* Frees old address, if exists */
			free(session->OpeningAddress);
		}
		session->OpeningAddress = address;

		return;
	}

	char *temp_address = NULL; /* A temporary pointer to the new address, in order to maintain the old address, in case of malloc failure */
	temp_address = malloc((strlen(address)+1)*sizeof(char));
	if (temp_address == NULL) { /* Checks malloc failure */
		*error = 4;

		return;
	}

	if (session->OpeningAddress != NULL) { /* Frees old address, if exists */

		free(session->OpeningAddress);
	}

	session->OpeningAddress = temp_address;
	strcpy(session->OpeningAddress, address);
}

TabNodePtr SessionReturnFirstTab(InfoSessionPtr session) { /* Returns first tab of a session */
	return session->FirstTab;
}

TabNodePtr SessionReturnLastTab(InfoSessionPtr session) { /* Returns last tab of a session */
	return session->LastTab;
}

TabNodePtr SessionReturnCurrTab(InfoSessionPtr session) { /* Returns current tab of a session */
	return session->CurrTab;
}

char *SessionReturnOpeningAddress(InfoSessionPtr session) { /* Returns opening address of a session */
	return session->OpeningAddress;
}

/* Functions used in BrowserSimulation.c below */

InfoSessionPtr SessionNew(char *address, int *error) { /* Creates a new session */
	InfoSessionPtr session;
	TabNodePtr tab;
	SiteNodePtr site;

	session = SessionMalloc();
	if (session == NULL) { /* Checks malloc failure */
		*error = 1;

		return NULL;
	}

	tab = TabMalloc();
	if (tab == NULL) { /* Checks malloc failure */
		*error = 2;
		SessionFree(session);

		return NULL;
	}

	site = SiteMalloc();
	if (site == NULL) { /* Checks malloc failure */
		*error = 3;
		SessionFree(session);
		TabFree(tab);

		return NULL;
	}

	/* Initializes site */
	SiteSetPrevSite(site, NULL);
	SiteSetNextSite(site, NULL);
	SiteSetUpTab(site, tab);
	SiteSetAddress(site, address, error);
	if (*error == 4) { /* Checks malloc failure */
		SessionFree(session);
		TabFree(tab);
		SiteFree(site);

		return NULL;
	}

	/* Initializes tab */
	TabSetPrevTab(tab, tab);
	TabSetNextTab(tab, tab);
	TabSetFirstSite(tab, site);
	TabSetCurrSite(tab, site);

	/* Initializes session */
	SessionSetFirstTab(session, tab);
	SessionSetLastTab(session, tab);
	SessionSetCurrTab(session, tab);
	SessionSetOpeningAddress(session, address, error);
	if (*error == 4) { /* Checks malloc failure */
		SessionFree(session);
		TabFree(tab);
		SiteFree(site);

		return NULL;
	}

	return session;
}

void SessionNewTab(InfoSessionPtr session, int *error) { /* Creates a new tab */
	if (session == NULL) { /* Checks if session exists */
		*error = 1;

		return;
	}

	int IsLastTab = 0;
	TabNodePtr newtab;
	SiteNodePtr newsite;
	TabNodePtr temp = SessionReturnCurrTab(session);

	newtab = TabMalloc();
	if (newtab == NULL) { /* Checks malloc failure */
		*error = 2;

		return;
	}

	newsite = SiteMalloc();
	if (newsite == NULL) { /* Checks malloc failure */
		*error = 3;
		TabFree(newtab);

		return;
	}

	if (SessionReturnLastTab(session) == SessionReturnCurrTab(session)) {
		IsLastTab = 1;  /* Flags, if it is the last tab */ 
	}

	/* Initializes site */
	SiteSetNextSite(newsite, NULL);
	SiteSetPrevSite(newsite, NULL);
	SiteSetUpTab(newsite, newtab);
	SiteSetAddress(newsite, SessionReturnOpeningAddress(session), error);
	if (*error == 4) { /* Checks malloc failure */
		TabFree(newtab);
		SiteFree(newsite);

		return;
	}

	/* Connects tabs properly */
	TabSetPrevTab(newtab, temp);
	TabSetNextTab(newtab, TabReturnNextTab(temp));
	TabSetFirstSite(newtab, newsite);
	TabSetCurrSite(newtab, newsite);

	TabSetNextTab(temp, newtab);
	TabSetPrevTab(TabReturnNextTab(newtab), newtab);

	SessionSetCurrTab(session, newtab); /* Current tab of the session is the new tab */
	if (IsLastTab) { /* Last tab of the session is the new tab */
		SessionSetLastTab(session, newtab);
	}
}

void SessionAddressShow(InfoSessionPtr session, int *error) { /* Shows the current address of the current tab  */
	if (session == NULL) { /* Checks if session exists */
		*error = 1;

		return;
	}

	else if (SessionReturnCurrTab(session) == NULL) {
		*error = 2; /* Not possible. It will be 'asserted' in main */

		return;
	}

	else if (SiteReturnAddress(TabReturnCurrSite(SessionReturnCurrTab(session))) == NULL) {
		*error = 3; /* Not possible. It will be 'asserted' in main */

		return;
	}
	printf("\nThe current address of the current tab is: %s\n", SiteReturnAddress(TabReturnCurrSite(SessionReturnCurrTab(session))));
}

void SessionTabNext(InfoSessionPtr session, int *error) { /* Goes to the next tab */
	if (session == NULL) { /* Checks if session exists */
		*error = 1;

		return;
	}
	SessionSetCurrTab(session, TabReturnNextTab(SessionReturnCurrTab(session)));
}

void SessionTabPrev(InfoSessionPtr session, int *error) { /* Goes to the previous tab */
	if (session == NULL) { /* Checks if session exists */
		*error = 1;

		return;
	}
	SessionSetCurrTab(session, TabReturnPrevTab(SessionReturnCurrTab(session)));
}

void SessionTabMoveLeft(InfoSessionPtr session, int *error) { /* Moves the current tab to the left */
	if (session == NULL) { /* Checks if session exists */
		*error = 1;

		return;
	}

	TabNodePtr curr = SessionReturnCurrTab(session);
	TabNodePtr left = TabReturnPrevTab(curr);
	TabNodePtr right = TabReturnNextTab(curr);

	if (SessionReturnCurrTab(session) == SessionReturnFirstTab(session)) { /* Checks if the current tab is the first tab */
		*error = -1; 
		if (SessionReturnCurrTab(session) == SessionReturnLastTab(session)) { /* Checks if there is only one tab */
			*error = -2;
		}
	}

	else if ((SessionReturnCurrTab(session) == SessionReturnLastTab(session)) && (TabReturnPrevTab(SessionReturnCurrTab(session)) == SessionReturnFirstTab(session))) { /* Checks if there are only two tabs in the session */
		/* We only need to change the first and the last tab of the session */
		SessionSetFirstTab(session, curr); 
		SessionSetLastTab(session, left);
	}

	else { /* 'General' occasion ; three tabs or more */
		if (TabReturnPrevTab(SessionReturnCurrTab(session)) == SessionReturnFirstTab(session)) { /* Checks if we need to change the first tab of the session */
			SessionSetFirstTab(session, curr);
		}

		if (SessionReturnCurrTab(session) == SessionReturnLastTab(session)) { /* Checks if we need to change the last tab of the session */
			SessionSetLastTab(session, left);
		}

		/* Connects tabs properly */
		TabSetNextTab(TabReturnPrevTab(left), curr);
		TabSetNextTab(left, right);
		TabSetPrevTab(curr, TabReturnPrevTab(left));
		TabSetPrevTab(right, left);
		TabSetNextTab(curr, left);
		TabSetPrevTab(left, curr);
	}
}

void SessionTabMoveRight(InfoSessionPtr session, int *error) { /* Moves the current tab to the right */
	if (session == NULL) { /* Checks if session exists */
		*error = 1;
		if (SessionReturnCurrTab(session) == SessionReturnLastTab(session)) { /* Checks if there is only one tab */
			*error = -2;
		}

		return;
	}

	TabNodePtr curr = SessionReturnCurrTab(session);
	TabNodePtr left = TabReturnPrevTab(curr);
	TabNodePtr right = TabReturnNextTab(curr);

	if (SessionReturnCurrTab(session) == SessionReturnLastTab(session)) { /* Checks if the current tab is the last tab or if it is only one tab */
		*error = -1;

		return;
	}

	else if ((SessionReturnCurrTab(session) == SessionReturnFirstTab(session)) && (TabReturnNextTab(SessionReturnCurrTab(session)) == SessionReturnLastTab(session))) {
		/* We only need to change the first and the last tab of the session */
		SessionSetLastTab(session, curr);
		SessionSetFirstTab(session, right);
	}

	else {
		if (TabReturnNextTab(SessionReturnCurrTab(session)) == SessionReturnLastTab(session)) { /* Checks if we need to change the last tab of the session */
			SessionSetLastTab(session, curr);
		}

		if (SessionReturnCurrTab(session) == SessionReturnFirstTab(session)) { /* Checks if we need to change the first tab of the session */
			SessionSetFirstTab(session, right);
		}

		/* Connects tabs properly */
		TabSetPrevTab(TabReturnNextTab(right), curr);
		TabSetPrevTab(right, left);
		TabSetNextTab(curr, TabReturnNextTab(right));
		TabSetNextTab(left, right);
		TabSetPrevTab(curr, right);
		TabSetNextTab(right, curr);
	}
}

void SessionNewOpeningAddress(InfoSessionPtr session, char *address, int *error) { /* Sets new opening address of the session */
	if (session == NULL) { /* Checks if session exists */
		*error = 1;

		return;
	}

	SessionSetOpeningAddress(session, address, error);
}

void SessionShowOpeningAddress(InfoSessionPtr session, int *error) { /* Shows the opening address of the session */
	if (session == NULL) { /* Checks if session exists */
		*error = 1;

		return;
	}

	printf("The default opening address is %s", SessionReturnOpeningAddress(session));
}

void SessionSiteNext(InfoSessionPtr session, int *error) { /* Goes to the next site of the current tab */
	if (session == NULL) { /* Checks if session exists */
		*error = 1;

		return;
	}

	else if (SessionReturnCurrTab(session) == NULL) {
		*error = 2; /* Not possible. It will be 'asserted' in main */

		return;
	}

	else if (TabReturnCurrSite(SessionReturnCurrTab(session)) == NULL) {
		*error = 3; /* Not possible. It will be 'asserted' in main */

		return;
	}

	if (SiteReturnNextSite(TabReturnCurrSite(SessionReturnCurrTab(session))) == NULL) { /* Checks if there is next site */
		*error = -1;

		return;
	}

	TabSetCurrSite(SessionReturnCurrTab(session), SiteReturnNextSite(TabReturnCurrSite(SessionReturnCurrTab(session))));
}

void SessionSitePrev(InfoSessionPtr session, int *error) { /* Goes to the previous site of the current tab */
	if (session == NULL) { /* Checks if session exists */
		*error = 1;

		return;
	}

	else if (SessionReturnCurrTab(session) == NULL) {
		*error = 2; /* Not possible. It will be 'asserted' in main */

		return;
	}

	else if (TabReturnCurrSite(SessionReturnCurrTab(session)) == NULL) {
		*error = 3; /* Not possible. It will be 'asserted' in main */

		return;
	}

	if (SiteReturnPrevSite(TabReturnCurrSite(SessionReturnCurrTab(session))) == NULL) {  /* Checks if there is previous site */
		*error = -1;

		return;
	}

	TabSetCurrSite(SessionReturnCurrTab(session), SiteReturnPrevSite(TabReturnCurrSite(SessionReturnCurrTab(session))));
}

void SessionTabClose(InfoSessionPtr session, int *error) { /* Closes the current tab */
	if (session == NULL) { /* Checks if session exists */
		*error = 1;

		return;
	}

	TabNodePtr Tmp = SessionReturnCurrTab(session);

	SiteNodePtr ToDel;
	SiteNodePtr Next = TabReturnFirstSite(SessionReturnCurrTab(session));

	while (Next != NULL) { /* Frees all sites of the tab */
		ToDel = Next;
		Next = SiteReturnNextSite(Next);

		SiteFree(ToDel);
	}

    if (SessionReturnFirstTab(session) == SessionReturnLastTab(session)) { /*Checks if its the only one tab left */
		/* Frees the whole session */
		*error = -1;
		TabFree(SessionReturnCurrTab(session));
		SessionFree(session);
    }

    else {
    	/* Connects remaining tabs properly */
    	TabSetNextTab(TabReturnPrevTab(Tmp), TabReturnNextTab(Tmp));
    	TabSetPrevTab(TabReturnNextTab(Tmp), TabReturnPrevTab(Tmp));

    	if (Tmp == SessionReturnFirstTab(session)) { /* Checks if the tab that is going to be deleted is the first tab */
    		SessionSetFirstTab(session, TabReturnNextTab(Tmp));
    	}
    	else if (Tmp == SessionReturnLastTab(session)) { /* Checks if the tab that is going to be deleted is the last tab */
    		SessionSetLastTab(session, TabReturnPrevTab(Tmp));
    	}

    	SessionSetCurrTab(session, TabReturnNextTab(SessionReturnCurrTab(session))); /* Sets current tab as the next tab */
    	TabFree(Tmp); /* Frees the tab */
    }
}

void SessionClose(InfoSessionPtr session, int *error) { /* Closes the session */
	if (session == NULL) { /* Checks if session exists */
		*error = 1;

		return;
	}

	SessionSetCurrTab(session, SessionReturnFirstTab(session)); /* Sets current tab as the first tab to begin freeing from the first till the last one */

	do {
		SessionTabClose(session, error);
	}
	while (*error != -1); /* 'error == -1' equals to 'the whole session has been freed' */

	*error = 0;
}

void SessionNewAddress(InfoSessionPtr session, char *address, int *error) { /* Enters a site in the current tab */
	if (session == NULL) { /* Checks if session exists */
		*error = 1;

		return;
	}

	SiteNodePtr newsite = NULL;
	newsite = SiteMalloc();
	if (newsite == NULL) { /* Checks malloc failure */
		*error = 3;

		return;
	}

	SiteSetAddress(newsite, address, error); /* Initializes the new site with the address */
	if (*error == 4) { /* Checks malloc failure */
		SiteFree(newsite);

		return;
	}

	if (SiteReturnNextSite(TabReturnCurrSite(SessionReturnCurrTab(session))) != NULL) { /* Checks if there are other sites after the current site */
		/*Deletes and frees the other sites */
		SiteNodePtr ToDel;
		SiteNodePtr Next = SiteReturnNextSite(TabReturnCurrSite(SessionReturnCurrTab(session)));

		while (Next != NULL) { /* Frees all sites of the tab */
	       ToDel = Next;
	       Next = SiteReturnNextSite(Next);

	       SiteFree(ToDel);
	    }
	}
	/* Initializes the site */
	SiteSetPrevSite(newsite, TabReturnCurrSite(SessionReturnCurrTab(session)));
	SiteSetNextSite(newsite, NULL);
	SiteSetUpTab(newsite, SessionReturnCurrTab(session));

	SiteSetNextSite(TabReturnCurrSite(SessionReturnCurrTab(session)), newsite); /* Connects the sites properly */

	TabSetCurrSite(SessionReturnCurrTab(session), newsite); /* Sets current site as the new site */
}
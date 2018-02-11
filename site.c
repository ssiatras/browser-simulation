/*************************************************************************
Implementation File : site.c
Author - Date       : Efstathios Siatras - 30/04/2017
Purpose             : Implementation file of ADT Site
*************************************************************************/
#include <stdlib.h>
#include <string.h>

#include "site.h"

struct SiteNode { /* Definition of SiteNode */
	SiteNodePtr PrevSite, NextSite;
	TabNodePtr UpTab;
	char *Address;
};



SiteNodePtr SiteMalloc(void) { /* Mallocs a site */
	SiteNodePtr site;
	site = malloc(sizeof(struct SiteNode));
	if (site == NULL) { /* Checks malloc failure */
		return NULL;
	}

	site->PrevSite = NULL;
	site->NextSite = NULL;
	site->UpTab = NULL;
	site->Address = NULL;

	return site;
}

void SiteFree(SiteNodePtr site) { /* Frees a site */
	if (site->Address != NULL) {
		free(site->Address);

		site->Address = NULL;
	}

	free(site);
}

void SiteSetPrevSite(SiteNodePtr site, SiteNodePtr previous) { /* Sets previous site of a site */
	site->PrevSite = previous;
}

void SiteSetNextSite(SiteNodePtr site, SiteNodePtr next) { /* Sets next site of a site */
	site->NextSite = next;
}

void SiteSetUpTab(SiteNodePtr site, TabNodePtr tab) { /* Sets up tab of a site */
	site->UpTab = tab;
}

void SiteSetAddress(SiteNodePtr site, char *address, int *error) { /* Sets address of a site */
	if (address == NULL) { /* If the address we want to set is NULL */
		if (site->Address != NULL) { /* Frees old address, if exists */
			free(site->Address);
		}
		site->Address = address;

		return;
	}
	char *temp_address = NULL; /* A temporary pointer to the new address being malloced, in order to maintain the old address, in case of malloc failure */
	temp_address = malloc((strlen(address)+1)*sizeof(char));
	if (temp_address == NULL) { /* Checks malloc failure */
		*error = 4;

		return;
	}

	if (site->Address != NULL) { /* Frees old address, if exists */

		free(site->Address);
	}

	site->Address = temp_address;
	strcpy(site->Address, address);
}

SiteNodePtr SiteReturnPrevSite(SiteNodePtr site) { /* Returns previous site of a site */
	return site->PrevSite;
}

SiteNodePtr SiteReturnNextSite(SiteNodePtr site) { /* Returns next site of a site */
	return site->NextSite;
}

TabNodePtr SiteReturnUpTab(SiteNodePtr site) { /* Returns up tab of a site */
	return site->UpTab;
}

char *SiteReturnAddress(SiteNodePtr site) { /* Returns address of a site */
	return site->Address;
}
/*************************************************************************
Header File   : site.h
Author - Date : Efstathios Siatras - 30/04/2017
Purpose       : Header file of ADT Site
*************************************************************************/
#ifndef SITE_H
#define SITE_H

#include "typedefs.h"

SiteNodePtr SiteMalloc(void);
void SiteFree(SiteNodePtr);
void SiteSetPrevSite(SiteNodePtr, SiteNodePtr);
void SiteSetNextSite(SiteNodePtr, SiteNodePtr);
void SiteSetUpTab(SiteNodePtr, TabNodePtr);
void SiteSetAddress(SiteNodePtr, char *, int *);
SiteNodePtr SiteReturnPrevSite(SiteNodePtr);
SiteNodePtr SiteReturnNextSite(SiteNodePtr);
TabNodePtr SiteReturnUpTab(SiteNodePtr);
char *SiteReturnAddress(SiteNodePtr);

#endif
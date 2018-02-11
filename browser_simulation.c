/*************************************************************************
Implementation File : browser_simulation.c
Author - Date       : Efstathios Siatras - 30/04/2017
Purpose             : Simulates the data structures used in a browser
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "typedefs.h"
#include "session.h"
#include "tab.h"
#include "site.h"

void print_options();
int get_option();
char *read_address(int *);

int main(void) {
	int option;
	int error = 0;
	char *address = NULL;

	InfoSessionPtr MySession = NULL;

	do {
		option = get_option();
		switch (option) { /* Selects function to use */

		case 1: /* Creates a new session */
			if (MySession != NULL) { /* Checks if there is already a session open */
				fprintf(stderr, "\nThere is already a session open!\nClose this session to open a new one!\n");

				break;
			}
			printf("\nEnter the default opening address: ");
			address = read_address(&error);
			if (error) { /* Checks malloc failure */
				fprintf(stderr, "\nThere is not enough memory for this address!\nTry a smaller one!\n");
				error = 0;

				break;
			}

			MySession = SessionNew(address, &error);

			free(address);
			address = NULL;

			if (error) { /* Checks malloc failure */
				fprintf(stderr, "\nSession could not be created!\nThere is not enough memory!\n");
				error = 0;

				break;
			}
			printf("\nSession created successfully!\n");

			break;

		case 2: /* Creates a new tab */
			SessionNewTab(MySession, &error);
			if (error) {
				fprintf(stderr, "\nTab could not be created!\n");
				if (error == 1) { /* Checks if session exists */
					fprintf(stderr, "Create a session first!\n");
				}

				else { /* Checks malloc failure */
					fprintf(stderr, "There is not enough memory!\n");
				}
				error = 0;

				break;
			}
			printf("\nTab created successfully!\n");

			break;

		case 3: /* Shows the current address of the current tab */
			SessionAddressShow(MySession, &error);
			if (error) {
				fprintf(stderr, "\nThe current address of the current tab could not be found!\n");
				if (error == 1) { /* Checks if session exists */
					fprintf(stderr, "Create a session first!\n");
				}

				else { /* error == 2 or error == 3 */
					assert(0); /* There is no tab in the session or there is no site in the current tab! Not possible! */
				}

				error = 0;
			}

			break;

		case 4: /* Goes to the next tab */
			SessionTabNext(MySession, &error);
			if (error) { /* Checks if session exists */
				fprintf(stderr, "\nCreate a session first!\n");

				error = 0;

				break;
			}
			printf("\nWent to next tab successfully!\n");

			break;

        case 5: /* Goes to the previous tab */
       		SessionTabPrev(MySession, &error);
			if (error) { /* Checks if session exists */
				fprintf(stderr, "\nCreate a session first!\n");

				error = 0;

				break;
			}
			printf("\nWent to previous tab successfully!\n");

            break;

		case 6: /* Moves the current tab to the left */
			SessionTabMoveLeft(MySession, &error);
			if (error) {
				fprintf(stderr, "\nCould not move the current tab to the left!\n");
				if (error == 1) { /* Checks if session exists */
					fprintf(stderr, "Create a session first!\n");
				}
				else if (error == -1) { /* Checks if current tab is the first tab */
					fprintf(stderr, "The current tab is the first tab!\n");
				}
				else if (error == -2) { /* Checks if there is only one tab */
					fprintf(stderr, "There is only one tab!\n");
				}
				error = 0;

				break;
			}
			printf("\nMoved the current tab to the left!\n");

			break;

		case 7:  /* Moves the current tab to the right */
			SessionTabMoveRight(MySession, &error);
			if (error) {
				fprintf(stderr, "\nCould not move the current tab to the right!\n");
				if (error == 1) { /* Checks if session exists */
					fprintf(stderr, "Create a session first!\n");
				}
				else if (error == -1) { /* Checks if current tab is the last tab */
					fprintf(stderr, "The current tab is the last tab!\n");
				}
				else if (error == -2) { /* Checks if there is only one tab */
					fprintf(stderr, "There is only one tab!\n");
				}
				error = 0;

				break;
			}
			printf("\nMoved the current tab to the right!\n");

			break;

		case 8: /* Sets new opening address of the session */
			if (MySession == NULL) { /* Checks if session exists, before its too late */
				fprintf(stderr, "\nThe default opening address could not be changed!\nCreate a session first!\n");

				break;
			}

			printf("\nEnter the new default opening address: ");
			address = read_address(&error);
			if (error) { /* Checks malloc failure */
				fprintf(stderr, "\nThe default opening address could not be changed!\nThere is not enough memory for this address! Try a smaller one!\n");
				error = 0;

				break;
			}

			SessionNewOpeningAddress(MySession, address, &error);
			free(address);
			address = NULL;

			if (error) {
				fprintf(stderr, "\nThe default opening address could not be changed!\n");

				if (error == 1) {
					assert(0); /* Already checked if MySession == NULL! Not possible! */
				}

				else if (error == 4) { /* Checks malloc failure */
					fprintf(stderr, "There is not enough memory for this address! Try a smaller one!\n");
				}

				error = 0;
			}
			
			break;
			
		case 9: /* Shows the opening address of the session */
			SessionShowOpeningAddress(MySession, &error);
			if (error) { /* Checks if session exists */
				fprintf(stderr, "\nThe default opening address of the session could not be found!\nCreate a session first!\n");
				error = 0;
			}

			break;

		case 10: /* Goes to the next site of the current tab */
			SessionSiteNext(MySession, &error);
			if (error == 1) { /* Checks if session exists */
				fprintf(stderr, "\nCreate a session first!\n");
				error = 0;

				break;
			}

			else if (error == -1) { /* Checks if there is next site */
				printf("\nThere is no next site!\nRemained on current site.\n");
				error = 0;

				break;
			}
			printf("\nWent to next site successfully!\n");

			break;

		case 11: /* Goes to the previous site of the current tab */
			SessionSitePrev(MySession, &error);
			if (error == 1) { /* Checks if session exists */
				fprintf(stderr, "\nCreate a session first!\n");
				error = 0;

				break;
			}

			else if (error == -1) { /* Checks if there is previous site */
				printf("\nThere is no previous site!\nRemained on current site.\n");
				error = 0;

				break;
			}
			printf("\nWent to previous site successfully!\n");

			break;

		case 12: /* Closes the current tab */
			SessionTabClose(MySession, &error);
			if (error == 1) { /* Checks if session exists */
				fprintf(stderr, "\nCreate a session first!\n");
				error = 0;

				break;
			}
			printf("\nTab closed!\n");

			if (error == -1) { /* Checks if that was the last tab */
				printf("That was the last tab! Session closed!\n");
				MySession = NULL;

				error = 0;

				break;
			}

			break;

		case 13: /* Closes the session */
			SessionClose(MySession, &error);
			if (error) { /* Checks if session exists */
				fprintf(stderr, "\nCreate a session first!\n");
				error = 0;

				break;
			}
			MySession = NULL;
			printf("\nSession closed!\n");

			break;

		case 14: /* Enters a site in the current tab */
			if (MySession == NULL) { /* Checks if session exists, before its too late */
				fprintf(stderr, "\nCannot enter to the site!\nCreate a session first!\n");

				break;
			}

			printf("\nEnter the address of the site: ");
			address = read_address(&error);
			if (error) { /* Checks malloc failure */
				fprintf(stderr, "\nCannot enter to the current site!\nThere is not enough memory for this address! Try a smaller one!\n");
				error = 0;

				break;
			}

			SessionNewAddress(MySession, address, &error);
			free(address);
			address = NULL;

			if (error) {
				fprintf(stderr, "\nCannot enter to the site!\n");

				if (error == 1) {
					assert(0); /* Already checked if MySession == NULL! Not possible! */
				}

				else if (error == 4) { /* Checks malloc failure */
					fprintf(stderr, "There is not enough memory for this address! Try a smaller one!\n");
				}

				error = 0;

				break;
			}
			printf("\n Entered successfully!\n");

			break;
		}
	}
	while (option);

	if (MySession != NULL) {
		SessionClose(MySession, &error);
		MySession = NULL;

	}

	return 0;
}

void print_options() {
	printf("\n");
	printf("                  __________________                 \n");
	printf("                 |BROWSER SIMULATION|                \n");
	printf(" ___________________________________________________ \n");
	printf("| 0.  Exit                                          |\n");
	printf("| 1.  Create a new session                          |\n");
	printf("| 2.  Create a new tab                              |\n");
	printf("| 3.  Show the current address of the current tab   |\n");
	printf("| 4.  Go to the next tab                            |\n");
	printf("| 5.  Go to the previous tab                        |\n");
	printf("| 6.  Move the current tab to the left              |\n");
	printf("| 7.  Move the current tab to the right             |\n");
	printf("| 8.  Set new opening address of the session        |\n");
	printf("| 9.  Show the opening address of the session       |\n");
	printf("| 10. Go to the next site of the current tab        |\n");
	printf("| 11. Go to the previous site of the current tab    |\n");
	printf("| 12. Close the current tab                         |\n");
	printf("| 13. Close the session                             |\n");
	printf("| 14. Enter a site in the current tab               |\n");
	printf("|___________________________________________________|\n");
	printf("|______________Enter your input (0-14)______________|\n");
	printf("                         ");

}

int get_option() {
	char *buf = NULL;
	size_t len = 0;
	ssize_t read = 0;
	int option = -1;

	while (option < 0 || option > 14) {
		print_options();

		read = getline(&buf, &len, stdin);
		assert(read != -1);
		sscanf(buf, "%d", &option);

		free(buf);
		buf = NULL;
		len = 0;
		read = 0;
	}

	return option;
}

char *read_address(int *error) {
	char *buf = NULL;
	size_t len = 0;
	ssize_t read = 0;
	char *address = NULL;

	read = getline(&buf, &len, stdin);
	assert(read != -1);

	address = malloc(read*sizeof(char)); /* Getline counts the newline character, but we also need space for the null character at the end of the string */
	if (address == NULL) {
		*error = 4;

		return NULL;
	}

	sscanf(buf, "%s", address);

	free(buf);
	buf = NULL;
	len = 0;
	read = 0;

	return address;
}
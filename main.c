/*  NAME	: SIVA KUMAR P
 *  DATE	: 10/10/2025
 *  DESCRIPTION	: This project is a basic version of a contact management application developed in C language. It allows users 
 		  to create, edit, and delete contacts efficiently using structures and functions. To ensure data persistence, 
		  the project utilizes File I/O operations, storing all contact details permanently in a CSV file. This enables 
		  users to retrieve and manage their contact information even after the program is closed.
		
		  Key Features:

			1. Add new contacts with name, phone number, and email
			2. Edit existing contact details
			3. Delete unwanted contacts
			4. Display all saved contacts
			5. Persistent storage using a CSV file
		  
		  Concepts Used:

			1. Structures
			2. Functions
			3. File handling (File I/O)
			4. Arrays and strings */
#include "contact.h"
int main() 
{
    int choice;

    struct AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do 
    {
	printf("\nAddress Book Menu:\n");
	printf("1. Create contact\n");
	printf("2. Search contact\n");
	printf("3. Edit contact\n");
	printf("4. Delete contact\n");
	printf("5. List all contacts\n");
	printf("6. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice) 
	{
	    case 1:
		createContact(&addressBook);
		break;
	    case 2:
		searchContact(&addressBook);
		break;
	    case 3:
		editContact(&addressBook);
		break;
	    case 4:
		deleteContact(&addressBook);
		break;
	    case 5:
		listContacts(&addressBook);
		break;
	    case 6:
		printf("Saving and Exiting...\n");
		saveContactsToFile(&addressBook);
		break;
	    default:
		printf("Invalid choice. Please try again.\n");
	}
    } while (choice != 6);

    return 0;
}

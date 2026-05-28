#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>

struct Contact
{
    char name[50];
    char phone[20];
    char email[50];
};

struct AddressBook
{
    struct Contact contacts[100];
    int contactCount;
};

void createContact(struct AddressBook *addressBook);
void searchContact(struct AddressBook *addressBook);
void editContact(struct AddressBook *addressBook);
void deleteContact(struct AddressBook *addressBook);
void listContacts(struct AddressBook *addressBook);
void initialize(struct AddressBook *addressBook);
void saveContactsToFile(struct AddressBook *addressBook);
// Function used inside create contact function
void create_name(struct AddressBook * addressBook);
int create_phone(struct AddressBook * addressBook,char *);
int create_email(struct AddressBook * addressBook,char *);
int valid_mobile(char []);
int unique_mobile(char [],struct AddressBook * addressBook);
int valid_Email(char []);
int unique_Email(char[],struct AddressBook * addressBook);
// Fuctions used to search the contact
void print_specific_contact(int ,struct AddressBook * addressBook,int);
int search_name(struct AddressBook * addressBook); 
int search_phone(struct AddressBook * addressBook);
int search_email(struct AddressBook * addressBook);
// Function used to Edit the Contact
void contact_edit(struct AddressBook * addressBook,int);
// A Global Array for Index
extern int Duplicate_index[100];
// Function used to Delete the Contact
void contact_delete(struct AddressBook * addressBook,int);
#endif

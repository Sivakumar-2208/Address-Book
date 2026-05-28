#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "contact.h"
#include "file.h"
#include "populate.h"
int Duplicate_index[100];//global array for storing count of contacts with same number
void listContacts(struct AddressBook *addressBook) 
{
    /* Define the logic for print the contacts */
	int j =	addressBook->contactCount;
	int count=1;
	for(int i=0;i<j;i++)
	{
		printf("\n-----------------------------------------------\n\n");
		printf("CONTACT : %d\n\n",count);
		printf("Name\t\t:\t%s\n",addressBook->contacts[i].name);
		printf("Phone Number\t:\t%s\n",addressBook->contacts[i].phone);
		printf("Email Id\t:\t%s\n",addressBook->contacts[i].email);
		count++;
	}
	printf("\n-----------------------------------------------");
}
void initialize(struct AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
void createContact(struct AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */
	printf("Enter the contact name:");
	create_name(addressBook);
	printf("Enter the phone number:");
	char mobile[30];//created a local Mobile number variable
	if(create_phone(addressBook,mobile))//If validation of the Mobile number becomes True copy local Mobile number variable to address book 
	{
		strcpy(addressBook->contacts[addressBook->contactCount].phone,mobile);
	}
	printf("Enter the email id:");
	char Email[30];//created a local Email variable
	if(create_email(addressBook,Email))//If validation of the Email address becomes True copy local Email variable to address book 
	{
		strcpy(addressBook->contacts[addressBook->contactCount].email,Email);
	}
	(addressBook->contactCount)++;
}
void create_name(struct AddressBook * addressBook)
{
	getchar();
	scanf("%[^\n]",addressBook->contacts[addressBook->contactCount].name);//Getting name as a input while creating contact
}
int create_phone(struct AddressBook * addressBook,char * mobile)
{
	int i=0;
	do
	{
		getchar();
		scanf("%[^\n]",mobile);
		if(!(valid_mobile(mobile)))//calling validate mobile function
		{
			printf("Invalid mobile number\nEnter the valid mobile number:");
			i=1;
		}
		else if(!(unique_mobile(mobile,addressBook)))//calling unique mobile function
		{
			printf("Duplicate mobile number\nEnter the unique mobile number:");
			i=1;
		}
		else
		{
			i=0;
		}
	}while(i);
	return 1;
}
int create_email(struct AddressBook * addressBook,char * Email)
{
	int i=0;
	do
	{
		getchar();
		scanf("%[^\n]",Email);
		if(!(valid_Email(Email)))//calling validate Email function
		{
			printf("Enter the valid Email Id:");
			i=1;
		}
		else if(!(unique_Email(Email,addressBook)))//calling unique Email function to check for duplicate Email
		{
			printf("Duplicate Email Id\nEnter the unique Email Id:");
			i=1;
		}
		else
		{
			i=0;
		}
	}while(i);
	return 1;
}
int valid_mobile(char mobile[])
{
	int j=strlen(mobile);
	for(int i=0;i<j;i++)
	{
		if(j != 10 || !(isdigit(mobile[i])))//check all characters are digits and characters count equal to 10
		{
			return 0;
		}
	}
	return 1;
}
int unique_mobile(char mobile[],struct AddressBook * addressBook)
{
	for(int i=0;i<(addressBook->contactCount);i++)
	{
		if(!(strcmp(mobile,addressBook->contacts[i].phone)))//compare all stored mobile numbers to find duplicate mobile number or not
		{
			return 0;
		}
	}
	return 1;
}
int valid_Email(char Email[])
{
	int flag=0;
	int j=strlen(Email);
	for(int i=0;i<j;i++)
	{
		if(isupper(Email[i]))//check any uppercase is present are not
		{
			printf("Uppercase characters are not allowed\n");
			return 0;
		}
		if(Email[i] == '@')//check for @ character is present are not
		{
			flag=1;
			if(!(isalnum(Email[i+1]) && isalnum(Email[i-1])))
			{
				printf("Before and After of the '@' only alphanumeric characters should be present\n");
				return 0;
			}
			if(isupper(Email[i+1]))
			{
				printf("Uppercase characters are not allowed\n");
				return 0;
			}
		}
	}
	if(flag==0)
	{
		printf("Every Email Id must contain '@' symbol\n");
		return 0;
	}
	char ch[] = {".com"};
	int len_ch = strlen(ch);
	char * k = strstr(Email,ch);//check for ".com" is present are not
	if(k)
	{
		if(!(*(k+len_ch) == '\0'))//check whether ".com" is present at last or not
		{
			printf("Every Email Id must End with '.com'\n");
			return 0;
		}
	}
	else
	{
		printf("Every Email Id must contain '.com'\n");
		return 0;
	}
	return 1;
}
int unique_Email(char Email[],struct AddressBook * addressBook)
{
	for(int i=0;i<(addressBook->contactCount);i++)
	{
		if(!(strcmp(Email,addressBook->contacts[i].email)))//Compare all Contact Emails to find duplicate or not 
		{
			return 0;
		}
	}
	return 1;
}
void searchContact(struct AddressBook *addressBook) 
{
	/* Define the logic for search */
	int option;
label:
	printf("Enter any one details option for searching:\n1.Name\n2.Phone number\n3.Email Id\n");
	scanf("%d",&option);
	int serial_no=1;
	switch(option)//used switch case to access a contact using details such as name,email,phone 
	{
		case 1:
			search_name(addressBook);
			break;
		case 2:
			int p = search_phone(addressBook);
			if(p != -1)//if search phone return -1 no such contact detail found
			{
				print_specific_contact(p,addressBook,serial_no);
			}
			break;
		case 3:
			int e = search_email(addressBook);
			if(e != -1)//if search email return -1 no such contact detail found
			{
				print_specific_contact(e,addressBook,serial_no);
			}
			break;
		default:
			printf("Invalid Option\n");
			goto label;
	}
}
int search_name(struct AddressBook * addressBook) 
{
	int count=0;
	char name[30];
	printf("Enter the name of the contact:");
	getchar();
	scanf("%[^\n]",name);
	int flag=0;
	int serial_no = 0;
	for(int i=0;i<(addressBook->contactCount);i++)
	{
		if(!(strcmp(name,addressBook->contacts[i].name)))//compare entire contact list with the specified contact name 
		{
			serial_no++;
			Duplicate_index[count]=i;	
			print_specific_contact(i,addressBook,serial_no);
			flag=1;
			count++;
		}
	}
	if(flag ==0)
	{
		printf("No Such Contact Found\n");
	}
	return count;
}
int search_phone(struct AddressBook *addressBook)
{
	char phone[30];
	int i;
	printf("Enter the phone number of the contact:");
	do
	{
		i=0;
		getchar();
		scanf("%[^\n]",phone);
		if(valid_mobile(phone))//caling valid mobile to check specified mobile is valid or not
		{
			for(int i=0;i<(addressBook->contactCount);i++)
			{
				if(!(strcmp(phone,addressBook->contacts[i].phone)))//compare each contact to find the specified contact
				{
					return i;
				}
			}
			printf("No Such Contact Phone Number Found");
			return -1;
		}
		else
		{
			printf("Invalid mobile number\nEnter the valid mobile number:");
			i=1;
		}
	}while(i);
}
int search_email(struct AddressBook * addressBook)
{
	char email[30];
	int i;
	printf("Enter the Email Id of the contact:");
	do
	{
		i=0;
		getchar();
		scanf("%[^\n]",email);
		if(valid_Email(email))//calling valid email to check specified email is valid or not
		{
			for(int i=0;i<(addressBook->contactCount);i++)
			{
				if(!(strcmp(email,addressBook->contacts[i].email)))//compare each contact with specified contact 
				{
					return i;
				}
			}
			printf("No Such Contact Email Id Found");
			return -1;
		}
		else
		{
			printf("Invalid Email Id\nEnter the valid Email Id:");
			i=1;
		}
	}while(i);
}
void print_specific_contact(int i,struct AddressBook * addressBook,int serial_no)//function to print a specific contact
{
	printf("\n-----------------------------------------------\n\n");
	printf("CONTACT : %d\n\n",serial_no);
	printf("Name\t\t:\t%s\n",addressBook->contacts[i].name);
	printf("Phone Number\t:\t%s\n",addressBook->contacts[i].phone);
	printf("Email Id\t:\t%s\n",addressBook->contacts[i].email);
	printf("\n-----------------------------------------------\n");
}
void editContact(struct AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
	int option;		
	do
	{
		printf("Enter any option to Search\n1.Search By Name\n2.Search By Phone Number\n3.Search By Email Id\n4.Exit\n");
		scanf("%d",&option);
		switch(option)//switch case for the options to search by which detail such as phone,email,name
		{
			case 1:
				int count = search_name(addressBook);
				if(count)
				{
					int dummy;
					int name_index;
					if(count > 1)//if more than one contact found with same name ask for confirmation which is user's specified contact
					{
						printf("Total %d Contacts Found With Same Name\nEnter the Specific Serial Number to Confirm the Contact:",count);
						scanf("%d",&dummy);
						name_index = Duplicate_index[dummy-1];
					}
					else
					{
						name_index = Duplicate_index[0];
					}
					contact_edit(addressBook,name_index);
				}
				break;
			case 2:
				int phone_index = search_phone(addressBook);
				if(phone_index != -1)
				{
					print_specific_contact(phone_index,addressBook,1);
					contact_edit(addressBook,phone_index);
				}
				break;
			case 3:
				int email_index = search_email(addressBook);
				if(email_index != -1)
				{
					print_specific_contact(email_index,addressBook,1);
					contact_edit(addressBook,email_index);
				}
				break;
			case 4:
				break;
			default:
				printf("Invalid option\n");
		}
	}while(option != 4);//runs untill user enter exit
}
void contact_edit(struct AddressBook * addressBook,int index)
{
	int opt;
	do
	{
		printf("Which detail you want to Edit\n1.Name\n2.Phone Number\n3.Email Id\n4.Exit\n");
		scanf("%d",&opt);
		switch(opt)//used switch to ask which details need to be edited
		{
			case 1:
				printf("Enter the name:");
				getchar();
				scanf("%[^\n]",addressBook->contacts[index].name);
				print_specific_contact(index,addressBook,1);
				printf("Details Edited Successfully\n");
				break;
			case 2:
				printf("Enter the phone number:");
				char mobile[30];
				if(create_phone(addressBook,mobile))//check whether user entered detail is valid and not duplicate
				{
					strcpy(addressBook->contacts[index].phone,mobile);
					print_specific_contact(index,addressBook,1);
					printf("Details Edited Successfully\n");
				}
				break;
			case 3:
				printf("Enter the email id:");
				char Email[30];
				if(create_email(addressBook,Email))//check the detail entered by user is valid and not duplicate
				{
					strcpy(addressBook->contacts[index].email,Email);
					print_specific_contact(index,addressBook,1);
					printf("Details Edited Successfully\n");
				}
				break;
			case 4:
				break;
			default:
				printf("Invalid Detail\n");
		}
	}while(opt != 4);//runs until user enters exit 
}
void deleteContact(struct AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
	int option,i;		
	do
	{
		printf("Enter any option to Search\n1.Search By Name\n2.Search By Phone Number\n3.Search By Email Id\n4.Exit\n");
		scanf("%d",&option);
		switch(option)//used switch case to give options to search by details such as phone,email,name
		{
			case 1:
				int count = search_name(addressBook);
				if(count)
				{
					int dummy;
					int name_index;
					if(count > 1)//if more than one contact found with same name ask for confirmation which is user's specified contact
					{
						printf("Total %d Contacts Found With Same Name\nEnter the Specific Serial Number to Confirm the Contact:",count);
						scanf("%d",&dummy);
						name_index = Duplicate_index[dummy-1];
					}
					else
					{
						name_index = Duplicate_index[0];
					}
					printf("Is this the contact you wish to Delete(1-Yes or 0-No):");//asks for confimation before deleting
					scanf("%d",&i);
					if(i)
					{
						contact_delete(addressBook,name_index);
					}
				}
				break;
			case 2:
				int phone_index = search_phone(addressBook);
				if(phone_index != -1)
				{
					print_specific_contact(phone_index,addressBook,1);
					printf("Is this the contact you wish to Delete(1-Yes or 0-No):");//asks for confirmation
					scanf("%d",&i);
					if(i)
					{
						contact_delete(addressBook,phone_index);
					}
				}
				break;
			case 3:
				int email_index = search_email(addressBook);
				if(email_index != -1)
				{
					print_specific_contact(email_index,addressBook,1);
					printf("Is this the contact you wish to Delete(1-Yes or 0-No):");//asks for confirmation
					scanf("%d",&i);
					if(i)
					{
						contact_delete(addressBook,email_index);
					}
				}
				break;
			case 4:
				break;
			default:
				printf("Invalid option\n");
		}
	}while(option != 4);
}
void contact_delete(struct AddressBook * addressBook,int index)
{
	for(int i=index;i<(addressBook->contactCount);i++)
	{
		strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
		strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
		strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);		
	}
	printf("Contact Deleted Successfully\n");
	(addressBook->contactCount)--;
}

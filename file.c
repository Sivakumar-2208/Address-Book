#include <stdio.h>
#include "file.h"

void loadContactsFromFile(struct AddressBook *addressBook) 
{
	int i=0;
	FILE * fp = fopen("Contacts.csv","r");	
	fscanf(fp,"#%d\n",&addressBook->contactCount);//copy no.of cotacts into contactCount variable
	while(!(feof(fp)))//using loop load contacts from csv file to address book stucture
	{
		fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
		i++;
	}
	fclose(fp);
}

void saveContactsToFile(struct AddressBook *addressBook) 
{
    	FILE * fp = fopen("Contacts.csv","w");
	fprintf(fp,"#%d\n",addressBook->contactCount);//save contact count in file
	for(int i=0;i<addressBook->contactCount;i++)//using loop storing contacts from address book structure
	{
		fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}
	fclose(fp);
}

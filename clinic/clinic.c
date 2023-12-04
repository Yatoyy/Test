/*/////////////////////////////////////////////////////////////////////////
						Assignment 1 - Milestone 3
Full Name  :Gian Carlo Rapirap
Student ID#:114480917
Email      :gcrapirap@myseneca.ca
Section    :NKK

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
	printf("Pat.# Name            Phone#\n"
		"----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
	if (fmt == FMT_FORM)
	{
		printf("Name  : %s\n"
			"Number: %05d\n"
			"Phone : ", patient->name, patient->patientNumber);
		displayFormattedPhone(patient->phone.number);
		printf(" (%s)\n", patient->phone.description);
	}
	else
	{
		printf("%05d %-15s ", patient->patientNumber,
			patient->name);
		displayFormattedPhone(patient->phone.number);
		printf(" (%s)\n", patient->phone.description);
	}
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
	printf("Clinic Appointments for the Date: ");

	if (isAllRecords)
	{
		printf("<ALL>\n\n");
		printf("Date       Time  Pat.# Name            Phone#\n"
			"---------- ----- ----- --------------- --------------------\n");
	}
	else
	{
		printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
		printf("Time  Pat.# Name            Phone#\n"
			"----- ----- --------------- --------------------\n");
	}
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
	const struct Appointment* appoint,
	int includeDateField)
{
	if (includeDateField)
	{
		printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
			appoint->date.day);
	}
	printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
		patient->patientNumber, patient->name);

	displayFormattedPhone(patient->phone.number);

	printf(" (%s)\n", patient->phone.description);
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
	int selection;

	do {
		printf("Veterinary Clinic System\n"
			"=========================\n"
			"1) PATIENT     Management\n"
			"2) APPOINTMENT Management\n"
			"-------------------------\n"
			"0) Exit System\n"
			"-------------------------\n"
			"Selection: ");
		selection = inputIntRange(0, 2);
		putchar('\n');
		switch (selection)
		{
		case 0:
			printf("Are you sure you want to exit? (y|n): ");
			selection = !(inputCharOption("yn") == 'y');
			putchar('\n');
			if (!selection)
			{
				printf("Exiting system... Goodbye.\n\n");
			}
			break;
		case 1:
			menuPatient(data->patients, data->maxPatient);
			break;
		case 2:
			menuAppointment(data);
			break;
		}
	} while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
	int selection;

	do {
		printf("Patient Management\n"
			"=========================\n"
			"1) VIEW   Patient Data\n"
			"2) SEARCH Patients\n"
			"3) ADD    Patient\n"
			"4) EDIT   Patient\n"
			"5) REMOVE Patient\n"
			"-------------------------\n"
			"0) Previous menu\n"
			"-------------------------\n"
			"Selection: ");
		selection = inputIntRange(0, 5);
		putchar('\n');
		switch (selection)
		{
		case 1:
			displayAllPatients(patient, max, FMT_TABLE);
			suspend();
			break;
		case 2:
			searchPatientData(patient, max);
			break;
		case 3:
			addPatient(patient, max);
			suspend();
			break;
		case 4:
			editPatient(patient, max);
			break;
		case 5:
			removePatient(patient, max);
			suspend();
			break;
		}
	} while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
	int selection;

	do {
		printf("Edit Patient (%05d)\n"
			"=========================\n"
			"1) NAME : %s\n"
			"2) PHONE: ", patient->patientNumber, patient->name);

		displayFormattedPhone(patient->phone.number);

		printf("\n"
			"-------------------------\n"
			"0) Previous menu\n"
			"-------------------------\n"
			"Selection: ");
		selection = inputIntRange(0, 2);
		putchar('\n');

		if (selection == 1)
		{
			printf("Name  : ");
			inputCString(patient->name, 1, NAME_LEN);
			putchar('\n');
			printf("Patient record updated!\n\n");
		}
		else if (selection == 2)
		{
			inputPhoneData(&patient->phone);
			printf("Patient record updated!\n\n");
		}
	} while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
	int selection;

	do {
		printf("Appointment Management\n"
			"==============================\n"
			"1) VIEW   ALL Appointments\n"
			"2) VIEW   Appointments by DATE\n"
			"3) ADD    Appointment\n"
			"4) REMOVE Appointment\n"
			"------------------------------\n"
			"0) Previous menu\n"
			"------------------------------\n"
			"Selection: ");
		selection = inputIntRange(0, 4);
		putchar('\n');
		switch (selection)
		{
		case 1:
			viewAllAppointments(data);  // ToDo: You will need to create this function!
			suspend();
			break;
		case 2:
			viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
			suspend();
			break;
		case 3:
			addAppointment(data->appointments, data->maxAppointments,
				data->patients, data->maxPatient);  // ToDo: You will need to create this function!
			suspend();
			break;
		case 4:
			removeAppointment(data->appointments, data->maxAppointments,
				data->patients, data->maxPatient);  // ToDo: You will need to create this function!
			suspend();
			break;
		}
	} while (selection);
}

// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
	int i = 0;

	displayPatientTableHeader();

	for (i = 0; i < max; i++)
	{
		if (patient[i].patientNumber != 0)
		{
			displayPatientData(&patient[i], fmt);
		}
	}
	printf("\n");
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{
	int selection, flag = 0;

	do
	{
		printf("Search Options\n"
			"==========================\n"
			"1) By patient number\n"
			"2) By phone number\n"
			"..........................\n"
			"0) Previous menu\n"
			"..........................\n"
			"Selection: ");

		scanf(" %d", &selection);

		switch (selection)
		{
		case 1:
			printf("\n");
			searchPatientByPatientNumber(patient, max);
			flag = 1;
			break;
		case 2:
			printf("\n");
			searchPatientByPhoneNumber(patient, max);
			suspend();
			flag = 2;
			break;
		case 0:
			printf("\n");
			flag = 0;
		}
	} while (flag != 0);
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
	int index = 0, i;
	int openIndex = 0;

	for (i = 0; i < max; i++)
	{
		if (patient[i].patientNumber > 0)
		{
			index++;
		}
		if (patient[i].patientNumber == 0)
		{
			openIndex = i;
			i = max;
		}
	}
	if (index == max)
	{
		printf("ERROR: Patient listing is FULL!\n");
		printf("\n");
	}
	else
	{
		patient[openIndex].patientNumber = nextPatientNumber(patient, max);
		inputPatient(&patient[openIndex]);
		printf("*** New patient record added ***\n");
		printf("\n");
	}
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
	int input, index;

	printf("Enter the patient number: ");
	input = inputInt();
	printf("\n");

	index = findPatientIndexByPatientNum(input, patient, max);
	if (index != -1)
	{
		menuPatientEdit(&patient[index]);
	}
	else
	{
		printf("ERROR: Patient record no found!\n");
	}
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
	int input, index;
	char options[3] = { 'y', 'n','\0' };
	char choice;

	printf("Enter the patient number: ");
	input = inputInt();
	printf("\n");

	index = findPatientIndexByPatientNum(input, patient, max);
	if (index != -1)
	{
		displayPatientData(&patient[index], FMT_FORM);

		printf("\n");
		printf("Are you sure you want to remove this patient record? (y/n): ");
		choice = inputCharOption(options);
		clearInputBuffer();

		if (choice == 'y')
		{
			patient[index].patientNumber = 0;
			strcpy(patient[index].name, "\0");
			strcpy(patient[index].phone.description, "\0");
			strcpy(patient[index].phone.number, "\0");

			printf("Patient record has been removed!\n");
			printf("\n");
		}
		else
		{
			printf("Operation aborted.\n");
			printf("\n");
		}
	}
	else
	{
		printf("ERROR: Patient record not found!\n");
		printf("\n");
	}
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data)
{
	int temp[50] = { 0 }, tempIndex[50] = { 0 };
	int i = 0, index = 0, numOfAppointments = 0;
	// Sort Appointments according to date and time
	appointmentSort(data, data->maxAppointments);

	//find the current max appointments
	for (i = 0; i < data->maxAppointments; i++)
	{
		if (data->appointments[i].date.year != 0)
		{
			temp[numOfAppointments] = data->appointments[i].patient.patientNumber;
			tempIndex[numOfAppointments] = i;
			numOfAppointments++;
		}
	}

	displayScheduleTableHeader(&data->appointments->date, FMT_TABLE);

	for (i = 0; i < numOfAppointments; i++)
	{
		index = findPatientIndexByPatientNum(temp[i], data->patients, data->maxPatient);
		displayScheduleData(&data->patients[index], &data->appointments[tempIndex[i]], FMT_TABLE);
	}

	printf("\n");
}
// View appointment schedule for the user input date
// Todo:
/*Prompt user to enter year month and day accomedate for leap years. Search for the appointment matching the input.
print the appointment schedule*/
void viewAppointmentSchedule(struct ClinicData* data)
{
	int temp[50] = { 0 }, tempIndex[50] = { 0 };
	int i, numOfAppointments = 0, index;
	int year, month, day;

	validDate(&year, &month, &day);
	printf("\n");

	//Sort Appointments according to date and time
	appointmentSort(data, data->maxAppointments);

	//find the current max appointments
	for (i = 0; i < data->maxAppointments; i++)
	{
		if (data->appointments[i].patient.patientNumber != 0)
		{
			if (data->appointments[i].date.year == year &&
				data->appointments[i].date.month == month &&
				data->appointments[i].date.day == day)
			{
				temp[numOfAppointments] = data->appointments[i].patient.patientNumber;
				tempIndex[numOfAppointments] = i;
				numOfAppointments++;
			}
		}
	}

	displayScheduleTableHeader(&data->appointments->date, 0);

	for (i = 0; i < numOfAppointments; i++)
	{
		index = findPatientIndexByPatientNum(temp[i], data->patients, data->maxPatient);
		displayScheduleData(&data->patients[index], &data->appointments[tempIndex[i]], 0);
	}

	printf("\n");
}
// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appointment, int maxAppointments, struct Patient* dataPatients, int maxPatients)
{
	int i, flag = 0, openIndex = -1, result = -1;
	int year = 0, month = 0, day = 0, hour = 0, minute = 0, inputPatientNumber;

	while (result == -1)
	{
		printf("Patient Number: ");
		inputPatientNumber = inputIntPositive();
		result = findPatientIndexByPatientNum(inputPatientNumber, dataPatients, maxPatients);
		if (result == -1)
		{
			printf("Error finding patient\n");
		}
	}

	do
	{
		validDate(&year, &month, &day);
		validTime(&hour, &minute);

		for (i = 0; i < maxAppointments; i++)
		{
			if(appointment[i].date.year != 0)
			{
				if (appointment[i].date.year == year && appointment[i].date.month == month &&
					appointment[i].date.day == day && appointment[i].time.hour == hour &&
					appointment[i].time.min == minute)
				{
					printf("\n");
					printf("ERROR: Appointment timeslot is not available!\n");
					printf("\n");
					openIndex = -1;
					i = maxAppointments;
					flag = 1;
				}
				else
				{
					openIndex = i;
				}
			}
		}

		if(openIndex != -1)
		{
			appointment[openIndex].date.year = year;
			appointment[openIndex].date.month = month;
			appointment[openIndex].date.day = day;
			appointment[openIndex].time.hour = hour;
			appointment[openIndex].time.min = minute;
			appointment[openIndex].patient.patientNumber = inputPatientNumber;
			printf("\n");
			printf("*** Appointment scheduled! ***\n");
			flag = 0;
		}
	} while (flag != 0);

}
// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appointment, int maxAppointments, struct Patient* patient, int maxPatients)
{
	char choice = 0, options[3] = { "yn" };
	int result = -1, i, validation = -1;
	int year = 0, month = 0, day = 0, inputPatientNumber;

	printf("Patient Number: ");
	inputPatientNumber = inputIntPositive();
	result = findPatientIndexByPatientNum(inputPatientNumber, patient, maxPatients);
	if (result == -1)
	{
		printf("ERROR: Patient record not found!\n");
		printf("\n");
		return;
	}

	validDate(&year, &month, &day);
	printf("\n");

	for (i = 0; i < maxAppointments; i++)
	{
		if (inputPatientNumber == appointment[i].patient.patientNumber &&
			appointment[i].date.year == year && appointment[i].date.month == month &&
			appointment[i].date.day == day)
		{
			validation = i;
			i = maxAppointments;
		}
	}

	if (validation == -1)
	{
		printf("Appointment not found\n");
	}
	else
	{
		displayPatientData(&patient[result], FMT_FORM);
		printf("\n");
		printf("Are you sure you want to remove this appointment (y,n): ");
		choice = inputCharOption(options);
		printf("\n");

		if (choice != 'y')
		{
			printf("Operation aborted.\n");
			printf("\n");
		}
		else
		{
			appointment[validation].date.year = 0;
			appointment[validation].date.month = 0;
			appointment[validation].date.day = 0;
			appointment[validation].time.hour = 0;
			appointment[validation].time.min = 0;
			appointment[validation].patient.patientNumber = 0;
			printf("Appointment record has been removed!\n");
			printf("\n");
		}
	}
}
//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
	int input, index;
	printf("Search by patient number: ");
	input = inputInt();

	index = findPatientIndexByPatientNum(input, patient, max);
	if (index != -1)
	{
		printf("\n");
		displayPatientData(&patient[index], FMT_FORM);
		printf("\n");
		suspend();
	}
	else
	{
		printf("\n");
		printf("*** No records found ***\n");
		printf("\n");
		suspend();
	}
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
	char input[1000] = { 0 };
	int i, matches = 0;
	int index[1000] = { 0 };
	char temp[1000] = { 0 };

	printf("Search by phone number: ");
	inputCString(input, PHONE_LEN, PHONE_LEN);
	printf("\n");

	for (i = 0; i < max; i++)
	{
		int len = strlen(patient[i].phone.number);
		if (len != 10)
		{
			strcpy(temp, patient[i].phone.number);
			trim(temp);
		}

		int results = strcmp(input,temp);
		if (results == 0)
		{
			index[matches] = i;
			matches++;
		}
	}

	displayPatientTableHeader();

	if (matches != 0)
	{
		if (matches == 1)
		{
			displayPatientData(&patient[index[0]], FMT_TABLE);
			clearInputBuffer();
			printf("\n");
		}
		else
		{
			for (i = 0; i < matches; i++)
			{
				displayPatientData(&patient[index[i]], FMT_TABLE);
			}
			clearInputBuffer();
			printf("\n");
		}
	}
	else
	{
		printf("\n");
		printf("*** No records found ***\n");
		clearInputBuffer();
		printf("\n");
	}
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
	int nextNumber = 0, i;

	for (i = 0; i < max; i++)
	{
		if (nextNumber < patient[i].patientNumber)
		{
			nextNumber = patient[i].patientNumber;
		}
	}

	nextNumber++;

	return nextNumber;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
	int index = -1, i;

	for (i = 0; i < max; i++)
	{
		if (patientNumber == patient[i].patientNumber)
		{
			index = i;
		}
	}
	return index;
}

// Sort Appointments in date and time
void appointmentSort(struct ClinicData* data, int max) {
	int i, j, swapped;
	struct Appointment tempA;

	for (i = 0; i < max - 1; i++) {
		swapped = 0;
		for (j = 0; j < max - i - 1; j++) {
			if (data->appointments[j].date.year > data->appointments[j + 1].date.year) {
				tempA = data->appointments[j];
				data->appointments[j] = data->appointments[j + 1];
				data->appointments[j + 1] = tempA;
				swapped = 1;
			}
			else if (data->appointments[j].date.year == data->appointments[j + 1].date.year) {
				if (data->appointments[j].date.month > data->appointments[j + 1].date.month) {
					tempA = data->appointments[j];
					data->appointments[j] = data->appointments[j + 1];
					data->appointments[j + 1] = tempA;
					swapped = 1;
				}
				else if (data->appointments[j].date.month == data->appointments[j + 1].date.month) {
					if (data->appointments[j].date.day > data->appointments[j + 1].date.day) {
						tempA = data->appointments[j];
						data->appointments[j] = data->appointments[j + 1];
						data->appointments[j + 1] = tempA;

						swapped = 1;
					}
					else if (data->appointments[j].date.day == data->appointments[j + 1].date.day) {
						if (data->appointments[j].time.hour > data->appointments[j + 1].time.hour) {
							tempA = data->appointments[j];
							data->appointments[j] = data->appointments[j + 1];
							data->appointments[j + 1] = tempA;
							swapped = 1;
						}
						else if (data->appointments[j].time.hour == data->appointments[j + 1].time.hour) {
							if (data->appointments[j].time.min > data->appointments[j + 1].time.min) {
								tempA = data->appointments[j];
								data->appointments[j] = data->appointments[j + 1];
								data->appointments[j + 1] = tempA;
								swapped = 1;
							}
						}
					}
				}
			}
		}
		if (swapped == 0)
			i = max; // Equivalent to using break
	}
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{
	printf("Patient Data Input\n");
	printf("------------------\n");
	printf("Number: 0%d\n", patient->patientNumber);

	printf("Name  : ");
	inputCString(patient->name, 0, NAME_LEN);

	printf("\n");
	inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone)
{
	int min = 1;
	int max = 4;
	int selection;

	printf("Phone Information\n");
	printf("-----------------\n");
	printf("How will the patient like to be contacted?\n");
	printf("1. Cell\n");
	printf("2. Home\n");
	printf("3. Work\n");
	printf("4. TBD\n");
	printf("Selection: ");

	selection = inputIntRange(min, max);

	switch (selection)
	{
	case 1:
		printf("\n");

		strcpy(phone->description, "CELL");
		printf("Contact: %s\n", phone->description);

		printf("Number : ");
		validPhoneNumber(phone->number, PHONE_LEN);
		clearInputBuffer();
		printf("\n");

		break;

	case 2:
		printf("\n");

		strcpy(phone->description, "HOME");
		printf("Contact: %s\n", phone->description);

		printf("Number : ");
		validPhoneNumber(phone->number, PHONE_LEN);
		clearInputBuffer();
		printf("\n");

		break;

	case 3:
		printf("\n");

		strcpy(phone->description, "WORK");
		printf("Contact: %s\n", phone->description);

		printf("Number : ");
		validPhoneNumber(phone->number, PHONE_LEN);
		clearInputBuffer();
		printf("\n");
		break;

	case 4:
		printf("\n");
		strcpy(phone->description, "TBD");
		strcpy(phone->number, "\0");
		break;
	}
}

// Search for valid time
void validTime(int* hour, int* min)
{
	int minHour = 0, minMinute = 0, maxHour = 23, maxMinute = 59;
	int flag = 0, inputHour, inputMinute;

	do
	{
		printf("Hour (%d-%d)  : ",minHour, maxHour);
		inputHour = inputIntRange(minHour, maxHour);
		printf("Minute (%d-%d): ",minMinute,maxMinute);
		inputMinute = inputIntRange(minMinute, maxMinute);

		if (inputHour < STARTING_HOUR || inputHour > CLOSING_HOUR)
		{
			printf("ERROR: Time must be between %02d:%02d and %02d:%02d in %d minute intervals.\n",
				STARTING_HOUR, STARTING_MIN, CLOSING_HOUR, CLOSING_MIN, APPOINTMENT_INTERVAL);
			printf("\n");
			flag = 1;
		}
		else if (inputHour == CLOSING_HOUR)
		{
			if (inputMinute > STARTING_MIN)
			{
				printf("ERROR: Time must be between %02d:%02d and %02d:%02d in %d minute intervals.\n",
					STARTING_HOUR, STARTING_MIN, CLOSING_HOUR, CLOSING_MIN, APPOINTMENT_INTERVAL);
				printf("\n");
				flag = 1;
			}
			else
			{
				*hour = inputHour;
				*min = inputMinute;
				flag = 0;
			}
		}
		else if (inputMinute != APPOINTMENT_INTERVAL && inputMinute != STARTING_MIN)
		{
			printf("ERROR: Time must be between %02d:%02d and %02d:%02d in %d minute intervals.\n",
				STARTING_HOUR, STARTING_MIN, CLOSING_HOUR, CLOSING_MIN, APPOINTMENT_INTERVAL);
			printf("\n");
			flag = 1;
		}

		else
		{
			*hour = inputHour;
			*min = inputMinute;
			flag = 0;
		}
	} while (flag != 0);

}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{
	int count = 0;
	char line[512];

	FILE* file = fopen(datafile, "r");

	if (file != NULL)
	{
		for (count = 0; count < max; count++)
		{
			fgets(line, sizeof(line), file);
			sscanf(line, "%d|%[^|]|%[^|]|%[^|]",
				&patients[count].patientNumber,
				patients[count].name,
				patients[count].phone.description,
				patients[count].phone.number);
		}
	}

	fclose(file);
	return count;
}
// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
	int i = 0, count = 0;
	FILE* file = fopen(datafile, "r");

	if (file != NULL)
	{
		for (i = 0; i < max; i++)
		{
			if (fscanf(file, "%d,%d,%d,%d,%d,%d",
				&appoints[i].patient.patientNumber,
				&appoints[i].date.year,
				&appoints[i].date.month,
				&appoints[i].date.day,
				&appoints[i].time.hour,
				&appoints[i].time.min) == 6)
			{
				count++;
			}
		}
	}

	fclose(file);
	return count;
}

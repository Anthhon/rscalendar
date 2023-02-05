#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define TERMINATOR 1

unsigned short getDaysInMonth(unsigned month_n){
	unsigned short days[] = {31, 28, 31, 30, 31, 30,
				   31, 31, 30, 31, 30, 31};
	return days[month_n];
}

void printCurrentCalendar(){
	/* timeData should store a value like
	 * Thu May 27 20:20:01 2023 
	 * if not this should return NULL value */
	time_t timeData = time(NULL);
	if (&timeData == NULL){
		puts("ERROR: Wasn't possible to retrieve time data!");
		return;
	}
	// Stores formatted time
	struct tm tm = *localtime(&timeData);

	/* For some reason year isn't being
	 * returned correctly so these magic numbers are needed*/
	unsigned short year = tm.tm_year + 1900;
	unsigned short day = tm.tm_mday;
	unsigned short month = tm.tm_mon + TERMINATOR;
	unsigned short monthDays = getDaysInMonth(tm.tm_mon);

	// Print calendar in table format
	printf("--------%04d %02d %02d--------", year, day, month);
	for (unsigned short day = 1; day <= monthDays; ++day){
		// Break line in each week 
		if (day % 7 == 1) puts("");
		printf("%02i  ", day);
	}
	puts("");

	return;
}

void printSpecificCalendar(unsigned short year, unsigned short monthNum){
	/* timeData should store a value like
	 * Thu May 27 20:20:01 2023 
	 * if not this should return NULL value */
	time_t timeData = time(NULL);
	if (&timeData == NULL){
		puts("ERROR: Wasn't possible to retrieve time data!");
		return;
	}
	// Stores formatted time
	struct tm tm = *localtime(&timeData);

	// Retrieve month name
	char months[12][4] = {"Jan", "Feb", "Mar", "Apr",
			      "May", "Jun", "Jul", "Aug",
			      "Sep", "Oct", "Nov", "Dec"};
	char month[4];
	strcpy(month, months[monthNum - TERMINATOR]);

	/* For some reason year and month
	 * are not being returned correctly
	 * so these magic numbers are needed*/
	unsigned short monthDays = getDaysInMonth(monthNum - TERMINATOR);

	// Print calendar in table format
	printf("---------%04d %s---------", year, month);
	for (unsigned short day = 1; day <= monthDays; ++day){
		// Break line in each week 
		if (day % 7 == 1) puts("");
		printf("%02i  ", day);
	}
	puts("");

	return;
}

// Handle user input
int main(int argc, char *argv[]){
	// Handle user parameters
	if (argc == 1){
		// Prompt user the current calendar if none arguments
		printCurrentCalendar();
		return 0;
	} else if (argc > 5){
		puts("INVALID INPUT: ./cCalendar -y [YEAR] -m [MONTH]");
		return 1;
	}

	// Search for parameters
	unsigned short inYear = 0;
	unsigned short inMonth = 0;
	for (int i = 0; i < argc; ++i){
		if (strcmp(argv[i], "-y") == 0|| strcmp(argv[i], "-Y") == 0){
			// Catch next argument as year
			// Should return 0 if not valid number
			int temp_year = atoi(argv[i + 1]);
			// Checks for a valid year
			if (temp_year == 0 || temp_year > 9999){
				printf("INVALID INPUT: %s %s\n", argv[i], argv[i + 1]);
				return 1;
			}
			inYear = temp_year;
		}
		else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "-M") == 0){
			// Catch next argument as month
			// Should return 0 if not valid number
			int temp_month = atoi(argv[i + 1]);
			// Checks for a valid month
			if (temp_month == 0 || temp_month > 12){
				printf("INVALID INPUT: %s %s\n", argv[i], argv[i + 1]);
				return 1;
			}
			inMonth = temp_month;
		}
	}
	// Check is has found parameters
	if (inYear != 0 && inMonth != 0)
		// Print calendar in specified time
		printSpecificCalendar(inYear, inMonth);
	else puts("INVALID INPUT: You should pass both parameters!");
	return 0;
}









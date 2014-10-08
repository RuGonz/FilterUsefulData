/*****************************************************************
Name: Rudy Gonzalez
Date: 05/6/13
Problem Number: Extra Credit
Instructor: Komogortsev, TSU
******************************************************************

 The purpose of this project is to create a readable output file
that shows the time and date, as well as the temperature in
Celcius. Lastly, the average of all temperatures for the entire
sample will be printed out as well. All output number are rounded
to two decimal places.

EDIT: Project must run in Linux and compile under cc

Sample Input File:
                     2
                     200707211245 F70.5
                     200708220812 C19.97
sample output File:
					 21.45 F --- recorded on 07/21/2007 at 1245
					 20.15 C --- recorded on 08/22/2007 at 0812

					 Average Temp --- 20.80 C
*****************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
/*****************************************************************
Function Prototypes
*****************************************************************/
void timeStamp(char stamp[], FILE *ifp); // inputs 12 characters into array
void symbolVer(char *xTemp, FILE *ifp, bool *status); // verifies if sympbol is
                                                      // appropriate (F or C)
void negNumb(double *temp, bool *tempStat, char xTemp, double *sumTemp); // verifues
                                                         // if degrees are positive

int main( )
{
	int     num = 0; //number of data entries
	char    stamp[13], // time stamp array initialized
	        xTemp; // letter that temp is abbreviated with
	double  temp = 0, // Temperature
			sumTemp = 0, // sum of temperatures
			avgTemp = 0; // avg temperatures
	bool    status,
	        tempStat;// if temp Symbol is F or C

	// initialize pointers to input and output files
	FILE *ifp, *ofp;

	//open input file
	ifp = fopen("biodata.dat", "r");
	if (ifp == NULL) {
	  fprintf(stderr, "Can't open input file!\n");
	  exit(1);
	}
    // create output file
	ofp = fopen("filtered_biodata.dat", "w");
	if (ofp == NULL) {
	  fprintf(stderr, "Can't open output file!");
	  exit(1);
	}
	// reads in number of lines from input file
	fscanf(ifp, "%d", &num);

	//outputs header text to output file
	fprintf(ofp, "BIODATA Formatted Output\n\n");
	int index;
	for(index = 0; index < num; index++)
	{
		timeStamp(stamp, ifp); // reads in time stamp to char array
		symbolVer(&xTemp, ifp, &status); // verify if temp is in F or C
		if(status== false)
		{
			exit(EXIT_FAILURE); // exits if failure occurs
		}
		// reads in temperature (double)
		fscanf(ifp, "%lf", &temp);
		// verifies acceptable temperature
		negNumb(&temp, &tempStat, xTemp, &sumTemp);
		if(tempStat == false)
		{
			fprintf(stderr, "\nError, Temperature can't be negative!\n");
			exit (EXIT_FAILURE);
		}
		//output to file all necessary information
		fprintf(ofp, "%.2f C --- recorded on ",temp);
		fprintf(ofp,"%c",*(stamp+4)); fprintf(ofp,"%c/",*(stamp+5));
		fprintf(ofp,"%c",*(stamp+6));fprintf(ofp,"%c/",*(stamp+7));
		fprintf(ofp,"%c",*(stamp+0));fprintf(ofp,"%c",*(stamp+1));fprintf(ofp,"%c",*(stamp+2));
		fprintf(ofp,"%c at ",*(stamp+3));
		fprintf(ofp,"%c",*(stamp+8));fprintf(ofp,"%c",*(stamp+9));fprintf(ofp,"%c",*(stamp+10));
		fprintf(ofp,"%c",*(stamp+11));fprintf(ofp,"%c",*(stamp+12));fprintf(ofp,"\n");
	}

	// averages sum of temperatures
	avgTemp = (sumTemp/num);
	//outputs to file the average temperature
	fprintf(ofp,"\nAverage Temperature --- %.2f C", avgTemp);

	//close input and output file
	fclose(ifp);
	fclose(ofp);

	return 0;
}

/*****************************************************************
//Function Definitions
*****************************************************************/

/* FUNCTION - void addSong
  *reads in time stamp from input file
          o returns nothing
 input parms - stamp array, file pointer
*/
void timeStamp(char stamp[], FILE *ifp)
{
	fscanf(ifp, "%s", stamp);
}

/* FUNCTION - void sumbolVer
  *verifies if symbol is F or C
          o returns nothing
 input parms - xTemp, file pointer, status
*/
void symbolVer(char *xTemp, FILE *ifp, bool *status)
{

	fgetc(ifp); // skip blank space
	*xTemp = fgetc(ifp); // read in degree character

	// upper case conversion if necessary
	if(*xTemp == 'f')
		*xTemp = 'F';
	if(*xTemp == 'c')
		*xTemp = 'C';

	if(*xTemp == 'F' || *xTemp == 'C')
		*status = true;
	else // if temp is negative
	{
		fprintf(stderr, "\nError, Temperature must be in F or C!\n");
		*status = false;
	}
}

/* FUNCTION - void negNumb
  *attempts to add a new song to the tsuPod
          o returns nothing
 input parms - temp, tempStat, xTemp, sumTemp
*/
void negNumb(double *temp, bool *tempStat, char xTemp, double *sumTemp)
{
	// converts from Fahrenheit to Celcius
	if(xTemp == 70)
		*temp = ((*temp-32)/1.8);

	// verifies Celcius temp is not negative
	if (*temp < 0)
		*tempStat = false;
	else
	{
		*sumTemp = (*sumTemp + *temp);
		*tempStat = true;
	}
}

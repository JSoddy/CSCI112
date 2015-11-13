#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 100

// Our files have comma-delimeted lines
const char delim[2] = ",";

// Function prototypes
void file_merge(FILE *, FILE *, FILE *);
void find_element(char[]);

// Most programs have one of these:
int main( int argc, char *argv[]) {

	// Open input and output files
	FILE *input_file1 = fopen("elements_file1.csv", "r");
	FILE *input_file2 = fopen("elements_file2.csv", "r");
	FILE *output_file = fopen("elements.csv", "w");

	// If any of the files failed to open, exit
	if ( input_file1 == NULL || input_file2 == NULL || output_file == NULL) {
		printf("Error loading file.");
		return 1; 		// Exit with an error
	}

	// Merge the two sorted input files into a single sorted output file
	file_merge (input_file1, input_file2, output_file);

	// close our input files
	fclose(input_file1);
	fclose(input_file2);
	fclose(output_file);
	
	// Loop through command line arguments, and search the elements
	//  file for the supplied strings
	int i;
	for (	i = 1; i < argc; i++){
		find_element(argv[i]);
	}

	return 0; // Exit with no errors
}

// Function to merge the contents of two data file into a single data file
void file_merge(FILE *input1, FILE *input2, FILE *output){

	// Strings to hold the contents of our read lines
	char file1_line[LINE_SIZE];
	char file2_line[LINE_SIZE];

	char file1_copy[LINE_SIZE];
	char file2_copy[LINE_SIZE];

	// Read a line from each of the two input files
	fgets(file1_line, LINE_SIZE, input1);
	fgets(file2_line, LINE_SIZE, input2);
	
	// Copy the file lines, so that we can retain them after modification
	strcpy(file1_copy, file1_line);
	strcpy(file2_copy, file2_line);
	
	// Until one of our files has reached EOF:
	while (! (feof(input1) || feof(input2))) {
		// read the first comma-delimited portion of each of our lines,
		//  giving us the atomic number of each read element as a string
		char *first = strtok(file1_line, delim);
		char *second = strtok(file2_line, delim);
		// convert the atomic number strings to integer
		int ato_num1 = atoi(first);
		int ato_num2 = atoi(second);
		// compare the two numbers, and write the smaller one into the output file
		if (ato_num1 < ato_num2) { // If the first atomic number is smaller:
			// Print the unchanged copy of the line
			fprintf(output, file1_copy);
			// Set line to empty
			file1_line[0] = '\0';
			// Read a new line from file 1
			fgets(file1_line, LINE_SIZE, input1);
			strcpy(file1_copy, file1_line);
			// Restore the unused line to its unchanged state
			strcpy(file2_line, file2_copy);
		} else {							// If the second atomic number is smaller:
			// Print the unchanged copy of the line
			fprintf(output, file2_copy);
			// Set line to empty
			file2_line[0] = '\0';
			// Read a new line
			fgets(file2_line, LINE_SIZE, input2);
			strcpy(file2_copy, file2_line);
			// Restore the unused line to its unchanged state
			strcpy(file1_line, file1_copy);
		}
	}
	// Copy each file until EOF. (Only one will be copied, since the other is already at EOF)
	while (!feof(input2)) { // Print each line and read the next until we hit the EOF
		fprintf(output, file2_line);
		fgets(file2_line, LINE_SIZE, input2);
	}
	while (!feof(input1)) { // Print each line and read the next until we hit EOF
		fprintf(output, file1_line);
		fgets(file1_line, LINE_SIZE, input1);
	}

	printf("\nFile merging complete.\n\n");
}

// Function to search our file of elements for a given element,
//  and print out the information about it
void find_element(char element[]){
	// Open our element file for reading -- return if there was an error
	FILE *elements = fopen("elements.csv", "r");

	// If the file failed to open, exit
	if (elements == NULL) {
		printf("Error loading file.");
		exit(1);   // Exit with an error
	}

	// A string to hold our 
	char file_line[LINE_SIZE];

	// Read the first line of the file, so we can
	//  start our loop properly
	fgets(file_line, LINE_SIZE, elements);

	// Keep on doing this until we've hit the end of the file...
	while (!feof(elements)) {
		if (file_line == NULL) {
			continue;
		}
		// Take the line we have read in, and break it into pieces
		char *atomic_number = strtok(file_line, delim);					// Extract the atomic number
		char *atomic_weight = strtok(NULL, delim);						// Extract the atomic weight
		char *element_name  = strtok(NULL, delim);						// Extract the element's name
		char *atomic_symbol = strtok(NULL, delim);						// Extract the atomic symbol
		char *year_discover = strtok(NULL, delim);						// Extract the year of discovery

		// If this element matches what we are searching for, print out its info
		if (strcmp(atomic_symbol, element) == 0) {
			printf("Element: %s\n", element_name);
			printf(" Symbol: %s\n", atomic_symbol);
			printf(" Atomic Number: %s\n", atomic_number);
			printf(" Atomic Weight: %s\n", atomic_weight);
			// Only print out the year of discovery if an actual year is given
			if (strcmp(year_discover, "ancient") != 0) {
				printf(" Year Discovered: %s\n", year_discover);
			}
			printf("\n");   // For formatting purposes
		}
		// Read in the next line so we can iterate through the loop again
		fgets(file_line, LINE_SIZE, elements);
	}
	// We're done here. Close the file, just for style points
	fclose(elements);
}

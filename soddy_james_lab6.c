/* James Soddy
 * CSCI 112
 * Lab 6
 * 3/26/15
 *
 * Simple program to determine whether or not
 * a barcode is valid
 */

#include <stdio.h>

// The length of our barcode is used in several functions
#define BARCODE_LENGTH 12


// function to get barcode input from user
void get_barcode(int[]);
// function to check if barcode is valid
void verify_barcode(int[]);

int main(void) {
	// integer array to hold barcode digits
	int barcode[BARCODE_LENGTH];

	// get barcode input from the user
	get_barcode(barcode);

	// See if the barcode is valid and inform the user
	verify_barcode(barcode);
	
	// return without errors
	return(0);
}

// Function to prompt user for a barcode and retrieve it from input
void get_barcode(int barcode[]) {
	// Prompt user for input
	printf("\nEnter a bar code to check. Separate digits with a space >\n");

	// Scan enough decimal digits from input to fill our barcode array
	int i;
	for (i = 0; i < BARCODE_LENGTH; i++){
		scanf("%d", &barcode[i]);
	}

	// Repeat back to the user what they entered.
	printf("\nYou entered the code: ");
	for (i = 0; i < BARCODE_LENGTH; i++){
		printf("%d ", barcode[i]);
	}
	printf("\n");
}

// function to check if an entered barcode is valid, and inform the user
void verify_barcode(int barcode[]) {
	// integers to hold our calculated values
	int odds = 0, evens = 0, sum = 0, check = 0, valid;
	// sum odd barcode positions
	int i;
	for (i = 0; i < BARCODE_LENGTH - 1; i += 2) {
		odds += barcode[i];
	}
	// multiply times 3
	odds = odds * 3;
	// Report sum to user
	printf("STEP 1: Sum of odds times 3 is %d\n", odds);
	// sum even barcode positions
	for (i = 1; i < BARCODE_LENGTH - 2; i += 2) {
		evens += barcode[i];
	}
	// Report sum to user
	printf("STEP 2: Sum of the even digits is %d\n", evens);
	// Add evens and odds
	sum = odds + evens;
	// Report sum to user
	printf("STEP 3: Total sum is %d\n", sum);
	// Calculate check digit
	check = (10 - (sum % 10)) % 10;
	// Report check digit to user
	printf("STEP 4: Calculated check digit is %d\n", check);
	// Determine if the check digit matches the calculated value
	valid = check == barcode[BARCODE_LENGTH - 1];
	// Report result to user;
	if (valid) {
		printf("STEP 5: Check digit and last digit match\nBarcode is VALID.\n");
	} else {
		printf("STEP 5: Check digit and last digit do not match\nBarcode is INVALID.\n");
	}
}




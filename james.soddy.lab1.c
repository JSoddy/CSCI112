#include <stdio.h>

#define CELSIUS_OFFSET   32
#define CELSIUS_MULTIPLE 1.8

/* James Soddy
 * CSCI 112, Lab 1
 * 1/28/15
 */


int main(void) {
	double fahrenheit;
	double celsius;

	// Prompts the user for a temp in fahrenheit
	printf("\nEnter a temperature in degrees Fahrenheit > ");
	// Reads input and saves it to floating point var fahrenheit
	scanf("%lf", &fahrenheit);
	
	// Converts the users input from celcius degrees to fahrenheit degrees
	celsius = (fahrenheit - CELSIUS_OFFSET) / CELSIUS_MULTIPLE;


	// Print the fahrenheit temperature for the user
	printf("%lf degrees Fahrenheit is equal to %lf degrees Celsius.\n\n", fahrenheit, celsius);
		
	// Promts the user for a temp in celsius
	printf("Enter a temperature in degrees Celsius > ");
	// Reads input and saves it to floating point var celsius
	scanf("%lf", &celsius);

	// Converts the user's input from fahrenheit degrees to celsius degrees
	fahrenheit = celsius * CELSIUS_MULTIPLE + CELSIUS_OFFSET;

	// Print the celsius temperature for the user
	printf("%lf degrees Celsius is equal to %lf degrees Fahrenheit.\n\n", celsius, fahrenheit);

	// Return with no errors
	return 0;
}

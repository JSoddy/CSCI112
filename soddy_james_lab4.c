/* James Soddy
 * CSCI 112
 * Lab 4
 * 3/5/15
 *
 * Simple program to display the value of trigonomentric functions evaluated
 * at a range of values
 */

#include <stdio.h>
#include <math.h>

#define PI 3.14159
#define LOOP_LIMIT 90
#define DEGREES_TO_RADIANS PI / 180

typedef enum MENU {Sine, Cosine, Tangent, QUIT} menu_t;

void evaluate(menu_t);

int main(){
	// an enum to hold the user's choice of action
	menu_t menu_choice;

	// Menu loop -- repeat until user chooses to quit
	do {
		// Prompt user for what they want to do
		printf("\nPlease choose an option: (0) Sine (1) Cosine (2) Tangent (3) QUIT\nEnter your choice > ");
		// Retrieve user choice
		scanf("%d", &menu_choice);
		// If the user wants to evaluate a trig function, do so
		switch (menu_choice) {
			case Sine:
			case Cosine:
			case Tangent:
				evaluate(menu_choice);
				break;
		// If the user wants to quit, reluctantly let them go
			case QUIT:
				printf("You chose QUIT. Thank you, come again!");
				break;
		// And if they have done anything else, let them know they've messed up
			default:
				printf("%d is not a valid choice. Please try again.\n", menu_choice);
		}
		
	} while (menu_choice != QUIT);

	// Return without errors
	return(0);
}

// Method to evaluate a selected trig function at several values
void evaluate(menu_t function) {
	// Evaluate the selected function at 15 degree intervals from 0 to our limit
	int angle;
	for (angle = 0; angle <= LOOP_LIMIT; angle += 15) {
		// Choose the correct function to evaluate
		switch (function) {
			// Evaluate sine at angle
			case Sine:
				printf("\tsin(%d) = %1.4f\n", angle, sin(angle * DEGREES_TO_RADIANS));
				break;
			// Evaluate cosine at angle
			case Cosine:
				printf("\tcos(%d) = %1.4f\n", angle, cos(angle * DEGREES_TO_RADIANS));
				break;
			// Evaluate tangent at angle
			case Tangent:
				// We shouldn't evaluate tangent at 90 degrees or 270 degrees (or their equivalent angles)
				if (angle % 90 == 0 && angle % 180 != 0) {
					printf("\ttan(%d) is UNDEFINED\n", angle);
				} else {
					printf("\ttan(%d) = %1.4f\n", angle, tan(angle * DEGREES_TO_RADIANS));
				}
				break;
		}
	}
	// We're done here. Return
}

/* James Soddy
 * CSCI 112
 * Lab 5
 * 3/19/15
 *
 * Simple program to calculate kinematic equations
 * on inputs given by users
 */

#include <stdio.h>
#include <math.h>


// List of all function declarations ( prototypes )

// Displays user menu , reads input , and validates the input
int user_menu ();

// Equation functions are pass by reference
void equation1 ( float *); // Calculate motion equation 1
void equation2 ( float *); // Calculate motion equation 2
void equation3 ( float *); // Calculate motion equation 3
void equation4 ( float *); // Calculate motion equation 4

// User input functions return a value from user
float get_position_initial ( void ); // Prompts user for x0
float get_position_final ( void ); // Prompts user for xf
float get_velocity_initial ( void ); // Prompts user for v0
float get_velocity_final ( void ); // Prompts user for vf
float get_acceleration ( void ); // Prompts user for a
float get_time ( void ); // Prompts user for t

int main ( void )
{
	// Print welcome message
	printf (" Welcome to the MOTION EQUATION CALCULATOR \n\n");

	// Variable for the user choice from menu
	int user_choice ;
	do{
		user_choice = user_menu (); // Print menu , validate choice is between 1 and 5
		// You will pass the address of this variable to your equation functions
		float result ; // Variable to hold calculated result
		// Handle menu choice selected by user
		switch ( user_choice ){
			case 1 :
				// User wants equation 1
				equation1 (&result);
				break;
			case 2 :
				// User wants equation 2
				equation2 (&result);
				break;
			case 3 :
				// User wants equation 3
				equation3 (&result);
				break;
			case 4 :
				// User wants equation 4
				equation4 (&result);
				break;
			case 5 :
				// Exit program if user selects QUIT
				printf (" Thank you for using the MOTION EQUATION CALCULATOR . Goodbye .\n");
				return 0;
		}
		// Print out the calculated result with four digits after the decimal point
		printf (" Your result is %.4f.\n\n", result );
	} while ( user_choice !=5); // Repeat until user chooses QUIT
	return 0; // Return without error
}

// Function to prompt user for which kinematic equation they would like to 
int user_menu(void) {
	int user_choice = 0;
	// Loop until we have valid input
	do {
	// Display menu
	printf(" Choose a motion equation 1-4 or choose 5 to QUIT > ");
	// Get user choice
	scanf("%d", &user_choice);

	// If we have invalid input...
	if (user_choice < 1 || user_choice > 5) {
		// Tell the user
		printf(" Invalid option. Please try again.\n\n");
	}
	} while (user_choice < 1 || user_choice > 5);
	
	// return input
	return user_choice;
}

// Calculate motion equation 1
void equation1 ( float * result) {
	// Prompt user for equation variables
	float initial_velocity	= get_velocity_initial();
	float acceleration		= get_acceleration();
	float time					= get_time();

	// Calculate result
	*result = initial_velocity + (acceleration * time);
}

// Calculate motion equation 2
void equation2 ( float * result) {
	// Prompt user for equation variables
	float initial_position	= get_position_initial();
	float initial_velocity	= get_velocity_initial();
	float time					= get_time();
	float acceleration		= get_acceleration();

	//Calculate result
	*result = initial_position + initial_velocity * time + .5 * acceleration * time * time;
}

// Calculate motion equation 3
void equation3 ( float * result) {
	// Prompt user for equation variables
	float initial_velocity	= get_velocity_initial();
	float acceleration		= get_acceleration();
	float final_position		= get_position_final();
	float initial_position	= get_position_initial();
	
	// Calculate result
	*result = sqrt(initial_velocity * initial_velocity + 2 * acceleration * (final_position - initial_position));
}

// Calculate motion equation 4
void equation4 ( float * result) {
	//Prompt user for equation variables
	float initial_position	= get_position_initial();
	float final_velocity		= get_velocity_final();
	float initial_velocity	= get_velocity_initial();
	float time					= get_time();

	// Calculate result
	*result = initial_position + .5 * (final_velocity + initial_velocity) * time;
}

 // Prompts user for x0
float get_position_initial ( void ) {
	float user_input;
	// prompt user
	printf("\t Enter initial position > ");
	// get input
	scanf("%f", &user_input);
	// return user's input
	return user_input;
}

// Prompts user for xf
float get_position_final ( void ) {
	float user_input;
	// promput user
	printf("\t Enter final position > ");
	// get input
	scanf("%f", &user_input);
	// return user's input
	return user_input;
} 

// Prompts user for v0
float get_velocity_initial ( void ) {
	float user_input;
	// promput user
	printf("\t Enter initial velocity > ");
	// get input
	scanf("%f", &user_input);
	// return user's input
	return user_input;
}

// Prompts user for vf
float get_velocity_final ( void ) {
	float user_input;
	// promput user
	printf("\t Enter final velocity > ");
	// get input
	scanf("%f", &user_input);
	// return user's input
	return user_input;
}

// Prompts user for a
float get_acceleration ( void ) {
	float user_input;
	// promput user
	printf("\t Enter acceleration > ");
	// get input
	scanf("%f", &user_input);
	// return user's input
	return user_input;
}

// Prompts user for t
float get_time ( void ) {
	float user_input;
	// promput user
	printf("\t Enter time > ");
	// get input
	scanf("%f", &user_input);
	// return user's input
	return user_input;
}



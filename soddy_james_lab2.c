
#include <stdio.h>

double get_input(void);
double get_next(double, double);
void print_result(double);

int main(void) {
	// Variables to hold values for previous terms of relation
	double first_term;
	double second_term;
	double temp;
	
	// Just print a blank line to make it prettier.
	printf("\n");

	// Get the first two terms of sequence from the user and save
	// them to the appropriate variables
	first_term  = get_input();
	second_term = get_input();

	// We have the first two terms, so we will start at two and then
	// calculate until we have the fifth term, the one we want
	int i;
	for(i = 2; i < 5; i++){
		// calculate next term in the sequence, and save it to temporary variable
		temp = get_next(first_term, second_term);
		// The x-1 term becomes the x-2 term
		first_term = second_term;
		// The new term we calculated becomes the x-1 term
		second_term = temp;
	}

	// Print out the last term that we calculated
	print_result(second_term);

	// Exit with no errors
	return(0);
}

// A function to get a relation term from the user
double get_input(void){
	// Variable to hold the user's input of our next relation term
	double relation_term;
	
	// Prompt the user for the next term and save it
	printf("Enter a value > ");
	scanf("%lf", &relation_term);

	// Return the relation term the user entered
	return(relation_term);
}

// A function to return the next term in the relation Xsubn = (Xsubn-2/2 + 3*Xsubn-1)
//  if given the two preceeding terms
double get_next(double n_minus_two_term, double n_minus_one_term){
	// calculate and return the next term in the sequence
	return ((n_minus_two_term / 2) + (3 * n_minus_one_term));
}

// A function which gives the user the calculated value of the fifth relation term
void print_result(double result){
	// Print the result for the user
	printf("The result is %0.2lf\n", result);
}

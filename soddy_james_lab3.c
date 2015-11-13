#include <stdio.h>

// prototypes
int     get_input(void);
int     is_valid(int);
void	print_pattern(int);


int main(void) {
	int pattern_size;

	//get input from user
	pattern_size = get_input();

	//print out the pattern
	print_pattern(pattern_size);
	
	//exit with no errors
	return(0);
}

// Function to get a number between 1 and 9 from the user
int get_input(void) {
	int user_input;

	// Ask user for input, and allow them to try until they have
	// entered valid input
	do {
		printf("Please enter an odd number between 1 and 9: ");
		scanf("%d", &user_input);
	} while(!is_valid(user_input));

	return user_input;
}

// Function to determine whether input is a valid integer between 1 and 9
int is_valid(int to_test) {
	// local variables
	int is_odd, larger_than_zero, smaller_than_ten;

	// is_odd is false (0) if to_test is an even number, true otherwise
	is_odd = to_test % 2;
	if (!is_odd) printf("You entered an even number.\n");
	
	// larger_than_zero is true if to_test is large enough, false otherwise
	larger_than_zero = to_test > 0;
	if (!larger_than_zero) printf("You entered a number smaller than 1.\n");

	// smaller_than_ten is true if to_test is small enough, false otherwise
	smaller_than_ten = to_test < 10;
	if (!smaller_than_ten) printf("You entered a number larger than 9.\n");

	// We will return true all conditions pass
	return is_odd && larger_than_zero && smaller_than_ten;
}

// Function to print out a diamond pattern of numbers, with dimensions
// determined by the provided integer
void print_pattern(int size) {
	// the halfway point of our diamond
	int halfway = size / 2 + 1;
	// the number of items to print on each line
	int to_print = 1;

	// loop "size" times, printing one line for each
	int i;
	for (i = 1; i <= size; i++) {
		// Print enough leading spaces to format our output
		//  this will be half of the difference between how many items
		//  we are printing, and how long our lines are
		printf("%*s", size - to_print + 1," ");
		
		// loop "to_print" times, printing our index each time
		int j;
		for (j = 1; j <= to_print; j++) {
			printf("%d ", j);
		}

		// just a newline to finish out our input
		printf("\n");

		// if we're < halfway, increment the number of items we are printing
		//  otherwise decrement it
		if (i < halfway) {
			to_print += 2;
		} else {
			to_print -= 2;
		}
	}
}

#include <stdio.h>

#define MAX_ARRAY_SIZE 50

int populate_array ( int array [] ); // Fill array with values from user
void print_array ( int array [] , int n ); // Print out the array values
void swap ( int array [] , int index1 , int index2 ); // Swap two array elements
void quicksort ( int array [] , int low , int high ); // Sorting algorithm
int partition ( int array [] , int low , int high ); // Find the partition point


int main() {
	
	// Integer array to hold numbers we will sort, and an
	//  integer to represent the number of items stored
	int array[MAX_ARRAY_SIZE];
	int n;
	
	// Get values from the user to fill the array
	n = populate_array(array);

	// Display the unsorted array
	printf("\nThe initial array contains:\n");
	print_array(array, n);

	// Sort the array
	quicksort(array, 0, n-1);

	// Display the sorted array
	printf("\nThe array is now sorted:\n");
	print_array(array, n);

	return 0; // Return with no errors
}

// Function to fill an array with integer values
int populate_array(int array[]){
	// Integer to store number of items in list
	int n = 0;
	
	// Prompt user for number of items to sort and check
	//  user input for validity
	while (n == 0){
		printf("Enter the value of n > ");
		scanf("%d", &n);
		
		if (n < 1) {
			printf("Array must contain at least one element. Please try again.\n\n");
			n = 0;
		} else if (n > 50) {
			printf("%d exceeds the maximum array size. Please try again.\n\n", n);
			n = 0;
		}
	}

	// Promput user for array values
	printf("Enter %d integers (positive, negative, or zero) >\n", n);

	// Scan n items from stdin and store them in array
	int i;
	for (i = 0; i < n; i++){
		scanf("%d", &array[i]);
	}

	// Return with the item count
	return n;
	
}


// Function to print out the values stored in an array
void print_array(int array[], int n) {

	// Iterate through the first n indices, printing out the values contained
	int i;
	for (i = 0; i < n; i++){	
		printf("%+5d\n", array[i]);
	}

}

//Function to swap the values at two array indices
void swap(int array[], int index1, int index2){

	// Just swap the two values. No sweat
	int temp;
	temp = array[index1];
	array[index1] = array[index2];
	array[index2] = temp;

}

//Function to sort an array of integers recursively
void quicksort(int array[], int low, int high){

	// integer to store the pivot point
	int pivot;

	// Divide the array into two halves and sort them recursively
	if (low < high){
		pivot = partition(array, low, high);
		quicksort(array, low, pivot - 1);
		quicksort(array, pivot + 1, high);
	}

}

//Function to divide an array of integers into those lower than and 
// those higher than a selected array element
int partition(int array[], int low, int high){

	int pivot = array[high];
	int i = low -1;
	int j;
	for (j = low; j < high; j++){
		if (array[j] <= pivot){
			i++;
			swap(array, i, j);		
		}
	}
	swap(array, i+1, high);
	return i+1;
}

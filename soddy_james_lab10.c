/*
 * James Soddy
 * CSCI 112
 * Lab 10
 *
 * A program to create a database of Magic: The Gathering cards
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 20

// The 'card' type to contain all of the relevant information about
//  a Magic: The Gathering card
typedef struct card_struct{
	char card_name[STRING_SIZE];														// Name
	char card_set[STRING_SIZE]; 														// Set
	enum {common, uncommon, rare, mythic_rare, rarity_count} 
		card_rarity; 															        // Rarity
	char card_artist[STRING_SIZE];													    // Artist
	enum {red, green, blue, black, white, colorless, color_count} 
		card_color; 															        // Color
	double card_value;														            // Value
	enum {sorcery, creature, instant, enchantment, artifact, land, planeswalker, type_count} 
		card_type; 																        // Type
	int  card_count;															        // Number of cards
	struct card_struct *next;												            // Next card
} card;

// Arrays of strings to hold the string values of our card enumerations
char* rarity_strings[]	= {"common", "uncommon", "rare", "mythic rare"};
char* color_strings[]	= {"red", "green", "blue", "black", "white", "colorless"};
char* type_strings[]	= {"sorcery", "creature", "instant", "enchantment", "artifact", "land", "planeswalker"};

// A menu choice enumeration, and an array of associated strings
enum Menu {
	enter,
	find,
	delete,
	print,
	quit,
	menu_count
};

char* menu_strings[] = {"enter a card", "find a card", "remove card from list", "print out database", "quit"};

// Function prototypes
enum Menu 	get_user_choice();				// Just gets menu input
void 		enter_card();					// Allows user to add a card to database
void        insert_card(card *, card *);	// Places a newly created card into the list
void 		get_input_line(char *);			// Removes newlines from within a string
void 		find_card(card *);				// Locates and prints data on a selected card
void 		remove_card(card *);			// Removes the chosen card information from the database
card*		card_search(card *, char *, int);// Prints all cards matching string and returns number of matches
void 		print_database(card *);			// Prints out all cards in the database
void 		print_card(card *);				// Prints out a card
card* 		add_cards();					// Set initial members of list
int			get_color();					// Get a valid card color from input
int			get_type();						// Get a valid card type from input
int			get_rarity();					// Get a valid card rarity from input

int main(){

	enum Menu user_choice = 99;
	card *card_list;

	card_list = add_cards();

	printf("Welcome to Magic: The Gathering card inventory!\n\n");
	
	// Loop to allow user to make repeated selections
	while (user_choice != quit) {
		// Display menu and get user input
		user_choice = get_user_choice();
		// Pick function based on user's choice
		switch (user_choice) {
			case enter:
				// User has chosen to enter a new card
				enter_card(card_list);
				break;
			case find:
				// User has chosen to find card data in the database
				printf("\nFind card by name:\n");
				find_card(card_list);
				break;
			case delete:
				// User has chosen to remove a card from the database
				printf("\nRemove card:\n");
				remove_card(card_list);
				break;
			case print:
				// User has chosen to print entire database
				printf("\nPrinting database:\n");
				print_database(card_list);
				break;
			case quit:
				printf("\nNow exiting. Please come again.");
				// User has chosen to quit
				break;
			default:
				// If user's entry does not align with options,
				//  politely let them know they have made a mistake
				printf("Invalid input. Please try again.\n\n");
				break;
		}
	}
	return 0; // Exit without errors
}

// Function to prompt user for what they want to do, and
//  retrieve their choice from input
enum Menu get_user_choice(){
	char choice[STRING_SIZE];
	int  selection;
	// Print out all of the user's options
	printf("\n");	// Formatting
	int i;
	for ( i = 0; i < menu_count; i++){
		printf(" Enter %d to %s.\n", i, menu_strings[i]);
	}
	// Prompt user for choice
	printf("What would you like to do? > ");
	// Retrieve user's choice as string, and convert it
	//  to an integer
	//  This allows us to filter bad input without a
	//  lot of extra lines of code
	get_input_line(choice);
	selection = atoi(choice);
	// If the selection is 0, but the string is not "0" then we have
	//  gotten bad input from the user, loop through the menu again
	if (selection == 0 && strcmp(choice, "0") != 0) {
		return -1;
	} else {
		// Otherwise, make their selection
		return selection;
	}
}

// Function to create a new card record and add it to the database
void enter_card(card *card_list){
	// Create new card
	card *new_card = (card*) malloc(sizeof(card));
	char input_line[STRING_SIZE];
	int chars_read;
	// Get Name
	printf("Enter a new card:\n");
	printf(" Please enter the card's name > ");
	get_input_line(new_card->card_name);
	// Get Set Name
	printf(" Please enter the card's set > ");
	get_input_line(new_card->card_set);
	// Get Color
	new_card->card_color = get_color();
	// Get Type
	new_card->card_type = get_type();
	// Get artist name
	printf(" Please enter the card's artist > ");
	get_input_line(new_card->card_artist);
	// Get card rarity
	new_card->card_rarity = get_rarity();
	// Get card's value
	printf(" Please enter the value of this card > ");
	fgets(input_line, STRING_SIZE, stdin);
	sscanf(input_line, "%lf", &(new_card->card_value));
	// Put the card in the list
	insert_card(card_list, new_card);
}

// Function get a line of input from stdin,
//  without the newline character
void get_input_line(char *string){
	// Get a line from stdin
	fgets(string, STRING_SIZE, stdin);
	int i = 0;
	// Overwrite every occurance of newline before terminator with terminator
	while (string[i] != '\0') {
		if (string[i] == '\n') string[i] = '\0';
		i++;
	}
}

// A function to insert a newly created card into the list
void insert_card(card *card_list, card *new_card){
	// Search through the linked list, until we find a
	//  card whose name is >= the card we are searching for
	card *insert_position = card_search(card_list, new_card->card_name, 0);
	
	// Insert the card to the list at the located spot
	new_card->next = insert_position->next;
	insert_position->next = new_card;
}

// Function to get a valid color for a new card from the user
int get_color(){	
	// String to hold a line of input
	char input_line[STRING_SIZE];
	int color = -1; // Set the color to an initial invalid option
	do {
		// prompt th user for input
		printf(" What is the card's color?\n");
		printf("Enter red, green, blue, black, white, or colorless > ");
		// Get their input string
		get_input_line(input_line);
		// Loop over the color options to see if the string matches one of them
		int i;
		for (i = 0; i < color_count; i++){
			if (strcmp(input_line, color_strings[i]) == 0)
				color = i;
		}
		// If we didn't get a match, tell the user to try again.
		if (color < 0 ) printf("\nInvalid input, please try again.\n");
	} while (color < 0);
	return color;
}

// Function to get a valid type for a new card from the user
int get_type(){
	// String to hold a line of input
	char input_line[STRING_SIZE];
	int type = -1; // Set type to an initial invalid option
	do {
		// prompt the user for input
		printf(" What type of card is it?\n");
		printf("Enter sorcery, creature, instant, enchantment, land, planeswalker or artifact > ");
		// Get their input string
		get_input_line(input_line);
		// Loop over the types and see if the input string matches one
		int i;
		for (i = 0; i < type_count; i++){
			if (strcmp(input_line, type_strings[i]) == 0)
				// If we find a match, set that as our type
				 type = i;
		}
		// If we didn't find a match, tell the user to try agian
		if (type < 0) printf("\nInvalid input, please try again.\n");
	} while (type < 0);
	return type;
}

// Function to get a valid rarity for a new card from the user
int get_rarity(){
	// String to hold our input lines
	char input_line[STRING_SIZE];
	int rarity = -1; // Initial invalid value
	do {
		// Prompt user for input
		printf(" What is the rarity of the card?\n");
		printf("Enter common, uncommon, rare, or mythic rare > ");
		// Get their input from keyboard
		get_input_line(input_line);
		// Loop over the rarities, and see if the input string matches one
		int i;
		for (i = 0; i < rarity_count; i++){
			if (strcmp(input_line, rarity_strings[i]) == 0)
				// If we find a match, that will be our value
				 rarity = i;
		}
		// If there was no match, then tell the user to try again.
		if (rarity < 0) printf("\nInvalid input, please try again.\n");
	} while (rarity < 0);
	return rarity;
}

// Function to search the database for a card. Takes a
//  pointer to the head of the list and a name to search for
//  returns the last position before either matching card or NULL
card *card_search(card *card_list, char* search_name, int match_count){	
	// Index pointers	
	card *previous = card_list;
	card *current 	= previous->next;

	// Search through the linked list, until we find null
	//  or a card whose name is >= the search_name
	while (current != NULL && ((strcmp(current->card_name, search_name) < 0) || (strcmp(current->card_name, search_name) == 0 && --match_count > 0)) ) {
		previous = current;
		current = current->next;
	}
	// Return the last card before the matching card.
	return previous;
}

void find_card(card* card_list) {
	char card_name[STRING_SIZE];
	int  match_count = 0;
	// Ask the user for the name of the card we want to match
	printf(" Enter the name of the card you want to find > ");
	get_input_line(card_name);
	// Until we have found a card that is not a match,
	//  or the end of the list, keep searching for cards
	//  which match our selection and printing them
	card *result = card_search(card_list, card_name, 1);
	while (result->next != NULL && strcmp(result->next->card_name, card_name) == 0){
		match_count++;
		printf("\nMatch number %d:\n", match_count);
		print_card(result->next);
		result = card_search(result->next, card_name, 1);
	}
	// Print out how many matches we found
	printf("\n%d total matches were found.\n", match_count);
}

// Function to remove a card entry from the database
void remove_card(card *card_list){
	char input_line[STRING_SIZE];
	char card_name[STRING_SIZE];
	int  match_count = 0;
	// Prompt user and get name of card to remove
	printf(" Enter the name of the card you want to remove > ");
	get_input_line(card_name);
	// In case the card name appears more than once, ask user which
	//  they would like to remove
	printf(" Which occurance of this card would you like to remove?\nEnter a number > ");
	fgets(input_line, STRING_SIZE, stdin);
	sscanf(input_line, "%d", &match_count);
	// Search to find the card we want to remove
	card *preceding = card_search(card_list, card_name, match_count);
	if (preceding->next != NULL && strcmp(preceding->next->card_name, card_name) == 0) {
		card *succeeding = preceding->next->next;
		free(preceding->next);
		preceding->next = succeeding;
		printf("\nThe card was removed successfully.\n");
	} else {
		printf("\nThe card was not found in the database.\n");
	}

	// Delete the selected record
}

// Function to print out the entire database
void print_database(card *card_list){
	// Pointer to our current position
	card *current_pos = card_list->next;

	// Iterate through the database, printing out each record
	//  and summing their values as we go
	while (current_pos != NULL) {
		printf("\n");
		print_card(current_pos);
		printf("\n");
		current_pos = current_pos->next;
	}
}

// Function to print out the information contained in a card
void print_card(card *this_card){
	// Print out card name
	printf("Card:\t%s\n", this_card->card_name);
	// Print out card's set
	printf("    Set:\t%s\n", this_card->card_set);
	// Print out artist for this card
	printf("    Artist:\t%s\n", this_card->card_artist);
	// Print out card's rarity
	printf("    Rarity:\t%s\n", rarity_strings[this_card->card_rarity]);
	// Print out card's color
	printf("    Color:\t%s\n", color_strings[this_card->card_color]);
	// Print out card's type
	printf("    Type:\t%s\n", type_strings[this_card->card_type]);
	// Print out card's value
	printf("    Value:\t%.2f\n", this_card->card_value);
}

// Initialize the array with new starting cards
card* add_cards(){
	// Allocate a blank sentinel node
	card *sentinel = malloc(sizeof(card));

	// Create a card
	card *new_card = malloc(sizeof(card));
	// Assign it values
	strcpy(new_card->card_name, "Black Lotus");
	strcpy(new_card->card_set, "Alpha");
	new_card->card_rarity = rare;
	strcpy(new_card->card_artist, "Christopher Rush");
	new_card->card_color = colorless;
	new_card->card_type	= artifact;
	new_card->card_value = 3051.00;
	// Insert it to the list
	insert_card(sentinel, new_card);
	
	// Rinse, repeat...
	new_card = malloc(sizeof(card));

	strcpy(new_card->card_name, "Black Lotus");
	strcpy(new_card->card_set, "Unlimited");
	new_card->card_rarity = rare;
	strcpy(new_card->card_artist, "Christopher Rush");
	new_card->card_color  = colorless;
	new_card->card_type  = artifact;
	new_card->card_value = 1574.98;

	insert_card(sentinel, new_card);
	
	new_card = malloc(sizeof(card));

	strcpy(new_card->card_name, "Imperial Seal");
	strcpy(new_card->card_set, "Portal Three Kingdoms");
	new_card->card_rarity = rare;
	strcpy(new_card->card_artist, "Li Tie");
	new_card->card_color  = black;
	new_card->card_type  = sorcery;
	new_card->card_value = 600.00;

	insert_card(sentinel, new_card);
	
	new_card = malloc(sizeof(card));

	strcpy(new_card->card_name, "Shivan Dragon");
	strcpy(new_card->card_set, "Revised");
	new_card->card_rarity = rare;
	strcpy(new_card->card_artist, "Melissa Benson");
	new_card->card_color  = red;
	new_card->card_type  = creature;
	new_card->card_value = 1.00;

	insert_card(sentinel, new_card);
	
	new_card = malloc(sizeof(card));

	strcpy(new_card->card_name, "Impending Disaster");
	strcpy(new_card->card_set, "Urza's Legacy");
	new_card->card_rarity = rare;
	strcpy(new_card->card_artist, "Pete Venters");
	new_card->card_color  = red;
	new_card->card_type  = enchantment;
	new_card->card_value = .65;

	insert_card(sentinel, new_card);
	
	new_card = malloc(sizeof(card));

	strcpy(new_card->card_name, "Sunscorch Regent");
	strcpy(new_card->card_set, "Dragons of Tarkir");
	new_card->card_rarity = rare;
	strcpy(new_card->card_artist, "Matt Stewart");
	new_card->card_color  = white;
	new_card->card_type  = creature;
	new_card->card_value = 2.00;

	insert_card(sentinel, new_card);
	
	// Return the sentinel card (The linked list)
	return sentinel;
}






#include <stdio.h>
#include <stdlib.h>

#define NAME_SIZE 25

typedef struct{
	int sid;
	char last[NAME_SIZE];
	char first[NAME_SIZE];
	float *grades;
	float gpa;
} student;

// Function prototypes
student get_student_info(int);
void print_student_records(student*, int, int);
float compute_gpa(float*, int);

int main(){
	int num_students = 0, num_grades = 0;
	// Get number of students
	while (num_students < 1) {
		// Prompt user for number of students
		printf("Enter the number of students:> ");
		// Record response
		scanf("%d", &num_students);
		if (num_students < 1) {
			printf("Please enter a positive number of students.\n");
		}
	}
	// Get number of grades to record for each student
	while (num_grades < 1) {
		// Prompt user for number of grades
		printf("Enter the number of grades to track:> ");
		// Record response
		scanf("%d", &num_grades);
		if (num_grades < 1) {
			printf("Please enter a positive number of students.\n");
		}
	}
	// Confirm to  user how many students and grades
	printf("\nThere are %d students.", num_students);
	printf("\nThere are %d grades.\n", num_grades);

	// allocate array of students
	student *students = malloc(sizeof(student) * num_students);

	// For each student, allocate array of grades, and get values from user
	int i;
	for (i = 0; i < num_students; i++) {
		students[i] = get_student_info(num_grades);
	}
	// Print out all records
	printf("\n\n"); // Just for formatting...
	print_student_records(students, num_students, num_grades);
	// Release memory
	free(students);
	// return without errors
	return 0;
}

// Function to get the information on one student from user
student get_student_info(int num_grades){
	printf("\nEnter information for student:\n");
	student new_student;
	float *grades = malloc(sizeof(float) * num_grades);
	// Prompt user for student ID
	printf("\tEnterSID:> ");
	scanf("%d", &(new_student.sid));
	// Prompt user for student name
	printf("\tEnter last name:> ");
	scanf("%s", &(new_student.last));
	printf("\tEnter first name:> ");
	scanf("%s", &(new_student.first));
	// Prompt user for student grades
	printf("\tEnter grades (separated by space):> ");
	int i;
	for (i = 0; i < num_grades; i++){
		scanf("%f", &grades[i]);
	}
	new_student.grades = grades;
	new_student.gpa = compute_gpa(grades, num_grades);
	return new_student;
}

// Function to print out all student information for user
void print_student_records(student* students, int num_students, int num_grades){
	int i;
	// For each student
	for (i = 0; i < num_students; i++){
		// Print all vital info
		printf("Student ID #%d:", students[i].sid);
		printf("\n\tName:\t%s %s", students[i].first, students[i].last);
		printf("\n\tGrades:\t");
		int j;
		for (j = 0; j < num_grades; j++){
			printf("%0.1lf ", students[i].grades[j]);
		}
		printf("\n\tGPA:\t%0.2lf\n", students[i].gpa);
	}
}

// Function to compute grade average from grades
float compute_gpa(float* grades, int num_grades){
	float total = 0.0;
	int i;
	// Sum all of the grades
	for (i = 0; i < num_grades; i++) {
		total += grades[i];
	}
	// Return sum divided by numb of grades (arithmetic mean)
	return total / num_grades;
}


/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
<Student Name>, DLSU ID# <Student ID>
*********************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/* Constants */
#define MAX_PASSENGERS		500
#define MAX_TRIPS		20
#define REGULAR_CAPACITY	13
#define WORST_CASE_CAPACITY	16
#define STRING10		11
#define STRING30		31
#define STRING50		51
#define STRING60		61
#define TOTAL_TRIPS		20

/* String typedefs */
typedef char string10[STRING10];
typedef char string30[STRING30];
typedef char string50[STRING50];
typedef char string60[STRING60];

/* Structure definitions */
struct passenger_tag {
	string10 str_trip_number;
	string30 str_name;
	string10 str_id_number;
	int n_priority;
	string60 str_drop_off_point;
	string60 str_embarkation_point;
	int n_seat_number;
};
typedef struct passenger_tag passenger_type;

struct trip_tag {
	string10 str_trip_number;
	passenger_type a_passengers[WORST_CASE_CAPACITY];
	int n_passenger_count;
	int n_capacity;
	string30 str_route;
	string10 str_departure_time;
	string60 str_embarkation_point;
};
typedef struct trip_tag trip_type;

/* Function prototypes */
void initialize_trips(trip_type a_trips[]);
void display_main_menu(void);
void display_passenger_menu(void);
void display_personnel_menu(void);
int get_user_choice(void);
void encode_passenger_info(trip_type a_trips[]);
void view_passenger_count(trip_type a_trips[]);
void view_drop_off_count(trip_type a_trips[]);
void view_passenger_info(trip_type a_trips[]);
void load_passenger(trip_type a_trips[]);
void search_passenger(trip_type a_trips[]);
void load_recent_trip_file(trip_type a_trips[]);
void save_to_file(trip_type a_trips[]);
int find_trip_index(trip_type a_trips[], string10 str_trip_number);
void sort_passengers_by_priority(passenger_type a_passengers[], int n_count);
void display_seat_chart(trip_type *p_trip);
void notify_trip_full(string10 str_trip_number);
void clear_input_buffer(void);
int validate_trip_number(string10 str_trip_number);
void get_drop_off_points(string10 str_trip_number, string60 a_drop_off_points[], int *pn_count);
int get_trip_capacity(string10 str_trip_number, int n_passenger_count);

/*
 * main - Entry point of the Arrows Express Line system
 *
 * Return: 0 on success
 */
int main(void)
{
	trip_type a_trips[TOTAL_TRIPS];
	int n_user_type;
	int n_choice;
	int n_continue;
	
	initialize_trips(a_trips);
	
	n_continue = 1;
	
	while (n_continue == 1) {
		display_main_menu();
		n_user_type = get_user_choice();
		
		if (n_user_type == 1) { /* Passenger */
			n_choice = 1;
			while (n_choice == 1) {
				display_passenger_menu();
				n_choice = get_user_choice();
				
				if (n_choice == 1)
					encode_passenger_info(a_trips);
			}
		} else if (n_user_type == 2) { /* Arrows Personnel */
			n_choice = 1;
			while (n_choice != 7) {
				display_personnel_menu();
				n_choice = get_user_choice();
				
				if (n_choice == 1) {
					view_passenger_count(a_trips);
				} else if (n_choice == 2) {
					view_drop_off_count(a_trips);
				} else if (n_choice == 3) {
					view_passenger_info(a_trips);
				} else if (n_choice == 4) {
					load_passenger(a_trips);
				} else if (n_choice == 5) {
					search_passenger(a_trips);
				} else if (n_choice == 6) {
					load_recent_trip_file(a_trips);
				}
			}
		} else if (n_user_type == 3) { /* Exit */
			save_to_file(a_trips);
			printf("Program terminated. Data saved successfully.\n");
			n_continue = 0;
		}
	}
	
	return 0;
}

/*
 * initialize_trips - Initialize all trip data with predefined schedule
 * @a_trips: array of trip structures to initialize
 *
 * Pre-condition: a_trips array has space for TOTAL_TRIPS elements
 */
void initialize_trips(trip_type a_trips[])
{
	string10 a_trip_numbers[TOTAL_TRIPS] = {
		"AE101", "AE102", "AE103", "AE104", "AE105", "AE106", "AE107", "AE108", "AE109",
		"AE150", "AE151", "AE152", "AE153", "AE154", "AE155", "AE156", "AE157", "AE158", "AE159", "AE160"
	};
	string10 a_times[TOTAL_TRIPS] = {
		"6:00 am", "7:30 am", "9:30 am", "11:00 am", "1:00 pm", "2:30 pm", "3:30 pm", "5:00 pm", "6:15 pm",
		"5:30 am", "5:45 am", "7:00 am", "7:30 am", "9:00 am", "11:00 am", "1:00 pm", "2:30 pm", "3:30 pm", "5:00 pm", "6:15 pm"
	};
	string30 a_routes[TOTAL_TRIPS] = {
		"Manila to Laguna", "Manila to Laguna", "Manila to Laguna", "Manila to Laguna", "Manila to Laguna",
		"Manila to Laguna", "Manila to Laguna", "Manila to Laguna", "Manila to Laguna",
		"Laguna to Manila", "Laguna to Manila", "Laguna to Manila", "Laguna to Manila", "Laguna to Manila",
		"Laguna to Manila", "Laguna to Manila", "Laguna to Manila", "Laguna to Manila", "Laguna to Manila", "Laguna to Manila"
	};
	string60 a_embarkation_points[TOTAL_TRIPS] = {
		"DLSU Manila Campus - South Gate Driveway", "DLSU Manila Campus - South Gate Driveway",
		"DLSU Manila Campus - South Gate Driveway", "DLSU Manila Campus - South Gate Driveway",
		"DLSU Manila Campus - South Gate Driveway", "DLSU Manila Campus - South Gate Driveway",
		"DLSU Manila Campus - South Gate Driveway", "DLSU Manila Campus - South Gate Driveway",
		"DLSU Manila Campus - South Gate Driveway",
		"DLSU Laguna Campus - MRR Building - East Canopy", "DLSU Laguna Campus - MRR Building - East Canopy",
		"DLSU Laguna Campus - MRR Building - East Canopy", "DLSU Laguna Campus - MRR Building - East Canopy",
		"DLSU Laguna Campus - MRR Building - East Canopy", "DLSU Laguna Campus - MRR Building - East Canopy",
		"DLSU Laguna Campus - MRR Building - East Canopy", "DLSU Laguna Campus - MRR Building - East Canopy",
		"DLSU Laguna Campus - MRR Building - East Canopy", "DLSU Laguna Campus - MRR Building - East Canopy",
		"DLSU Laguna Campus - MRR Building - East Canopy"
	};
	int i;
	int j;
	
	for (i = 0; i < TOTAL_TRIPS; i++) {
		strcpy(a_trips[i].str_trip_number, a_trip_numbers[i]);
		strcpy(a_trips[i].str_departure_time, a_times[i]);
		strcpy(a_trips[i].str_route, a_routes[i]);
		strcpy(a_trips[i].str_embarkation_point, a_embarkation_points[i]);
		a_trips[i].n_passenger_count = 0;
		a_trips[i].n_capacity = REGULAR_CAPACITY;
		
		for (j = 0; j < WORST_CASE_CAPACITY; j++) {
			strcpy(a_trips[i].a_passengers[j].str_trip_number, "");
			strcpy(a_trips[i].a_passengers[j].str_name, "");
			strcpy(a_trips[i].a_passengers[j].str_id_number, "");
			a_trips[i].a_passengers[j].n_priority = 0;
			strcpy(a_trips[i].a_passengers[j].str_drop_off_point, "");
			strcpy(a_trips[i].a_passengers[j].str_embarkation_point, "");
			a_trips[i].a_passengers[j].n_seat_number = 0;
		}
	}
}

/*
 * display_main_menu - Show the main menu options
 *
 * Pre-condition: none
 */
void display_main_menu(void)
{
	printf("\n==========Main Menu==========\n");
	printf("Select user type:\n");
	printf("1 - Passenger\n");
	printf("2 - Arrows Personnel\n");
	printf("3 - Exit Program (End of day)\n");
	printf("User type: ");
}

/*
 * display_passenger_menu - Show passenger menu options
 *
 * Pre-condition: none
 */
void display_passenger_menu(void)
{
	printf("\n==========Passenger Menu==========\n");
	printf("1 - Encode Passenger Information\n");
	printf("2 - Back to Main Menu\n");
	printf("Select an option: ");
}

/*
 * display_personnel_menu - Show personnel menu options
 *
 * Pre-condition: none
 */
void display_personnel_menu(void)
{
	printf("\n==========Arrows Personnel Menu==========\n");
	printf("1 - View Passenger Count\n");
	printf("2 - View Drop-off Count\n");
	printf("3 - View Passenger Information\n");
	printf("4 - Load Passenger(Single passenger)\n");
	printf("5 - Search Passenger\n");
	printf("6 - Load Recent Trip File for Viewing\n");
	printf("7 - Back to Main Menu\n");
	printf("Select an option: ");
}

/*
 * get_user_choice - Get user input choice and validate it
 *
 * Return: integer choice from user input
 * Pre-condition: none
 */
int get_user_choice(void)
{
	int n_choice;
	
	if (scanf("%d", &n_choice) != 1) {
		n_choice = -1; /* Invalid input */
	}
	clear_input_buffer();
	
	return n_choice;
}

/*
 * encode_passenger_info - Handle passenger information input and trip assignment
 * @a_trips: array of all trips
 *
 * Pre-condition: a_trips is properly initialized
 */
void encode_passenger_info(trip_type a_trips[])
{
	string10 str_trip_number;
	string30 str_name;
	string10 str_id_number;
	int n_priority;
	string60 str_drop_off_point;
	string60 a_drop_off_points[4];
	int n_drop_off_count;
	int n_trip_index;
	int n_choice;
	int n_valid_trip;
	int i;
	
	printf("\nEnter Trip Number: ");
	if (scanf("%s", str_trip_number) != 1) {
		printf("Error reading trip number.\n");
		clear_input_buffer();
		return;
	}
	clear_input_buffer();
	
	n_valid_trip = validate_trip_number(str_trip_number);
	
	if (n_valid_trip == 1) {
		n_trip_index = find_trip_index(a_trips, str_trip_number);
		
		if (n_trip_index != -1) {
			/* Check if trip is full */
			if (a_trips[n_trip_index].n_passenger_count >= a_trips[n_trip_index].n_capacity) {
				notify_trip_full(str_trip_number);
			} else {
				printf("Enter Passenger Name: ");
				if (fgets(str_name, sizeof(str_name), stdin) == NULL) {
					printf("Error reading passenger name.\n");
					return;
				}
				/* Remove newline if present */
				if (strlen(str_name) > 0 && str_name[strlen(str_name) - 1] == '\n')
					str_name[strlen(str_name) - 1] = '\0';
				
				/* Check if name is empty */
				if (strlen(str_name) == 0) {
					printf("Error: Empty passenger name.\n");
					return;
				}
				
				printf("Enter ID Number: ");
				if (scanf("%s", str_id_number) != 1) {
					printf("Error reading ID number.\n");
					clear_input_buffer();
					return;
				}
				clear_input_buffer();
				
				printf("Enter Priority Number (1-6): ");
				if (scanf("%d", &n_priority) != 1) {
					printf("Error reading priority number.\n");
					clear_input_buffer();
					return;
				}
				clear_input_buffer();
				
				/* Validate priority range */
				if (n_priority < 1 || n_priority > 6) {
					printf("Invalid priority number. Must be between 1-6.\n");
					return;
				}
				
				/* Get available drop-off points for this trip */
				get_drop_off_points(str_trip_number, a_drop_off_points, &n_drop_off_count);
				
				if (n_drop_off_count > 0) {
					printf("Available Drop-off Points:\n");
					for (i = 0; i < n_drop_off_count; i++)
						printf("%d - %s\n", i + 1, a_drop_off_points[i]);
					
					printf("Select Drop-off Point: ");
					n_choice = get_user_choice();
					
					if (n_choice >= 1 && n_choice <= n_drop_off_count) {
						strcpy(str_drop_off_point, a_drop_off_points[n_choice - 1]);
						
						/* Validate array bounds before adding passenger */
						if (a_trips[n_trip_index].n_passenger_count < WORST_CASE_CAPACITY) {
							/* Add passenger to trip */
							strcpy(a_trips[n_trip_index].a_passengers[a_trips[n_trip_index].n_passenger_count].str_trip_number, str_trip_number);
							strcpy(a_trips[n_trip_index].a_passengers[a_trips[n_trip_index].n_passenger_count].str_name, str_name);
							strcpy(a_trips[n_trip_index].a_passengers[a_trips[n_trip_index].n_passenger_count].str_id_number, str_id_number);
							a_trips[n_trip_index].a_passengers[a_trips[n_trip_index].n_passenger_count].n_priority = n_priority;
							strcpy(a_trips[n_trip_index].a_passengers[a_trips[n_trip_index].n_passenger_count].str_drop_off_point, str_drop_off_point);
							strcpy(a_trips[n_trip_index].a_passengers[a_trips[n_trip_index].n_passenger_count].str_embarkation_point, a_trips[n_trip_index].str_embarkation_point);
							
							a_trips[n_trip_index].n_passenger_count++;
							
							/* Sort passengers by priority and assign seats */
							sort_passengers_by_priority(a_trips[n_trip_index].a_passengers, a_trips[n_trip_index].n_passenger_count);
							
							/* Update capacity if needed */
							a_trips[n_trip_index].n_capacity = get_trip_capacity(str_trip_number, a_trips[n_trip_index].n_passenger_count);
							
							printf("Passenger successfully added to trip %s\n", str_trip_number);
						} else {
							printf("Error: Trip capacity exceeded.\n");
						}
					} else {
						printf("Invalid drop-off point selection.\n");
					}
				} else {
					printf("No drop-off points available for this trip.\n");
				}
			}
		} else {
			printf("Trip not found.\n");
		}
	} else {
		printf("Invalid trip number.\n");
	}
}

/*
 * view_passenger_count - Display the seating chart for a specific trip
 * @a_trips: array of all trips
 *
 * Pre-condition: a_trips is properly initialized
 */
void view_passenger_count(trip_type a_trips[])
{
	string10 str_trip_number;
	int n_trip_index;
	int n_valid_trip;
	
	printf("\nEnter Trip Number: ");
	scanf("%s", str_trip_number);
	clear_input_buffer();
	
	n_valid_trip = validate_trip_number(str_trip_number);
	
	if (n_valid_trip == 1) {
		n_trip_index = find_trip_index(a_trips, str_trip_number);
		
		if (n_trip_index != -1) {
			printf("\nTrip %s - Passenger Count: %d/%d\n", 
			       str_trip_number, a_trips[n_trip_index].n_passenger_count, a_trips[n_trip_index].n_capacity);
			display_seat_chart(&a_trips[n_trip_index]);
		} else {
			printf("Trip not found.\n");
		}
	} else {
		printf("Invalid trip number.\n");
	}
}

/*
 * view_drop_off_count - Display passenger count per drop-off point for a trip
 * @a_trips: array of all trips
 *
 * Pre-condition: a_trips is properly initialized
 */
void view_drop_off_count(trip_type a_trips[])
{
	string10 str_trip_number;
	int n_trip_index;
	int n_valid_trip;
	string60 a_unique_drop_offs[10];
	int a_drop_off_counts[10];
	int n_unique_count;
	int i;
	int j;
	int n_found;
	
	printf("\nEnter Trip Number: ");
	scanf("%s", str_trip_number);
	clear_input_buffer();
	
	n_valid_trip = validate_trip_number(str_trip_number);
	
	if (n_valid_trip == 1) {
		n_trip_index = find_trip_index(a_trips, str_trip_number);
		
		if (n_trip_index != -1) {
			n_unique_count = 0;
			
			/* Count passengers per drop-off point */
			for (i = 0; i < a_trips[n_trip_index].n_passenger_count; i++) {
				n_found = 0;
				
				for (j = 0; j < n_unique_count; j++) {
					if (strcmp(a_trips[n_trip_index].a_passengers[i].str_drop_off_point, a_unique_drop_offs[j]) == 0) {
						a_drop_off_counts[j]++;
						n_found = 1;
					}
				}
				
				if (n_found == 0) {
					strcpy(a_unique_drop_offs[n_unique_count], a_trips[n_trip_index].a_passengers[i].str_drop_off_point);
					a_drop_off_counts[n_unique_count] = 1;
					n_unique_count++;
				}
			}
			
			printf("\nDrop-off Count for Trip %s:\n", str_trip_number);
			for (i = 0; i < n_unique_count; i++)
				printf("%s: %d passengers\n", a_unique_drop_offs[i], a_drop_off_counts[i]);
		} else {
			printf("Trip not found.\n");
		}
	} else {
		printf("Invalid trip number.\n");
	}
}

/*
 * view_passenger_info - Display passenger information sorted by priority
 * @a_trips: array of all trips
 *
 * Pre-condition: a_trips is properly initialized
 */
void view_passenger_info(trip_type a_trips[])
{
	string10 str_trip_number;
	int n_trip_index;
	int n_valid_trip;
	int i;
	
	printf("\nEnter Trip Number: ");
	scanf("%s", str_trip_number);
	clear_input_buffer();
	
	n_valid_trip = validate_trip_number(str_trip_number);
	
	if (n_valid_trip == 1) {
		n_trip_index = find_trip_index(a_trips, str_trip_number);
		
		if (n_trip_index != -1) {
			printf("\nPassenger Information for Trip %s (sorted by priority):\n", str_trip_number);
			printf("%-30s %-15s %-10s\n", "Name", "ID Number", "Priority");
			printf("--------------------------------------------------------\n");
			
			for (i = 0; i < a_trips[n_trip_index].n_passenger_count; i++) {
				printf("%-30s %-15s %-10d\n", 
				       a_trips[n_trip_index].a_passengers[i].str_name,
				       a_trips[n_trip_index].a_passengers[i].str_id_number,
				       a_trips[n_trip_index].a_passengers[i].n_priority);
			}
		} else {
			printf("Trip not found.\n");
		}
	} else {
		printf("Invalid trip number.\n");
	}
}

/*
 * load_passenger - Load passenger data from a text file
 * @a_trips: array of all trips
 *
 * Pre-condition: a_trips is properly initialized
 */
void load_passenger(trip_type a_trips[])
{
	string30 str_file_name;
	FILE *p_file;
	string10 str_trip_number;
	string60 str_embarkation_point;
	string30 str_name;
	string10 str_id_number;
	int n_priority;
	string60 str_drop_off_point;
	int n_trip_index;
	int n_success;
	
	printf("\nEnter filename to load: ");
	scanf("%s", str_file_name);
	clear_input_buffer();
	
	p_file = fopen(str_file_name, "r");
	
	if (p_file != NULL) {
		n_success = 1;
		
		while (n_success == 1 && !feof(p_file)) {
			if (fscanf(p_file, "%s", str_trip_number) == 1) {
				fgets(str_embarkation_point, sizeof(str_embarkation_point), p_file); /* Read newline */
				fgets(str_embarkation_point, sizeof(str_embarkation_point), p_file);
				str_embarkation_point[strlen(str_embarkation_point) - 1] = '\0';
				
				fgets(str_name, sizeof(str_name), p_file);
				str_name[strlen(str_name) - 1] = '\0';
				
				fscanf(p_file, "%s", str_id_number);
				fscanf(p_file, "%d", &n_priority);
				
				fgets(str_drop_off_point, sizeof(str_drop_off_point), p_file); /* Read newline */
				fgets(str_drop_off_point, sizeof(str_drop_off_point), p_file);
				str_drop_off_point[strlen(str_drop_off_point) - 1] = '\0';
				
				n_trip_index = find_trip_index(a_trips, str_trip_number);
				
				if (n_trip_index != -1 && a_trips[n_trip_index].n_passenger_count < WORST_CASE_CAPACITY) {
					strcpy(a_trips[n_trip_index].a_passengers[a_trips[n_trip_index].n_passenger_count].str_trip_number, str_trip_number);
					strcpy(a_trips[n_trip_index].a_passengers[a_trips[n_trip_index].n_passenger_count].str_name, str_name);
					strcpy(a_trips[n_trip_index].a_passengers[a_trips[n_trip_index].n_passenger_count].str_id_number, str_id_number);
					a_trips[n_trip_index].a_passengers[a_trips[n_trip_index].n_passenger_count].n_priority = n_priority;
					strcpy(a_trips[n_trip_index].a_passengers[a_trips[n_trip_index].n_passenger_count].str_drop_off_point, str_drop_off_point);
					strcpy(a_trips[n_trip_index].a_passengers[a_trips[n_trip_index].n_passenger_count].str_embarkation_point, str_embarkation_point);
					
					a_trips[n_trip_index].n_passenger_count++;
					
					sort_passengers_by_priority(a_trips[n_trip_index].a_passengers, a_trips[n_trip_index].n_passenger_count);
					a_trips[n_trip_index].n_capacity = get_trip_capacity(str_trip_number, a_trips[n_trip_index].n_passenger_count);
				}
			} else {
				n_success = 0;
			}
		}
		
		fclose(p_file);
		printf("Passenger data loaded successfully.\n");
	} else {
		printf("Error: Could not open file %s\n", str_file_name);
	}
}

/*
 * search_passenger - Search for passengers by last name
 * @a_trips: array of all trips
 *
 * Pre-condition: a_trips is properly initialized
 */
void search_passenger(trip_type a_trips[])
{
	string30 str_last_name;
	int i;
	int j;
	int n_found;
	
	printf("\nEnter last name to search: ");
	scanf("%s", str_last_name);
	clear_input_buffer();
	
	printf("\nSearch Results:\n");
	printf("%-30s %-15s %-10s %-10s\n", "Name", "ID Number", "Priority", "Trip");
	printf("--------------------------------------------------------------------\n");
	
	n_found = 0;
	
	for (i = 0; i < TOTAL_TRIPS; i++) {
		for (j = 0; j < a_trips[i].n_passenger_count; j++) {
			if (strstr(a_trips[i].a_passengers[j].str_name, str_last_name) != NULL) {
				printf("%-30s %-15s %-10d %-10s\n",
				       a_trips[i].a_passengers[j].str_name,
				       a_trips[i].a_passengers[j].str_id_number,
				       a_trips[i].a_passengers[j].n_priority,
				       a_trips[i].a_passengers[j].str_trip_number);
				n_found = 1;
			}
		}
	}
	
	if (n_found == 0)
		printf("No passengers found with last name: %s\n", str_last_name);
}

/*
 * load_recent_trip_file - Load and display trip file information
 * @a_trips: array of all trips
 *
 * Pre-condition: a_trips is properly initialized
 */
void load_recent_trip_file(trip_type a_trips[])
{
	string30 str_file_name;
	FILE *p_file;
	char str_line[100];
	
	printf("\nEnter trip filename to view: ");
	scanf("%s", str_file_name);
	clear_input_buffer();
	
	p_file = fopen(str_file_name, "r");
	
	if (p_file != NULL) {
		printf("\nTrip File Contents:\n");
		printf("-------------------\n");
		
		while (fgets(str_line, sizeof(str_line), p_file))
			printf("%s", str_line);
		
		fclose(p_file);
	} else {
		printf("Error: Could not open file %s\n", str_file_name);
	}
}

/*
 * save_to_file - Save current trip data to a text file
 * @a_trips: array of all trips
 *
 * Pre-condition: a_trips is properly initialized
 */
void save_to_file(trip_type a_trips[])
{
	string60 str_file_name;
	FILE *p_file;
	time_t t_current_time;
	struct tm *p_time_info;
	int i;
	int j;
	
	time(&t_current_time);
	p_time_info = localtime(&t_current_time);
	
	sprintf(str_file_name, "Trip-%02d-%02d-%04d.txt", 
		p_time_info->tm_mday, p_time_info->tm_mon + 1, p_time_info->tm_year + 1900);
	
	p_file = fopen(str_file_name, "w");
	
	if (p_file != NULL) {
		for (i = 0; i < TOTAL_TRIPS; i++) {
			for (j = 0; j < a_trips[i].n_passenger_count; j++) {
				fprintf(p_file, "%s\n", a_trips[i].a_passengers[j].str_trip_number);
				fprintf(p_file, "%s\n", a_trips[i].a_passengers[j].str_embarkation_point);
				fprintf(p_file, "%s\n", a_trips[i].a_passengers[j].str_name);
				fprintf(p_file, "%s\n", a_trips[i].a_passengers[j].str_id_number);
				fprintf(p_file, "%d\n", a_trips[i].a_passengers[j].n_priority);
				fprintf(p_file, "%s\n", a_trips[i].a_passengers[j].str_drop_off_point);
				fprintf(p_file, "\n");
			}
		}
		
		fclose(p_file);
		printf("Data saved to %s\n", str_file_name);
	} else {
		printf("Error: Could not save to file.\n");
	}
}

/*
 * find_trip_index - Find the array index for a given trip number
 * @a_trips: array of all trips
 * @str_trip_number: trip number to search for
 *
 * Return: index of trip or -1 if not found
 * Pre-condition: a_trips is properly initialized
 */
int find_trip_index(trip_type a_trips[], string10 str_trip_number)
{
	int i;
	int n_index;
	
	n_index = -1;
	
	for (i = 0; i < TOTAL_TRIPS; i++) {
		if (strcmp(a_trips[i].str_trip_number, str_trip_number) == 0)
			n_index = i;
	}
	
	return n_index;
}

/*
 * sort_passengers_by_priority - Sort passengers array by priority (lowest number = highest priority)
 * @a_passengers: array of passengers to sort
 * @n_count: number of passengers in array
 *
 * Pre-condition: a_passengers array contains valid passenger data
 */
void sort_passengers_by_priority(passenger_type a_passengers[], int n_count)
{
	int i;
	int j;
	int n_min_index;
	passenger_type temp_passenger;
	
	/* Safety check */
	if (n_count <= 0 || n_count > WORST_CASE_CAPACITY)
		return;
	
	for (i = 0; i < n_count - 1; i++) {
		n_min_index = i;
		
		for (j = i + 1; j < n_count; j++) {
			if (a_passengers[j].n_priority < a_passengers[n_min_index].n_priority)
				n_min_index = j;
		}
		
		if (n_min_index != i) {
			temp_passenger = a_passengers[i];
			a_passengers[i] = a_passengers[n_min_index];
			a_passengers[n_min_index] = temp_passenger;
		}
	}
	
	/* Assign seat numbers */
	for (i = 0; i < n_count; i++)
		a_passengers[i].n_seat_number = i + 1;
}

/*
 * display_seat_chart - Display the seating arrangement for a trip
 * @p_trip: pointer to trip structure
 *
 * Pre-condition: p_trip points to valid trip data
 */
void display_seat_chart(trip_type *p_trip)
{
	char a_seat_chart[WORST_CASE_CAPACITY];
	int i;
	
	/* Initialize all seats as available */
	for (i = 0; i < WORST_CASE_CAPACITY; i++)
		a_seat_chart[i] = 'O';
	
	/* Mark occupied seats */
	for (i = 0; i < p_trip->n_passenger_count; i++) {
		if (p_trip->a_passengers[i].n_seat_number > 0 && 
		    p_trip->a_passengers[i].n_seat_number <= WORST_CASE_CAPACITY)
			a_seat_chart[p_trip->a_passengers[i].n_seat_number - 1] = 'X';
	}
	
	printf("\nSeating Chart:\n");
	
	if (p_trip->n_capacity == REGULAR_CAPACITY) {
		printf("Regular Seating (13 passengers):\n");
		printf("   %c   %c   %c\n", a_seat_chart[0], a_seat_chart[1], a_seat_chart[2]);
		printf("   %c   %c   %c\n", a_seat_chart[3], a_seat_chart[4], a_seat_chart[5]);
		printf("   %c   %c   %c\n", a_seat_chart[6], a_seat_chart[7], a_seat_chart[8]);
		printf("  %c   %c   %c\n", a_seat_chart[9], a_seat_chart[10], a_seat_chart[11]);
		printf("      %c\n", a_seat_chart[12]);
		printf("    Driver\n");
	} else {
		printf("Worst Case Seating (16 passengers):\n");
		printf("  %c   %c   %c   %c\n", a_seat_chart[0], a_seat_chart[1], a_seat_chart[2], a_seat_chart[3]);
		printf("  %c   %c   %c   %c\n", a_seat_chart[4], a_seat_chart[5], a_seat_chart[6], a_seat_chart[7]);
		printf("  %c   %c   %c   %c\n", a_seat_chart[8], a_seat_chart[9], a_seat_chart[10], a_seat_chart[11]);
		printf("     %c   %c   %c\n", a_seat_chart[12], a_seat_chart[13], a_seat_chart[14]);
		printf("        %c\n", a_seat_chart[15]);
		printf("      Driver\n");
	}
	
	printf("\nLegend: X = Occupied, O = Available\n");
}

/*
 * notify_trip_full - Display notification when trip is at capacity
 * @str_trip_number: trip number that is full
 *
 * Pre-condition: str_trip_number contains valid trip number
 */
void notify_trip_full(string10 str_trip_number)
{
	printf("\nTrip %s is currently full.\n", str_trip_number);
	printf("Please select another trip or wait for the next available trip.\n");
}

/*
 * clear_input_buffer - Clear the input buffer of extra characters
 *
 * Pre-condition: none
 */
void clear_input_buffer(void)
{
	int n_char;
	
	while ((n_char = getchar()) != '\n' && n_char != EOF) {
		/* Clear buffer */
	}
}

/*
 * validate_trip_number - Check if trip number is valid
 * @str_trip_number: trip number to validate
 *
 * Return: 1 if valid, 0 if invalid
 * Pre-condition: str_trip_number contains string to validate
 */
int validate_trip_number(string10 str_trip_number)
{
	string10 a_valid_trips[TOTAL_TRIPS] = {
		"AE101", "AE102", "AE103", "AE104", "AE105", "AE106", "AE107", "AE108", "AE109",
		"AE150", "AE151", "AE152", "AE153", "AE154", "AE155", "AE156", "AE157", "AE158", "AE159", "AE160"
	};
	int i;
	int n_valid;
	
	n_valid = 0;
	
	for (i = 0; i < TOTAL_TRIPS; i++) {
		if (strcmp(str_trip_number, a_valid_trips[i]) == 0)
			n_valid = 1;
	}
	
	return n_valid;
}

/*
 * get_drop_off_points - Get available drop-off points for a specific trip
 * @str_trip_number: trip number
 * @a_drop_off_points: array to store drop-off points
 * @pn_count: pointer to store number of drop-off points
 *
 * Pre-condition: a_drop_off_points has space for at least 4 elements
 */
void get_drop_off_points(string10 str_trip_number, string60 a_drop_off_points[], int *pn_count)
{
	int n_trip_num;
	
	/* Initialize count to 0 */
	*pn_count = 0;
	
	/* Extract trip number */
	if (str_trip_number[2] == '1' && str_trip_number[3] >= '0' && str_trip_number[3] <= '9') {
		n_trip_num = (str_trip_number[3] - '0');
		
		if (n_trip_num % 2 == 1) { /* Odd numbers - Via Mamplasan Exit */
			strcpy(a_drop_off_points[0], "Mamplasan Toll Exit");
			strcpy(a_drop_off_points[1], "Phase 5, San Jose Village");
			strcpy(a_drop_off_points[2], "MRR Building - East Canopy");
			*pn_count = 3;
		} else { /* Even numbers - Via ETON Exit */
			strcpy(a_drop_off_points[0], "Laguna Blvd. Guard House");
			strcpy(a_drop_off_points[1], "MRR Building - East Canopy");
			*pn_count = 2;
		}
	} else if (str_trip_number[2] == '5') {
		n_trip_num = (str_trip_number[3] - '0');
		
		if (n_trip_num % 2 == 1) { /* Odd numbers - Via Estrada */
			strcpy(a_drop_off_points[0], "Petron Station Gil Puyat Ave");
			strcpy(a_drop_off_points[1], "Gate 4: Gokongwei Gate");
			strcpy(a_drop_off_points[2], "Gate 2: North Gate (HSSH)");
			strcpy(a_drop_off_points[3], "Gate 1: South Gate (LS Building)");
			*pn_count = 4;
		} else { /* Even numbers - Via Buendia/LRT */
			strcpy(a_drop_off_points[0], "CSB along Taft Avenue");
			strcpy(a_drop_off_points[1], "Gate 4: Gokongwei Gate");
			strcpy(a_drop_off_points[2], "Gate 2: North Gate (HSSH)");
			strcpy(a_drop_off_points[3], "Gate 1: South Gate (LS Building)");
			*pn_count = 4;
		}
	}
}

/*
 * get_trip_capacity - Determine appropriate capacity based on passenger count
 * @str_trip_number: trip number
 * @n_passenger_count: current number of passengers
 *
 * Return: appropriate capacity (13 or 16)
 * Pre-condition: str_trip_number is valid trip number
 */
int get_trip_capacity(string10 str_trip_number, int n_passenger_count)
{
	int n_capacity;
	
	if (n_passenger_count > REGULAR_CAPACITY)
		n_capacity = WORST_CASE_CAPACITY;
	else
		n_capacity = REGULAR_CAPACITY;
	
	return n_capacity;
}
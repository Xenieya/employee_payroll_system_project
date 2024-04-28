// Group 7


#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_USERS 50             // maximum number of users
#define MAX_USER_LENGTH 50		 // maximum number of characters for usernames
#define MAX_PASSWORD_LENGTH 20   // maximum number of characters for password
#define MAX_CHAR 100			 // maximum number of characters for other char types


// Define user structure
typedef struct{
	
	char passwords[MAX_PASSWORD_LENGTH]; // password of the user
	char usernames[MAX_USER_LENGTH];     // username of the employee or admin   
	char names[MAX_CHAR];				 // name of the employee
	char positions[MAX_CHAR];		     // position of the employee
	int contacts;						 // contact number of the employee
	
	
	float work_hours;      				 // total number of hours worked.
	float hourly_rates;    				 // pay per hour
	float overtime_rates;  				 // overtime pay per hour
	float overtime_hours;  				 // total number of overtime in hours worked.
	float bonus;                         // amount of bonus of the employee 
	
	
	int userTypes;         				 // 0 for employee, 1 for admin
	
} User;

// Global arrays to store usernames, passwords, and user types
User users[MAX_USERS];
int numUsers = 0;

// Predefined admin credentials
char adminUsername[] = "admin";
char adminPassword[] = "admin123";

void main_menu();                      // main-menu of employee payroll system


User* find_user(const char *username); // Function to check if the username exists
void clean();                          // clears console
void wait_clean();                     // clears console after user press any key
void change_password(User* user);      // changes user password
void change_username(User* user);      // changes user username
void change_name(User* user);          // changes user name
void change_contact(User* user);       // changes user contact
void login_system();				   // user login menu

// employee menu
void user(User* user);                 // employee main-menu
void user_payslip(User* user);		   // displays salary payslip
void user_info_update(User* user);	   // displays & allows change of employee information

// admin menu
void admin(User* user);				   // admin main-menu
void admin_manage();				   // menu to manage employees
void add_employee();				   // register's new employee

// salary computations
float calculate_basic_salary(User* user);   // calculates basic salary
float calculate_overtime(User* user);       // calculates overtime pay
float calculate_gross_pay(User* user);      // calculates gross pay


void main() {
	
    // Copy predefined admin account to array structure of "User"
    strcpy(users[0].usernames, adminUsername);
    strcpy(users[0].passwords, adminPassword);
    users[0].userTypes = 1; // set to admin
    numUsers++;
    
    main_menu();
}


// Function for the main menu
void main_menu(){
	
	char choice;
	
	do{
		//design
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*           Welcome to Employee Payroll System           *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*    [A] Login                                           *\n");
    	printf("*    [X] Exit                                            *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf(" %c", &choice);
    	choice = toupper(choice);
    	getchar(); // Consume the newline character left in the input buffer
    
    	switch (choice){
    	
    		case 'A':
    			login_system();
    			break;
    		case 'X':
    			break;
    		default:
    			clean();
    			printf("\n\t\t\tnot in option\n");
    			wait_clean();
    			
		}
	}while(choice != 'X');
	
}

// Function to check if the username exists
User* find_user(const char *username){
    int i;
    
    for (i = 0; i < numUsers; i++) {
    	
    	if (strcmp(users[i].usernames, username) == 0) { // Checks if user exist
            	return &users[i]; // Return index of the user if found
        } 
    }
    return NULL; // Return NULL if username not found
}



void login_system(){
	
	int attempt = 4;       // number of attempts for username input
	int attempt_pass = 4;  // number of attempts for password input
	
	char username[MAX_USER_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    
    clean();
    
    do{ 
    	

    	printf("\n\t\tLogin\n\n");
    	printf("\t\tUsername: ");
    	scanf("%s", username);
    

    	User* index = find_user(username); // checks if username exists
    	if (index != NULL) { 
    		
    		attempt = 0; // stops the loop if username exists
    		
    		do{
    			
    			printf("\t\tPassword: ");
    			scanf("%s", password);
    			
    			int i;
    		
				if (strcmp(index->passwords, password) == 0) { // checks inputted password
				
					attempt_pass = 0; // stops the loop if password is corrects
					
					if (index->userTypes == 1){ //checks if its an admin
					
						clean();

    					printf("\n\n\tAdmin login successful. Welcome, %s!\n\n", username);
    					wait_clean();
        				admin(index);
					} else { // if not, prompts to employee menu
					
						clean();
					
						printf("\n\n\tEmployee login successful. Welcome, %s!\n\n", username);
    					wait_clean();
        				user(index);	
					}
				} else {
				
					clean();
					attempt_pass--;
					
					if(attempt_pass == 0){
						
						clean();
					} else {
						
						printf("\n\n\tWrong password! Please try again. [%d]\n\n", attempt_pass);
					}
					
				}
    			
			}while(attempt_pass != 0);
			
    		
        
    	} else {
    		
    		clean();
    		attempt--;
    		
    		if(attempt == 0){
    			
    			clean();
			} else {
				
				printf("\n\n\tUser does not exist. Please try again. [%d]\n\n", attempt);
			}
			
		} 
    	
	}while(attempt != 0);
    
    
}


// Function for the user menu
void user(User* user){
	
	char choice;
	
	do{
		//design
		printf("\n\n\n\t\t*** Welcome: %s ***\n\n", user->usernames);                 //need I rework ung design 
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*                      Employee Menu                     *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*    [A] View Payslip                                    *\n");
    	printf("*    [B] Update personal info                            *\n");
    	printf("*    [X] Logout                                          *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf(" %c", &choice);
    	choice = toupper(choice);
    	getchar(); // Consume the newline character left in the input buffer
    
    	switch (choice){
    	
    		case 'A':
    			user_payslip(user);
    			break;
    		case 'B':
    			user_info_update(user);
    			break;
    		case 'C':
    			printf("\nN/a\n");
    			break;
    		case 'X':
    			clean();
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 'X');
	
}

void user_payslip(User* user){
	
	char choice;
	
	float basic_salary = calculate_basic_salary(user);
	float overtime = calculate_overtime(user);
	float user_gross_pay = calculate_gross_pay(user);
	
	clean();
	
	do{
		//design & display payslip
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*                      Salary Payslip                    *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("* Personal Information:                                  *\n");
    	printf("*                                                        *\n");
    	printf("* Employee Name: %s\n", user->names);
    	printf("* Position: %s\n", user->positions);
    	printf("* Contact: %d\n", user->contacts);
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("* Regular Hours Worked: %.0f\n", user->work_hours);
    	printf("* Hourly Rate: %.2f\n", user->hourly_rates);
    	printf("* Overtime Hours Worked: %.0f\n", user->overtime_hours);
    	printf("* Overtime Rate: %.2f\n", user->overtime_rates);
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("* Earnings:                                              *\n");
    	printf("*                                                        *\n");
    	printf("* Basic Salary: %.2f\n", basic_salary);
    	printf("* Overtime: %.2f\n", overtime);
    	printf("* Bonus: %.2f\n", user->bonus);
    	printf("* Total Earnings: %.2f\n", user_gross_pay);
    	printf("*                                                        *\n");
    	printf("*                                                        *\n");
    	printf("* Deductions:                                            *\n");
    	printf("*                                                        *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	//printf("*    [A] Withdraw Salary                                 *\n");
    	printf("*    [X] Back                                            *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf(" %c", &choice);
    	choice = toupper(choice);
    	getchar(); // Consume the newline character left in the input buffer
    
    	switch (choice){
    	
    		case 'A':
    			printf("\nN/a\n");
    			break;
    		case 'X':
    			wait_clean();
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 'X');
	
}

void user_info_update(User* user){
	
	char choice;
	
	clean();
	
	do{
		//design
		// need I rework ung design magmula dito
		printf("\n\n\n\tUser Information\n");
    	printf("________________________________________\n\n");
    	printf("\tUsername: %s\n", user->usernames);
    	printf("\tName: %s\n", user->names);
    	printf("\tPosition: %s\n", user->positions);
    	printf("\tContact: %d\n", user->contacts);
    	printf("________________________________________\n");
    	// hanggang dito
    	
    	
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*               Update Personal Information              *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*    [A] Username                                        *\n");
    	printf("*    [B] Full Name                                       *\n");
    	printf("*    [C] Contact                                         *\n");
    	printf("*    [D] Change Password                                 *\n");
    	printf("*    [X] Back                                            *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf(" %c", &choice);
    	choice = toupper(choice);
    	getchar(); // Consume the newline character left in the input buffer
    
    	switch (choice){
    	
    		case 'A':
    			change_username(user);
    			break;
    		case 'B':
    			change_name(user);
    			break;
    		case 'C':
    			change_contact(user);
    			break;
    		case 'D':
    			change_password(user);
    			break;
    		case 'X':
    			clean();
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 'X');
	
}


// Function for the admin menu
void admin(User* user){
	
	char choice;
	
	do{
		//design
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*                      Admin Menu                        *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*    [A] Manage Employees                                *\n");
    	printf("*    [B] Change Password                                 *\n");
    	printf("*    [X] Logout                                          *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf(" %c", &choice);
    	choice = toupper(choice);
    	getchar(); // Consume the newline character left in the input buffer
    
    	switch (choice){
    	
    		case 'A':
    			admin_manage();
    			break;
    		case 'B':
    			change_password(user);
    			break;
    		case 'X':
    			clean();
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 'X');
	
}

void admin_manage(){
	
	char choice;
	int i;
	
	clean();
	
	do{
		//design
		printf("\n**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*                   Manage Employees                     *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	
    	// Check if there are any users (employees) registered
    	if (numUsers == 0) {
    	
        	printf("\n\nNo employees registered.\n");
        	
    	} else {
    		
        	printf("\n\nEmployee List:\n");
        	printf("------------------------------------------------------------------------------------------------------------------\n");
        	printf("ID\t Name\t\t\t Position\t\t Basic Salary\t\t Overtime\t\t Total Earnings\n");
        	printf("------------------------------------------------------------------------------------------------------------------\n");

        	// Loop through each user and display their details
        	for (i = 1; i < numUsers; i++) {
        		
            	// Calculate basic salary, overtime, and gross pay
            	float basic_salary = calculate_basic_salary(&users[i]);
            	float overtime = calculate_overtime(&users[i]);
            	float gross_pay = calculate_gross_pay(&users[i]);

            	// Print employee details along with computed values
            	printf("[%d]\t| %s\t\t| %s\t\t| %.2f\t\t| %.2f\t\t| %.2f\n", i, users[i].names, users[i].positions, basic_salary, overtime, gross_pay);
            	
        	}
        	printf("------------------------------------------------------------------------------------------------------------------\n\n\n");
    	}
    	
    	printf("**********************************************************\n");
    	printf("*                                                        *\n");
    	printf("*    [A] Edit salary                                     *\n");
    	printf("*    [B] Delete employee                                 *\n");
    	printf("*    [C] Add employee                                    *\n");
    	printf("*    [X] Back                                            *\n");
    	printf("*                                                        *\n");
    	printf("**********************************************************\n");
    	printf("\tEnter: ");
    	scanf(" %c", &choice);
    	choice = toupper(choice);
    	getchar(); // Consume the newline character left in the input buffer
    
    	switch (choice){
    	
    		case 'A':
    			printf("\nN/a\n");
    			break;
    		case 'B':
    			printf("\nN/a\n");
    			break;
    		case 'C':
    			add_employee();
    			break;
    		case 'X':
    			clean();
    			break;
    		default:
    			printf("\n\t\t\tnot in option\n");
    			break;
		}
	}while(choice != 'X');
	
}

// register's new employee "ONLY ADMIN CAN REGISTER"
void add_employee(){
	
	clean();
	
	if (numUsers >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

	// need I-rework design
    printf("\n\t\tRegister New Employee\n\n");
    
    printf("\tUsername: ");
    scanf("%s", users[numUsers].usernames);
    
    printf("\tPassword: ");
    scanf("%s", users[numUsers].passwords);
    getchar(); // Consume the newline character left in the input buffer
    
    printf("\tName: ");
    scanf("%[^\n]s", users[numUsers].names);    // Use %[^\n] to read the entire line including spaces
    
    printf("\tPosition: "); 
    scanf("%s", users[numUsers].positions);
    
    printf("\tContact: "); 
    scanf("%d", &users[numUsers].contacts);
    
    printf("\n\n\t\tEmployee Salary Computation\n\n");
    
	printf("\tSet Basic Salary Rate Per Hour: "); 
    scanf("%f", &users[numUsers].hourly_rates);
    
    printf("\tSet Overtime Rate Per Hour: "); 
    scanf("%f", &users[numUsers].overtime_rates);
    
    printf("\tTotal number of hours worked (in a month): "); 
    scanf("%f", &users[numUsers].work_hours);
    
    printf("\tTotal number of overtime hours worked (in a month): "); 
    scanf("%f", &users[numUsers].overtime_hours);
    
    printf("\tTotal Bonuses (in a month): "); 
    scanf("%f", &users[numUsers].bonus);
    
    users[numUsers].userTypes = 0; // automatically set to employee

    printf("\tRegistration successful.\n");

    numUsers++;
    
    wait_clean();
    
}

// basic salary computation
float calculate_basic_salary(User* user){
	
	float basic_salary = user->work_hours * user->hourly_rates;
	
	return basic_salary;
}

float calculate_overtime(User* user){
	
	float overtime = user->overtime_hours * user->overtime_rates;
	
	return overtime;
}

// gross pay computation
float calculate_gross_pay(User* user){
	
	float salary = calculate_basic_salary(user);
	float overtime = calculate_overtime(user);
	
	float gross_pay = salary + overtime + user->bonus;
	//float gross_pay = (user->work_hours * user->hourly_rates) + (user->overtime_hours * user->overtime_rates);
	
	return gross_pay;
	
}

//clears console
void clean(){

	system("cls"); // Clear console on Windows
}

//clears console after user press any key
void wait_clean(){
	
	printf("\n\n\tpress any key to continue...");
	_getch(); // Wait for keypress
	system("cls"); // Clear console on Windows
}

// change password
void change_password(User* user){
	
	clean();
	
	char currentPassword[MAX_PASSWORD_LENGTH];
	
    printf("\n\tEnter current password: ");
    scanf("%s", currentPassword);
    
    if (strcmp(currentPassword, user->passwords) == 0) {
    	
        printf("\n\tEnter new password: ");
        scanf("%s", user->passwords);
            
        printf("\n\tPassword updated successfully.\n");
        wait_clean();
            
    } else {
    	
        printf("\n\tIncorrect password. Password not updated.\n");
        wait_clean();
    }
    
}

void change_username(User* user){
	
	clean();
	
	//getchar(); // Consume the newline character left in the input buffer
	printf("\nEnter new username: ");
    scanf(" %s", user->usernames); 
    printf("\nUsername updated successfully.\n");
    
    wait_clean();
}

void change_name(User* user){
	
	clean();
	
	
	printf("\nEnter new name: ");
    scanf(" %[^\n]", user->names); // Use %[^\n] to read the entire line including spaces
    getchar(); // Consume the newline character left in the input buffer
    printf("\nName updated successfully.\n");
    
    wait_clean();
}

void change_contact(User* user){
	
	clean();
	
	//getchar(); // Consume the newline character left in the input buffer
	printf("\nEnter new contact: ");
    scanf("%d", &user->contacts); 
    printf("\nContact updated successfully.\n");
    
    wait_clean();
}




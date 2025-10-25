#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Function declarations
void display_clear();
int is_duplicate_id(char id[]);
void candidate_r();
void view_candidate_list();
void total_candidate_count();


int main()
{
    int num;
    int exitProgram = 0; // Declared missing variable

    // Main menu loop
    while (exitProgram == 0)
    {
        printf("\033[1;32m======== Choose Your Option ==========\n");

        printf("\033[1;32m| 1. Voter Registration              |\n");
        printf("\033[1;32m| 2. Candidate Registration          |\n");
        printf("\033[1;32m| 3. Voting                          |\n");
        printf("\033[1;32m| 4. Result Display                  |\n");
        printf("\033[1;32m| 5. Exit                            |\n");
        printf("\033[1;32m======================================\n");

        printf("\033[1;33m\nEnter Choose Number:");
        // Check if scanf fails
        if (scanf("%d", &num) != 1)
        {
            printf("\033[1;31mInvalid input. Please enter a number.\n\n");
            // Clear input buffer to prevent infinite loop on non-integer input
            while (getchar() != '\n')
                ;
            continue;
        }

        display_clear();

        switch (num)
        {

        case 1:

            printf("Voter Registration not implemented yet (Option 1)\n\n");

            break;

        case 2:
        { 
            int choice;
            // Corrected flag: 0 to continue, 1 to exit
            int exitcandidatemenu = 0;

            while (exitcandidatemenu == 0)
            { // Loop while exitcandidatemenu is 0
                printf("\033[1;32m==============Candidate Menu================\n");
                printf("01.Add Candidate\n02.View candidate Details\n03.Exit to Main Menu\n");
                printf("=========================================\n");
                printf("\n\nEnter your choice:");

                if (scanf("%d", &choice) != 1)
                {
                    printf("\033[1;31mInvalid input. Please enter a number.\n\n");
                    while (getchar() != '\n')
                        ;
                    continue;
                }

                display_clear();

                switch (choice)
                {

                case 1:
                    candidate_r();
                    break;

                case 2:
                    view_candidate_list();
                    break;

                case 3:
                    printf("\033[1;33mReturning to Main Menu...\n\n");
                    exitcandidatemenu = 1; // exit sub-menu
                    break;

                default:
                    printf("\033[1;31mInvalid choice. Please try again!\n\n");
                    break;
                }
            }
        }
        break;

        case 3:
            printf("Voting not implemented yet (Option 3)\n\n");
            break;

        case 4:
            printf("Result Display not implemented yet (Option 4)\n\n");
            break;

        case 5:
            total_candidate_count(); // Display total registered candidates
            printf("\033[1;36mThank you for using the system!\n");
            exitProgram = 1; // exit main menu
            break;

        default:
            printf("\033[1;31mInvalid choice.\n\n");
            break;
        }
    } // End of main menu while loop

    return 0;
}


//--------------------------------
// Candidate registration function
//--------------------------------


void candidate_r()
{
    // Standard size for strings
    char name[100], district[15], id[13];
    char party;
    int age;

    printf("\033[1;32m======== CANDIDATE REGISTRATION ==========\n");

    // Get ID
    printf("\033[1;32mEnter Your ID Number : ");
    scanf("%12s", id);

    printf("Enter Your Full Name: ");
    getchar(); // Clear input buffer
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // remove newline

    printf("\033[1;32mEnter Your Age : ");
    scanf("%d", &age);

    // Get party (A/B/C)
    do {
        printf("\033[1;32mEnter party (A/B/C): \033[0m");
        scanf(" %c", &party);
        if (party != 'A' && party != 'B' && party != 'C') {
            printf("\033[1;31mInvalid party! Must be A, B, or C.\n\033[0m");
        }
    } while (party != 'A' && party != 'B' && party != 'C');

    // District check
    printf("\033[1;32mEnter district: \033[0m");
    scanf("%14s", district);

    if (strcmp(district, "Matara") != 0) {
        printf("\033[1;31mError: Only 'Matara' district is allowed for registration!\n\033[0m");
        return;
    }

    // Filter ID (keep digits only)
    char filter_id[13];
    int t = 0;
    for (int i = 0; id[i] != '\0' && t < 12; i++) {
        if (isdigit(id[i])) {
            filter_id[t++] = id[i];
        }
    }
    filter_id[t] = '\0';

    // Check ID and Age
    int length = strlen(filter_id);

    if (length == 12) {
        if (age >= 18) {
            int a = is_duplicate_id(filter_id);

            if (a == 0) {
                // AUTO CANDIDATE NUMBER GENERATE
                int candidate_number = 0;
                FILE *countFile = fopen("candidate.txt", "r");
                if (countFile != NULL) {
                    char temp[300];
                    while (fgets(temp, sizeof(temp), countFile) != NULL) {
                        if (strstr(temp, "candidateNo:") != NULL)
                            candidate_number++;
                    }
                    fclose(countFile);
                }
                candidate_number++;

                // SAVE CANDIDATE DATA
                FILE *candidatedata = fopen("candidate.txt", "a");
                if (candidatedata == NULL) {
                    printf("\033[;31mError opening candidate.txt file!\n");
                    return;
                }

                fprintf(candidatedata,
                        "candidateNo: %d: id: %s name: %s age: %d party: %c District: %s\n",
                        candidate_number, filter_id, name, age, party, district);
                fclose(candidatedata);

                //  SUCCESS MESSAGE
                display_clear();
                printf("\033[1;32m============================================\n");
                printf("Registration Successful!\n");
                printf("Your Candidate Number is: %d\n", candidate_number);
                printf("============================================\n\033[0m\n");

                //  PAUSE BEFORE RETURNING TO MENU
                printf("Press Enter to return to the menu...");
                getchar(); // clear buffer
                getchar(); // wait for Enter
            } else {
                printf("\033[1;31mAlready registered with ID number..!\n\n");
                printf("Press Enter to return to the menu...");
                getchar(); getchar();
            }
        } else {
            printf("\n\033[1;31mYou Are Under 18 Years Old..!\n");
            printf("Press Enter to return to the menu...");
            getchar(); getchar();
        }
    } else {
        printf("\033[1;31mInvalid ID Number..! It must contain 12 digits.\n\n");
        printf("Press Enter to return to the menu...");
        getchar(); getchar();
    }
}

//-------------------
// Duplicate ID check (Corrected)
//-------------------

int is_duplicate_id(char id[]) {
    FILE *file = fopen("candidate.txt", "r");
    if (!file) return 0;  //file doesn't exit -no duplicate
    
    char line[300];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, id)) {//if ID found in line
            fclose(file);
            return 1; //duplicate exists
        }
    }
    fclose(file);
    return 0;
}



//-------------------
// display_clear function
//-------------------
void display_clear()
{

#ifdef _WIN32
    system("cls");
#elif __linux__ // Corrected macro name for Linux
    system("clear");
#else
  // Fallback for other systems
    printf("\n\n");
#endif
}

void view_candidate_list()
{
    FILE *file;
    char line[300];

    file = fopen("candidate.txt", "r");
    if (file == NULL)
    {
        printf("\033[1;31mNo candidate records found!\n");
        return;
    }

    // Arrays to store candidates by party
    char partyA[100][300], partyB[100][300], partyC[100][300];
    int countA = 0, countB = 0, countC = 0;

    // Read each line
    while (fgets(line, sizeof(line), file))
    {
        if (strlen(line) <= 2)
            continue; // skip empty lines

        // Identify party from line
        if (strstr(line, "party: A") != NULL || strstr(line, "Party: A") != NULL)
        {
            strcpy(partyA[countA++], line);
        }
        else if (strstr(line, "party: B") != NULL || strstr(line, "Party: B") != NULL)
        {
            strcpy(partyB[countB++], line);
        }
        else if (strstr(line, "party: C") != NULL || strstr(line, "Party: C") != NULL)
        {
            strcpy(partyC[countC++], line);
        }
    }
    fclose(file);

    printf("\033[1;32m======== CANDIDATE LIST ==========\n\n");

    // Print Party A candidates
    printf("\033[1;33m---- Party A Candidates ----\n");
    if (countA == 0)
        printf("No candidates for Party A\n");
    for (int i = 0; i < countA; i++)
        printf("%s", partyA[i]);

    // Print Party B candidates
    printf("\n\033[1;34m---- Party B Candidates ----\n");
    if (countB == 0)
        printf("No candidates for Party B\n");
    for (int i = 0; i < countB; i++)
        printf("%s", partyB[i]);

    // Print Party C candidates
    printf("\n\033[1;35m---- Party C Candidates ----\n");
    if (countC == 0)
        printf("No candidates for Party C\n");
    for (int i = 0; i < countC; i++)
        printf("%s", partyC[i]);

    printf("\033[1;33m\n==================================\n");
}



void total_candidate_count()
{
    FILE *file;
    char line[200];
    int count = 0;

    file = fopen("candidate.txt", "r");
    if (file == NULL)
    {
        // If file doesn't exist, count is 0
        printf("\033[1;32mTotal Registered Candidates: 0\n\n");
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Check for the unique start of a candidate record to count accurately
        if (strstr(line, "candidateNo:") != NULL)
        {
            count++;
        }
    }

    fclose(file);

    printf("\033[1;32mTotal Registered Candidates: %d\n\n", count);
}
    
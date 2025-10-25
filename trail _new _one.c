#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Function declarations
void display_clear();
int duplicate(char id_to_check[]);
void candidate_r();
void view_candidate_list();
void total_candidate_count();
// Corrected declaration to use char array for party name
void view_party_candidates(char party_name[]);

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
        { // Use braces for local variables in switch case
            int choise;
            // Corrected flag: 0 to continue, 1 to exit
            int exitcandidatemenu = 0;

            while (exitcandidatemenu == 0)
            { // Loop while exitcandidatemenu is 0
                printf("\033[1;32m==============Candidate Menu================\n");
                printf("01.Add Candidate\n02.View candidate Details\n03.Exit to Main Menu\n");
                printf("=========================================\n");
                printf("\n\nEnter your choise:");

                if (scanf("%d", &choise) != 1)
                {
                    printf("\033[1;31mInvalid input. Please enter a number.\n\n");
                    while (getchar() != '\n')
                        ;
                    continue;
                }

                display_clear();

                switch (choise)
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
    char name[100];
    char id[13]; // ID up to 12 digits + null terminator
    int age;
    char party[10];
    char district[15];

    printf("\033[1;32m======== CANDIDATE REGISTATION ==========\n");

    printf("\033[1;32mEnter Your id Number : ");
    scanf("%12s", id); // Use %12s to prevent buffer overflow, removed &

    // Note: scanf("%s") will stop reading at the first whitespace.
    // For names with spaces, use fgets or a more complex scanf pattern.
  
    printf("Enter Your full Name: ");
    getchar(); // clear leftover newline from previous scanf
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // remove newline

    printf("\033[1;32mEnter Your Age : ");
    scanf("%d", &age);


do {
    printf("\033[1;32mEnter Your Party (A/B/C): ");
    scanf(" %c", &party[0]);
    party[1] = '\0'; // convert char to string

    if (party[0] != 'A' && party[0] !='B' && party[0] != 'C')
    {
        printf("\033[1;31mInvalid party! Must be A, B, or C.\n");
    }
} while (party[0] != 'A' && party[0] != 'B' && party[0] != 'C');

   
    do
{
    printf("\033[1;32mEnter Your District: ");
    scanf("%14s", district);

    if (strcmp(district, "Matara") != 0)
        printf("\033[1;31mInvalid district! Only Matara is allowed.\n");
} while (strcmp(district, "Matara") != 0);


    display_clear();


    //-----------------------------------------
    // filter ID - keep only digits
    //----------------------------------------

    char filter_id[13]; // Corrected size
    int t = 0;

    for (int i = 0; id[i] != '\0' && t < 12; i++)
    {
        if (isdigit(id[i]))
        {
            filter_id[t++] = id[i];
        }
    }
    filter_id[t] = '\0';

    //-------------------------------
    // validate ID and Age
    //-------------------------------

    int length = strlen(filter_id); // Check id length

    if (length == 12)
    { // 12-digit ID check

        if (age >= 18)
        { // age check

            int a = 0;
            a = duplicate(filter_id);

            if (a == 0)
            {
                //----------------------------
                // AUTO CANDIDATE NUMBER GENARATE
                //-------------------------------

                int candidate_number = 0;

                // Count how many candidates already in the file
                FILE *countFile = fopen("candidate.txt", "r");
                if (countFile != NULL)
                {
                    char temp[300];
                    while (fgets(temp, sizeof(temp), countFile) != NULL)
                    {
                        // Check for non-empty or properly formatted line (simplified check)
                        if (strstr(temp, "candidateNo:") != NULL)
                            candidate_number++; // count each candidate line
                    }
                    fclose(countFile);
                }
                candidate_number++; // assign next number

                //---------------------------
                // SAVE CANDIDATE DATA
                //----------------------------

                FILE *candidatedata;
                // Open for append
                candidatedata = fopen("candidate.txt", "a");
                if (candidatedata == NULL)
                {
                    printf("\033[;31mError opening candidate.txt file!\n");
                    return;
                }

                // FIX: Corrected fprintf format string syntax
                fprintf(candidatedata, "candidateNo: %d: id: %s name: %s age: %d party: %s District: %s\n", candidate_number, filter_id, name, age, party, district);
                fclose(candidatedata);

                printf("\033[1;33mYour Register is Successful....\n\n");
                printf("\033[1;36mYour Candidate Number is: %d\n\n", candidate_number);
            }
            else if (a == 1)
            {

                printf("\033[1;31mAlready registered with ID number..!\n\n");
            }
        }
        else
        {
            printf("\n\033[1;31mYou Are Under 18 Years Old..!");
        }
    }
    else
    {
        display_clear();
        printf("\033[1;31mInvalid ID Number..!It must contain 12 digits. \n\n");
    }
}

//-------------------
// Duplicate ID check (Corrected)
//-------------------

int duplicate(char id_to_check[])
{
    FILE *file;
    char line[300]; // Buffer to read a full line
    char d_id[20];
    int found = 0;

    file = fopen("candidate.txt", "r");
    if (file == NULL)
    {
        // File doesn't exist, so no duplicates.
        return 0;
    }

    // Read data from the file, line by line
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Look for the "id: " prefix in the line
        char *id_start = strstr(line, "id: ");
        if (id_start != NULL)
        {
            // Move pointer past "id: " (4 characters: 'i', 'd', ':', ' ')
            id_start += 4;

            // Attempt to read the ID number (assumed to be the next word)
            // Use sscanf to extract the next word (the ID)
            if (sscanf(id_start, "%s", d_id) == 1)
            {
                if (strcmp(id_to_check, d_id) == 0)
                {
                    found = 1;
                    break;
                }
            }
        }
    }

    // Close the file
    fclose(file);

    // Return 1 if found, 0 if not found
    return found;
}

//-------------------
// display_clear function
//-------------------
void display_clear()
{ // for clear display

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
    while (fgets(line, sizeof(line), file) != NULL)
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


void view_party_candidates(char party_name[])
{ // reads and count each party of
    FILE *file;
    char line[200];
    int count = 0;

    // Create a search string for the party, ensuring we don't accidentally match a party name
    // that is a substring of another party name (e.g., "AB" in "ABC")
    // A simple approach is to search for the party name followed by " District:" (based on the file format)
    char search_string[30];
    // Check buffer size before using snprintf
    if (sizeof(search_string) > (strlen(party_name) + 11))
    {
        sprintf(search_string, "party: %s District:", party_name);
    }
    else
    {
        // Handle case where party_name is too long for the search_string buffer
        return;
    }

    file = fopen("candidate.txt", "r");
    if (file == NULL)
    {
        printf("\033[1;31mNo candidate records found!\n");
        return;
    }

    printf("\033[1;32m\n======== Candidates of Party %s ==========\n", party_name);

    while (fgets(line, sizeof(line), file) != NULL)
    {

        // Use the precise search string to find records for this party
        if (strstr(line, search_string) != NULL)
        {
            printf("%s", line);
            count++;
        }
    }

    printf("\n\033[1;33m------------------------------------------\n");
    printf("\033[1;33mTotal Candidates in Party %s: %d\n", party_name, count);
    printf("\033[1;33m------------------------------------------\n");

    fclose(file);
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
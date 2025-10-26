#include <stdio.h>
#include <string.h>

int main(void) {
    int vote[1000];
    int count[1000];
    int size = 0;
    char fname[50];
    char lname[50];
    int age, candidateNumber;
    FILE *file;
    FILE *file2;
    int max = 0;
    int num;

    /* open vote numbers file */
    file = fopen("numbers.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening numbers.txt\n");
        return 1;
    }

    /* initialize counts */
    memset(count, 0, sizeof(count));

    int i;
    while (fscanf(file, "%d", &num) == 1) {
        /* look for existing candidate number */
        for (i = 0; i < size; i++) {
            if (vote[i] == num) {
                count[i]++;
                break;
            }
        }
        
        if (i == size) {
            if (size >= (int)(sizeof(vote) / sizeof(vote[0]))) {
                fprintf(stderr, "Too many distinct candidate numbers (max %d)\n", (int)(sizeof(vote) / sizeof(vote[0])));
                break;
            }
            vote[size] = num;
            count[size] = 1;
            size++;
        }
    }

    fclose(file);

    if (size == 0) {
        printf("No votes found in numbers.txt\n");
        return 0;
    }


    max = count[0];
    int value = vote[0];
    for (i = 1; i < size; i++) {
        if (count[i] > max) {
            max = count[i];
            value = vote[i];
        }
    }


    file2 = fopen("candidate.txt", "r");
    if (file2 == NULL) {
        fprintf(stderr, "Error opening candidate.txt\n");
        return 1;
    }

    int found = 0;
    while (fscanf(file2, "%49s %49s %d %d", fname, lname, &age, &candidateNumber) == 4) {
        if (candidateNumber == value) {
            
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Winner candidate name: %s %s\n", fname, lname);
        printf("Winner Votes: %d\n", max);
        
    }

    for (i = 0; i < size; i++) {
        printf("Candidate number %d Number of votes won %d.\n", vote[i], count[i]);
    }

    fclose(file2);

    return 0;
}
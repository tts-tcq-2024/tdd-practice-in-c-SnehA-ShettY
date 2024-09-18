#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 1000

// Function to replace newline or delimiter with commas
void ReplaceWithCommas(char* input, const char* delimiter, char* result) {
    int i = 0;
    while (*input) {
        if (*input == '\n' || strchr(delimiter, *input)) {
            result[i++] = ',';
        } else {
            result[i++] = *input;
        }
        input++;
    }
    result[i] = '\0';
}

// Function to find and process the delimiter
void FindDelimiter(const char* input, char* delimiter, char* numbersStr) {
    strcpy(delimiter, ","); // Default delimiter
    if (strncmp(input, "//", 2) == 0) {
        const char* delimiterPos = strchr(input, '\n');
        if (delimiterPos) {
            strncpy(delimiter, input + 2, delimiterPos - input - 2);
            delimiter[delimiterPos - input - 2] = '\0';
            strcpy(numbersStr, delimiterPos + 1);
        }
    } else {
        strcpy(numbersStr, input);
    }
    char temp[MAX_STRING_LENGTH];
    ReplaceWithCommas(numbersStr, delimiter, temp);
    strcpy(numbersStr, temp);
}

// Function to find negatives in the input
void FindNegatives(const char* updatedinput) {
    char* token;
    char inputCopy[MAX_STRING_LENGTH];
    strcpy(inputCopy, updatedinput);
    token = strtok(inputCopy, ",");

    while (token != NULL) {
        int number = atoi(token);
        if (number < 0) {
            printf("Error: Negatives not allowed\n");
            exit(1);
        }
        token = strtok(NULL, ",");
    }
}

// Function to calculate the sum
int FindSum(const char* updatedinput) {
    int sum = 0;
    char* token;
    char inputCopy[MAX_STRING_LENGTH];
    strcpy(inputCopy, updatedinput);

    token = strtok(inputCopy, ",");
    while (token != NULL) {
        int number = atoi(token);
        if (number <= 1000) {
            sum += number;
        }
        token = strtok(NULL, ",");
    }
    return sum;
}

// Main add function
int add(const char* input) {
    if (strlen(input) == 0) {
        return 0;
    }

    char updatedinput[MAX_STRING_LENGTH];
    char delimiter[MAX_STRING_LENGTH];
    FindDelimiter(input, delimiter, updatedinput);

    FindNegatives(updatedinput);

    return FindSum(updatedinput);
}

int main() {
    // Test cases
    printf("Sum: %d\n", add("1\n2,3"));
    printf("Sum: %d\n", add("//;\n1;2"));
    return 0;
}

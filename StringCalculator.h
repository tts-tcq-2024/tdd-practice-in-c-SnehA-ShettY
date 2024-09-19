#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 1000

// Helper function to check if a character is a delimiter or newline
int IsDelimiter(char c, const char* delimiter) {
    return (c == '\n' || strchr(delimiter, c) != NULL);
}

// Function to replace newline or delimiter with commas
void ReplaceWithCommas(const char* input, const char* delimiter, char* result) {
    while (*input) {
        *result++ = IsDelimiter(*input, delimiter) ? ',' : *input;
        input++;
    }
    *result = '\0';
}

// Function to set the default delimiter
void SetDefaultDelimiter(char* delimiter) {
    strcpy(delimiter, ",");
}

// Function to extract custom delimiter if present
int ExtractCustomDelimiter(const char* input, char* delimiter, char* numbersStr) {
    if (strncmp(input, "//", 2) == 0) {
        const char* delimiterPos = strchr(input, '\n');
        if (delimiterPos) {
            strncpy(delimiter, input + 2, delimiterPos - input - 2);
            delimiter[delimiterPos - input - 2] = '\0';
            strcpy(numbersStr, delimiterPos + 1);
            return 1; // Custom delimiter found
        }
    }
    return 0; // No custom delimiter
}

// Function to find and process the delimiter
void FindDelimiter(const char* input, char* delimiter, char* numbersStr) {
    SetDefaultDelimiter(delimiter);
    if (!ExtractCustomDelimiter(input, delimiter, numbersStr)) {
        strcpy(numbersStr, input);
    }
    ReplaceWithCommas(numbersStr, delimiter, numbersStr);
}

// Function to find negatives in the input
void CheckForNegatives(const char* updatedinput) {
    char* token;
    char inputCopy[MAX_STRING_LENGTH];
    strcpy(inputCopy, updatedinput);
    token = strtok(inputCopy, ",");

    while (token != NULL) {
        if (atoi(token) < 0) {
            printf("Error: Negatives not allowed\n");
            exit(1);
        }
        token = strtok(NULL, ",");
    }
}

// Function to calculate the sum
int CalculateSum(const char* updatedinput) {
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
    if (*input == '\0') {
        return 0;
    }

    char updatedinput[MAX_STRING_LENGTH];
    char delimiter[MAX_STRING_LENGTH];

    FindDelimiter(input, delimiter, updatedinput);
    CheckForNegatives(updatedinput);

    return CalculateSum(updatedinput);
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 1000

// Utility function to check if a character is a delimiter or newline
int IsDelimiterOrNewline(char c, const char* delimiter) {
    return (c == '\n' || strchr(delimiter, c) != NULL);
}

// Function to replace newline or delimiter with commas
void ReplaceWithCommas(const char* input, const char* delimiter, char* result) {
    while (*input) {
        *result++ = IsDelimiterOrNewline(*input, delimiter) ? ',' : *input;
        input++;
    }
    *result = '\0';
}

// Helper function to extract custom delimiter
void ExtractCustomDelimiter(const char* input, char* delimiter, char* numbersStr) {
    const char* delimiterPos = strchr(input, '\n');
    strncpy(delimiter, input + 2, delimiterPos - input - 2);
    delimiter[delimiterPos - input - 2] = '\0';
    strcpy(numbersStr, delimiterPos + 1);
}

// Function to find and process the delimiter
void FindDelimiter(const char* input, char* delimiter, char* numbersStr) {
    strcpy(delimiter, ","); // Default delimiter
    if (input[0] == '/' && input[1] == '/') {
        ExtractCustomDelimiter(input, delimiter, numbersStr);
    } else {
        strcpy(numbersStr, input);
    }
    ReplaceWithCommas(numbersStr, delimiter, numbersStr);
}

// Function to check for negatives and calculate the sum
int CheckNegativesAndSum(const char* updatedinput, int* sum) {
    char inputCopy[MAX_STRING_LENGTH];
    char* token;
    strcpy(inputCopy, updatedinput);

    token = strtok(inputCopy, ",");
    while (token != NULL) {
        int number = atoi(token);
        if (number < 0) {
            printf("Error: Negatives not allowed\n");
            return 1; // Return 1 for error due to negatives
        }
        if (number <= 1000) {
            *sum += number;
        }
        token = strtok(NULL, ",");
    }
    return 0; // No error
}

// Main add function
int add(const char* input) {
    if (strlen(input) == 0) {
        return 0;
    }

    char updatedinput[MAX_STRING_LENGTH];
    char delimiter[MAX_STRING_LENGTH];
    int sum = 0;

    FindDelimiter(input, delimiter, updatedinput);

    if (CheckNegativesAndSum(updatedinput, &sum) != 0) {
        exit(1); // Exit if negatives are found
    }

    return sum;
}

int main() {
    // Test cases
    printf("Sum: %d\n", add("1\n2,3"));
    printf("Sum: %d\n", add("//;\n1;2"));
    return 0;
}

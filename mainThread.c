//Caroline Conrad OS Final pt 2
//DOCUMENTATION:
//The purpose of the program is to use pthreads to read input from multiple files,
//process the data, and sort it from least to greatest, and then write it to an output.
//In this program, I created a function work() to open and read a file, and to scan the numbers
//in the file if there are any and then print it in ascending order using qsort(). I also created
//5 threads for this program, that each process a file concurrently. The pthread_join is used to
//wait for the completion of each thread.
//
//Some challenges I faced when creating this program was understanding the C language in general and
//having to try to write code in the language. However, taking the example from class and seeing the
//supplemental pictures & videos on the assignment helped me visualize what I am actually trying to create.
//Not only that, but I could not figure out how to make the .txt files have a local location, even though
//I believe that I put them in the same location as the mainThread.c. So I just copied the absolute
//path reference and that seemed to allow the program to work.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NUMBERS 100

// Sorting the numbers from least to greatest
int sortInt(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void* work(void *num) {
    char *filename = (char *)num; // Cast the argument to char*

    FILE *file, *outputFile;
    int numbers[MAX_NUMBERS];
    int number, count = 0;

    // Open the file for reading
    file = fopen(filename, "r");

    // Check if the file is successfully opened
    if (file == NULL) {
        perror("Error opening file");
        exit(1); // Exit the program with an error code
    }

    // Read numbers from the file and store them in an array
    while (fscanf(file, "%d", &number) == 1) {
        numbers[count++] = number;
    }

    // Close the input file
    fclose(file);

    // Sort the array of numbers
    qsort(numbers, count, sizeof(int), sortInt);

    // Open the output file for writing
    char outputFilename[20];
    snprintf(outputFilename, sizeof(outputFilename), "output_%s", filename);
    outputFile = fopen(outputFilename, "w");

    // Check if the output file is successfully opened
    if (outputFile == NULL) {
        perror("Error opening output file");
        exit(1); // Exit the program with an error code
    }

    // Write sorted numbers to the output file
    for (int i = 0; i < count; ++i) {
        fprintf(outputFile, "%d\n", numbers[i]);
    }

    // Close the output file
    fclose(outputFile);

    pthread_exit(NULL); // Notify that the thread has finished
}


int main() {
        char i1[] = "input1.txt";
        char i2[] = "input2.txt";
        char i3[] = "input3.txt";
        char i4[] = "input4.txt";
        char i5[] = "input5.txt";

        pthread_t t1, t2, t3, t4, t5;

        // Calling the function and creating the threads
        pthread_create(&t1, NULL, work, i1);
        pthread_create(&t2, NULL, work, i2);
        pthread_create(&t3, NULL, work, i3);
        pthread_create(&t4, NULL, work, i4);
        pthread_create(&t5, NULL, work, i5);

        // Wait until each thread is finished
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        pthread_join(t3, NULL);
        pthread_join(t4, NULL);
        pthread_join(t5, NULL);

        return 0;
}



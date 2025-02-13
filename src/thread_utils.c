#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "thread_utils.h"

pthread_mutex_t console_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    FILE *file;
    char *data;
} ThreadArgs;

// Implementation of strdup, because it's not C standard function
char *my_strdup(const char *s) {
    char *copy = malloc(strlen(s) + 1);
    if (copy) strcpy(copy, s);
    return copy;
}

// Thread function. Writing data to file
void *write_to_file_thread(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    if (args->file) {
        if (fputs(args->data, args->file) == EOF) {
            fprintf(stderr, "Error writing to file\n");
        }
        fflush(args->file);
    }
    free(args->data);
    free(args);
    return NULL;
}

// Thread function. Writing data to console (stdout)
void *write_to_console_thread(void *arg) {
    char *data = (char *)arg;

    pthread_mutex_lock(&console_mutex);  // Lock to prevent mixed output
    if (printf("%s", data) < 0) {
        fprintf(stderr, "Error printing to console\n");
    }
    fflush(stdout);
    pthread_mutex_unlock(&console_mutex);

    free(data);
    return NULL;
}

// Function to create and launch threads for writing
void write_to_files_and_console(FILE **files, int file_count, const char *data) {
    pthread_t threads[file_count + 1];  // +1 for console thread

    // Start console output thread
    char *console_data = my_strdup(data);  // Copy data for thread safety
    if (!console_data) {
        fprintf(stderr, "Memory allocation failed for console data\n");
        return;
    }

    if (pthread_create(&threads[file_count], NULL, write_to_console_thread, console_data) != 0) {
        fprintf(stderr, "Error creating console output thread\n");
        free(console_data);
    } else {
        pthread_detach(threads[file_count]); // Detach the console thread as well
    }

    // Start file write threads
    for (int i = 0; i < file_count; i++) {
        if (files[i]) {
            ThreadArgs *args = malloc(sizeof(ThreadArgs));
            if (!args) {
                fprintf(stderr, "Memory allocation failed for file thread arguments\n");
                continue;
            }

            args->file = files[i];
            args->data = my_strdup(data);
            if (!args->data) {
                fprintf(stderr, "Memory allocation failed for file data\n");
                free(args);
                continue;
            }

            if (pthread_create(&threads[i], NULL, write_to_file_thread, args) != 0) {
                fprintf(stderr, "Error creating thread for file %d\n", i);
                free(args->data);
                free(args);
            } else {
                pthread_detach(threads[i]); // Detach the thread so resources are cleaned up automatically
            }
        }
    }

}

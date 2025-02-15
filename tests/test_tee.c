#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include "thread_utils.h"
#include "tee.h"
#include "file_utils.h"


void test_write_to_stdout() {
    int pipefd[2];
    char buffer[1024] = {0};
    char *test_string = "Hello, tee!\n";

    // Save original stdout
    int saved_stdout = dup(STDOUT_FILENO);

    printf("DEBUG: using write_to_files_and_console()\n");
    fflush(stdout);

    // Create pipe for capturing output
    pipe(pipefd);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    // Test writing to stdout
    write_to_files_and_console(NULL, 0, test_string);

    // Restore original stdout before further output
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);

    // Read from pipe
    read(pipefd[0], buffer, sizeof(buffer));
    close(pipefd[0]);

    assert(strcmp(buffer, test_string) == 0);
    printf("✔ test_write_to_stdout passed\n");
    fflush(stdout);
}


void test_write_to_file() {
    char *test_string = "File test line\n";
    FILE *file = fopen("test_output.txt", "w");

    assert(file != NULL);

    FILE *files[] = {file};
    write_to_files_and_console(files, 1, test_string);

    fclose(file);

    // Fileinhalt kontrollieren
    file = fopen("test_output.txt", "r");
    char buffer[1024] = {0};
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    assert(strcmp(buffer, test_string) == 0);
	printf("✔ test_write_to_file passed\n");
	fflush(stdout);
}

void test_append_mode() {
    char *test_string1 = "First line\n";
    char *test_string2 = "Appended line\n";

    FILE *file = fopen("test_append.txt", "w");
    assert(file != NULL);
    fputs(test_string1, file);
    fclose(file);

    FILE *files[] = {fopen("test_append.txt", "a")};
    assert(files[0] != NULL);

    write_to_files_and_console(files, 1, test_string2);
    fclose(files[0]);

    file = fopen("test_append.txt", "r");
    char buffer[1024] = {0};
    fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    assert(strstr(buffer, test_string1) != NULL);
    assert(strstr(buffer, test_string2) != NULL);
    printf("✔ test_append_mode passed\n");
    fflush(stdout);
}
void test_write_to_invalid_file() {
    FILE *files[] = {fopen("/root/protected.txt", "w")};
    assert(files[0] == NULL);

    int result = write_to_files_and_console(files, 1, "This should fail\n");

    assert(result == 0);
    printf("✔ test_write_to_invalid_file passed\n");
    fflush(stdout);
}

void test_write_to_multiple_files() {
    char *test_string = "Multifile test\n";

    FILE *files[2];
    files[0] = fopen("test1.txt", "w");
    files[1] = fopen("test2.txt", "w");

    assert(files[0] != NULL);
    assert(files[1] != NULL);

    write_to_files_and_console(files, 2, test_string);

    fclose(files[0]);
    fclose(files[1]);

    
    char buffer1[1024] = {0};
    char buffer2[1024] = {0};

    files[0] = fopen("test1.txt", "r");
    files[1] = fopen("test2.txt", "r");

    fread(buffer1, 1, sizeof(buffer1), files[0]);
    fread(buffer2, 1, sizeof(buffer2), files[1]);

    fclose(files[0]);
    fclose(files[1]);

    assert(strcmp(buffer1, test_string) == 0);
    assert(strcmp(buffer2, test_string) == 0);
    printf("✔ test_write_to_multiple_files passed\n");
    fflush(stdout);
}
void test_empty_input() {
    char *empty_string = "";

    FILE *file = fopen("empty_test.txt", "w");
    assert(file != NULL);

    FILE *files[] = {file};
    write_to_files_and_console(files, 1, empty_string);

    fclose(file);

    file = fopen("empty_test.txt", "r");
    char buffer[1024] = {0};
    fread(buffer, 1, sizeof(buffer), file);
    fclose(file);
    assert(strlen(buffer) == 0);
    printf("✔ test_empty_input passed\n");
    fflush(stdout);
}



int main() {
	setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    fprintf(stderr, "DEBUG: main() is ready!\n");
    fflush(stderr);
    
    test_write_to_stdout();
    test_write_to_file();
    test_append_mode();
    test_write_to_invalid_file();
    test_write_to_multiple_files();
    test_empty_input();

    printf("All unit tests passed!\n");
    fflush(stdout);

   
    write(STDOUT_FILENO, "✔ DIRECT WRITE TO STDOUT\n", 26);
	fflush(stdout);
    return 0;

}


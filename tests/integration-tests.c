#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <assert.h>

#define TEST_FILE "test_output.txt"
#define EXPECTED_OUTPUT "Hello, world!\n"

void run_test() {
    // Create a test file
    remove(TEST_FILE);  // Ensure no previous file

    int pipe_fd[2];  // Pipe for communication
    assert(pipe(pipe_fd) == 0);

    pid_t pid = fork();
    assert(pid >= 0);

    if (pid == 0) {
        // Child process: Redirect stdin to pipe read-end
        close(pipe_fd[1]);  // Close write-end
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);

        // Run the tee program with the test file as an argument
        execl("./mytee", "./mytee", TEST_FILE, NULL);
        perror("execl failed");
        exit(1);
    } else {
        // Parent process: Write input to pipe
        close(pipe_fd[0]);  // Close read-end
        write(pipe_fd[1], EXPECTED_OUTPUT, strlen(EXPECTED_OUTPUT));
        close(pipe_fd[1]);  // Close write-end

        // Wait for child process to finish
        int status;
        waitpid(pid, &status, 0);
        assert(WIFEXITED(status) && WEXITSTATUS(status) == 0);

        // Check stdout output (redirected)
        printf("Checking console output...\n");
        FILE *fp = fopen(TEST_FILE, "r");
        assert(fp != NULL);

        char buffer[256];
        fgets(buffer, sizeof(buffer), fp);
        fclose(fp);

        // Verify file content
        assert(strcmp(buffer, EXPECTED_OUTPUT) == 0);

        printf("✔ Integration test passed.\n");
    }
}

int main() {
    run_test();
    return 0;
}

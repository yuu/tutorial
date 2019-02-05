#include <unistd.h>
#include <stdio.h>
#include <string.h>

static const int READ = 0;
static const int WRITE = 1;

int main() {
    int fd[2] = {0};
    pipe(fd); // create an unnamed pipe

    const int ret = fork();
    if (ret < 0)
        return -1;

    // below parent process (writer)
    if (ret > 0 ) {
        const char *str = "Hello World";
        write(fd[WRITE], str, strlen(str)+1);
        sleep(2);
    }

    // below child process (reader)
    if (ret == 0) {
        sleep(1);
        char r[12];
        read(fd[READ], r, sizeof(r));
        printf("read data=%s\n", r);
    }

    return 0;
}

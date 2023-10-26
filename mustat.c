#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#define LENGTH(X)   (sizeof(X) / sizeof (X[0]))
#define CMDLENGTH   50

typedef struct {
    char* command;
    unsigned int interval;
    unsigned int signal;
} Block;

#include "config.h"

static char output[CMDLENGTH];
static char status[LENGTH(blocks)][CMDLENGTH] = {0};
static int running = 1;
static int uptodate = 1;

void runcmd(unsigned int i) {
    FILE *cmdf = popen(blocks[i].command, "r");
    if (!cmdf) return;
    fgets(output, CMDLENGTH, cmdf);
    pclose(cmdf);
    int eos = strlen(output)-1;
    if (output[eos] == '\n')
        output[eos] = '\0';
    if (!strcmp(output, status[i])) return;
    strcpy(status[i], output);
    uptodate = 0;
}

void writestatus() {
    if (uptodate) return;
    for (unsigned int i = 0; i < LENGTH(blocks); ++i)
        printf("%s%s", i ? delim : "", status[i]);
    putchar('\n');
    fflush(stdout);
    uptodate = 1;
}

void sighandler(int signum) {
    unsigned int signal = signum-SIGRTMIN;
    for (unsigned int i = 0; i < LENGTH(blocks); ++i)
        if (blocks[i].signal == signal)
            runcmd(i);
    writestatus();
}

void termhandler() {
    running = 0;
}

int main(int argc, char** argv) {
    signal(SIGTERM, termhandler);
    signal(SIGINT, termhandler);

    for (int i = SIGRTMIN; i <= SIGRTMAX; ++i)
        signal(i, SIG_IGN);
    for (unsigned int i = 0; i < LENGTH(blocks); ++i) {
        runcmd(i);
        if (blocks[i].signal)
            signal(SIGRTMIN+blocks[i].signal, sighandler);
    }

    for(int time = 1; running; ++time) {
        writestatus();
        sleep(1.0);
        for (unsigned int i = 0; i < LENGTH(blocks); ++i) {
            unsigned int interval = blocks[i].interval;
            if (interval && time % interval == 0)
                runcmd(i);
        }
    }

    return 0;
}

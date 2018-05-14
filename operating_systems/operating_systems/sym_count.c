#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int counter = 0;
char symbol;
void my_signal_handler(int signum, siginfo_t* info, void* ptr) {
	if (signum == SIGCONT) {
		printf("Process %d continues\n", getpid());
	}
	else if (signum == SIGTERM) {
		printf("Process %d finishes. Symbol %c. Instances %d.\n", getpid(), symbol, counter);
		exit(0);
	}
}

int main(int argc, char * argv[]) {
	char * fileP = argv[1];
	symbol = argv[2][0];
	int pid;
	int i = 0;
	int ReadNum = open(fileP, O_RDONLY);
	struct sigaction new_action;
	memset(&new_action, 0, sizeof(new_action));
	new_action.sa_sigaction = my_signal_handler;
	new_action.sa_flags = SA_SIGINFO;
	if (0 != sigaction(SIGCONT, &new_action, NULL) || sigaction(SIGTERM, &new_action, NULL) != 0)
	{
		printf("Signal handle registration " "failed. %s\n",
			strerror(errno));
		return -1;
	}
	if (ReadNum <= 0) {
		printf("Error. couldnt open the file\n");
		return 0;
	}
	char buf[1024];
	while (read(ReadNum,buf, 1024) > 0) {
		for (i = 0; i < strlen(buf); i++) {
			if (buf[i] == symbol) {
				counter++;
				pid = getpid();
				printf("Process %d, symbol %c, going to sleep\n", pid, symbol);
				raise(SIGSTOP);
			}
		}
	}
	raise(SIGTERM);

}
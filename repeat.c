#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

#define INTERVAL_LENGTH 5	/* seconds */

char * command;

void handleSigint (int sig) {
	printf ("\nCancelled\n\n");
	free (command);
	exit (EXIT_SUCCESS);
}

int main (int argc, char ** argv) {
	signal (SIGINT, handleSigint);
	int i;
	size_t length;
	float seconds;

	
	length = 1;
	for (i = 1; i < argc; i++) {
		length += 1 + strlen (argv[i]);
	}

	command = malloc (length + 1);
	if (command == NULL)
		return (EXIT_FAILURE);

	for (i = 1; i < argc; i++) {
		strcat (command, argv[i]);
		strcat (command, " ");
	}
	
	while (true) {
		/* execute the command */
		system (command);
		
		seconds = INTERVAL_LENGTH;
		/* wait five seconds */
		while (seconds > 0) {
			usleep (100000);
			printf ("%02.1f seconds left...\r", seconds);
			seconds -= 0.1f;
		}
		printf ("\n");
	}

	return 0;
}

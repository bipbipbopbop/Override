#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void	log_wrapper(FILE *file, char *str, char *who)
{
	// 8 bytes canary
	char	buf[256];

	strcpy(buf, str);
	// repnz scas * 2
	snprintf(buf + strlen(buf), 0xfe - strlen(buf), who);
	buf[strcspn(buf, "\n")] = '\0';
	fprintf(file, "LOG: %s\n", buf);
	// canary check
}

int		main(int ac, char **av)
{
	// 8 bytes canary
	char	buf[100];
	char	a = 0xff;
	int		b = 0xffffffff;
	FILE	*src;
	FILE	*log_file;

	if (ac != 2)
		printf("Usage: %s filename\n", av[0]);

	log_file = fopen("./backups/.log", "w");
	if (log_file == NULL)
	{
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}

	log_wrapper(log_file, "starting back up: ", av[1]);
	src = fopen(av[1], "r");
	if (src == NULL)
	{
		printf("ERROR: Failed to open %s\n", av[1]);
		exit(1);
	}

	*(uint64_t *)buf = *(uint64_t *)"./backups/";
	*(((uint16_t *)buf) + 4) = *(((uint16_t *)"./backups/") + 4);
	buf[10] = "./backups/"[10];
	strncat(buf, av[1], 99 - strlen(buf)/*repnz scas*/);
	b = open(buf, O_WRONLY | O_ASYNC | O_FSYNC, 0x1b0);
	if (b < 0)
	{
		printf("ERROR: Failed to open %s%s\n", "./backups/", av[1]);
		exit(1);
	}
	do
	{
		write(b, &a, 1);
		a = fgetc(src);
	} while (a != 0xff);
	log_wrapper(log_file, "Finished back up ", av[1]);
	fclose(src);
	close(b);
	// canary check
	return 0;
}
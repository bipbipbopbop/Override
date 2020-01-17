#include <stdio.h>
#include <string.h>
#include <stdint.h>

void clear_stdin(void)
{
    char x = 0;
    while(1)
    {
        x = getchar();
        if(x == '\n' || x == EOF)
            break;
    }
}

unsigned int get_unum(void)
{
    unsigned int res = 0;
    fflush(stdout);
    scanf("%u", &res);
    clear_stdin();
    return res;
}

int		store_number(int *buf)
{
	int	a;
	int	b;

	printf(" Number: ");
	a = get_unum();
	printf(" Index: ");
	b = get_unum();

	// not on stack
	unsigned int edx_tmp = ((uint64_t)b * 0xaaaaaaab) >> 32;//32 == high-order bits
	edx_tmp >>= 1;
	edx_tmp = b - (edx_tmp + edx_tmp + edx_tmp);
	//to simplify, all numbers that are multiple of 3 are bad index
	if (edx_tmp != 0 && ((unsigned)a >> 24) != 0xb7)
	{
		buf[b] = a;
		return 0;
	}

	puts(" *** ERROR! ***");
	puts("   This index is reserved for wil!");
	puts(" *** ERROR! ***");
	return 1;
}

int		read_number(int *buf)
{
	int		a = 0;

	printf(" Index: ");
	a = get_unum();
	printf(" Number at data[%u] is %u\n", a, buf[a]);
	return 0;
}

int		main(int ac, char **av)
{
	// 4 bytes canary
	char	cmd[20] = {};// manually set to zero, 4 bytes per 4 bytes
	int		c6 = 0;
	int 	buf[25] = {};// rep stos
	char	**a = av;
	char	**b = av + 1;

	while (a != NULL)
	{
		memset(*a, 0, strlen(*a)/*repnz scas*/);
		a++;
	}
	while (b != NULL)
	{
		memset(*b, 0, strlen(*b)/*repnz scas*/);
		b++;
	}
	puts("----------------------------------------------------\n  Welcome to wil's crappy number storage service!   \n----------------------------------------------------\n Commands:                                          \n    store - store a number into the data storage    \n    read  - read a number from the data storage     \n    quit  - exit the program                        \n----------------------------------------------------\n   wil has reserved some storage :>                  \n----------------------------------------------------\n");
	while (1)
	{
		printf("Input command: ");
		c6 = 1;
		fgets(cmd, 20, stdin);
		// repnz scas
		cmd[strlen(cmd)] = '\0';
		// repz cmpsb
		if (strncmp(cmd, "store", 5) == 0)
			c6 = store_number(buf);
		// repz cmpsb
		else if (strncmp(cmd, "read", 4) == 0)
			c6 = read_number(buf);
		// repz cmpsb
		else if (strncmp(cmd, "quit", 4) == 0)
			return 0;//canary check
		if (c6 != 0)
			printf(" Failed to do %s command\n", cmd);
		else
			printf(" Completed %s command successfully\n", cmd);
		// manually set to zero, 4 bytes per 4 bytes
		memset(cmd, 20, stdin);
	}
	return 0;
}

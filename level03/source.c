#include <stdio.h>
#include <time.h>
#include <stddef.h>

void	clear_stdin()
{
	char	var = 0;

	while (var != 0xff)
	{
		var = getchar();
		if (var == 0xa)
			return ;
	}
}

unsigned int	get_unum()
{
	unsigned int	var = 0;

	fflush(stdout);
	scanf("%u", var);
	clear_stdin();
	return var;
}

void	prog_timeout()
{
	exit(1);
}

void	decrypt(void *addr)
{
	// There is a use of a stack canary here
	//int	canary = gs:0x14
	char	var1 = 0;
	int		var2 = 0x33617c7d;
	int		var3 = 0x7b66737e;
	int		var4 = 0x67667360;
	int		var5 = 0x757c7d51;
	unsigned int	var6 = strlen(&var5);//repnz scas
	unsigned int	var7 = 0;

	while (var6 > var7)
	{
		*(uint8_t *)(&var5 + var7) = (uint8_t)(((uint8_t)*(&var5 + var7)) ^ (uintptr_t)addr);
		var7 += 1;
	}
	//repz cmpsb
	if (strncmp("Congratulations!", (char *)&var5, 17) == 0)
		system("/bin/sh");
	else
		puts("\nInvalid Password");
	// check canary, that may leads to a call to __stack_chk_fail()
	return ;
}

void	test(int var, uintptr_t addr)
{
	uintptr_t	sub = addr - var;

	if (sub <= 0x15)
	{
		goto **(void***)(sub << 2 + 0x80489f0U);// it's a computed goto ; a GCC extension. In fact it doesn't do what is done in asm. their is just a jump on the value contain in sub.

		decrypt(sub); return ;
		decrypt(sub); return ;
		decrypt(sub); return ;
		decrypt(sub); return ;
		decrypt(sub); return ;
		decrypt(sub); return ;
		decrypt(sub); return ;
		decrypt(sub); return ;
		decrypt(sub); return ;
		decrypt(sub); return ;
		decrypt(sub); return ;
		decrypt(sub); return ;
		decrypt(sub); return ;
		decrypt(sub); return ;
		decrypt(sub); return ;

	}
	decrypt(rand());
	return ;
}

int	main(void)
{
	int		var;
	//some instructions that look useless and not translatable in C

	srand(time(NULL));
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:")
	scanf("%d", &var);
	test(var, 0x1337d00d);
	return 0;
}
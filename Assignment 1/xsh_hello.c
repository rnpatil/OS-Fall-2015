/* xsh_hello.c - xsh_hello */

#include <xinu.h>

#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_hello - print Hello <string>, Welcome to the world of Xinu!!
 *------------------------------------------------------------------------
 */

shellcmd xsh_hello(int nargs,char *args[])
{
	if(nargs>2)
	{		
		printf("Too many arguments!!\n");
		
	}
	else if(nargs<2)
	{
		printf("Too less arguments!!\n");
	}
	else 
	{
		printf("Hello, %s Welcome to the world of XINU!!\n", args[1]);
	}

}


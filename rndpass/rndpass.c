/*
 * Copyright (c) 2008, Joshua M. Clulow. All rights reserved.
 *
 * This file is distributable under the BSD license.
 *    (see ../BSD_LICENSE)
 */

/*  Compile:  gcc -std=c99 -o rndpass rndpass.c  */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

char *genpass(int rndfd, int len)
{
	char *pass = malloc(sizeof(char) * len + 1);
	
	int r = read(rndfd, pass, len);
	if (r != len)
	{
		fprintf(stderr, "Sigh, error while reading from /dev/random.");
		free(pass);
		return NULL;
	}
	
	for (int q = 0; q < len; q++)
	{
		int p = abs(*(pass+q)) % (26 * 2 + 10 + 4); /* A-Z, a-z, 0-9, $, %, #, . */
		/* log(66^8,2) ~= 48 bits of entropy for 8char password */
		/*  DISCLAIMER:  ABOVE MATH COULD BE COBBLERS. */
		
		if (p >= 0 && p <= 25)
			pass[q] = p - 0  + 'A';
		else if (p >= 26 && p <= 51)
			pass[q] = p - 26 + 'a';
		else if (p >= 52 && p <= 61)
			pass[q] = p - 52 + '0';
		else switch(p)
		{
			case 62: *(pass+q) = '$'; break;
			case 63: *(pass+q) = '%'; break;
			case 64: *(pass+q) = '#'; break;
			case 65: *(pass+q) = '.'; break;
		}
	}
	*(pass+len) = 0;
	return pass;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <num> <len>\n", argv[0]);
		fprintf(stderr, "   Where <num> is the number of passwords of length <len>.\n");
		return 35;
	}
	errno = 0;
	int num = atol(argv[1]);
	if (errno == EINVAL || errno == ERANGE || num < 1)
	{
		fprintf(stderr, "<num> must be a valid positive integer.\n");
		return 5;
	}
	errno = 0;
	int len = atol(argv[2]);
	if (errno == EINVAL || errno == ERANGE || len < 1)
	{
		fprintf(stderr, "<len> must be a valid positive integer.\n");
		return 6;
	}

	int fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Sigh, couldn't open /dev/random.");
		return 1;
	}

	for (int m = 0; m < num; m++)
	{
		char *pss = genpass(fd, len);
		if (pss == NULL)
			return 3;
		printf("%s\n", pss);
		free(pss);
	}
	
	close(fd);
}



/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2010 Joshua M. Clulow.  All rights reserved.
 * Use is subject to license terms.
 */
/*
 *
 *  NS1 Decryption Function Wrapper
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *dvalue(char *);

int main(int argc, char** argv)
{
	char* dv;
	if (argc != 2)
	{
		printf("{NS1} Decrypter\n");
		printf("Usage: %s \"{NS1}CRYPTEDPW\"\n", argv[0]);
		exit(1);
	}
	if (strlen(argv[1]) < 5 || strncmp(argv[1], "{NS1}", 5) != 0)
	{
		printf("Provided argument doesn't look like an NS1 hash.\n");
		printf(" (needs to begin with \"{NS1}\")\n");
		exit(2);
	}
	dv = dvalue(argv[1]);
	printf("%s\n", dv);
	free(dv);
	exit(0);
}


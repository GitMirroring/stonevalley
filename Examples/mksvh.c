/*
 * Name:        mksvh.c
 * Description: Make one StoneValley header tool.
 * Author:      cosh.cage#hotmail.com
 * File ID:     0709250909A0709250910L00134
 * License:     LGPLv3
 * Copyright (C) 2025 John Cage
 *
 * This file is part of StoneValley.
 *
 * StoneValley is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * StoneValley is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with StoneValley.
 * If not, see <https://www.gnu.org/licenses/>.
 *
 * Tips of usage:
 * Put mksvh.c(this file) under StoneValley/src/ and run this compound command line under GNU/Linux.
 * $ cc mksvh.c -o mksvh; ./mksvh;
 * You can see a file named sv.h at StoneValley/src/.
 * Please include sv.h whenever and wherever you want.
 *
 */
#include <stdio.h>
#include <stdlib.h>

typedef unsigned bool;

#ifndef true
#define true  1
#endif

#ifndef false
#define false 0
#endif

#define SZ_HEADER "sv.h"

const char * SZFILE[] = 
{
	"svdef.h",
	"svstring.h",
	"svatom.c",
	"svarray.c",
	"svlist.c",
	"svmatrix.c",
	"svmisc.c",
	"svstack.h",
	"svstack.c",
	"svqueue.h",
	"svqueue.c",
	"svtree.h",
	"svbytree.c",
	"svhtree.c",
	"svctree.c",
	"svgtree.c",
	"svstree.c",
	"svhash.h",
	"svhash.c",
	"svset.h",
	"svset.c",
	"svgraph.h",
	"svgraph.c"
};

FILE * GetFile(const char * szfile)
{
	FILE * fp;
	
	fp = fopen(szfile, "r");
	
	return fp;
}

bool PutFile(FILE * fpin, FILE * fpout)
{
	if (NULL == fpin || NULL == fpout)
		return false;
	
	while (!feof(fpout))
	{
		register int c;
		c = fgetc(fpout);
		if (EOF != c)
			fputc(c, fpin); /* Move a char in the file. */
	}
	
	fclose(fpout);
	
	return true;
}

void PAssert(bool exp, const char * sz)
{
	if (!exp)
	{
		printf("File operation failure at file %s!\n", sz);
		exit(2);
	}
}

int main()
{
	FILE * fpsvh;
	
	fpsvh = fopen(SZ_HEADER, "w");
	
	if (NULL != fpsvh)
	{
		size_t i;
		
		fputs("#ifndef _SV_H_\r\n", fpsvh);
		fputs("#define _SV_H_\r\n", fpsvh);
		
		for (i = 0; i < sizeof(SZFILE) / sizeof(SZFILE[0]); ++i)
		{
			PAssert(PutFile(fpsvh, GetFile(SZFILE[i])), SZFILE[i]);
		}
		
		fputs("#endif\r\n\r\n", fpsvh);
		
		fclose(fpsvh);
	}
	else
		return 1;
	
	return 0;
}


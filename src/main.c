#include <stdio.h>
#include "svstring.h"

int cbftvs(void * pitem, size_t param)
{
	size_t i;
	for (i = 0; i < param; ++i)
		putchar(i[(char *)pitem]);
	printf("\n");
	return CBF_CONTINUE;
}

int main()
{
	P_ARRAY_Z pp = strCreateCharacterStringArrayZ("GEEK"); // Pattern.
	P_ARRAY_Z pt = strCreateCharacterStringArrayZ("GEEKS FOR GEEKS AND GEEKS"); // Text.
	strZSearchArrayZ(pt, pp, sizeof(char), cbftvs, strLevelArrayZ(pp));
	strDeleteArrayZ(pp); // Do not forget to delete array here.
	strDeleteArrayZ(pt);
	return 0;
}


#include <stdio.h>
#include "svstring.h"

int cbf(void * pitem, size_t param)
{
	printf("%zd\n", *(size_t *)pitem);
	DWC4100(param);
	return CBF_CONTINUE;
}

int main()
{
	size_t i = 12345;
	P_ARRAY_Z p = strCreateArrayZ(15, sizeof i);
	// int c = 'A';
	strSetArrayZ(p, &i, sizeof i);
	
	strTraverseArrayZ(p, sizeof i, cbf, 0, false);
	
	strDeleteArrayZ(p);
	return 0;
}


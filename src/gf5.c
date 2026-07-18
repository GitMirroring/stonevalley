#include <stdio.h>
#include "svgraph.h"

int cbftvsppp(void * pitem, size_t param)
{
	printf("[%zd, w:%zd]->", ((P_EDGE)(((P_NODE_S)pitem)->pdata))->vid, ((P_EDGE)(((P_NODE_S)pitem)->pdata))->weight);
	return CBF_CONTINUE;
}

int cbftvs(void * pitem, size_t param)
{
	printf("(%zd)->", ((P_VERTEX_L)pitem)->vid);
	strTraverseLinkedListSC_N(((P_VERTEX_L)pitem)->adjlist, NULL, cbftvsppp, 0);
	printf("\n");
	return CBF_CONTINUE;
}

void dbgprint(P_GRAPH_L p)
{
	grpTraverseVerticesL(p, cbftvs, 0, ETM_INORDER);
}

int cbfp(void * pitem, size_t param)
{
	printf("%zd ", *(size_t *)pitem);
	return CBF_CONTINUE;
}

int cbfparr(void * pitem, size_t param)
{
	printf("(%zd, %zd)\n", *(size_t *)pitem, *((size_t *)pitem + 1));
	DWC4100(param);
	return CBF_CONTINUE;
}

int path1(void * pitem, size_t param)
{
	size_t * p = (size_t *)((P_NODE_D)pitem)->pdata;
	
	printf("(%zd, %zd)\n", *p, *++p);
	DWC4100(param);
	return CBF_CONTINUE;
}

int main()
{
	P_GRAPH_L pf = grpCreateL(), pc = grpCreateL();
	P_ARRAY_Z pa;
	P_LIST_D pl;
	
	grpInsertVertexL(pf, 0);
	grpInsertVertexL(pf, 1);
	grpInsertVertexL(pf, 2);
	grpInsertVertexL(pf, 3);
	grpInsertVertexL(pf, 4);
	grpInsertVertexL(pf, 5);
	grpInsertVertexL(pf, 6);
	grpInsertVertexL(pf, 7);
	
	grpInsertEdgeL(pf, 0, 1, 0);
	grpInsertEdgeL(pf, 0, 2, 0);
	grpInsertEdgeL(pf, 1, 2, 0);
	grpInsertEdgeL(pf, 1, 5, 0);
	grpInsertEdgeL(pf, 2, 4, 0);
	grpInsertEdgeL(pf, 4, 6, 0);
	grpInsertEdgeL(pf, 5, 6, 0);
	grpInsertEdgeL(pf, 3, 5, 0);
	grpInsertEdgeL(pf, 3, 7, 0);
	grpInsertEdgeL(pf, 5, 7, 0);
	
	pa = grpTopologicalSortL(pf);
	
	if (NULL != pa)
	{
		strTraverseArrayZ(pa, sizeof(size_t), cbfp, 0, false);
		printf("\n");
		strDeleteArrayZ(pa);
	}
	
	grpInsertVertexL(pc, 0);
	grpInsertVertexL(pc, 1);
	grpInsertVertexL(pc, 2);
	grpInsertVertexL(pc, 3);
	grpInsertVertexL(pc, 4);
	grpInsertVertexL(pc, 5);
	grpInsertVertexL(pc, 6);
	grpInsertVertexL(pc, 7);
	
	grpInsertEdgeL(pc, 0, 2, 2);
	grpInsertEdgeL(pc, 2, 0, 3);
	grpInsertEdgeL(pc, 0, 4, 2);
	grpInsertEdgeL(pc, 2, 4, 5);
	grpInsertEdgeL(pc, 2, 6, 7);
	grpInsertEdgeL(pc, 4, 7, 3);
	grpInsertEdgeL(pc, 6, 7, 2);
	grpInsertEdgeL(pc, 7, 6, 7);
	grpInsertEdgeL(pc, 5, 3, 2);
	grpInsertEdgeL(pc, 5, 1, 4);
	grpInsertEdgeL(pc, 5, 6, 4);
	
	pl = grpDijkstraShortestPathL(pc, 0, 7);
	strTraverseLinkedListDC_N(*pl, NULL, path1, 0, false);
	printf("======================\n");
	pa = grpShortestPathFastL(pc, 0);
	if (NULL != pa)
	{
		strTraverseArrayZ(pa, sizeof(size_t), cbfparr, 0, false);
		printf("\n");
		strDeleteArrayZ(pa);
	}
	
	// grpMinimalSpanningTreeL(pc);
	dbgprint(pc);
	
	grpDeleteL(pf);
	grpDeleteL(pc);
	
	return 0;
}


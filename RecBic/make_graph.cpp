/* Author:  Zhenjia Wang Dec. 22, 2014
 * Usage: This is part of bicluster package. Use, redistribution, modify without limitations
 * show how does the whole program work
 *
 * Produces two graphs sequentially, derived from microarray data.
 * 
 * The first graph is generated from the raw data where an edge is defined
 * as two genes having common components from same condition, the score on
 * the edge being the number of the same components. The edges in the first
 * graph, are used as vertices in the second graph, where edges are defined
 * as the common columns between two co-vertex edges in the first graph,
 * with scores defined as the number of same columns for all three genes.
 *
 */

#include "make_graph.h"
#include <stdio.h> 
/*we can reduce the HEAP_SIZE when the data contain so many genes so that memory is not enough*/
static const int HEAP_SIZE = 20000000;

/**************************************************************************/

/* String intersection function without string copying, only numbers */
/*caculate the weight of the edge in the first graph*/
int str_intersect_r (const discrete *s1, const discrete *s2,char tag)
{
	int common_cnt = 0;
	/* s1 and s2 of equal length, so we check s1 only */
	int i;
	if(tag == 'P')
		for (i=0;i<cols;i++)
		{
		    /*  if ((*s1) * (*s2) != 0)  */
			if ((*s1) * (*s2) > 0) 
				common_cnt++;
			s1++; 
			s2++;
		}
	if(tag == 'N')
		for (i=0;i<cols;i++)
		{
			if ((*s1) * (*s2) != 0)
				common_cnt++;
			s1++; 
			s2++;
		}
	return common_cnt;
}

/* Fibonacci heap related subroutines */
static int edge_cmpr(void *a, void *b)
{
	float score_a, score_b;
	score_a = ((Edge *)a)->score;
	score_b = ((Edge *)b)->score;

	if (score_a < score_b) return -1;
	if (score_a == score_b) return 0;
	return 1;
}

/* Maintain a fixed size heap */
static void fh_insert_fixed(struct fibheap *a, Edge *i, Edge **cur_min)
{
	if (a->fh_n < HEAP_SIZE) 
	{
		fh_insert(a, (void *)i);
	}
	else
	{
		if (edge_cmpr(cur_min, i) < 0)
		{
			/* Remove least value and renew */
			fh_extractmin(a);
			fh_insert(a, (void *)i);
			/* Keep a memory of the current min */
			*cur_min = (Edge *)fh_min(a);
		}
	}
}

/*sort the edges in decrease order so that e1 is the largest edge*/
static void fh_dump(struct fibheap *a, Edge **res)
{
	int i;
	int n = a->fh_n;
	for (i=n-1; i>=0; i--)
		res[i] = (Edge *) fh_extractmin(a);
}

/*********************************************************************/
/*********************************************************************/
void make_graph (const char* fn)
{
	FILE *fw = mustOpen(fn, "w");
	int i, j,k,cnt,step,endi;
	int rec_num = 0;
	int PART=4;
/*	if(rows > 15000)
		PART = 5;
	else if(rows <3000)
		PART = 1;
	else
		PART = rows/3000; */

	po->COL_WIDTH = MAX(3+floor(cols/30), po->COL_WIDTH);
	
	/* edge_ptr describe edges */
        edge_list = (Edge **)malloc(sizeof(Edge *) * HEAP_SIZE);

        /* Allocating heap structure */
	struct fibheap *heap;
	heap = fh_makeheap();
	fh_setcmp(heap, edge_cmpr);

	/* Generating seed list and push into heap */
	progress("Generating seed list (minimum weight %d)", po->COL_WIDTH);	

	Edge __cur_min = {0, 0, po->COL_WIDTH};
	Edge *_cur_min = &__cur_min;
	Edge **cur_min = & _cur_min;
	/* iterate over all genes to retrieve all edges */
	step = rows/PART;
	for(k=0;k<PART;k++)
	{	
		endi=(k+1)*step;
		if(k==PART-1)
			endi=rows;
		for (i=k*step; i < endi; i++)
		{
			for (j = i+1; j < endi; j++)
			{
				//必须在这里改，原因，两行基因可以有多个最长公共子序列，或者说多个最长路，不过这里只是得到两个基因和最长路的长度最为得分，那么在这里改是不对的。。。
				cnt = str_intersect_r(arr_c[i], arr_c[j],'N');//ignore the zero-discrete-expression data
                                if (cnt < ((*cur_min)->score)) continue;
				cnt=get_Genes_LCS_length(arr_c[i], arr_c[j]);//score function
				if (cnt < ((*cur_min)->score)) continue;

                edge_ptr = (Edge *)malloc(sizeof(*edge_ptr));
                edge_ptr -> gene_one = i;
				edge_ptr -> gene_two = j;
				edge_ptr -> score = cnt;
				fh_insert_fixed(heap, edge_ptr, cur_min);

			}
		}
	}

	rec_num = heap->fh_n;
	if (rec_num == 0)
		errAbort("Not enough overlap between genes");

	/* sort the seeds */
	uglyTime("%d seeds generated", rec_num);
        edge_list = (Edge **)realloc(edge_list, sizeof(*edge_list) * rec_num);
        fh_dump(heap, edge_list);
//cout seeds (
/*
FILE *stream;
stream = fopen( "/home/lxy/fprintf.out", "w" );
fprintf(stream,"%d""aaaa",rec_num);
for(int i=0; i<rec_num;i++)
{
     fprintf(stream,"%d\t", edge_list[i]->gene_one);
	fprintf(stream,"%d\t",edge_list[i]->gene_two);
	fprintf(stream,"%d\n", edge_list[i]->score);
	edge_list++;

}
fclose( stream );

*/




///)
	/* bi-clustering */
        int n_blocks = 0;
	progress("Clustering started");
	n_blocks = cluster(fw, edge_list, rec_num);
	uglyTime("%d clusters are written to %s", n_blocks, fn);

	/* clean up */
	for (i=0; i<rec_num; i++)
		free(edge_list[i]);
	free(edge_list);
}

/***************************************************************************/


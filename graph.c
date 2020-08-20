#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

typedef int TCost;

typedef struct node
{
	int v;
	TCost c;
	struct node *next;
} TNode, *ATNode;

typedef struct
{
	int nn;
	ATNode *adl;
}	TGraphL;


void alloc_list(TGraphL * G, int n)
{
    int i;
    G->nn = n;
	G->adl = (ATNode*) malloc((n+1)*sizeof(ATNode));
	for(i = 0; i < n; i++)
		G->adl[i] = NULL;

}

void free_list(TGraphL *G)
{
    int i;
    ATNode it;
    for(i = 1; i < G->nn; i++){
		it = G->adl[i];
		while(it != NULL){
			ATNode aux = it;
			it = it->next;
			free(aux);
		}
		G->adl[i] = NULL;
	}
	G->nn = 0;
}

void insert_edge_list(TGraphL *G, int v1, int v2, int c)
{
 TNode *t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v2; t->c=c; t->next = G->adl[v1]; G->adl[v1]=t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v1;  t->c=c; t->next = G->adl[v2]; G->adl[v2]=t;
}

int *seteaza_vector_distante(int sursa,TGraphL G){
	int *vector=(int*)malloc(G.nn*sizeof(int));
	int INF=99999999;
	for (int i = 0; i < G.nn; ++i)
	{
		vector[i]=INF;
	}
	vector[sursa]=0;
	return vector;
}
int *seteaza_vector_constant(int c,int nr_c){
	int *v=(int*)malloc(nr_c*sizeof(int));
	for (int i = 0; i < nr_c; ++i)
	{
		v[i]=c;
	}
	return v;
}
int allVisited(int n,int *viz){
	for (int i = 0; i < n; ++i)
	{
		if(viz[i]==0)
			return 0;
	}
	return 1;
}
int cauta_minim_nevizitat(int *d,int *viz,int n){
	int dmin=999999999;
	int poz;
	for (int i = 0; i < n; ++i)
	{
		if(dmin>d[i]&&viz[i]!=1){
			dmin=d[i];
			poz=i;
		}
	}
	return poz;
}
void afisare(int sursa, int *distante,int n){
	for (int i = 0; i < n; ++i)
	{
		printf("Distanta minima de la %d la %d este: %d \n",sursa,i,distante[i]);
	}
}
void dijkstra(TGraphL G, int s)
{
    int *vector_distante=seteaza_vector_distante(s,G);
    int nr_maxim_muchii=(G.nn * (G.nn-1))/2;
    int min=s;
    int *viz=seteaza_vector_constant(0,G.nn);
    while(!(allVisited(G.nn,viz))){
    	TNode *currsor=G.adl[min];
    	viz[min]=1;
    	while(currsor!=NULL){
    		if(vector_distante[currsor->v]>vector_distante[min]+currsor->c){
    			vector_distante[currsor->v]=vector_distante[min]+currsor->c;
    		}
    		currsor=currsor->next;
    	}
    	min=cauta_minim_nevizitat(vector_distante,viz,G.nn);
    }
    afisare(s,vector_distante,G.nn);
}

void Prim(TGraphL G)
{
    int *parinti=seteaza_vector_constant(0,G.nn);
    int *viz=seteaza_vector_constant(0,G.nn);
    int p=0;
    viz[0]=1;
    int index;
    while(!(allVisited(G.nn,viz))){
    	int min=999999999;
    	for (int i = 0; i < G.nn; ++i)
    	{
    		if(viz[i]==1){
    			TNode *cursor=G.adl[i];
    			while(cursor!=NULL){
    				if(viz[cursor->v]==0 && cursor->c<min){
    					min=cursor->c;
    					index=cursor->v;
    					p=i;
    				}
    				cursor=cursor->next;

    			}
    		}
    	}
    	parinti[index]=p;
    	viz[index]=1;
    }
   	for (int i = 1; i < G.nn; ++i)
   	{
   		printf("Varf:%d Parinte->%d\n",i,parinti[i]);
   	}
}


int main()
{
    int i,v1,v2,c;
	int V,E;
	TGraphL G;
	ATNode t;
	freopen ("graph.in", "r", stdin);
	scanf ("%d %d", &V, &E);
	alloc_list(&G, V);

	for (i=1; i<=E; i++)
	{
		scanf("%d %d %d", &v1, &v2, &c);
	    insert_edge_list(&G, v1,v2, c);
	}

	for(i=0;i<G.nn;i++)
	{
    printf("%d : ", i);
    for(t = G.adl[i]; t != NULL; t = t->next)
    printf("%d ",t->v,t->c);
    printf("\n");
	}
	dijkstra(G,0);
	Prim(G);

	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Util.h"
#include "Graph.h"

TGraphM* createGraphAdjMatrix(int numberOfNodes){
	TGraphM *matrix=(TGraphM*)malloc(sizeof(TGraphM));
	matrix->nn=numberOfNodes;
	matrix->Ma=(int**)malloc(numberOfNodes*sizeof(int*));
	for (int i = 0; i < numberOfNodes; ++i)
	{
		matrix->Ma[i]=(int*)calloc(numberOfNodes,sizeof(int));
	}
	return matrix;
}

TGraphL* createGraphAdjList(int numberOfNodes){
	TGraphL *graph=(TGraphL*)malloc(sizeof(TGraphL));
	graph->nn=numberOfNodes;
	graph->adl=(TNode**)malloc(sizeof(TNode*));
	for (int i = 0; i < numberOfNodes; ++i)
	{
		graph->adl[i]=(TNode*)malloc(sizeof(TNode));
		graph->adl[i]=NULL;
	}
	return graph;
}

void addEdgeMatrix(TGraphM* graph, int v1, int v2){
	graph->Ma[v1][v2]=1;
	graph->Ma[v2][v1]=1;
}

void addEdgeList(TGraphL* graph, int v1, int v2){
	TNode *aux=(TNode*)malloc(sizeof(TNode));
	aux->v=v2;
	aux->next=graph->adl[v1];
	graph->adl[v1]=aux;
	TNode *aux2=(TNode*)malloc(sizeof(TNode));
	aux2->v=v1;
	aux2->next=graph->adl[v2];
	graph->adl[v2]=aux2;
}

void removeEdgeMatrix(TGraphM* graph, int v1, int v2){
	graph->Ma[v1][v2]=0;
	graph->Ma[v2][v1]=0;
}

void removeNodeMatrix(TGraphM* graph, int v){
	for (int i = 0; i < graph->nn; ++i)
	{
		if(graph->Ma[v][i]==1){
			removeEdgeMatrix(graph,v,i);
		}
	}
}

TNode *sterge_element_lista(TNode *lista,int element_de_sters){
	TNode *iter=lista;
	if (iter->v==element_de_sters)
	{
		lista=lista->next;
		return lista;
	}
	else{
		TNode *iterBack=iter;
		while(iter!=NULL){
			if(iter->v==element_de_sters){
				iterBack->next=iter->next;
				return lista;
			}
			iterBack=iter;
			iter=iter->next;
		}
	}
	return lista;
}
void removeEdgeList(TGraphL* graph, int v1, int v2){
	graph->adl[v1]=sterge_element_lista(graph->adl[v1],v2);
	graph->adl[v2]=sterge_element_lista(graph->adl[v2],v1);
}

void removeNodeList(TGraphL* graph, int v){
	TNode *aux=graph->adl[v];
	while(aux){
		removeEdgeList(graph,v,aux->v);
		aux=aux->next;
	}
}


void destroyGraphAdjMatrix(TGraphM *graph){
	for (int i = 0; i < graph->nn; ++i)
	{
		removeNodeMatrix(graph,i);
		free(graph->Ma[i]);
	}
	free(graph->Ma);
}

void destroyGraphAdjList(TGraphL* graph){
	for (int i = 0; i < graph->nn; ++i)
	{
		removeNodeList(graph,i);
		free(graph->adl[i]);
	}
	free(graph->adl);
}
List *addToList(List *lista , int key){
	ListNode *p=lista->head;
	ListNode *deAdaugat=(ListNode*)malloc(sizeof(ListNode));
	deAdaugat->key=key;
	while(p->next!=lista->head)
		p=p->next;
	p->next->prev=deAdaugat;
	deAdaugat->prev=p;
	deAdaugat->next=p->next;
	p->next=deAdaugat;
	return lista;
}
void printList(List *lista){
	ListNode *iter=lista->head->next;
	while(iter!=lista->head){
		printf("%d->",iter->key);
		iter=iter->next;
	}
}
List* dfsIterativeGM(TGraphM* graph, int s){
	int visited[graph->nn];
	for (int i = 0; i < graph->nn; ++i)
	{
		visited[i]=0;
	}
	Stack *stiva=createStack();
	List *lista_de_parcurgere=createList();
	push(stiva,s);
	while(!(isStackEmpty(stiva))){
		int curent=top(stiva);
		pop(stiva);
		if(visited[curent]==0)
			lista_de_parcurgere=addToList(lista_de_parcurgere,curent);
		visited[curent]=1;
		
		for (int i = graph->nn-1; i >=0; --i)
		{
			if(graph->Ma[curent][i]==1&&visited[i]==0)
				push(stiva,i);
		}
	}

	
	lista_de_parcurgere->head=lista_de_parcurgere->head->next;
	return lista_de_parcurgere;
}

void dfsRecGMHelper(TGraphM* G,int* visited, List* path, int s){
	visited[s]=1;
	push(path,s);
	for (int i = 0; i < G->nn; ++i)
	{
		if(visited[i]==0&&G->Ma[s][i]==1){
			dfsRecGMHelper(G,visited,path,i);
		}
	}
	
}

List* dfsRecursiveGM(TGraphM* G, int s){
	List *path=createList();
	int visited[G->nn];
	for (int i = 0; i < G->nn; ++i)
	{
		visited[i]=0;
	}
	dfsRecGMHelper(G,visited,path,s);
	return path;
}

void dfsRecGLHelper(TGraphL* G, int* visited, List* path, int s){
	TNode *iter=G->adl[s];
	printf("%d\n",s );
	for (int i = 0; i < G->nn; ++i)
	{
		printf("%d-",visited[i]);
	}
	printf("\n");
	visited[s]=1;
	while(iter!=NULL){
		printf("%d-----------\n",visited[iter->v] );
		if(visited[iter->v]==0)
			dfsRecGLHelper(G,visited,path,iter->v);
		iter=iter->next;
	}
}

List* dfsRecursiveGL(TGraphL* G, int s){
	printf("%d\n",G->nn ); /// NU INTELEG DE CE IMI DA 0 DACA POATE CINEVA SA MA SUNE PE TEAMS SAU SA MI EXPLICE CHIAR AS DORI SA STIU
	return NULL;
}

List* bfsGL(TGraphL* graph, int s){
	return NULL;
}



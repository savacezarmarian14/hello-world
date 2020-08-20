#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <string.h>

typedef struct {
    unsigned char value;
    int left, right;
} HuffmanNode;

#define Item int

// Including below so Item is defined.
#include "heap.h"

void computeFreqs(char *text, int size, int freqs[256]) {
for (int i = 0; i <size ; i++)
	freqs[(int)text[i]]++;
}

HuffmanNode *makeTree(int freqs[256], int *size) {

PriQueue *heap = makeQueue(256);
HuffmanNode *huffman = (HuffmanNode*)malloc(256*2*sizeof(HuffmanNode));

  for(int i = 0; i < 256; ++i)
    {    
    	ItemType aux;
        if( freqs[i] != 0)
    	{
            aux.prior = freqs[i];
            aux.content = *size;
            insert(heap,aux);
			huffman[(*size)].value = i;
            huffman[(*size)].left = huffman[(*size)].right = -1;
            (*size)++;
        }
    }
    if( heap->size == 1)
    {
        ItemType aux = getMin(heap);
        huffman[(*size)].left = aux.content;
        huffman[(*size)].right = -1;
        (*size)++; 
    }
  	if(heap->size != 1)
   {
      	while(heap->size > 1)
        {
            ItemType auxx,auxy;
            auxx = getMin(heap);   
            removeMin(heap);
            auxy = getMin(heap);
            removeMin(heap);
            huffman[(*size)].left = auxx.content;
            huffman[(*size)].right = auxy.content;
            aux.content = *size;
            aux.prior = auxx.prior + auxy.prior;
            insert(heap,aux);
            (*size)++;
        }
    }
    return huffman;
}

void makeCodes(int index, HuffmanNode *nodes, char **codes, char *code) {
	if( nodes[index].value != 0){
        codes[index] = (char*) malloc((strlen(code) + 1)*sizeof(char));
        strcpy(codes[index],code);
    }
    else{
        strcat(code,"0");
        makeCodes(nodes[index].left,nodes,codes,code);
        code[strlen(code) - 1] = 0;
        strcat(code,"1");
        makeCodes(nodes[index].right,nodes,codes,code);
        code[strlen(code) - 1] = 0;
    }
}

char *compress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
	int v[256],k = 0;

    if( textSize == 0){
        char *nul =(char*)malloc(2*sizeof(char));
        nul[0] = ' ';
        return nul;
    }

    for(int i = 0; i < numNodes ;i++){
        v[nodes[i].value] = k;
        k++;
    }
    char *codes = (char*) malloc(k*sizeof(char*));

    char *code = (char*) malloc(256*sizeof(char));
    code[0] = 0;
    makeCodes(numNodes - 1,nodes,codes,code);
    
    char *c = (char*) malloc(256*sizeof(char));
    c[0] = 0;
    for(int i = 0; i < textSize; i++){
        int aux = v[(int)text[i]];
        strcat(c,codes[aux]);
    }
    free(code);
    for(int i = 0; i < k; i++)
        free(codes[i]);
    return c;

}

char *decompress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
	char *message =  malloc(256*sizeof(char));
    if( textSize == 0 ){
        return message;
    }
    int k = numNodes - 1,len = 0;
    for(int i = 0; i < textSize; i++){
        if( text[i] == '0' ){
            k = nodes[k].left;
        }
        else if (text[i] == '1'){
            k = nodes[k].right;
        }
        if( nodes[k].value != 0 ){
            message[len] = nodes[k].value;
            len++;
            k = numNodes - 1;
        }
    }
    return message;
}

#endif
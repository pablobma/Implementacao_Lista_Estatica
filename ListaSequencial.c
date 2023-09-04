#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaSequencial.h"

struct lista{
   int qtd;
   struct aluno dados[MAX];
};

Lista* criar_lista(){
   Lista* li;
   li = (Lista*) malloc (sizeof(struct lista));
   if (li != NULL)
      li->qtd = 0; // Não há posições ocupadas na lista! qtd=0
   return li;
}

void liberar_lista(Lista* li){
   free(li);
}

int tamanho_lista (Lista* li) {
    if(li == NULL)
        return -1;
    else
        return li->qtd;
}

int lista_vazia(Lista *li){
    if(li == NULL)
        return -1;
    else
        return (li->qtd == 0); // Retorna 0 ou 1
}

int lista_cheia(Lista *li){
    if(li == NULL)
        return -1;
    else
        return (li->qtd == MAX); // Retorna 0 ou 1
}

int inserir_lista_inicio(Lista *li, struct aluno al){
    if (li == NULL)
        return 0;
    if(li->qtd == MAX)
        return 0;
    int i;
    for(i=li->qtd-1; i>=0; i--)
        li->dados[i+1] = li->dados[i];
    li->dados[0] = al;
    li->qtd++;
    return 1;
}

int inserir_lista_final(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    if(li->qtd == MAX)
        return 0;
    li->dados[li->qtd] = al;
    li->qtd++;
    return 1;
}

int inserir_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    if(li->qtd == MAX)
        return 0;
    int i,k = 0;
    while(i < li->qtd && li->dados[i].matricula < al.matricula)
        i++;
    for(k=li->qtd-1; k>=i; k--)
        li->dados[k+1] = li->dados[k];
    li->dados[i] = al;
    li->qtd++;
    return 1;
}

void imprimir_lista(Lista *li){
   int i;
   printf("-------------\n");
   for(i=0;i < li->qtd; i++){
      printf("Matricula: %d\n", li->dados[i].matricula);
      printf("Nome: %s\n",li->dados[i].nome);
      printf("-------------\n");
   }
}

int remover_lista_inicio(Lista *li){
    if (li == NULL)
        return 0;
    if(li->qtd == 0)
        return 0;
    int k = 0;
    for(k=0;k < li->qtd-1; k++)
        li->dados[k] = li->dados[k+1];
    li->qtd--;
    return 1;
}

int remover_lista_final(Lista *li){
    if(li == NULL)
        return 0;
    if(li->qtd == 0)
        return 0;
    li->qtd--;
    return 1;
}

int remover_lista(Lista *li, int mat){
    if (li == NULL)
        return 0;
    if(li->qtd == 0)
        return 0;
    int k,i = 0;
    while(i < li->qtd && li->dados[i].matricula != mat)
        i++;
    if(i == li->qtd) //não encontrado
        return 0;

    for(k=i; k < li->qtd-1; k++)
        li->dados[k] = li->dados[k+1];
    li->qtd--;
    return 1;
}

// IMPLEMENTAÇÕES
int busca_lista_mat(Lista* li, int matricula, struct aluno* al) {
    if(li == 0)
        return 0;
    for(int i = 0; i < li->qtd; i++) {
        if(li->dados[i].matricula == matricula) {
            *al = li->dados[i];
            return 1;
        }
    }
    return 0;
}

int inserir_nome_lista(Lista* li, char nome[50], float n1, float n2, float n3) {
    if (li == NULL)
        return 0;
    if(li->qtd >= MAX)
        return 0;

    for (int i = 0; i < li->qtd; i++) {
        if (strcmp(li->dados[i].nome, nome) == 0) {
            li->dados[i].n1 = n1;
            li->dados[i].n2 = n2;
            li->dados[i].n3 = n3;

            return 1;
        }
    }
    return 0;
}


int verificar_aprovacao(Lista* li, int matricula) {
    struct aluno al;
    if(busca_lista_mat(li, matricula, &al)) {
        float media_aluno = (al.n1 + al.n2 + al.n3)/3.0;

        printf("Matricula: %d\n", al.matricula);
        printf("Nome: %s\n", al.nome);
        printf("Media: %.2f", media_aluno);

        if(media_aluno >= 7.0)
            printf("APROVADO!\n");
        else if(media_aluno >= 5.0 && media_aluno <= 7.0)
            printf("PROVA FINAL\n");
        else
            printf("REPROVADO\n");

        return 1;
    } else{
        printf("Aluno nao matriculado!\n");
        return 0;
    }
}

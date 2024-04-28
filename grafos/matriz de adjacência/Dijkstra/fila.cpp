#include "fila.hpp"

int inicializar(t_fila *f)
{
    f->inicio = NULL;
    f->final = NULL;

    return SUCESSO;
}

int enfileirar(int v, t_fila *f)
{
    t_apontador novo = (t_apontador)malloc(sizeof(t_no));
    if (novo == NULL) {
        return CHEIA;
    }

    novo->valor = v;
    novo->proximo = NULL; // Novo elemento será o último, então não tem próximo

    if (f->final != NULL) {
        f->final->proximo = novo; // Faz o antigo "final" apontar para o novo nó
    }
    f->final = novo; // Atualiza o "final" para ser o novo nó

    if (f->inicio == NULL) {
        f->inicio = novo; // Se a fila estava vazia, "inicio" também aponta para o novo nó
    }

    return SUCESSO;
}

int desenfileirar(t_fila *f)
{
    if(vazia(f)){
        return VAZIA;
    }

    t_apontador aux = f->inicio;
    int valorDesenfileirado = aux->valor;
    f->inicio = aux->proximo;
    if(aux->proximo == NULL){
        f->final = NULL;
    }
    free(aux);

    return valorDesenfileirado;
}

int vazia(t_fila *f)
{
    if(f->inicio == NULL && f->final == NULL){
        return 1;
    }
    return 0;
}
void inicio(t_fila *f)
{
    if(f->inicio == NULL){
        printf("NULL\n");
    }
    printf("inicio: %d\n", f->inicio->valor);
}
void final(t_fila *f)
{
    if(f->final == NULL){
        printf("NULL\n");
    }
    printf("final: %d\n", f->final->valor);
}
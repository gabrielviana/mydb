#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "mydb.h"
/* ============LISTA ENCADEADA============================================================= */
void FLVazia(TipoLista *Lista)
{ Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Primeiro;
  Lista -> Primeiro -> Prox = NULL;
}

short Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo); }

void InsereL(TipoItem x, TipoLista *Lista)
{ Lista->Ultimo->Prox = (TipoCelula *)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox; Lista->Ultimo->Item = x;
  Lista->Ultimo->Prox = NULL;
}

void RetiraL(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{  /* -- Obs.: o item a ser retirado o seguinte ao apontado por p -- */
  TipoApontador q;
  if (Vazia(*Lista) || p == NULL || p->Prox == NULL)
  { printf(" Erro Lista vazia ou posicao nao existe\n");
    return;
  }
  q = p->Prox; *Item = q->Item; p->Prox = q->Prox;
  if (p->Prox == NULL)
  Lista->Ultimo = p;
  free(q);
}
/* ==================================  HASH  ======================================= */
void GeraPesos(unsigned int p[256])
{
    int i;
    for(i=0; i<256; i++){
        p[i] = (unsigned int)rand();
        //printf("%d\n",p[i]);
    }

}

int h(char Chave[], unsigned int p[])
{
    int i,r;
    unsigned int Soma = 0;
    int comp = strlen(Chave);
    for ( i = 0; i < comp; i ++)
        Soma += (unsigned int)Chave[i] * p[i];
    r = (int)Soma%TAMHASH;
    return r;
}
void Inicializa(TipoLista T[TAMHASH])
{
	int i;
	for(i=0;i<TAMHASH; i++) FLVazia(&T[i]);
}

void Insere(TipoItem x, unsigned int p[],  TipoLista T[])
{
    unsigned int i=h(x.Chave,p);
	InsereL(x, &T[i]);
	//printf("--%d\n",i);
}


TipoApontador PesquisaR(TipoItem it, unsigned int p[], TipoLista T[])
{ /* Obs.: TipoApontador de retorno aponta para o item anterior da lista */
  unsigned int i;
  TipoApontador Ap;
  i = h(it.Chave, p);
  if (Vazia(T[i])) return NULL;  /* Pesquisa sem sucesso */
  else
  { Ap = T[i].Primeiro;
    while (Ap->Prox != NULL && it.chaveReg != Ap->Prox->Item.chaveReg)
      Ap = Ap->Prox;

    if (it.chaveReg ==Ap->Prox->Item.chaveReg)
    return Ap;
    else return NULL;  /* Pesquisa sem sucesso */
  }
}
void Retira(TipoItem x , unsigned int p[],  TipoLista T[])
{
	TipoApontador Ap;
	Ap = PesquisaR(x, p, T) ;
	if (Ap == NULL)
	printf("Registro nao esta presente\n");
	else RetiraL(Ap, &T[h(x .Chave, p)],&x );
	//printf("retira %d\n",Ap->Prox->Item.chaveReg);
}
void Imp(TipoLista Lista)
{ TipoApontador Aux;
  Aux = Lista.Primeiro->Prox;
  while (Aux != NULL)
    { printf("%d ",Aux->Item.chaveReg);
      Aux = Aux->Prox;
    }
}

void Imprime(TipoLista Tabela[])
{ int i;
  for (i = 0; i < TAMHASH; i++)
    { printf("%d: ", i);
      if (!Vazia(Tabela[i]))
      Imp(Tabela[i]);
      putchar('\t');
    }
}

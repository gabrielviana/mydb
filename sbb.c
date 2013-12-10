#include <sys/time.h>
#include<stdlib.h>
#include<stdio.h>
#include "sbb.h"

void EE(TipoApont *Ap)
{ TipoApont Ap1;
  Ap1 = (*Ap)->Esq; (*Ap)->Esq = Ap1->Dir; Ap1->Dir = *Ap;
  Ap1->BitE = Vertical; (*Ap)->BitE = Vertical; *Ap = Ap1;
}
void ED(TipoApont *Ap)
{ TipoApont Ap1, Ap2;
  Ap1 = (*Ap)->Esq; Ap2 = Ap1->Dir; Ap1->BitD = Vertical;
  (*Ap)->BitE = Vertical; Ap1->Dir = Ap2->Esq; Ap2->Esq = Ap1;
  (*Ap)->Esq = Ap2->Dir; Ap2->Dir = *Ap; *Ap = Ap2;
}
void DD(TipoApont *Ap)
{ TipoApont Ap1;
  Ap1 = (*Ap)->Dir; (*Ap)->Dir = Ap1->Esq; Ap1->Esq = *Ap;
  Ap1->BitD = Vertical; (*Ap)->BitD = Vertical; *Ap = Ap1;
}
void DE(TipoApont *Ap)
{ TipoApont Ap1, Ap2;
  Ap1 = (*Ap)->Dir; Ap2 = Ap1->Esq; Ap1->BitE = Vertical;
  (*Ap)->BitD = Vertical; Ap1->Esq = Ap2->Dir; Ap2->Dir = Ap1;
  (*Ap)->Dir = Ap2->Esq; Ap2->Esq = *Ap; *Ap = Ap2;
}

void IInsere(TipoReg x, TipoApont *Ap,TipoInclinacao *IAp, short *Fim)
{ if (*Ap == NULL)
  { *Ap = (TipoApont)malloc(sizeof(TipoNo));
    *IAp = Horizontal;  (*Ap)->Reg = x;
    (*Ap)->BitE = Vertical;  (*Ap)->BitD = Vertical;
    (*Ap)->Esq = NULL; (*Ap)->Dir = NULL; *Fim = FALSE;
    return;
  }
  if (x.Chave < (*Ap)->Reg.Chave)
  { IInsere(x, &(*Ap)->Esq, &(*Ap)->BitE, Fim);
    if (*Fim) return;
    if ((*Ap)->BitE != Horizontal) { *Fim = TRUE; return; }
    if ((*Ap)->Esq->BitE == Horizontal)
    { EE(Ap); *IAp = Horizontal; return; }
    if ((*Ap)->Esq->BitD == Horizontal) { ED(Ap); *IAp = Horizontal; }
    return;
  }
  //COMPARA플O AQUI
  if (x.Chave <= (*Ap)->Reg.Chave)
  { printf("Erro: Chave ja esta na arvore\n");
    *Fim = TRUE;
    return;
  }
  IInsere(x, &(*Ap)->Dir, &(*Ap)->BitD, Fim);
  if (*Fim) return;
  if ((*Ap)->BitD != Horizontal) { *Fim = TRUE;  return; }
  if ((*Ap)->Dir->BitD == Horizontal)
  { DD(Ap); *IAp = Horizontal; return;}
  if ((*Ap)->Dir->BitE == Horizontal) { DE(Ap); *IAp = Horizontal; }
}

void SbbInsere(TipoReg x, TipoApont *Ap)
{ short Fim;  TipoInclinacao IAp;
  IInsere(x, Ap, &IAp, &Fim);
}

void SbbInicializa(TipoApont *Dicionario)
{ *Dicionario = NULL; }

void EsqCurto(TipoApont *Ap, short *Fim)
{ /* Folha esquerda retirada => arvore curta na altura esquerda */
  TipoApont Ap1;
  if ((*Ap)->BitE == Horizontal)
  { (*Ap)->BitE = Vertical; *Fim = TRUE; return; }
  if ((*Ap)->BitD == Horizontal)
  { Ap1 = (*Ap)->Dir; (*Ap)->Dir = Ap1->Esq; Ap1->Esq = *Ap; *Ap = Ap1;
    if ((*Ap)->Esq->Dir->BitE == Horizontal)
    { DE(&(*Ap)->Esq); (*Ap)->BitE = Horizontal;}
    else if ((*Ap)->Esq->Dir->BitD == Horizontal)
         { DD(&(*Ap)->Esq); (*Ap)->BitE = Horizontal; }
    *Fim = TRUE;
    return;
  }
  (*Ap)->BitD = Horizontal;
  if ((*Ap)->Dir->BitE == Horizontal) { DE(Ap); *Fim = TRUE; return; }
  if ((*Ap)->Dir->BitD == Horizontal) {  DD(Ap); *Fim = TRUE; }
}

void DirCurto(TipoApont *Ap, short *Fim)
{ /* Folha direita retirada => arvore curta na altura direita */
  TipoApont Ap1;
  if ((*Ap)->BitD == Horizontal)
  { (*Ap)->BitD = Vertical; *Fim = TRUE; return; }
  if ((*Ap)->BitE == Horizontal)
  { Ap1 = (*Ap)->Esq; (*Ap)->Esq = Ap1->Dir; Ap1->Dir = *Ap; *Ap = Ap1;
    if ((*Ap)->Dir->Esq->BitD == Horizontal)
    { ED(&(*Ap)->Dir); (*Ap)->BitD = Horizontal; }
    else if ((*Ap)->Dir->Esq->BitE == Horizontal)
         { EE(&(*Ap)->Dir); (*Ap)->BitD = Horizontal;}
    *Fim = TRUE;
    return;
  }
  (*Ap)->BitE = Horizontal;
  if ((*Ap)->Esq->BitD == Horizontal) { ED(Ap); *Fim = TRUE; return; }
  if ((*Ap)->Esq->BitE == Horizontal) { EE(Ap); *Fim = TRUE; }
}

void Antecessor(TipoApont q, TipoApont *r, short *Fim)
{ if ((*r)->Dir != NULL)
  { Antecessor(q, &(*r)->Dir, Fim);
    if (!*Fim) DirCurto(r, Fim);
    return;
  }
  q->Reg = (*r)->Reg; q = *r; *r = (*r)->Esq; free(q);
  if (*r != NULL) *Fim = TRUE;
}

void IRetira(TipoReg x, TipoApont *Ap, short *Fim)
{ TipoNo *Aux;
  if (*Ap == NULL)
  { printf("Chave nao esta na arvore\n"); *Fim = TRUE; return; }
 //COMPARA플O AQUI
  if (x.Chave < (*Ap)->Reg.Chave)
  { IRetira(x, &(*Ap)->Esq, Fim);
    if (!*Fim) EsqCurto(Ap, Fim);
    return;
  }//COMPARA플O AQUI
  if (x.Chave > (*Ap)->Reg.Chave)
  { IRetira(x, &(*Ap)->Dir, Fim);
    if (!*Fim) DirCurto(Ap, Fim);
    return;
  }
  *Fim = FALSE; Aux = *Ap;
  if (Aux->Dir == NULL)
  { *Ap = Aux->Esq;  free(Aux);
    if (*Ap != NULL) *Fim = TRUE;
    return;
  }
  if (Aux->Esq == NULL)
  { *Ap = Aux->Dir; free(Aux);
    if (*Ap != NULL) *Fim = TRUE;
    return;
  }
  Antecessor(Aux, &Aux->Esq, Fim);
  if (!*Fim) EsqCurto(Ap, Fim); /* Encontrou chave */
}

void SbbRetira(TipoReg x, TipoApont *Ap)
{ short Fim;
  IRetira(x, Ap, &Fim);
}
/*
void SbbPesquisa(TipoReg *x, TipoApont *p)
{ if (*p == NULL)
  { printf("Erro: Registro nao esta presente na arvore\n");
    return;
  }
  //COMPARA플O AQUI
  if (x->Chave < (*p)->Reg.Chave)
  { SbbPesquisa(x, &(*p)->Esq);
    return;
  }
  //COMPARA플O AQUI
  if (x->Chave > (*p)->Reg.Chave)
  SbbPesquisa(x, &(*p)->Dir);
  else
  *x = (*p)->Reg;
}
*/
void Testa1(TipoApont p, int nivel, int *NivelFolhas, short *PrimeiraFolha)
{ if (p == NULL)
  return;
  if (*PrimeiraFolha)
  if (*NivelFolhas < nivel) *NivelFolhas = nivel;
  if (p->Esq == NULL && p->Dir == NULL)
  { if (*PrimeiraFolha == TRUE)
    *PrimeiraFolha = FALSE;
    else
    { if (nivel != *NivelFolhas)
      { printf("Erro: Folhas em niveis diferentes\n"); exit(1); }
    }
  }
  if (p->BitE == Horizontal)
  Testa1(p->Esq, nivel, NivelFolhas, PrimeiraFolha);
  else
  Testa1(p->Esq, nivel + 1, NivelFolhas, PrimeiraFolha);
  if (p->BitD == Horizontal)
  Testa1(p->Dir, nivel, NivelFolhas, PrimeiraFolha);
  else
  Testa1(p->Dir, nivel + 1, NivelFolhas, PrimeiraFolha);
}

void Testa2(TipoApont p, int *NivelFolhas, short *PrimeiraFolha)
{ if (p == NULL)
  return;
  if (p->Esq != NULL)//COMPARA플O AQUI
  { if (p->Reg.Chave < p->Esq->Reg.Chave)
    { printf("Erro: %d < que filho a esquerda \n", p->Reg.Chave);
      exit(1);
    }
    Testa2(p->Esq, NivelFolhas, PrimeiraFolha);
  }
  if (p->Dir == NULL)
  return;//COMPARA플O AQUI
  if (p->Reg.Chave > p->Dir->Reg.Chave)
  { printf("Erro: %d > que filho a direita \n", p->Reg.Chave);
    exit(1);
  }
  Testa2(p->Dir, NivelFolhas, PrimeiraFolha);
}

void Testa(TipoApont Arvore)
{ int NivelFolhas = 0;
  short PrimeiraFolha = TRUE;
  Testa1(Arvore, 1, &NivelFolhas, &PrimeiraFolha);
  Testa2(Arvore, &NivelFolhas, &PrimeiraFolha);
}

double rand0a1() {
  double resultado = (double) rand() / RAND_MAX; /* Dividir pelo maior inteiro */
  if (resultado > 1.0) resultado = 1.0;
  return resultado;
}

void Permut(int *A, int n)
{ /* Obtem permutacao randomica dos numeros entre 1 e n */
  int  i, j, b;
  for (i = n; i >= 1; i--)
  { j = (int)(i * rand0a1()  + 1); b = A[i - 1];
    A[i - 1] = A[j - 1]; A[j - 1] = b;
  }
}


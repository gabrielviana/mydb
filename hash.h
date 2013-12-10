#define TAMHASH 443

typedef int TipoChave;

typedef struct {
  char Chave[255];
  unsigned int chaveReg;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro,Ultimo;
} TipoLista;

int h(char Chave[], unsigned int p[]);
short Vazia(TipoLista Lista);
void GeraPesos(unsigned int p[256]);
void Inicializa(TipoLista T[TAMHASH]);
void Insere(TipoItem x , unsigned int p[],  TipoLista T[]);
void Retira(TipoItem x , unsigned int p[],  TipoLista T[]);
void Imprime(TipoLista Tabela[]);

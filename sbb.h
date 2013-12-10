#define TRUE  1
#define FALSE 0
#define MAX 10
typedef struct TipoReg{
  /* outros componentes */
  unsigned int Chave;
  unsigned int chaveReg;
} TipoReg;
typedef enum {
  Vertical, Horizontal
} TipoInclinacao;
typedef struct TipoNo* TipoApont;
typedef struct TipoNo {
  TipoReg Reg;
  TipoApont Esq, Dir;
  TipoInclinacao BitE, BitD;
} TipoNo;

void SbbInsere(TipoReg x, TipoApont *Ap);
void SbbInicializa(TipoApont *Dicionario);
void SbbRetira(TipoReg x, TipoApont *Ap);
void SbbPesquisa(TipoReg *x, TipoApont *p);
void Testa(TipoApont Arvore);


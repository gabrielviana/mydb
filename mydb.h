#include "hash.h"
#include "sbb.h"
typedef struct Registro
{
    unsigned int chave;
    char nome[60];
    char rua[255];
    char bairro[100];
    char cidade[60];
    char estado[3];
    char telefone[14];
    char email[100];
}Registro;
FILE* cria_arquivo(char* nome, char* op);
void separa_comando(char comando[],char funcao[],char detalhes[]);
void Insert(char detalhes[],unsigned int p[], TipoLista N[],TipoLista R[],TipoLista B[],TipoLista C[],TipoLista E[],TipoLista EM[],TipoApont *apChave,TipoApont *apTel);
void Select(char detalhes[],unsigned int p[], TipoLista N[],TipoLista R[],TipoLista B[],TipoLista C[],TipoLista E[],TipoLista EM[],TipoApont *apChave,TipoApont *apTel);
void Update(char detalhes[],unsigned int p[], TipoLista N[],TipoLista R[],TipoLista B[],TipoLista C[],TipoLista E[],TipoLista EM[],TipoApont *apChave,TipoApont *apTel,int del);
void Delete(char detalhes[],unsigned int p[], TipoLista N[],TipoLista R[],TipoLista B[],TipoLista C[],TipoLista E[],TipoLista EM[],TipoApont *apChave,TipoApont *apTel);;
int Pesquisa(char Ch[],unsigned int p[], TipoLista T[], Registro regs[]);
void constroiSbb();
void constroiHash();

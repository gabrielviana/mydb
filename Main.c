#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mydb.h"
#define TAMHASH 443
int main(){
    int ctrl = 0;
    char comando[255];
    char detalhes[255];
    char funcao[10];
    unsigned int p[256];
    GeraPesos(p);

    TipoLista hashnome[TAMHASH];Inicializa(hashnome);
    constroiHash(p,hashnome,"nome");
    TipoLista hashrua[TAMHASH];Inicializa(hashrua);
     constroiHash(p,hashrua,"rua");
    TipoLista hashbairro[TAMHASH];Inicializa(hashbairro);
     constroiHash(p,hashbairro,"bairro");
    TipoLista hashcidade[TAMHASH];Inicializa(hashcidade);
     constroiHash(p,hashcidade,"cidade");
    TipoLista hashestado[TAMHASH];Inicializa(hashestado);
     constroiHash(p,hashestado,"estado");
    TipoLista hashemail[TAMHASH];Inicializa(hashemail);
     constroiHash(p,hashemail,"email");

     TipoApont SbbChave; SbbInicializa(&SbbChave);
     constroiSbb(&SbbChave,"chave");

     TipoApont SbbTelefone; SbbInicializa(&SbbTelefone);
     constroiSbb(&SbbTelefone,"telefone");

     //Imprime(hashestado);

    //Pesquisa("centro",p,hashbairro,campos_d);

    printf("Instituto Federal do Norte de Minas Gerais\n");
     printf("Trabalho final da diciplina Algoritmos e estrutura de dados II \n");
     printf("Professor: Renato Cota \n");
     printf("Academicos: Endi Daniel Coelho Silva, Gabriel Silveira V. de Carvalho\n");

    printf("\n   -----------------------------MyDB-----------------------------   \n");
    while(ctrl == 0){//LOOP PRINCIPAL
        comando[0]='\0';
        detalhes[0]='\0';
        funcao[0]='\0';
        printf("\nmydb> ");gets(comando);
        separa_comando(comando,funcao,detalhes);
        if(strcmp(funcao,"select")==0){
           Select(detalhes,p,hashnome,hashrua,hashbairro,hashcidade,hashestado,hashemail,&SbbChave,&SbbTelefone);
        }else if(strcmp(funcao,"update")==0){
           Update(detalhes,p,hashnome,hashrua,hashbairro,hashcidade,hashestado,hashemail,&SbbChave,&SbbTelefone,0);
        }else if(strcmp(funcao,"insert")==0){
           Insert(detalhes,p,hashnome,hashrua,hashbairro,hashcidade,hashestado,hashemail,&SbbChave,&SbbTelefone);
        }else if(strcmp(funcao,"delete")==0){
           Delete(detalhes,p,hashnome,hashrua,hashbairro,hashcidade,hashestado,hashemail,&SbbChave,&SbbTelefone);;
        }else if(strcmp(comando,"sair")==0){
           ctrl = 1;
           printf("Tchau\n");
           getch();
        }else if(strcmp(comando,"")==0){
           //printf("\n");
        }else{
            printf("Erro de sintaxe!\n\n");
        }
    }
    return 0;
}

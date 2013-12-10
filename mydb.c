#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "mydb.h"
//QuickSort para Caracteres
void charquickSort(Registro vetor[],char items[][255], int left, int right)
{
  int i, j;
  Registro tmp;
  char *x;
  char temp[255];

  i = left;
  j = right;
  x = items[(left+right)/2];

  do {
    while((strcmp(items[i],x) < 0) && (i < right)) {
       i++;
    }
    while((strcmp(items[j],x) > 0) && (j > left)) {
        j--;
    }
    if(i <= j) {
      strcpy(temp, items[i]);
      strcpy(items[i], items[j]);
      strcpy(items[j], temp);

      tmp=vetor[i];
      vetor[i]=vetor[j];
      vetor[j]=tmp;



      i++;
      j--;
   }
  } while(i <= j);

  if(left < j) {
     charquickSort(vetor,items, left, j);
  }
  if(i < right) {
     charquickSort(vetor,items, i, right);
  }
}

void quickSortMain(Registro vetor[], char items[][255], int count)
{
  charquickSort(vetor, items, 0, count-1);
}

// ----------- QuickSort Para Numeros------------------------
void swap(int* a, int* b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
void swap2(Registro a[],int i,int j)
{
    Registro tmp;
      tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;

}

//-----------------------------------------------------------

int partition(Registro vec2[], int vec[], int left, int right)
{
    int i, j;

    i = left;
    for (j = left + 1; j <= right; ++j)
    {
        if (vec[j] < vec[left])
        {
            ++i;
            swap(&vec[i], &vec[j]);
            swap2(vec2,i,j);
        }
    }
    swap(&vec[left], &vec[i]);

    swap2(vec2,left,i);

    return i;
}
//-----------------------------------------------------------

void quickSort(Registro vec2[],int vec[], int left, int right)
{
    int r;

    if (right > left)
    {
        r = partition(vec2,vec, left, right);
        quickSort(vec2,vec, left, r - 1);
        quickSort(vec2,vec, r + 1, right);
    }

}
//Funçoes MYDB--------------------------------------------------------------------
/*     Essa função separa o tipo do comando das suas especificações    */
void separa_comando(char comando[],char funcao[],char detalhes[]){
    int i,j=0,k=0;
    for(i=0;i<strlen(comando);i++){
        if(comando[i]==' ' && j==0){
           funcao[i]='\0';
           j++;
        }else if(j==0){
           funcao[i]=comando[i];
        }
        if(j!=0){
           detalhes[k]=comando[i];
           detalhes[k+1]='\0';
            k++;
        }
    }
}
//cria ponteiro para arquivo e ou abre
FILE* cria_arquivo(char* nome, char* op)
{
    FILE *fp;
    fp=fopen(nome,op);
    if(!fp)
    {
      return NULL;
    }
    return fp;
}
//Essa função separa os detalhes para a fução INSERT
int separa_insert(Registro *r,char detalhes[]){
 int i,j=0,k=0,ctrl=0,t=0;
 r->nome[0]='\0';
 r->rua[0]='\0';
 r->bairro[0]='\0';
 r->cidade[0]='\0';
 r->estado[0]='\0';
 r->telefone[0]='\0';
 r->email[0]='\0';

    if(detalhes[strlen(detalhes)-1]!=';')
       return 0;
    for(i=0;i<strlen(detalhes);i++){
        if(detalhes[i]=='"'){
            t++;
            if(ctrl==0)
                ctrl=1;
            else{
                ctrl=0;
                k=0;
                j++;
            }
        }
        if(detalhes[i]==',' && j==5){
            if(ctrl==0)
                ctrl=1;
            else{
               ctrl=0;
                k=0;
                j++;
            }
        }
        if(ctrl == 1 && j==0 && detalhes[i]!='"'){
            r->nome[k]=detalhes[i];
            r->nome[k+1]='\0';
            k++;
        }
         else if(ctrl == 1 && j==1 && detalhes[i]!='"'){
            r->rua[k]=detalhes[i];
            r->rua[k+1]='\0';
            k++;
        }
         else if(ctrl == 1 && j==2 && detalhes[i]!='"'){
            r->bairro[k]=detalhes[i];
            r->bairro[k+1]='\0';
            k++;
        }
         else  if(ctrl == 1 && j==3 && detalhes[i]!='"'){
            r->cidade[k]=detalhes[i];
            r->cidade[k+1]='\0';
            k++;
        }
          else  if(ctrl == 1 && j==4 && detalhes[i]!='"' && k<2){
            r->estado[k]=detalhes[i];
            r->estado[k+1]='\0';
            k++;
        }
         else  if(ctrl == 1 && j==5 && detalhes[i]!='"'&& detalhes[i]!=','){
            r->telefone[k]=detalhes[i];
            r->telefone[k+1]='\0';
            //printf("%c\n",r->telefone[k]);
            k++;
        }
         else  if(ctrl == 1 && j==6 && detalhes[i]!='"'){
            r->email[k]=detalhes[i];
            r->email[k+1]='\0';
            k++;
        }
    }
    if(t%2!=0)
        return 0;
return 1;
}/*   fim separa_insert()   */
// Esta função devolve a chave do ultimo registro
int ult_reg(){
FILE *fp = cria_arquivo("DB","rb");
Registro t;
unsigned int a=0;
    if(fp!=NULL)
    {
        int num;
       fseek(fp, 0*sizeof(Registro), SEEK_END);
       num = ftell(fp)/sizeof(Registro);

        if(num==0)
            a=0;
         else
        {
                fseek(fp,-(long) sizeof(Registro), SEEK_END);
                fread(&t,sizeof(Registro),1,fp);
                 a=t.chave;
        }
    }
    fclose(fp);
    return a;
}
//converte o telefone para inteiro
unsigned int tel_para_int(char tel[]){
unsigned int i,j=0;
char aux[strlen(tel)];
for(i=0;i<strlen(tel);i++){
    if(isdigit(tel[i])&&tel[i]!='('&&tel[i]!=')'&&tel[i]!='-'){
        aux[j]=tel[i];
        aux[j+1]='\0';
        j++;
    }
}
i = (unsigned int)atoi(aux);
//printf("%d--\n",i);
return i;
}

void Insert(char detalhes[],unsigned int p[], TipoLista N[],TipoLista R[],TipoLista B[],TipoLista C[],TipoLista E[],TipoLista EM[],TipoApont *apChave,TipoApont *apTel)
{
    int erro,i=0;
   Registro r;
   TipoItem it;
    TipoReg reg;
    Registro regs[15];
   FILE *fp;
   erro=separa_insert(&r,detalhes);
   if(erro == 0){
    printf("Erro de sintaxe!\n");
   return;
   }
   else{
        if(strlen(r.nome)==0||strcmp(r.nome," ")==0||strcmp(r.nome,"  ")==0){
            printf("o campo nome nao pode ser nulo.\n");
        }else if(strlen(r.telefone)==0||strcmp(r.telefone," ")==0||strcmp(r.telefone,"  ")==0){
         printf("o campo telefone nao pode ser nulo.\n");
        }
        else{
                i=Pesquisa(r.nome,p,N,regs);
                printf("%d\n",i);
                if(i==0){
                                     r.chave = ult_reg()+1;
                fp = cria_arquivo("DB","ab");
                if(fp!=NULL) {
                   fwrite(&r, sizeof(Registro), 1, fp);
                   if(ferror(fp)) printf("\nErro ao inserir\n");
                   else printf("Dados inseridos com sucesso.\n");
                    fclose(fp);

                    it.chaveReg = r.chave;

                    strcpy(it.Chave,r.nome);
                    Insere(it,p,N);

                     strcpy(it.Chave,r.rua);
                    Insere(it,p,R);

                     strcpy(it.Chave,r.bairro);
                    Insere(it,p,B);

                     strcpy(it.Chave,r.cidade);
                    Insere(it,p,C);

                     strcpy(it.Chave,r.estado);
                    Insere(it,p,E);

                     strcpy(it.Chave,r.email);
                    Insere(it,p,EM);

                    reg.chaveReg = r.chave;

                    reg.Chave = r.chave;
                    SbbInsere(reg,apChave);

                    reg.Chave = tel_para_int(r.telefone);
                    SbbInsere(reg,apTel);
                    }
                }else{
                printf("Este este nome já está em usado por outro usuário\n.");
                }

        }
       //teste printf("%d",r.chave);
    }
}
//função para separar os detalhes da função SELECT
int separa_select(char detalhes[],char chave[],char valor[],char campos_d[7][10],char orderby[10],char camp[10]){
    int i,j=0,k=0,ctrl=0;
    char campos[80];
    char where[10];
    char aux1[10];
    char aux2[10];

    orderby[0]='\0';
    char chave_valor[100];
    campos[0]='\0';
    campos_d[0][0]='\0';
    campos_d[1][0]='\0';
    campos_d[2][0]='\0';
    campos_d[3][0]='\0';
    campos_d[4][0]='\0';
    campos_d[5][0]='\0';
    campos_d[6][0]='\0';
    where[0]='\0';
    aux1[0]='\0';
    aux2[0]='\0';
    chave_valor[0]='\0';
    for(i=0;i<strlen(detalhes);i++){
        if(detalhes[i]==' ' && (ctrl==0|| detalhes[i]==';')){
              k=0;
              ctrl=0;
              if(i!=0)j++;
        }
        if(detalhes[i]=='='&&j==2){
            ctrl=1;
        }else if(detalhes[i]=='"'&&detalhes[i+1]==' '&&j==2&&ctrl==1){
            ctrl=0;
        }

     if(j==0 && detalhes[i]!=' ' && detalhes[i]!=';'){
         campos[k]=detalhes[i];
         campos[k+1]='\0';
         k++;
     }else if(j==1 && detalhes[i]!=' ' && detalhes[i]!=';'){
         where[k]=detalhes[i];
         where[k+1]='\0';
         k++;
     }else if(j==2 && detalhes[i]!=' ' && detalhes[i]!=';'){
         chave_valor[k]=detalhes[i];
         chave_valor[k+1]='\0';
         k++;
     }else if(j==2 && ctrl==1 && detalhes[i]!=';'){
         chave_valor[k]=detalhes[i];
         chave_valor[k+1]='\0';
         k++;
     }else if(j==3 && detalhes[i]!=' ' && detalhes[i]!=';'){
         aux1[k]=detalhes[i];
         aux1[k+1]='\0';
         k++;
     }
     else if(j==4 && detalhes[i]!=' ' && detalhes[i]!=';'){
         aux2[k]=detalhes[i];
         aux2[k+1]='\0';
         k++;
     }else if(j==5 && detalhes[i]!=' ' && detalhes[i]!=';'){
         camp[k]=detalhes[i];
         camp[k+1]='\0';
         k++;
     }
     else if(j==6 && detalhes[i]!=' ' && detalhes[i]!=';'){
         orderby[k]=detalhes[i];
         orderby[k+1]='\0';
         k++;
     }
     if(detalhes[strlen(detalhes)-1]!=';'){
        return 0;
     }
    }//fim for
//printf("chave valor %s--\n\n",chave_valor);
    j=0;
    k=0;
    if(strlen(campos)!=0){
        for(i=0;i<strlen(campos);i++){
            if(campos[i]==','){
                k=0;
                j++;
            }
            if(j==0 && campos[i]!=',' && campos[i]!=' '){
                    if(campos[i]=='w')
                    return 0;
                 campos_d[j][k]=campos[i];
                 campos_d[j][k+1]='\0';
                 k++;
            }else if(j==1 && campos[i]!=',' && campos[i]!=' '){
                 campos_d[j][k]=campos[i];
                 campos_d[j][k+1]='\0';
                 k++;
            }else if(j==2 && campos[i]!=',' && campos[i]!=' '){
                 campos_d[j][k]=campos[i];
                 campos_d[j][k+1]='\0';
                 k++;
            }else if(j==3 && campos[i]!=',' && campos[i]!=' '){
                 campos_d[j][k]=campos[i];
                 campos_d[j][k+1]='\0';
                 k++;
            }else if(j==4 && campos[i]!=',' && campos[i]!=' '){
                 campos_d[j][k]=campos[i];
                 campos_d[j][k+1]='\0';
                 k++;
            }else if(j==5 && campos[i]!=',' && campos[i]!=' '){
                 campos_d[j][k]=campos[i];
                 campos_d[j][k+1]='\0';
                 k++;
            }else if(j==6 && campos[i]!=',' && campos[i]!=' '){
                 campos_d[j][k]=campos[i];
                 campos_d[j][k+1]='\0';
                 k++;
            }
        }//Fim FOR
    }else//fim if campos
        return 0;
    	if(strcmp(where,"where")==0){
			if(strlen(chave_valor)!=0){
			   j=0;
			   k=0;
			   for(i=0;i<strlen(chave_valor);i++){
				   if(chave_valor[i]=='='){
					 k=0;
					 j++;
				   }
				   if(j==0 && chave_valor[i]!='='){
					 chave[k]=chave_valor[i];
					 chave[k+1]='\0';
					 k++;
				   } else if(j==1 && chave_valor[i]!='='){
					 valor[k]=chave_valor[i];
					 valor[k+1]='\0';
					 k++;
				   }
			   }//Fim for
			   if(strlen(chave)==0||strlen(valor)==0)
				return 0;
			}
		    if(strcmp(aux1,"")&&strcmp(aux2,"")){
       //             printf("Teste\n");
                        if(strcmp(aux1,"order")==0&&strcmp(aux2,"by")==0){
                        if(strcmp(orderby,"DESC")&&strcmp(orderby,"ASC"))
                        return 0;

                    }else{ return 0;}
                }

		 }else if(strcmp(where,"order")==0 &&strcmp(chave_valor,"by")==0){
             if(strcmp(aux2,"DESC")==0){
                orderby[0]='D';
                orderby[1]='E';
                orderby[2]='S';
                orderby[3]='C';
                orderby[4]='\0';
                strcpy(camp,aux1);
             }else if(strcmp(aux2,"ASC")==0){
                orderby[0]='A';
                orderby[1]='S';
                orderby[2]='C';
                orderby[3]='\0';
                strcpy(camp,aux1);
            // printf("TEste %s\n",orderby);
             }else{
             return 0;
             }
                return 2;
                }else if(strcmp(where,"")==0){//&&strcmp(campos,"*")==0){
                 return 2;
                }else{
                return 0;
                }
       if(valor[0]!='"'||valor[strlen(valor)-1]!='"'){
                if(strcmp(chave,"chave")!=0&&strcmp(chave,"telefone")!=0){
                    //printf("teste-%s-\n",chave);
                    return 0;
                }
			}else{
            	for(i=0;i<strlen(valor);i++)
            {
                if(i==strlen(valor)-2)
                {
                   valor[i] = '\0';
                   break;
                }
                else{
                   valor[i]=valor[i+1];
                }
            }
		}
//printf("%s\n---",valor);
    return 1;
}//Fim função SEPARA_SELECT
//Esta função verifica se os campos digitados pelo usuário existem ou não
int verifica_campos(char campos_d[7][10],char chave[],char valor[]){
    int i,ctrl=0,aux=0;
    for(i=0;i<7;i++){
            ctrl=0;
        if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"nome")==0){
            ctrl++;
        }else if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"rua")==0){
            ctrl++;
        }else if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"bairro")==0){
            ctrl++;
        }else if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"cidade")==0){
            ctrl++;
        }else if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"estado")==0){
            ctrl++;
        }else if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"telefone")==0){
            ctrl++;
        }else if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"email")==0){
            ctrl++;
        }else if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"chave")==0){
            ctrl++;
        }else if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"*")==0){
            ctrl++;
            aux++;
        }
        if(ctrl==0&&strlen(campos_d[i])!=0){
            printf("Erro de sintaxe!\n Os campos digitados nao existem.\n");
            return 0;
        }
    }
    if(aux==0){
         ctrl=0;
         if(strcmp(chave,"nome")==0){
            ctrl++;
        }else if(strcmp(chave,"rua")==0){
            ctrl++;
        }else if(strcmp(chave,"bairro")==0){
            ctrl++;
        }else if(strcmp(chave,"cidade")==0){
            ctrl++;
        }else if(strcmp(chave,"estado")==0){
            ctrl++;
        }else if(strcmp(chave,"telefone")==0){
            ctrl++;
        }else if(strcmp(chave,"chave")==0){
            ctrl++;
        }
         if(ctrl==0){
            printf("Erro de sintaxe!\n A chave usada nao existe.\n");
            return 0;
        }
    }

        return 1;
}
//Essa função marca 1 nos campos que iram ser mostrados no função constroi tabela
int mostrar_campos(char campos_d[7][10],int *nome,int *rua,int *bairro,int *cidade,int *estado,int *telefone,int *email,int *chave){
        int i;
        *nome=0;*rua=0;*bairro=0;*cidade=0;*estado=0;*telefone=0;*email=0;*chave=0;
    for(i=0;i<7;i++){
        if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"nome")==0){
            *nome=1;
        }else if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"rua")==0){

            *rua=1;
        }else if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"bairro")==0){

            *bairro=1;
        }else if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"cidade")==0){

            *cidade=1;
        }else if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"estado")==0){

            *estado=1;
        }else if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"telefone")==0){

            *telefone=1;
        }else if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"email")==0){

            *email=1;
        }else if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"chave")==0){

            *chave=1;
        }if(strlen(campos_d[i])!=0&&strcmp(campos_d[i],"*")==0){
            *nome=1;
            *rua=1;
            *bairro=1;
            *cidade=1;
            *estado=1;
            *telefone=1;
            *email=1;
            *chave=1;
        }
    }
        return 1;
}
// esta função recebe um vetor de registros monta e mostra a tabela
void constroitabela(Registro regs[],int n,char campos_d[7][10],char orderby[]){
 int nome,rua,bairro,cidade,estado,telefone,email,chave,i;
 mostrar_campos(campos_d,&nome,&rua,&bairro,&cidade,&estado,&telefone,&email,&chave);

//printf("%s-\n",orderby);
if(n==0){
    printf("Nenhum registro encontrado.");
}else{
        printf("+");
                        if(chave==1)
                    printf("-------+");
                        if(nome==1)
                    printf("-------------+");
                        if(rua==1)
                    printf("------------+");
                         if(bairro==1)
                    printf("---------+");
                         if(cidade==1)
                    printf("--------+");
                         if(estado==1)
                    printf("----+");
                         if(telefone==1)
                    printf("----------+");
                         if(email==1)
                    printf("------------+");
                    printf("\n");
		///////----------------
                    printf("|");
                    if(chave==1)
                    printf(" chave |");
                        if(nome==1)
                    printf("      nome      |");
                        if(rua==1)
                    printf("   rua    |");
                         if(bairro==1)
                    printf("    bairro     |");
                         if(cidade==1)
                    printf("    cidade    |");
                         if(estado==1)
                    printf(" estado |");
                         if(telefone==1)
                    printf(" telefone |");
                         if(email==1)
                    printf("    email    |");
                    printf("\n");
                     printf("+");
                            if(chave==1)
                    printf("-------+");
                        if(nome==1)
                    printf("-------------+");
                        if(rua==1)
                    printf("------------+");
                         if(bairro==1)
                    printf("---------+");
                         if(cidade==1)
                    printf("--------+");
                         if(estado==1)
                    printf("----+");
                         if(telefone==1)
                    printf("----------+");
                         if(email==1)
                    printf("------------+");
                    printf("\n");

                    if(strcmp(orderby,"DESC")==0){
                   for(i=n-1;i>=0;i--){
                        printf("|");
                        if(chave==1)
                    printf("  %d   |",regs[i].chave);
                        if(nome==1)
                    printf(" %s |",regs[i].nome);
                        if(rua==1)
                    printf(" %s |",regs[i].rua);
                         if(bairro==1)
                    printf(" %s |",regs[i].bairro);
                         if(cidade==1)
                    printf(" %s |",regs[i].cidade);
                         if(estado==1)
                    printf(" %c%c |",regs[i].estado[0],regs[i].estado[1]);
                         if(telefone==1)
                    printf(" %s |",regs[i].telefone);
                         if(email==1)
                    printf(" %s |",regs[i].email);
                     printf("\n+");
                        if(chave==1)
                    printf("-------+");
                        if(nome==1)
                    printf("-------------+");
                        if(rua==1)
                    printf("------------+");
                         if(bairro==1)
                    printf("---------+");
                         if(cidade==1)
                    printf("--------+");
                         if(estado==1)
                    printf("----+");
                         if(telefone==1)
                    printf("----------+");
                         if(email==1)
                    printf("------------+");
                    printf("\n");

                    }
                    }else{

                      for(i =0;i<n;i++){
                            printf("|");
                          if(chave==1)
                    printf("  %d   |",regs[i].chave);
                        if(nome==1)
                    printf(" %s |",regs[i].nome);
                        if(rua==1)
                    printf(" %s |",regs[i].rua);
                         if(bairro==1)
                    printf(" %s |",regs[i].bairro);
                         if(cidade==1)
                    printf(" %s |",regs[i].cidade);
                         if(estado==1)
                    printf(" %c%c |",regs[i].estado[0],regs[i].estado[1]);
                         if(telefone==1)
                    printf(" %s |",regs[i].telefone);
                         if(email==1)
                    printf(" %s |",regs[i].email);
                     printf("\n+");
                           if(chave==1)
                    printf("-------+");
                        if(nome==1)
                    printf("-------------+");
                        if(rua==1)
                    printf("------------+");
                         if(bairro==1)
                    printf("---------+");
                         if(cidade==1)
                    printf("--------+");
                         if(estado==1)
                    printf("----+");
                         if(telefone==1)
                    printf("----------+");
                         if(email==1)
                    printf("------------+");
                    printf("\n");

                    }
                    }
                  /*  printf("+");
                           if(chave==1)
                    printf("-------+");
                        if(nome==1)
                    printf("-------------+");
                        if(rua==1)
                    printf("------------+");
                         if(bairro==1)
                    printf("---------+");
                         if(cidade==1)
                    printf("--------+");
                         if(estado==1)
                    printf("----+");
                         if(telefone==1)
                    printf("----------+");
                         if(email==1)
                    printf("------------+");
                    printf("\n");*/
    }
}
// Esta função preenche o vetor de registros com todos os registros do arquivo
int dump(Registro regs[])
{
    int j=0;
    FILE *fp = cria_arquivo("DB","rb");
    fflush(fp);
    Registro c;
    if(fp!=NULL)
    {
      while(fread(&c,sizeof(Registro),1,fp)){
      if(ferror(fp))
      printf("Erro ao ler o arquivo");
      else {
            if(strcmp(c.nome,"")){
                regs[j]=c;
                j++;
            }
      }
      }
      fclose(fp);
    }
    return j;
}
//Esta função recebe a chave e um registro do banco e resgata este registro no arquivo
void resgata(TipoReg r,Registro regs[]){
        Registro x;
        FILE *fp = cria_arquivo("DB","rb+");
        fseek(fp,(long) (r.chaveReg - (unsigned int)1)*sizeof(Registro), SEEK_SET);
        if(fread(&x,sizeof(Registro),1,fp)==0){
           printf("Erro na base de dados");
        return;
        }
        else{
            regs[0]=x;
        }
        fclose(fp);
}


void Select(char detalhes[],unsigned int p[], TipoLista N[],TipoLista R[],TipoLista B[],TipoLista C[],TipoLista E[],TipoLista EM[],TipoApont *apChave,TipoApont *apTel){
char chave[15];
char valor[255];
char campos_d[7][10];
 char orderby[10];
 char camp[10];
int n,ctrl,j;
Registro regs[ult_reg()];
n=0;
ctrl = separa_select(detalhes,chave,valor,campos_d,orderby,camp);
//printf("%s %s %d\n",orderby,camp,ctrl);
if(ctrl==0){
    printf("Erro de sintaxe");
    return;
}else if(ctrl==1){
  // printf("%s--\n\n",camp);
    if(verifica_campos(campos_d,chave,valor)==1){
     //      printf("valor %s\n",valor);
        if(strcmp(chave,"nome")==0)
        n=Pesquisa(valor,p,N,regs);
        else if(strcmp(chave,"rua")==0)
        n=Pesquisa(valor,p,R,regs);
        else if(strcmp(chave,"bairro")==0)
        n=Pesquisa(valor,p,B,regs);
        else if(strcmp(chave,"cidade")==0)
        n=Pesquisa(valor,p,C,regs);
        else if(strcmp(chave,"estado")==0)
        n=Pesquisa(valor,p,E,regs);
        else if(strcmp(chave,"email")==0)
        n=Pesquisa(valor,p,EM,regs);
        else if(strcmp(chave,"chave")==0){
        n=1;
        TipoReg it;
        it.Chave = atoi(valor);
        SbbPesquisa(&it, apChave);
        resgata(it,regs);
        }else if(strcmp(chave,"telefone")==0){
          n=1;
        TipoReg it;
        it.Chave = tel_para_int(valor);
        SbbPesquisa(&it, apTel);
        resgata(it,regs);
        }
       // constroitabela(regs,n,campos_d);
    }
}else if(ctrl==2){
        n=dump(regs);
       // printf("--%d",n);
       // constroitabela(regs,n,campos_d);
    }
    int vetor[n];
    char vetorstring[n][255];
    if(strcmp(orderby,"")){//se o order by for diferente de nulo
                            //chama-se o quick sort para ordenar pelo registro escolhido
        if(strcmp(camp,"nome")==0){
            for(j=0;j<n;j++)
            strcpy(vetorstring[j],regs[j].nome);

            quickSortMain(regs,vetorstring,n);
        }else if(strcmp(camp,"rua")==0){
            for(j=0;j<n;j++)
            strcpy(vetorstring[j],regs[j].rua);

            quickSortMain(regs,vetorstring,n);
        }else if(strcmp(camp,"bairro")==0){
            for(j=0;j<n;j++)
            strcpy(vetorstring[j],regs[j].bairro);

            quickSortMain(regs,vetorstring,n);
        }else if(strcmp(camp,"cidade")==0){
            for(j=0;j<n;j++)
            strcpy(vetorstring[j],regs[j].cidade);

            quickSortMain(regs,vetorstring,n);
        }else if(strcmp(camp,"estado")==0){
              for(j=0;j<n;j++)
            strcpy(vetorstring[j],regs[j].estado);

            quickSortMain(regs,vetorstring,n);
        }else if(strcmp(camp,"telefone")==0){
              for(j=0;j<n;j++)
            strcpy(vetorstring[j],regs[j].telefone);

            quickSortMain(regs,vetorstring,n);
        }else if(strcmp(camp,"email")==0){
              for(j=0;j<n;j++)
            strcpy(vetorstring[j],regs[j].email);

            quickSortMain(regs,vetorstring,n);

        }else if(strcmp(camp,"chave")==0){
            //printf("TEste %d\n",n);
            for(j=0;j<n;j++)
            vetor[j]=regs[j].chave;

            quickSort(regs,vetor,0,n-1);
        }
    }
     constroitabela(regs,n,campos_d,orderby);

}//FIM select
//esta função separa os comandos da função update
int separa_update(char detalhes[],char chave[15],char valor[255],char novachave[15],char novovalor[255]){
    char where[10];
    char campos[50];
    char chave_valor[300];
    chave_valor[0]='\0';
    where[0]='\0';
    campos[0]='\0';
    int i,j=0,k=0,ctrl=0;
    if(detalhes[strlen(detalhes)-1]!=';')
    return 0;

    for(i=0;i<strlen(detalhes);i++){
        if(detalhes[i]==' '&&ctrl==0&&i!=0){
           j++;ctrl=0;
           k=0;
        }
        if(detalhes[i]=='='&&j==0&&detalhes[i+1]=='"'){
            ctrl=1;
        }else if(detalhes[i]=='"'&&detalhes[i+1]==' '&&j==0&&ctrl==1){
            ctrl=0;
        }

        if(detalhes[i]=='='&&j==2){
            ctrl=1;
        }
        if(j==0&&detalhes[i]!=' '&&detalhes[i]!=';'){
            campos[k]=detalhes[i];
            campos[k+1]='\0';
            k++;
        }else if(j==0&&ctrl==1){
            campos[k]=detalhes[i];
            campos[k+1]='\0';
            k++;
        }
        else if(j==1&&detalhes[i]!=' '&&detalhes[i]!=';'){
            where[k]=detalhes[i];
            where[k+1]='\0';
            k++;
        }else if(j==2&&detalhes[i]!=' '&&detalhes[i]!=';'){
            chave_valor[k]=detalhes[i];
            chave_valor[k+1]='\0';
            k++;
        }else if(j==2&&ctrl==1&&detalhes[i]!=';'){
            chave_valor[k]=detalhes[i];
            chave_valor[k+1]='\0';
            k++;
        }
    }
//printf("--%s-%s-%s\n",campos,where,chave_valor);
    if(strcmp(where,"where")!=0)
        return 0;
    else{
        	if(strlen(chave_valor)!=0){
			   j=0;
			   k=0;
			   for(i=0;i<strlen(chave_valor);i++){
				   if(chave_valor[i]=='='){
					 k=0;
					 j++;
				   }
				   if(j==0 && chave_valor[i]!='='){
					 chave[k]=chave_valor[i];
					 chave[k+1]='\0';
					 k++;
				   } else if(j==1 && chave_valor[i]!='='){
					 valor[k]=chave_valor[i];
					 valor[k+1]='\0';
					 k++;
				   }
			   }//Fim for
              //printf("--%s--%s\n",chave,valor);

			   if(strlen(chave)==0||strlen(valor)==0)
				return 0;
			}else
			return 0;

			if(strlen(campos)!=0){
			   j=0;
			   k=0;
			   for(i=0;i<strlen(campos);i++){
				   if(campos[i]=='='){
					 k=0;
					 j++;
				   }
				   if(j==0 && campos[i]!='='){
					 novachave[k]=campos[i];
					 novachave[k+1]='\0';
					 k++;
				   } else if(j==1 && campos[i]!='='){
					 novovalor[k]=campos[i];
					 novovalor[k+1]='\0';
					 k++;
				   }
			   }//Fim for
                //printf("%s--%s--\n",novachave,novovalor);
			   if(strlen(novachave)==0||strlen(novovalor)==0)
				return 0;
			}

			if(novovalor[0]=='"'&&novovalor[strlen(novovalor)-1]=='"')
             {
                 if(strcmp(novachave,"telefone")==0)
                    return 0;
                for(i=0;i<strlen(novovalor);i++)
                {
                if(i==strlen(novovalor)-2)
                {
                   novovalor[i] = '\0';
                   break;
                }
                else{
                    novovalor[i]=novovalor[i+1];
                }
                }
			}else if(strcmp(novachave,"telefone")!=0)
			return 0;

			if(valor[0]=='"'&&valor[strlen(valor)-1]=='"')
			{
			    if(strcmp(chave,"chave")==0){
                    return 0;
			    }
                for(i=0;i<strlen(valor);i++)
                {
                    if(i==strlen(valor)-2)
                    {
                        valor[i] = '\0';
                        break;
                    }
                    else{
                    valor[i]=valor[i+1];
                    }
                }
			}else if(strcmp(chave,"chave")!=0){
                return 0;
			}
    }
    return 1;
}
void Update(char detalhes[],unsigned int p[], TipoLista N[],TipoLista R[],TipoLista B[],TipoLista C[],TipoLista E[],TipoLista EM[],TipoApont *apChave,TipoApont *apTel, int del)
{
 char chave[15];char valor[255];char novachave[15];char novovalor[255];
 int i;
 unsigned int a=0;
 i = separa_update(detalhes,chave,valor,novachave,novovalor);
 if(i==0)
    printf("Erro de sintaxe.");
 else{
      if(strcmp(chave,"nome")!=0&&strcmp(chave,"chave")!=0){
            printf("O update eh feito pela chave ou pelo nome.\n");
            return;
      }else if(strcmp(novachave,"chave")==0){
          printf("Nao eh possivel alterar a chave.\n");
          return;
      }else{

    Registro regs[10];
    TipoReg reg;
    TipoReg x;
    TipoItem it;
    FILE *fp = cria_arquivo("DB","r+b");
    if(fp!=NULL)
    {
        if(strcmp(chave,"nome")==0){
            a=Pesquisa(valor,p,N,regs);
            //printf("%s",valor);
        }else if(strcmp(chave,"chave")==0){
            x.Chave = atoi(valor);
           // printf("--%d--%s\n",x.Chave,valor);
            SbbPesquisa(&x,apChave);
            resgata(x,regs);
           // printf("--%d\n",valor);
            a=1;
        }
      if(a==0)
      printf("Registro nao encontrado.");
      else{
    //printf("%s--\n",regs[0].nome);
        it.chaveReg = regs[0].chave;
        reg.chaveReg = regs[0].chave;
        if(strcmp(novachave,"nome")==0){
                if(strcmp(novovalor,"")==0 && del==0)
                {
                    printf("O campo nome nao pode ser nulo.\n");
                    return;
                }
            //    printf("teste\n");
            strcpy(it.Chave,regs[0].nome);
            Retira(it,p,N);
            strcpy(regs[0].nome,novovalor);
            strcpy(it.Chave,regs[0].nome);
            Insere(it,p,N);
        }else if(strcmp(novachave,"rua")==0){
            strcpy(it.Chave,regs[0].rua);
            Retira(it,p,R);
            strcpy(regs[0].rua,novovalor);
            strcpy(it.Chave,regs[0].rua);
            Insere(it,p,R);
        }
        else if(strcmp(novachave,"bairro")==0){
            strcpy(it.Chave,regs[0].bairro);
            Retira(it,p,B);
            strcpy(regs[0].bairro,novovalor);
            strcpy(it.Chave,regs[0].bairro);
            Insere(it,p,B);
        }
        else if(strcmp(novachave,"cidade")==0){
            strcpy(it.Chave,regs[0].cidade);
            Retira(it,p,C);
            strcpy(regs[0].cidade,novovalor);
            strcpy(it.Chave,regs[0].cidade);
            Insere(it,p,C);
        }
        else if(strcmp(novachave,"estado")==0){
            strcpy(it.Chave,regs[0].estado);
            Retira(it,p,E);
            strcpy(regs[0].estado,novovalor);
            strcpy(it.Chave,regs[0].estado);
            Insere(it,p,E);
        }
        else if(strcmp(novachave,"telefone")==0){
            reg.Chave=tel_para_int(regs[0].telefone);
            SbbRetira(reg,apTel);
            strcpy(regs[0].telefone,novovalor);
            reg.Chave = tel_para_int(regs[0].telefone);
            SbbInsere(reg,apTel);
        }
        else if(strcmp(novachave,"email")==0){
            strcpy(it.Chave,regs[0].email);
            Retira(it,p,EM);
            strcpy(regs[0].email,novovalor);
            strcpy(it.Chave,regs[0].email);
            Insere(it,p,EM);
        }else if(strcmp(novachave,"chave")==0){
            printf("Não eh possivel alterar chave\n");
            return;
        }
            a=regs[0].chave;
            //printf("--%d--",a);
            fseek(fp,(a-1)*sizeof(Registro), SEEK_SET);
            if(fwrite(&regs[0], sizeof(Registro), 1, fp)!=0)
            printf("Operacao realizada com sucesso.\n");
    }
    }
    fclose(fp);
      }
 }
}

//Separa os comandos para a funçáo delete
int separa_delete(char detalhes[],char chave[15],char valor[255]){
    char chave_valor[255];
    chave_valor[0]='\0';
    int i,j=0,k=0,ctrl=0;
 for(i=0;i<strlen(detalhes);i++){
        if(detalhes[i]==' '&&ctrl==0&&i!=0){
           j++;ctrl=0;
           k=0;
        }
        if(j==0 && ctrl==0 && detalhes[i]=='='){
            ctrl=1;
        }
        if(j==0&&detalhes[i]!=' '&&detalhes[i]!=';'){
            chave_valor[k]=detalhes[i];
            chave_valor[k+1]='\0';
            k++;
        }else if(j==0&&ctrl==1&&detalhes[i]!=';'){
            chave_valor[k]=detalhes[i];
            chave_valor[k+1]='\0';
            k++;
        }
    }
   // printf("%s--",chave_valor);
    	if(strlen(chave_valor)!=0){
			   j=0;
			   k=0;
			   for(i=0;i<strlen(chave_valor);i++){
				   if(chave_valor[i]=='='){
					 k=0;
					 j++;
				   }
				   if(j==0 && chave_valor[i]!='='){
					 chave[k]=chave_valor[i];
					 chave[k+1]='\0';
					 k++;
				   } else if(j==1 && chave_valor[i]!='='){
					 valor[k]=chave_valor[i];
					 valor[k+1]='\0';
					 k++;
				   }
			   }//Fim for
               //printf("TEste %s %s\n",valor,chave);
			   if(strlen(chave)==0||strlen(valor)==0){
                 //   printf("1TEste %s\n",valor);
                return 0;
			   }

			}else{
			return 0;
			}
			if(valor[0]=='"' && valor[strlen(valor)-1]=='"'){
               if(strcmp(chave,"chave")==0)
                return 0;

                for(i=0;i<strlen(valor);i++)
                {
                    if(i==strlen(valor)-2)
                    {
                        valor[i] = '\0';
                        i=strlen(valor);
                    }
                    else{
                        valor[i]=valor[i+1];
                    }
                }
            }else if(strcmp(chave,"chave")!=0)
                return 0;
   return 1;
}
void Delete(char detalhes[],unsigned int p[], TipoLista N[],TipoLista R[],TipoLista B[],TipoLista C[],TipoLista E[],TipoLista EM[],TipoApont *apChave,TipoApont *apTel)
{
    char chave[15];char valor[255];char comand[300];
     int u;
     comand[0]='\0';
     u = separa_delete(detalhes,chave,valor);
  if(u==0){
        printf("Erro de sintaxe");
 }else if(strcmp(chave,"nome")==0 ||strcmp(chave,"chave")==0){
        strcpy(comand," nome=\"\" where ");
        strcat(comand,chave);
        strcat(comand,"=");
        if(strcmp(chave,"nome")==0)
            strcat(comand,"\"");
        strcat(comand,valor);
        if(strcmp(chave,"nome")==0)
            strcat(comand,"\"");
        strcat(comand,";");
        Update(comand,p,N,R,B,C,E,EM,apChave,apTel,1);
    }else
        printf("A funcao delete usa a chave ou o nome.\n");
}

//adiciona a uma tabela hash todos os itens do BD
void constroiHash(unsigned int p[], TipoLista T[],char campo[]){
    FILE *fp = cria_arquivo("DB","rb");
    fflush(fp);
    Registro c;
    if(fp!=NULL)
    {
      while(fread(&c,sizeof(Registro),1,fp)){
      if(ferror(fp))
      printf("Erro na base de dados\n");
      else {
            TipoItem it;
             it.chaveReg=c.chave;
            if(strcmp(c.nome,"")){
                if(strcmp(campo,"nome")==0){
                    strcpy(it.Chave,c.nome);
                    Insere(it,p,T);
                }else if(strcmp(campo,"rua")==0){
                    strcpy(it.Chave,c.rua);
                    Insere(it,p,T);
                }else if(strcmp(campo,"bairro")==0){
                    strcpy(it.Chave,c.bairro);
                        //printf("%s --\n",it.Chave);
                    Insere(it,p,T);
                }else if(strcmp(campo,"cidade")==0){
                    strcpy(it.Chave,c.cidade);
                    //printf("%s --\n",it.Chave);
                    Insere(it,p,T);
                }else if(strcmp(campo,"estado")==0){
                    strcpy(it.Chave,c.estado);
                    Insere(it,p,T);
                }else if(strcmp(campo,"email")==0){
                    strcpy(it.Chave,c.email);
                    Insere(it,p,T);
                }
            }
      }
      }
      fclose(fp);
    }

}
//PEsquisa no hash
int Pesquisa(char Ch[],unsigned int p[], TipoLista T[],Registro regs[])
{
    int i,j=0;
	TipoApontador Ap;
	FILE *fp = cria_arquivo("DB","rb+");
	fflush(fp);
	i = h(Ch,p);

	//printf("pesquisa %d \n",i);
	if (Vazia(T[i])) return 0 ; /* Pesquisa sem sucesso */
	else
	{
        j=0;
        Ap = T[i].Primeiro->Prox;
		while (Ap!=NULL)
        {
        Registro x;
            if(strcmp(Ch,Ap->Item.Chave)==0){
            //printf("item da lista %d -- %s\n",Ap->Item.chaveReg,Ch);
                 fseek(fp,(long) (Ap->Item.chaveReg - (unsigned int)1)*sizeof(Registro), SEEK_SET);
                 if(fread(&x,sizeof(Registro),1,fp)==0){
                        printf("Erro na base de dados");
                        return 0;
                }
                else{
                        if(strcmp(x.nome,"")){
                            regs[j]=x;
                             //printf("Chave pesquisa: %d\n",regs[j].chave);
                            j++;
                        }
                }
                Ap = Ap ->Prox;
            }
        }
           fclose(fp);
       if(j==0){
             printf("Nenhum registro encontrado..\n");
        }
	return j;
	}
}
//insere em uma arvore sbb todos os itens do BD
void constroiSbb(TipoApont *ap,char campo[]){
    FILE *fp = cria_arquivo("DB","rb");
    fflush(fp);
//    int i;
    Registro c;
    TipoReg it;
    if(fp!=NULL)
    {
      while(fread(&c,sizeof(Registro),1,fp)){
      if(ferror(fp))
      printf("Erro na base de dados\n");
      else {
//printf("%d\n",c.chave);
             if(strcmp(c.nome,"")){
                    it.chaveReg=c.chave;
            if(strcmp(campo,"chave")==0){
                it.Chave=c.chave;
                SbbInsere(it,ap);
            }else if(strcmp(campo,"telefone")==0){
                it.Chave = tel_para_int(c.telefone);
                SbbInsere(it,ap);
                //printf("--%d--%d\n",c.chave,tel_para_int(c.telefone));
            }

             }
             //Testa(ap);
      }
      }
      fclose(fp);
    }
    /*
    it.chaveReg=4;
    SbbPesquisa(&it,ap);
    printf("--%d\n",it.chaveReg);*/
}
//Pesquisa no SBB
void SbbPesquisa(TipoReg *x, TipoApont *p)
{ if (*p == NULL)
  { //printf("Erro: Registro nao esta presente na arvore\n");
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

























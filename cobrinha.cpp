#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <io.h>
#include <locale>
#include "keyb.h"

#define MaxTam          100
//tamanho maximo da cobrinha


typedef int Apontador;


typedef struct
{
  int x;
  int y;
} TipoItem;

typedef struct {
  TipoItem Item[MaxTam];
  Apontador Frente, Tras;
} TipoFila;

void FFVazia(TipoFila *Fila)
{
  Fila->Frente = 0;
  Fila->Tras = Fila->Frente;
}  /* FFVazia */


int Vazia(TipoFila Fila)
{
  return (Fila.Frente == Fila.Tras);
}  /* Vazia */


void Enfileira(TipoItem x, TipoFila *Fila)
{
  if (((Fila->Tras + 1) % MaxTam) == Fila->Frente)
    printf(" Erro! Fila esta cheia!\n");
  else {
    Fila->Item[Fila->Tras] = x;
    Fila->Tras = (Fila->Tras + 1) % MaxTam;
  }
}  /* Enfileira */


void Desenfileira(TipoFila *Fila, TipoItem *Item)
{
  if (Vazia(*Fila))
    printf(" Erro! Fila esta vazia!\n");
  else {
    *Item = Fila->Item[Fila->Frente];
    Fila->Frente = (Fila->Frente + 1) % MaxTam;
  }
}  /* Desenfileira */


void comida(int *x2,int *y2, TipoFila Atual)
{
 TipoItem Temp;
 int i,encima=0;

 do
 {
  encima=0;

  randomize();

  *x2=0;
  while(*x2<11)
  {
   *x2=random(69);
  }

  *y2=0;
  while(*y2<4)
  {
   *y2=random(22);
  }

  for(i=0;i<MaxTam;i++)
  {
   if(Vazia(Atual)!=1)
   {
    Desenfileira(&Atual,&Temp);
    if((Temp.x==*x2)&&(Temp.y==*y2))
     encima=1;
   }
  }
 }while(encima==1);//fim do while encima
}

unsigned char fim=0;
unsigned char erro=0;

void main()
{

 textcolor(BLUE);
 textbackground(WHITE);

 while(!fim)
 {

 TipoFila Apaga,Compara,Copia;
 TipoItem Temp;
 int cont=1,l=1,i=0,x=25,y=10,x1=0,y1=0,x2=0,y2=0;
 int tecla=255,pontos=0,velocidade=2000000;
 char controle='D';

 if(erro!=TRUE)
 {
  clrscr();

  printf("\a");

  gotoxy(33,5);
  printf("JOGO DA COBRINHA");

  gotoxy(36,7);
  printf("VERSAO 1.0");

  gotoxy(10,10);
  printf("UTILIZE AS TECLAS 2, 4, 6 E 8 DO TECLADO NUMERICO PARA JOGAR.");

  gotoxy(21,13);
  printf("TECLE ENTER PARA INICIAR OU ESC PARA SAIR.");

  gotoxy(24,16);
  printf("DESENVOLVIDO POR JOAO PAULO DE LIMA");

  getch();
 }

 clrscr();
 erro=FALSE;

 FFVazia(&Apaga);

 //desenha limite de cima
 for(i=11;i<70;i++)
 {
  gotoxy(i,3);
  printf("_");
 }
 //desenha limite de baixo
 for(i=10;i<=70;i++)
 {
  gotoxy(i,23);
  printf("_");
 }

 //desenha limite da esquerda
 for(i=4;i<=23;i++)
 {
  gotoxy(10,i);
  printf("|");
 }

 //desenha limite da direita
 for(i=4;i<=23;i++)
 {
  gotoxy(70,i);
  printf("|");
 }

 gotoxy(12,2);
 printf("V 1.0                JOGO DA COBRINHA       PONTUACAO:");

 i=0;

 comida(&x2,&y2,Apaga);
 gotoxy(x2,y2);
 printf("@");

 while(!erro)
 {
  if(kbhit())
  {
   tecla=getch();

     switch(toupper(tecla))
      {
       case ESC:
        fim=TRUE;
        erro=TRUE;
        break;

       case 52:
        controle='E';
        break;

       case 54:
        controle='D';
        break;

       case 50:
        controle='B';
        break;

       case 56:
        controle='C';
        break;

      } // fim do switch tecla normal pressionada
  
  } // if (kbhit()) --> evento foi uma tecla pressionada

  if(controle=='D')
   x=x+1;

  else if(controle=='E')
        x=x-1;

       else if(controle=='C')
             y=y-1;

            else
             y=y+1;

  FFVazia(&Compara);
  FFVazia(&Copia);

  for(i=0;i<MaxTam;i++)
  {
   if(Vazia(Apaga)!=1)
   {
    Desenfileira(&Apaga,&Temp);
    Enfileira(Temp,&Compara);
    Enfileira(Temp,&Copia);
   }
  }

  for(i=0;i<MaxTam;i++)
  {
   if(Vazia(Copia)!=1)
   {
    Desenfileira(&Copia,&Temp);
    Enfileira(Temp,&Apaga);
   }
  }


  if((x<11)||(x>69)||(y<4)||(y>22))
  {
   gotoxy(25,15);
   printf("FIM DO JOGO!!! TENTE NOVAMENTE!!!");
   erro=TRUE;
  }

  for(i=0;i<MaxTam;i++)
  {
   if(Vazia(Compara)!=1)
   {
    Desenfileira(&Compara,&Temp);
    if((x==Temp.x)&&(y==Temp.y))
    {
     gotoxy(25,15);
     printf("FIM DO JOGO!!! TENTE NOVAMENTE!!!");
     erro=TRUE;
    }
   }
  }

  if(erro!=TRUE)
  {
   gotoxy(x,y);
   printf("@");
   if((x==x2)&&(y==y2))
   {
    comida(&x2,&y2,Apaga);
    gotoxy(x2,y2);
    printf("@");
    l=l-1;
    gotoxy(68,2);
    pontos=pontos+5;
    printf("%d",pontos);
   }
  }

  Temp.x=x;
  Temp.y=y;
  Enfileira(Temp,&Apaga);


  if((cont>5)&&(l==1))
  {
   Desenfileira(&Apaga,&Temp);
   x1=Temp.x;
   y1=Temp.y;
   gotoxy(x1,y1);
   printf(" ");
  }


  for(i=0;i<velocidade;i++)
  {
   i=i;
  }

  if (l==0)
   l++;
  cont++;

 } // fim do while(!erro)

 if(fim!=1)
 {
  getch();
  getch();
 }

 }//fim do while(!fim)

} //fim do void main()



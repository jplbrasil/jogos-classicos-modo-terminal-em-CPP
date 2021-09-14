#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <io.h>
#include <locale>
//--------------------------------------------------------------------
//                 TAD FILA
//--------------------------------------------------------------------

//Tamanho maximo da fila de Posicoes x e y
#define MaxTam          500

//Quantidade de fantasminhas no jogo
#define NumFan          8

//Variaveis globais
int erro=0,pontos=0,
    p1=1,p2=1,p3=1,p4=1;//pastilhas

struct Personagem
{
  int x,//coordenada 'x' do personagem na tela
      y,//coordenada 'y' do personagem na tela
      super, //tempo durante o qual o pacman e' invencivel
      ativo; //indica se o personagem esta' ativo ou nao
  char controle; //direcao para onde o personagem esta' se movendo
};

typedef int Apontador;

struct TipoItem
{
 int x,y;
};

struct TipoFila
{
 TipoItem Item[MaxTam];
 Apontador Frente, Tras;
};

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

//Deleta um item específico da fila
void Deleta_Item(TipoFila *Fila, TipoItem Item)
{
  int ponteiro;
  TipoItem temp;

  ponteiro=Fila->Frente;

  while( ponteiro < Fila->Tras )
  {
   temp = Fila->Item[ponteiro];
   if( (temp.x==Item.x) && (temp.y==Item.y) )
   {
    Fila->Item[ponteiro].x=0;
    Fila->Item[ponteiro].y=0;
    pontos++;
   }

   ponteiro = (ponteiro + 1) % MaxTam;
  }
}  /* Deleta_Item */

//--------------------------------------------------------------------
//                 FUNCOES DO PROGRAMA
//--------------------------------------------------------------------

void linha_hor(int x,int y,int tam,char tipo);
void linha_ver(int x,int y,int tam,char tipo);
void limite(int xi,int xf,int yi,int yf,char tipo1,char tipo2);
void cenario();
void faz_comidas(TipoFila *Comida,TipoFila *Compara);
void primeira_tela();
void cabecalho();
int  pode_andar(int *x,int *y,char controle,TipoFila Compara);
int  move_come_come(Personagem *pacman,Personagem fant[],int cont,TipoFila *Apaga,TipoFila *Comida);
int  move_fantasma(Personagem pacman,Personagem *fantasma,TipoFila Comida,TipoFila Compara);
void main();

void main()
{

  int i,cont=1,tecla=255,espera=1000000,QtdeFan=1,fim=0,vidas=2,comida=0;
  char controle='D';

  Personagem pacman;

  Personagem fant[NumFan];

  while(!fim)
  {

  //Inicializa o come come
  pacman.x=40;
  pacman.y=16;
  pacman.super=0;
  pacman.controle='D';

  //Inicializa os fantasmas
  for(i=0;i<NumFan;i++)
  {
   fant[i].x=40;
   fant[i].y=9;
   fant[i].ativo=1;
   if(i%2==0)
    fant[i].controle='D';
   else
    fant[i].controle='E';
  }

  TipoFila Apaga,//Guarda as posicoes x e y que devem ser apagadas apos serem comidas pelo come-come
           Compara,//Guarda as posicoes x e y por onde o come-come pode andar
           Comida,//Guarda as posicoes x e y das comidas que ainda restam
           Copia;//Uma copia temporaria usada quando o pacman e' capturado

  TipoItem Temp;

  FFVazia(&Apaga);
  FFVazia(&Compara);
  FFVazia(&Comida);

  //Desenha o labirinto do jogo
  cenario();

  //Informacoes sobre o jogo
  textcolor(3);
  gotoxy(6,3);
  cprintf("PacMan");
  gotoxy(2,6);
  cprintf("Pontos:");
  gotoxy(2,8);
  cprintf("Vidas: %d",vidas);
  gotoxy(2,12);
  cprintf("+ -> mais rapido");
  gotoxy(2,14);
  cprintf("- -> mais devagar");
  gotoxy(2,20);
  cprintf("Desenvolvido por:");
  gotoxy(2,21);
  cprintf("Joao Paulo de Lima");
  textcolor(15);

  //Informa as posicoes x e y por onde o come-come e os fantasmas
  //podem andar, desenha as comidinhas na tela e habilita o elevador
  faz_comidas(&Comida,&Compara);

 while(vidas)
 {
  if(tecla=kbhit())
  {

  //Uso o getch() duas vezes para pegar as setas do teclado
   tecla=getch();

   //Testa se o ESC foi pressionado
   if(tecla==27)
    vidas=0;

   //Tecla '+' pressionada -> aumenta a velocidade do jogo
   else if(tecla==43)
    espera=espera/2;

   //Tecla '-' pressionada -> diminui a velocidade do jogo
   else if(tecla==45)
   {
    if(espera<3000000)
     espera=espera*2;
   }

   else
   {
    tecla=getch();

    switch(tecla)
    {
     //Seta para a esquerda
     case 75:
      controle='E';
      break;

     //Seta para a direita
     case 77:
      controle='D';
      break;

     //Seta para baixo
     case 80:
      controle='B';
      break;

     //Seta para cima
     case 72:
      controle='C';
      break;
    } //Fim do switch tecla

   }//Fim do else

  } //Fim do kbhit()

  //Informa ao usuario sobre a imunidade do pacman
  textcolor(10);
  gotoxy(2,16);
  if(pacman.super>0)
  {
   cprintf("Imunidade: %d ",pacman.super);
   pacman.super--;
  }
  else
  {
   cprintf("Imunidade: 0 ");
   for(i=0;i<QtdeFan;i++)
    fant[i].ativo=1;
  }
  //Volta a cor do texto ao normal
  textcolor(15);

  //Movimenta de acordo com a escolha do jogador
  if( pode_andar(&pacman.x,&pacman.y,controle,Compara) )
  {
   erro=move_come_come(&pacman,fant,cont,&Apaga,&Comida);
   pacman.controle=controle;
  }

  //Se o jogador tentou um movimento invalido,
  //continua na mesma direcao anterior
  else if( pode_andar(&pacman.x,&pacman.y,pacman.controle,Compara) )
   erro=move_come_come(&pacman,fant,cont,&Apaga,&Comida);

  if( (pontos%200==0) && (pontos!=0) )
  {
   vidas++;
   textcolor(3);
   gotoxy(2,8);
   cprintf("Vidas: %d",vidas);
   textcolor(15);
  }

  //Move os fantasminhas
  for(i=0;i<QtdeFan;i++)
  {
   if(!erro)
    erro=move_fantasma(pacman,&fant[i],Comida,Compara);
  }

  //Diminui a velocidade do jogo
  for(i=0;i<espera;i++)
   i=i;

  //Ajuda na movimentacao grafica do pacman
  cont++;

  //Incrementa o numero de fantasmas atual no jogo
  //Cria o efeito de saida no inicio do jogo
  if(QtdeFan<NumFan)
   QtdeFan++;

  //Quando o jogador e' capturado, perde uma vida e recomeca
  if(erro)
  {
   vidas--;
   erro=0;
   textcolor(3);
   gotoxy(2,8);
   cprintf("Vidas: %d",vidas);
   textcolor(15);

   //Re-inicializa o come come
   pacman.x=40;
   pacman.y=16;
   pacman.super=0;
   pacman.controle='\0';

   //Re-inicializa os fantasmas
   for(i=0;i<NumFan;i++)
   {
    //Redesenha o caracter da posicao atual do fantasma

    //Verifica se o caracter era uma comida ou um "branco"

    Copia = Comida;
    comida=0;

    while( (!Vazia(Copia)) && (comida==0) )
    {
     Desenfileira(&Copia,&Temp);
     if( (Temp.x==fant[i].x) && (Temp.y==fant[i].y) )
      comida=1;
    }

    if(comida)
    {
     //Muda a cor do texto para amarelo para desenhar a comidinha
     textcolor(14);
     gotoxy(fant[i].x,fant[i].y);
     cprintf("o");
     //Volta a cor do texto ao normal
     textcolor(15);
    }
    else
    {
     gotoxy(fant[i].x,fant[i].y);
     printf(" ");
    }

    //Re-inicializa o fantasminha
    fant[i].x=40;
    fant[i].y=9;
    fant[i].ativo=1;
    if(i%2==0)
     fant[i].controle='D';
    else
     fant[i].controle='E';
   }

   QtdeFan=1;

   //Avisa ao usuario sobre a captura
   textbackground(WHITE);
   textcolor(BLUE);
   gotoxy(62,8);
   cprintf("             ");
   gotoxy(62,9);
   cprintf("             ");
   gotoxy(62,10);
   cprintf("   OH SHIT!  ");
   gotoxy(62,11);
   cprintf("             ");
   gotoxy(62,12);
   cprintf("             ");

   while(tecla!=13)
    tecla=getch();

   //Volta as cores ao normal
   textbackground(BLACK);
   textcolor(7);

   gotoxy(62,8);
   cprintf("             ");
   gotoxy(62,9);
   cprintf("             ");
   gotoxy(62,10);
   cprintf("             ");
   gotoxy(62,11);
   cprintf("             ");
   gotoxy(62,12);
   cprintf("             ");

   //Poe o PacMan em movimento novamente
   pode_andar(&pacman.x,&pacman.y,'D',Compara);
   move_come_come(&pacman,fant,cont,&Apaga,&Comida);

  }

 } // fim do while(vidas)

  fim=1;
  tecla=0;

  //Fim do jogo
  textbackground(WHITE);
  textcolor(BLUE);
  gotoxy(35,8);
  cprintf("             ");
  gotoxy(35,9);
  cprintf("             ");
  gotoxy(35,10);
  cprintf(" GAME OVER!  ");
  gotoxy(35,11);
  cprintf("             ");
  gotoxy(35,12);
  cprintf("             ");

  while((tecla!=13)&&(tecla!=27))
  {
    tecla=getch();

    if(tecla==13)
    {
     fim=0;
     erro=0;
     cont=1;
     QtdeFan=1;
     textbackground(BLACK);
     textcolor(7);
     vidas=2;
     p1=p2=p3=p4=1;
     pontos=0;
    }

  }

 }//Fim do while(!fim)

} //fim do void main()

//------------------------------------------------
//    CODIGO DAS FUNCOES
//------------------------------------------------

void linha_hor(int x,int y,int tam,char tipo)
{
 int i;
 for(i=x;i<tam;i++)
 {
  gotoxy(i,y);
  printf("%c",205);
 }
}

void linha_ver(int x,int y,int tam,char tipo)
{
 int i;
 for(i=y;i<tam;i++)
 {
  gotoxy(x,i);
  printf("%c",186);
 }
}

void limite(int xi,int xf,int yi,int yf,char tipo1,char tipo2)
{
 //desenha limite de cima
 linha_hor(xi,yi,xf,tipo1);

 //desenha limite de baixo
 linha_hor(xi,yf,xf,tipo1);

 //desenha limite da direita
 linha_ver(xf,yi+1,yf+1,tipo2);

 //desenha limite da esquerda
 linha_ver(xi-1,yi+1,yf+1,tipo2);

 //desenha conector de cima a direita
 gotoxy(xf,yi);
 printf("%c",187);

 //desenha conector de baixo a direita
 gotoxy(xf,yf);
 printf("%c",188);

 //desenha conector de cima a esquerda
 gotoxy(xi-1,yi);
 printf("%c",201);

 //desenha conector de baixo a esquerda
 gotoxy(xi-1,yf);
 printf("%c",200);

}

void cenario()
{
 clrscr();

 //desenha limite maior
 limite(25,58,1,24,' ',' ');

 //desenha quadrado no meio
 limite(39,44,10,15,'_','|');

 //desenha limites ao lado esquerdo
 //do quadrado do meio
 limite(33,36,7,11,'_','|');
 limite(33,36,13,18,'_','|');

 //desenha limites ao lado direito
 //do quadrado do meio
 limite(47,50,7,11,'_','|');
 limite(47,50,13,18,'_','|');

 //desenha limites em cima e em baixo
 //do quadrado do meio
 limite(39,44,7,8,'_','|');
 limite(39,44,17,18,'_','|');

 //desenha limites em cima e em baixo
 //antes do elevador
 limite(33,50,3,5,'_','|');
 limite(33,50,20,22,'_','|');

 //desenha entradas das salas lado direito
 linha_ver(52,2,6,' ');
 linha_ver(52,7,19,' ');
 linha_ver(52,20,24,' ');

 //desenha entradas das salas lado esquerdo
 linha_ver(30,2,6,' ');
 linha_ver(30,7,19,' ');
 linha_ver(30,20,24,' ');

 //desenha obstáculos dentro da sala esquerda
 limite(27,28,3,4,'_','|');
 linha_hor(25,7,28,'_');
 limite(27,28,9,10,'_','|');
 linha_hor(26,12,30,'_');
 limite(27,28,14,17,'_','|');
 linha_hor(25,19,28,'_');
 limite(27,28,21,22,'_','|');

 //desenha obstáculos dentro da sala direita
 limite(55,56,3,4,'_','|');
 linha_hor(55,7,58,'_');
 limite(55,56,9,10,'_','|');
 linha_hor(53,12,57,'_');
 limite(55,56,14,17,'_','|');
 linha_hor(55,19,58,'_');
 limite(55,56,21,22,'_','|');

 //desenha elevador encima e embaixo
 gotoxy(41,1);
 printf("%c",' ');

 gotoxy(41,24);
 printf("%c",' ');
}

void faz_comidas(TipoFila *Comida,TipoFila *Compara)
{
 int i;
 TipoItem Temp;
 TipoFila Temporaria;

 FFVazia(&Temporaria);

 //Preenche a Temporaria com as coordenadas dos pinos
 for(i=31;i<52;i++)
 {
  Temp.x=i;
  Temp.y=23;
  Enfileira(Temp,&Temporaria);
 }

 for(i=28;i<55;i++)
 {
  Temp.x=i;
  Temp.y=19;
  Enfileira(Temp,&Temporaria);
 }

 for(i=31;i<52;i++)
 {
  Temp.x=i;
  Temp.y=2;
  Enfileira(Temp,&Temporaria);
 }

 for(i=25;i<58;i++)
 {
  Temp.x=i;
  Temp.y=6;
  Enfileira(Temp,&Temporaria);
 }

 for(i=2;i<24;i++)
 {
  Temp.x=31;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=2;i<24;i++)
 {
  Temp.x=51;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=7;i<19;i++)
 {
  Temp.x=45;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=7;i<19;i++)
 {
  Temp.x=37;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=37;i<46;i++)
 {
  Temp.x=i;
  Temp.y=16;
  Enfileira(Temp,&Temporaria);
 }

 for(i=37;i<46;i++)
 {
  Temp.x=i;
  Temp.y=9;
  Enfileira(Temp,&Temporaria);
 }

 for(i=32;i<37;i++)
 {
  Temp.x=i;
  Temp.y=12;
  Enfileira(Temp,&Temporaria);
 }

 for(i=46;i<51;i++)
 {
  Temp.x=i;
  Temp.y=12;
  Enfileira(Temp,&Temporaria);
 }

 for(i=53;i<58;i++)
 {
  Temp.x=i;
  Temp.y=2;
  Enfileira(Temp,&Temporaria);
 }

 for(i=53;i<58;i++)
 {
  Temp.x=i;
  Temp.y=8;
  Enfileira(Temp,&Temporaria);
 }

 for(i=53;i<58;i++)
 {
  Temp.x=i;
  Temp.y=11;
  Enfileira(Temp,&Temporaria);
 }

 for(i=53;i<58;i++)
 {
  Temp.x=i;
  Temp.y=13;
  Enfileira(Temp,&Temporaria);
 }

 for(i=53;i<58;i++)
 {
  Temp.x=i;
  Temp.y=18;
  Enfileira(Temp,&Temporaria);
 }

 for(i=53;i<58;i++)
 {
  Temp.x=i;
  Temp.y=20;
  Enfileira(Temp,&Temporaria);
 }

 for(i=53;i<58;i++)
 {
  Temp.x=i;
  Temp.y=23;
  Enfileira(Temp,&Temporaria);
 }

 for(i=25;i<30;i++)
 {
  Temp.x=i;
  Temp.y=2;
  Enfileira(Temp,&Temporaria);
 }

 for(i=25;i<30;i++)
 {
  Temp.x=i;
  Temp.y=8;
  Enfileira(Temp,&Temporaria);
 }

 for(i=25;i<30;i++)
 {
  Temp.x=i;
  Temp.y=11;
  Enfileira(Temp,&Temporaria);
 }

 for(i=25;i<30;i++)
 {
  Temp.x=i;
  Temp.y=13;
  Enfileira(Temp,&Temporaria);
 }

 for(i=25;i<30;i++)
 {
  Temp.x=i;
  Temp.y=18;
  Enfileira(Temp,&Temporaria);
 }

 for(i=25;i<30;i++)
 {
  Temp.x=i;
  Temp.y=20;
  Enfileira(Temp,&Temporaria);
 }

 for(i=25;i<30;i++)
 {
  Temp.x=i;
  Temp.y=23;
  Enfileira(Temp,&Temporaria);
 }

 for(i=3;i<6;i++)
 {
  Temp.x=53;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=9;i<11;i++)
 {
  Temp.x=53;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=14;i<18;i++)
 {
  Temp.x=53;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=19;i<23;i++)
 {
  Temp.x=53;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=3;i<6;i++)
 {
  Temp.x=57;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=9;i<11;i++)
 {
  Temp.x=57;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=14;i<18;i++)
 {
  Temp.x=57;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=20;i<23;i++)
 {
  Temp.x=57;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 Temp.x=53;
 Temp.y=7;
 Enfileira(Temp,&Temporaria);

 Temp.x=57;
 Temp.y=12;
 Enfileira(Temp,&Temporaria);

 for(i=3;i<6;i++)
 {
  Temp.x=25;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=9;i<11;i++)
 {
  Temp.x=25;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=14;i<18;i++)
 {
  Temp.x=25;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=20;i<23;i++)
 {
  Temp.x=25;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=3;i<6;i++)
 {
  Temp.x=29;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=9;i<11;i++)
 {
  Temp.x=29;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=14;i<18;i++)
 {
  Temp.x=29;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=19;i<23;i++)
 {
  Temp.x=29;
  Temp.y=i;
  Enfileira(Temp,&Temporaria);
 }

 for(i=54;i<58;i++)
 {
  Temp.x=i;
  Temp.y=5;
  Enfileira(Temp,&Temporaria);
 }

 for(i=26;i<29;i++)
 {
  Temp.x=i;
  Temp.y=5;
  Enfileira(Temp,&Temporaria);
 }

 Temp.x=29;
 Temp.y=7;
 Enfileira(Temp,&Temporaria);

 Temp.x=25;
 Temp.y=12;
 Enfileira(Temp,&Temporaria);

 //Muda a cor do texto para amarelo para desenhar as comidinhas
 textcolor(14);

 //Copia a fila Temporaria nas filas Compara e Comida
 while(Vazia(Temporaria)!=1)
 {
  Desenfileira(&Temporaria,&Temp);
  Enfileira(Temp,&*Compara);
  Enfileira(Temp,&*Comida);

  //Desenha as comidinhas na tela
  gotoxy(Temp.x,Temp.y);
  cprintf("o");
 }

 //Volta a cor do texto ao normal
 textcolor(15);

 //Habilita o elevador em cima e em baixo
 //O elevador e' desenhado na funcao cenario()
 Temp.x=41;
 Temp.y=1;
 Enfileira(Temp,&*Compara);

 Temp.x=41;
 Temp.y=24;
 Enfileira(Temp,&*Compara);

 //desenha as pastilhas
 textcolor(13);
 gotoxy(25,2);
 cprintf("%c",'#');
 gotoxy(57,2);
 cprintf("%c",'#');
 gotoxy(25,23);
 cprintf("%c",'#');
 gotoxy(57,23);
 cprintf("%c",'#');

}

void cabecalho()
{
 gotoxy(12,1);
 printf("VERSAO BETA               PAC MAN           PONTUACAO:");
}

int pode_andar(int *x,int *y,char controle,TipoFila Compara)
{
 int x_ant,y_ant;
 TipoItem Temp;

 x_ant=*x;
 y_ant=*y;

 if(controle=='D')
   *x=*x+1;

  else if(controle=='E')
        *x=*x-1;
       else if(controle=='C')
            {
             if((*y==2)&&(*x==41))
              *y=23; //Elevador de cima para baixo
             else
              *y=*y-1;
            }

            else if(controle=='B')
             {
             if((*y==23)&&(*x==41))
              *y=2; //Elevador de baixo para cima
             else
              *y=*y+1;
            }
            else
             return 0; //Proibe o movimento do personagem

 while(Vazia(Compara)!=1)
 {
  Desenfileira(&Compara,&Temp);
  if((Temp.x==*x)&&(Temp.y==*y))
   return 1; //Permite o movimento do personagem
 }

  *x=x_ant;
  *y=y_ant;
  return 0; //Proibe o movimento do personagem

}

int move_come_come(Personagem *pacman,Personagem fant[],int cont,TipoFila *Apaga,TipoFila *Comida)
{
 TipoItem Temp;
 int i;

  //Muda a cor do texto para azul para desenhar o come come
  textcolor(3);

  gotoxy(pacman->x,pacman->y);
  cprintf("%c",'@');

  //Volta a cor do texto ao normal
  textcolor(15);

  Temp.x=pacman->x;
  Temp.y=pacman->y;
  Enfileira(Temp,&*Apaga);

  //Simula o ato de comer do come-come,
  //apagando sua posição anterior e deletando o item da fila Comida
  if(cont>1)
  {
   Desenfileira(&*Apaga,&Temp);
   gotoxy(Temp.x,Temp.y);
   printf(" ");
   Deleta_Item(&*Comida,Temp);
   gotoxy(10,6);
   printf("%d",pontos);
  }

  //Testa se o pacman se encontrou com algum fantasminha
   for(i=0;i<NumFan;i++)
   {
    if( (pacman->x==fant[i].x)&&(pacman->y==fant[i].y)&&(fant[i].ativo) )
    {
     if(pacman->super==0)
      return 1;
     else
     {
      fant[i].ativo=0;
      pontos=pontos+10;
     }
    }
   }

  //Testa se ele comeu uma pastilha
  if(pacman->x==25 && pacman->y==2 && p1)
  {
   pacman->super=60;
   p1=0;
  }
  else if(pacman->x==57 && pacman->y==2 && p2)
  {
   pacman->super=60;
   p2=0;
  }
  else if(pacman->x==25 && pacman->y==23 && p3)
  {
   pacman->super=60;
   p3=0;
  }
  else if(pacman->x==57 && pacman->y==23 && p4)
  {
   pacman->super=60;
   p4=0;
  }

  return 0;
}

int move_fantasma(Personagem pacman,Personagem *Fantasma,TipoFila Comida,TipoFila Compara)
{
 TipoItem Temp;
 int x_ant,y_ant,direc,comida=0,mover=0,temp;
 char tipo='X',controle='\0';

 //Se o fantasminha estiver na mesma linha ou
 //mesma coluna do come come, promove uma perseguicao
 if(pacman.super==0)
 {
  if(pacman.x==Fantasma->x)
  {
   if(pacman.y>Fantasma->y)
    controle='B';
   else
    controle='C';
  }
  if(pacman.y==Fantasma->y)
  {
   if(pacman.x>Fantasma->x)
    controle='D';
   else
    controle='E';
  }
 }

 //Se o pacman comeu uma pastilha, promove uma fuga
 else
 {
  if(pacman.x==Fantasma->x)
  {
   if(pacman.y>Fantasma->y)
    controle='C';
   else
    controle='B';
  }
  if(pacman.y==Fantasma->y)
  {
   if(pacman.x>Fantasma->x)
    controle='E';
   else
    controle='D';
  }
 }


 //Guarda as posicoes anteriores do fantasma
 x_ant=Fantasma->x;
 y_ant=Fantasma->y;


 if(!pode_andar(&Fantasma->x,&Fantasma->y,controle,Compara))
 {
  //Se nao esta' em perseguicao, tenta seguir
  //a mesma direcao do ultimo movimento feito
  if(!pode_andar(&Fantasma->x,&Fantasma->y,Fantasma->controle,Compara))
  {
   //Encontra um movimento valido
   randomize();
   while(!mover)
   {
    direc=random(4);

    if (direc==0)
     Fantasma->controle='C';
    else if (direc==1)
     Fantasma->controle='B';
    else if (direc==2)
     Fantasma->controle='E';
    else
     Fantasma->controle='D';

    mover=pode_andar(&Fantasma->x,&Fantasma->y,Fantasma->controle,Compara);
   }//Fim do while

  }//Fim do segundo !pode_andar

 }//Fim do primeiro !pode_andar

 //Se o fantasminha conseguiu se mover na mesma
 //direcao anterior, guarda a direcao e vai embora!
 else
  Fantasma->controle=controle;

  //Muda a cor do texto desenhar o fantasminha
  if(pacman.super==0)
   textcolor(12);
  else
   textcolor(10);

  //Testa se o fantasminha esta' ativo ou foi devorado
  if(Fantasma->ativo)
   tipo='X';
  else
   tipo='*';

  //Movimenta o fantasma
  gotoxy(Fantasma->x,Fantasma->y);
  cprintf("%c",tipo);

  //Volta a cor do texto ao normal
  textcolor(15);

  //Redesenha o caracter da posicao anterior do fantasma

  //Verifica se o caracter anterior era uma comida ou um "branco"
  while( (!Vazia(Comida)) && (comida==0) )
  {
   Desenfileira(&Comida,&Temp);
   if( (Temp.x==x_ant) && (Temp.y==y_ant) )
    comida=1;
  }

  if(comida)
  {
   //Muda a cor do texto para amarelo para desenhar a comidinha
   textcolor(14);
   gotoxy(x_ant,y_ant);
   cprintf("o");
   //Volta a cor do texto ao normal
   textcolor(15);
  }
  else
  {
   gotoxy(x_ant,y_ant);
   printf(" ");
  }

  //Testa se ele comeu uma pastilha e redesenha
  if(x_ant==25 && y_ant==2 && p1)
  {
   textcolor(13);
   gotoxy(x_ant,y_ant);
   cprintf("#");
   textcolor(15);
  }
  else if(x_ant==57 && y_ant==2 && p2)
  {
   textcolor(13);
   gotoxy(x_ant,y_ant);
   cprintf("#");
   textcolor(15);
  }
  else if(x_ant==25 && y_ant==23 && p3)
  {
   textcolor(13);
   gotoxy(x_ant,y_ant);
   cprintf("#");
   textcolor(15);
  }
  else if(x_ant==57 && y_ant==23 && p4)
  {
   textcolor(13);
   gotoxy(x_ant,y_ant);
   cprintf("#");
   textcolor(15);
  }

  //Testa se o fantasminha capturou o pacman e vice-versa
   if( (pacman.x==Fantasma->x)&&(pacman.y==Fantasma->y)&&(Fantasma->ativo) )
   {
    if(pacman.super==0)
     return 1;
    else
    {
     Fantasma->ativo=0;
     pontos=pontos+10;
    } 
   }


  return 0;

}


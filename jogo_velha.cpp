//Autor: Joao Paulo de Lima

#include<iostream.h>
#include<conio.h>

//Preenche a matriz jogo com espaços em branco;
void preenche(char jogo[][3]);

//Imprime a matriz jogo;
void imprime(char jogo[][3]);

//Sorteia quem começará jogando;
int sorteio();

//Abre o prompt para que o jogador jogue;
void jogador(char jogo[][3],int&q);

//Confere se alguem venceu;
void confere1(char jogo[][3],int&q);

//Função auxiliar da função "confere1";
void confere2(char x,char y,char z,int&q,char jogo[][3]);

//Confere se deu velha no jogo;
void velha(char jogo[][3],int&q);

//Chama as funções "analisa" e "jogamicro";
void micro(char jogo[][3],int&q);

//Analisa a configuração da matriz e retorna o peso para cada jogada;
void analisa(char x,char y,char z,int&px,int&py,int&pz);

//Analisa o peso de cada jogada e depois joga;
void jogamicro(char&x,int px,int&flag,int peso);

//Analisa as jogadas conhecidas, defende e ataca;
void ataque(int&flag,char jogo[][3],char&u,char&v,char&x,char&y,char&z);

//Função principal;
void main()
{
 int inicio,q=0;
 char jogo[3][3];


 preenche(jogo);
 inicio=sorteio();

 //Se o numero sorteado for 1, o jogador começa jogando;
 if(inicio==1)
 {
  //Enquanto ninguém ganhar (q==0), o laço continua;
  while(q==0)
  {
   jogador(jogo,q);

   //Se o jogador ganhar (q==1) o micro não joga;
   if(q==0)
   micro(jogo,q);
  }
 }

 //Se o numero sorteado for 0, o micro começa jogando;
 else
 {
  //Enquanto ninguém ganhar (q==0), o laço continua;
  while(q==0)
  {
   micro(jogo,q);

   //Se o micro ganhar (q==1) o jogador não joga;
   if(q==0)
   jogador(jogo,q);
  }
 }
 getch();
}

int sorteio()
{
 int i;
 randomize();
 i=random(2);
 return i;
}

void preenche(char jogo[][3])
{

 /* Cada posição recebe espaço em branco para que a
    impressão fique identica ao jogo da velha */

 jogo[0][0]=' ';
 jogo[0][1]=' ';
 jogo[0][2]=' ';
 jogo[1][0]=' ';
 jogo[1][1]=' ';
 jogo[1][2]=' ';
 jogo[2][0]=' ';
 jogo[2][1]=' ';
 jogo[2][2]=' ';
}

void imprime(char jogo[][3])
{

 //Imprime uma matriz com a relação entre as letras e as posições;
 //a
 gotoxy(10,3);
 cout<<"a";
 cout<<char(179);
 gotoxy(10,4);
 cout<<char(196);
 gotoxy(11,4);
 cout<<char(197);
 //b
 gotoxy(12,3);
 cout<<"b";
 cout<<char(179);
 gotoxy(12,4);
 cout<<char(196);
 gotoxy(13,4);
 cout<<char(197);
 //c
 gotoxy(14,3);
 cout<<"c";
 gotoxy(14,4);
 cout<<char(196);
 //d
 gotoxy(10,5);
 cout<<"d";
 cout<<char(179);
 gotoxy(10,6);
 cout<<char(196);
 gotoxy(11,6);
 cout<<char(197);
 //e
 gotoxy(12,5);
 cout<<"e";
 cout<<char(179);
 gotoxy(12,6);
 cout<<char(196);
 gotoxy(13,6);
 cout<<char(197);
 //f
 gotoxy(14,5);
 cout<<"f";
 gotoxy(14,6);
 cout<<char(196);
 //g
 gotoxy(10,7);
 cout<<"g";
 cout<<char(179);
 //h
 gotoxy(12,7);
 cout<<"h";
 cout<<char(179);
 //i
 gotoxy(14,7);
 cout<<"i";

 //Imprime a matriz jogo em disposição de Jogo da Velha;
 //a
 gotoxy(10,10);
 cout<<jogo[0][0];
 cout<<char(179);
 gotoxy(10,11);
 cout<<char(196);
 gotoxy(11,11);
 cout<<char(197);
 //b
 gotoxy(12,10);
 cout<<jogo[0][1];
 cout<<char(179);
 gotoxy(12,11);
 cout<<char(196);
 gotoxy(13,11);
 cout<<char(197);
 //c
 gotoxy(14,10);
 cout<<jogo[0][2];
 gotoxy(14,11);
 cout<<char(196);
 //d
 gotoxy(10,12);
 cout<<jogo[1][0];
 cout<<char(179);
 gotoxy(10,13);
 cout<<char(196);
 gotoxy(11,13);
 cout<<char(197);
 //e
 gotoxy(12,12);
 cout<<jogo[1][1];
 cout<<char(179);
 gotoxy(12,13);
 cout<<char(196);
 gotoxy(13,13);
 cout<<char(197);
 //f
 gotoxy(14,12);
 cout<<jogo[1][2];
 gotoxy(14,13);
 cout<<char(196);
 //g
 gotoxy(10,14);
 cout<<jogo[2][0];
 cout<<char(179);
 //h
 gotoxy(12,14);
 cout<<jogo[2][1];
 cout<<char(179);
 //i
 gotoxy(14,14);
 cout<<jogo[2][2];
}

void jogador(char jogo[][3],int&q)
{
 char jogada;

 //Se o jogador jogar em uma posicao ocupada volta ate aqui;
 inicio:

 //Apaga a mensagem de erro de jogada se ela existir;
 cout<<"\n                                         ";

 imprime(jogo);

 //Abre o prompt para o jogador fazer sua opção;
 jogada=getch();

 if (jogada=='a')
 {
  if((jogo[0][0]!='O')&&(jogo[0][0]!='X'))
   jogo[0][0]='O';
  else
  {
   cout<<"\n\nJOGADA INVALIDA! JOGUE EM OUTRA LETRA!";
   goto inicio;
  }
 }

 if (jogada=='b')
 {
  if((jogo[0][1]!='O')&&(jogo[0][1]!='X'))
   jogo[0][1]='O';
  else
  {
   cout<<"\n\nJOGADA INVALIDA! JOGUE EM OUTRA LETRA!";
   goto inicio;
  }
 }

 if (jogada=='c')
 {
  if((jogo[0][2]!='O')&&(jogo[0][2]!='X'))
   jogo[0][2]='O';
  else
  {
   cout<<"\n\nJOGADA INVALIDA! JOGUE EM OUTRA LETRA!";
   goto inicio;
  }
 }
 if (jogada=='d')
 {
  if((jogo[1][0]!='O')&&(jogo[1][0]!='X'))
   jogo[1][0]='O';
  else
  {
   cout<<"\n\nJOGADA INVALIDA! JOGUE EM OUTRA LETRA!";
   goto inicio;
  }
 }

 if (jogada=='e')
 {
  if((jogo[1][1]!='O')&&(jogo[1][1]!='X'))
   jogo[1][1]='O';
  else
  {
   cout<<"\n\nJOGADA INVALIDA! JOGUE EM OUTRA LETRA!";
   goto inicio;
  }
 }
 if (jogada=='f')
 {
  if((jogo[1][2]!='O')&&(jogo[1][2]!='X'))
   jogo[1][2]='O';
  else
  {
   cout<<"\n\nJOGADA INVALIDA! JOGUE EM OUTRA LETRA!";
   goto inicio;
  }
 }

 if (jogada=='g')
 {
  if((jogo[2][0]!='O')&&(jogo[2][0]!='X'))
   jogo[2][0]='O';
  else
  {
   cout<<"\n\nJOGADA INVALIDA! JOGUE EM OUTRA LETRA!";
   goto inicio;
  }
 }

 if (jogada=='h')
 {
  if((jogo[2][1]!='O')&&(jogo[2][1]!='X'))
   jogo[2][1]='O';
  else
  {
   cout<<"\n\nJOGADA INVALIDA! JOGUE EM OUTRA LETRA!";
   goto inicio;
  }
 }

 if (jogada=='i')
 {
  if((jogo[2][2]!='O')&&(jogo[2][2]!='X'))
   jogo[2][2]='O';
  else
  {
   cout<<"\n\nJOGADA INVALIDA! JOGUE EM OUTRA LETRA!";
   goto inicio;
  }
 }

 cout<<"\n";

 //Confere se o jogador ganhou;
 confere1(jogo,q);

}
void confere1(char jogo[][3],int&q)
{
 char a,b,c,d,e,f,g,h,i;

 //Atribui o valor de cada posição a uma letra para facilitar a comparação;
 a=jogo[0][0];
 b=jogo[0][1];
 c=jogo[0][2];
 d=jogo[1][0];
 e=jogo[1][1];
 f=jogo[1][2];
 g=jogo[2][0];
 h=jogo[2][1];
 i=jogo[2][2];

 //Verifica cada possibilidade de fim de jogo;
 confere2(a,b,c,q,jogo);
 confere2(d,e,f,q,jogo);
 confere2(g,h,i,q,jogo);
 confere2(a,d,g,q,jogo);
 confere2(b,e,h,q,jogo);
 confere2(c,f,i,q,jogo);
 confere2(a,e,i,q,jogo);
 confere2(c,e,g,q,jogo);
 velha(jogo,q);
}

void confere2(char x,char y,char z,int&q,char jogo[][3])
{

 //Confere se o jogador ganhou;
 if((x==y)&&(y==z)&&(x=='O'))
 {
  cout<<"\n\n\n    PARABENS! VOCE VENCEU!\n\n";
  imprime(jogo);
  q=1;
 }

 //Confere se o computador ganhou;
 if((x==y)&&(y==z)&&(x=='X'))
 {
  cout<<"\n\n\n    VOCE PERDEU! TENTE NOVAMENTE!!\n\n";
  imprime(jogo);
  q=1;
 }
}

void velha(char jogo[][3],int&q)
{
 int l,c,v=0;

 //Confere se deu velha;
 for(l=0;l<3;l++)
 {
  for(c=0;c<3;c++)
  {
   if ((jogo[l][c]!='X')&&(jogo[l][c]!='O'))
    //Se v receber 1 é porque não deu velha ainda;
    v=1;
  }
 }
 if((v==0)&&(q!=1))
 {
  cout<<"\n\n\n    DEU VELHA!!! TENTE NOVAMENTE!!!\n\n";
  imprime(jogo);
  q=1;
 }
}

void micro(char jogo[][3],int&q)
{
 char a,b,c,d,e,f,g,h,i;
 int pa=1,pb=1,pc=1,pd=1,pe=1,pf=1,pg=1,ph=1,pi=1,j=0,l,col,s=0;

 //Antes de tudo joga estrategicamente no meio;
 if((jogo[1][1]!='O')&&(jogo[1][1]!='X'))
 {
  jogo[1][1]='X';
  j=1;
 }

 //Atribui o valor de cada posição a uma letra para facilitar a comparação;
 a=jogo[0][0];
 b=jogo[0][1];
 c=jogo[0][2];
 d=jogo[1][0];
 e=jogo[1][1];
 f=jogo[1][2];
 g=jogo[2][0];
 h=jogo[2][1];
 i=jogo[2][2];

 //Analisa o peso de cada jogada para o micro;
 analisa(a,b,c,pa,pb,pc);
 analisa(d,e,f,pd,pe,pf);
 analisa(g,h,i,pg,ph,pi);
 analisa(a,d,g,pa,pd,pg);
 analisa(b,e,h,pb,pe,ph);
 analisa(c,f,i,pc,pf,pi);
 analisa(a,e,i,pa,pe,pi);
 analisa(c,e,g,pc,pe,pg);


 //Executa a jogada mais importante de acordo com o peso 3;
 jogamicro(a,pa,j,3);
 jogamicro(b,pb,j,3);
 jogamicro(c,pc,j,3);
 jogamicro(d,pd,j,3);
 jogamicro(e,pe,j,3);
 jogamicro(f,pf,j,3);
 jogamicro(g,pg,j,3);
 jogamicro(h,ph,j,3);
 jogamicro(i,pi,j,3);


 //Executa a jogada mais importante de acordo com o peso 2;
 jogamicro(a,pa,j,2);
 jogamicro(b,pb,j,2);
 jogamicro(c,pc,j,2);
 jogamicro(d,pd,j,2);
 jogamicro(e,pe,j,2);
 jogamicro(f,pf,j,2);
 jogamicro(g,pg,j,2);
 jogamicro(h,ph,j,2);
 jogamicro(i,pi,j,2);

 //Atribui o valor de cada letra a cada posição para atualizar o jogo;
 jogo[0][0]=a;
 jogo[0][1]=b;
 jogo[0][2]=c;
 jogo[1][0]=d;
 jogo[1][1]=e;
 jogo[1][2]=f;
 jogo[2][0]=g;
 jogo[2][1]=h;
 jogo[2][2]=i;

 /* Analisa a configuração do jogo e cria uma jogada interessante
    de forma que o jogador adversário não encontre uma possibilidade
    de vencer. Se não houver nenhuma jogada especial disponível e
    nenhuma jogada de peso 2 ou 3, joga aleatoriamente; */

 if(pa==1)
  if(pb==1)
   if(pc==1)
    if(pd==1)
     if(pe==1)
      if(pf==1)
       if(pg==1)
        if(ph==1)
         if(pi==1)
         {
          ataque(j,jogo,a,b,c,f,i);
//          cout<<"\nflag "<<j;
          ataque(j,jogo,a,d,g,h,i);
//          cout<<"\nflag "<<j;
          ataque(j,jogo,c,b,a,d,g);
//          cout<<"\nflag "<<j;
          ataque(j,jogo,c,f,i,h,g);
//          cout<<"\nflag "<<j;
          ataque(j,jogo,i,f,c,b,a);
//          cout<<"\nflag "<<j;
          ataque(j,jogo,i,h,g,d,a);
//          cout<<"\nflag "<<j;
          ataque(j,jogo,g,d,a,b,c);
//          cout<<"\nflag "<<j;
          ataque(j,jogo,g,h,i,f,c);
//          cout<<"\nflag "<<j;

          //Atribui o valor de cada letra a cada posição para atualizar o jogo;
          jogo[0][0]=a;
          jogo[0][1]=b;
          jogo[0][2]=c;
          jogo[1][0]=d;
          jogo[1][2]=f;
          jogo[2][0]=g;
          jogo[2][1]=h;
          jogo[2][2]=i;

          if(j!=1)
          {
           randomize();
           comput:
           l=random(3);
           col=random(3);
           while(s==0)
           {
            //Confere se a posição gerada está ocupada;
            if((jogo[l][col]!='O')&&(jogo[l][col]!='X'))
            {
             jogo[l][col]='X';
             s=1;
            }
            //Se a posição estiver ocupada gera outra;
            else goto comput;
           }
          }
         }
 confere1(jogo,q);
 j=0;

}

void analisa(char x,char y,char z,int&px,int&py,int&pz)
{
 /* Analisa cada possibilidade do adversário vencer
   e atribui peso 2 à jogada que vai impedir */

 if((x==y)&&(x=='O')&&(z!='X'))
 {
  pz=2;
 }

 if((x==z)&&(x=='O')&&(y!='X'))
 {
  py=2;
 }

 if((y==z)&&(y=='O')&&(x!='X'))
 {
  px=2;
 }

 /* Analisa cada possibilidade do micro vencer na
    próxima jogada e atribui peso 3 para a jogada */

 if((x==y)&&(x=='X')&&(z!='O'))
 {
  pz=3;
 }

 if((x==z)&&(x=='X')&&(y!='O'))
 {
  py=3;
 }

 if((y==z)&&(y=='X')&&(x!='O'))
 {
  px=3;
 }
}

void jogamicro(char&x,int px,int&flag,int peso)
{

 /* Se o peso da posição for igual ao peso passado
    como parâmetro, o micro efetua a jogada */

 if((px==peso)&&(flag!=1))
 {
  x='X';
  flag=1;
 }
}

void ataque(int&flag,char jogo[][3],char&u,char&v,char&x,char&y,char&z)
{

  //Analisa a configuração atual do jogo e arma uma jogada conhecida;
  if((u==v)&&(v==x)&&(x==y)&&(y==z)&&(z==' ')&&(flag!=1))
  {
   if((u!='X')&&(u!='O'))
   {
    u='X';
    flag=1;
   }
  }

  if((u=='X')&&(v==x)&&(x==y)&&(y==z)&&(z==' ')&&(flag!=1))
  {
   if((y!='X')&&(y!='O'))
   {
    y='X';
    flag=1;
   }
  }

  if((u=='X')&&(v==x)&&(x==y)&&(z=='O')&&(flag!=1))
  {
   if((jogo[1][1]!='X')&&(jogo[1][1]!='O'))
   {
    jogo[1][1]='X';
    flag=1;
   }
  }

  if((u=='X')&&(v==x)&&(x==z)&&(z==' ')&&(y=='X')&&(flag!=1))
  {
   if((x!='X')&&(x!='O'))
   x='X';
   flag=1;
  }
}

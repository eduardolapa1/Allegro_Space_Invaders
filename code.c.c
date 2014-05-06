#include <allegro.h>
#include <stdio.h>
#define TELA_X 640
#define TELA_Y 480
void FecharJanela(void);
void inicializa_blocos(void);
void colisaoBlocos(void);
enum boolean {
    true = 1, false = 0
};
typedef  enum boolean  bool; //cria um tipo booleano,muito util!:D
typedef struct personagemt
{
	int x, y,espera,orientacao;
        bool status,data,disparo;

}inimigo;
struct EDisparoinimigo
{
	int x, y,
	    animacao, quadro,
        status,
	    Ntiro,
	    orientacao;
} EDisparoinimigo;

typedef struct blocos
{
	int x, y,
	    status;
}blocos;
int mortos=0;
bool fechar=false;
void controla_tanque(void);
void naveIA(void);
void colisaoNave(void);
void alienIA(int Tipo,int NAlien);
void inicializa_alien(void);
void ExeAliens(void);
void colisaoAlien(void);
void tiroAlien(void);
 int tanquex=328,tanquey=431;
 bool tanqueTiro=false;
 int tanqueTiroX,tanqueTiroY;
  int tanqueVida=3;
  int pontos=0;
 int NaveEspera=0;
 int naveX,naveY;
 int NaveStatus=false;
 int t1,p1;
 inimigo alien[3][5];
blocos EBloco[15];
int main()
{
    EDisparoinimigo.x=0;
EDisparoinimigo.y=0;
EDisparoinimigo.Ntiro=4;
EDisparoinimigo.status=0;
EDisparoinimigo.orientacao=0;
    int i,j;
    int x=220,y=100;
    int func = 0;
    bool fullscreen=false;
    bool som=true;
    int faseV=50;
    BITMAP *TELA;
    allegro_init(); //inicializa o allegro
    install_keyboard(); //habilita funcoes de  teclado
    install_mouse(); //habilita funcoes de mouse
    set_color_depth(16); //modo 16 bits de cor
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,TELA_X,TELA_Y,0,0)) //resolucao 640x480 nao fullscreen
    {
        //se der merda
        allegro_message("Problems na inicializacao do video!Erro:%s",allegro_error); // manda msg pro user fica putasso
        exit(1);  //e sai sorrateiramente...
    }
    if(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL)) //inicializa funcoes de audio
    {
        //se der merda
        allegro_message("Problems na inicializacao do som!Erro:%s",allegro_error); // manda msg pro user fica putasso
        exit(1); //e sai sorrateiramente...
    }
    set_window_title("Space Invaders"); //muda titulo de janela para Space invaders
    TELA = create_bitmap(TELA_X,TELA_Y); //util para tecnica de screen buffer
     BITMAP *fundo;
    fundo = create_bitmap(640,480);
    fundo = load_bitmap("image/back.bmp",NULL);
     BITMAP *alien1=create_bitmap(59,50);
    alien1=load_bitmap("image/sprites4.bmp",NULL);
    BITMAP *tanque=create_bitmap(51,46);
    tanque=load_bitmap("image/tanque0.bmp",NULL);
    BITMAP *tiro;
    tiro=create_bitmap(10,9);
    tiro=load_bitmap("image/tiro.bmp",NULL);
    BITMAP *naveB;
    naveB=load_bitmap("image/navebonus1.bmp",NULL);
    MIDI *musica;
    musica = load_midi("som/fundo.mid");
    inicializa_alien();
    inicializa_blocos();
    BITMAP *alienB[3][5];
    BITMAP *blocosperfeitos[15];
    BITMAP *blocosdanificados[15];
    BITMAP *blocosfudidos[15];
    for(i=0;i<15;i++)
    {
        blocosperfeitos[i]=create_bitmap(18,18);
        blocosperfeitos[i]=load_bitmap("image/bloco0.bmp",NULL);
        blocosdanificados[i]=create_bitmap(18,18);
        blocosdanificados[i]=load_bitmap("image/bloco1.bmp",NULL);
        blocosfudidos[i]=create_bitmap(18,18);
         blocosfudidos[i]=load_bitmap("image/bloco2.bmp",NULL);
    }
    for(i=0;i<3;i++)
    {
        for(j=0;j<5;j++)
        {
            alienB[i][j]=create_bitmap(59,50);
                if(i==0)
                {
                    alienB[i][j]=load_bitmap("image/sprites0.bmp",NULL);
                }
                else if(i==1)
                {
                    alienB[i][j]=load_bitmap("image/sprites2.bmp",NULL);
                }
                else if(i==2)
                {
                        alienB[i][j]=load_bitmap("image/sprites4.bmp",NULL);
                }
    }
    }
    if(!fundo || !alien1) //se de problema na image
    {
        allegro_message("Erro ao carregar imagem!");
        exit(1);
    }
    if(!som)
    {
        allegro_message("Problemas para iniciar som!");
        exit(1);
    }
    set_close_button_callback(FecharJanela); //se apertar x entao chama a funcao fecharjanela
    play_midi(musica,TRUE);
    text_mode(-1); //texto transparente
    while(!(key[KEY_ESC] || fechar)) //enquanto o usuario não achou o jogo um lixo e apertou esc,ou fechou pela janela xD
    {

        if(func == 0)
        { //esse e o menu
            blit(fundo,TELA, 0, 0, 0, 0, 640, 480); //copia fundo para bitmap TELA
            textout_centre(TELA, font, "Space Invaders", 320,20 , makecol(0,255,0));
            textout_centre(TELA,font,"1.Jogar",320,120,makecol(0,255,0));
            if(fullscreen==true) //se estiver em modo fullscreen
                textout_centre(TELA,font,"2.Janela",320,140,makecol(0,255,0));
            else
                textout_centre(TELA,font,"2.Fullscreen",320,140,makecol(0,255,0));
            textout_centre(TELA,font,"3.Som",320,160,makecol(0,255,0));
            textout_centre(TELA,font,"4.Sair",320,180,makecol(0,255,0));
             masked_blit(alien1,TELA, 0, 0, x, y, 59, 50);
             if(key[KEY_UP])
             {
                y-=20;
             }
            if(key[KEY_DOWN])
            {
                y+=20;
            }
            if(y<100 || y>160) //se o usuario mexeu ao extremo para cima ou para baixo
                y=100;
            if(key[KEY_ENTER]) //se o usuario apertar enter verificar a opcao desejada
            {
                if(y==100)
                {
                    inicializa_alien();
                    tanqueVida=3;
                    pontos=0;
                    inicializa_blocos();
                    func=1; //variavel func cuida quando o jogo vai ser inicializado,se for 1 o jogo comeca
                }
                if(y==120)
                {
                    if(fullscreen==false)
                    {
                        set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,TELA_X,TELA_Y,0,0);
                        fullscreen=true;
                    }
                    else
                    {
                        set_gfx_mode(GFX_AUTODETECT_WINDOWED,TELA_X,TELA_Y,0,0);
                        fullscreen=false;
                    }
                }
                if(y==140)
                {
                    if(som==true) //se tiver tocando midi
                        stop_midi();  //para
                    else
                        play_midi(musica,TRUE);
                }
                if(y==160)
                    fechar=true;
            }

            blit(TELA,screen, 0, 0, 0, 0, TELA_X, TELA_Y); //copia TELA para o monitor
            }
        if(func==1)
        {
            clear(TELA);
            naveIA();
            ExeAliens();
            masked_blit(fundo,TELA,0,0,0,0,TELA_X,TELA_Y);
            masked_blit(tanque,TELA, 0, 0, tanquex,tanquey ,59, 50);
            for(i=0;i<3;i++)
            {
                for(j=0;j<5;j++)
                {
                    if(alien[i][j].status==true)
                    {
                        masked_blit(alienB[i][j],TELA,0,0,alien[i][j].x,alien[i][j].y,59,50);
                    }
                    printf("x=%d,y=%d\n",alien[i][j].x,alien[i][j].y);
                }
            }
            tiroAlien();
            if(EDisparoinimigo.status==1)
            {
                masked_blit(tiro,TELA,0,0,EDisparoinimigo.x,EDisparoinimigo.y,10,9);
                EDisparoinimigo.y+=5;
                if(EDisparoinimigo.y>620)
                    EDisparoinimigo.status=0;
                if(EDisparoinimigo.x >= tanquex && EDisparoinimigo.x<=tanquex+51 && EDisparoinimigo.y >= tanquey && EDisparoinimigo.y<=tanquey+46)
                {
                    EDisparoinimigo.status=0;
                    tanqueVida--;
                }
            }
            if(tanqueTiro==true)
            {
                masked_blit(tiro,TELA,0,0,tanqueTiroX,tanqueTiroY,10,9);
                tanqueTiroY-=5;
                colisaoNave();
                colisaoAlien();
            }
            if(NaveStatus==true)
            {
                 masked_blit(naveB,TELA,0,0,naveX,naveY,57,30);
                 naveX-=5;
            }
             for(i=0;i<15;i++)
            {
                if(EBloco[i].status==3)
                {
                    masked_blit(blocosperfeitos[i],TELA,0,0,EBloco[i].x,EBloco[i].y,18,18);
                }
                else if(EBloco[i].status==2)
                {
                    masked_blit(blocosdanificados[i],TELA,0,0,EBloco[i].x,EBloco[i].y,18,18);
                }
                else if(EBloco[i].status==1)
                {
                    masked_blit(blocosfudidos[i],TELA,0,0,EBloco[i].x,EBloco[i].y,18,18);
                }
            }
            textprintf(TELA,font,10,10,makecol(255,255,255),"Pontos: %i",pontos);
            textprintf(TELA,font,580,10,makecol(255,255,255),"Vida: %i",tanqueVida);
            blit(TELA,screen, 0, 0, 0, 0, TELA_X, TELA_Y); //copia TELA para o monitor
            controla_tanque();
            colisaoBlocos();
            if(tanqueVida==0)
            {
                faseV=50;
                func=0;
            }
            if(mortos>=15)
            {
                mortos=0;
                faseV-=5;
              inicializa_alien();
            }
        }
       rest(faseV); //controla a velocidade do jogo,inicialmente comeca com 50,depois vai diminuindo pra ficar mais rapido
    }
     END_OF_MAIN()
    return 0;
}
 void FecharJanela() //essa função é chamada quando o evento de saida é tratado
    {
        fechar=true; //muda o valor de fechar para true,saindo assim do loop
    }END_OF_FUNCTION(FecharJanela)

void controla_tanque() //funcao para o controle do tanque
{
    if(key[KEY_SPACE] && tanqueTiro==false) //verifica se o usuario apertou a tecla de espaco,se sim ele atirou,verifica também se o tiro está desativado impossiblitando 2 tiros ao msmo tempo
    {
        tanqueTiro=true;//muda o valor de tanqueTiro para true
        tanqueTiroX=tanquex+20;//possiciona o tiro em cima da cabeca do tanque
        tanqueTiroY=tanquey;//posição y do tiro é igual a posicao y do tanque
    }
    if(key[KEY_LEFT])
    {
        if(tanquex>46)
        {
        tanquex-=5; //tanque não pode passar dos extremos da tela,a esquerda
        }
    }
    else if(key[KEY_RIGHT])
    {
        if(tanquex<520)
        {
            tanquex+=5; //o tanque não pode passar dos extremos da tela,a esquerda
        }
    }
    if(tanqueTiro==true && tanqueTiroY<0) //se o tiro chegou ao extremo superior da tela
        tanqueTiro=false;
}

void naveIA(void)
{
    NaveEspera++; //vai incrimentando NaveEspera
    if(NaveEspera>50 && NaveStatus==false) //quando NaveEspera eh maior que 50 e ja n tenha aparecido
    {
        NaveStatus=true; //Nave se ativa
        naveX=520,naveY=37; //inicia no canto superior direito da tela
    }
}
void colisaoNave() //funcao responsavel pela detectacao de colisao entre o tiro e a nave
{
        if(tanqueTiroX >= naveX && tanqueTiroX <= naveX+57 && tanqueTiroY >= naveY && tanqueTiroY<=naveY+30 && NaveStatus==true) //verifica se a posicao x  do tiro estiver entre a posicao x da nave + sua largura e se a posicao y+altura esta entre a posicao y+altura da nave
        {
            NaveStatus=false; //se estiver entao o status é negativo
            NaveEspera=0; //reinicia a contagem para a nave aparecer denovo
            tanqueTiro=false; //se o tiro acertou entao some
            pontos+=30; //soma os pontos do usuario com 30
        }
        if(naveX<0 && NaveStatus==true) //se a nave atravessou toda tela entao desaparece e reinicia a contagem
        {
            NaveStatus=false;
            NaveEspera=0;
        }
}
void inicializa_alien(void) //funcao responsavel por posicionar os aliens na tela
{
    int i,j,pontox=320,pontoy=67,valorx=0,valory=0;

    for(i=0;i<3;i++)
    {
        for(j=0;j<5;j++)
        { //percorre a matriz,os aliens sao divididos em 3 tipos cada tipo em uma posicao y somada com 59 do tipo anterior,a variavel I é responsavel pelos tipos e a J responsavel pela classe dos aliens
            alien[i][j].x=pontox+valorx; //soma o alien com o ponto inicial mais valorX responsavel pelo espacamento entre um alien e o outro
            alien[i][j].y=pontoy+valory; //soma o alien com o ponto y mais valorY responsavel pela altura
            alien[i][j].data=true;
            alien[i][j].status=true; //ativa todos os aliens
            valorx=valorx+59; //vai somando com 59 para causar o espacamento
        }
        valory=valory+50; //soma valory com 50,o tipo mudou,os proximos se posicionaram acima
        valorx=0; //valorx volta a 0,os aliens se organizaram em colunas
    }
}
void inicializa_blocos(void)
{
    int i;
    //posiciona os blocos
    EBloco[0].x=212; EBloco[0].y=315;
EBloco[1].x=324; EBloco[1].y=315;
EBloco[2].x=342; EBloco[2].y=315;
EBloco[3].x=360
; EBloco[3].y=315;
EBloco[4].x=194; EBloco[4].y=315;
EBloco[5].x=212; EBloco[5].y=315;
EBloco[6].x=324; EBloco[6].y=315;
EBloco[7].x=342; EBloco[7].y=315;
EBloco[8].x=360; EBloco[8].y=315;
EBloco[9].x=25; EBloco[9].y=333;
EBloco[10].x=61; EBloco[10].y=333;
EBloco[11].x=176; EBloco[11].y=333;
EBloco[12].x=212; EBloco[12].y=333;
EBloco[13].x=324; EBloco[13].y=333;
EBloco[14].x=360; EBloco[14].y=333;
for(i=0;i<15;i++)
{ //ativa todos os blocos,os blocos terao 3 estados,o 3 é o estado perfeito
        EBloco[i].status=3;
}
}

void alienIA(int Tipo,int NAlien) //responsavel pela movimentacao dos aliens na tela
{

if(alien[Tipo][NAlien].status==true) //se o alien estiver ativo
{
    if(alien[Tipo][NAlien].orientacao==0) //verifica a orientacao do alien,sao 2,esquerda e direia
    {
        alien[Tipo][NAlien].x-=2; //vai indo para a esquerda
    }
}
if (alien[Tipo][NAlien].x<40) //se o alien chegar a exrema esquerda
{
    alien[Tipo][NAlien].x+=2; //alien vai para a direita
    for(t1=0; t1<3; t1++)
    {
        for (p1=0; p1<5; p1++) //percorre a lista de aliens
    {
            alien[t1][p1].orientacao=1; //muda a orientacao
            alien[t1][p1].y+=5; //vai para baixo
    }
}
}
    if (alien[Tipo][NAlien].orientacao==1) //se a orientação estiver 1 entao alien esta indo para direita
{
    alien[Tipo][NAlien].x+=2; //vai levando alien para a direita
}
    if (alien[Tipo][NAlien].x>580) //se alien atingir a extrema esquerda
{
    for (t1=0; t1<3; t1++)
{
        for (p1=0; p1<5; p1++)
{ //percorre a matriz de aliens
    alien[t1][p1].orientacao=0; //muda orientacao para direta
    alien[t1][p1].y+=5; //puxa alien para direta
}
}
}
if(alien[Tipo][NAlien].y>431)
    { //se alien chegar embaixo
           tanqueVida=0; //vida acaba,gameover
    }

}
void ExeAliens()
{
    int t,p;
for (t=0; t<3; t++)
 {
  for (p=0; p<5; p++)
  {
   if (alien[t][p].status==true)
    {
     alienIA(t, p);
    }
  }// fecha segundo for
 }// fecha primeiro for

}
void colisaoAlien()
{
    int t,p;
    for(t=0;t<3;t++)
    {
        for(p=0;p<5;p++)
        { //percorre toda lista
              if(tanqueTiroX >= alien[t][p].x && tanqueTiroX <= alien[t][p].x + 59 && tanqueTiroY >= alien[t][p].y && tanqueTiroY<=alien[t][p].y +50 && alien[t][p].status==true)
              {  //verifica se ouve alguma colisao entre tiro e os aliens,verica se  tanquetirox esta entre alien.x e alien.x+59 que é sua largura,o mesmo com o tanquetiroy se está entre alien.y +50 sua altura
                  mortos++;
                  pontos+=5;
                  alien[t][p].status=false;
                  tanqueTiro=false;
              }

        }
    }
}


void tiroAlien()
{
    if (EDisparoinimigo.status==false)
  { //verifica se nenhum disparo foi feito

   if (alien[2][EDisparoinimigo.Ntiro].status==true) //verifica o status de cada tiro ligado a alien, se for verdadeiro posiciona tiro
    {
     EDisparoinimigo.status=1;
     EDisparoinimigo.x=alien[2][EDisparoinimigo.Ntiro].x+25;
     EDisparoinimigo.y=alien[2][EDisparoinimigo.Ntiro].y+50;
    }

   else if (alien[1][EDisparoinimigo.Ntiro].status==true)
    {
     EDisparoinimigo.status=1;
     EDisparoinimigo.x=alien[1][EDisparoinimigo.Ntiro].x+25;
     EDisparoinimigo.y=alien[1][EDisparoinimigo.Ntiro].y+50;
    }

   else if (alien[0][EDisparoinimigo.Ntiro].status==true)
    {
     EDisparoinimigo.status=1;
     EDisparoinimigo.x=alien[0][EDisparoinimigo.Ntiro].x+25;
     EDisparoinimigo.y=alien[0][EDisparoinimigo.Ntiro].y+50;
    }




   if (EDisparoinimigo.orientacao==0 && EDisparoinimigo.Ntiro>0) //verifica se o tiro esta partindo da direita para esquerda
    {
     EDisparoinimigo.Ntiro--;
      if (EDisparoinimigo.Ntiro==0) //se chegar a fim muda orcientação
       {
        EDisparoinimigo.orientacao=1;
        EDisparoinimigo.Ntiro--;
       }
    }

   if (EDisparoinimigo.orientacao==1 && EDisparoinimigo.Ntiro<4)
    {
     EDisparoinimigo.Ntiro++;
      if (EDisparoinimigo.Ntiro==4)
       {
        EDisparoinimigo.orientacao=0;
       }
    }

  }
}
void colisaoBlocos()
{
        int i;
        if(tanqueTiro==true)
        {
        for(i=0;i<15;i++)
        { //percorre o vetor com todos os blocos e verifica se tiro colidiu com blocos
            if(EBloco[i].status>0 && tanqueTiroX >= EBloco[i].x && tanqueTiroX<=EBloco[i].x+18 && tanqueTiroY>=EBloco[i].y && tanqueTiroY <=EBloco[i].y+18)
            {
                EBloco[i].status--; //se colidiu desincrementa seu estado
                tanqueTiro=false; //se colidiu tiro some
            }
        }
        }
        if(EDisparoinimigo.status==true)
        {
             for(i=0;i<15;i++)
        {
            if(EBloco[i].status>0 && EDisparoinimigo.x>=EBloco[i].x && EDisparoinimigo.x<=EBloco[i].x+18 && EDisparoinimigo.y>=EBloco[i].y && EDisparoinimigo.y <=EBloco[i].y+18)
            {
                EBloco[i].status--;
                EDisparoinimigo.status=false;
            }
        }
        }
}








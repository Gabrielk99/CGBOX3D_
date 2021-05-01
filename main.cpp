#include <stdio.h>
#include "util.h"
#include <string>
#include <stdlib.h>
//Controle dos incrementos
#define inc_andar 0.25
#define inc_girar 0.15
#define inc_soca1  0.5
#define inc_soca2  0.33
#define max_angle_soca 13
#define max_angle_perna1 60
#define inc_anglep 0.30
#define view 500
//janela
float h1 = view;
float w1 = view;

//Criando os as variaveis que guardam as informações necessárias de cada objeto
Arena arena;
Inimigo inimigo;
Jogador jogador;
//Status dos controles
int keyStatus[256];
//Controla angulo dos socos
int soca=0;
//controla o braço a socar
float initialx=0;
//controla movimento inimigo
bool IAactive = false;
bool moveI = true;
bool podeGirar = true;
//controla perna jogador
bool voltouPernaD = false;
bool voltouPernaE = false;
//controla perna inimigo
bool voltouPernaDi=false;
bool voltouPernaEi=false;
//controla soco do inimigo
float incSocoAcc = 0;
int socoDirection = 0;
bool finalizousoco = false;
//controla fim de jogo
bool fim = false;
using namespace std;
//controla camera
double camDist=0;
double camXYAngle=30;
double camXZAngle=0;
int toggleCam = 0;
int camAngle = 90;
int lastX = 0;
int lastY = 0;
int buttonDown=0;
//Controla iluminação
bool noturno = false;
// controla textura do jogador
int jogadorT = 0;
GLuint jogadorHT[4];
// controla textura do inimigo
int inimigoT = 0;
GLuint inimigoHT[4];
//control texture mode
bool activeT=true;
//controle do help
bool help = true;
//rotaciona Win
float angleWin=0;
//ImprimePlacar
static char str[1000];
void *font = GLUT_BITMAP_9_BY_15;
void changeCamera(int w,int h);
void imprimePlacar(GLfloat x,GLfloat y){
    glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        //define cor branca
        glColor3f(1,1,1);
        char*tmpStr;
        //escreve a mensagem de score do jogador
        sprintf(str,"JogadorScore : %d",jogador.returnPontuation());
        //coloca na posição 
        glRasterPos3f(x,y,0);
        //passa para o ponteiro
        tmpStr=str;
        //imprime a mensagem na tela
        while(*tmpStr){
            glutBitmapCharacter(font,*tmpStr);
            tmpStr++;
        }
        //escreve mensagem de score do inimigo
        sprintf(str,"InimigoScore : %d",inimigo.returnPontuation());
        //coloca a posição correta
        tmpStr=str;
        float deslocx = glutBitmapLength(font,(const unsigned char*)tmpStr);
        deslocx/=w1;
        glRasterPos3f(x+1-deslocx,y,0);
      
        while(*tmpStr){
            glutBitmapCharacter(font,*tmpStr);
            tmpStr++;
        }
    glPopAttrib();
}
//Imprime Mensagem De Vitoria
void imprimeVitoria(GLfloat x,GLfloat y,int qual,GLfloat R,GLfloat G,GLfloat B){
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    //define a cor da mensagem
    glColor3f(R,G,B);
    char*tmpStr;
    // escolhe se quem ganhou foi jogador ou inimigo
    if(qual == 1){
        sprintf(str,"JOGADOR WIN");
    }
    else if(qual ==2){
        sprintf(str,"JOGADOR LOSE");
    }
    tmpStr=str;
    // mensagem fica no meio da tela, calcula o tamanho da mensagem
    // para deslocar metade para esquerda do meio e metade para a direita
    float deslocx = glutBitmapLength(font,(const unsigned char*)tmpStr)/2.0f;
    glRasterPos2f(x-deslocx/w1,y);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    glPopAttrib();
}

//redefine lookat
void redefineLookAt(){
    float x,y,z;
    jogador.getEyesPosition(x,y,z);
    float raio;
    jogador.obtemRaio(raio);
    float eyex,eyey,eyez;
    if(toggleCam==0){
        float focusx,focusy,focusz;
        jogador.getFocusPosition(focusx,focusy,focusz);
        gluLookAt(x,y,z,focusx,focusy,focusz,0,1,0);
    }
    else if(toggleCam==1){
        jogador.getPulsoPosition(x,y,z);
        float focusx,focusy,focusz;
        float upx,upy,upz;
        jogador.getUpPosition(upx,upy,upz);
        jogador.getPulsoFocusPosition(focusx,focusy,focusz);
        gluLookAt(x,y,z,focusx,focusy,focusz,upx,upy,upz);
    }
    else if(toggleCam==2){
        float cx,cy,cz;
        jogador.obtemcXcYcZ(cx,cy,cz);
        eyex =cx-camDist*sin(camXZAngle*M_PI/180)*cos((camXYAngle*M_PI/180));
        eyey =cy+camDist*sin((camXYAngle*M_PI/180));
        eyez =cz-camDist*cos(camXZAngle*M_PI/180)*cos((camXYAngle*M_PI/180));
        gluLookAt(eyex,eyey,eyez,cx,cy,cz,0,1,0);
    }

}
//desenha as luzes e aplica as luzes
void DesenhaLuz(float altura,float largura,float comprimento){
    GLfloat materialEmission[] = { 0.5, 0.5, 0.5, 1};
    GLfloat materialColor[] = { 1.0, 1.0, 0.0, 1};
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = { 50.0 };
   
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );

    glBindTexture (GL_TEXTURE_2D, 0);
    float positionx,positiony,positionz;

    positionx = largura/2;
    positionz = comprimento/2;
    positiony = altura;

    GLfloat light_position[] = {positionx, positiony-25, positionz, 1};
    if(!noturno){
        glEnable(GL_LIGHT0);
        GLfloat light0_ambient [] = {0, 0, 0, 1.0};
        GLfloat light0_diffuse [] = {5.0, 5.0, 5.0, 1.0};
        GLfloat light0_specular [] = {5.0, 5.0, 5.0, 1.0};
        glLightfv (GL_LIGHT0, GL_AMBIENT, light0_ambient);
        glLightfv (GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
        glLightfv (GL_LIGHT0, GL_SPECULAR, light0_specular);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
        glLightfv(GL_LIGHT0,GL_POSITION,light_position);
        
    }
   glPushMatrix(); 
            glTranslatef(positionx,positiony,positionz);
            glutSolidSphere(20,20,10);
    glPopMatrix();
    if(noturno){
       //holofote do jogador
       float cx,cy,cz;
       jogador.obtemcXcYcZ(cx,cy,cz);
       float spot_position[] = {largura/2,altura,comprimento/2,1};
       glDisable(GL_LIGHT0);
       GLfloat light1_ambient [] = {0.0, 0.0, 0.0, 1.0};
       GLfloat light1_diffuse [] = {10.0, 10.0, 10.0, 1.0};
       GLfloat light1_specular [] = {3.0, 3.0, 3.0, 1.0};
       glLightfv (GL_LIGHT1, GL_AMBIENT, light1_ambient);
       glLightfv (GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
       glLightfv (GL_LIGHT1, GL_SPECULAR, light1_specular);
       glEnable(GL_LIGHT1);
       glLightfv(GL_LIGHT1,GL_POSITION,spot_position);
       
       float spot_direction[] = {cx,jogador.retornaAltura()/2,cz};
       spot_direction[0]=spot_direction[0]-spot_position[0];
       spot_direction[1]=spot_direction[1]-spot_position[1];
       spot_direction[2]=spot_direction[2]-spot_position[2];
      
       glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,20);
       glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,spot_direction);
       glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,1);

       //holofote do inimigo
       inimigo.obtemcXcYcZ(cx,cy,cz);
       glLightfv (GL_LIGHT2, GL_AMBIENT, light1_ambient);
       glLightfv (GL_LIGHT2, GL_DIFFUSE, light1_diffuse);
       glLightfv (GL_LIGHT2, GL_SPECULAR, light1_specular);
       glEnable(GL_LIGHT2);
       glLightfv(GL_LIGHT2,GL_POSITION,spot_position);
    
       float spot_direction1[] = {cx,inimigo.retornaAltura()/2,cz};
       spot_direction1[0]=spot_direction1[0]-spot_position[0];
       spot_direction1[1]=spot_direction1[1]-spot_position[1];
       spot_direction1[2]=spot_direction1[2]-spot_position[2];
      
       glLightf(GL_LIGHT2,GL_SPOT_CUTOFF,20);
       glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,spot_direction1);
       glLightf(GL_LIGHT2,GL_SPOT_EXPONENT,1);

    }
}
//desenha o delimitador do minimapa
void desenhaQuadrado(float w,float h){
    glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glColor3f(1.0,0,0);
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
            glVertex3f(-w/2,0,0);
            glVertex3f(w/2,0,0);
            glVertex3f(w/2,h,0);
            glVertex3f(-w/2,h,0);
        glEnd();
    glPopAttrib();
}
//desenha circulo pro minimapa
void drawCircle(float r,GLfloat R,GLfloat G,GLfloat B){
    int num_seg = 150;
   glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glColor3f(R,G,B);
        glBegin(GL_POLYGON);
            for(int i = 0; i<num_seg;i++){

                float theta = (2.0*M_PI/float(num_seg))*float(i);
                double x = r*cos(theta);
                double y = r*sin(theta);

                glVertex3f(x,y,0);
            }
        glEnd();
    glPopAttrib();
}
//desenha mini mapa
void miniMap(){
    float cx,cy,cz;
    jogador.obtemcXcYcZ(cx,cy,cz);
    double largura,comprimento;
    arena.obtemAlturaLargura(largura,comprimento);
    float r;
    float raioP ;
    jogador.obtemRaio(raioP);
    
    float altura;
    float larg;
    if(largura>comprimento){
        larg=0.25;
        altura = comprimento/largura*0.25;
        r=raioP/largura*0.25;
    }
    else{
        altura=0.25;
        larg=largura/comprimento*0.25;
        r=raioP/comprimento*0.25;
    }
    
    cx = r+(cx-raioP)/(largura-2*raioP)*(larg-2*r);
    cz = r+(cz-raioP)/(comprimento-2*raioP)*(altura-2*r);

    float cxi,cyi,czi;
    inimigo.obtemcXcYcZ(cxi,cyi,czi);
    cxi = r+(cxi-raioP)/(largura-2*raioP)*(larg-2*r);
    czi = r+(czi-raioP)/(comprimento-2*raioP)*(altura-2*r);
    cx= larg-cx;
    cxi= larg-cxi;
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(0,1,0,1,-1,1);
        glTranslatef(0.75+0.125,0.0,0);
        desenhaQuadrado(larg,altura);
        glPushMatrix();
            glTranslatef(cxi-larg/2,czi,0);
            drawCircle(r,1,0,0);
        glPopMatrix();
        glTranslatef(cx-larg/2,cz,0);
        drawCircle(r,0,1,0);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
//call placar
void callPlacar(){
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(0,1,0,1,-1,1);
        imprimePlacar(0,0.95);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
void imprimeHelp (float x,float y){
    //define a cor da mensagem
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3f(1,0,1);
    char*tmpStr;
    sprintf(str,"HELP");
    tmpStr=str;
    // mensagem fica no meio da tela, calcula o tamanho da mensagem
    // para deslocar metade para esquerda do meio e metade para a direita
    float deslocx = glutBitmapLength(font,(const unsigned char*)tmpStr)/2.0f;
    glRasterPos2f(x-deslocx/w1,y);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    glPopAttrib();
}
void imprimeRules(float x,float y){
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3f(1,1,1);
    char*tmpStr;
    sprintf(str,"H - Pausa o jogo e mostra teclas");
    tmpStr=str;
    glRasterPos2f(x,y);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    sprintf(str,"W S A D - Movimenta o personagem");
    tmpStr=str;
    glRasterPos2f(x,y+0.05);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    sprintf(str,"0 - Ativa oponente ");
    tmpStr=str;
    glRasterPos2f(x,y+0.1);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    sprintf(str,"1 - Camera primeira pessoa");
    tmpStr=str;
    glRasterPos2f(x,y+0.15);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    sprintf(str,"2 - Camera pulso");
    tmpStr=str;
    glRasterPos2f(x,y+0.20);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    sprintf(str,"3 - Camera terceira pessoa");
    tmpStr=str;
    glRasterPos2f(x,y+0.25);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    sprintf(str,"Mouse Click L (arraste) - SOCA");
    tmpStr=str;
    glRasterPos2f(x,y+0.3);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    sprintf(str,"N - Modo noturno (clique denovo e desative)");
    tmpStr=str;
    glRasterPos2f(x,y+0.35);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    sprintf(str,"T - Ativa e desativa textura");
    tmpStr=str;
    glRasterPos2f(x,y+0.4);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    sprintf(str,"R - Reseta game");
    tmpStr=str;
    glRasterPos2f(x,y+0.45);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    sprintf(str,"J - Troca textura do jogador");
    tmpStr=str;
    glRasterPos2f(x,y+0.5);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    sprintf(str,"I - Troca textura do inimigo");
    tmpStr=str;
    glRasterPos2f(x,y+0.55);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    sprintf(str,"ESC - Sai do Jogo");
    tmpStr=str;
    glRasterPos2f(x,y+0.6);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    glPopAttrib();
}
//call help 
void callHelp(){
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(0,1,0,1,-1,1);
        imprimeHelp(0.5,0.8);
        imprimeRules(0.05,0.1);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
void imprimeWin(float x,float y,float z,GLfloat R,GLfloat G,GLfloat B){
 glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    //define a cor da mensagem
    glColor3f(R,G,B);
    char*tmpStr;
   
    sprintf(str,"WIN");
    
    tmpStr=str;
    // mensagem fica no meio da tela, calcula o tamanho da mensagem
    // para deslocar metade para esquerda do meio e metade para a direita
    float deslocx = glutBitmapLength(font,(const unsigned char*)tmpStr)/2.0f;
    glRasterPos3f(x-deslocx,y,z);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    glPopAttrib();
}
void imprimeLose(float x,float y,float z,GLfloat R,GLfloat G,GLfloat B){
 glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    //define a cor da mensagem
    glColor3f(R,G,B);
    char*tmpStr;
   
    sprintf(str,"LOSE");
    
    tmpStr=str;
    // mensagem fica no meio da tela, calcula o tamanho da mensagem
    // para deslocar metade para esquerda do meio e metade para a direita
    float deslocx = glutBitmapLength(font,(const unsigned char*)tmpStr)/2.0f;
    glRasterPos3f(x-deslocx,y,z);
    while(*tmpStr){
        glutBitmapCharacter(font,*tmpStr);
        tmpStr++;
    }
    glPopAttrib();
}
void callVictory(){
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(0,1,0,1,-1,1);
        if(jogador.validBoxer()){
            imprimeVitoria(0.5,0.85,1,0,1,0);
        }
        else if(inimigo.validBoxer()){
            imprimeVitoria(0.5,0.9,2,1,0,0);
        
        }
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void trocaCameraVitoria(float centerx,float centery,float centerz){
    double largura,comprimento;
    arena.obtemAlturaLargura(largura,comprimento);
    float eyex,eyey,eyez;
    
    eyex = centerx+camDist*sin(camXZAngle*M_PI/180)*cos((camXYAngle*M_PI/180));
    eyey = centery+camDist*sin((camXYAngle*M_PI/180));
    eyez = centerz+camDist*cos(camXZAngle*M_PI/180)*cos((camXYAngle*M_PI/180));
    
    gluLookAt(eyex,eyey,eyez,centerx,centery,centerz,0,1,0);
}
//CallBack de renderizar a cena
void renderScene(){
    
   
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //define variáveis para capturar os 
    //parametros da arena
    GLdouble largura,comprimento;
    arena.obtemAlturaLargura(largura,comprimento);
    float altura = arena.returnAltura();
    //Limpa a cor com azulado
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    callPlacar();

    if(help) callHelp();
    
    if(!fim) {
        miniMap();
        redefineLookAt();
    }
    else {
        float cxv,cyv,czv;
        float cxl,cyl,czl;
        float r;
        callVictory();
        if(jogador.validBoxer()){
            jogador.obtemcXcYcZ(cxv,cyv,czv);
            trocaCameraVitoria(cxv,cyv,czv);
            jogador.obtemRaio(r);
            cyv+=r*1.5;
            inimigo.obtemcXcYcZ(cxl,cyl,czl);
            cyl+=r*.5;
        }
        else if(inimigo.validBoxer()){
            inimigo.obtemcXcYcZ(cxv,cyv,czv);
            trocaCameraVitoria(cxv,cyv,czv);
            inimigo.obtemRaio(r);
            cyv+=r*1.5;
            jogador.obtemcXcYcZ(cxl,cyl,czl);
            cyl+=r*.5;
        }
        glPushMatrix();
            glTranslatef(cxv,cyv,czv);
            glRotatef(angleWin,0,1,0);
            imprimeWin(r*2,0,0,0,1,0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(cxl,cyl,czl);
            glRotatef(angleWin,0,1,0);
            imprimeLose(r*2,0,0,1,0,0);
        glPopMatrix();
       
    }
    DesenhaLuz(altura,largura,comprimento);
    
    if(arena.validArena()){
        arena.Desenha();
    }
    //verifica se existe jogador
    jogador.Desenha();
    //verifica se existe inimigo
    inimigo.Desenha();
    

    //troca as janelas 
    //DrawAxes(0,0,altura/5,largura/5);

    glutSwapBuffers();
    glFlush();
}
//Callback de pressionar o botão do mouse
void mousePresse(int button,int state,int x,int y){
    //verifica se o evento foi do botão esquerdo
    if(button==GLUT_LEFT_BUTTON){
        // se tiver abaixado o botão inicializa que vai socar
        if(state==GLUT_DOWN){
            soca = 1;
            initialx = x;
        }
        //se o botão for solto reseta o soco
        else {
            soca=0;
            //Volta braço pra origem
            jogador.resetanglebracdir();
            jogador.resetanglebracesq();
            //reseta x click
            initialx=0;
        }
    }
    else if (button ==GLUT_RIGHT_BUTTON){
        if(state==GLUT_DOWN){
            lastX=x;
            lastY=y;
            buttonDown=1;
        }
        else buttonDown=0;
    }
    glutPostRedisplay();
}
//Callback de movimentar o mouse
void mouseMotion(int x,int y){
    //obtem os parametros da arena
    GLdouble altura,largura;
    arena.obtemAlturaLargura(largura,altura);
    //obtem os parametros do inimigo
    GLfloat cxini,cyini,czini,rini;
    inimigo.obtemcXcYcZ(cxini,cyini,czini);
    inimigo.obtemRaio(rini);
    //verifica se está ativado o movimento de soco e se 
    //o personagem pode socar
    if(soca && jogador.returnValidSoco() ){
        //pega a atual posição em x baseado no primeiro x  de click e o x atual
        float atualposition = x-initialx;
        float theta,maxangle;
        //pega o maximo angulo de soco
        maxangle=max_angle_soca;
        //calcula o angulo atual com base a posição atual
        theta = maxangle*atualposition/(w1/2); 
        //se for > 0 significa que é o braço direito
        //só pode ir ate largura/2 
        if(atualposition>0 && atualposition<(w1/2)){
            jogador.socoDireito(-theta,rini,cxini,cyini,czini);
        }
        //se for < 0 é o braço esquerdo
        if(atualposition<0 && abs(atualposition)<(w1/2)){
            jogador.socoEsquerdo(theta,rini,cxini,cyini,czini);
        }
    }
    if(buttonDown && (toggleCam==2 || fim)){
        camXZAngle-= x-lastX;
        if(camXYAngle+y-lastY<=60 && camXYAngle+y-lastY>=-60){
            camXYAngle+=y-lastY;
        }

        lastY=y;
        lastX=x;
    }
    glutPostRedisplay();
}
//callback de teclado
void keyPress(unsigned char key,int x,int y){
   //sempre que pressionar uma tecla será atribuido 1
   //as suas variaveis de estado
   switch (key)
   {
   case 'a':
   case 'A':
       keyStatus[(int)('a')] = 1;
       break;
   case 'd':
   case 'D':
        keyStatus[(int)('d')]=1;
        break;
    case 's':
    case 'S':
        keyStatus[(int)('s')]=1;
        break;
    case 'w':
    case 'W':
        keyStatus[(int)('w')]=1;
        break;
    case 'n':
    case 'N':
        noturno=!noturno;
        break;
    case '+':
        if(toggleCam==2 || fim){
            camDist+=50;
        }
        break;
    case '-':
        if(toggleCam==2 || fim){
            camDist-=50;
        }
        break;
    case '3':
        if(toggleCam!=2 && !fim){
            toggleCam=2;
            camDist = jogador.retornaAltura()*1.5;
            float angle = jogador.returnAngle();
            camXZAngle=angle*180/M_PI;
            camAngle=60;
            changeCamera(GLUT_WINDOW_WIDTH,GLUT_WINDOW_HEIGHT);
        }
        break;
    case '1':
        if(!fim){
            toggleCam=0;
            camAngle=90;
            changeCamera(GLUT_WINDOW_WIDTH,GLUT_WINDOW_HEIGHT);
        }
        break;
    case '2':
        if(!fim){
            toggleCam=1;
            camAngle=90;
            changeCamera(GLUT_WINDOW_WIDTH,GLUT_WINDOW_HEIGHT);
        }
        break;
    case 'j':
    case 'J':
        if(jogadorT==3) jogadorT=0;
        else jogadorT+=1;
        jogador.defineHeadT(jogadorHT[jogadorT]);
        break;
    case 'i':
    case 'I':
        if(inimigoT==3) inimigoT=0;
        else inimigoT+=1;
        inimigo.defineHeadT(inimigoHT[inimigoT]);
        break;
    case 't':
    case 'T':
        activeT=!activeT;
        if(activeT){
            glEnable(GL_TEXTURE_2D);

        }
        else{
            glDisable(GL_TEXTURE_2D);
        
        }
        break;
    case 'h':
    case 'H':
        help =!help;
        break;
    case 'r':
    case 'R':
        if(fim){
            jogador.reset();
            inimigo.reset();
            fim=!fim;
            help=!help;
            toggleCam=0;
            IAactive=!IAactive;
        }
        break;
    case 27:
        exit(0);
        break;
   default:
        keyStatus[key]=1;
       break;
   }
   
   //se qualquer uma das teclas de movimento for pressionada 
   //o jogador não pode socar
    if(keyStatus[(int)('a')]||keyStatus[(int)('d')]||keyStatus[(int)('w')]
                            ||keyStatus[(int)('s')]){
        jogador.defineValidSoco(false);
    }
    //se pressionado 0 ativa a IA 
    //ou desativa a IA
    if(keyStatus[(int)('0')]){
        if(!IAactive){
            IAactive = true;
        }
        else IAactive = false;
    }
    //redesenha a tela
    glutPostRedisplay();
}
//callback de teclado
void keyUp(unsigned char key, int x,int y){
    //se soltado a tecla atribui 0 a variável
    //de estado
     switch (key)
   {
   case 'a':
   case 'A':
       keyStatus[(int)('a')] = 0;
       break;
   case 'd':
   case 'D':
        keyStatus[(int)('d')]=0;
        break;
    case 's':
    case 'S':
        keyStatus[(int)('s')]=0;
        break;
    case 'w':
    case 'W':
        keyStatus[(int)('w')]=0;
        break;
   default:
        keyStatus[key]=0;
       break;
   }
    //verifica se todas as teclas são soltas 
    // se sim o jogador está parado e pode socar
     if(!keyStatus[(int)('a')] && !keyStatus[(int)('d')] && !keyStatus[(int)('w')]
                              && !keyStatus[(int)('s')]){
        jogador.defineValidSoco(true);
    }
    glutPostRedisplay();
}
//Callback de idle sempre chamado pelo sistema
void idle(){
    //Pega o tempo 
    static GLdouble previousTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble currentTime,timeDiference;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDiference = currentTime-previousTime;
    previousTime = currentTime;
    //se o jogo ainda não acabou
    if(!fim && !help){
        //Pega os parametros da arena
        GLdouble width,height;
        arena.obtemAlturaLargura(width,height);

        
       // Verifica pontuação
        if(jogador.returnPontuation()==10){
            //reseta e redefine posição 
            inimigo.defineValid(false);
            float rI;
            jogador.obtemRaioImaginary(rI);
            float r;
            inimigo.obtemRaio(r);
            inimigo.reposition(width/2+rI,r,height/2);
            jogador.reposition(width/2,jogador.retornaAltura()*6.5/7.5,height/2);
            inimigo.defineValid(false);
            jogador.resetanglebracdir();
            jogador.resetanglebracesq();
            camXZAngle=0;
            camXYAngle=0;
            camDist = jogador.retornaAltura()*1.65;  
            fim = true;
            noturno=!noturno;
            camAngle=60;
            changeCamera(GLUT_WINDOW_WIDTH,GLUT_WINDOW_HEIGHT);
            
        }
        else if(inimigo.returnPontuation()==10){
            jogador.defineValid(false);
            inimigo.resetanglebracdir();
            inimigo.resetanglebracesq();
            inimigo.reposition(width/2,inimigo.retornaAltura()*6.5/7.5,height/2);
            jogador.defineValid(false);
            float rI;
            inimigo.obtemRaioImaginary(rI);
            float r;
            jogador.obtemRaio(r);
            jogador.reposition(width/2+rI,r,height/2);
            camXZAngle=0;
            camXYAngle=0;
            camDist = inimigo.retornaAltura()*1.65;
            fim = true;
            noturno=!noturno;
            camAngle=60;
            changeCamera(GLUT_WINDOW_WIDTH,GLUT_WINDOW_HEIGHT);
        }

        

        //Realiza os movimentos do jogador
        double inc_giro = inc_girar;
        double inc_anda = inc_andar;
        //define parametros de colisão com a arena
        float limitdireita = width;
        float limitesquerda = 0;
        float limitcima = height;
        float limitbaixo = 0;
        //define parametros de colisão com o inimigo
        GLfloat cxinimigo,cyinimigo,czinimigo,raioinimigo;
        inimigo.obtemcXcYcZ(cxinimigo,cyinimigo,czinimigo);
        inimigo.obtemRaio(raioinimigo);
        float anglep1,anglep2;
        if(keyStatus[(int)('a')]){
            jogador.Gira(inc_giro,timeDiference);
        }
        if(keyStatus[(int)('d')]){
            jogador.Gira(-inc_giro,timeDiference);
        }
        if(keyStatus[(int)('w')]){
            //controla o retorno da perna para posição do corpo 
            voltouPernaD = false;
            voltouPernaE = false;
            if(jogador.returnPerna()){
                jogador.returnAnglepdireita(anglep1,anglep2);
                if((anglep1-inc_anda*0.65*timeDiference)>-max_angle_perna1*1.10){
                    jogador.Move(inc_anda,timeDiference,limitesquerda,limitdireita,limitcima,
                                    limitbaixo,cxinimigo,czinimigo,raioinimigo,true,inc_anda*0.65);
                    
                }
                else{
                    jogador.trocaPerna();

                }
   
            }
            else{
                jogador.returnAnglepesquerda(anglep1,anglep2);
                if((anglep1-inc_anda*0.65*timeDiference)>-max_angle_perna1*1.10 ){
                    jogador.Move(inc_anda,timeDiference,limitesquerda,limitdireita,limitcima,
                                    limitbaixo,cxinimigo,czinimigo,raioinimigo,true,inc_anda*0.65);
                }
                else{
                    jogador.trocaPerna();
                }
        
            }
            
        }
        if(!keyStatus[(int)('w')] && !keyStatus[(int)('s')]){
            bool perna = jogador.returnPerna();
            if(perna){
                float angle1,angle2;
                jogador.returnAnglepdireita(angle1,angle2);
                float angle1I,angle2I;
                jogador.returnAngleIpdireita(angle1I,angle2I);
                if(angle1<angle1I && !voltouPernaD){
                    jogador.Move(0,timeDiference,limitesquerda,limitdireita,limitcima,
                                    limitbaixo,cxinimigo,czinimigo,raioinimigo,false,-inc_anda*0.65);
                    jogador.returnAnglepdireita(angle1,angle2);
                    jogador.returnAngleIpdireita(angle1I,angle2I);
                    if(angle1>=angle1I){
                        voltouPernaD=true;
                    }
                }
                else if(angle1>angle1I && !voltouPernaD){
                    jogador.Move(0,timeDiference,limitesquerda,limitdireita,limitcima,
                                    limitbaixo,cxinimigo,czinimigo,raioinimigo,false,inc_anda*0.65);
                    jogador.returnAnglepdireita(angle1,angle2);
                    jogador.returnAngleIpdireita(angle1I,angle2I);
                    if(angle1<=angle1I){
                        voltouPernaD=true;
                    }
                }
                else{
                    jogador.trocaPerna();
                }
            }
            else{
                float angle1,angle2;
                jogador.returnAnglepesquerda(angle1,angle2);
                float angle1I,angle2I;
                jogador.returnAngleIpesquerda(angle1I,angle2I);
                if(angle1<angle1I && !voltouPernaE){
                    jogador.Move(0,timeDiference,limitesquerda,limitdireita,limitcima,
                                    limitbaixo,cxinimigo,czinimigo,raioinimigo,false,-inc_anda*0.65);
                    jogador.returnAnglepesquerda(angle1,angle2);
                    jogador.returnAngleIpesquerda(angle1I,angle2I);
                    if(angle1>=angle1I){
                        voltouPernaE=true;
                    }
                }
                else if (angle1>angle1I && !voltouPernaE){
                    jogador.Move(0,timeDiference,limitesquerda,limitdireita,limitcima,
                                    limitbaixo,cxinimigo,czinimigo,raioinimigo,false,inc_anda*0.65);
                    jogador.returnAnglepesquerda(angle1,angle2);
                    jogador.returnAngleIpesquerda(angle1I,angle2I);
                    if(angle1<=angle1I){
                        voltouPernaE=true;
                    }
                }
                else{
                    jogador.trocaPerna();
                }
            }
        }


        if(keyStatus[(int)('s')]){
            //controla o retorno da perna para posição do corpo 
            voltouPernaD = false;
            voltouPernaE = false;
            if(jogador.returnPerna()){
                jogador.returnAnglepdireita(anglep1,anglep2);
                if((anglep2+inc_anda*0.65*timeDiference)<max_angle_perna1){
                    jogador.Move(-inc_anda,timeDiference,limitesquerda,limitdireita,limitcima,
                                    limitbaixo,cxinimigo,czinimigo,raioinimigo,true,-inc_anda*0.65);
                    
                }
                else{
                    jogador.trocaPerna();

                }
   
            }
            else{
                jogador.returnAnglepesquerda(anglep1,anglep2);
                if((anglep2+inc_anda*0.65*timeDiference)<max_angle_perna1){
                    jogador.Move(-inc_anda,timeDiference,limitesquerda,limitdireita,limitcima,
                                    limitbaixo,cxinimigo,czinimigo,raioinimigo,true,-inc_anda*0.65);
                }
                else{
                    jogador.trocaPerna();
                }
        
            }
            
        }

        //Se a IA tiver ativada
        if(IAactive){
            //Movimento do inimigo
            //parametros de colisão do jogador
            GLfloat cxjogador,cyjogador,czjogador;
            jogador.obtemcXcYcZ(cxjogador,cyjogador,czjogador);
            GLfloat raioIjogador;
            GLfloat raiojogador;
            jogador.obtemRaio(raiojogador);
            jogador.obtemRaioImaginary(raioIjogador);
            //define o anculo em relação ao jogador
            GLfloat theta=0;
            inimigo.retornaAnguloRelativoAoJogador(cxjogador,czjogador,theta);
            //calcula a diferença de angulo entre o atual e o anterior
            GLfloat anguloAtual = inimigo.returnAngle();
            GLfloat angleDiference = theta-anguloAtual;
            //calcula a distancia do inimigo ao jogador
            GLfloat dist = inimigo.distanceAoJogadorF(inc_anda,timeDiference,cxjogador,czjogador);
            //pega raio imaginario do inimigo para tratar colisão
            GLfloat raioI; 
            inimigo.obtemRaioImaginary(raioI);
            //decide se o inimigo pode mover ou socar
            if((raioIjogador)<dist){
                //se não houve colisão movimenta-se
                inimigo.defineValidSoco(false);
               //Se o jogador tiver a uma distancia segura de raioI do inimigo pixels
               //ativa o movimento do inimigo
               //o inimigo vai movimentar quando o jogador não andar para frente e para tras
                if((dist-(raioIjogador))>raioI || (!keyStatus[(int)('w')] && !keyStatus[(int)('s')]) ){
                    moveI = true;
                    incSocoAcc = 0;
                }
            }
            //se houve colisão o inimigo chegou ao jogador
            //é hora de atacar
            else {
                moveI = false;
                inimigo.defineValidSoco(true);
            }
            //calculando o angulo compensador
            angleDiference = atan2(sin(angleDiference),cos(angleDiference));
            //transformando em radianos pois theta e angulo atual ta em radianos
            float inc_giro_r = inc_giro*M_PI/180;
            //se o angulo que compensa girar é negativo
            //decrementa o angulo atual
            //inimigo.defineAngle(theta);
            if(angleDiference<0){
                if((anguloAtual-inc_giro_r*timeDiference)>(anguloAtual+angleDiference)){
                    inimigo.Gira(-inc_giro,timeDiference);
                }
            } 
            //se não incrementa
            else if (angleDiference>0){
                if((anguloAtual+inc_giro_r*timeDiference)<(anguloAtual+angleDiference)){
                    inimigo.Gira(inc_giro,timeDiference);
                }
            }
            //se o nimigo pode mover, então mova-se
           if(moveI){
                //controla o retorno da perna para posição do corpo 
                voltouPernaDi = false;
                voltouPernaEi = false;
                if(inimigo.returnPerna()){
                    inimigo.returnAnglepdireita(anglep1,anglep2);
                    if((anglep1-inc_anda*0.65*timeDiference)>-max_angle_perna1*1.10){
                        inimigo.Move(inc_anda,timeDiference,limitesquerda,limitdireita,limitcima,
                                        limitbaixo,cxjogador,czjogador,raiojogador,true,inc_anda*0.65);
                        
                    }
                    else{
                        inimigo.trocaPerna();

                    }
    
                }
                else{
                    inimigo.returnAnglepesquerda(anglep1,anglep2);
                    if((anglep1-inc_anda*0.65*timeDiference)>-max_angle_perna1*1.10 ){
                        inimigo.Move(inc_anda,timeDiference,limitesquerda,limitdireita,limitcima,
                                        limitbaixo,cxjogador,czjogador,raiojogador,true,inc_anda*0.65);
                    }
                    else{
                        inimigo.trocaPerna();
                    }
            
                }
            }
            else{
                bool perna = inimigo.returnPerna();
                if(perna){
                    float angle1,angle2;
                    inimigo.returnAnglepdireita(angle1,angle2);
                    float angle1I,angle2I;
                    inimigo.returnAngleIpdireita(angle1I,angle2I);
                    if(angle1<angle1I && !voltouPernaDi){
                        inimigo.Move(0,timeDiference,limitesquerda,limitdireita,limitcima,
                                        limitbaixo,cxjogador,czjogador,raiojogador,false,-inc_anda*0.65);
                        inimigo.returnAnglepdireita(angle1,angle2);
                        inimigo.returnAngleIpdireita(angle1I,angle2I);
                        if(angle1>=angle1I){
                            voltouPernaDi=true;
                        }
                    }
                    else if(angle1>angle1I && !voltouPernaDi){
                        inimigo.Move(0,timeDiference,limitesquerda,limitdireita,limitcima,
                                        limitbaixo,cxjogador,czjogador,raiojogador,false,inc_anda*0.65);
                        inimigo.returnAnglepdireita(angle1,angle2);
                        inimigo.returnAngleIpdireita(angle1I,angle2I);
                        if(angle1<=angle1I){
                            voltouPernaDi=true;
                        }
                    }
                    else{
                        inimigo.trocaPerna();
                    }
                }
                else{
                    float angle1,angle2;
                    inimigo.returnAnglepesquerda(angle1,angle2);
                    float angle1I,angle2I;
                    inimigo.returnAngleIpesquerda(angle1I,angle2I);
                    if(angle1<angle1I && !voltouPernaEi){
                        inimigo.Move(0,timeDiference,limitesquerda,limitdireita,limitcima,
                                        limitbaixo,cxjogador,czjogador,raiojogador,false,-inc_anda*0.65);
                        inimigo.returnAnglepesquerda(angle1,angle2);
                        inimigo.returnAngleIpesquerda(angle1I,angle2I);
                        if(angle1>=angle1I){
                            voltouPernaEi=true;
                        }
                    }
                    else if (angle1>angle1I && !voltouPernaEi){
                        inimigo.Move(0,timeDiference,limitesquerda,limitdireita,limitcima,
                                        limitbaixo,cxjogador,czjogador,raiojogador,false,inc_anda*0.65);
                        inimigo.returnAnglepesquerda(angle1,angle2);
                        inimigo.returnAngleIpesquerda(angle1I,angle2I);
                        if(angle1<=angle1I){
                            voltouPernaEi=true;
                        }
                    }
                    else{
                        inimigo.trocaPerna();
                    }
                }
            }
            //Soca Inimigo
            if(inimigo.returnValidSoco()){
                GLdouble largura,altura;
                arena.obtemAlturaLargura(largura,altura);
                float incsoco = (max_angle_soca-5)/(360.0f)*timeDiference*2;
                
                //socoDirection começa como zero
                //sorteia para decidir o primeiro braço a socar  
                if(!socoDirection){
                    socoDirection = rand()%2+1;
                }
                //ação de soco para 2 casos diferentes
                switch (socoDirection)
                {
                //se for o braço direito
                case 1:
                    //enquanto não tiver finalizado o soco e o angulo de soco
                    // for menor que o max permitido
                    if(!finalizousoco && incSocoAcc>-max_angle_soca){
                        incSocoAcc-=incsoco;
                        inimigo.socoDireito(incSocoAcc,raiojogador,cxjogador,cyjogador,czjogador);
                        if(incSocoAcc<=-max_angle_soca){
                            finalizousoco=true;
                        }
                    }
                    //enquanto incSocoAcc for maior do que zero
                    //retorne o soco para a posição inicial
                    //decrementando o acumulador
                    else if(incSocoAcc<0 && finalizousoco) {
                        incSocoAcc+= incsoco;
                        inimigo.socoDireito(incSocoAcc,raiojogador,cxjogador,cyjogador,czjogador);
                    }
                    //quando retornado sorteie novamente o braço
                    //resete as variaveis de estados
                    else {
                        finalizousoco=false;
                        incSocoAcc = 0;
                        socoDirection = rand()%2+1;
                    }
                    break;
                //Se for o braço esquerdo
                case 2:
                    //Mesma situação enquanto não finalizar o soco
                    // e enquanto for maior que o -angulo maximo
                    if(!finalizousoco && incSocoAcc>-max_angle_soca){
                        incSocoAcc-=incsoco;
                        inimigo.socoEsquerdo(incSocoAcc,raiojogador,cxjogador,cyjogador,czjogador);
                        if(incSocoAcc<=-max_angle_soca){
                            finalizousoco=true;
                        }
                    }
                    //incrementa para retornar a posição original
                    else if(incSocoAcc<0 && finalizousoco) {
                        incSocoAcc+= incsoco;
                        inimigo.socoEsquerdo(incSocoAcc,raiojogador,cxjogador,cyjogador,czjogador);
                    }
                    //reseta e sorteia quando terminado o movimento de soco
                    else {
                        incSocoAcc = 0;
                        socoDirection = rand()%2+1;
                        finalizousoco=false;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
    else{
        angleWin+=0.05*timeDiference;
    }
    glutPostRedisplay();
}
//inicializa o sistema gráfico
void init(void){
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);  
    glEnable(GL_LIGHT0 | GL_LIGHT1 | GL_LIGHT2);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
   // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

   GLuint tex = loadText("chao.png");
   arena.chaotexturaD(tex);
   arena.cordatesturaD(loadText("rope1.jpg"));
   arena.colunatesturaD(loadText("coluna.jpg"));
   arena.ambientetesturaD(loadText("amb.png"));
   jogador.defineHeadT(loadText("head7.png"));
   inimigo.defineHeadT(loadText("head6.png"));
   GLuint texturaJ[4] = {loadText("head7.png"),loadText("head5.jpg"),
                         loadText("head5.png"),loadText("head2.png")
                            };
   GLuint texturaI[4] = {loadText("head6.png"),loadText("head8.png"),
                         loadText("head9.png"),loadText("head3.png")
                            };
    for(int i =0;i<4;i++){
        jogadorHT[i]=texturaJ[i];
        inimigoHT[i]=texturaI[i];
    }
    jogador.defineHandT(loadText("hand.jpg"));
    inimigo.defineHandT(loadText("hand.jpg"));
    jogador.defineBodyT(loadText("body.jpg"));
    inimigo.defineBodyT(loadText("body.jpg"));
    jogador.defineDressT(loadText("dress1.jpg"));
    inimigo.defineDressT(loadText("dress2.jpg"));
    

}
void changeCamera(int w,int h){
    GLdouble largura,altura;
    arena.obtemAlturaLargura(largura,altura);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluPerspective (camAngle, (GLfloat)h/(GLfloat)w, 1, altura*largura);
    else
        gluPerspective (camAngle, (GLfloat)w/(GLfloat)h, 1, altura*largura);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}
void reshape (int w, int h)
{
  
    //Ajusta o tamanho da tela com a janela de visualizacao
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    changeCamera(w,h);
    h1=h;
    w1=w;
}

//função principal
int main (int argc, char* argv[]){
    //pega o nome do arquivo
    string filename;
    filename = argv[1];
    Util utilidades(filename);
    //Inicializando os objetos arena,inimigo e jogador
    utilidades.parsesElements(arena,inimigo,jogador);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    //Criando janela
    glutInitWindowSize(view,view);
    glutInitWindowPosition(150,50);
    glutCreateWindow("Box-Game");
    //Instanciando as callbacks
    init();
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyUp);
    glutMouseFunc(mousePresse);
    glutMotionFunc(mouseMotion);
    glutIdleFunc(idle);
 

    
    glutMainLoop();
    return 0;
}
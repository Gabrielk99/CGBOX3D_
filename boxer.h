#ifndef BOXER_H
#define BOXER_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//auxiliar de mesh
typedef struct
{
    //Vertex coordinate
    double X;
    double Y;
    double Z;
    
    //Vertex texture coordinate
    double U;
    double V;
} VERTICES;
typedef struct 
{
    VERTICES * VTX;
    int qtdV;
}PLANO;

using namespace std;
//Classe que define o objeto boxeador
class Boxer
{
    //centro e raio do boxeador
    GLfloat cX;
    GLfloat cY;
    GLfloat cZ;
    GLfloat cX_I;
    GLfloat cY_I;
    GLfloat cZ_I;

    GLfloat radiuS;
    
    GLfloat altura;
    //raio imaginario
    GLfloat radiusImaginary;
    //booleano de se o boxeador existe
    bool valid = false;
    //identificador de cor (jogador ou inimigo)
    string color;
    //identificador de angulo de direção
    GLfloat angle;
    //guarda o angulo inicial
    GLfloat angleInicial;
    //identificadores de angulos iniciais do braço esquerdo
    GLfloat anglebraco11_inicial=45;
    GLfloat anglebraco12_inicial=-90;
    GLfloat anglebraco13_inicial=-20;
    GLfloat anglebraco14_inicial=30;
    //identificadores de angulos atuais do braço esquerdo
    GLfloat anglebraco11=45;
    GLfloat anglebraco12=-90;
    GLfloat anglebraco13=-20;
    GLfloat anglebraco14=30;
    //identificadores de angulos iniciais do braço direito
    GLfloat anglebraco21_inicial=45;
    GLfloat anglebraco22_inicial=-90;
    GLfloat anglebraco23_inicial=20;
    GLfloat anglebraco24_inicial=-30;
    //identificadores de angulo atuais do braço direito
    GLfloat anglebraco21=45;
    GLfloat anglebraco22=-90;
    GLfloat anglebraco23=20;
    GLfloat anglebraco24=-30;
     //identificadores de angulos iniciais da perna esquerda
    GLfloat angleperna11_inicial=-30;
    GLfloat angleperna12_inicial=40;
    //identificadores de angulos atuais da perna esquerda
    GLfloat angleperna11=-30;
    GLfloat angleperna12=40;
    //identificadores de angulos iniciais da perna direita
    GLfloat angleperna21_inicial=-30;
    GLfloat angleperna22_inicial=40;
    //identificadores de angulo atuais da perna direita
    GLfloat angleperna21=-30;
    GLfloat angleperna22=40;
    //angulo max de inclinação da perna
    GLfloat angleMaxp = 60;
    //define perna 
    bool perna = true; //true é perna direita, false é esquerda.
    //pontuação
    int pontuation = 0;
    //se a pontuação é valida de calcular
    bool pontuationValid = true;
    //se o jogador pode socar
    bool socoValid = true;
    //apenas um roubo, quero que o soco colida com o personagem
    //sem atravessar a cabeça, se eu deixa fluir a posição futura ao menos
    //uma vez, o soco colide sem atravessar e sem não encostar
    bool avancaUltimaPosixSoco = true;
    //head texture
    GLuint headText;
    //hand texture
    GLuint handText;
    //body texture;
    GLuint bodyText;
    //dress texture
    GLuint dressText;
private:
    //auxiliares de desenho do personagem
    PLANO* CreatePlane (float W,float H,float space,int plan,float x,float y,float z);
    void DesenhaEsfera(GLfloat radius,GLfloat R,GLfloat G,GLfloat B,GLuint textura);
    void DesenhaCone(GLfloat size,GLfloat R,GLfloat G,GLfloat B);
    void DesenhaTorax(GLfloat size,GLfloat R,GLfloat G,GLfloat B);
    void DesenhaParalepipedo(GLfloat sizex,GLfloat sizey,GLfloat sizez,float space,GLfloat R,GLfloat G,GLfloat B);
    void DesenhaBraco(GLfloat x,GLfloat y,GLfloat z,GLfloat size,GLfloat angle1,
                        GLfloat angle2,GLfloat angle3,GLfloat angle4,GLfloat radius);
    void DesenhaPerna(GLfloat x,GLfloat y,GLfloat z,GLfloat size,GLfloat angle1,GLfloat angle2);
    void DesenhaNariz(GLfloat x,GLfloat y,GLfloat z,GLfloat radius);
    void DesenhaBoxer(GLfloat cx,GLfloat cy,GLfloat cz,
                        GLfloat radius,string color,GLfloat angle,
                        GLfloat angleb11,GLfloat angleb12,GLfloat angleb13,GLfloat angleb14,
                        GLfloat angleb21,GLfloat anlgeb22,GLfloat angleb23,GLfloat angleb24,
                        GLfloat anglep11,GLfloat anglep12, GLfloat anglep21,GLfloat anglep22
                        );
public:
    Boxer(GLfloat cx,GLfloat cy,GLfloat radius,string cor){
        cX = cx;
        cZ = cy;
        cY = 6.5*radius;
        cY_I=cY;
      

        altura = 7.5*radius;

        radiuS = radius;
        //proporção ao raio definido para o personagem
        radiusImaginary = radius*4;
        valid = true;
        color = cor;
        
    };
    //auxiliar para poder criar a classe vazia
    Boxer(){};
    //chama a função desenha 
    void Desenha(){
        DesenhaBoxer(cX,cY,cZ,radiuS,color,angle,anglebraco11,anglebraco12,anglebraco13,anglebraco14,
            anglebraco21,anglebraco22,anglebraco23,anglebraco24,angleperna11,angleperna12,
            angleperna21,angleperna22);
    };
    //retorna validade de existencia
    bool validBoxer(){
        return valid;
    }
    bool returnPerna(){
        return perna;
    }
    void trocaPerna(){
        perna = !perna;
    }
    //define a textura da cabeça
    void defineHeadT(GLuint text){
        headText=text;
    }
    //define a textura da mão
    void defineHandT(GLuint text){
        handText=text;
    }
    //define a textura do vestido
    void defineBodyT(GLuint text){
        bodyText=text;
    }
    void defineDressT(GLuint text){
        dressText=text;
    }
    void returnAnglepdireita(float &angle1,float &angle2){
        angle1=angleperna21;
        angle2=angleperna22;
    }
    void returnAngleIpdireita(float &angle1,float &angle2){
        angle1=angleperna21_inicial;
        angle2=angleperna22_inicial;
    }
    void returnAnglepesquerda(float &angle1,float &angle2){
        angle1=angleperna11;
        angle2=angleperna12;
    }
    void returnAngleIpesquerda(float &angle1,float &angle2){
        angle1=angleperna11_inicial;
        angle2=angleperna12_inicial;
    }
    //retorna o centro do personagem
    void obtemcXcYcZ(GLfloat &cx,GLfloat &cy,GLfloat &cz){
        cx = cX;
        cy = cY;
        cz = cZ;
    }
    //retorna o raio do personagem
    void obtemRaio(GLfloat &r){
        r=radiuS;
    }
    //retorna o raio imaginario do personagem (limitador)
    void obtemRaioImaginary(GLfloat &r){
        r = radiusImaginary;
    }
    //retorna altura do personagem
    GLfloat retornaAltura(){
        return altura;
    }
    //define o angulo do personagem
    void defineAngle(GLfloat theta){
        angle = theta;
        angleInicial=theta;
    }
    // retorna angulo inicial do jogador
    float returnAngleI(){
        return angleInicial;
    }
    // redefine o cy do personagem para o eixo ideal
    void redefinecz(GLdouble altura,GLfloat y){
        cZ= cZ-y;
        cZ_I=cZ;
    }
    // redefine o cy do personagem para o eixo ideal
    void redefinecx(GLfloat x){
        cX= cX-x;
        cX_I=cX;
    }
    //funções de movimento e soco
    void Gira(GLdouble inc,GLdouble time);
    void Move(GLdouble inc,GLdouble time,GLfloat limesq,GLfloat limdir,GLfloat cima,GLfloat baixo,
                GLfloat cxadv,GLfloat cyadv,GLfloat r,bool andando,float incA);
    void socoDireito(GLfloat inc,GLfloat raioadversario,GLfloat cx,GLfloat cy,GLfloat cz);
    void socoEsquerdo(GLfloat inc,GLfloat raioadversario,GLfloat cx,GLfloat cy,GLfloat cz);
    void resetanglebracdir();
    void resetanglebracesq();
    //retorna posição da luva
    void getGlovesPosition(GLfloat &cx,GLfloat &cy,GLfloat &z,GLfloat angle1,GLfloat angle2,GLfloat angle3,GLfloat angle4,bool esq,bool dir);
    //obtem posição do olho
    void getEyesPosition(GLfloat &x,GLfloat &y,GLfloat &z);
    //obtem centro de foco da camera
    void getFocusPosition(GLfloat &x,GLfloat &y, GLfloat &z);
    //obtem pulso do personagem
    void getPulsoPosition(GLfloat &x,GLfloat &y, GLfloat &z);
    //obtem foco do pulso
    void getPulsoFocusPosition(GLfloat &x,GLfloat &y, GLfloat &z);
    //obtem up camera pulso
    void getUpPosition(GLfloat &x,GLfloat &y, GLfloat &z);
    //obtem costas
    void getBackPosition(GLfloat &x,GLfloat &y, GLfloat &z);
    //define a validade do soco (pode socar ou não socar)
    void defineValidSoco(bool validade){
        socoValid = validade;
    }
    //retorna se o soco é valido
    bool returnValidSoco(){
        return socoValid;
    }
    //retorna o angulo de direção do personagem
    float returnAngle(){
        return angle;
    }
    //define a validade do personagem
    void defineValid(bool validade){
        valid = validade;
    }
    //retorna a pontuação
    int returnPontuation(){
        return pontuation;
    }
    //reposiciona o personagem (finalização do jogo)
    void reposition(GLfloat cx,GLfloat cy,GLfloat cz){
        cX = cx;
        cZ = cz;
        cY=cy;
        angle = 0;
    }
    void reset(){
        cX=cX_I;
        cY=cY_I;
        cZ=cZ_I;
        angle=angleInicial;
        pontuation=0;
        valid=true;
    }
};


#endif /* BOXER_H*/
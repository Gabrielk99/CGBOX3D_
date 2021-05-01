#ifndef ARENA_H
#define ARENA_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
//Classe que define a arena
class Arena
{
    //Origem da arena
    GLfloat gX;
    GLfloat gY;
    //largura e altura
    GLdouble widthA;
    GLdouble heightA;
    //cor da arena
    string colorA;
    GLfloat altura;
    //validade da arena
    bool valid=false;
    //textura chão
    GLuint chaoText;
    //textura cordas
    GLuint cordaText;
    //textura coluna
    GLuint colunaText;
    //ambiente textura
    GLuint ambientText;

private:
    //funções para desenhar a arena
    void DesenhaParalepipedo(GLfloat sizex,GLfloat sizey,GLfloat sizez,float space,GLfloat R,GLfloat G,GLfloat B,GLuint text);
    void DesenhaArena(GLdouble width,GLdouble height,GLfloat altura,string color);
public:
    //inicializa a arena
    Arena(GLfloat x, GLfloat y,GLdouble width,GLdouble height,string color){
        gX = x;
        gY = y;
        widthA = width;
        heightA = height;
        colorA = color;
        valid = true;
    };
    //permite criar objeto sem inicialização
    Arena(){};
    //desenha a arena
    void Desenha(){
        DesenhaArena(widthA,heightA,altura,colorA);
    };
    void defineAltura(GLfloat alturaPersonagem){
        altura = 2*alturaPersonagem;
    }
    //retorna altura da arena
    float returnAltura(){
        return altura;
    }
    //retorna a altura e largura da arena
    void obtemAlturaLargura(GLdouble &width,GLdouble &height){
        width = widthA;
        height = heightA;
    }
    //retorna origem da arena
    void ObtemOrigem(GLfloat &x,GLfloat &y){
        x=gX;
        y=gY;
    }
    //retorna validade da arena
    bool validArena(){
        return valid;
    }
    //define textura do chão
    void chaotexturaD(GLuint text){
        chaoText=text;
    }
    void cordatesturaD(GLuint text){
        cordaText=text;
    }
    void colunatesturaD(GLuint text){
        colunaText=text;
    }
    void ambientetesturaD(GLuint text){
        ambientText=text;
    }
};





#endif /* ARENA_H*/
#ifndef JOGADOR_H
#define JOGADOR_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "boxer.h"
using namespace std;

//Classe que define o jogador
class Jogador : public Boxer
{

private:

public:
    Jogador(GLfloat cx,GLfloat cy,GLfloat radius,string cor):Boxer(cx,cy,radius,cor){
    };
    //permite criar classe vazia
    Jogador(){};
    //calcula o angulo do nariz do jogador
    void calculeAngleNarizJogador(GLfloat cxinimigo,GLfloat cyinimigo,GLfloat czinimigo){
       GLfloat cX,cY,cZ;
       //obetem o centro do jogador
       Boxer::obtemcXcYcZ(cX,cY,cZ);
       //calcula a diferença dos centros
       float distx = cxinimigo-cX;
       float distz = -(czinimigo-cZ);
       //retorna e define o angulo
       float theta = atan2(distz,distx);
       Boxer::defineAngle(theta+M_PI/2);
    }

};


#endif /* JOGADOR_H */
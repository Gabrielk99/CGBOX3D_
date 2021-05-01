#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <stdlib.h>
#include "tinyxml2.h"
#include <string>
#include "arena.h"
#include "jogador.h"
#include "inimigo.h"
#include "SOIL.h"
//invocando o tinyxml2 para leituras do svg
using namespace tinyxml2;
using namespace std;
//Classe util para leitura e inicialização dos objetos
class Util
{
    //nome do SVG
    string svgfilename;
    //doc de leitura do svg
    XMLDocument doc;
    //elemento raiz
    XMLElement*  root;
    //verificação de erro
    XMLError lido;
private:
  
public:
    Util(string filename){
        svgfilename = filename;
        lido = doc.LoadFile(svgfilename.c_str());
        if(lido==XML_SUCCESS){
            root = doc.FirstChildElement("svg");
        }
    };
    Util(){};
    Arena  return_proprieties_Arena(XMLElement* pParam);
    void  return_proprieties_JogadorOrInimigo(XMLElement* pParam,Inimigo &inimigo,Jogador &jogador);
    void parsesElements(Arena &arena,Inimigo &inimigo,Jogador &jogador);
    void defineFilename(string filename){
        svgfilename=filename;
    }
    void Parse(){
        lido = doc.LoadFile(svgfilename.c_str());
        if(lido==XML_SUCCESS){
            root = doc.FirstChildElement("svg");
        }
    }
};
void DrawAxes(GLfloat x, GLfloat y,GLfloat altura,GLfloat largura);//desenha os eixos 3D
GLuint loadText(const char* path);




















#endif /* UTIL_H */
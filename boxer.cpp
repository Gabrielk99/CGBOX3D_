#include "boxer.h"


//Desenha circulo (chamado para desenhar a cabeça, a luva e o nariz)
void Boxer :: DesenhaEsfera(GLfloat radius,GLfloat R,GLfloat G,GLfloat B,GLuint textura){
    //define o centro como 0,0 para realizar rotações em torno do proprio objeto
    GLfloat materialEmission[] = { R, G, B, 1};
    GLfloat materialColor[] = { R, G, B, 1};
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    glColor3f(R,G,B);   
    GLUquadric* Quad =  gluNewQuadric();
    gluQuadricTexture(Quad,true);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );

    glBindTexture (GL_TEXTURE_2D, textura);
    gluSphere(Quad,radius,50,20);
    //glutSolidSphere(radius,50,15);

    
    
}
//Desenha Cone (chamando para desenhar o torax)
void Boxer:: DesenhaCone(GLfloat size,GLfloat R,GLfloat G,GLfloat B){
    GLfloat materialEmission[] = { R, G, B, 1};
    GLfloat materialColor[] = { R, G, B, 1};
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    glColor3f(R,G,B);
    GLUquadric* Quad =  gluNewQuadric();
    gluQuadricTexture(Quad,true);
    gluCylinder(Quad,size/2,0,size,50,10);
    //glutSolidCone(size/2,size,50,10);
    
  
    
}
PLANO* Boxer :: CreatePlane (float W,float H,float space,int plan,float x,float y,float z){
    PLANO * plano = new PLANO;
    plano->qtdV = ((int)(abs(W)/space)*4)*(int)(abs(H)/space);
    plano->VTX = new VERTICES [plano->qtdV];
    int n =0;
    //plano xy
    if(plan==0){
        for(int k = 0;k<=abs(H)-space;k+=space){
            for(int j = 0;j<=abs(W)-space;j+=space ){


                float pass1A = j;
                float pass1F = j+space;
                float pass2A = k;
                float pass2F = k+space;

                if(W<0){
                    pass1A*=-1;
                    pass1F*=-1;
                }
                if(H<0){
                    pass2A*=-1;
                    pass2F*=-1;
                }

                plano->VTX[n].X = x+pass1A;
                plano->VTX[n].Y = y+pass2A;
                plano->VTX[n].Z = z;

                plano->VTX[n].U = 0;
                plano->VTX[n].V = 0;

                n++;


                plano->VTX[n].X = (x+pass1F);
                plano->VTX[n].Y = (y+pass2A);
                plano->VTX[n].Z = z;

                plano->VTX[n].U = 0;
                plano->VTX[n].V = 1;

                n++;

                plano->VTX[n].X = (x+pass1F);
                plano->VTX[n].Y = (y+pass2F);
                plano->VTX[n].Z = z;

                plano->VTX[n].U = 1;
                plano->VTX[n].V = 1;

                n++;

                plano->VTX[n].X = (x+pass1A);
                plano->VTX[n].Y = (y+pass2F);
                plano->VTX[n].Z = z;

                plano->VTX[n].U = 1;
                plano->VTX[n].V = 0;

                n++;
                
        
            }
        }
    }
    //plano xz
    else if(plan == 1){
          n=0;
          for(int k = 0;k<=abs(H)-space;k+=space){
            for(int j = 0;j<=abs(W)-space;j+=space ){
                
                float pass1A = j;
                float pass1F = j+space;
                float pass2A = k;
                float pass2F = k+space;

                if(W<0){
                    pass1A*=-1;
                    pass1F*=-1;
                }
                if(H<0){
                    pass2A*=-1;
                    pass2F*=-1;
                }


                plano->VTX[n].X = x+pass1A;
                plano->VTX[n].Y = y;
                plano->VTX[n].Z = z+pass2A;

                plano->VTX[n].U = 0;
                plano->VTX[n].V = 0;

                n++;


                plano->VTX[n].X = (x+pass1F);
                plano->VTX[n].Y = (y);
                plano->VTX[n].Z = (z+pass2A);

                plano->VTX[n].U = 0;
                plano->VTX[n].V = 1;

                n++;

                plano->VTX[n].X = (x+pass1F);
                plano->VTX[n].Y = (y);
                plano->VTX[n].Z = (z+pass2F);

                plano->VTX[n].U = 1;
                plano->VTX[n].V = 1;

                n++;

                plano->VTX[n].X = (x+pass1A);
                plano->VTX[n].Y = (y);
                plano->VTX[n].Z = (z+pass2F);

                plano->VTX[n].U = 1;
                plano->VTX[n].V = 0;

                n++;

            }
        }
    }
   
    //plano yz
    else if(plan == 2){
         n=0;
          for(int k = 0;k<=abs(H)-space;k+=space){
            for(int j = 0;j<=abs(W)-space;j+=space ){
                
                float pass1A = j;
                float pass1F = j+space;
                float pass2A = k;
                float pass2F = k+space;

                if(W<0){
                    pass1A*=-1;
                    pass1F*=-1;
                }
                if(H<0){
                    pass2A*=-1;
                    pass2F*=-1;
                }


                plano->VTX[n].X = x;
                plano->VTX[n].Y = y+pass1A;
                plano->VTX[n].Z = z+pass2A;

                plano->VTX[n].U = 0;
                plano->VTX[n].V = 0;

                n++;


                plano->VTX[n].X = (x);
                plano->VTX[n].Y = (y+pass1F);
                plano->VTX[n].Z = (z+pass2A);

                plano->VTX[n].U = 0;
                plano->VTX[n].V = 1;

                n++;

                plano->VTX[n].X = (x);
                plano->VTX[n].Y = (y+pass1F);
                plano->VTX[n].Z = (z+pass2F);

                plano->VTX[n].U = 1;
                plano->VTX[n].V = 1;

                n++;

                plano->VTX[n].X = (x);
                plano->VTX[n].Y = (y+pass1A);
                plano->VTX[n].Z = (z+pass2F);

                plano->VTX[n].U = 1;
                plano->VTX[n].V = 0;

                n++;
  
            }
        }
    }
    return plano;
}
void Boxer:: DesenhaParalepipedo(GLfloat sizex,GLfloat sizey,GLfloat sizez,float space,GLfloat R,GLfloat G,GLfloat B){
    GLfloat materialEmission[] = { R, G, B, 1};
    GLfloat materialColor[] = { R, G, B, 1};
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    glColor3f(R,G,B);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );

    glBindTexture (GL_TEXTURE_2D, bodyText);
    // //Desenha fundo
    PLANO *fundo = new PLANO;
    fundo = CreatePlane(sizex,sizey,space,0,0,0,0);

    glBegin(GL_QUADS);
        for(int i =0;i<fundo->qtdV;i++){
            glNormal3f(0,0,-1);
            glTexCoord2f(fundo->VTX[i].X/sizex,fundo->VTX[i].Y/sizey);
            glVertex3f(fundo->VTX[i].X,fundo->VTX[i].Y,fundo->VTX[i].Z);
        }
    glEnd();

    delete(fundo->VTX);
    delete(fundo);
    //Desenha lateral esquerda
    PLANO *esquerda = new PLANO;
    esquerda = CreatePlane(sizey,sizez,space,2,sizex,0,0);

    glBegin(GL_QUADS);
        for(int i =0;i<esquerda->qtdV;i++){
            glNormal3f(1,0,0);
            glTexCoord2f(esquerda->VTX[i].Y/sizey,esquerda->VTX[i].Z/sizez);
            glVertex3f(esquerda->VTX[i].X,esquerda->VTX[i].Y,esquerda->VTX[i].Z);
        }
    glEnd();

    delete(esquerda->VTX);
    delete(esquerda);
    //Desenha lateral direita
    PLANO *direita = new PLANO;
    direita = CreatePlane(sizey,sizez,space,2,0,0,0);

    glBegin(GL_QUADS);
        for(int i =0;i<direita->qtdV;i++){
            glNormal3f(-1,0,0);
            glTexCoord2f(direita->VTX[i].Y/sizey,direita->VTX[i].Z/sizez);
            glVertex3f(direita->VTX[i].X,direita->VTX[i].Y,direita->VTX[i].Z);
        }
    glEnd();

    delete(direita->VTX);
    delete(direita);
    //Desenha frente
    PLANO *frente = new PLANO;
    frente = CreatePlane(sizex,sizey,space,0,0,0,sizez);

    glBegin(GL_QUADS);
        for(int i =0;i<frente->qtdV;i++){
            glNormal3f(0,0,1);
            glTexCoord2f(frente->VTX[i].X/sizex,frente->VTX[i].Y/sizey);
            glVertex3f(frente->VTX[i].X,frente->VTX[i].Y,frente->VTX[i].Z);
        }
    glEnd();

    delete(frente->VTX);
    delete(frente);
    
    //Desenhando superior
    PLANO *superior= new PLANO;
    float yinicial=0;
    if(sizey>0){
        yinicial=sizey;
    }
    superior = CreatePlane(sizex,sizez,space,1,0,yinicial,0);
    glBegin(GL_QUADS);
        for(int i =0;i<superior->qtdV;i++){
            glNormal3f(0,1,0);
            glTexCoord2f(superior->VTX[i].X/sizex,superior->VTX[i].Z/sizez);
            glVertex3f(superior->VTX[i].X,superior->VTX[i].Y,superior->VTX[i].Z);
        }
    glEnd();
  
    delete(superior->VTX);
    delete(superior);

    //Desenhando inferior
    PLANO * inferior= new PLANO;
    yinicial=0;
    if(sizey<0){
        yinicial=sizey;
    }
    inferior = CreatePlane(sizex,sizez,space,1,0,yinicial,0);
    glBegin(GL_QUADS);
        for(int i =0;i<inferior->qtdV;i++){
            glNormal3f(0,-1,0);
            glTexCoord2f(inferior->VTX[i].X/sizex,inferior->VTX[i].Z/sizez);
            glVertex3f(inferior->VTX[i].X,inferior->VTX[i].Y,inferior->VTX[i].Z);
        }
    glEnd();
  
    delete(inferior->VTX);
    delete(inferior);

}
//Desenha braço do personagem
void Boxer:: DesenhaBraco(GLfloat x,GLfloat y,GLfloat z,GLfloat size,GLfloat angle1,
                                GLfloat angle2,GLfloat angle3,GLfloat angle4,GLfloat radius){
    //salva as atuais transformações inserindo uma copia
    
    glPushMatrix();
        //translada para o primeiro braço
        glTranslatef(x,y,z);
        //realiza rotação
       
        glRotatef(angle4,0,0,1);
        glRotatef(-angle3,0,1,0);
        glRotatef(angle1,1,0,0);
       
        //desenha o braço
        DesenhaParalepipedo(size*0.3,size*0.3,size*1.5,size/10,0.5,0.5,0.5);
        //translada para o segundo braço
        //uma pequena diferença para designer dos personagens
        glTranslatef(0,0,size*1.5);
        //rotaciona o braço
       
        glRotatef(angle2,1,0,0);
        //desenha o antebraço
        DesenhaParalepipedo(size*0.3,size*0.3,size*2,size/10,0.5,0.5,0.5);
        //translada de toda altura do braço e desenha a luva
        glTranslatef(size*0.3/2,size*0.3/2,size*2);
        DesenhaEsfera(radius,0.5,0.5,0.5,handText);
    glPopMatrix();
     //romeveu a copia da pilha
    

}
void Boxer:: DesenhaPerna(GLfloat x,GLfloat y,GLfloat z,GLfloat size,GLfloat angle1,GLfloat angle2){
    //salva as atuais transformações inserindo uma copia
    glPushMatrix();
        //translada para a primeira perna
        glTranslatef(x,y,z);
        //realiza rotação
        glRotatef(angle1,1,0,0);
        //desenha a perna
        DesenhaParalepipedo(size*0.3,-size*1.5,size*0.3,size/10,0.5,0.5,0.5);
        //translada para a segunda perna
        glTranslatef(0,-size,0);
        //rotaciona a perna
        glRotatef(angle2,1,0,0);
        //desenha o canela
        DesenhaParalepipedo(size*0.3,-size*2,size*0.3,size/10,0.5,0.5,0.5);
    glPopMatrix();

}
//desenha nariz
void Boxer:: DesenhaNariz(GLfloat x,GLfloat y,GLfloat z,GLfloat radius){
  
    glPushMatrix();
        glTranslatef(x,y,z);
        glRotatef(90,0,0,1);
        glRotatef(270,1,0,0);
        DesenhaEsfera(radius,1.0,1.0,1.0,0);
    glPopMatrix();

}
void Boxer:: DesenhaTorax(GLfloat size,GLfloat R,GLfloat G,GLfloat B){
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );

    glBindTexture (GL_TEXTURE_2D, dressText);
    glPushMatrix();
        glTranslatef(0,-size-size/2,0);
        glRotatef(-90,1,0,0);
        DesenhaCone(size,R,G,B);
    glPopMatrix();
}
//Desenha todo o personagem
void Boxer :: DesenhaBoxer(GLfloat cx,GLfloat cy,GLfloat cz,GLfloat radius,
                                string color,GLfloat angle,GLfloat angleb11,
                                GLfloat angleb12,GLfloat angleb13,GLfloat angleb14,
                                GLfloat angleb21,GLfloat angleb22,GLfloat angleb23,GLfloat angleb24,
                                GLfloat anglep11,GLfloat anglep12,GLfloat anglep21,GLfloat anglep22){
    //Começa desenho
    //copia as atuais transformações e insere na pilha
    glPushMatrix();
        //translada a té a posição do personagem
        glTranslatef(cx,cy,cz);
        //rotaciona do angulo de direção
        glRotatef(angle*180/M_PI,0,1,0);
        if(valid){
            //desenha o braço esquerdo
            DesenhaBraco(radius-radius*0.3/2,-radius*1.5-radius*0.3/2,0,radius,angleb11,angleb12,angleb13,angleb14,radius/2);
            //desenha o braço direito
            DesenhaBraco(-radius-radius*0.3/2,-radius*1.5-radius*0.3/2,0,radius,angleb21,angleb22,angleb23,angleb24,radius/2);
            //desenha o nariz
            //DesenhaNariz(0,0,radius,radius/4);
            //Desenha corpo
            DesenhaTorax(radius*2,0.5,0.5,0.5);
            //Desenha perna esquerda
            DesenhaPerna(radius/2-radius*0.3/2,-radius*3-radius*0.5,-radius*0.3/2,radius,anglep11,anglep12);
            //Desenha perna direita
            DesenhaPerna(-radius/2-radius*0.3/2,-radius*3-radius*0.5,-radius*0.3/2,radius,anglep21,anglep22);
        }
        //decide a cor da cabeça a partir da cor predefinida do persoangem
        glRotatef(90,1,0,0);
        glRotatef(180,0,0,1);
        if (!color.compare("green")){
          DesenhaEsfera(radius,0.5,0.5,0.5,headText);
        }
        if (!color.compare("red")){
          DesenhaEsfera(radius,0.5,0.5,0.5,headText);
        }
    //remove do topo da pilha a copia
    glPopMatrix();
  

}
void Boxer :: Gira(GLdouble inc,GLdouble time){
    // reseta o soco
    resetanglebracdir();
    resetanglebracesq();
    
    //gira o boneco
    angle+=inc*M_PI/180*time;
}
void Boxer :: Move(GLdouble inc, GLdouble time,GLfloat limesq,GLfloat limdir,
GLfloat cima,GLfloat baixo,GLfloat cxadv,GLfloat cyadv,GLfloat r,bool andando,float incA){ 
    //reseta o soco
    if(andando){
        resetanglebracdir();
        resetanglebracesq();
    }
    //começa a função
    //calcula os incrementos necessários e o movimento circular
    //com base ao angulo de direção
    float incx = inc*time*sin((angle));
    float incz = inc*time*cos((angle));
    //calcula a posições possíveis maximas da arena
    float x_dir,z_cima;
    float x_esq,z_baixo;
    x_dir = cX+radiuS+incx;
    x_esq = cX-radiuS+incx;
    z_cima = cZ+radiuS+incz;
    z_baixo = cZ-radiuS+incz;
    //calcula a distancia do personagem ao adversario
    float  distcx =  (cX+incx)-cxadv;
    float distcy = (cZ+incz)-cyadv;
    float dist = sqrt(pow(distcx,2)+pow(distcy,2));
    
    if(x_esq>limesq && x_dir < limdir){
       if(dist>radiusImaginary){
            cX+=incx;
       }
    }
    if(z_baixo>baixo && z_cima < cima ){
       if(dist>radiusImaginary){ 
            cZ+=incz;
       }
    }
    
    if(perna){
        if(andando){
            angleperna21-=incA*time;
            angleperna22-=incA*time;
            if((angleperna12+incA*time)<angleMaxp && (angleperna11+incA*time)>-angleMaxp*1.10){
                angleperna11+=incA*time;
                angleperna12+=incA*time;
            }
        }
        else {
            angleperna21-=incA*time;
            angleperna22-=incA*time;
        }
    }
    else{
        if(andando){
            angleperna11-=incA*time;
            angleperna12-=incA*time;
            if((angleperna22+incA*time)<angleMaxp && (angleperna21+incA*time)>-angleMaxp*1.10){
                angleperna21+=incA*time;
                angleperna22+=incA*time;
            }
        }
          else {
            angleperna11-=incA*time;
            angleperna12-=incA*time;
        }
    }

}
//reseta os angulos do braço direito
void Boxer:: resetanglebracdir(){
    anglebraco21=anglebraco21_inicial;
    anglebraco22=anglebraco22_inicial;
    anglebraco23=anglebraco23_inicial;
    anglebraco24=anglebraco24_inicial;
}
//reseta os angulos do braço esquerdo
void Boxer:: resetanglebracesq(){
    anglebraco11=anglebraco11_inicial;
    anglebraco12=anglebraco12_inicial;
    anglebraco13=anglebraco13_inicial;
    anglebraco14=anglebraco14_inicial;
}
//auxiliar de rotacionar um ponto
void rotacionaPT(GLfloat x, GLfloat y, GLfloat z,GLfloat theta,GLfloat &xOut,GLfloat &yOut,GLfloat &zOut,int eixo){
    //definição de rotação
    if(eixo == 0){ //rotação em Z
        xOut = x*cos(theta)-y*sin(theta);
        yOut = x*sin(theta)+y*cos(theta);
        zOut = z;
    }
    else if(eixo == 1){//rotação em X
        xOut = x;
        yOut = y*cos(theta)-z*sin(theta);
        zOut = y*sin(theta)+z*cos(theta);
    }
    else if (eixo == 2){//rotação em Y
        xOut = x*cos(theta)+z*sin(theta);
        yOut = y;
        zOut = -x*sin(theta)+z*cos(theta);
    }
}
void rotacionaPTI(GLfloat x, GLfloat y, GLfloat z,GLfloat theta,GLfloat &xOut,GLfloat &yOut,GLfloat &zOut,int eixo){
    //definição de rotação
    if(eixo == 0){ //rotação em Z
        xOut = x*cos(theta)+y*sin(theta);
        yOut = -x*sin(theta)+y*cos(theta);
        zOut = z;
    }
    else if(eixo == 1){//rotação em X
        xOut = x;
        yOut = y*cos(theta)+z*sin(theta);
        zOut = -y*sin(theta)+z*cos(theta);
    }
    else if (eixo == 2){//rotação em Y
        xOut = x*cos(theta)-z*sin(theta);
        yOut = y;
        zOut = x*sin(theta)+z*cos(theta);
    }
}
//pega a posição da luva
void Boxer:: getGlovesPosition(GLfloat &cx,GLfloat &cy,GLfloat &cz,GLfloat angle1,GLfloat angle2,GLfloat angle3,GLfloat angle4 ,bool esq=false,bool dir=false){
    /* PARAMETRO
      cx cy --> onde será guardado o centro da luva
      angle1 --> angulo da primeira parte do braço
      angle2 --> angulo da segunda parte do braço
      esq --> se for o braço esquerdo
      dir --> se for o braço direito
    */
    
    // calcula posição da luva para conferir pontuação
    float xinicial,yinicial,zinicial;
    //tamanho do braço
    float bracolength1 = radiuS*1.5;
    float bracolength2 = radiuS*2;
    //verifica o braço e atribui a posição inicial da base de cada braço
    if(dir){
        xinicial = -radiuS-radiuS*0.3/2;
        yinicial =  -radiuS*1.5-radiuS*0.3/2;
        zinicial=0;
    }
    else if(esq){
        xinicial = +radiuS-radiuS*0.3/2;
        yinicial = -radiuS*1.5-radiuS*0.3/2;
        zinicial=0;
    }
          
    //acha a posição final da luva
    float luvax ;
    float luvay ;
    float luvaz ;
    rotacionaPT(radiuS*0.3/2,radiuS*0.3/2,bracolength2,(angle2*M_PI/180),luvax,luvay,luvaz,1);
    luvaz+=radiuS*1.5;
    rotacionaPT(luvax,luvay,luvaz,(angle1*M_PI/180),luvax,luvay,luvaz,1);
    rotacionaPT(luvax,luvay,luvaz,(-angle3*M_PI/180),luvax,luvay,luvaz,2);
    rotacionaPT(luvax,luvay,luvaz,(angle4*M_PI/180),luvax,luvay,luvaz,0);
    
    luvax+=xinicial;
    luvay+=yinicial;
    rotacionaPT(luvax,luvay,luvaz,angle,luvax,luvay,luvaz,2);
    luvax+=cX;
    luvay+=cY;
    luvaz+=cZ;

    
    cx = luvax;
    cy = luvay;
    cz = luvaz;

}
//soco direito
void Boxer::socoDireito(GLfloat inc,GLfloat raioadversario,GLfloat cx,GLfloat cy,GLfloat cz){
    //calcula se acertou o adversário
    //pega a posição da luva do braço direito
    float luvax,luvay,luvaz;
    getGlovesPosition(luvax,luvay,luvaz,anglebraco21_inicial+3*inc,anglebraco22_inicial-5*inc,
                                        anglebraco23_inicial,anglebraco24_inicial+5*inc,false,true);
    //calcula a distancia ao adversário
    float distcx = luvax - cx;
    float distcy = luvay - cy;
    float distcz = luvaz - cz;

    float dist = sqrt(pow(distcx,2)+pow(distcy,2)+pow(distcz,2));
    //retorna o raio da luva
    float raioluva = radiuS/2;
    //verifica se a luva colidiu com o adversário
    if((raioadversario+raioluva)<(dist)){
        // define os angulos de soco
        anglebraco21=anglebraco21_inicial + 3*inc;
        anglebraco22=anglebraco22_inicial -5*inc; 
        anglebraco24 = anglebraco24_inicial+5*inc;
      
        //primeira colisão define como valida a pontuação
        pontuationValid=true;
        //define que pode avançar mais uma posição
        avancaUltimaPosixSoco = true;
    }
    //se colidiu então 
    else{
        if(avancaUltimaPosixSoco){
            // define os angulos de soco
            anglebraco21=anglebraco21_inicial + 3*inc;
            anglebraco22=anglebraco22_inicial -5*inc; 
            anglebraco24 = anglebraco24_inicial+5*inc;
            
            avancaUltimaPosixSoco = false;
        }
        //verifica se pode pontuar se sim pontua
       if(pontuationValid && (anglebraco21_inicial+3*inc)<(anglebraco21)){
            pontuation++;
            //define como falso para não pontuar de forma errada
            pontuationValid = false;
        }
    }
   
}
//soco esquerdo
void  Boxer :: socoEsquerdo(GLfloat inc,GLfloat raioadversario,GLfloat cx,GLfloat cy,GLfloat cz){

    //calcula se acertou o adversário
    //pega a posição da luva do braço esquerdo
    float luvax,luvay,luvaz;
    getGlovesPosition(luvax,luvay,luvaz,anglebraco11_inicial+3*inc,anglebraco12_inicial-5*inc,
                                        anglebraco13_inicial,anglebraco14_inicial-5*inc,true,false);
    //calcula a distancia até o adversário
    float distcx = luvax - cx;
    float distcy = luvay - cy;
    float distcz = luvaz - cz;

    float dist = sqrt(pow(distcx,2)+pow(distcy,2)+pow(distcz,2));
    //retorna raio da luva
    float raioluva = radiuS/2;
    //verifica se o soco acertou o adversario
    if((raioadversario+raioluva)<(dist)){
        //define angulo do soco
        anglebraco11 = anglebraco11_inicial + 3*inc;
        anglebraco12 = anglebraco12_inicial -5*inc;
        anglebraco14 = anglebraco14_inicial -5*inc;
        pontuationValid=true;
        avancaUltimaPosixSoco = true;
    }
    //pontuar quando valido
    else {
        if(avancaUltimaPosixSoco){
            // define os angulos de soco
            anglebraco11=anglebraco11_inicial + 3*inc;
            anglebraco12=anglebraco12_inicial -5*inc;
            anglebraco14 = anglebraco14_inicial -5*inc;
            avancaUltimaPosixSoco = false;
        }
        if(pontuationValid && (anglebraco11_inicial+3*inc)<(anglebraco11)){
            pontuation++;
            pontuationValid = false;
        }
       
    }
}
void Boxer::getEyesPosition(GLfloat &x,GLfloat &y, GLfloat &z){
    float xinicial,yinicial,zinicial;
    xinicial=0;
    yinicial=radiuS/2;
    zinicial = radiuS;
    float olhox,olhoy,olhoz;
    rotacionaPT(xinicial,yinicial,zinicial,angle,olhox,olhoy,olhoz,2);
    olhox+=cX;
    olhoy+=cY;
    olhoz+=cZ;
    x=olhox;
    y=olhoy;
    z=olhoz;
}
void Boxer::getBackPosition(GLfloat &x,GLfloat &y, GLfloat &z){
    float xinicial,yinicial,zinicial;
    xinicial=0;
    yinicial=altura;
    zinicial = -altura;
    float backx,backy,backz;
    rotacionaPT(xinicial,yinicial,zinicial,angle,backx,backy,backz,2);
    backx+=cX;
    backy+=cY;
    backz+=cZ;
    x=backx;
    y=backy;
    z=backz;
}
void Boxer::getFocusPosition(GLfloat &x,GLfloat &y, GLfloat &z){
    float xinicial,yinicial,zinicial;
    xinicial=0;
    yinicial=radiuS/2;
    zinicial = 2*radiuS;
    float focusx,focusy,focusz;
    rotacionaPT(xinicial,yinicial,zinicial,angle,focusx,focusy,focusz,2);
    focusx+=cX;
    focusy+=cY;
    focusz+=cZ;
    x=focusx;
    y=focusy;
    z=focusz;
}
void Boxer:: getPulsoPosition(GLfloat &x,GLfloat &y, GLfloat &z){
 // calcula posição do foco do pulso (camera)
    float xinicial,yinicial,zinicial;
    //tamanho do braço
    float bracolength1 = radiuS*1.5;
    float bracolength2 = radiuS*2;
    //verifica o braço e atribui a posição inicial da base de cada braço
   
    xinicial = -radiuS-radiuS*0.3/2;
    yinicial =  -radiuS*1.5-radiuS*0.3/2;
    zinicial=0;
  
          
    //acha a posição final da luva
    float pulsox ;
    float pulsoy ;
    float pulsoz ;
    rotacionaPT(-radiuS*0.1,radiuS*0.3/2,bracolength2-radiuS,(anglebraco22*M_PI/180),pulsox,pulsoy,pulsoz,1);
    pulsoz+=radiuS*1.5;
    rotacionaPT(pulsox,pulsoy,pulsoz,(anglebraco21*M_PI/180),pulsox,pulsoy,pulsoz,1);
    rotacionaPT(pulsox,pulsoy,pulsoz,(-anglebraco23*M_PI/180),pulsox,pulsoy,pulsoz,2);
    rotacionaPT(pulsox,pulsoy,pulsoz,(anglebraco24*M_PI/180),pulsox,pulsoy,pulsoz,0);
    
    pulsox+=xinicial;
    pulsoy+=yinicial;
    rotacionaPT(pulsox,pulsoy,pulsoz,angle,pulsox,pulsoy,pulsoz,2);
    pulsox+=cX;
    pulsoy+=cY;
    pulsoz+=cZ;

    
    x = pulsox;
    y = pulsoy;
    z = pulsoz;
}
void Boxer:: getPulsoFocusPosition(GLfloat &x,GLfloat &y, GLfloat &z){
  // calcula posição do foco do pulso (camera)
    float xinicial,yinicial,zinicial;
    //tamanho do braço
    float bracolength1 = radiuS*1.5;
    float bracolength2 = radiuS*2;
    //verifica o braço e atribui a posição inicial da base de cada braço
   
    xinicial = -radiuS-radiuS*0.3/2;
    yinicial =  -radiuS*1.5-radiuS*0.3/2;
    zinicial=0;
  
          
    //acha a posição final da luva
    float pulsox ;
    float pulsoy ;
    float pulsoz ;
    rotacionaPT(-radiuS*0.1,radiuS*0.3/2,bracolength2,(anglebraco22*M_PI/180),pulsox,pulsoy,pulsoz,1);
    pulsoz+=radiuS*1.5;
    rotacionaPT(pulsox,pulsoy,pulsoz,(anglebraco21*M_PI/180),pulsox,pulsoy,pulsoz,1);
    rotacionaPT(pulsox,pulsoy,pulsoz,(-anglebraco23*M_PI/180),pulsox,pulsoy,pulsoz,2);
    rotacionaPT(pulsox,pulsoy,pulsoz,(anglebraco24*M_PI/180),pulsox,pulsoy,pulsoz,0);
    
    pulsox+=xinicial;
    pulsoy+=yinicial;
    rotacionaPT(pulsox,pulsoy,pulsoz,angle,pulsox,pulsoy,pulsoz,2);
    pulsox+=cX;
    pulsoy+=cY;
    pulsoz+=cZ;

    
    x = pulsox;
    y = pulsoy;
    z = pulsoz;
}
void Boxer :: getUpPosition(GLfloat &x,GLfloat &y, GLfloat &z){
    float upx=-1,upy=0,upz=0;
    rotacionaPT(upx,upy,upz,(anglebraco22*M_PI/180),upx,upy,upz,1);
    rotacionaPT(upx,upy,upz,(anglebraco21*M_PI/180),upx,upy,upz,1);
    rotacionaPT(upx,upy,upz,(-anglebraco23*M_PI/180),upx,upy,upz,2);
    rotacionaPT(upx,upy,upz,(anglebraco24*M_PI/180),upx,upy,upz,0);
    rotacionaPT(upx,upy,upz,angle,upx,upy,upz,2);
    x=upx;
    y=upy;
    z=upz;
}
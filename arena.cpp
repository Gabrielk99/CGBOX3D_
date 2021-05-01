#include "arena.h"
typedef struct
{
    //Vertex coordinate
    double X;
    double Y;
    double Z;
    
} VERTICES;

typedef struct 
{
    VERTICES * VTX;
    int qtdV;
}PLANO;
PLANO* CreatePlane (float W,float H,float space,int plan,float x,float y,float z){
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



                n++;


                plano->VTX[n].X = (x+pass1A);
                plano->VTX[n].Y = (y+pass2F);
                plano->VTX[n].Z = z;


                n++;

                plano->VTX[n].X = (x+pass1F);
                plano->VTX[n].Y = (y+pass2F);
                plano->VTX[n].Z = z;

        

                n++;

                plano->VTX[n].X = (x+pass1F);
                plano->VTX[n].Y = (y+pass2A);
                plano->VTX[n].Z = z;

         
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

                n++;


                plano->VTX[n].X = (x+pass1A);
                plano->VTX[n].Y = (y);
                plano->VTX[n].Z = (z+pass2F);


                n++;

                plano->VTX[n].X = (x+pass1F);
                plano->VTX[n].Y = (y);
                plano->VTX[n].Z = (z+pass2F);


                n++;

                plano->VTX[n].X = (x+pass1F);
                plano->VTX[n].Y = (y);
                plano->VTX[n].Z = (z+pass2A);

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


                n++;


                plano->VTX[n].X = (x);
                plano->VTX[n].Y = (y+pass1F);
                plano->VTX[n].Z = (z+pass2A);

        
                n++;

                plano->VTX[n].X = (x);
                plano->VTX[n].Y = (y+pass1F);
                plano->VTX[n].Z = (z+pass2F);

    
                n++;

                plano->VTX[n].X = (x);
                plano->VTX[n].Y = (y+pass1A);
                plano->VTX[n].Z = (z+pass2F);

                n++;

            }
        }
    }
    return plano;
}
void Arena:: DesenhaParalepipedo(GLfloat sizex,GLfloat sizey,GLfloat sizez,float space,GLfloat R,GLfloat G,GLfloat B,GLuint text){
    GLfloat materialEmission[] = { R,G, B, 1};
    GLfloat materialColor[] = { R, G, B, 1};
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
   //GLfloat mat_shininess[] = { 100.0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    glColor3f(R,G,B);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );

    glBindTexture (GL_TEXTURE_2D, text);
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
//desenha a arena
void Arena::DesenhaArena(GLdouble width,GLdouble height,GLfloat altura,string color){
    //não possui transformações não precisa de glPushMatrix()
    //desenha retangulo
    GLUquadric* Quad =  gluNewQuadric();
    glPushMatrix();
        DesenhaParalepipedo(width,-60,height,10,0.5,0.5,0.5,chaoText);
        glTranslatef(0,altura,0);
        DesenhaParalepipedo(width,50,height,10,0.5,0.5,0.5,chaoText);
    glPopMatrix();
    gluQuadricTexture(Quad,true);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );

    glBindTexture (GL_TEXTURE_2D, cordaText);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(1,width/100,1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0,30,height);
        glRotatef(90,0,1,0);
        gluCylinder(Quad,10,10,width,50,50);
        glTranslatef(0,60,0);
        gluCylinder(Quad,10,10,width,50,50);
        glTranslatef(0,60,0);
        gluCylinder(Quad,10,10,width,50,50);
        glTranslatef(0,60,0);
        gluCylinder(Quad,10,10,width,50,50);
        glTranslatef(0,60,0);
        gluCylinder(Quad,10,10,width,50,50);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,30,0);
        glRotatef(90,0,1,0);
        gluCylinder(Quad,10,10,width,50,50);
        glTranslatef(0,60,0);
        gluCylinder(Quad,10,10,width,50,50);
        glTranslatef(0,60,0);
        gluCylinder(Quad,10,10,width,50,50);
        glTranslatef(0,60,0);
        gluCylinder(Quad,10,10,width,50,50);
        glTranslatef(0,60,0);
        gluCylinder(Quad,10,10,width,50,50);
    glPopMatrix();
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(1,height/100,1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0,30,height);
        glRotatef(180,0,1,0);
        gluCylinder(Quad,10,10,height,50,50);
        glTranslatef(0,60,0);
        gluCylinder(Quad,10,10,height,50,50);
        glTranslatef(0,60,0);
        gluCylinder(Quad,10,10,height,50,50);
        glTranslatef(0,60,0);
        gluCylinder(Quad,10,10,height,50,50);
        glTranslatef(0,60,0);
        gluCylinder(Quad,10,10,height,50,50);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(width,30,height);
        glRotatef(180,0,1,0);
        gluCylinder(Quad,10,10,height,50,50);
        glTranslatef(0,60,0);
        gluCylinder(Quad,10,10,height,50,50);
        glTranslatef(0,60,0);
        gluCylinder(Quad,10,10,height,50,50);
        glTranslatef(0,60,0);
        gluCylinder(Quad,10,10,height,50,50);
        glTranslatef(0,60,0);
        gluCylinder(Quad,10,10,height,50,50);
    glPopMatrix();
     glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );

    glBindTexture (GL_TEXTURE_2D, colunaText);
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(1,altura/100,1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(width-10,0,height-10);
        glRotatef(-90,1,0,0);
        gluCylinder(Quad,10,10,altura,50,50);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(10,0,height-10);
        glRotatef(-90,1,0,0);
        gluCylinder(Quad,10,10,altura,50,50);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(10,0,10);
        glRotatef(-90,1,0,0);
        gluCylinder(Quad,10,10,altura,50,50);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(width-10,0,10);
        glRotatef(-90,1,0,0);
        gluCylinder(Quad,10,10,altura,50,50);
    glPopMatrix();
   
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );

    glBindTexture (GL_TEXTURE_2D, ambientText);
    glPushMatrix();
        glTranslatef(width/2,0,height/2);
        glRotatef(90,0,1,0);
        glRotatef(90,1,0,0);
        gluSphere(Quad,altura*4,50,15);
    glPopMatrix();
  
}
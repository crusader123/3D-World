t#pragma comment(lib, "winmm.lib")
#include "stdafx.h"
#include "imageloader.h"
#include<GL/glut.h>
#include<gl/freeglut.h>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <cstring>
#include <MMSystem.h>
#include <time.h>
//#include<unistd.h>
#include<iostream>
//completed till humanoid+walk+jump+texture backgound

using namespace std;

//some headers imported from "http://videotutorialrocks.com"
#include "imageloader.h"

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

typedef struct
{
	float X;
	float Z;
}bullets;

//global variales
int numCoinsReqFirstLevel=1,countExit=0,countLevelCmplt=0,displayTime=1,countTimeout=0,countExit2=0,countExit3=0;
double seconds;
int flagSound=1,countSound=0;
float nightVar=0,factor=1;
int automatic1=0,automatic2=0;
int xpos2,zpos2,xpos,zpos;
float var1=0,var2=0;
int numBullets=3;
bullets bulletsArr[10];
int secondRobot=0;
int levelOne=1,levelTwo=0,bulletsMode=1,timeMode=1;
time_t startTime,presentTime;
static float ratio,legAngle=0,newlegAngle=90;
static float legAngle2=0,newlegAngle2=90;
float rotateAngle=0.0,initialX=-9.0,initialY=1.5,initialZ=1.0;
float rotateAngle2=0.0,initialX2=100,initialY2=150,initialZ2=1.0; 
static float x=0,y=5, z=15.0f;
static float lx=0.0f,ly=-5.0f,lz=-21.0f;
float vh=800,vw=600;
/*static float x =18,y=8,z=10,lx=-28,ly=-8,lz=-28;*/
int sp=0;
int sp2=0; //for 2nd
int cnn = 0,cnn2=0,cnn3=0,cnn4=0;
int zn,xn;
int zn2,xn2; // for 2nd
int spot=0;

float water_texture_time=8.0f,water_texture_size=0.7f,water_alpha=0.8f,water_texture_offset=0,stepUp=0.01;
float movingheight=0.0,staticheight=1.0,staticheight2=1.0,movingcubeheight=2;
float blockIndex[15][15]={{0}};
float blockflag[15][15]={{0}};
int waterRed=1,waterGreen=1,waterBlue=1;
int coinr=1,coing=1,coinb=1,lookanglechange=0,win=0,timeout=100;
int caughtundermovingcube=0,moveonblock=0;
int caughtundermovingcube2=0,moveonblock2=0;

int red=0.0,green=0.0,blue=0.0;
int ccc=0,ccc2=0;
int jump=0,jumpcount=0,walkcheck1=0,walkcheck2=0,walkUp=0,walkDown=0,walkUpCount=0,walkDownCount=0;
int jump2=0,jumpcount2=0,walkcheck2_1=0,walkcheck2_2=0,walkUp2=0,walkDown2=0,walkUpCount2=0,walkDownCount2=0;
int firstPersonView=0,top=0,thirdPersonView=0,helicopterView=0;
int inx=(initialX+10)/2,inz=(2-initialZ)/2;
int inx2=(initialX2+10)/2,inz2=(2-initialZ2)/2;
int movingBlock=0,isMoving=0,emptytile=0,movingcubecount=0,chancecount=0,chanceflag=0,drag=0;
int isMoving2=0,emptytile2=0,chancecount2=0,chanceflag2=0;
int score=0,nocoins=0,nocoins2=0,score2=0;
float n=0,v=0,camz=15,camlz=lz,cmz=0;
float mouseX=0,mouseY=0,mouseinX=0,mouseinY=0;
float difx=0,dify=0,lx1=x,ly1=y;
int zoomin=0,zoomout=0,totalcoins=5,totallife=3,tileviewx=0,tileviewz=0,tileView=0,favourite=0;
//int hel=0;
GLUquadricObj* quadric;
//-----------------------------------------------------------------------------------------------------------------------------

//function definitions
void firstView();
void normalView();
void topView();
void thirdView();
void helicopter();
void tiledview();
void favouriteView();


//Credits : taken from http://www.codersource.net/MFC/OpenGL/DisplayingTextOpenGLTutorial5.aspx
void drawBitmapText(char *string,float x1,float y1,float z1) 
{  
	glColor3f(1.0,0.0,0.0);
	char *c;
	glRasterPos3f(x1, y1,z1);

	for (c=string; *c != '\0'; c++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

void reInitialiseVars()
{
	//global variales
	ccc=0,ccc2=0,score2=0;
	automatic1=0,automatic2=0;
	xpos2=0,zpos2=0,xpos=0,zpos=0;
	var1=0,var2=0;
	secondRobot=1;
	levelOne=0,levelTwo=1,bulletsMode=1,timeMode=0;
	//ratio=0;
	legAngle=0,newlegAngle=90;
	legAngle2=0,newlegAngle2=90;
	rotateAngle=0.0,initialX=-9.0,initialY=1.5,initialZ=1.0;
	rotateAngle2=0.0,initialX2=0.0,initialY2=1.5,initialZ2=1.0; 

	x=0,y=5, z=15.0f;
	lx=0.0f,ly=-5.0f,lz=-21.0f;
	//vh=800,vw=600;
	sp=0;
	sp2=0; //for 2nd
	cnn = 0,cnn2=0,cnn3=0,cnn4=0;
	zn=0,xn=0;
	zn2=0,xn2=0; // for 2nd

	water_texture_time=8.0f,water_texture_size=0.7f,water_alpha=0.8f,water_texture_offset=0,stepUp=0.01;
	movingheight=0.0,staticheight=1.0,staticheight2=1.0,movingcubeheight=2;
	waterRed=1,waterGreen=1,waterBlue=1;
	coinr=1,coing=1,coinb=1,lookanglechange=0,win=0;
	caughtundermovingcube=0,moveonblock=0;
	caughtundermovingcube2=0,moveonblock2=0;

	red=0.0,green=0.0,blue=0.0;
	jump=0,jumpcount=0,walkcheck1=0,walkcheck2=0,walkUp=0,walkDown=0,walkUpCount=0,walkDownCount=0;
	jump2=0,jumpcount2=0,walkcheck2_1=0,walkcheck2_2=0,walkUp2=0,walkDown2=0,walkUpCount2=0,walkDownCount2=0;
	firstPersonView=0,top=0,thirdPersonView=0,helicopterView=0;
	inx=(initialX+10)/2,inz=(2-initialZ)/2;
	inx2=(initialX2+10)/2,inz2=(2-initialZ2)/2;
	movingBlock=0,isMoving=0,emptytile=0,movingcubecount=0,chancecount=0,chanceflag=0,drag=0;
	isMoving2=0,emptytile2=0,chancecount2=0,chanceflag2=0;
	score=0,nocoins=0;
	n=0,v=0,camz=15,camlz=lz,cmz=0;
	mouseX=0,mouseY=0,mouseinX=0,mouseinY=0;
	difx=0,dify=0,lx1=x,ly1=y;
	zoomin=0,zoomout=0,totalcoins=5,totallife=3,tileviewx=0,tileviewz=0,tileView=0,favourite=0;
	blockIndex[0][9]=6;blockIndex[2][5]=6;blockIndex[2][2]=6;blockIndex[3][8]=6;blockIndex[4][5]=6;
	blockIndex[5][3]=6;blockIndex[6][7]=6;blockIndex[7][4]=6;blockIndex[7][7]=6;blockIndex[8][2]=6;
} 
//IMPORTANT NOTE:   credits: loadtexture has been talen from videotutorial rocks.com--------------------------------------------------------------------------
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}


GLuint _textureId; //The id of the texture for island
GLuint _textureId2;//The id of the texture for water
GLuint _textureId3;//The id of the texture for water
GLuint _textureId4;
GLuint _textureId5;


//--------------------------------------------------------------------------------------------------------------------------------------------------
void changeSize(int w, int h)

{

	vh = (float)h, vw = (float)w;

	if(h == 0)h = 1;
	ratio = float(w) / float(h);

	/*glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  glViewport(0, 0, w,h);
	  gluPerspective(45,ratio,1,1000);
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  if(firstPersonView==1)
	  {
	  gluLookAt(initialX,initialY,initialZ,initialX+lx,initialY+ly,initialZ+lz,0.0,1.0,0.0);
	  }
	  else
	  {

	  gluLookAt(x, y, z,x + lx,y + ly,z + lz,0.0f,1.0f,0.0f);

	  }*/
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------
//trying to move water: credits:taken from videotutorialrocks.com----------------------------------------------------------------------------------
void advance()
{
	water_texture_offset+=stepUp/water_texture_time;
	while(water_texture_offset > water_texture_size)
		water_texture_offset-=water_texture_size;
}

// taken from net
void drawnewtree(int X,int Z)
{
	glPushMatrix();
	GLUquadricObj *quadratic1;
	quadratic1 = gluNewQuadric();
	glTranslatef(X,0,Z);
	//glPushMatrix();
	glRotatef(90,1,0,0);
	glColor3f(0.3, 0.1, 0.0);
	gluCylinder(quadratic1,0.2f,0.4f,2.0f,32,32);
	glRotatef(180,1,0,0);
	//glPopMatrix();
	glColor3f(0.0,0.3,0.0);	
	glutSolidCone(1,2,100,100);
	glPopMatrix();
}

void textures(int flags)
{
	glEnable(GL_TEXTURE_2D);
	if(flags==4)
	{
		glBindTexture(GL_TEXTURE_2D, _textureId4);
		glColor3f(1.0,1.0,1.0);
	}
	else if(flags==5)
	{
		glBindTexture(GL_TEXTURE_2D, _textureId3);
		glColor3f(1.0,1.0,1.0);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


int xcordinate(float initialX)
{
	return (initialX+10)/2;
}
int zcordinate(float initialZ)
{
	return (2-initialZ)/2;
}

void movingcube(float xx,float yy,float zz,int flags,float ht)
{
	textures(flags);

	glBegin(GL_QUADS);
	glNormal3f( 0.0f, 0.0f, 1.0f);                  // Normal Pointing Towards Viewer
	glTexCoord2f(0.0f, 0.0f); glVertex3f(xx,yy-ht,zz);  // Point 1 (Front)
	glTexCoord2f(1.0f, 0.0f); glVertex3f( xx, yy,  zz);  // Point 2 (Front)
	glTexCoord2f(1.0f, 1.0f); glVertex3f( xx+2, yy,  zz);  // Point 3 (Front)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xx+2, yy-ht,  zz);  // Point 4 (Front)
	// Back Face
	glNormal3f( 0.0f, 0.0f,-1.0f);                  // Normal Pointing Away From Viewer
	glTexCoord2f(1.0f, 0.0f); glVertex3f(xx, yy-ht, zz-2);  // Point 1 (Back)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(xx,  yy, zz-2);  // Point 2 (Back)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xx+2, yy, zz-2);  // Point 3 (Back)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(xx+2,yy-ht, zz-2);  // Point 4 (Back)
	// Top Face
	glNormal3f( 0.0f, 1.0f, 0.0f);                  // Normal Pointing Up
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xx,yy,zz);  // Point 1 (Top)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(xx,yy, zz-2);  // Point 2 (Top)
	glTexCoord2f(1.0f, 0.0f); glVertex3f( xx+2,yy, zz-2);  // Point 3 (Top)
	glTexCoord2f(1.0f, 1.0f); glVertex3f( xx+2,yy, zz);  // Point 4 (Top)
	// Bottom Face
	glNormal3f( 0.0f,-1.0f, 0.0f);                  // Normal Pointing Down
	glTexCoord2f(1.0f, 1.0f); glVertex3f(xx,yy-ht,zz);  // Point 1 (Top)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xx,yy-ht, zz-2);  // Point 2 (Top)
	glTexCoord2f(0.0f, 0.0f); glVertex3f( xx+2,yy-ht, zz-2);  // Point 3 (Top)
	glTexCoord2f(1.0f, 1.0f); glVertex3f( xx+2,yy-ht, zz);  // Point 4 (Top)
	// Right face
	glNormal3f( 1.0f, 0.0f, 0.0f);                  // Normal Pointing Right
	glTexCoord2f(1.0f, 0.0f); glVertex3f( xx+2, yy-ht, zz);  // Point 1 (Right)
	glTexCoord2f(1.0f, 1.0f); glVertex3f( xx+2, yy,zz);  // Point 2 (Right)
	glTexCoord2f(0.0f, 1.0f); glVertex3f( xx+2, yy,zz-2);  // Point 3 (Right)
	glTexCoord2f(0.0f, 0.0f); glVertex3f( xx+2, yy-ht,zz-2);  // Point 4 (Right)
	// Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);                  // Normal Pointing Left
	glTexCoord2f(0.0f, 0.0f); glVertex3f( xx, yy-ht, zz);  // Point 1 (Right)
	glTexCoord2f(1.0f, 0.0f); glVertex3f( xx, yy,zz);  // Point 2 (Right)
	glTexCoord2f(1.0f, 1.0f); glVertex3f( xx, yy,zz-2);  // Point 3 (Right)
	glTexCoord2f(0.0f, 1.0f); glVertex3f( xx, yy-ht,zz-2);  // Point 4 (Right)/////

	glEnd(); 
	glDisable(GL_TEXTURE_2D);

}

void drawcube(float xx,float zz)
{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId3);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glColor3f(1.0f, 1.0f, 1.0f);
	if(blockIndex[zcordinate(zz)][xcordinate(xx)]==7)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(1.0f, 1.0f, 1.0f);
	if(zcordinate(zz)==1 && xcordinate(xx)==6)
		glColor3f(0.0,1.0,1.0);

	glBegin(GL_QUADS);
	glNormal3f( 0.0f, 0.0f, 1.0f);                  // Normal Pointing Towards Viewer
	glTexCoord2f(0.0f, 0.0f); glVertex3f(xx, 0.0,zz);  // Point 1 (Front)
	glTexCoord2f(1.0f, 0.0f); glVertex3f( xx, 1,  zz);  // Point 2 (Front)
	glTexCoord2f(1.0f, 1.0f); glVertex3f( xx+2,1,  zz);  // Point 3 (Front)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xx+2,  0.0f,  zz);  // Point 4 (Front)
	// Back Face
	glNormal3f( 0.0f, 0.0f,-1.0f);                  // Normal Pointing Away From Viewer
	glTexCoord2f(1.0f, 0.0f); glVertex3f(xx, 0.0f, zz-2);  // Point 1 (Back)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(xx,  1, zz-2);  // Point 2 (Back)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xx+2, 1, zz-2);  // Point 3 (Back)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(xx+2, 0.0f, zz-2);  // Point 4 (Back)
	// Top Face
	glNormal3f( 0.0f, 1.0f, 0.0f);                  // Normal Pointing Up
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xx,1,zz);  // Point 1 (Top)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(xx,1, zz-2);  // Point 2 (Top)
	glTexCoord2f(1.0f, 0.0f); glVertex3f( xx+2,1, zz-2);  // Point 3 (Top)
	glTexCoord2f(1.0f, 1.0f); glVertex3f( xx+2,1, zz);  // Point 4 (Top)
	// Bottom Face
	glNormal3f( 0.0f,-1.0f, 0.0f);                  // Normal Pointing Down
	glTexCoord2f(1.0f, 1.0f); glVertex3f(xx,0,zz);  // Point 1 (Top)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xx,0, zz-2);  // Point 2 (Top)
	glTexCoord2f(0.0f, 0.0f); glVertex3f( xx+2,0, zz-2);  // Point 3 (Top)
	glTexCoord2f(1.0f, 1.0f); glVertex3f( xx+2, 0, zz);  // Point 4 (Top)
	// Right face
	glNormal3f( 1.0f, 0.0f, 0.0f);                  // Normal Pointing Right
	glTexCoord2f(1.0f, 0.0f); glVertex3f( xx+2, 0.0, zz);  // Point 1 (Right)
	glTexCoord2f(1.0f, 1.0f); glVertex3f( xx+2,1,zz);  // Point 2 (Right)
	glTexCoord2f(0.0f, 1.0f); glVertex3f( xx+2, 1,zz-2);  // Point 3 (Right)
	glTexCoord2f(0.0f, 0.0f); glVertex3f( xx+2, 0.0,zz-2);  // Point 4 (Right)
	// Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);                  // Normal Pointing Left
	glTexCoord2f(0.0f, 0.0f); glVertex3f( xx, 0.0, zz);  // Point 1 (Right)
	glTexCoord2f(1.0f, 0.0f); glVertex3f( xx,1,zz);  // Point 2 (Right)
	glTexCoord2f(1.0f, 1.0f); glVertex3f( xx, 1,zz-2);  // Point 3 (Right)
	glTexCoord2f(0.0f, 1.0f); glVertex3f( xx, 0.0,zz-2);  // Point 4 (Right)/////

	glEnd(); 
	glDisable(GL_TEXTURE_2D);

}



void drawcube2(float xx,float zz)
{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId3);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glNormal3f( 0.0f, 0.0f, 1.0f);                  // Normal Pointing Towards Viewer
	glTexCoord2f(0.0f, 0.0f); glVertex3f(xx, 0.0,zz);  // Point 1 (Front)
	glTexCoord2f(1.0f, 0.0f); glVertex3f( xx, staticheight,  zz);  // Point 2 (Front)
	glTexCoord2f(1.0f, 1.0f); glVertex3f( xx+2,  staticheight,  zz);  // Point 3 (Front)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xx+2,  0.0f,  zz);  // Point 4 (Front)
	// Back Face
	glNormal3f( 0.0f, 0.0f,-1.0f);                  // Normal Pointing Away From Viewer
	glTexCoord2f(1.0f, 0.0f); glVertex3f(xx, 0.0f, zz-2);  // Point 1 (Back)
	glTexCoord2f(1.0f, 1.0f); glVertex3f(xx,  staticheight, zz-2);  // Point 2 (Back)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xx+2, staticheight, zz-2);  // Point 3 (Back)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(xx+2, 0.0f, zz-2);  // Point 4 (Back)
	// Top Face
	glNormal3f( 0.0f, 1.0f, 0.0f);                  // Normal Pointing Up
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xx, staticheight,zz);  // Point 1 (Top)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(xx,staticheight, zz-2);  // Point 2 (Top)
	glTexCoord2f(1.0f, 0.0f); glVertex3f( xx+2,staticheight, zz-2);  // Point 3 (Top)
	glTexCoord2f(1.0f, 1.0f); glVertex3f( xx+2, staticheight, zz);  // Point 4 (Top)
	// Bottom Face
	glNormal3f( 0.0f,-1.0f, 0.0f);                  // Normal Pointing Down
	glTexCoord2f(1.0f, 1.0f); glVertex3f(xx,0,zz);  // Point 1 (Top)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xx,0, zz-2);  // Point 2 (Top)
	glTexCoord2f(0.0f, 0.0f); glVertex3f( xx+2,0, zz-2);  // Point 3 (Top)
	glTexCoord2f(1.0f, 1.0f); glVertex3f( xx+2, 0, zz);  // Point 4 (Top)
	// Right face
	glNormal3f( 1.0f, 0.0f, 0.0f);                  // Normal Pointing Right
	glTexCoord2f(1.0f, 0.0f); glVertex3f( xx+2, 0.0, zz);  // Point 1 (Right)
	glTexCoord2f(1.0f, 1.0f); glVertex3f( xx+2, staticheight,zz);  // Point 2 (Right)
	glTexCoord2f(0.0f, 1.0f); glVertex3f( xx+2,  staticheight,zz-2);  // Point 3 (Right)
	glTexCoord2f(0.0f, 0.0f); glVertex3f( xx+2, 0.0,zz-2);  // Point 4 (Right)
	// Left Face
	glNormal3f(-1.0f, 0.0f, 0.0f);                  // Normal Pointing Left
	glTexCoord2f(0.0f, 0.0f); glVertex3f( xx, 0.0, zz);  // Point 1 (Right)
	glTexCoord2f(1.0f, 0.0f); glVertex3f( xx, staticheight,zz);  // Point 2 (Right)
	glTexCoord2f(1.0f, 1.0f); glVertex3f( xx,  staticheight,zz-2);  // Point 3 (Right)
	glTexCoord2f(0.0f, 1.0f); glVertex3f( xx, 0.0,zz-2);  // Point 4 (Right)/////

	glEnd(); 
	glDisable(GL_TEXTURE_2D);

}

void drawcoin()
{

	glColor3d(coinr,coing,coinb);
	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++) {
		glVertex2f(0.5 * cos(DEG2RAD(i)), 0.5 * sin(DEG2RAD(i)));
	}
	glEnd();
}

void drawBullet()
{

	glColor3d(0,0,0);
	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++) {
		glVertex2f(0.2 * cos(DEG2RAD(i)), 0.2 * sin(DEG2RAD(i)));
	}
	glEnd();
}

//Credits: Taken from http://www.codersource.net/MFC/OpenGL/DisplayingTextOpenGLTutorial5.aspx
void drawBitmapText2(char *string,float x1,float y1,float z1) 
{  
	glColor3f(1.0,0.0,0.0);
	char *c;
	glRasterPos3f(x1, y1,z1);


	for (c=string; *c != '\0'; c++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

	}

}

void checkgameover()
{
	//cout << "############################################################################\n";
	while(countExit2<10000000)
		{
			if(countExit2==0)
				PlaySound(TEXT("mariodie.wav"), NULL,SND_ASYNC);
			countExit2++;
		}
		//countExit2=0;
	if(chanceflag==0)
	{
		countExit2=0;
		while(countExit2<10000000)
		{
			if(countExit2==0)
				PlaySound(TEXT("mariodie.wav"), NULL,SND_ASYNC);
			countExit2++;
		}				
		chancecount++;
		chanceflag=1;
	}
	initialY-=0.3;
	emptytile++;
	//waterRed=(waterRed+1)%2,waterGreen=(waterGreen+1)%2,waterBlue=(waterBlue+1)%2;
	if(emptytile==20)
	{
		//cout << "in " << initialY << endl;
		blockIndex[zpos][xpos]=0;
		if(chancecount<3)
		{
			//if(staticheight>=0)	
			initialY=1.5;
			initialX=-9,initialZ=1;
			emptytile=0;


		}
		else
		{
			
			if(chancecount==3)
			{
				initialZ=-17;
				initialX=7;
			}
			if(levelOne==1)
			{
				if(chancecount>=3)
					exit(0);
			}
			if(levelTwo==1)
			{
				if(chancecount>=3 && chancecount2>=3)
					exit(0);
			}
			/*
			if(chancecount>=3 && chancecount2>=3)
				exit(0);*/		
		}
	}
}


void checkgameover2()
{
	//cout << "############################################################################\n";
	if(emptytile==20)
	{
		/*
		while(countExit2<10000000)
		{
			if(countExit2==0)
				PlaySound(TEXT("mariodie.wav"), NULL,SND_ASYNC);
			countExit2++;
		}
		countExit2=0;
		*/
		chancecount++;
		chanceflag=1;
	}
	moveonblock=0;
	//cout << " check " << initialY << endl;
	initialY-=0.3;
	//cout << " check2 " << initialY << endl;
	//initialY-=0.3;
	emptytile++;
	//waterRed=(waterRed+1)%2,waterGreen=(waterGreen+1)%2,waterBlue=(waterBlue+1)%2;
	if(emptytile==20)
	{
		//cout << "in " << initialY << endl;
		if(chancecount<3)
		{
			//if(staticheight>=0)	
			chancecount++;
			initialY=1.5;
			initialX=-9,initialZ=1;
			emptytile=0;


		}
		else
		{
			if(chancecount==3)
			{
				//initialZ=-9;
				//initialX=-1;
				initialZ=-17;
				initialX=7;
			}
			if(levelOne==1)
			{
				if(chancecount>=3)
					exit(0);
			}
			if(levelTwo==1)
			{
				if(chancecount>=3 && chancecount2>=3)
					exit(0);
			}
			/*
			if(chancecount>=3 && chancecount2>=3)
				exit(0);*/		
		}
	}
}

void checkgameover3()
{
	if(secondRobot==0)     // i.e. in level1 i.e. levelTwo==0
		return;
	//cout << "############################################################################\n";
	while(countExit3<10000000)
		{
			if(countExit3==0)
				PlaySound(TEXT("mariodie.wav"), NULL,SND_ASYNC);
			countExit3++;
		}
		//countExit2=0;
	if(chanceflag2==0)
	{
		countExit3=0;
		while(countExit3<10000000)
		{
			if(countExit3==0)
				PlaySound(TEXT("mariodie.wav"), NULL,SND_ASYNC);
			countExit3++;
		}				
	
		chancecount2++;
		chanceflag2=1;
	}
	initialY2-=0.3;
	emptytile2++;
	//waterRed=(waterRed+1)%2,waterGreen=(waterGreen+1)%2,waterBlue=(waterBlue+1)%2;
	if(emptytile2==20)
	{
		blockIndex[zpos2][xpos2]=0;
		//cout << "in " << initialY2 << endl;
		if(chancecount2<3)
		{
			//if(staticheight>=0)	
			initialY2=1.5;
			initialX2=9,initialZ2=1;
			emptytile2=0;
		}
		else
		{
			if(chancecount2==3)
			{
				initialZ2=-17;
				initialX2=7;
			}
			if(levelOne==1)
			{
				if(chancecount2>=3)
					exit(0);
			}
			if(levelTwo==1)
			{
				if(chancecount>=3 && chancecount2>=3)
					exit(0);
			}
			/*
			if(chancecount>=3 && chancecount2>=3)
				exit(0);*/		
		}
	}
}


void checkgameover4()
{
	if(secondRobot==0)
		return;
	//cout << "############################################################################\n";
	if(emptytile2==20)
	{
		chancecount2++;
		chanceflag2=1;
	}
	moveonblock2=0;
	//cout << " check " << initialY2 << endl;
	initialY2-=0.3;
	//cout << " check2 " << initialY2 << endl;
	//initialY-=0.3;
	emptytile2++;
	//waterRed=(waterRed+1)%2,waterGreen=(waterGreen+1)%2,waterBlue=(waterBlue+1)%2;
	if(emptytile2==20)
	{
		//cout << "in " << initialY2 << endl;
		if(chancecount2<3)
		{
			//if(staticheight>=0)	
			chancecount2++;
			initialY2=1.5;
			initialX2=9,initialZ2=1;
			emptytile2=0;
		}
		else
		{
			if(chancecount2==3)
			{
				initialZ2=-17;
				initialX2=7;
			}
			if(levelOne==1)
			{
				if(chancecount2>=3)
					exit(0);
			}
			if(levelTwo==1)
			{
				if(chancecount>=3 && chancecount2>=3)
					exit(0);
			}
			/*
			   if(chancecount>=3 && chancecount2>=3)
			   exit(0);*/		
		}
	}
}
void update(int value)
{	
	nightVar=nightVar + factor*0.010;
	if(nightVar>=1)
		factor=-1;
	if(nightVar<=0)
		factor=1;
	if(timeMode==1)
	{
		time(&presentTime);
		seconds = difftime(presentTime,startTime);
		if(seconds>timeout)
		{
			displayTime=0;
			if(countTimeout==0)
					PlaySound(TEXT("warning.wav"), NULL,SND_ASYNC);				
			countTimeout++;
			if(countTimeout>40)
			{
				exit(1);
			}
			// some error msg
		}
	}
	if(bulletsMode==1)
	{
		for(int i=0;i<1;i++)
		{
			if(i==0)
			{
				if(bulletsArr[i].X< -10 || bulletsArr[i].X>10 || bulletsArr[i].Z<-18 || bulletsArr[i].Z>2)
				{
					bulletsArr[i].X = -10;
					bulletsArr[i].Z = -18; 
				}
				else			
				{
					bulletsArr[i].X += 0.5; 
					bulletsArr[i].Z += 0.5;
				}
				continue;
			}
			/*
			   bulletsArr[i].X += 0.5; 
			   bulletsArr[i].Z += 0.5;
			   if(i==1 && bulletsArr[i].X==10)
			   {
			   bulletsArr[i].X = -10;
			   bulletsArr[i].Z = -10; 
			   }
			   else if(i==2 && bulletsArr[i].X==10)
			   {
			   bulletsArr[i].X = -5;
			   bulletsArr[i].Z = -5; 
			   }*/
		}
		if(var1==10)
			var1=-10;
		else
			var1+=0.5;
		if(var2==10)
			var2=-5;
		else
			var2+=0.5;
	}

	if(coinb==1)
	{
		coinb=0;
	}
	else if(coinb==0)
	{
		coinb=1;
	}
	red=(red+1)%2;
	green=(green+1)%2;
	blue=(blue+1)%2;
	stepUp=(float)500/20000;
	advance();

	if(blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==7)
	{
		//cout << "teee-------------------------------------------------------------------\n";
		if(initialY<=2.5)initialY = 2.5;
		cnn2=1;
		if((cnn==1 && initialY==2.5) || (cnn!=1 && (cnn%10)<5))
		{
			initialY+=0.3;
		}
		else if(cnn%10>=5 && cnn%10<10 && initialY >=1.3)initialY-=0.3;
		cnn++;
		//if(cnn==10)cnn=0;
	}
	else
	{
		cnn2=0;
		cnn=1;
	}

	if(initialX<-10 || initialX>=10 || initialZ>2 || initialZ<-18)
	{		
		/*
		while(countExit2<10000000)
		{
			if(countExit2==0)
				PlaySound(TEXT("mariodie.wav"), NULL,SND_ASYNC);
			countExit2++;
		}
		*/
		checkgameover();
	}
	else
	{
		//jump-----------------------------------------------------------------------------
		
		if(jump==1)
		{
			
			if(jumpcount<5 )
				initialY+=0.3;
			if(jumpcount>=5 && jumpcount<10 && initialY>=1.5)
				initialY-=0.3;
			if(((blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=3 && blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=7)|| (moveonblock==1))&& blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=2 && blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=4  )
				//if((blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=3 || (blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==3 && moveonblock==1)) && blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=2 && blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=4)
			{
				initialX+=0.4*sin((rotateAngle/180)*PI);
				initialZ+=0.4*cos((rotateAngle/180)*PI);
			}

			if(((blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==3 && cnn2==0) ||(blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==7 && cnn2!=0)) && initialY-1>=staticheight && moveonblock==0)

				//if(blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==3 && initialY-1>=staticheight && moveonblock==0)
			{

				//cout << initialY-1.5 << endl;
				initialY=staticheight+1.5;
				jumpcount=9;
				moveonblock=1;

				//jump=0;

			}
			jumpcount++;
			//cout << initialY << " initialss " <<  " static " << staticheight << endl;

			//    cout << initialY << "####" << "jumpcount"<<jumpcount <<" \n";
		}
		if(jumpcount==10)
		{
			jump=0;
			jumpcount=0;
			legAngle=0.0;
		}
		//------------------------------------------------------------------------------------------

		//------------------to maintain momentum while walking back-------------------------------
		if(walkUp==1)
		{

			if(walkcheck1==0)
			{
				legAngle=45;
				walkcheck1=1;
			}
			else
			{
				legAngle=-45;
				walkcheck1=0;
			}
			int chkx=xcordinate((initialX)-(0.5*sin((rotateAngle/180)*PI)));
			int chkz=zcordinate((initialZ)-(0.5*cos((rotateAngle/180)*PI)));

			//if(blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=2 && ((blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==3 && moveonblock==1)|| ( blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==3 && blockIndex[chkz][chkx]!=3) || blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=3))

			if(blockIndex[(zcordinate(initialZ))][xcordinate(initialX)]!=2 && (((blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==3 || blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==7 ) && moveonblock == 1) ||( (blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==3 || blockIndex[zcordinate(initialZ)][xcordinate(initialX)] == 7 )&& (blockIndex[chkz][chkx]!=7 && blockIndex[chkz][chkx]!=3)) || (blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=3 && blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=7)  ))
			{
				initialX-=0.5*sin((rotateAngle/180)*PI);
				initialZ-=0.5*cos((rotateAngle/180)*PI);
			}
			walkUpCount++;

			if(walkUpCount==4)
			{
				walkUpCount=0;
				walkUp=0;

				//legAngle=0;


			}

		}

		//cout << initialY << " initialvvv " <<  " static " << staticheight << endl;
		//cout << " move " << moveonblock << endl;
		if(blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==3 && (sp == 1 || initialY>=staticheight+1.5))
		{
			if(zcordinate(initialZ)==1 && xcordinate(initialX)==6)
			{
				moveonblock=0;
				cout << initialY << " " << ccc <<endl;
				if(initialY>= -2.5 && ccc==0)
				initialY=initialY-0.5;
				if(initialY<=-2.5)
				{

					//initialY=initialY+0.5;
					//ccc++;
					  initialX=-9,initialZ=-5,initialY=1.5;
					  ccc=0;
				}
/*				else if(initialY >= -2.5 && ccc>=1 && ccc<9)
				{
					initialY=initialY+0.5;
					ccc++;

				}
				else if(initialY >=1.5 && ccc==9)
				{
					ccc=0;
					initialX=-9,initialZ=-5;
						//initialY=1.5;
				} */

				
			}
			else
			{
			staticheight-=0.1;
			zn=zcordinate(initialZ),xn = xcordinate(initialX);
			blockflag[zn][xn]=1;
			if(initialY>1.5)
				initialY=staticheight+1.5;
			if(staticheight<0 && initialY<=1.5)
			{
				//cout << initialY << " initial " <<  " static " << staticheight << endl;
				checkgameover2();
			}
			}

			sp=1;
			
			// moveonblock=1;

		}
		else if(!(blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==3 && (sp2 == 1 || initialY2>=staticheight+1.5)))
		{
			blockflag[zn][xn]=0;
			staticheight=1;
			sp=0;
		}


		//----------------------------------------------------------------------------------------

		//---------------------------------to maintain momentum while forward moving---------------------------

		if(walkDown==1 || automatic1==1)
		{


			if(walkcheck2==0)
			{
				legAngle=-45;
				walkcheck2=1;
			}
			else
			{
				legAngle=45;
				walkcheck2=0;
			}

			int chkx=xcordinate((initialX)+(0.5*sin((rotateAngle/180)*PI)));
			int chkz=zcordinate((initialZ)+(0.5*cos((rotateAngle/180)*PI)));
			if(blockIndex[(zcordinate(initialZ))][xcordinate(initialX)]!=2 && (((blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==3 || blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==7 ) && moveonblock == 1) ||( (blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==3 || blockIndex[zcordinate(initialZ)][xcordinate(initialX)] == 7 )&& (blockIndex[chkz][chkx]!=7 && blockIndex[chkz][chkx]!=3)) || (blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=3 && blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=7)  ))
				//if(blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=2 && ((blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==3 && moveonblock==1)|| ( blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==3 && blockIndex[chkz][chkx]!=3) || blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=3))
			{
				initialX+=0.5*sin((rotateAngle/180)*PI);
				initialZ+=0.5*cos((rotateAngle/180)*PI);
			}
			walkDownCount++;


			if(walkDownCount==4)
			{
				walkDownCount=0;
				walkDown=0;

			}

		}


		/*if(coinb==1)
		  {
		  coinb=0;
		  }
		  else if(coinb==0)
		  {
		  coinb=1;
		  }
		  red=(red+1)%2;
		  green=(green+1)%2;
		  blue=(blue+1)%2;
		  stepUp=(float)500/20000;
		  advance();*/
		if(movingheight>=3)movingBlock=1;
		if(movingheight<=0.0)movingBlock=0;
		if(movingBlock==0)
		{
			movingheight+=0.25;
		}
		else movingheight-=0.25;

		if(isMoving==1)initialY=movingheight+1.5;
		inx=(initialX+10)/2,inz=(2-initialZ)/2;
		if(movingcubeheight>=6)movingcubecount=1;
		if(movingcubeheight<=2)movingcubecount=0;   
		if(movingcubecount==0 && caughtundermovingcube!=1)movingcubeheight+=0.1;
		else if(movingcubecount==1 && caughtundermovingcube!=1)movingcubeheight-=0.1;
		if(caughtundermovingcube==1)movingcubeheight=-5;
		if(inx<10 && inx>=0 && inz<10 && inz>=0 && blockIndex[inz][inx]==1)
		{
			isMoving=1;
			float check=initialY-1.5;
			if(check>=movingheight)
			{

				initialY=movingheight+1.5;

				jump=0;
				jumpcount=0;
				legAngle=0.0;
			}

		}
		else if((blockIndex[inz][inx]==3 || blockIndex[inz][inx]==7)&& jump==0 && initialY==2.5)
		{
			//cout << "ii" << initialY << endl;
			//	moveonblock=1;
		}
		else if(blockIndex[inz][inx]==3 && initialY<2.5 && sp==0)moveonblock=0;
		else if(blockIndex[inz][inx]==7 && initialY<2.5 && cnn2!=1)moveonblock=0;
		//else if(blockIndex[inz][inx]!=3)moveonblock=1; 
		else if(jump!=1 && blockIndex[inz][inx]!=2 && blockIndex[inz][inx]!=4 && sp==0 && cnn2==0)
		{
			isMoving=0;
			initialY=1.5;
		}



		if(inx<10 && inx>=0 && inz<10 && inz>=0 && blockIndex[inz][inx]==2) 
		{
			checkgameover();

		}

		if(inx<10 && inx>=0 && inz<10 && inz>=0 && blockIndex[inz][inx]==4 && movingcubeheight-2<=initialY+0.5) 
		{
			caughtundermovingcube=1;
			//	if(emptytile==20)exit(0);
			checkgameover();
			if(emptytile==0)
			{
				caughtundermovingcube=0;
				movingcubeheight=2;
			}

		}


		if(inx<10 && inx>=0 && inz<10 && inz>=0 && blockIndex[inz][inx]==6) 
		{
			blockIndex[inz][inx]=0;
			PlaySound(TEXT("coin.wav"), NULL,SND_ASYNC);
			flagSound=0;
			countSound=0;
			nocoins++;
			score+=100;
			/*
			if(nocoins==numCoinsReqFirstLevel && levelOne==1)
			{
				levelOne=0;
				reInitialiseVars();
				levelTwo=1;
				timeMode=0;
				secondRobot=1;
			}*/
			//cout << nocoins << " " << score << endl;
		}

		if(blockIndex[inz][inx]==0)chanceflag=0;

		for(int i1=0;i1<numBullets;i1++)
		{
			cout << "diffX " << fabs(bulletsArr[i1].X - initialX) << endl;
			cout << "diffY " << fabs(initialY - 1.5) << endl;
			cout << "diffZ " << fabs(bulletsArr[i1].Z - initialZ) << endl;
			if(fabs(bulletsArr[i1].X-initialX)<= 0.3 && fabs(bulletsArr[i1].Z-initialZ)<= 0.3 && fabs(initialY-1.5)<=0.3 )
			{
				//exit(1);
				xpos = xcordinate(initialX);
				zpos = zcordinate(initialZ);
				blockIndex[zpos][xpos]=2;
				while(countExit2<1000000)
				{
					if(countExit2==0)
						PlaySound(TEXT("mariodie.wav"), NULL,SND_ASYNC);
					countExit2++;
				}
				countExit2=0;
				checkgameover();
				cout << chancecount << endl;
			}
		}
		if(blockIndex[inz][inx]!=3 && blockIndex[inz][inx]!=7)moveonblock=0;
		//cout << "block " << inz << " " << inx << " " << blockIndex[inz][inx] << " " << initialY << " " << initialX << " " << initialZ <<endl;
		
		
			if(nocoins>=numCoinsReqFirstLevel && levelOne==1 && inx==9 && inz==9)
			{
				win++;
				if(countLevelCmplt==0)
					PlaySound(TEXT("stageclear.wav"), NULL,SND_ASYNC);				
				countLevelCmplt++;
				if(countLevelCmplt>40)
				{
					levelOne=0;
					reInitialiseVars();
					levelTwo=1;
					timeMode=0;
					secondRobot=1;
				}
			}
		
	}//outer else


	//-------------for 2nd robot-----------------------
	if(secondRobot==1)
	{

		if(blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==7)
		{
			if(initialY2<=2.5)initialY2 = 2.5;
			cnn4=1;
			if((cnn3==1 && initialY2==2.5) || (cnn3!=1 && (cnn3%10)<5))
			{
				initialY2+=0.3;
			}
			else if(cnn3%10>=5 && cnn3%10<10 && initialY2 >=1.3)initialY2-=0.3;
			cnn3++;
			//if(cnn==10)cnn=0;
		}
		else
		{
			cnn4=0;
			cnn3=1;
		}

		if(initialX2<-10 || initialX2>=10 || initialZ2>2 || initialZ2<-18)
		{
			checkgameover3();
		}
		else
		{
			//jump-----------------------------------------------------------------------------
			if(jump2==1)
			{
				if(jumpcount2<5 )
					initialY2+=0.3;
				if(jumpcount2>=5 && jumpcount2<10 && initialY2>=1.5)
					initialY2-=0.3;
				if(((blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=3 && blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=7)|| (moveonblock2==1 && (blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=7)))&& blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=2 && blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=4  )
					//if((blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=3 || (blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==3 && moveonblock2==1)) && blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=2 && blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=4)
				{
					initialX2+=0.4*sin((rotateAngle2/180)*PI);
					initialZ2+=0.4*cos((rotateAngle2/180)*PI);
				}

				if(((blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==3 && cnn4==0) ||(blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==7 && cnn4!=0)) && initialY2-1>=staticheight && moveonblock2==0)
					//if(blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==3 && initialY2-1>=staticheight && moveonblock2==0)
				{

					//cout << initialY2-1.5 << endl;
					initialY2=staticheight+1.5;
					jumpcount2=9;
					moveonblock2=1;

					//jump=0;

				}
				jumpcount2++;
				//cout << initialY2 << " initialss " <<  " static " << staticheight << endl;

				//    cout << initialY << "####" << "jumpcount"<<jumpcount <<" \n";
			}
			if(jumpcount2==10)
			{
				jump2=0;
				jumpcount2=0;
				legAngle2=0.0;
			}
			//------------------------------------------------------------------------------------------

			//------------------to maintain momentum while walking back-------------------------------
			if(walkUp2==1)
			{

				if(walkcheck2_1==0)
				{
					legAngle2=45;
					walkcheck2_1=1;
				}
				else
				{
					legAngle2=-45;
					walkcheck2_1=0;
				}
				int chkx2=xcordinate((initialX2)-(0.5*sin((rotateAngle2/180)*PI)));
				int chkz2=zcordinate((initialZ2)-(0.5*cos((rotateAngle2/180)*PI)));
				if(blockIndex[(zcordinate(initialZ2))][xcordinate(initialX2)]!=2 && (((blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==3 || blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==7 ) && moveonblock2 == 1) ||( (blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==3 || blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)] == 7 )&& (blockIndex[chkz2][chkx2]!=7 && blockIndex[chkz2][chkx2]!=3)) || (blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=3 && blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=7)  ))
					//if(blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=2 && ((blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==3 && moveonblock2==1)|| ( blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==3 && blockIndex[chkz2][chkx2]!=3) || blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=3))
				{
					initialX2-=0.5*sin((rotateAngle2/180)*PI);
					initialZ2-=0.5*cos((rotateAngle2/180)*PI);
				}
				walkUpCount2++;

				if(walkUpCount2==2)
				{
					walkUpCount2=0;
					walkUp2=0;

					//legAngle2=0;


				}

			}

			//cout << initialY2 << " initialvvv " <<  " static " << staticheight << endl;
			//cout << " move " << moveonblock2 << endl;
			if(blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==3 && (sp2 == 1 || initialY2>=staticheight+1.5))
			{

			if(zcordinate(initialZ2)==1 && xcordinate(initialX2)==6)
			{
				//cout << initialY << " " << ccc <<endl;
				moveonblock2=0;
				if(initialY2>= -2.5 && ccc2==0)
				initialY2=initialY2-0.5;
				if(initialY2<=-2.5)
				{

				//	initialY2=initialY2+0.5;
					//ccc2++;
					initialX2=-9,initialZ2=-5,initialY2=1.5;
					  ccc2=0;
				}
/*				else if(initialY2 >= -2.5 && ccc2>=1 && ccc2<9)
				{
					initialY2=initialY2+0.5;
					ccc2++;

				}
				else if(initialY2 >=1.5 && ccc2==9)
				{
					ccc2=0;
					initialX2=-9,initialZ2=-5;
						//initialY=1.5;
				}*/
			}
			else
			{

				staticheight-=0.1;
				zn2=zcordinate(initialZ2),xn2 = xcordinate(initialX2);
				blockflag[zn2][xn2]=1;
				if(initialY2>1.5)
					initialY2=staticheight+1.5;
				if(staticheight<0 && initialY2<=1.5)
				{
					//cout << initialY2 << " initial " <<  " static " << staticheight << endl;
					checkgameover4();
				}
			}

				sp2=1;
				// moveonblock2=1;

			}
			else if(!(blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==3 && (sp == 1 || initialY>=staticheight+1.5)))

			{
				blockflag[zn2][xn2]=0;
				staticheight=1;
				sp2=0;
			}


			//----------------------------------------------------------------------------------------

			//---------------------------------to maintain momentum while forward moving---------------------------

			if(walkDown2==1 || automatic2==1)
			{


				if(walkcheck2_2==0)
				{
					legAngle2=-45;
					walkcheck2_2=1;
				}
				else
				{
					legAngle2=45;
					walkcheck2_2=0;
				}

				int chkx2=xcordinate((initialX2)+(0.5*sin((rotateAngle2/180)*PI)));
				int chkz2=zcordinate((initialZ2)+(0.5*cos((rotateAngle2/180)*PI)));
				if(blockIndex[(zcordinate(initialZ2))][xcordinate(initialX2)]!=2 && (((blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==3 || blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==7 ) && moveonblock2 == 1) ||( (blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==3 || blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)] == 7 )&& (blockIndex[chkz2][chkx2]!=7 && blockIndex[chkz2][chkx2]!=3)) || (blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=3 && blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=7)  ))
					//if(blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=2 && ((blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==3 && moveonblock2==1)|| ( blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==3 && blockIndex[chkz2][chkx2]!=3) || blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=3))
				{
					initialX2+=0.5*sin((rotateAngle2/180)*PI);
					initialZ2+=0.5*cos((rotateAngle2/180)*PI);
				}
				walkDownCount2++;


				if(walkDownCount2==2)
				{
					walkDownCount2=0;
					walkDown2=0;
				}

			}

			/*if(coinb==1)
			  {
			  coinb=0;
			  }
			  else if(coinb==0)
			  {
			  coinb=1;
			  }
			  red=(red+1)%2;
			  green=(green+1)%2;
			  blue=(blue+1)%2;
			  stepUp=(float)500/20000;
			  advance();
			 */
			if(movingheight>=3)movingBlock=1;
			if(movingheight<=0.0)movingBlock=0;
			if(movingBlock==0)
			{
				movingheight+=0.25;
			}
			else
				movingheight-=0.25;

			if(isMoving2==1)
				initialY2=movingheight+1.5;
			inx2=(initialX2+10)/2,inz2=(2-initialZ2)/2;
			if(movingcubeheight>=6)movingcubecount=1;
			if(movingcubeheight<=2)movingcubecount=0; 
			if(movingcubecount==0 && caughtundermovingcube2!=1)movingcubeheight+=0.1;
			else if(movingcubecount==1 && caughtundermovingcube2!=1)movingcubeheight-=0.1;
			if(caughtundermovingcube2==1)movingcubeheight=-5;
			if(inx2<10 && inx2>=0 && inz2<10 && inz2>=0 && blockIndex[inz2][inx2]==1)
			{
				isMoving2=1;
				float check=initialY2-1.5;
				if(check>=movingheight)
				{

					initialY2=movingheight+1.5;

					jump2=0;
					jumpcount2=0;
					legAngle2=0.0;
				}

			}
			else if((blockIndex[inz2][inx2]==3||blockIndex[inz2][inx2]==7) && jump2==0 && initialY2==2.5)
			{
				//cout << "ii" << initialY2 << endl;
				//	moveonblock2=1;
			}
			else if(blockIndex[inz2][inx2]==3 && initialY2<2.5 && sp2==0)moveonblock2=0;
			else if(blockIndex[inz2][inx2]==7 && initialY2<2.5 && cnn4!=1)moveonblock2=0;
			//else if(blockIndex[inz2][inx2]!=3)moveonblock2=1; 
			else if(jump2!=1 && blockIndex[inz2][inx2]!=2 && blockIndex[inz2][inx2]!=4 && sp2==0 && cnn4==0)
			{
				isMoving2=0;
				initialY2=1.5;
			}

			if(inx2<10 && inx2>=0 && inz2<10 && inz2>=0 && blockIndex[inz2][inx2]==2) 
			{

				checkgameover3();
			}

			if(inx2<10 && inx2>=0 && inz2<10 && inz2>=0 && blockIndex[inz2][inx2]==4 && movingcubeheight-2<=initialY2+0.5) 
			{
				caughtundermovingcube2=1;
				//	if(emptytile==20)exit(0);
				checkgameover3();
				if(emptytile2==0)
				{
					caughtundermovingcube2=0;
					movingcubeheight=2;
				}

			}


			if(inx2<10 && inx2>=0 && inz2<10 && inz2>=0 && blockIndex[inz2][inx2]==6) 
			{
				blockIndex[inz2][inx2]=0;
				nocoins2++;
				score2+=100;
				PlaySound(TEXT("coin.wav"), NULL,SND_ASYNC);
				flagSound=0;
			countSound=0;
				//cout << nocoins << " " << score << endl;
			}

			if(blockIndex[inz2][inx2]==0)
				chanceflag2=0;
			for(int i1=0;i1<numBullets;i1++)
			{
				if( fabs(bulletsArr[i1].X-initialX2) < 0.1 && fabs(bulletsArr[i1].Z-initialZ2) < 0.3 && fabs(initialY2-1.5)<0.3 )
				{
					//exit(1);
					xpos2 = xcordinate(initialX2);
					zpos2 = zcordinate(initialZ2);
					blockIndex[zpos2][xpos2]=2;
					checkgameover3();
					cout << chancecount2 << endl;
				}
			}


			if(blockIndex[inz2][inx2]!=3 && blockIndex[inz2][inx2]!=7)moveonblock2=0;
			//cout << "block " << inz << " " << inx << " " << blockIndex[inz][inx] << " " << initialY << " " << initialX << " " << initialZ <<endl;
			if(inx2==9 && inz2==9)
			{
				win++;
			}

		}//outer else  */
	}
		if((nocoins+nocoins2)>=3 && levelTwo==1 && ( (inz==9 && inx==9/* && nocoins>=nocoins2*/) || (inz2==9 && inx2==9/* && nocoins2>=nocoins*/)))
			{
				if(countExit==0)
				{
					PlaySound(TEXT("worldclear.wav"), NULL,SND_ASYNC);				
				}
				if(countExit<=50)
				{
					printf("Hiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii");
					//Sleep(100);
			  	   char str[100]="Sorry Game Over !!!";
				    drawBitmapText(str,0,5,0);
				}
				countExit++;
				if(countExit>50)
					exit(0);
			}

	glutTimerFunc(100, update, 0);
}


//----------------------------------------------------drawHuman-------------------------------------------------------------------------------
void drawHumanoid()

{



	//--------------------------------------------------torso------------------------------------------------------
	glColor3f(0.4,0.4,0.4);
	glPushMatrix();
	glTranslatef(initialX,initialY,initialZ);
	glRotatef(rotateAngle,0.0,1.0,0.0);
	glPushMatrix();
	glRotatef(90.0,1.0,0.0,0.0);
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricOrientation(quadric, GLU_OUTSIDE);

	gluCylinder(quadric,0.3,0.3,1,10,10);

	glPopMatrix();

	//--------------------------------------------------head-------------------------------------------
	glColor3f(0.2,1.0,0.0);
	glTranslatef(0.0,0.25,0.0);
	glutSolidSphere(0.25,10,10);

	//-------------------------------------------------eyes--------------------------------------------
	glPushMatrix();

	glColor3d(red,green,blue);
	glTranslatef(0.05f, 0.10f, 0.18f);

	glutSolidSphere(0.05f,10,10);

	glTranslatef(-0.1f, 0.0f, 0.0f);

	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

	//-----------------------------------------------------mouth---------------------------------------------
	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glTranslatef(0.0,-0.1,0.25);
	glutSolidSphere(0.05,10,10);
	glPopMatrix();

	//-------------------------------------------------------------------------

	//----------------------------------------------------right shoulder-----------------------------------
	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glTranslatef(0.35,-0.35,0.0);
	glutSolidSphere(0.1,10,10);


	//---------------------------------------------------------right arm-------------------------------------------


	glTranslatef(0.00,-0.08,0.0);
	//glRotatef(45,0.0,1.0,0.0);
	if(jump==0)
		glRotatef(legAngle,1.0,0.0,0.0);
	else
		glRotatef(newlegAngle,1.0,0.0,0.0);
	glRotatef(90,1.0,0.0,0.0);


	GLUquadricObj* quadric2;
	quadric2 = gluNewQuadric();
	glColor3f(0.0,0.0,1.0);
	gluQuadricDrawStyle(quadric2, GLU_FILL);
	gluQuadricNormals(quadric2, GLU_SMOOTH);
	gluQuadricOrientation(quadric2, GLU_OUTSIDE);
	gluCylinder(quadric2,0.1,0.1,0.5,10,10);

	glTranslatef(0.0,0.0,0.60);
	glColor3f(1.0,0.0,0.0);
	glutSolidSphere(0.1,10,10);
	glPopMatrix();


	//-------------------------------------------------------------------------
	//-----------------------------------------------left shoulder-----------------------------------------------------------
	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glTranslatef(-0.35,-0.35,0.0);
	glutSolidSphere(0.1,10,10);


	//-------------------------------------------------------leftt arm------------------------------------------------------------

	glTranslatef(0.00,-0.08,0.0);
	// glRotatef(-45,0.0,1.0,0.0);
	if(jump==0)
		glRotatef(-legAngle,1.0,0.0,0.0);
	else
		glRotatef(newlegAngle,1.0,0.0,0.0);
	glRotatef(90,1.0,0.0,0.0);

	GLUquadricObj* quadric3;
	quadric3 = gluNewQuadric();
	glColor3f(0.0,0.0,1.0);
	gluQuadricDrawStyle(quadric3, GLU_FILL);
	gluQuadricNormals(quadric3, GLU_SMOOTH);
	gluQuadricOrientation(quadric3, GLU_OUTSIDE);
	gluCylinder(quadric3,0.1,0.1,0.5,10,10);

	glTranslatef(0.0,0.0,0.60);
	glColor3f(1.0,0.0,0.0);
	glutSolidSphere(0.1,10,10);
	glPopMatrix();


	//-----------------------------------------------------------------------------right leg----------------------------------

	glPushMatrix();
	glTranslatef(0.0,-1.25,0.0);
	if(jump==0)
		glRotatef(legAngle,1.0,0.0,0.0);
	else
		glRotatef(-newlegAngle,1.0,0.0,0.0);
	//rightleg
	glPushMatrix();
	glTranslatef(0.25,0.0,0.0);
	//glRotatef(legAngle,0.0,1.0,0.0);
	glRotatef(90,1.0,0.0,0.0);
	GLUquadricObj* quadric4;
	quadric4 = gluNewQuadric();
	glColor3f(0.0,0.0,1.0);
	gluQuadricDrawStyle(quadric4, GLU_FILL);
	gluQuadricNormals(quadric4, GLU_SMOOTH);
	gluQuadricOrientation(quadric4, GLU_OUTSIDE);
	gluCylinder(quadric4,0.08,0.08,0.5,10,10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.25,-0.58,0.00);
	glColor3f(1.0,0.0,0.0);
	glutSolidSphere(0.08,10,10);
	glPopMatrix();
	glPopMatrix();
	//---------------------------------------------------------------------------------left leg----------------------------------
	glPushMatrix();

	glTranslatef(0.0,-1.25,0.0);
	if(jump==0)
		glRotatef(-legAngle,1.0,0.0,0.0);
	else
		glRotatef(-newlegAngle,1.0,0.0,0.0);


	glPushMatrix();
	glTranslatef(-0.25,0.0,0.0);
	//glRotatef(legAngle,0.0,1.0,0.0);
	glRotatef(90,1.0,0.0,0.0);
	GLUquadricObj* quadric5;
	quadric5 = gluNewQuadric();
	glColor3f(0.0,0.0,1.0);
	gluQuadricDrawStyle(quadric5, GLU_FILL);
	gluQuadricNormals(quadric5, GLU_SMOOTH);
	gluQuadricOrientation(quadric5, GLU_OUTSIDE);
	gluCylinder(quadric5,0.08,0.08,0.5,10,10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.25,-0.58,0.00);
	glColor3f(1.0,0.0,0.0);
	glutSolidSphere(0.08,10,10);
	glPopMatrix();
	glPopMatrix();



	glPopMatrix();//for the outermost


}

void drawHumanoid2()
{



	//--------------------------------------------------torso------------------------------------------------------
	glColor3f(0.8,0.8,0.8);
	glPushMatrix();
	glTranslatef(initialX2,initialY2,initialZ2);
	glRotatef(rotateAngle2,0.0,1.0,0.0);
	glPushMatrix();
	glRotatef(90.0,1.0,0.0,0.0);
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricOrientation(quadric, GLU_OUTSIDE);

	gluCylinder(quadric,0.3,0.3,1,10,10);

	glPopMatrix();

	//--------------------------------------------------head-------------------------------------------
	glColor3f(1.0,1.0,0.0);
	glTranslatef(0.0,0.25,0.0);
	glutSolidSphere(0.25,10,10);

	//-------------------------------------------------eyes--------------------------------------------
	glPushMatrix();

	glColor3d(red,green,blue);
	glTranslatef(0.05f, 0.10f, 0.18f);

	glutSolidSphere(0.05f,10,10);

	glTranslatef(-0.1f, 0.0f, 0.0f);

	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

	//-----------------------------------------------------mouth---------------------------------------------
	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glTranslatef(0.0,-0.1,0.25);
	glutSolidSphere(0.05,10,10);
	glPopMatrix();

	//-------------------------------------------------------------------------

	//----------------------------------------------------right shoulder-----------------------------------
	glPushMatrix();
	glColor3f(0.0,0.0,1.0);
	glTranslatef(0.35,-0.35,0.0);
	glutSolidSphere(0.1,10,10);


	//---------------------------------------------------------right arm-------------------------------------------


	glTranslatef(0.00,-0.08,0.0);
	//glRotatef(45,0.0,1.0,0.0);
	if(jump2==0)
		glRotatef(legAngle2,1.0,0.0,0.0);
	else
		glRotatef(newlegAngle2,1.0,0.0,0.0);
	glRotatef(90,1.0,0.0,0.0);


	GLUquadricObj* quadric2;
	quadric2 = gluNewQuadric();
	glColor3f(1.0,0.0,0.0);
	gluQuadricDrawStyle(quadric2, GLU_FILL);
	gluQuadricNormals(quadric2, GLU_SMOOTH);
	gluQuadricOrientation(quadric2, GLU_OUTSIDE);
	gluCylinder(quadric2,0.1,0.1,0.5,10,10);

	glTranslatef(0.0,0.0,0.60);
	glColor3f(0.0,0.0,1.0);
	glutSolidSphere(0.1,10,10);
	glPopMatrix();


	//-------------------------------------------------------------------------
	//-----------------------------------------------left shoulder-----------------------------------------------------------
	glPushMatrix();
	glColor3f(0.0,0.0,1.0);
	glTranslatef(-0.35,-0.35,0.0);
	glutSolidSphere(0.1,10,10);


	//-------------------------------------------------------leftt arm------------------------------------------------------------

	glTranslatef(0.00,-0.08,0.0);
	// glRotatef(-45,0.0,1.0,0.0);
	if(jump2==0)
		glRotatef(-legAngle2,1.0,0.0,0.0);
	else
		glRotatef(newlegAngle2,1.0,0.0,0.0);
	glRotatef(90,1.0,0.0,0.0);

	GLUquadricObj* quadric3;
	quadric3 = gluNewQuadric();
	glColor3f(1.0,0.0,0.0);
	gluQuadricDrawStyle(quadric3, GLU_FILL);
	gluQuadricNormals(quadric3, GLU_SMOOTH);
	gluQuadricOrientation(quadric3, GLU_OUTSIDE);
	gluCylinder(quadric3,0.1,0.1,0.5,10,10);

	glTranslatef(0.0,0.0,0.60);
	glColor3f(0.0,0.0,1.0);
	glutSolidSphere(0.1,10,10);
	glPopMatrix();


	//-----------------------------------------------------------------------------right leg----------------------------------

	glPushMatrix();
	glTranslatef(0.0,-1.25,0.0);
	if(jump2==0)
		glRotatef(legAngle2,1.0,0.0,0.0);
	else
		glRotatef(-newlegAngle2,1.0,0.0,0.0);
	//rightleg
	glPushMatrix();
	glTranslatef(0.25,0.0,0.0);
	//glRotatef(legAngle,0.0,1.0,0.0);
	glRotatef(90,1.0,0.0,0.0);
	GLUquadricObj* quadric4;
	quadric4 = gluNewQuadric();
	glColor3f(1.0,0.0,0.0);
	gluQuadricDrawStyle(quadric4, GLU_FILL);
	gluQuadricNormals(quadric4, GLU_SMOOTH);
	gluQuadricOrientation(quadric4, GLU_OUTSIDE);
	gluCylinder(quadric4,0.08,0.08,0.5,10,10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.25,-0.58,0.00);
	glColor3f(0.0,0.0,1.0);
	glutSolidSphere(0.08,10,10);
	glPopMatrix();
	glPopMatrix();
	//---------------------------------------------------------------------------------left leg----------------------------------
	glPushMatrix();

	glTranslatef(0.0,-1.25,0.0);
	if(jump2==0)
		glRotatef(-legAngle2,1.0,0.0,0.0);
	else
		glRotatef(-newlegAngle2,1.0,0.0,0.0);


	glPushMatrix();
	glTranslatef(-0.25,0.0,0.0);
	//glRotatef(legAngle,0.0,1.0,0.0);
	glRotatef(90,1.0,0.0,0.0);
	GLUquadricObj* quadric5;
	quadric5 = gluNewQuadric();
	glColor3f(1.0,0.0,0.0);
	gluQuadricDrawStyle(quadric5, GLU_FILL);
	gluQuadricNormals(quadric5, GLU_SMOOTH);
	gluQuadricOrientation(quadric5, GLU_OUTSIDE);
	gluCylinder(quadric5,0.08,0.08,0.5,10,10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.25,-0.58,0.00);
	glColor3f(0.0,0.0,1.0);
	glutSolidSphere(0.08,10,10);
	glPopMatrix();
	glPopMatrix();



	glPopMatrix();//for the outermost


}

//-----------------------------------------------------------------------------------------------------------------------------
void initScene()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0);


	Image* image = loadBMP("index.bmp");
	_textureId = loadTexture(image);
	delete image;
	Image* image2 = loadBMP("water.bmp");
	_textureId2 = loadTexture(image2);
	delete image2;
	Image* image3 = loadBMP("crate.bmp");
	_textureId3 = loadTexture(image3);
	delete image3;

	Image* image4 = loadBMP("crate2.bmp");
	_textureId4 = loadTexture(image4);
	delete image4;

	Image* image5 = loadBMP("jungle.bmp");
	_textureId5 = loadTexture(image5);
	delete image5;



}




void scenery(float x11,float y11,float z11,float x22,float y22,float z22,float x33,float y33,float z33,float x44,float y44,float z44)
{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId5);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glDisable(GL_NORMALIZE);
	glColor3f(1.0f-nightVar, 1.0f-nightVar, 1.0f-nightVar);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f,0.0f);
	glVertex3f(x11,y11,z11);
	glTexCoord2f(-1.0, 0.0f);
	glVertex3f(x22, y22,z22);

	glTexCoord2f(-1.0f, -1.0f);
	glVertex3f( x33, y33,  z33);

	glTexCoord2f(0.0f, -1.0f);
	glVertex3f( x44, y44,z44);

	glEnd();
	//glDisable(GL_NORMALIZE);
	glDisable(GL_TEXTURE_2D);
}

//-----------------------------------------------------------------------------------------------------------------------------------
void renderScene(void) 
{
	countSound+=1;
	if (flagSound==1 || (flagSound==0 && countSound > 50))
	{
		PlaySound(TEXT("mario2.wav"), NULL,SND_ASYNC);
		flagSound=-1;
	}
	//Enable(GL_SCISSOR_TEST);
	//t ambientColor[]={0.5.0.5.0.5};
	//GLfloat ambientColor[4];
	if(spot==1)
	{
	GLfloat ambientColor[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.2, 0.2, 0.2)
	      	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	}
	else if(spot==0)
	{
	GLfloat ambientColor[] = {1.0f, 1.0f, 1.0f, 1.0f}; //Color (0.2, 0.2, 0.2)
	      	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	}
	                                     
	//LightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	GLfloat position[]={initialX,initialY+10,initialZ,1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	GLfloat diffuse[]={1.0f,1.0f,1.0f,1.0f};
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);


	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,20.0);
	glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,4.0);
	GLfloat spot_direction[] = {0,-1,0};
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);



	//Lighting part taken from VideoTutorialRocks.com

	/*  GLfloat lightColor0[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.5, 0.5)
	    GLfloat lightPos0[] = {9.0f, 5.0f, -17.0f, 1.0f}; //Positioned at (4, 0, 8)
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	    GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = {9.0f, 5.0f, -17.0f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);*/


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, vw,vh);
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
	//glScissor(0, 0, (float)vw , vh);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();
	/*if(firstPersonView==1)
	  {
	  gluLookAt(initialX2,initialY,initialZ,initialX2+lx,initialY+ly,initialZ+lz,0.0,1.0,0.0);
	  }
	  else*/
	/*{

	  gluLookAt(x, y, z,x + lx,y + ly,z + lz,0.0f,1.0f,0.0f);

	  }**/


	float height=0.01f;
	//initialising index 1 for moving tiles
	blockIndex[0][2]=1;blockIndex[1][3]=1;blockIndex[3][4]=1;blockIndex[4][3]=1;blockIndex[5][6]=1;
	blockIndex[6][5]=1;blockIndex[7][6]=1;blockIndex[8][7]=1;blockIndex[9][6]=1,blockIndex[4][9]=1;
	//missing tiles
	blockIndex[1][5]=2; blockIndex[2][4]=2; blockIndex[4][7]=2; blockIndex[5][2]=0; blockIndex[6][3]=0;
	blockIndex[8][3]=2;blockIndex[9][4]=2,blockIndex[6][9]=2;
	//falling block
	blockIndex[3][2]=3;blockIndex[3][7]=3,blockIndex[1][6]=3;;
	// spring blocks
	blockIndex[5][1]=7;blockIndex[7][3]=7;
	//oscillating block
	blockIndex[8][8]=4,blockIndex[2][9]=4,blockIndex[5][4]=4,blockIndex[7][1]=4;
/*	
	
	
	glPushMatrix();
	glTranslatef(var1+1,0.5,var1+1);
	drawBullet();
	glPopMatrix(); 

	glPushMatrix();
	glTranslatef(var2-5,0.5,var2+1);
	drawBullet();
	glPopMatrix();
 */	

	//if( ( abs(var-initialX2) <0.1) && ( abs(var-initialZ2) < 0.1)  && abs(initialY2-(1.5-0.5))<0.1 )
	//	checkgameover3();

	if(bulletsMode==1)
	{
		for(int i=0;i<numBullets;i++)
		{
			glPushMatrix();
			if(i==0)
				glTranslatef(bulletsArr[i].X,0.5,bulletsArr[i].Z);
			else if(i==1)
			{
				bulletsArr[i].X = var1+1;
				bulletsArr[i].Z = var1+1;
				glTranslatef(bulletsArr[i].X,0.5,bulletsArr[i].Z);
			}
			else if(i==2)
			{
				bulletsArr[i].X = var2-5;
				bulletsArr[i].Z = var2+1;
				glTranslatef(bulletsArr[i].X,0.5,bulletsArr[i].Z);
			}
			drawBullet();
			glPopMatrix();

			//if( abs(bulletsArr[i].X-initialX2) < 0.1 && abs(bulletsArr[i].Z-initialZ2) < 0.1 && abs(initialY2-(1.5-0.5))<0.1 )
			//{
			//exit(1);
			//	checkgameover3();
			//}
		}
	}
	drawnewtree(-26,-25);
	drawnewtree(-22,-25);
	drawnewtree(22,-25);
	drawnewtree(26,-25);

	//draw island
	cmz=2;
	int i,j,xx=0,yy=0;
	for(i=2;i>-18;i=i-2)
	{
		yy=0;
		for(j=-10;j<10;j=j+2)
		{
			if(blockIndex[xx][yy]!=2)
			{

				if(blockIndex[xx][yy]==1)height=movingheight;
				else height=0;
				if(tileviewx==yy && tileviewz==xx)
					cmz=height;


				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, _textureId);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glDisable(GL_NORMALIZE);

				if(yy==inx && xx==inz && spot==0)glColor3f(0.0,10.0,0.0);
				else if(yy==inx2 && xx==inz2)glColor3f(10.0,0.0,0.0);
				else
					glColor3f(1.0f, 1.0f, 1.0f);
				glBegin(GL_QUADS);

				glTexCoord2f(1, 0);
				glVertex3f(j, height, i);
				glTexCoord2f(1, 1);
				glVertex3f(j, height, i-2);
				glTexCoord2f(0, 1);
				glVertex3f(j+2, height,i-2);
				glTexCoord2f(5, 5);
				glVertex3f(j+2, height, i);
				glEnd();
				glDisable(GL_TEXTURE_2D);
				if(blockIndex[xx][yy]==3)
				{
					if(blockflag[zcordinate(i)][xcordinate(j)]==1)
						drawcube2(j,i);
					else drawcube(j,i);
				}
				if(blockIndex[xx][yy]==7)drawcube(j,i);
				if(blockIndex[xx][yy]==4)movingcube(j,movingcubeheight,i,4,2);
				if(blockIndex[xx][yy]==6)
				{
					glPushMatrix();
					glTranslatef(j+1,0.5,i-1);
					drawcoin();
					glPopMatrix();
				}
			}//if
			yy++;
		}
		xx++;
	}


	//------------------------------------------------------------------------------------------------------
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,_textureId2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glDisable(GL_NORMALIZE);
	glEnable(GL_BLEND);
	glColor3d(waterRed, waterGreen,waterBlue/*, water_alpha*/);
	glNormal3f(0, 1, 0);

	glBegin(GL_QUADS);
	glTexCoord2f(200 / water_texture_size,
			-water_texture_offset / water_texture_size);
	glVertex3f(-100, -5, -100);
	glTexCoord2f(200 / water_texture_size,
			(200 - water_texture_offset) / water_texture_size);
	glVertex3f(-100, -5, 100);
	glTexCoord2f(0, (200 - water_texture_offset) / water_texture_size);
	glVertex3f(100, -5, 100);
	glTexCoord2f(0, -water_texture_offset / water_texture_size);
	glVertex3f(100, -5, -100);
	glEnd();
	//Note: Idea taken from "http://videotutorialrocks.com"
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);






	scenery(300,100,-400,
			-300,100,-400,
			-300,-50,-400,
			300,-50,-400);


	scenery(300,100,-400,
			300,100,400,
			300,-50,400,
			300,-50,-400);


	scenery(-300,100,-400,
			-300,100,400,
			-300,-50,400,
			-300,-50,-400);




	glPushMatrix();
	if(chancecount<3)
		drawHumanoid();
	if(chancecount2<3 && secondRobot==1)
		drawHumanoid2();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0,0.0,-7);
	glutSolidSphere(0.5,10,10);
	glPopMatrix();
	int sec = timeout - (int)seconds;

	char exp1[20],exp2[20],exp3[20],exp4[10000];
	sprintf(exp1,"%d",score);
	sprintf(exp2,"%d",nocoins);
	sprintf(exp3,"%d",totallife-chancecount);
	sprintf(exp4,"%d",sec);

	//itoa(score,exp,10);
	char str1[100]="Score: ";
	char str2[100]="Coins Collected: ";
	char str3[100]="Life Remaining: ";
	char str4[1000]="Time Remaining : ";
	char str5[1000]="Robot1 Won!! ";
	char str6[1000]="Robot2 Won!! ";	
	strcat(str1,exp1);
	strcat(str2,exp2);
	strcat(str3,exp3);
	strcat(str4,exp4);

	drawBitmapText(str1,-10,6,0);
	drawBitmapText(str2,-10,5.7,0);
	drawBitmapText(str3,-10,5.4,0);
	if(levelOne==1 && displayTime==1)
		drawBitmapText(str4,-2.5,5.7,0);

	if(countExit>0 && countExit<=50)
	{
		if(nocoins>nocoins2)
			drawBitmapText(str5,-2.5,6,0);
		else if(nocoins<nocoins2)
			drawBitmapText(str6,-2.5,6,0);		
	}

	if(levelTwo==1)
	{

	char exp5[20],exp6[20],exp7[20];
	sprintf(exp7,"%d",score2);
	sprintf(exp5,"%d",nocoins2);
	sprintf(exp6,"%d",totallife-chancecount2);
	//sprintf(exp4,"%d",sec);

	//itoa(score,exp,10);
	char str7[100]="Score: ";
	char str5[100]="Coins Collected: ";
	char str6[100]="Life Remaining: ";
	//char str4[1000]="Time : ";
	strcat(str5,exp5);
	strcat(str6,exp6);
	strcat(str7,exp7);
	//strcat(str4,exp4);

	drawBitmapText(str7,5,6,0);
	drawBitmapText(str5,5,5.7,0);
	drawBitmapText(str6,5,5.4,0);
	}

	/*
	   if(emptytile>0 && emptytile<20 && chancecount<3 && sp!=1)
	   {
	   char str[100]="Lost a Life !!!";
	   drawBitmapText2(str,0,5,5);
	   }

	   if(emptytile>0 && emptytile<20 && chancecount==3)
	   {
	   char str[100]="Sorry Game Over !!!";
	   drawBitmapText2(str,0,5,5);
	   }
	   if(emptytile==20 && chancecount==3)exit(0);

	   if(win>0 &&  win < 50 && score==1000)
	   {
	   char str[100]="Congracts , You Won!!!";
	   drawBitmapText2(str,0,5,5);

	   }
	   if (win==50 && score==1000)exit(0);
	//char end[10]="End";
	//drawBitmapText(end,-9,0,2);
	difx=0,dify=0;
	 */


	if(firstPersonView==1)
	{
		firstView();

	}
	else if(top==1)
	{
		topView();
	}
	else if(thirdPersonView==1)
	{
		cout << " teri\n";
		thirdView();
	}
	else if(helicopterView==1)
		helicopter();

	else if(tileView==1)tiledview();
	else if(favourite==1)favouriteView();
	else normalView();
	glFlush();
	glutSwapBuffers();

}

//------------------------------------------------------------------------------------------------------------------------
void firstView() {

	float lx1 = sin((rotateAngle/180)*PI);
	float lz1 = cos((rotateAngle/180)*PI);
	//printf("lx %f lz %f",lx1,lz1);
	//printf("rotateangle %f\n",rotateAngle);
	glLoadIdentity();
	gluLookAt(initialX,initialY,initialZ,initialX+lx1,initialY-0.5,initialZ+lz1,0.0,1.0,0.0);

}

void thirdView()
{

	float lx1 = sin((rotateAngle/180)*PI);
	float lz1 = cos((rotateAngle/180)*PI);
	printf("lx %f lz %f",lx1,lz1);
	glLoadIdentity();
	gluLookAt(initialX-10*lx1,initialY,initialZ-10*lz1,initialX,initialY,initialZ,0.0,1.0,0.0);

}


void helicopter()
{
	if(lookanglechange==1)
	{
		if(mouseX<-10)lx1=-10;
		else if(mouseX>10)lx1=10;
		else lx1=mouseX;
		if(mouseY<0)ly1=0;
		else if(mouseY>0)ly1=0;
		else ly1=mouseY;



		lookanglechange=0;
	}
	if(zoomin==1)
	{
		camz=camz-1;
		zoomin=0;
	}
	if(zoomout==1)
	{
		camz=camz+1;
		zoomout=0;
	}
	glLoadIdentity();
	gluLookAt(/*lx1*/x,y,camz,lx1,ly1,lz,0,1.0,0);


}

//-----------------------------------------------------------------------------------------------------------------------
void normalView() {



	glLoadIdentity();

	gluLookAt(x, y, z,

			x + lx,y + ly,z + lz,

			0.0f,1.0f,0.0f);

}

//-----------------------------------------------------------------------------------------------------------------------
void topView()
{
	glLoadIdentity();
	gluLookAt(0,15,10,0,0,-10,0,1,0);
	//gluLookAt(initialX-5,15,initialZ,initialX,0,initialZ,0,1,0);
}

void favouriteView()
{
	glLoadIdentity();
	gluLookAt(initialX-5,15,initialZ,initialX,0,initialZ,0,1,0);
}

//This function is used to find cordinates of mouse. Taken from a website
void GetOGLPos(int x, int y)
{
	int viewport[4];
	double modelview[16];
	double projection[16];
	float winX, winY, winZ;
	double posX, posY, posZ;
	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	//return CVector3(posX, posY, posZ);
	mouseinX=mouseX,mouseinY=mouseY;
	mouseX=(float)posX;
	mouseY=(float)posY;


	//printf("sam %f %f\n",(float)posX,(float)posY);
}

void passiveMouse(int x,int y)
{
	GetOGLPos(x,y);
}
void pm(int button,int state,int x,int y)
{
	if ((state == GLUT_DOWN) && button == GLUT_LEFT_BUTTON )
	{
		lookanglechange=1;
	}
	if(button==3)
	{
		zoomin=1;
		zoomout=0;
	}
	if(button==4)
	{
		zoomout=1;
		zoomin=0;
	}

}

void tiledview()
{

	float cmx=2*float(tileviewx)-10;
	float cmy=2-2*float(tileviewz);
	//cout << "cm" << cmz << endl;
	glLoadIdentity();
	gluLookAt(cmx,cmz,cmy+1.5,initialX,initialY+1,initialZ,0,1,0);
}

//---------------------------------------------------------------------------------------------------------------------
void handleKeypress1(unsigned char key, int x, int y) {

	if (key == 27) {

		exit(0);     // escape key is pressed
	}

	//	if(staticheight>=0)
	//	{
	if((key==106 || key==32))
	{
		jump=1;
		PlaySound(TEXT("jump.wav"), NULL,SND_ASYNC);
		flagSound=0;
		countSound=0;
	}
	if(key==55)
	{
		jump2=1;
		PlaySound(TEXT("jump.wav"), NULL,SND_ASYNC);
		flagSound=0;
		countSound=0;
	}
	//	}
	if(key==97)
	{
		firstPersonView=(firstPersonView+1)%2;
	}

	if(key==116)
	{
		top=(top+1)%2;
	}
	if(key==115)
	{
		thirdPersonView=(thirdPersonView+1)%2;
	}
	if(key==104)helicopterView=(helicopterView+1)%2;
	if(key==100)
	{
		tileView=(tileView+1)%2;
	}
	if(tileView==1)
	{

		if(key==56)tileviewz++;
		else if(key==50)tileviewz--;
		else if(key==52)tileviewx--;
		else if(key==54)tileviewx++;
	}
	if(key==102)
	{
		favourite=(favourite+1)%2;
	}

	// navigation for 2nd robot

	// for left key
	if((key== 52) &&((blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==3 && moveonblock2==1) ||( blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=3)) && staticheight>=0)
	{
		rotateAngle2+=90;
	}

	else if(key==54 &&((blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]==3 && moveonblock2==1) ||( blockIndex[zcordinate(initialZ2)][xcordinate(initialX2)]!=3))&& staticheight>=0 )
	{
		rotateAngle2-=90;
	}
	else if(key== 56 && staticheight>=0)
	{
		walkUp2=1;
	}

	else if(key==50 && staticheight>=0)
	{
		walkDown2=1;
	}
	if(key =='u')
	{
		automatic1=(automatic1+1)%2;
		automatic2=(automatic2+1)%2;
	}
	if(key=='v')
	{
		spot=(spot+1)%2;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------
void handleKeypress2(int key, int x, int y)
{
	if((key== GLUT_KEY_LEFT) &&((blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==3 && moveonblock==1) ||( blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=3)) && staticheight>=0)
	{
		rotateAngle+=90;

	}

	else if(key==GLUT_KEY_RIGHT &&((blockIndex[zcordinate(initialZ)][xcordinate(initialX)]==3 && moveonblock==1) ||( blockIndex[zcordinate(initialZ)][xcordinate(initialX)]!=3))&& staticheight>=0 )
	{
		rotateAngle-=90;
	}
	else if(key== GLUT_KEY_UP && staticheight>=0)
	{
		walkUp=1;
	}

	else if(key==GLUT_KEY_DOWN && staticheight>=0)
	{
		walkDown=1;
	}

}




//------------------------------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
	//PlaySound(TEXT("bgm2.wav"), NULL,SND_ASYNC|SND_LOOP);
	time(&startTime);
	bulletsArr[0].X=-10;	bulletsArr[0].Z=-18;	
	bulletsArr[1].X=-10;	bulletsArr[1].Z=-18;	
	bulletsArr[2].X=-10;	bulletsArr[2].Z=-18;	
	blockIndex[0][9]=6;blockIndex[2][5]=6;blockIndex[2][2]=6;blockIndex[3][8]=6;blockIndex[4][5]=6;
	blockIndex[5][3]=6;blockIndex[6][7]=6;blockIndex[7][4]=6;blockIndex[7][7]=6;blockIndex[0][5]=6;


	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowPosition(100,100);

	glutInitWindowSize(640,360);

	glutCreateWindow("THE FUN BEGINS....");
	initScene();
	lookanglechange=0;
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutMouseFunc(pm);
	glutPassiveMotionFunc(passiveMouse);
	glutReshapeFunc(changeSize);
	glutTimerFunc(10, update, 0);
	glutMainLoop();
	return(0);
}

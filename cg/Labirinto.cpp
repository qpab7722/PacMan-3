#include "Labirinto.h"
#include <stdio.h>
#include <GL/glut.h>

#define IMAGE_ROWS 16      // Texture image rows and columns
#define IMAGE_COLS 16

// Texture
GLubyte imageData[IMAGE_ROWS][IMAGE_COLS][3]; // Texture image data

GLfloat _noMat[] = { 0.0, 0.0, 0.0, 1.0 };

//materiais chao
//GLfloat _matAmbient[] = { 0.15f, 0.15f, 0.15f, 1.0 };
GLfloat _matChaoAmbientGray[] = { 0.55f, 0.55f, 0.55f, 1.0 };
GLfloat _matChaoDiffuseGray[] = { 0.10, 0.10, 0.10, 1.0 };

//materiais paredes
GLfloat _matAmbientBlue[] = { 0., 0., .2, 1.};
GLfloat _matDiffuseBlue[] = { 0.160784f, 0.160784f, 1.0f, 1.0 };

//materiais bolas normal
GLfloat _matSphereDiffuseGray[] = { 0.90, 0.90, 0.90, 1.0 };
GLfloat _matSphereSpecularGray[] = { 1.0, 1.0, 1.0, 1.0 };

//materiais bolas bouus
GLfloat _sphereDiffuse[] = { .7, .5, .1, 1.};
GLfloat _sphereSpecular[] = { 1., .95, .8, 1.};

GLfloat _noShininess[] = { 0.0 };
GLfloat _lowShininess[] = { 5.0 };
GLfloat _medShininess[] = { 20.0 };
GLfloat _highShininess[] = { 100.0 };


Labirinto::Labirinto(){
	// Load pattern into image data array
	loadTextureImageData();   
	int i=0, j=0, aux=0;
	FILE *mazefile;
	_numbolas=66;

	mazefile = fopen("defaultmaze.dat", "r");

	if(!mazefile){
		printf("Error: Missing maze file!\n");
		printf("       Maze not loaded!\n");
		return;
	}

	for(i = 0; i < 12; i++){
		for(j=0; j<12; j++){
			fscanf(mazefile,"%d", &aux);
			_lab[i][j] = aux;
		}
	}

	fclose(mazefile);
};

bool Labirinto::paredeQ(int i, int j){ // verifica se ha uma parede em (i,j)
	int k, l;
	if(_lab[j][i]==2)
		return true;
	return false;
}

bool Labirinto::bolaQ(int i, int j){ // verifica se ha uma bola em (i,j)
	int k, l;
	if(_lab[j][i]==1)
		return true;
	return false;
}

bool Labirinto::bolaBonusQ(int i, int j){ // verifica se ha uma bola bonus em (i,j)
	int k, l;
	if(_lab[j][i]==3)
		return true;
	return false;
}

void Labirinto::comeBola(int i, int j){
	if(_lab[j][i]==1 || _lab[j][i]==3) {_lab[j][i]=0; _numbolas-=1;};
};

void Labirinto::changeLabirinto(int num){
	if(num==1){//mudar para labirinto 1
		setLab("defaultmaze.dat");
		_numbolas=66;
	};
	if(num==2){//mudar para labirinto 2
		setLab("maze2.dat");
		_numbolas=63;
	};
	if(num==3){//mudar para labirinto 3
		setLab("maze3.dat");
		_numbolas=65;
	};
	//printf("o num de bolas são: %d", _numbolas);
}

void Labirinto::setLab(char *mazefilename){
	int i=0, j=0, aux=0;
	FILE *mazefile;
	//_numbolas=0;

	mazefile = fopen(mazefilename, "r");

	if(!mazefile){
		printf("Error: Missing maze file!\n");
		printf("       Maze not changed!\n");
		return;
	}
	while(i<12){
		j=0;
		while(j<12){
			fscanf(mazefile,"%d", &aux);
			_lab[i][j] = aux;
			//if(aux==1 || aux==3) _numbolas+=1;
			j++;
		}
		i++;
	}
	fclose(mazefile);
};

void Labirinto::drawChao() {
	//chao
	glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();

	glNormal3f(0.0f, 0.0f, 1.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, _matChaoAmbientGray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _matChaoDiffuseGray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, _noMat);
	glMaterialfv(GL_FRONT, GL_SHININESS, _noShininess);

	glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
	glVertex3f(-6.0f, -6.0f, -0.5f);
	glVertex3f(6.0f, -6.0f, -0.5f);
	glVertex3f(6.0f, 6.0f, -0.5f);
	glVertex3f(-6.0f, 6.0f, -0.5f);
	glEnd();
	glPopMatrix();
}

void Labirinto::draw(){
	//drawChao();

	double x_max = 6.0f;
	for(int i = -6.0f; i<x_max; i++){
		drawPolyForChao(-6.0f, 6.0f, i);
	}

	int i=0;
	int j;
	glPushMatrix();
	glTranslatef(5.5, 6.5, 0.0);
	while(i<12){
		j=0;
		glTranslatef(-12.0, -1.0, 0.0);
		while(j<12){ // 0 = nao ha nada logo nao aparece
			glTranslatef(1.0, 0.0, 0.0);
			if(_lab[i][j]==2) { //desenhar as paredes
					glColor3f(0.137255f, 0.556863f, 0.137255f); // 2 = existe uma parede
					glPushMatrix();

					glMaterialfv(GL_FRONT, GL_AMBIENT, _matAmbientBlue);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, _matDiffuseBlue);
				    glMaterialfv(GL_FRONT, GL_SPECULAR, _noMat);
				    glMaterialfv(GL_FRONT, GL_SHININESS, _noShininess);


					glScalef(1.0f,1.0f,0.4f);
					glutSolidCube(1.0f);
					glPopMatrix();
				}
			else {
				if(_lab[i][j]==1) { //desenhar as bolas
				glColor3f(1.0f, 1.0f, 1.0f); // 1 = existe uma bola
				glPushMatrix();

				glMaterialfv(GL_FRONT, GL_AMBIENT, _noMat);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _matSphereDiffuseGray);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _matSphereSpecularGray);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, _highShininess);				

				glTranslated(0.0f,0.0f,0.10f);
				glutSolidSphere(0.15,20,20);
				glPopMatrix();
				}
				 
				else {
					if(_lab[i][j]==3){ //desenhar as bolas bonus
						glColor3f(0.5f, 0.5f, 0.5f); // 3 = existe uma bola bonus
						glPushMatrix();

						glMaterialfv(GL_FRONT, GL_AMBIENT, _noMat);
						glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _sphereDiffuse);
						glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _sphereSpecular);
						glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, _medShininess);

						glTranslated(0.0f,0.0f,0.18f);
						glutSolidSphere(0.25,20,20);
						glPopMatrix();
					}
				}
			}
			j++;
		}
		i++;
	}
	glTranslatef(-5.5, 5.5, 0.0);
	glPopMatrix();
}


void Labirinto::drawPolyForChao(float y_min, float y_max,  float x_min){ 
	
	// Create texture from image data
	glTexImage2D(GL_TEXTURE_2D, 0, 4, IMAGE_COLS, IMAGE_ROWS, 0, GL_RGB, 
         GL_UNSIGNED_BYTE, imageData);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   
	glEnable(GL_TEXTURE_2D);  // Enable 2D texture 

	//top side
	glColor3f(0.0f, 0.0f, 1.0f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, _matChaoAmbientGray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _matChaoDiffuseGray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, _noMat);
	glMaterialfv(GL_FRONT, GL_SHININESS, _noShininess);

	for (int i=y_min; i<y_max; i++){
		glBegin(GL_QUAD_STRIP);
			glTexCoord2f(0.0f, 0.0f);  glVertex3f( x_min, i, -0.5f);   
			glTexCoord2f(0.0f, 1.0f);  glVertex3f( x_min, i+1, -0.5f); 	
			glTexCoord2f(1.0f, 0.0f); glVertex3f( x_min+1, i, -0.5f); 
			glTexCoord2f(1.0f, 1.0f); glVertex3f( x_min+1, i+1, -0.5f);  
		glEnd();
	}

	//right side	
	glColor3f(0.0f, 0.0f, 1.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, _matChaoAmbientGray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _matChaoDiffuseGray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, _noMat);
	glMaterialfv(GL_FRONT, GL_SHININESS, _noShininess);
	
	for (int i=y_min; i<y_max; i++){	
		glBegin(GL_QUAD_STRIP);
			glTexCoord2f(1.0f, 0.0f);  glVertex3f( x_min+1, i, -1.5f);   
			glTexCoord2f(1.0f, 1.0f);  glVertex3f( x_min+1, i+1, -1.5f); 	
			glTexCoord2f(0.0f, 0.0f); glVertex3f( x_min+1, i, -0.5f); 
			glTexCoord2f(0.0f, 1.0f);  glVertex3f( x_min+1, i+1, -0.5f);  
		glEnd();	
	}

	//left side
	glColor3f(0.0f, 0.0f, 1.0f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, _matChaoAmbientGray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _matChaoDiffuseGray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, _noMat);
	glMaterialfv(GL_FRONT, GL_SHININESS, _noShininess);
	for (int i=y_min; i<y_max; i++){	
		glBegin(GL_QUAD_STRIP);
			glTexCoord2f(0.0f, 0.0f);  glVertex3f( x_min, i, -1.5f);   
			glTexCoord2f(0.0f, 1.0f);  glVertex3f( x_min, i+1, -1.5f); 	
			glTexCoord2f(1.0f, 0.0f);  glVertex3f( x_min, i, -0.5f); 
			glTexCoord2f(1.0f, 1.0f); glVertex3f( x_min, i+1, -0.5f);  
		glEnd();

	}

	//front side
	glColor3f(0.0f, 0.0f, 1.0f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, _matChaoAmbientGray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _matChaoDiffuseGray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, _noMat);
	glMaterialfv(GL_FRONT, GL_SHININESS, _noShininess);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( x_min, y_min, -1.5f);   
		glTexCoord2f(0.0f, 0.0f);  glVertex3f( x_min, y_min, -0.5f); 	
		glTexCoord2f(1.0f, 0.0f);  glVertex3f( x_min+1, y_min, -0.5f); 
		glTexCoord2f(1.0f, 1.0f);  glVertex3f( x_min+1, y_min, -1.5f);  
	glEnd();

	//backside
	glColor3f(0.0f, 0.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, _matChaoAmbientGray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _matChaoDiffuseGray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, _noMat);
	glMaterialfv(GL_FRONT, GL_SHININESS, _noShininess);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( x_min, y_max, -1.5f);   
		glTexCoord2f(0.0f, 1.0f); glVertex3f( x_min, y_max, -0.5f); 	
		glTexCoord2f(1.0f, 1.0f);  glVertex3f( x_min+1, y_max, -0.5f); 
		glTexCoord2f(1.0f, 0.0f);  glVertex3f( x_min+1, y_max, -1.5f);  

	glEnd();
	//glDisable(GL_TEXTURE_2D);  // Disable 2D texture 

}
// Load the imageData array with checkerboad pattern
void Labirinto::loadTextureImageData() {
   int value;
   for (int row = 0; row < IMAGE_ROWS; row++) {
      for (int col = 0; col < IMAGE_COLS; col++) {
         // Each cell is 8x8, value is 0 or 255 (black or white)
        value = (((row & 0x8) == 0) ^ ((col & 0x8) == 0)) * 255;
		imageData[row][col][0] = (GLubyte)value;
		imageData[row][col][1] = (GLubyte)value;
		imageData[row][col][2] = (GLubyte)value;
		imageData[row][col][3] = 1;
	}
   }
}

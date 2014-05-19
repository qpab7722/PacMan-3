#pragma once
#include <iostream>
#include <fstream>

class Labirinto{
private: int _lab[12][12];
		 int _numbolas;
public: Labirinto();
		bool paredeQ(int i, int j);
		bool bolaQ(int i, int j);
		bool bolaBonusQ(int i, int j);
		void comeBola(int i, int j);
		//sets
		void setLab(char *mazefilename);
		void setLabIJ(int val, int i, int j){_lab[i][j]=val;};
		//gets
		int getLabIJ(int i, int j){return _lab[i][j];};
		int getNumBolas(){return _numbolas;};
		//desenho
		void draw();
		void changeLabirinto(int num);
private: 
		void drawChao();
		void drawPolyForChao(float y_min, float y_max, float current_x);
		void loadTextureImageData();

};


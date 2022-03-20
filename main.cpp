#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h> // library de opengl
#include <iostream>

#include <ctime>     // pour la fonction rand
#include <time.h>
#include <math.h>
#include <string>
#include <windows.h>


#include <cstdio>

using namespace std;


// Défini les dimentions de la grille de jeu

#define COLONNE 19 //definition de la colonne
#define LIGNE 18 // definition de ligne

int gridX; // definition de la grille celon l'axes de X
int gridY ; // definition de la grille celon l'axes de Y

//Eléments nécessaire au déplacement du pacman
#define NONE 4
#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

#define WIDTHH 1
#define HEIGHTT 1

//Position de départ
int posX = 9; // PosX pisition initial celon X
int posY = 7; // PosX pisition initial celon Y



//Ce line code comporte la direction du pacman et score atteind , le nombre de vie du pacman et ca vitesse de deplacement

int pacman_Direction = NONE ;
int score = 0; // Score de jeux
int vie=3; //  Vie depart
int vitesse=1; // la vitesse de deplacment du pacman et du fontom


//position du fontom
//Elements necessaires pour les fantomes
int posXF1 = 12.0;
int posYF1 = 4.0;



//direction du fantom

int fontom_Directionblinky = LEFT;


//Grille standard du jeu pacman: 0 ou il peut se deplacer, 1 ou il y à des murs, 2 ou il ya  rien du tout , 3 pour les portes blanch et 6 pour la pacGomme

int grille [18][19] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                        {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                        {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
                        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                        {1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1},
                        {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
                        {1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1},
                        {2,2,2,1,0,1,0,0,0,0,0,0,0,1,0,1,2,2,2},
                        {1,1,1,1,0,1,0,1,1,3,1,1,0,1,0,1,1,1,1},
                        {3,0,0,0,0,0,0,1,2,2,2,1,0,0,0,0,0,0,3},
                        {1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1},
                        {2,2,2,1,0,1,0,0,0,0,0,0,0,1,0,1,2,2,2},
                        {1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1},
                        {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                        {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
                        {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
                        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                        {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
};

//une variable pour stocker le temp ecouler du debut du jeu a la fin
int chronometre = 0;

////////////////////////// Fonctions pour la grille ////////////////////////////////////////

void unite(int x, int y){

    if (grille [y][x] == 1){
        glLineWidth(5.0);
        glColor3f(0.15,0.1,0.8);
    }
    else if (grille [y][x] == 3){
        glLineWidth(5.0);
        glColor3f(1.0,1.0,1.0);
    }
    else{
        glLineWidth(0.1);
        glColor3f(0.0,0.0,0.0);
    }

    //glLoadIdentity();
    glBegin(GL_QUADS); //Figure fermé comme une boucle (loop), les points sont espacés d'une unité
        glVertex2f(x,y); //2f: 2 dimensions
        glVertex2f(x+1,y);
        glVertex2f(x+1,y+1); //Sens trigo avec point de départ à l'origine (en bas à gauche)
        glVertex2f(x,y+1);
    glEnd();
    return;

}

void initialisation_Grid(int x, int y){

    gridX = x;
    gridY = y;

}


void dessin_Grid (){
	// la fonction de la

    for (int x=0; x<gridX; x++){
        for (int y=0; y<gridY; y++){

            unite (x,y);

        }
    }
}

////////////////////////// Fonctions graphiques: PACMAN et autres formes necessaires ///////////////////



void dessin_Pacman(float cx, float cy, float r, int num_segments){
	//fonction pout trace le pacman du forme de cercle
    glLineWidth(10.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
    glLineWidth(1.0);
}



void dessin_Fantoms(float cx, float cy,float r, int num_segments){
	//fonction pout trace le fantom en forme de cercle
    glLineWidth(10.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
    glLineWidth(1.0);
}


/////////////////////////// Fonctions pour la nourriture ///////////////////////////////////////


void DrawALLFood(float cx, float cy, float r, int num_segments){
	//cette fonction dessine la nourriture en forme de petit cerle de couleur blanc
    glLineWidth(5.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calcule de la composonte x
        float y = r * sinf(theta);//calcule de la composonte y
        glVertex2f(x + cx, y + cy);//sortir vertex
    }
    glEnd();
    glLineWidth(1.0);
	//cette cherche dans la grille les casse de egal a 0 et ajoute de la nourriture et si la pacman passe la dessus elle retire la nourriture
}



void food(int foodX, int foodY){
	// FoodX represente la position du food celon l'axes X
	// FoodX represente la position du food celon l'axes Y
    glLineWidth(1.0);
    if (grille [foodY][foodX] == 0 )
	//Position du food dans la grille
	{
        glColor3f(1.0,1.0,1.0); // couleur du food dans le grille
    //dessin du food dans la grille
        DrawALLFood(foodX+0.5, foodY+0.5, 0.1, 2);
    }
    // pacman mange le foot puis obtien 10 points deplus dans le score
    if(posX==foodX && posY==foodY){
        if(grille [foodY][foodX] != 4){
        grille [foodY][foodX] = 4;
        score = score + 10;
		//cette fonction fait parcourir la grille puis donne la resultat au fonction food
        }
    }
}

// fonction permet dessin la food
void dessin_Food(){

    for (int foodX=0; foodX<gridX; foodX++){
        for (int foodY=0; foodY<gridY; foodY++){

            food (foodX,foodY);

        }
    }
}


//////////////////////////////// Deplacement du pacman ///////////////////////////////////////////



void Appel_sur_le_clavier(int key,int,int){
	// cette fonction est faite pour lire le touche de l utilisateur sur le claviers .elle est appelle par glutSpecialFunc()
	//Les deux int correspondent à la position de la souris: on en à pas besoin pour l'instant
    switch(key)
    {
    case GLUT_KEY_UP: //Touche haut sur le clavier
        if (grille [posY-1][posX] == 0 || grille [posY-1][posX] == 4 || grille [posY-1][posX] == 6 ) //Pour chaque cas, je verifie que la position dans laquelle l'utilisateur veut aller est possible en testant la position +1 dans la grille.
            pacman_Direction = UP;            //Cela evite les arrets non voulu du pacman.
        break;
    case GLUT_KEY_DOWN: //touche bas sur le clavier
        if (grille [posY+1][posX] == 0 || grille [posY+1][posX] == 4 || grille [posY+1][posX] == 6)
            pacman_Direction = DOWN;
        break;
    case GLUT_KEY_RIGHT: //Touche droite sur le clavier
        if (grille [posY][posX+1] == 0 || grille [posY][posX+1] == 4 || grille [posY][posX+1] == 6)
            pacman_Direction = RIGHT;
        break;
    case GLUT_KEY_LEFT: //Touche gauche sur le clavier
        if (grille [posY][posX-1] == 0 || grille [posY][posX-1] == 4 || grille [posY][posX-1] == 6)
            pacman_Direction = LEFT;
        break;
    case GLUT_KEY_END: //Touche pour echap le jeu
        exit(0); //Ferme le programme
        break;
    }
}



void Mouvement_Pacman(){
	//cette fonction donne de mouvement au pacman avec un evitement de mur puis dessine le nouveaux position du pacman celon l'utilisateur ou le joueur
    switch(pacman_Direction)
    {
    case UP:
        if (grille [posY-1][posX] == 0 || grille [posY-1][posX] == 4 || grille [posY-1][posX] == 6 ) //Pour chaque cas, je verifie que la position dans laquelle l'utilisateur veut aller est possible en testant la position +1 dans la grille.
            posY-=vitesse;
        break;
    case DOWN:
        if (grille [posY+1][posX] == 0 || grille [posY+1][posX] == 4 || grille [posY+1][posX] == 6)
            posY+=vitesse;
        break;
    case RIGHT:
        if (grille [posY][posX+1] == 0 || grille [posY][posX+1] == 4 || grille [posY][posX+1] == 6)
            posX+=vitesse;
        break;
    case LEFT:
        if (grille [posY][posX-1] == 0 || grille [posY][posX-1] == 4 || grille [posY][posX-1] == 6)
            posX-=vitesse;
        break;
    }

    glColor3f(1.0,1.0,0.0);
    dessin_Pacman(posX+0.5, posY+0.5, 0.5, 10.0);
}



///////////////////////////////////////////Fonction pour le fantome ///////////////////////////////////////////



void aleatoire (){
	//cette fonction est faite pour trouver de direction aleatoire ,normalement il ya une algo di determiner me direction
    //initialise le générateur de nombre aléatoire pour le fantoms
    int alea1;
    alea1 = rand() % 4; //Genere un nombre aléatoire entre 1 et 3 en utilisant l'operaeur modulo

    switch (alea1){
        case 0:
            fontom_Directionblinky = UP; // direction fontom vers le haut
            break;
        case 1:
            fontom_Directionblinky = DOWN; // direction fontom vers le bas
            break;
        case 2:
            fontom_Directionblinky = RIGHT; // direction fontom vers le droit
            break;
        case 3:
            fontom_Directionblinky = LEFT; // direction fontom vers le gauche
            break;
    }

}

void Mouvement_Fantome(){
	//cette fonction est dedie au mouvement aleatoir du fantom avec un evitement du collisition avec le mur
    switch(fontom_Directionblinky){
    case UP:
        if (grille [int(posYF1-1)][int(posXF1)] == 0 || grille [int(posYF1-1)][posXF1] == 4 ||  grille [posYF1-1][posXF1] == 6) //Je verifie que la case suivante est accessible avant d'incrémenter. Si le deplacement n'est pas possible, Alors je ne fais rien et il continue dans sa direction
            posYF1--;
        else
            aleatoire();
        break;
    case DOWN:
        if (grille [posYF1+1][posXF1] == 0 || grille [posYF1+1][posXF1] == 4 || grille [posYF1+1][posXF1] == 6)
            posYF1++;
        else
            aleatoire();
        break;
    case RIGHT:
        if (grille [posYF1][posXF1+1] == 0 || grille [posYF1][posXF1+1] == 4 || grille [posYF1][posXF1+1] == 6)
            posXF1++;
        else
            aleatoire();
        break;
    case LEFT:
        if (grille [posYF1][posXF1-1] == 0 || grille [posYF1][posXF1-1] == 4 || grille [posYF1][posXF1-1] == 6)
            posXF1--;
        else
            aleatoire();
        break;
    }
    //dessin du grille bleu
    glColor3f(0.7, 0.9, 0.95); // couleur du fontom
    dessin_Fantoms(posXF1+0.5, posYF1+0.5, 0.4, 10.0);// position initial du fontom

}

//////////// Fonction pour le chrono /////////////////////

void chrono(int){
	//addition du temps de initial +1 seconde " conpte a rebour du jeux " .elle est appele regulierement par glutTimerFunc()
    chronometre ++;
    glutTimerFunc(1000,chrono,0);
}



void text(){


    char text[32];
    sprintf(text, "score:%d  vie:%d  temps:%d", score,vie,chronometre);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3f( 4 , 17.5,0 );
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
		  }



void Pacman_Affichage() {

	/*
		cette est la fonction de rendering .elle est appelle regulierement par glutDisplayFunc().
		Elle sert a appelle toutes les fonction de dessin et un peu pres la foncrion principale.elle gere aussi l'evolution du pacman dans le jeu et a l arret
		du jeu quand le pacman qu'ont on gagne ou perd.
	*/

    glClearColor(0.0,0.0,0.0,1.0); //RVB et Alpha: ici j'initialise une fenetre noir (0 RVB). Intensité de la couleur comprise entre 0 et 1
    glClear(GL_COLOR_BUFFER_BIT); //Nettoi les buffer avec la couleur donnée dans la fonction init (GL CLEAR COLOR).
    char msg [40];
    //detection pacman si il est en collition avec le fontom ou pas
    if ((posX == posXF1 && posY == posYF1)){
         posX = 9; //Position de départ celon X
         posY = 7; //Position de départ celon Y
        if(vie>0) vie--;
        MessageBox(NULL,"le fantome vous a manger vous perdez une vie","INFO",0);
        	// ce ci seras affiche en cas ou si vous perde un points de vie
        if(vie<=0)
        {
        sprintf(msg,"vous ete mort avec un temps de %d seconde et un score de %d",chronometre,score);
		// ce ci seras affiche en cas si vous perdu tput aux points de vie

        MessageBox(NULL, msg, "DEFAITE", MB_OK); // Affiche sur un box le mots defaite
        exit(0);
        }
    }
    if(score>=1420){
        sprintf(msg,"vous avez gagne avec un temps de %d seconde et un score de %d",chronometre,score);
        	// ce ci seras affiche si vous avez gagne
        MessageBox(NULL, msg, "VICTOIRE", MB_OK);
        exit(0);
    }
    dessin_Grid(); //Dessine la grille
    Mouvement_Pacman(); //fonction lie au mouvement du pacman
    dessin_Food();   //dessine le nourriture
    Mouvement_Fantome(); //fonction lie au mouvement du fontom
    text(); // fonction de message texte
    glutSwapBuffers(); //Permet de faire tourner les buffers une fois qu'ils ont été dessiné.
}


void Pacman_Redimensement(int w, int h) {
	//Cette fonction sert a redimensioner de la pacman en cas si la fenetre subit changement de taille.
	//Longueur w et hauteur h
    glViewport(0, 0, w, h);
	//Défini l'aire de la fenetre: l'origine se situe en haut à gauche et comme pour les maths: x en abscice et y en ordonné
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); //realisation de la camera
    gluOrtho2D(0.0,(double)COLONNE,(double)LIGNE,0.0); //Origine en haut a gauche
}



void timer_callback(int){
	//cette fonction est appelle regulierement par glutTimerFunc().elle sert reactualiser tout les 0.09 seconde
    glutPostRedisplay();
    glutTimerFunc(70,timer_callback,0); //Permet de donner la vitesse de défilement des buffers
}


///////////////////////////////////////// Main /////////////////////////////////////////////


int main(int argc, char **argv){
	// fonction principale
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );//Mode d'affichage: couleur RVB, 2 tampons
    glutInitWindowPosition(300, 90); //Initialise la position de la fenetre sur l'écran
    glutInitWindowSize(550,700); //Initialise la taille de la fenetre
    glutCreateWindow("PACMAN"); //Crée et nomme une fenetre

    glutDisplayFunc(Pacman_Affichage); //Fonction d'affichage

    glutReshapeFunc(Pacman_Redimensement); //Fonction de redimentionnement

    glutTimerFunc(0,timer_callback,0); // boucle d'animation

    glutTimerFunc(1000,chrono,0); // la fonction du temps

    glutSpecialFunc(Appel_sur_le_clavier); //Fonction d'affectation des touches du clavier

    initialisation_Grid(COLONNE, LIGNE); // appel de la fonction d'initialisation de la grille

    glutMainLoop(); // la fonction du mainloop : la boucle qui tourne afin de joue au jeux

    return 0;
}

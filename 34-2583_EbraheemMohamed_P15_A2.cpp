#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <math.h>
#include <stdio.h>

//<<Global Variables>>
float cup = 0.0f;
float foodHolderY = 0.0f;
float foodHolderAngle = 0.0f;
float cupAngle = 0.0f;
float candleAngle = 0.0f;
float chandelierAngle = 0.0f;
float passX = 0.0f;
float flameY = 0.0f;
float passY = 0.0f;
float scaleY = 1.0f;
float scaleX = 1.0f;
float scaleXC = 1.0f;//C stands for Chandelier scaling
float chandelierCounter = 8.0f;
float chandelierX = 0.0f;
float chandelierY = 0.0f;
float chandelierZ = 0.0f;
float foodHolderX = 0.0f;
float foodHolderY2 = 0.0f;
float foodHolderZ = 0.0f;
float foodHolderCounter = 3.0f;
float bottleHShift = 0.0f;
float bottle = 0.0f;
float angleCandleX = 0.0f;
float candlesX = 0.0f;
float candlesY = 0.0f;
float candlesZ = 0.0f;
float candlesCounter = 3.0f;
float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 9.0f;
float alpha = 0.0f;
float rotateX = 0.0f;
float rotateZ = 0.0f;
float BackVanish = 0.0f;
bool candlesSpiral = false;
bool angleCandleXIncrease = true;
bool rotateCandle = false;
bool candleComplex = false;
bool flameIncrease = true;
bool bottleBezierTurn = false;
bool bottlePositive = true;
bool foodHSpilarIncrease= true;
bool candlesSpiralIncrease = true;
bool translateUpFood = true;
bool foodHolderSpilarTurn = false;
bool foodHolderAngleTurn = false;
bool chandelierBackToOrigin = true;
bool foodHolderAngleIncrease = true;
bool trivialChandelier = false;
bool chandelierScal = true;
bool chandelierDown = true;
bool chandelierUpperLevel = false;
bool rotateCup = false;
bool cupAnglePos = true;
bool candleAngleIncrease = true;
bool chandelierAngleIncrease = true;
bool cupRight = true;
bool scalingDirectionY = true;
bool swap = false;
bool scalingDirectionZ = true;
bool bottleRight = true;
bool ca = false;
bool t = false;
bool b = false;
bool cu = false;
bool ch = false;
bool fh = false;
bool playAll = false;
bool rotateScene = false;
bool removeFront = true;
bool removeRight = false;
bool removeLeft = false;
bool removeBack = false;
bool removeMiddle = false;
int cupP0[2]= {125,47};
int cupP1[2]={0,544};
int cupP2[2] = {498,30};
int cupP3[2] = {685,46};
int cupShift[2] = {0, 0};
int bottleP0[2]= {241, 4};
int bottleP1[2]={32, 184};
int bottleP2[2] = {424, 206};
int bottleP3[2] = {433, 4};
int bottleShift[2] = {0, 0};
//<<Declaration of the methods used>>
void Anim();
void drawWholeCandle();
void handleCamera();
void handleCup();
void drawBottle();
void handleFoodHolder();
void drawTeaPot(double);
void handleCandle();
void handleTeaPotDeformation();
void drawCandleBase();
void drawCandleSides();
void drawCup();
void bezier(int);
void handleCandleComplexAnimation();
void drawChandelier();
void drawFoodHolder();
void drawRightHalfCircle(float);

void drawUpperCandle();
void handleBottle();
void handleChandelier();

/*
-- The Command to run the file:
g++ 34-2583_EbraheemMohamed_P15_A2.cpp  -lglut -lGL -lGLU -lGLEW  -o assignment2 && ./assignment2
*/

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*void glOrtho(
	 GLdouble  Left, 
     GLdouble  Right, 
     GLdouble  Bottom, 
     GLdouble  Top, 
     GLdouble  Near,  
     GLdouble  Far)*/
	glOrtho(-1000.0, 1000.0, -1000.0, 1000.0, -750.0, 1000.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//cameraZ+rotateZ
	if(rotateScene)
	{
		gluLookAt(rotateX, cameraY+passY, rotateZ , 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}
	else{
		gluLookAt(cameraX+rotateX, cameraY+passY, 2.0f, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		
	}
}

void key(unsigned char k, int x, int y)//keyboard function, takes 3 parameters
// k is the key pressed from the keyboard
// x and y are mouse postion when the key was pressed.
{
	if (k == 'a' && !playAll)//if the letter a is pressed, then the teapot will be animated
		t = !t;
	if (k == 's' && !playAll)//if the letter s is pressed, then the chandelier will be animated
		ch = !ch;
	if (k == 'd' && !playAll)//if the letter d is pressed, then the candles will be animated
		ca = !ca;
	if (k == 'f' && !playAll)//if the letter f is pressed, then the bottle will be animated
		b = !b;
	if (k == 'g' && !playAll)//if the letter g is pressed, then the food-holder will be animated
		fh = !fh;
	if (k == 'h' && !playAll)//if the letter h is pressed, then the cup will be animated
		cu = !cu;
	if (k == 'p')//if the letter h is pressed, then the cup will be animated
		{
			playAll = !playAll;
			t = false;
			ch = false;
			ca = false;
			b = false;
			fh = false;
			cu = false;
		}
	if(k == 'r'){
		if(rotateScene)
		{
			alpha = 0.0f;
			rotateX = 0.0f;
			rotateZ = 0.0f;
			removeBack = false;
			removeFront = true;
			removeRight = false;
			removeLeft = false;
		}
		rotateScene = ! rotateScene;
	}
	if(k == 'm'){
		removeMiddle = ! removeMiddle;
	}
	glutPostRedisplay();//redisplay to update the screen with the changes
}



void Display(void){
	// Setup light
	//SetupLights();
	//set the camera
	setupCamera();

	//start drawing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Here we start drawing after ClearColor
	//Teapot
	glPushMatrix();
	glTranslatef(500.0f, -650.0f, 0.0f);
	glScalef(scaleX, scaleY, 1.0f);
	drawTeaPot(100);
	glPopMatrix();
	//Drawing the Candles (1st complex Object)
	glPushMatrix();
	glTranslatef(0.0f, 50.0f, 0.0f);
	drawWholeCandle();
	glPopMatrix();
	//Cup
	glPushMatrix();
	if(cupShift[0] > 0)
	{
		glTranslatef(cupShift[0] - 125, cupShift[1] - 47, 0.0f);
	}
	glRotatef(cupAngle, 0.0, 1.0, 0.0);
	drawCup();
	glPopMatrix();
	//Drawing the Chandelier (2nd complex Object)
	glPushMatrix();
	glTranslatef(0.0f, 650.0f, 0.0f);
	drawChandelier();
	glPopMatrix();
	// //Drawing the food holder
	glPushMatrix();
	glTranslatef(-500.0f, 50.0f, 0.0f);
	drawFoodHolder();
	glPopMatrix();
	// //Drawing a bottle
	glPushMatrix();
	glTranslatef(400.0f, 60.0f, 0.0f);
	drawBottle();
	glPopMatrix();

	
	
	//Back wall
	if(! removeBack)
	{
		glPushMatrix();
		glTranslatef(00.0f, 0.0f, -700.0);
		glColor3f(0.1098f, 0.50196f, 0.6470f);
		glScaled(1.2f,1.0f,0.01f);
		glutSolidCube(1500);
		glPopMatrix();
	}
	//Front wall
	if( ! removeFront)
	{
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 700.0f);
		glColor3f(0.1098f, 0.50196f, 0.6470f);
		glScaled(1.2f,1.0f,0.01f);
		glutSolidCube(1500);
		glPopMatrix();
	}
	
	if(! removeLeft)
	{
		//Left Wall
		glPushMatrix();
		glTranslatef(-780.0f, 0.0f, 100.0f);
		glColor3f(0.1098f, 0.50196f, 0.6470f);
		glRotated(-90,0.0,1.0,0);
		glScaled(1.2f,1.0f,0.01f);
		glutSolidCube(1500);
		glPopMatrix();
	}
	if(! removeRight )
	{
		// //Right Wall
		glPushMatrix();
		glTranslatef(780.0f, 0.0f, 100.0f);
		glColor3f(0.1098f, 0.50196f, 0.6470f);
		glRotated(-90,0.0,1.0,0);
		glScaled(1.2f,1.0f,0.01f);
		glutSolidCube(1500);
		glPopMatrix();
	}

	if(! removeMiddle)
	{
		//Middle Wall
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -200.0f);
		glColor3f(0.9216f, 0.549f, 0.0f);
		glRotated(-90,1.0,0,0);
		glScaled(1.0f,0.7f,0.01f);
		glutSolidCube(1500);
		glPopMatrix();
	}

	//Below wall
	glPushMatrix();
	glTranslatef(0.0f, -750.0f, -200.0f);
	glColor3f(0.988f, 0.365f, 0.2392f);
	glRotated(-90,1.0,0,0);
	glScalef(1.2f,1.2f,0.01f);
	glutSolidCube(1500);
	glPopMatrix();
	glFlush();
}
void handleBottle(){
	if(! bottleBezierTurn)
	{
		if(bottlePositive && bottleHShift < 65)
		{
			bottleHShift += 0.09;
		} else if(bottlePositive){
			bottlePositive = false;
		} else if((! bottlePositive) && bottleHShift > 0)
		{
			bottleHShift -= 0.09;
		} else if(! bottlePositive)
		{
			bottlePositive = true;
			bottleBezierTurn = true;
		}
	}
	else{
		if(bottleShift[0] < 433 && bottleRight)
		{
			bottle += 0.001;
			bezier(2);
		} else if(bottleRight)
		{
			bottle -= 0.001;
			bottleRight = false;
			bezier(2);
		}
		else if((! bottleRight) && bottleShift[0] > 241)
		{
			bottle -= 0.001;
			bezier(2);
		}
		else if((! bottleRight) && bottleShift[1] > 4){
			bottle -= 0.001;
			bezier(2);
		}else if(! bottleRight){
			bottleBezierTurn = false;
			bottleRight = true;
		}
	}
	
}

void drawBottle(){
	GLUquadric *quadObj = gluNewQuadric();
	//Here we draw the bottle
	glPushMatrix();
	if(bottleShift[0] > 0)
	{
		glTranslatef(bottleShift[0] - 241, bottleShift[1] - 4, 0.0f);
	}
	//The upper cylinder (Mouth) of the bottle
	glPushMatrix();
	glColor3d(0, 1, 0);
	glTranslatef(0.0f, 280.0f, 0.0f);
	glRotatef(90, 1, 0, 0);
	gluCylinder(quadObj, 20.0f, 20.0f, 50.0f, 50, 50);
	glPopMatrix();

	//The upper part of the bottle
	glPushMatrix();
	glColor3d(0, 1, 0);
	glTranslatef(0.0f, 230.0f, 0.0f);
	glRotatef(90, 1, 0, 0);
	gluCylinder(quadObj, 20.0f, 40.0f, 65.0f, 50, 50);
	glPopMatrix();
	//The upper part but one of the bottle
	glPushMatrix();
	glTranslatef(bottleHShift, 0.0f, 0.0f);
	glColor3f(0.65f, 0.165f, 0.165f);
	glTranslatef(0.0f, 165.0f, 0.0f);
	glRotatef(90, 1, 0, 0);
	gluCylinder(quadObj, 40.0f, 70.0f, 65.0f, 50, 50);
	glPopMatrix();
	//The middle part of the bottle
	glPushMatrix();
	glColor3d(0, 1, 0);
	glTranslatef(0.0f, 100.0f, 0.0f);
	glRotatef(90, 1, 0, 0);
	gluCylinder(quadObj, 70.0f, 70.0f, 100.0f, 50, 50);
	glPopMatrix();
	glTranslatef(-bottleHShift, 0.0f, 0.0f);
	//Drawing the base of the bottle to fill the cylinder
	glPushMatrix();
	glColor3d(0, 1, 0);
	glTranslatef(0.0f, -65.0f, 0.0f);
	glRotatef(90, 1, 0, 0);
	gluDisk(quadObj, 0, 50, 50, 50);
	glPopMatrix();
	glColor3d(0, 1, 0);
	//the base cylinder of the bottle
	glRotatef(90, 1, 0, 0);
	gluCylinder(quadObj, 70.0f, 50.0f, 65.0f, 50, 50);
	glPopMatrix();
}

void handleFoodHolder(){
	if(foodHolderAngleTurn)
	{
		if(foodHolderAngleIncrease)
		{
			if(foodHolderAngle < 90)
			{
				foodHolderAngle += 0.07;
			}
			else{
				foodHolderAngleIncrease = false;
				foodHolderAngleTurn = false;
			}
		}
		else{
			if(foodHolderAngle > 0)
			{
				foodHolderAngle -= 0.07;
			}
			else{
				foodHolderAngleIncrease = true;
				foodHolderAngleTurn = false;
			}
		}
	}
	else if(!foodHolderSpilarTurn){
		if(foodHolderY < 20 && translateUpFood)
		{
			foodHolderY += 0.04;
		}
		else if(translateUpFood)
		{
			translateUpFood = false;
			foodHolderAngleTurn = true;
		}
		else if(! translateUpFood && (foodHolderY > 0) )
		{
			foodHolderY -= 0.04;
		}
		else{
			translateUpFood = true;
			foodHolderSpilarTurn = true;
		}
	}
	else{
		if(foodHSpilarIncrease)
		{
			if(foodHolderCounter < 6.28)
			{
				foodHolderX = foodHolderCounter * cosf(6*foodHolderCounter);
				foodHolderY2 = foodHolderCounter * sinf(6*foodHolderCounter);
				foodHolderZ = foodHolderCounter;
				foodHolderCounter += 0.008;
			}
			else
				foodHSpilarIncrease = false;
		} else{
			if(foodHolderCounter > 3.0)
			{
				foodHolderX = foodHolderCounter * cosf(6*foodHolderCounter);
				foodHolderY2 = foodHolderCounter * sinf(6*foodHolderCounter);
				foodHolderZ = foodHolderCounter;
				foodHolderCounter -= 0.008;
			}
			else
			{
				foodHSpilarIncrease = true;
				foodHolderSpilarTurn = false;
			}
		}
	}
}
void drawFoodHolder(){
	GLUquadric *quadObj = gluNewQuadric();
	//Drawing the base of the food-holder
	glPushMatrix();

	//Drawing the upper part of the food-holder
	glPushMatrix();
	glTranslatef(0.0f, foodHolderY, 0.0f);
	glRotatef(foodHolderAngle, 0, 1, 0);
	//Drawing the holder of the upper part of the food-holder
	glPushMatrix();
	
	glTranslatef(0.0f, 75.0f, 0.0f);
	glRotatef(90, 0, 0, 1);
	glScalef(1.0f, 1.0f, 0.5f);
	drawRightHalfCircle(50.0f);
	glPopMatrix();

	glColor3f(0.63, 0.87, 1);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(100, 100, 30, 30);
	glPopMatrix();

	glTranslatef(foodHolderX, foodHolderY2, foodHolderZ);
	//Drawing the upper cover of the base
	glColor3f(0.63, 0.87, 1);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	gluDisk(quadObj, 0, 100, 50, 50);
	glPopMatrix();
	glRotatef(90, 1, 0, 0);
	gluCylinder(quadObj, 100.0f, 120.0f, 35.0f, 50, 50);
	glPopMatrix();
}

void handleChandelier(){
	//Here we do the non-trivial animation of the Chandelier
	if(! trivialChandelier && (chandelierBackToOrigin))
	{	//Here we move in a spiral way
		if(chandelierDown && (! chandelierUpperLevel))
		{
			if(chandelierCounter < 25.133)
			{
				chandelierX = 0.5 * exp(0.15 * chandelierCounter) * cosf(2 * chandelierCounter);
				chandelierY = 0.5 * exp(0.15 * chandelierCounter) * sinf(2 * chandelierCounter);
				chandelierZ = 0.5 * exp(0.15 * chandelierCounter);
				chandelierCounter += 0.01;
			} else
				chandelierDown = false;
		}else if(!chandelierUpperLevel){
			if(chandelierCounter > 8)
			{
				chandelierX = 0.5 * exp(0.15 * chandelierCounter) * cosf(2 * chandelierCounter);
				chandelierY = 0.5 * exp(0.15 * chandelierCounter) * sinf(2 * chandelierCounter);
				chandelierZ = 0.5 * exp(0.15 * chandelierCounter);
				chandelierCounter -= 0.01;
			}
			else{
				chandelierDown = true;
				chandelierUpperLevel = true;
			}
		}
		//Now we deform the upper-level
		else if (chandelierUpperLevel)
		{
			if(chandelierScal)
			{
				if(scaleXC >= 0.5)
				{
					scaleXC -= 0.001;
				}
				else
					chandelierScal = false;
			} else{
				if(scaleXC < 1.0)
				{
					scaleXC += 0.001;
				}
				else{
					chandelierScal = true;
					chandelierUpperLevel = false;
					trivialChandelier = true;
				}
			}
		}
	}
	else if(chandelierBackToOrigin){
		if(chandelierAngle < 20.0 && chandelierAngleIncrease)
		{
			chandelierAngle += 0.06;
		}
		else if(chandelierAngleIncrease)
		{
			chandelierAngleIncrease = false;
		}
		else if ((! chandelierAngleIncrease) && chandelierAngle > -20.0)
		{
			chandelierAngle -= 0.06;
		}
		else if((! chandelierAngleIncrease))
		{
			chandelierAngleIncrease = true;
			chandelierBackToOrigin = false;
		}
	}
	else{
		if(chandelierAngle < 0)
		{
			chandelierAngle += 0.06;
		}
		else 
			chandelierBackToOrigin = true;
			trivialChandelier = false;
	}

	
}

void drawChandelier(){
	GLUquadric *quadObj = gluNewQuadric();
	glPushMatrix();
	//This Matrix to draw the upper levels of the cylinder
	glRotatef(chandelierAngle, 0, 0.0, 1.0);
	glPushMatrix();
	glScalef(scaleXC, 1.0f, 1.0f);
	glPushMatrix();
	//Cover of CYlinder (Upper-Surface)
	glPushMatrix();
	glTranslatef(0.0f, 100.0f, 0.0f);
	glRotatef(90, 1, 0, 0);
	gluDisk(quadObj, 0, 50, 50, 50);
	glPopMatrix();
	//This is the second level
	glTranslatef(0.0f, 100.0f, 0.0f);
	glColor3d(1, 1, 0);
	glRotatef(90, 1, 0, 0);
	gluCylinder(quadObj, 50.0f, 50.0f, 35.0f, 50, 50);
	glPopMatrix();

	//Cover of CYlinder (Upper-Surface)
	glPushMatrix();
	glTranslatef(0.0f, 70.0f, 0.0f);
	glRotatef(90, 1, 0, 0);
	gluDisk(quadObj, 0, 100, 50, 50);
	glPopMatrix();
	//This is the first level
	glTranslatef(0.0f, 70.0f, 0.0f);
	glColor3d(1, 1, 0);
	glRotatef(90, 1, 0, 0);
	gluCylinder(quadObj, 100.0f, 100.0f, 55.0f, 50, 50);
	glPopMatrix();
	//Cylinder in the mid of the chandelier
	glPushMatrix();
	glColor3d(1, 1, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quadObj, 25.0f, 25.0f, 150.0f, 50, 50);
	glPopMatrix();

	glTranslatef(chandelierX, chandelierY, chandelierZ);
	//Here is the matrix of candles on the cone
	glPushMatrix();
	//Right Candle
	glPushMatrix();
	glTranslatef(150.0f, 60.0f, 0.0f);
	drawCandleSides();
	glPopMatrix();
	//Left Candle
	glPushMatrix();
	glTranslatef(-150.0f, 60.0f, 0.0f);
	drawCandleSides();
	glPopMatrix();
	//Front Candle
	glPushMatrix();
	glTranslatef(0.0f, 60.0f, 150.0f);
	drawCandleSides();
	glPopMatrix();
	//Back Candle
	glPushMatrix();
	glTranslatef(0.0f, 60.0f, -150.0f);
	drawCandleSides();
	glPopMatrix();
	glPopMatrix();
	
	//The base of the Chandelier
	glColor3d(1, 1, 0);
	glRotatef(90, 1, 0, 0);
	glutSolidCone(180,100,30,30);

	glPopMatrix();
}

void handleTeaPotDeformation(){
	if(! swap)
	{
		if(scalingDirectionY){
		if( scaleY > 0.4)
			scaleY -= 0.001;
		else 
			scalingDirectionY = false;
		}
		else if(! scalingDirectionY){
			if(scaleY >= 1.0){
				scalingDirectionY = true;
				swap = true;
			}
			else
				scaleY += 0.001;
		}
	} else{
		if(scalingDirectionZ){
		if( scaleX > 0.4)
			scaleX -= 0.001;
		else 
			scalingDirectionZ = false;
		}
		else if(! scalingDirectionZ){
			if(scaleX >= 1.0){
				scalingDirectionZ = true;
				swap = false;
			}
			else
				scaleX += 0.001;
		}
	}

}

void drawTeaPot(double size)
{
	//After this line the coordinates will be a bit missed as +z will point to -x and +x will point to -z
	//That's because of the rotation
	glRotated(-90, 0, 1, 0);
	//Drawing the Teapot itself
	glColor3d(0.63, 0.76, 0.82);
	glutSolidTeapot(size);
	//Drawing the Left Eye of it
	glPushMatrix();
	//Left Nne :D
	glPushMatrix();

	glTranslatef(90, 20, 40);
	glColor3d(0.2, 0.36, 0.44);
	glutWireSphere(10, 100, 100);
	
	glPopMatrix();
	//Normal Eye
	glTranslatef(70, 20, 40);
	glColor3d(1,1,1);
	glutWireSphere(25, 100, 100);
	glPopMatrix();
	
	glPushMatrix();
	//Drawing the Right Eye of it
	//Right Nne :D
	glPushMatrix();

	glTranslatef(90, 20, -40);
	glColor3d(0.2, 0.36, 0.44);
	glutWireSphere(10, 100, 100);
	
	glPopMatrix();
	//Normal Eye
	glTranslatef(70, 20, -40);
	glColor3d(1,1,1);
	glutWireSphere(25, 100, 100);
	glPopMatrix();
}

void bezier(int whichOne)
{
    if(whichOne == 1){
        cupShift[0]=pow((1-cup),3)*cupP0[0]+3*cup*pow((1-cup),2)*cupP1[0]+3*pow(cup,2)*(1-cup)*cupP2[0]+pow(cup,3)*cupP3[0];
        cupShift[1]=pow((1-cup),3)*cupP0[1]+3*cup*pow((1-cup),2)*cupP1[1]+3*pow(cup,2)*(1-cup)*cupP2[1]+pow(cup,3)*cupP3[1];
    }else{
		bottleShift[0] = pow((1-bottle),3)*bottleP0[0]+3*bottle*pow((1-bottle),2)*bottleP1[0]+3*pow(bottle,2)*(1-bottle)*bottleP2[0]+pow(bottle,3)*bottleP3[0];
		bottleShift[1] = pow((1-bottle),3)*bottleP0[1]+3*bottle*pow((1-bottle),2)*bottleP1[1]+3*pow(bottle,2)*(1-bottle)*bottleP2[1]+pow(bottle,3)*bottleP3[1];
	}
}
void Anim(){
	
	if(cu || playAll)
	{
		handleCup();
	}
	if(ca || playAll)
	{
		handleCandle();
	}
	if(ch || playAll)
	{
		handleChandelier();
	}
	if(t || playAll){
		handleTeaPotDeformation();
	}
	if(fh || playAll){
		handleFoodHolder();
	}
	if(b || playAll){
		handleBottle();
	}
	if(rotateScene)
	{
		handleCamera();
	}
	glutPostRedisplay();
}

void handleCup(){
	if(! rotateCup)
	{	//Here the cup moves according to its bezier curve
		if((cupShift[0] < 685) && cupRight)
		{
			//Here the cup moves normally to the right
			bezier(1);
			cup += 0.001;	
		}
		else if(cupRight && cupShift[0] >= 685)
		{
			//Here the cup has reached the max x-point so it should move back
			cup -= 0.001;
			cupRight = false;
			rotateCup = true;
			bezier(1);
			
		}else if (cupShift[0] > 125 && (!cupRight)){
			//Here the cup moves normally to the left
			bezier(1);
			cup -= 0.001;
		}
		else if((!cupRight)&& cupShift[0] <= 125 && cupShift[1] > 46){
			//Here we ensure that the cup came back to the start point
			cup -= 0.001f;
			bezier(1);
		} else{
			//Here the cup has reached the original starting point and will repeat the curve again
			cupRight = true;
			bezier(1);
		}
	}
	else
	{
		//Here we rotate the cup when it reaches the end of the curve
		if(cupAngle >= 45 && cupAnglePos)
		{
			cupAnglePos = false;
		} else if (cupAnglePos){
			cupAngle += 0.09;
		} else if (cupAngle > 0 && (!cupAnglePos)){
			cupAngle -= 0.09;
		} else if(! cupAnglePos){
			cupAnglePos = true;
			rotateCup = false;
		}

	}
	
}

void handleCandleComplexAnimation(){
	if(! rotateCandle)
	{
		//Translation of the three candles
		if(flameY < 40 && flameIncrease)
		{
			flameY += 0.08;
		}
		else if(flameIncrease){
			rotateCandle = true;
			flameIncrease = false;
		}
		else if(! flameIncrease && flameY > 0)
		{
			flameY -= 0.08;
		} 
		else if(! flameIncrease)
		{
			flameIncrease = true;
			candleComplex = false;
		}
	} else if(!candlesSpiral) {
		//Rotation of the three candles only
		if(angleCandleX < 40 && angleCandleXIncrease)
		{
			angleCandleX += 0.06;
		} else if(angleCandleXIncrease)
		{
			angleCandleXIncrease = false;
		} else if(angleCandleX > 0 && (! angleCandleXIncrease))
		{
			angleCandleX -= 0.06;
		}
		else if(! angleCandleXIncrease)
		{
			angleCandleXIncrease = true;
			candlesSpiral = true;
		}
	}
	else{
		//Spiral Movement of the candles
		if(candlesSpiralIncrease)
		{
			if(candlesCounter < 6.28)
			{
				candlesX = candlesCounter * cosf(6*candlesCounter);
				candlesY = candlesCounter * sinf(6*candlesCounter);
				candlesZ = candlesCounter;
				candlesCounter += 0.009;
			}
			else
				candlesSpiralIncrease = false;
		} else{
			if(candlesCounter > 3.0)
			{
				candlesX = candlesCounter * cosf(6*candlesCounter);
				candlesY = candlesCounter * sinf(6*candlesCounter);
				candlesZ = candlesCounter;
				candlesCounter -= 0.009;
			}
			else
			{
				candlesSpiralIncrease = true;
				candlesSpiral = false;
				rotateCandle = false;
			}
		}
	}
	
}
void handleCandle(){
	if(! candleComplex )
	{
		if(candleAngle >= 20.0 && candleAngleIncrease)
		{
			candleAngleIncrease = false;
		}
		else if (!candleAngleIncrease && candleAngle <= 0)
		{
			candleAngleIncrease = true;
			candleComplex = true;
		}
		if(candleAngleIncrease){
			candleAngle += 0.08;
		}else{
			candleAngle -= 0.08;
		}
	} else{
		handleCandleComplexAnimation();
	}
}
void drawWholeCandle(){
	glLineWidth(300.0f);	
	glPushMatrix();
	//We want the candle to be rotated in the x-z Plane
	glRotatef(candleAngle,0.0,0.0,1.0);
	//Here the base is the main object to be rotated
	//Now this matrix to draw the lines that hold the candles
	glPushMatrix();
	glTranslatef(0.0f, flameY, 0.0f);
	glRotatef(-angleCandleX, 1, 0, 0);
	glBegin(GL_LINES);
	glColor3f(0.23f,0.23f,0.09f);
	glVertex3f(0.0f, 140.0f, 0.0f);
	glVertex3f(0.0f,200.0f,0.0f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.23f,0.23f,0.09f);
	glVertex3f(0.0f, 140.0f, 0.0f);
	glVertex3f(75.0f,200.0f,0.0f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.23f,0.23f,0.09f);
	glVertex3f(0.0f, 140.0f, 0.0f);
	glVertex3f(-75.0f,200.0f,0.0f);
	glEnd();

	//This matrix to draw th candles
	glPushMatrix();
	glTranslatef(candlesX, candlesY, candlesZ);
	drawUpperCandle();
	glPopMatrix();

	glPopMatrix();
	
	//drawing the candle base
	glTranslatef(0.0f,-40.0f,0.0f);
	drawCandleBase();

	glPopMatrix();
}

void drawUpperCandle(){
    glPushMatrix();
        //This matrix holds the right candle
        glPushMatrix();
        glTranslatef(-75.0f,240.0f,0.0f);
        drawCandleSides();
        glPopMatrix();
		//This matrix holds the left candle
		glPushMatrix();
		glTranslatef(75.0f,240.0f,0.0f);
		drawCandleSides();
		glPopMatrix();
        //This matrix holds the center candle
        glPushMatrix();
        glTranslatef(0.0f,250.0f,0.0f);
        drawCandleSides();
        glPopMatrix();
       
    glPopMatrix();
}

void drawCandleBase(){
    GLUquadric *quadObj = gluNewQuadric();
	glPushMatrix();
	//To draw the cone which is the base of the Candle Base
	glPushMatrix();
	//To draw the arm of the Candle Base
	glPushMatrix();
	//To draw the sphere in the Candle Base
	glTranslatef(0.0f, 180.0f, 15.0f);
	glutWireSphere(15, 50, 50);
	glPopMatrix();

	glRotated(-90.0, 1, 0, 0);
	glColor3f(0.23f,0.23f,0.09f);
	gluCylinder(quadObj,25.0f,25.0f,180.0f,32,32);
	glPopMatrix();
	glRotated(-90.0, 1, 0, 0);
    //gluSolidCone(base_radius, height, slices, stacks)
	glutSolidCone(50,20,30,30);
	glPopMatrix();
}

void drawCandleSides(){
    GLUquadric *quadObj = gluNewQuadric();
    
    glPushMatrix();
    glRotated(90.0, 1, 0, 0);

    glPushMatrix();

    //Drawing the flame
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-40.0f);
    glRotated(180.0, 1, 0, 0);
    glColor3d(1,1,0);
    //gluSolidCone(base_radius, height, slices, stacks)
    glutSolidCone(20.0f,25.0f,30,30);
    glPopMatrix();

    //The small candle itself
    glColor3f(0.66f,0.77f,0.051f);
    glTranslatef(0.0f,0.0f,-30.0f);
    gluCylinder(quadObj,25.0f,25.0f,30.0f,32,32);
    glPopMatrix();

    glColor3f(0.23f,0.23f,0.09f);
    //Holder of the small candle
    gluCylinder(quadObj,35.0f,10.0f,60.0f,32,32);
    glPopMatrix();
}

void drawRightHalfCircle(float r)  // the empty one
{
    float radius = r;
    float twoPI = 2 * 3.14159;
	glPointSize(4.0f);
    glBegin(GL_POINTS);
	
    for (float i = 0.0; i <= twoPI / 2; i += 0.001)
        glVertex3f((sinf(i)*radius), 0.0f, (cosf(i)*radius));

    glEnd(); 
}

void handleCamera(){

	if (alpha >= 6.20)
	{
		alpha = 0.0f;
	}
	else 
		alpha += 0.001;
	
	rotateX = 1 * sinf(alpha);
	rotateZ = 1 * cosf(alpha);
	
	if((alpha >= 0 && alpha <= 0.7) || (alpha > 4.9))
	{
		removeFront = true;
		removeBack = false;
		removeLeft = false;
		removeRight = false;
	} else if( alpha > 0.7 && alpha <= 2.1)
	{
		removeFront = false;
		removeBack = false;
		removeLeft = false;
		removeRight = true;
	} else if( alpha > 2.1 && alpha <= 3.5)
	{
		removeFront = false;
		removeBack = true;
		removeLeft = false;
		removeRight = false;
	} else if( alpha > 3.5 && alpha <= 4.9)
	{
		removeFront = false;
		removeBack = false;
		removeLeft = true;
		removeRight = false;
	}

	//printf("alpha = %f \n", alpha);
}
void drawCup(){

	GLUquadric *quadObj = gluNewQuadric();
	
	glPushMatrix();
	glTranslatef(-600.0f, -680.0f, 0.0f);
	glRotated(90.0, 1, 0, 0);
	//Here the matrix of the upper body of the cup
	glPushMatrix();
	glColor3f(0.18f, 0.59f, 0.6f);
	//This Matrix draws the holder of the cup
	glPushMatrix();
	glTranslatef(50.0f, 0.0f, -35.0f);
	drawRightHalfCircle(30.0f);
	glPopMatrix();

	
	glTranslatef(0.0f, 0.0f, -70.0f);
	gluCylinder(quadObj, 50.0f, 20.0f, 90.0f, 32, 32);
	glPopMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	//Here is the base of the cup
	gluCylinder(quadObj, 0.0f, 35.0f, 50.0f, 32, 32);
	glPopMatrix();
}

void spe(int k, int x, int y)// keyboard special key function takes 3 parameters
// int k: is the special key pressed such as the keyboard arrows the f1,2,3 and so on
{
	
	if (k == GLUT_KEY_UP)//if the up arrow is pressed, then the object will be translated in the y axis by 10. (moving upwords)
		passY = 30.0f;
	if (k == GLUT_KEY_DOWN)//if the down arrow is pressed, then the object will be translated in the y axis by -10. (moving downwords)
		passY = 0.0f;

	glutPostRedisplay();//redisplay to update the screen with the changes
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Lab 5");
	glutDisplayFunc(Display);
	glutIdleFunc(Anim);
	glutSpecialFunc(spe);			//call the keyboard special keys function
	glutKeyboardFunc(key);	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
	return 1;
}
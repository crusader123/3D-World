
Graphics :: Assignment 2 (Adventure with 3D World)
Game     :: The Fun Begins.......................
Made By  :: Shubham Sangal – 201101008 and J N Venkatesh - 201102007


Continuation of Assignment 2.1

1. First Unzip the 201101008_assignment2.2.zip.

2. "main.cpp" file contains the main code. 
   
Rest are some of the files which will help run code in windows and some other.
"imageloader.h","imageloader.cpp" are the image loading files. I have taken this files directly from the website                        "http://www.videotutorialsrock.com/opengl_tutorial/textures/home.php". They are basically used for reading images and loading them as textures.

3. "index.bmp","water.bmp" are  uesd for texture. These files are also taken from web. "water.bmp" is taken explicitly from                "http://videotutorialrocks.com" and "index.bmp","crate.bmp","jungle.bmp","jungle2.bmp" from google images.

4. "Makefile" is for generating the executable of the game. "Game" is the executable for game.

5. Steps to compile and run the game.

	1) type the command: make
	2) Once you typed the make command, the executable "Game" will be generated / updated.
	3) Run the executable Game by ./Game and the window of game appears.
	4) Maximise the window
	
	Instead of all these, we can follow these steps as well:
	1) type : g++ -lglut -lGL -lGLU main.cpp imageloader.cpp -o test2
	2) Executable test2 gets generated.
	3) run ./test2

5. Controls of the game:
	1) Down Arrow Key: Forward Moving
	2) Up Arrow Key  : Backward Moving
	3) Right Arrow Key: Turning Right
	4) Left Arrow Key: Turning Left
	5) j/Space Key   : Jump
	6) a             : First Person View
	7) t             : top View
	8) s             : third person View
	9) Esc key       : quit
	10) d            : tile view
	11) f            : favourite view(additional)
	12) h            : helicopter
	13) 8,4,6,2      : for navigating tiles in tile view
	14) mouse        : for dragging camera in helicopter view
	15) v		 : for spotlifgt

	Note: Once you enter in any view, to get back in normal view you have to press that key again. For example, you pressed t and got into top view. Now to be back in normal view, press t again.


6. Instructions for playing: 
You have to start from [0][0]th tile and reach the diagonally opposite most tile collectilg all coins. You have 3 lives.
Beware of the obstacles.They can cost you a life:
	Dont try to cross the boundary of tiles to jump in water. It will cost a life.
	Dont try to touch the moving blocks. It can cost you a life.
	Go from beneath the moving Block to cross it.
	Static blocks can be crossed through unless you jump on it.
	Jump on the Missing tiles also cost a life.
	After 3 lives are finished, Game will be over.


7. Acknowledgements:

All through developing process, I have taken help of a lot of websites some of which are:

        1)http://www.alpcentauri.info/glut_part_2.html#Animation : I have tried to follow their template and programming style. I have kept their snowman program as base of my code.
	2)http://videotutorialrocks.com : I have closely watched some of their video tutorials and used some of their headers and files such as "imageloader.h", "imageloader.cpp","water.bmp"  straightforward without any change mainly for the purpose of providing texture.Also I have imported some of functions in my main.cpp such as void advance,GLuint loadTexture(Image* image),void drawBitmapText(char *string,float x1,float y1,float z),void GetOGLPos(int x, int y) etc.
	3)http://www.codersource.net/MFC/OpenGL/DisplayingTextOpenGLTutorial5.aspx : For implementing OpenGl fonts.


	--------------------------------------------------------------------------------------------------------------



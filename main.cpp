#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <fstream>
using namespace std;



int best_score;
int number_undo;
int dem_undo;
int score_undo[5];
int de_undo[5][4][4];
int score;
int broad[4][4];
int deroad[4][4];
int dir_line[] = { 1,0,-1,0 };
int dir_column[] = { 0,1,0,-1 };

std::pair<int, int> sinh() {
	int thu = 1, cot, hang;
	while (thu) {
		hang = rand() % 4;
		cot = rand() % 4;
		if (broad[hang][cot] == 0)
			thu = 0;
	}
	return make_pair(hang, cot);
}

string chuyen_doi(int a)
{
	string s;
	char x;
	int n;
	if (a == 0) return "0";
	while (a != 0)
	{
		n = a % 10;
		x = n + '0';
		s = x + s;
		a = a / 10;
	}
	return s;
}

void undo()
{
	if (number_undo == 0)return;
	else {
		number_undo--;
		if (dem_undo > 0)dem_undo--;
		else dem_undo = 4;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				broad[i][j] = de_undo[dem_undo][i][j];
		score = score_undo[dem_undo];
	}
}

bool end_game()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (broad[i][j] == 0)return true;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			if (broad[i][j] == broad[i][j + 1])return true;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			if (broad[i][j] == broad[i + 1][j])return true;
	return false;

}

void khai() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			deroad[i][j] = 0;
}

void addpiece(int ngau_nhien) {
	pair<int, int> pos = sinh();
	if (ngau_nhien % 4 == 0)    broad[pos.first][pos.second] = 2;
	else broad[pos.first][pos.second] = 1;
}

void NewGame() {
	score = 0;
	dem_undo = 0;
	number_undo = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			broad[i][j] = 0;
	khai();
	addpiece(2);
	addpiece(2);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			de_undo[dem_undo][i][j] = broad[i][j];
	score_undo[dem_undo] = score;
	dem_undo++;
}
void PrintUI() {
	system("cls");
	cout << " score: " << score << " " << best_score << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			if (broad[i][j] == 0)
				cout << setw(4) << ".";
			else
				cout << setw(4) << broad[i][j];
		cout << endl;
	}
	cout << "n: New Game \nw: Up \ns: Down\nd: Right\na: Left\nq: Quit\n";
}

bool CanDoMove(int line, int column, int NextLine, int NextColumn) {
	if (line < 0 || column < 0 || NextColumn >= 4 || NextLine >= 4 || NextColumn < 0 || NextLine < 0
		|| (broad[line][column] != broad[NextLine][NextColumn] && broad[NextLine][NextColumn] != 0))
		return false;
	if (deroad[line][column] == 1 && broad[NextLine][NextColumn] != 0)return false;
	if (deroad[NextLine][NextColumn] == 1 && broad[line][column] != 0)return false;
	return true;
}

void applymove(int direction) {
	int startline = 0, startcolumn = 0, linestep = 1, columnstep = 1;
	if (direction == 0) {
		startline = 3;
		linestep = -1;
	}
	if (direction == 1) {
		startcolumn = 3;
		columnstep = -1;
	}
	int movepossible, CanAddPiece = 0;
	do {
		movepossible = 0;
		for (int i = startline; i >= 0 && i < 4; i += linestep)
			for (int j = startcolumn; j >= 0 && j < 4; j += columnstep) {
				int nextI = i + dir_line[direction], nextJ = j + dir_column[direction];
				if (broad[i][j] && CanDoMove(i, j, nextI, nextJ)) {
					if (broad[nextI][nextJ] != 0) score += pow(2, broad[i][j] + 1);
					if (broad[nextI][nextJ] != 0)
					{
						deroad[i][j] = 1;
						broad[nextI][nextJ] = broad[i][j] + 1;
					}
					if (broad[nextI][nextJ] == 0) broad[nextI][nextJ] += broad[i][j];

					deroad[nextI][nextJ] += deroad[i][j];
					broad[i][j] = 0; deroad[i][j] = 0;
					movepossible = CanAddPiece = 1;
				}
			}
		PrintUI();
	} while (movepossible);
	if (CanAddPiece) {
		int so = rand() % 7 + 1;
		addpiece(so);
	}
	khai();

}
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};
const int BUTTON_WIDTH = 120;
const int BUTTON_HEIGHT = 40;
const int TOTAL_BUTTONS = 1;

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};

const int SCREEN_WIDTH = 540;
const int SCREEN_HEIGHT = 670;

class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	void setBlendMode(SDL_BlendMode blending);

	void setAlpha(Uint8 alpha);

	void free();

	void render(int x, int y);
	void renders(int x, int y, SDL_Rect* clip);

	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

class LButton
{
public:
	LButton();

	void setPosition(int x, int y);

	void handleEvent1(SDL_Event* e);
	void handleEvent2(SDL_Event* e);

	void render();

private:
	SDL_Point mPosition;

	LButtonSprite mCurrentSprite;
};

bool init();

bool loadMedia();

void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
LTexture gCurrentSurface;

LTexture gSpriteSheetTexture;
SDL_Rect gSpriteClips[16];

LTexture gBackgroundTexture;
LTexture gGameover;

TTF_Font* gFont = NULL;
LTexture gTextTexture;
LTexture gTextTexture2;

LTexture gButtonSpriteSheetTexture;
LButton gButtons[1];
LTexture gButtonSpriteSheetTexture2;
LButton gButtons2[1];



LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != NULL;

}


void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

void LTexture::renders(int x, int y, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}
void LButton::handleEvent1(SDL_Event* e)
{

	if (e->type == SDL_MOUSEBUTTONDOWN)
	{

		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;

		if (x < 250)
		{
			inside = false;
		}
		else if (x > 370)
		{
			inside = false;
		}
		else if (y < 90)
		{
			inside = false;
		}
		else if (y > 130)
		{
			inside = false;
		}

		if (!inside)
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				NewGame();
				break;
			}
		}
	}
}

void LButton::handleEvent2(SDL_Event* e)
{

	if (e->type == SDL_MOUSEBUTTONDOWN)
	{

		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;

		if (x < 400)
		{
			inside = false;
		}
		else if (x > 520)
		{
			inside = false;
		}
		else if (y < 90)
		{
			inside = false;
		}
		else if (y > 130)
		{
			inside = false;
		}

		if (!inside)
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		else
		{
			switch (e->type)
			{
			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				undo();
				break;
			}
		}
	}
}

void LButton::render()
{
	gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y);
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{

	bool success = true;


	if (!gButtonSpriteSheetTexture.loadFromFile("img/newgame.png"))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else
	{
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = BUTTON_WIDTH;
		gSpriteClips[0].h = BUTTON_HEIGHT;

		gButtons[0].setPosition(250, 90);
	}if (!gButtonSpriteSheetTexture2.loadFromFile("img/undo.png"))
	{
		printf("Failed to load button sprite texture!\n");
		success = false;
	}
	else
	{
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = BUTTON_WIDTH;
		gSpriteClips[0].h = BUTTON_HEIGHT;

		gButtons[0].setPosition(400, 90);
	}
	if (!gSpriteSheetTexture.loadFromFile("img/tiles.png"))
	{
		printf("Failed to load sprite sheet texture!\n");
		success = false;
	}
	else
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				gSpriteClips[i * 4 + j].x = 100 * j;
				gSpriteClips[i * 4 + j].y = 100 * i;
				gSpriteClips[i * 4 + j].w = 100;
				gSpriteClips[i * 4 + j].h = 100;
			}

	}

	if (!gGameover.loadFromFile("img/Game_Over.png"))
	{
		printf("Failed to load game over texture image!\n");
		success = false;
	}
	if (!gBackgroundTexture.loadFromFile("img/hello_world.png"))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}
	if (!gKeyPressSurfaces[KEY_PRESS_SURFACE_UP].loadFromFile("img/hello_world.png"))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}
	if (!gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN].loadFromFile("img/hello_world.png"))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}
	if (!gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT].loadFromFile("img/hello_world.png"))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}
	if (!gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT].loadFromFile("img/hello_world.png"))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}


	return success;
}

void close()
{

	gBackgroundTexture.free();
	gSpriteSheetTexture.free();
	gTextTexture.free();
	gTextTexture.free();
	gButtonSpriteSheetTexture.free();
	gButtonSpriteSheetTexture2.free();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;


	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	srand(time(0));
	ifstream higher_score;
	higher_score.open("img/highest_score.txt");
	higher_score >> best_score;
	higher_score.close();
	NewGame();

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					//User presses a key
					else if (e.type == SDL_KEYDOWN)
					{
						//Select surfaces based on key press
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
							applymove(2);
							for (int i = 0; i < 4; i++)
								for (int j = 0; j < 4; j++)
									de_undo[dem_undo][i][j] = broad[i][j];
							score_undo[dem_undo] = score;
							if (number_undo < 5)number_undo++;
							if (dem_undo < 4)dem_undo++;
							else dem_undo = 0;
							break;

						case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
							applymove(0);
							for (int i = 0; i < 4; i++)
								for (int j = 0; j < 4; j++)
									de_undo[dem_undo][i][j] = broad[i][j];
							score_undo[dem_undo] = score;
							if (number_undo < 5)number_undo++;
							if (dem_undo < 4)dem_undo++;
							else dem_undo = 0;
							break;

						case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
							applymove(3);
							for (int i = 0; i < 4; i++)
								for (int j = 0; j < 4; j++)
									de_undo[dem_undo][i][j] = broad[i][j];
							score_undo[dem_undo] = score;
							if (number_undo < 5)number_undo++;
							if (dem_undo < 4)dem_undo++;
							else dem_undo = 0;
							break;

						case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
							applymove(1);
							for (int i = 0; i < 4; i++)
								for (int j = 0; j < 4; j++)
									de_undo[dem_undo][i][j] = broad[i][j];
							score_undo[dem_undo] = score;
							if (number_undo < 5)number_undo++;
							if (dem_undo < 4)dem_undo++;
							else dem_undo = 0;
							break;

						default:
							gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
					gButtons[0].handleEvent1(&e);
					gButtons2[0].handleEvent2(&e);
					gButtons[0].render();
					gButtons2[0].render();
				}

				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				gButtonSpriteSheetTexture.render(250, 90);
				gButtonSpriteSheetTexture2.render(400, 90);



				SDL_RenderPresent(gRenderer);

				gBackgroundTexture.render(0, -50);

				gFont = TTF_OpenFont("img/lazy.ttf", 36);
				if (gFont == NULL)
				{
					printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());

				}
				else
				{

					SDL_Color textColor = { 0, 0, 0 };
					if (!gTextTexture.loadFromRenderedText(chuyen_doi(score), textColor))
					{
						printf("Failed to render text texture!\n");

					}
				}
				gTextTexture.render(405, 45);
				if (gFont == NULL)
				{
					printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());

				}
				else
				{

					SDL_Color textColor = { 0, 0, 0 };
					if (!gTextTexture2.loadFromRenderedText(chuyen_doi(best_score), textColor))
					{
						printf("Failed to render text texture!\n");

					}
				}
				gTextTexture2.render(255, 45);
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
						if (broad[i][j] != 0)
							gSpriteSheetTexture.renders(46 + 116 * j, 176 + 116 * i, &gSpriteClips[broad[i][j] - 1]);

				if (!end_game())
					gGameover.render(0, 0);

				SDL_RenderPresent(gRenderer);
			}

		}
	}
	if (score > best_score)
	{
		ofstream outfile;
		outfile.open("img/highest_score.txt");
		outfile << score << endl;
		outfile.close();
	}

	close();

	return 0;
}
bool ghost_isolated[4] = { true, true, true, true };
bool ghost_eaten[4] = { false, false, false, false };
bool ghost_eatening[4]= { false, false, false, false };
bool ghost_frightened[4] = { false, false, false, false };
bool ghost_leave[4] = { false, false, false, false };
int ghost_frightened_dalay = 30;

bool period_init = true;
bool period_die = false;
bool period_die2 = false;
bool period_frightened = false;
bool period_frightened_end = false;
bool period_eatghost = false;
bool period_paceaten = false;
bool period_pac2eaten = false;
bool period_dissolve = false;
bool period_dissolve2 = false;
bool period_disappear = false;
bool period_end = false;

int l_grid = 18;
int padding = 15;
int l_char = 30;
int v_gh = 3;
int v_pac = 3;

int time_init;
int time_frightened;
int time_die;
int time_die2;
int time_isolated;
int time_ghost_isolated[4] = { 0, 10000 / v_pac, 20000 / v_pac, 30000 / v_pac };
int time_ghost_eaten[4];
int time_animation;
int time_pause;
int pause_duration;
int time_total_paused;
int time_pass;

int cnt = 0;
int t = 0;

int slider[4];
int y_down;
int mode;
bool fail;
double theta = 180;

bool playDeathMusic = false;

#define _CRT_SECURE_NO_DEPRECATE
#include "set.h"

enum STATUS
{
	MENU, // main menu
	SELECT, // choose mode
	CONTROL,
	ABOUT,
	HIGHSCORE,
	CREATE_MAP,
	SINGLE_1,
	SINGLE_2,
	DOUBLE_1,
	DOUBLE_2,
	SET,
	READFILE,
	ENTER_NAME,
	SELECT_WALL,
	PAUSE,
	_3D
};

char pacmanPath[100] = "../images/pacman.png";
ImageData pacman;

TextData menu[5];
SDL_Point menuPos[5] = { {WIDTH / 2,350},{WIDTH / 2,400},{WIDTH / 2,450},{WIDTH / 2,500},{WIDTH / 2,550} }; // center position
SDL_Color menuColor[5];

TextData text[8];
SDL_Point textPos[8];
SDL_Color textColor[8];


int mouseX, mouseY;
MouseState mouseState;

vector<int> v(N, 0);
vector<vector<int>> map(M, v);  //fixed
vector<vector<int>> map1(M, v); //changable
vector<vector<int>> map2(M, v); //image type
vector<vector<int>> m(M / 3, vector<int>(N/3, 0));


char wallpath[100] = "../images/wall.png";
char wall3path[100] = "../images/wall3.png";
char wall4path[100] = "../images/wall4.png";
char pacPath[100] = "../images/pac.png";
char pac2Path[100] = "../images/pac2.png";
char diePath[100] = "../images/die.png";
char die2Path[100] = "../images/die2.png";
char ghost1Path[100] = "../images/ghost1.png";
char ghost2Path[100] = "../images/ghost2.png";
char ghost3Path[100] = "../images/ghost3.png";
char ghost4Path[100] = "../images/ghost4.png";
char images1Path[100] = "../images/set.png";
char images2Path[100] = "../images/pause2.png";
char images3Path[100] = "../images/mode1.png";
char images4Path[100] = "../images/mode2.png";
char images5Path[100] = "../images/mode3.png";
char images6Path[100] = "../images/play.png";

ImageData wall;
ImageData wall3;
ImageData wall4;
ImageData pac, pac2;
ImageData die, die2;
ImageData ghost[4];
ImageData lives[3];
ImageData pause;
ImageData change;
ImageData sett;
ImageData images[6];

int pacIndex[5] = { 0 };
int pac2Index[5] = { 0 };
int dieIndex[5] = { 0 };
int die2Index[5] = { 0 };
int ghostIndex[6] = { 0 };

TextData hint, score_text, set_sign[8];

int live = 3;
int lives_alp[3] = { 255, 255, 255 };
int score = 0;
int pac_alp = 255, pac2_alp = 255;
int die_alp = 0, die2_alp = 0, ghost_alp = 255, hint_alp = 0;

Rank r[100];
int ranknum;

char inputString[20] = " \0";
bool textFlag;

bool pauseFlag = false;
bool pausedisplay = false;
bool passFlag = false;
bool validMap = true;
int lop;
int length;
int length_list[13] = { 25, 30, 35, 40, 45, 50, 54, 58, 62, 66, 70, 76, 85};
int lop_list[13] =     { 2,  6,  9, 12, 14, 16, 18, 20, 23, 27, 32, 38, 50};
int produ;
int big_sign;
int slow_list[10] = { 95, 78, 63, 50, 39, 30, 23, 18, 15, 0 };
int slow = 0;
bool enlargeFlag = false;
bool forwardFlag = false;
double magnitude = 1;
vector<vector<vector<int>>> files(40,vector<vector<int>>(M, vector<int>(N,0)));
FILE* fp1;
int fileorder;
int fileaimpos;
int filepos;
int filenum;
int button=1;
int volume = 50;
int alpha;
bool eeat = false;
int wallchange = 0;

bool quit;
SDL_Event e;
STATUS status;

#include "variable.h"
#include "stdwall.h"
#include "wall.h"
#include "blinky.h"
#include "action.h"
#include "drawMenu.h"
#include "drawClassic.h"
#include "draw3D.h"


SDL_TimerID timerID_pac = SDL_AddTimer(100, pacAction, &pacIndex);
SDL_TimerID timerID_pac2 = SDL_AddTimer(100, pac2Action, &pac2Index);
SDL_TimerID timerID_die = SDL_AddTimer(96, dieAction, &dieIndex);
SDL_TimerID timerID_die2 = SDL_AddTimer(96, die2Action, &die2Index);
SDL_TimerID timerID_ghostStyle = SDL_AddTimer(120, ghostAction, &ghostIndex);
SDL_TimerID timerID_ghost_isolated = SDL_AddTimer(10, ghost_isolated_Action, NULL);
SDL_TimerID timerID_forward_view = SDL_AddTimer(40, forward_view_Action, NULL);
SDL_TimerID timerID_file_move = SDL_AddTimer(20, file_move_Action, NULL);

int main(int argc, char* args[])
{
	if (initSDL())
	{
		printf("Failed to initialize SDL!\n");
		return -1;
	}
	loadAudio();

	loadwall(map);
	pacman = loadImgTexture(pacmanPath, 1, 1, 1, false, 0xFF, 0xFF, 0xFF);
	wall3 = loadImgTexture(wall3path, 1, 1, 1, false, 0xFF, 0xFF, 0xFF);
	wall = loadImgTexture(wallpath, 10, 3, 4, false, 0xFF, 0xFF, 0xFF);
	wall4 = loadImgTexture(wall4path, 10, 3, 4, false, 0xFF, 0xFF, 0xFF);
	pac = loadImgTexture(pacPath, 12, 4, 3, false, 0, 0, 0);
	pac2 = loadImgTexture(pac2Path, 12, 4, 3, false, 0, 0, 0);
	die = loadImgTexture(diePath, 13, 1, 13, false, 0, 0, 0);
	die2 = loadImgTexture(die2Path, 13, 1, 13, false, 0, 0, 0);
	ghost[0] = loadImgTexture(ghost1Path, 24, 3, 8, false, 0, 0, 0);
	ghost[1] = loadImgTexture(ghost2Path, 24, 3, 8, false, 0, 0, 0);
	ghost[2] = loadImgTexture(ghost3Path, 24, 3, 8, false, 0, 0, 0);
	ghost[3] = loadImgTexture(ghost4Path, 24, 3, 8, false, 0, 0, 0);
	images[0] = loadImgTexture(images1Path, 1, 1, 1, false, 255, 255, 255);
	images[1] = loadImgTexture(images2Path, 1, 1, 1, false, 255, 255, 255);
	images[2] = loadImgTexture(images3Path, 1, 1, 1, false, 255, 255, 255);
	images[3] = loadImgTexture(images4Path, 1, 1, 1, false, 255, 255, 255);
	images[4] = loadImgTexture(images5Path, 1, 1, 1, false, 255, 255, 255);
	images[5] = loadImgTexture(images6Path, 1, 1, 1, false, 255, 255, 255);
	for (int i = 0; i < 3; i++)
		lives[i] = loadImgTexture(pacPath, 12, 4, 3, false, 0, 0, 0);

	quit = false;
	status = MENU;
//	status = _3D;
	loadwall(map);
	time_animation = SDL_GetTicks();

	loadRank(r, &ranknum);
	sortRank(r, ranknum);
	updateRank(r);

	srand(time(NULL));

	SDL_StartTextInput();
	bool excdir[4];

	loadObjFile("3Dwall.obj", meshWall);
	loadObjFile("3Dghost.obj", meshGhost);
	loadObjFile("3Ddot.obj", meshDot);
	loadObjFile("3DBigdot.obj", meshBigdot);
	while (!quit)
	{
		mouseState = NONE;
		textFlag = false;
		while (SDL_PollEvent(&e) != 0)
		{
			mouseHandleEvent(&e, &mouseState, &mouseX, &mouseY);
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				dirr = (dir + 270) % 360;
				switch (e.key.keysym.sym)
				{
				case SDLK_LEFT:
					dirr += 180;
					if (!forwardFlag &&( map1[pacp.y][(pacp.x - 1 + N) % N] != 0 || map1[(pacp.y + pv.y + M) % M][(pacp.x - 1 + N) % N] != 0)) dir = 180;
					if (status == _3D)
						vCamera.x -= 1.0f;
					mv = { -1,0 };
					break;
				case SDLK_RIGHT:
					dirr += 0;
					if (!forwardFlag && (map1[pacp.y][(pacp.x + 1) % N] != 0 || map1[(pacp.y + pv.y + M) % M][(pacp.x + 1) % N] != 0)) dir = 0;
					if (status == _3D)
						vCamera.x += 1.0f;
					mv = { 1,0 };
					break;
				case SDLK_UP:
					dirr += 90;
					if (!forwardFlag && (map1[(pacp.y - 1 + M) % M][pacp.x] != 0 || map1[(pacp.y - 1 + M) % M][(pacp.x + pv.x + N) % N] != 0)) dir = 90;
					if (status == _3D)
						vCamera.y += 1.0f;
					mv = { 0,-1 };
					break;
				case SDLK_DOWN:
					dirr += 270;
					if (!forwardFlag && (map1[(pacp.y + 1) % M][pacp.x] != 0 || map1[(pacp.y + 1) % M][(pacp.x + pv.x + N) % N] != 0)) dir = 270;
					if (status == _3D)
						vCamera.y -= 1.0f;
					mv = { 0,1 };
					break;
				case SDLK_PLUS:
				case SDLK_EQUALS:
					volume += 4;
					if (volume > 128) volume = 128;
					break;
				case SDLK_MINUS:
					volume -= 4;
						if (volume < 0) volume = 0;
					break;
				}
				dirr %= 360;
				if (forwardFlag) {
					switch (dirr)
					{
					case 180:
						if (map1[pacp.y][(pacp.x - 1 + N) % N] != 0 || map1[(pacp.y + pv.y + M) % M][(pacp.x - 1 + N) % N] != 0) dir = 180;
						break;
					case 0:
						if (map1[pacp.y][(pacp.x + 1) % N] != 0 || map1[(pacp.y + pv.y + M) % M][(pacp.x + 1) % N] != 0) dir = 0;
						break;
					case 90:
						if (map1[(pacp.y - 1 + M) % M][pacp.x] != 0 || map1[(pacp.y - 1 + M) % M][(pacp.x + pv.x + N) % N] != 0) dir = 90;
						break;
					case 270:
						if (map1[(pacp.y + 1) % M][pacp.x] != 0 || map1[(pacp.y + 1) % M][(pacp.x + pv.x + N) % N] != 0) dir = 270;
						break;
					}
				}

				switch (e.key.keysym.sym)
				{
				case SDLK_a:
					if (map1[pacp2.y][(pacp2.x - 1 + N) % N] != 0 || map1[(pacp2.y + pv2.y + N) % M][(pacp2.x - 1 + N) % N] != 0) dir2 = 180; 
					if (status == _3D)
						fYaw += 30.0f;
					break;
				case SDLK_d:
					if (map1[pacp2.y][(pacp2.x + 1) % N] != 0 || map1[(pacp2.y + pv2.y + M) % M][(pacp2.x + 1) % N] != 0) dir2 = 0;
					if (status == _3D)
						fYaw -= 30.0f;
					break;
				case SDLK_w:
					if (map1[(pacp2.y - 1 + M) % M][pacp2.x] != 0 || map1[(pacp2.y - 1 + M) % M][(pacp2.x + pv2.x + N) % N] != 0) dir2 = 90;
					if (status == _3D)
						vCamera = Vector_Add(vCamera, vForward);
					break;
				case SDLK_s:
					if (map1[(pacp2.y + 1) % M][pacp2.x] != 0 || map1[(pacp2.y + 1) % M][(pacp2.x + pv2.x + N) % N] != 0) dir2 = 270;
					if (status == _3D)
						vCamera = Vector_Sub(vCamera, vForward);
					break;
				}
				if (e.key.keysym.sym == SDLK_BACKSPACE)
					if (strlen(inputString) > 1)
					{
						inputString[strlen(inputString) - 1] = '\0';
						textFlag = true;
					}
				if (e.key.keysym.sym == SDLK_KP_ENTER)
					if (status == ENTER_NAME && strcmp(inputString, " "))
					{
						loadRank(r, &ranknum);
						char* tmp = new char[20];
						tmp = strchr(inputString, inputString[1]);
						strcpy(r[ranknum].name, tmp);
						r[ranknum].score = score;
						ranknum++;
						sortRank(r, ranknum);
						updateRank(r);
						status = HIGHSCORE;
						time_animation = SDL_GetTicks();
					}
			}
			else if (e.type == SDL_TEXTINPUT)
			{
				if (strlen(inputString) < 19)
				{
					strcat_s(inputString, 20, e.text.text);
					textFlag = true;
				}
			}
			else if (e.type == SDL_MOUSEWHEEL)
			{
				if (enlargeFlag)
				{
					if (e.wheel.y > 0 && magnitude < 5)
						magnitude += 0.1;
					else if (e.wheel.y < 0 && magnitude>1)
						magnitude -= 0.1;
				}
			}
		}
		SDL_Rect fullview;
		fullview.x = 0;
		fullview.y = 0;
		fullview.w = WIDTH;
		fullview.h = HEIGHT;
		SDL_RenderSetViewport(renderer, &fullview);
		Mix_VolumeMusic(volume);
		if (status == SINGLE_1 || status == DOUBLE_1 || status == _3D) {
			if (eeat && Mix_Playing(1) == 0) {
				Mix_PlayChannel(1, chomp, 0);
				eeat = false;
			}
			if (period_frightened && !period_eatghost && Mix_PlayingMusic() == 0) {
				cout << "play_backtocenter\n";
				Mix_PlayMusic(backtocenter, -1);
			}
			if (passFlag)
				Mix_HaltMusic();
		}
		wallchange = (wallchange + 1) % 10;
		
		if (status == MENU) {
			drawAnimation();
			drawMenu();
		}
		else if (status == SELECT)
			drawSelect();
		else if (status == CONTROL)
			drawControl();
		else if (status == ABOUT)
			drawAbout();
		else if (status == HIGHSCORE)
			drawHighscore();
		else if (status == CREATE_MAP)
			drawcreatemap();
		else if (status == ENTER_NAME)
			drawEnterName();
		else if (status == SET)
			drawset();
		else if (status == READFILE)
			drawreadfile();
		else if (status == SINGLE_1)
			if (pauseFlag)
				drawPause();
			else
				drawClassic();
		else if (status == DOUBLE_1)
			if (pauseFlag)
				drawPause();
			else
				drawDouble();
		else if (status == _3D)
			if (pauseFlag)
				drawPause();
			else
				draw3D();
		SDL_Delay(slow);
//		printf("%d\n", SDL_GetTicks() - t);
		t = SDL_GetTicks();

		SDL_DestroyTexture(hint.texture);
		SDL_DestroyTexture(score_text.texture);
		for (int i = 0; i < 5; i++) {
			SDL_DestroyTexture(menu[i].texture);
		}
		for (int i = 0; i < 8; i++) {
			SDL_DestroyTexture(text[i].texture);
			SDL_DestroyTexture(set_sign[i].texture);
		}
	}

	SDL_DestroyTexture(pacman.texture);
	SDL_DestroyTexture(wall3.texture);
	SDL_DestroyTexture(wall.texture);
	SDL_DestroyTexture(wall4.texture);
	SDL_DestroyTexture(pac.texture);
	SDL_DestroyTexture(pac2.texture);
	SDL_DestroyTexture(die.texture);
	SDL_DestroyTexture(die2.texture);
	for(int i=0; i<4; i++)
		SDL_DestroyTexture(ghost[i].texture);
	for(int i=0; i<6; i++)
		SDL_DestroyTexture(images[i].texture);
	for (int i = 0; i < 3; i++)
		SDL_DestroyTexture(lives[i].texture);

	SDL_StopTextInput();
	closeSDL();

	return 0;
}

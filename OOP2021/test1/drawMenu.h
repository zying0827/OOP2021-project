void drawMenu()
{
	enlargeFlag = false;
	forwardFlag = false;
	slow = 0;
	int size[5] = { 30,30,30,30,30 };
	for (int i = 0; i < 5; i++)
		if (mouseX > menuPos[i].x - menu[i].width/2 && mouseX < menuPos[i].x + menu[i].width/2 && mouseY > menuPos[i].y - menu[i].height/2 && mouseY < menuPos[i].y + menu[i].height/2)
		{
			menuColor[i].r = 255;
			menuColor[i].g = 0;
			menuColor[i].b = 0;
			size[i] = 40;
			if (mouseState == LB_SC || mouseState == LB_DC)
			{

				switch (i)
				{
				case 0:
					status = SELECT;
					break;
				case 1:
					status = CONTROL;
					break;
				case 2:
					status = ABOUT;
					break;
				case 3:
					status = HIGHSCORE;
					break;
				case 4:
					status = CREATE_MAP;
	//				y_down = 0;
					mp = { 0,0 };
					for (int i = 0; i < M / 3; i++)
						for (int j = 0; j < N / 3; j++)
							m[i][j] = 0;
					button = 1;
					m[3][3] = 9;	m[3][4] = 5;	m[3][5] = 5;	m[3][6] = 12;
					m[4][3] = 10;	m[4][4] = 0;	m[4][5] = 0;	m[4][6] = 10;
					m[5][3] = 3;	m[5][4] = 5;	m[5][5] = 5;	m[5][6] = 6;

					bi.clear();
					break;
				}
			}
		}
		else
		{
			menuColor[i].r = 255;
			menuColor[i].g = 255;
			menuColor[i].b = 255;
			size[i] = 30;
		}

	menu[0] = loadTextTexture("START GAME", "../fonts/pac_font.ttf", size[0], menuColor[0].r, menuColor[0].g, menuColor[0].b, BLENDED, NULL, NULL, NULL);
	menu[1] = loadTextTexture("CONTROLS", "../fonts/pac_font.ttf", size[1], menuColor[1].r, menuColor[1].g, menuColor[1].b, BLENDED, NULL, NULL, NULL);
	menu[2] = loadTextTexture("ABOUT", "../fonts/pac_font.ttf", size[2], menuColor[2].r, menuColor[2].g, menuColor[2].b, BLENDED, NULL, NULL, NULL);
	menu[3] = loadTextTexture("HIGH SCORES", "../fonts/pac_font.ttf", size[3], menuColor[3].r, menuColor[3].g, menuColor[3].b, BLENDED, NULL, NULL, NULL);
	menu[4] = loadTextTexture("CREATE MAP", "../fonts/pac_font.ttf", size[4], menuColor[4].r, menuColor[4].g, menuColor[4].b, BLENDED, NULL, NULL, NULL);

	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(intermission, -1);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);
	imgRender(renderer, pacman, WIDTH / 2 - pacman.width / 2, 50, 0, NULL, NULL, NULL, no, 255, 1, 1);
	for (int i = 0; i < 5; i++)
		textRender(renderer, menu[i], menuPos[i].x - menu[i].width / 2, menuPos[i].y - menu[i].height / 2, NULL, NULL, NULL, no, 255);

	//SDL_RenderPresent(renderer);
}

void drawPause()
{
	pause_duration = SDL_GetTicks() - time_pause;
	if (pausedisplay) {
		SDL_Rect p = { 580, 80, 50, 50 };
		if (mouseX > p.x && mouseX < p.x + p.w && mouseY > p.y && mouseY < p.y + p.h)
			if (mouseState == LB_SC || mouseState == LB_DC)
			{
				pauseFlag = false;
				pausedisplay = false;
				if (Mix_PausedMusic() == 1)
					Mix_ResumeMusic();
				if (Mix_Paused(-1))
					Mix_Resume(-1);

				time_total_paused += pause_duration;
				pause_duration = 0;
			}
		imgRender(renderer, images[5], p.x, p.y, 0, NULL, NULL, NULL, no, 255, 1, 1);
		SDL_RenderPresent(renderer);
		return;
	}
	int size[5] = { 30,30,30,30,30 };
	if (mouseX > menuPos[1].x - menu[1].width / 2 && mouseX < menuPos[1].x + menu[1].width / 2 && mouseY > menuPos[1].y - 100 - menu[1].height / 2 && mouseY < menuPos[1].y - 100 + menu[1].height / 2)
	{
		menuColor[1].r = 255;
		menuColor[1].g = 0;
		menuColor[1].b = 0;
		size[1] = 40;
		if (mouseState == LB_SC || mouseState == LB_DC)
		{
			pauseFlag = false; 
			if (Mix_PausedMusic() == 1)
				Mix_ResumeMusic();
			if (Mix_Paused(-1))
				Mix_Resume(-1);
			time_total_paused += pause_duration;
			pause_duration = 0;
		}
	}
	else
	{
		menuColor[1].r = 255;
		menuColor[1].g = 255;
		menuColor[1].b = 255;
		size[1] = 30;
	}
	if (mouseX > menuPos[2].x - menu[2].width / 2 && mouseX < menuPos[2].x + menu[2].width / 2 && mouseY > menuPos[2].y - 75 - menu[2].height / 2 && mouseY < menuPos[2].y - 75 + menu[2].height / 2)
	{
		menuColor[2].r = 255;
		menuColor[2].g = 0;
		menuColor[2].b = 0;
		size[2] = 40;
		if (mouseState == LB_SC || mouseState == LB_DC)
		{
			map1 = map; //update
			live = 3;
			for (int i = 0; i < live; i++) {
				lives_alp[i] = 255;
			}
			score = 0;
			period_init = true;
			time_init = SDL_GetTicks();
			Mix_PlayMusic(beginning, 0);
			pause_duration = 0;
			time_total_paused = 0;
			pauseFlag = false;
		}
	}
	else
	{
		menuColor[2].r = 255;
		menuColor[2].g = 255;
		menuColor[2].b = 255;
		size[2] = 30;
	}
	if (mouseX > menuPos[4].x - menu[4].width / 2 && mouseX < menuPos[4].x + menu[4].width / 2 && mouseY > menuPos[4].y - 100 - menu[4].height / 2 && mouseY < menuPos[4].y - 100 + menu[4].height / 2)
	{
		menuColor[4].r = 255;
		menuColor[4].g = 0;
		menuColor[4].b = 0;
		size[4] = 40;
		if (mouseState == LB_SC || mouseState == LB_DC)
		{
			status = MENU;
			pauseFlag = false;
			Mix_HaltMusic();
			time_animation = SDL_GetTicks();
		}
	}
	else
	{
		menuColor[4].r = 255;
		menuColor[4].g = 255;
		menuColor[4].b = 255;
		size[4] = 30;
	}
	SDL_Rect s = { 200, 500, 300, 10 };
	if (mouseX > s.x && mouseX < s.x + s.w && mouseY > s.y - 15 && mouseY < s.y + s.h + 15) {
		if (mouseState == LB_SC || mouseState == LB_DC || e.type == SDL_MOUSEBUTTONDOWN) {
			slider[2] = 100 * (mouseX - s.x) / s.w + 1;
		}
	}
	SDL_Rect b = { s.x + (slider[2]) * (s.w / 100) - s.w / 200 - 5 , s.y - 10, 10, 30 };
	slow = slow_list[(slider[2] - 1) / 10];

	menu[0] = loadTextTexture("PAUSE", "../fonts/akabara-cinderella.ttf", 50, 255, 255, 255, BLENDED, NULL, NULL, NULL);
	menu[1] = loadTextTexture("continue", "../fonts/akabara-cinderella.ttf", size[1], menuColor[1].r, menuColor[1].g, menuColor[1].b, BLENDED, NULL, NULL, NULL);
	menu[2] = loadTextTexture("restart", "../fonts/akabara-cinderella.ttf", size[2], menuColor[2].r, menuColor[2].g, menuColor[2].b, BLENDED, NULL, NULL, NULL);
	menu[4] = loadTextTexture("exit", "../fonts/akabara-cinderella.ttf", size[4], menuColor[4].r, menuColor[4].g, menuColor[4].b, BLENDED, NULL, NULL, NULL);
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);

	char sign[2][100] = { "speed\0", "\0" };
	sprintf_s(sign[1], "%d", (slider[2] - 1) / 10 + 1);
	for (int i = 0; i < 2; i++) {
		set_sign[i] = loadTextTexture(sign[i], "../fonts/TaipeiSansTCBeta-Regular.ttf", 28, 255, 255, 255, SHADED, 0, 0, 0);
	}

	SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
	SDL_RenderFillRect(renderer, &s);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &b);
	textRender(renderer, menu[0], menuPos[0].x - menu[0].width / 2, 200 - menu[0].height / 2, NULL, NULL, NULL, no, 255);
	textRender(renderer, menu[1], menuPos[1].x - menu[1].width / 2, menuPos[1].y - 100 - menu[1].height / 2, NULL, NULL, NULL, no, 255);
	textRender(renderer, menu[2], menuPos[2].x - menu[2].width / 2, menuPos[2].y - 75 - menu[2].height / 2, NULL, NULL, NULL, no, 255);
	textRender(renderer, menu[4], menuPos[4].x - menu[4].width / 2, menuPos[4].y - 100 - menu[4].height / 2, NULL, NULL, NULL, no, 255);
	textRender(renderer, set_sign[0], 180 - set_sign[0].width, 490 , NULL, NULL, NULL, no, 255);
	textRender(renderer, set_sign[1], 520, 490 , NULL, NULL, NULL, no, 255);


	SDL_RenderPresent(renderer);
}

void drawSelect()
{
	slow = 0;
	int size[5] = { 30,30,30,30,30 };
	for (int i = 0; i < 5; i++)
	{
		if (mouseX > menuPos[i].x - menu[i].width / 2 && mouseX < menuPos[i].x + menu[i].width / 2 && mouseY > menuPos[i].y - menu[i].height / 2 && mouseY < menuPos[i].y + menu[i].height / 2)
		{
			menuColor[i].r = 255;
			menuColor[i].g = 0;
			menuColor[i].b = 0;
			size[i] = 40;
			if (mouseState == LB_SC || mouseState == LB_DC)
			{
				switch (i)
				{
				case 0:
					loadwall(map);
					status = SET;
					slider[0] = 50, slider[1] = 50, slider[2] = 50, slider[3] = 50;
					map1 = map;
					fail = true;
					stdwall(map1, map2);
					slider[2] = 50;
					mode = 1;
					break;
				case 1:
					loadwall(map);
					status = SET;
					slider[0] = 50, slider[1] = 50, slider[2] = 50, slider[3] = 50;
					map1 = map;
					fail = true;
					stdwall(map1, map2);
					slider[2] = 50;
					mode = 2;
					break;
				case 2:
					loadwall(map);
					Mix_PlayMusic(beginning, 0);
					map1 = map; //update
					live = 3;
					for (int i = 0; i < live; i++)
						lives_alp[i] = 255;
					score = 0;
					period_init = true;
					time_init = SDL_GetTicks();
					pauseFlag = false;
					pause_duration = 0;
					time_total_paused = 0;
					status = _3D;
					slider[2] = 99;
					break;
				case 4:
					status = MENU;
					time_animation = SDL_GetTicks();
				}
			}
		}
		else
		{
			menuColor[i].r = 255;
			menuColor[i].g = 255;
			menuColor[i].b = 255;
			size[i] = 30;
		}
	}
	menu[0] = loadTextTexture("one player", "../fonts/akabara-cinderella.ttf", size[0], menuColor[0].r, menuColor[0].g, menuColor[0].b, BLENDED, NULL, NULL, NULL);
	menu[1] = loadTextTexture("two players", "../fonts/akabara-cinderella.ttf", size[1], menuColor[1].r, menuColor[1].g, menuColor[1].b, BLENDED, NULL, NULL, NULL);
	menu[2] = loadTextTexture("3D", "../fonts/akabara-cinderella.ttf", size[2], menuColor[2].r, menuColor[2].g, menuColor[2].b, BLENDED, NULL, NULL, NULL);
	menu[3] = loadTextTexture(" ", "../fonts/akabara-cinderella.ttf", size[3], menuColor[3].r, menuColor[3].g, menuColor[3].b, BLENDED, NULL, NULL, NULL);
	menu[4] = loadTextTexture("Back to menu", "../fonts/akabara-cinderella.ttf", size[4], menuColor[4].r, menuColor[4].g, menuColor[4].b, BLENDED, NULL, NULL, NULL);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);

	imgRender(renderer, pacman, WIDTH / 2 - pacman.width / 2, 50, 0, NULL, NULL, NULL, no, 255, 1, 1);
	for (int i = 0; i < 5; i++)
		textRender(renderer, menu[i], menuPos[i].x - menu[i].width / 2, menuPos[i].y - menu[i].height / 2, NULL, NULL, NULL, no, 255);

	SDL_RenderPresent(renderer);
}

void drawControl()
{
	int size[5] = { 30,30,30,30,30 };
	if (mouseX > menuPos[4].x - menu[4].width / 2 && mouseX < menuPos[4].x + menu[4].width / 2 && mouseY > menuPos[4].y - menu[4].height / 2 && mouseY < menuPos[4].y + menu[4].height / 2)
	{
		menuColor[4].r = 255;
		menuColor[4].g = 0;
		menuColor[4].b = 0;
		size[4] = 40;
		if (mouseState == LB_SC || mouseState == LB_DC)
		{
			status = MENU;
			time_animation = SDL_GetTicks();
		}
	}
	else
	{
		menuColor[4].r = 255;
		menuColor[4].g = 255;
		menuColor[4].b = 255;
		size[4] = 30;
	}
	menu[0] = loadTextTexture("CONTROLS", "../fonts/akabara-cinderella.ttf", 30, 255, 255, 255, BLENDED, NULL, NULL, NULL);
	menu[4] = loadTextTexture("Back to menu", "../fonts/akabara-cinderella.ttf", size[4], menuColor[4].r, menuColor[4].g, menuColor[4].b, BLENDED, NULL, NULL, NULL);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);

	textRender(renderer, menu[0], 100, 100, NULL, NULL, NULL, no, 255);
	textRender(renderer, menu[4], menuPos[4].x - menu[4].width / 2, menuPos[4].y - menu[4].height / 2, NULL, NULL, NULL, no, 255);

	pv = { 1,0 };
	imgRender(renderer, pac, 125, 200, pacIndex[0], NULL, NULL, NULL, no, 255, 2, 2);
	pv2 = { 1,0 };
	imgRender(renderer, pac2, 475, 200, pac2Index[0], NULL, NULL, NULL, no, 255, 2, 2);

	roundedBoxRGBA(renderer, 120, 400, 180, 460, 10, 255, 255, 255, 255);
	roundedBoxRGBA(renderer, 120, 320, 180, 380, 10, 255, 255, 255, 255);
	roundedBoxRGBA(renderer, 40, 400, 100, 460, 10, 255, 255, 255, 255);
	roundedBoxRGBA(renderer, 200, 400, 260, 460, 10, 255, 255, 255, 255);

	Sint16 vx[4][3] = { { 140,150,160 },{ 140,150,160 },{ 80,60,80 },{ 220,240,220 } };
	Sint16 vy[4][3] = { { 360,340,360 },{ 420,440,420 },{ 420,430,440 },{ 420,430,440 } };
	filledPolygonRGBA(renderer, vx[0], vy[0], 3, 0, 0, 0, 255);
	filledPolygonRGBA(renderer, vx[1], vy[1], 3, 0, 0, 0, 255);
	filledPolygonRGBA(renderer, vx[2], vy[2], 3, 0, 0, 0, 255);
	filledPolygonRGBA(renderer, vx[3], vy[3], 3, 0, 0, 0, 255);

	roundedBoxRGBA(renderer, 470, 400, 530, 460, 10, 255, 255, 255, 255);
	roundedBoxRGBA(renderer, 470, 320, 530, 380, 10, 255, 255, 255, 255);
	roundedBoxRGBA(renderer, 550, 400, 610, 460, 10, 255, 255, 255, 255);
	roundedBoxRGBA(renderer, 390, 400, 450, 460, 10, 255, 255, 255, 255);

	TextData W = loadTextTexture("W", "../fonts/akabara-cinderella.ttf", 30, 0, 0, 0, BLENDED, NULL, NULL, NULL);
	TextData S = loadTextTexture("S", "../fonts/akabara-cinderella.ttf", 30, 0, 0, 0, BLENDED, NULL, NULL, NULL);
	TextData A = loadTextTexture("A", "../fonts/akabara-cinderella.ttf", 30, 0, 0, 0, BLENDED, NULL, NULL, NULL);
	TextData D = loadTextTexture("D", "../fonts/akabara-cinderella.ttf", 30, 0, 0, 0, BLENDED, NULL, NULL, NULL);
	textRender(renderer, W, 500 - W.width / 2, 350 - W.height / 2, NULL, NULL, NULL, no, 255);
	textRender(renderer, S, 500 - S.width / 2, 430 - S.height / 2, NULL, NULL, NULL, no, 255);
	textRender(renderer, A, 420 - A.width / 2, 430 - A.height / 2, NULL, NULL, NULL, no, 255);
	textRender(renderer, D, 580 - D.width / 2, 430 - D.height / 2, NULL, NULL, NULL, no, 255);

	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(W.texture);
	SDL_DestroyTexture(A.texture);
	SDL_DestroyTexture(S.texture);
	SDL_DestroyTexture(D.texture);
	
}

void drawAbout()
{
	int size = 30;
	if (mouseX > menuPos[4].x - menu[4].width/2 && mouseX < menuPos[4].x + menu[4].width/2 && mouseY > menuPos[4].y - menu[4].height/2 && mouseY < menuPos[4].y + menu[4].height/2)
	{
		menuColor[4].r = 255;
		menuColor[4].g = 0;
		menuColor[4].b = 0;
		size = 40;
		if (mouseState == LB_SC || mouseState == LB_DC)
		{
			status = MENU;
			time_animation = SDL_GetTicks();
		}
	}
	else
	{
		menuColor[4].r = 255;
		menuColor[4].g = 255;
		menuColor[4].b = 255;
		size = 30;
	}


	menu[0] = loadTextTexture("ABOUT", "../fonts/akabara-cinderella.ttf", 30, 255, 255, 255, BLENDED, NULL, NULL, NULL);
	menu[4] = loadTextTexture("Back to menu", "../fonts/akabara-cinderella.ttf", size, menuColor[4].r, menuColor[4].g, menuColor[4].b, BLENDED, NULL, NULL, NULL);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);

	textRender(renderer, menu[0], 100, 100, NULL, NULL, NULL, no, 255);
	textRender(renderer, menu[4], menuPos[4].x - menu[4].width / 2, menuPos[4].y - menu[4].height / 2, NULL, NULL, NULL, no, 255);

	SDL_RenderPresent(renderer);
}

void loadRank(Rank r[],int *ranknum)
{
	FILE* fp;
	fp = fopen("highscore.txt", "r");
	rewind(fp);
	int t = 0;
	while (fscanf_s(fp, "%s", r[t].name,100) != EOF)
	{
		fscanf_s(fp, "%d", &r[t].score);
		t++;
	}
	*ranknum = t;
}
void sortRank(Rank r[],int t)
{
	for (int i = 0; i < t - 1; i++)
		for (int j = i + 1; j < t; j++)
			if (r[i].score < r[j].score)
			{
				Rank tmp = r[i];
				r[i] = r[j];
				r[j] = tmp;
			}
}
void updateRank(Rank r[])
{
	FILE* fp = fopen("highscore.txt", "w");
	for (int i = 0; i < 5; i++)
		fprintf(fp, "%s %d\n", r[i].name, r[i].score);
	fclose(fp);
}
void drawHighscore()
{
	int size = 30;
	if (mouseX > menuPos[4].x - menu[4].width/2 && mouseX < menuPos[4].x + menu[4].width/2 && mouseY > menuPos[4].y-menu[4].height/2 && mouseY < menuPos[4].y + menu[4].height/2)
	{
		menuColor[4].r = 255;
		menuColor[4].g = 0;
		menuColor[4].b = 0;
		size = 40;
		if (mouseState == LB_SC || mouseState == LB_DC)
		{
			status = MENU;
			time_animation = SDL_GetTicks();
		}
	}
	else
	{
		menuColor[4].r = 255;
		menuColor[4].g = 255;
		menuColor[4].b = 255;
		size = 30;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);

	TextData rank_info;
	for (int i = 0; i < 5; i++)
	{
		rank_info = loadTextTexture(r[i].name, "../fonts/akabara-cinderella.ttf", 20, 255, 255, 255, BLENDED, NULL, NULL, NULL);
		textRender(renderer, rank_info, WIDTH / 4, 200 + 50 * i, NULL, NULL, NULL, no, 255);
		
		char score_str[100] = "\0";
		sprintf_s(score_str, "%d", r[i].score);
		rank_info = loadTextTexture(score_str, "../fonts/akabara-cinderella.ttf", 20, 255, 255, 255, BLENDED, NULL, NULL, NULL);
		textRender(renderer, rank_info, WIDTH * 3 / 4 , 200 + 50 * i, NULL, NULL, NULL, no, 255);
	}

	menu[0] = loadTextTexture("Highscores", "../fonts/akabara-cinderella.ttf", 50, 255, 255, 255, BLENDED, NULL, NULL, NULL);
	menu[4] = loadTextTexture("Back to menu", "../fonts/akabara-cinderella.ttf", size, menuColor[4].r, menuColor[4].g, menuColor[4].b, BLENDED, NULL, NULL, NULL);

	textRender(renderer, menu[0], WIDTH / 2 - menu[0].width / 2, 100, NULL, NULL, NULL, no, 255);
	textRender(renderer, menu[4], menuPos[4].x - menu[4].width / 2, menuPos[4].y - menu[4].height / 2, NULL, NULL, NULL, no, 255);

	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(rank_info.texture);
}

void drawEnterName()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseX > menuPos[4].x - menu[4].width / 2 && mouseX < menuPos[4].x + menu[4].width / 2 && mouseY > menuPos[4].y - menu[4].height / 2 && mouseY < menuPos[4].y + menu[4].height / 2)
	{
		menuColor[4].r = 255;
		menuColor[4].g = 0;
		menuColor[4].b = 0;

		if (mouseState == LB_SC || mouseState == LB_DC )
		{
			loadRank(r, &ranknum);
			char* tmp = new char[20];
			tmp= strchr(inputString, inputString[1]); //remove space at inputString[0]
			strcpy(r[ranknum].name, tmp);
			r[ranknum].score = score;
			ranknum++;
			sortRank(r, ranknum);
			updateRank(r);
			status = HIGHSCORE;
			time_animation = SDL_GetTicks();
		}
	}
	else
	{
		menuColor[4].r = 255;
		menuColor[4].g = 255;
		menuColor[4].b = 255;
	}
	TextData text = loadTextTexture(inputString, "../fonts/lazy.ttf", 30, 255, 200, 14, BLENDED, NULL, NULL, NULL);

	if (textFlag)
	{
		if (strcmp(inputString, "") != 0)
			text = loadTextTexture(inputString, "../fonts/lazy.ttf", 30, 255, 200, 14, BLENDED, NULL, NULL, NULL);
		else
			text = loadTextTexture(" ", "../fonts/lazy.ttf", 30, 255, 200, 14, BLENDED, NULL, NULL, NULL);
	}
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer); 
	menu[0] = loadTextTexture("Enter your name: ", "../fonts/akabara-cinderella.ttf", 30, 255, 255, 255, BLENDED, NULL, NULL, NULL);
	menu[4] = loadTextTexture("Enter", "../fonts/akabara-cinderella.ttf", 30, menuColor[4].r, menuColor[4].g, menuColor[4].b, BLENDED, NULL, NULL, NULL);
	textRender(renderer, menu[0], WIDTH / 2 - menu[0].width / 2, 100, NULL, NULL, NULL, no, 255);
	textRender(renderer, text, WIDTH / 2 - text.width / 2, 200, NULL, NULL, NULL, no, 255);
	textRender(renderer, menu[4], menuPos[4].x - menu[4].width / 2, menuPos[4].y - menu[4].height / 2, NULL, NULL, NULL, no, 255);

	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(text.texture);
}

void drawAnimation()
{
	// t5 : start time
	int timer = (SDL_GetTicks() - time_animation) % 38000;

	for (int i = 0; i < 4; i++)
	{
		gv[i] = { 1,0 };
	}

	pac_alp = 255;
	int ghost_alpha[4] = { 255,255,255,255 };
	hint_alp = 0;
	hint = loadTextTexture("BLINKY", "../fonts/pac_font.ttf", 20, 255, 0, 0, BLENDED, NULL, NULL, NULL);

	pacc = { 240, 250 };
	ghostc[0] = { 190, 250 };
	ghostc[1] = { 160, 250 };
	ghostc[2] = { 130, 250 };
	ghostc[3] = { 100, 250 };


	if (timer >= 1000 && timer < 4900)
	{
		pv = { 1,0 };
		for (int i = 0; i < 4; i++)
		{
			gv[i] = { 1,0 };
			ghost_frightened[i] = false;
			ghost_eaten[i] = false;
			ghost_eatening[i] = false;
		}
		pacc.x = 240 + ((timer - 1000) / 10);
		ghostc[0].x = 190 + ((timer - 1000) / 10);
		ghostc[1].x = 160 + ((timer - 1000) / 10);
		ghostc[2].x = 130 + ((timer - 1000) / 10);
		ghostc[3].x = 100 + ((timer - 1000) / 10);
	}
	else if (timer >= 4900 && timer < 10200)
	{
		pv = { -1,0 };
		for (int i = 0; i < 4; i++)
		{
			gv[i] = { -1,0 };
			ghost_frightened[i] = true;
		}
		pacc.x = 630 - ((timer - 4900) / 10);
		ghostc[0].x = 580 - ((timer - 4900) / 15);
		ghostc[1].x = 550 - ((timer - 4900) / 15);
		ghostc[2].x = 520 - ((timer - 4900) / 15);
		ghostc[3].x = 490 - ((timer - 4900) / 15);
//		t = SDL_GetTicks();
		pacp = { pacc.x / 15, pacc.y / 15 };
		for (int i = 0; i < 4; i++)
		{
			ghostp[i].x = ghostc[i].x / 15;
			ghostp[i].y = ghostc[i].y / 15;
			if (pacc.x - ghostc[i].x < 15 && !ghost_eaten[i])
			{
				ghost_eaten[i] = true;
				ghost_eatening[i] = true;
//				t2 = SDL_GetTicks();
				cnt++;
			}
		}
		if (timer > 6500)
			ghost_alpha[0] = 0;
		if (timer > 7400)
			ghost_alpha[1] = 0;
		if (timer > 8300)
			ghost_alpha[2] = 0;
		if (timer > 9200)
			ghost_alpha[3] = 0;
	}
	else if (timer >= 10500 && timer < 14500)
	{
		for (int i = 0; i < 4; i++) {
			ghost_frightened[i] = false;
			ghost_eaten[i] = false;
			ghost_eatening[i] = false;
		}
			
		pac_alp = 0;
		ghost_alpha[0] = 255;
		ghost_alpha[1] = 0;
		ghost_alpha[2] = 0;
		ghost_alpha[3] = 0;
		ghostc[0].x = 100 + ((timer - 10500) / 10);
	}
	else if (timer >= 14500 && timer < 16500)
	{
		hint = loadTextTexture("BLINKY", "../fonts/TaipeiSansTCBeta-Regular.ttf", 24, 255, 0, 0, BLENDED, NULL, NULL, NULL);
		hint_alp = 255;
		pac_alp = 0;
		ghost_alpha[0] = 255;
		ghost_alpha[1] = 0;
		ghost_alpha[2] = 0;
		ghost_alpha[3] = 0;
		ghostc[0].x = 500;
	}
	else if (timer >= 16500 && timer < 20500)
	{
		hint_alp = 0;
		pac_alp = 0;
		ghost_alpha[0] = 255;
		ghost_alpha[1] = 255;
		ghost_alpha[2] = 0;
		ghost_alpha[3] = 0;
		ghostc[0].x = 500 + ((timer - 16500) / 10);
		ghostc[1].x = 100 + ((timer - 16500) / 10);
	}
	else if (timer >= 20500 && timer < 22500)
	{
		hint = loadTextTexture("PINKY", "../fonts/TaipeiSansTCBeta-Regular.ttf", 24, 252, 181, 255, BLENDED, NULL, NULL, NULL);
		hint_alp = 255;
		pac_alp = 0;
		ghost_alpha[0] = 0;
		ghost_alpha[1] = 255;
		ghost_alpha[2] = 0;
		ghost_alpha[3] = 0;
		ghostc[1].x = 500;
	}
	else if (timer >= 22500 && timer < 26500)
	{
		hint_alp = 0;
		pac_alp = 0;
		ghost_alpha[0] = 0;
		ghost_alpha[1] = 255;
		ghost_alpha[2] = 255;
		ghost_alpha[3] = 0;
		ghostc[1].x = 500 + ((timer - 22500) / 10);
		ghostc[2].x = 100 + ((timer - 22500) / 10);
	}
	else if (timer >= 26500 && timer < 28500)
	{
		hint = loadTextTexture("INKY", "../fonts/TaipeiSansTCBeta-Regular.ttf", 24, 0, 255, 255, BLENDED, NULL, NULL, NULL);
		hint_alp = 255;
		pac_alp = 0;
		ghost_alpha[0] = 0;
		ghost_alpha[1] = 0;
		ghost_alpha[2] = 255;
		ghost_alpha[3] = 0;
		ghostc[2].x = 500;
	}
	else if (timer >= 28500 && timer < 32500)
	{
		hint_alp = 0;
		pac_alp = 0;
		ghost_alpha[0] = 0;
		ghost_alpha[1] = 0;
		ghost_alpha[2] = 255;
		ghost_alpha[3] = 255;
		ghostc[2].x = 500 + ((timer - 28500) / 10);
		ghostc[3].x = 100 + ((timer - 28500) / 10);
	}
	else if (timer >= 32500 && timer < 34500)
	{
		hint = loadTextTexture("CLYDE", "../fonts/TaipeiSansTCBeta-Regular.ttf", 24, 247, 187, 85, BLENDED, NULL, NULL, NULL);
		hint_alp = 255;
		pac_alp = 0;
		ghost_alpha[0] = 0;
		ghost_alpha[1] = 0;
		ghost_alpha[2] = 0;
		ghost_alpha[3] = 255;
		ghostc[3].x = 500;
	}
	else if (timer >= 34500 && timer < 36500)
	{
		hint_alp = 0;
		pac_alp = 0;
		ghost_alpha[0] = 0;
		ghost_alpha[1] = 0;
		ghost_alpha[2] = 0;
		ghost_alpha[3] = 255;
		ghostc[3].x = 500 + ((timer - 34500) / 10);
	}
	else if (timer >= 36500)
	{
		cnt = 0;
		pac_alp = 0;
		for (int i = 0; i < 4; i++)
			ghost_alpha[i] = 0;
		hint_alp = 0;
	}
	else
	{
		pac_alp = 0;
		for (int i = 0; i < 4; i++)
			ghost_alpha[i] = 0;
		hint_alp = 0;
	}
	imgRender(renderer, wall, 640 - 180, 257, timer > 4900 ? 0 : 8, NULL, NULL, NULL, no, 255, 1, 1); // the dot
	imgRender(renderer, pac, pacc.x - 180, pacc.y, pacIndex[0], NULL, NULL, NULL, no, pac_alp, 1, 1);
	imgRender(renderer, ghost[0], ghostc[0].x - 190, ghostc[0].y, ghostIndex[0], NULL, NULL, NULL, no, ghost_alpha[0], 1, 1);
	imgRender(renderer, ghost[1], ghostc[1].x - 190, ghostc[1].y, ghostIndex[1], NULL, NULL, NULL, no, ghost_alpha[1], 1, 1);
	imgRender(renderer, ghost[2], ghostc[2].x - 190, ghostc[2].y, ghostIndex[2], NULL, NULL, NULL, no, ghost_alpha[2], 1, 1);
	imgRender(renderer, ghost[3], ghostc[3].x - 190, ghostc[3].y, ghostIndex[3], NULL, NULL, NULL, no, ghost_alpha[3], 1, 1);
	textRender(renderer, hint, 400-155-hint.width/2, 264-hint.height / 2, NULL, NULL, NULL, no, hint_alp);
	SDL_RenderPresent(renderer);
}
void drawset()
{
	textPos[0] = { WIDTH / 5, 660 };
	textPos[1] = { 4 * WIDTH / 5, 660 };
	textPos[2] = { 2 * WIDTH / 5, 660 };
	textPos[3] = { 3 * WIDTH / 5, 660 };
	textPos[4] = { WIDTH / 2, 2 * HEIGHT / 5 };
	textPos[5] = { WIDTH / 2, 2 * HEIGHT / 5 };
	textPos[6] = { WIDTH / 2, 2 * HEIGHT / 5 };
	textPos[7] = { WIDTH / 2, 2 * HEIGHT / 5 };
	textColor[4] = { 25, 225, 25 };
	textColor[5] = { 225, 225, 25 };
	textColor[6] = { 225, 25, 25 };
	textColor[7] = { 25, 225, 25 };
	static int tips = 0;
	bool repeat;
	int size[8] = { 30,30,30,30, 100, 100, 100, 100};
	for (int i = 0; i < 4; i++) {
		if (mouseX > textPos[i].x - text[i].width / 2 && mouseX < textPos[i].x + text[i].width / 2 && mouseY > textPos[i].y - text[i].height / 2 && mouseY < textPos[i].y + text[i].height / 2)
		{
			textColor[i].r = 255;
			textColor[i].g = 0;
			textColor[i].b = 0;
			size[i] = 40;
			if (mouseState == LB_SC || mouseState == LB_DC)
			{
				switch (i)
				{
				case 0:
					status = SELECT;
					break;
				case 1:
					if (mode == 1) {
						Mix_PlayMusic(beginning, 0);
						map1 = map; //update
						live = 3;
						for (int i = 0; i < live; i++) {
							lives_alp[i] = 255;
						}
						score = 0;
						period_init = true;
						time_init = SDL_GetTicks();
						pauseFlag = false;
						pause_duration = 0;
						time_total_paused = 0;
						status = SINGLE_1;
						enlargeFlag = false;
						forwardFlag = false;

						initpac = { 16 * l_grid + l_grid / 2, 22 * l_grid + l_grid / 2 };
						ghostc[0] = { 15 * l_grid, (10 + y_down) * l_grid + l_grid / 2 };
						while(map1[initpac.y/l_grid][initpac.x/l_grid]==0 || dist(initpac, ghostc[0], l_grid*l_grid*40)){
							initpac = { (rand() % 30) * l_grid + l_grid/2, (rand() % 33) *l_grid + l_grid/2 };
						}
					}
					else if (mode == 2) {
						Mix_PlayMusic(beginning, 0);
						map1 = map; //update
						live = 3;
						for (int i = 0; i < live; i++) {
							lives_alp[i] = 255;
						}
						score = 0;
						period_init = true;
						time_init = SDL_GetTicks();
						pauseFlag = false;
						pause_duration = 0;
						time_total_paused = 0;
						status = DOUBLE_1;
						enlargeFlag = false;
						forwardFlag = false;

						initpac = { 16 * l_grid + l_grid / 2, 22 * l_grid + l_grid / 2 };
						initpac2 = { 16 * l_grid + l_grid / 2, 4 * l_grid + l_grid / 2 };
						ghostc[0] = { 15 * l_grid, (10 + y_down) * l_grid + l_grid / 2 };
						while (map1[initpac.y / l_grid][initpac.x / l_grid] == 0 || dist(initpac, ghostc[0], l_grid * l_grid * 40)) {
							initpac = { (rand() % 30) * l_grid + l_grid / 2, (rand() % 33) * l_grid + l_grid / 2 };
						}
						while (map1[initpac2.y / l_grid][initpac2.x / l_grid] == 0 || dist(initpac2, ghostc[0], l_grid * l_grid * 40)) {
							initpac2 = { (rand() % 30) * l_grid + l_grid / 2, (rand() % 33) * l_grid + l_grid / 2 };
						}
					}
					break;
				case 2:
					int ma[M][N];
					repeat = false;
					fp1 = fopen("files.dat", "rb");
					while (!feof(fp1) && !repeat) {
						cout << "repeat\n";
						tips = 5;
						repeat = true;
						for (int i = 0; i < M && repeat; i++) {
							for (int j = 0; j < N && repeat; j++) {
								fread(&(ma[i][j]), sizeof(int), 1, fp1);
								if (map1[i][j] != ma[i][j]) {
									repeat = false;
									fseek(fp1, sizeof(int) * (M * N - i * N - j - 2), SEEK_CUR);
								}
							}
						}
						fread(&(ma[0][0]), sizeof(int), 1, fp1);
					}
					fclose(fp1);
					if (!repeat) {
						cout << "save" << endl;
						tips = 4;
						fp1 = fopen("files.dat", "ab");
						for (int i = 0; i < M; i++) {
							for (int j = 0; j < N; j++) {
								fwrite(&(map1[i][j]), sizeof(int), 1, fp1);
							}
						}
						fclose(fp1);
					}
					alpha = 225;
					break;
				case 3:
					status = READFILE;
					fp1 = fopen("files.dat", "rb");
					for (int i = 0; i < 20; i++) {
						filenum = i;
						for (int j = 0; j < M; j++) {
							for (int k = 0; k < N; k++) {
								if (!feof(fp1))
									fread(&(files[i][j][k]), sizeof(int), 1, fp1);
								else {
									i = 20, j = M;
									break;
								}
							}
						}
					}
					fclose(fp1);
					fileorder = 0;
					fileaimpos = 0;
					filepos = 0;
				}
			}
		}
		else
		{
			textColor[i].r = 255;
			textColor[i].g = 255;
			textColor[i].b = 255;
			size[i] = 30;
		}
	}
	text[0] = loadTextTexture("back", "../fonts/akabara-cinderella.ttf", size[0], textColor[0].r, textColor[0].g, textColor[0].b, BLENDED, NULL, NULL, NULL);
	text[1] = loadTextTexture("next", "../fonts/akabara-cinderella.ttf", size[1], textColor[1].r, textColor[1].g, textColor[1].b, BLENDED, NULL, NULL, NULL);
	text[2] = loadTextTexture("save", "../fonts/akabara-cinderella.ttf", size[2], textColor[2].r, textColor[2].g, textColor[2].b, BLENDED, NULL, NULL, NULL);
	text[3] = loadTextTexture("file", "../fonts/akabara-cinderella.ttf", size[3], textColor[3].r, textColor[3].g, textColor[3].b, BLENDED, NULL, NULL, NULL);
	text[4] = loadTextTexture("saved", "../fonts/akabara-cinderella.ttf", size[4], textColor[4].r, textColor[4].g, textColor[4].b, BLENDED, NULL, NULL, NULL);
	text[5] = loadTextTexture("repeated", "../fonts/akabara-cinderella.ttf", size[5], textColor[5].r, textColor[5].g, textColor[5].b, BLENDED, NULL, NULL, NULL);
	text[6] = loadTextTexture("fail", "../fonts/akabara-cinderella.ttf", size[6], textColor[6].r, textColor[6].g, textColor[6].b, BLENDED, NULL, NULL, NULL);
	text[7] = loadTextTexture("success", "../fonts/akabara-cinderella.ttf", size[7], textColor[7].r, textColor[7].g, textColor[7].b, BLENDED, NULL, NULL, NULL);

	SDL_Rect s[4] = { {150, 450, 400, 10}, {150, 500, 400, 10}, {150, 550, 400, 10}, {150, 600, 400, 10} };
	SDL_Rect b[4];
	for (int i = 0; i < 4; i++) {
		if (mouseX > s[i].x && mouseX < s[i].x + s[i].w && mouseY > s[i].y - 15 && mouseY < s[i].y + s[i].h + 15) {
			if (mouseState == LB_SC || mouseState == LB_DC || e.type == SDL_MOUSEBUTTONDOWN) {
				slider[i] = 100 * (mouseX - s[i].x) / s[i].w +1  ;
			}
		}
		b[i] = { s[i].x + (slider[i]) * (s[i].w / 100) - s[i].w / 200 -5 , s[i].y - 10, 10, 30 };
	}
	slow = slow_list[(slider[2] - 1) / 10];
	char sign[8][100] = { "diameter\0", "two-way", "speed\0", "big dot\0", "\0", "\0", "\0", "\0" };
	for (int i = 0; i < 3; i++) {
		sprintf_s(sign[i + 4], "%d", (slider[i]-1)/10+1);
	}
	sprintf_s(sign[7], "%d", (slider[3] - 1) / 10);
	for (int i = 0; i < 8; i++) {
		set_sign[i] = loadTextTexture(sign[i], "../fonts/TaipeiSansTCBeta-Regular.ttf", 24, 255, 255, 255, SHADED, 0, 0, 0);
	}
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);
	/*
	for (int i = 0; i < 12; i++) {
		cout << length_list[i] << " " << lop_list[i] << endl;
	}
	SDL_Delay(10000);
	*/
	SDL_SetRenderDrawColor(renderer, 0x10, 0x60, 0x10, 0xFF);
	SDL_Rect p={ 550, 350, 50, 50 };
	fail = true;
	if (mouseX > p.x && mouseX < p.x + p.w && mouseY > p.y && mouseY < p.y + p.h) {
		SDL_SetRenderDrawColor(renderer, 0x30, 0xC0, 0x30, 0xFF);
		produ = 0;
		if (mouseState == LB_SC || mouseState == LB_DC) {
			cout << endl;
			fail = false;
			do
			{
				generateRandWall(map);
				if (validMap) check_map(map);
				if (produ > 999) {
					fail = true;
					cout << "fail\n";
					tips = 6;
					alpha = 255;
					break;
				}
				produ++;
				cout << produ <<". diameter: "<< length << "  two-way: " << lop << endl;
			} while (!validMap || length <= length_list[(slider[0]-1)/10] || length > length_list[(slider[0]-1)/10 +3] || lop <= lop_list[(slider[1]-1)/10] || lop > lop_list[(slider[1] - 1) / 10 +3]);
			big_sign = 0;
		}
	}
	if (!fail) {
		map1 = map;
		tips = 7;
		alpha = 255;
		stdwall(map1, map2);
	}
	double mag = 0.7;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			imgRender(renderer, wall, 120 + j * l_grid * mag, 15 + i * l_grid * mag, map2[i][j], NULL, NULL, NULL, no, 255, mag, mag);


	SDL_RenderFillRect(renderer, &p);

	SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
	SDL_RenderFillRects(renderer, s, 4);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRects(renderer, b, 4);

	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(intermission, -1);

	for (int i = 0; i < 4; i++) {
		textRender(renderer, set_sign[i], WIDTH / 5 - set_sign[i].width, 440 + 50*i , NULL, NULL, NULL, no, 255);
		textRender(renderer, set_sign[i+4], 9*WIDTH / 10 , 440 + 50*i, NULL, NULL, NULL, no, 255);
	}

	for (int i = 0; i < 4; i++)
		textRender(renderer, text[i], textPos[i].x - text[i].width / 2, textPos[i].y - text[i].height / 2, NULL, NULL, NULL, no, 255);
	if(tips>0) textRender(renderer, text[tips], textPos[tips].x - text[tips].width / 2, textPos[tips].y - text[tips].height / 2, NULL, NULL, NULL, no, alpha);
	SDL_RenderPresent(renderer);
}

void drawreadfile() {
	textPos[0] = { WIDTH / 4, 650 };
	textPos[1] = { 3 * WIDTH / 4, 650 };
	textPos[2] = { 2 * WIDTH / 4, 650 };
	textPos[3] = { WIDTH / 2, 2 * HEIGHT / 5 };
	int size[4] = {30,30,30,100};

	for (int i = 0; i < 3; i++) {
		if (mouseX > textPos[i].x - text[i].width / 2 && mouseX < textPos[i].x + text[i].width / 2 && mouseY > textPos[i].y - text[i].height / 2 && mouseY < textPos[i].y + text[i].height / 2)
		{
			textColor[i].r = 255;
			textColor[i].g = 0;
			textColor[i].b = 0;
			size[i] = 40;
			if (mouseState == LB_SC || mouseState == LB_DC)
			{
				switch (i)
				{
				case 0:
					status = SET;
					break;
				case 1:
					for (int i = 0; i < M; i++) {
						for (int j = 0; j < N; j++) {
							cout << map1[i][j] << " ";
						}
						cout << endl;
					}
					if (mode == 1) {
						Mix_PlayMusic(beginning, 0);
						live = 3;
						for (int i = 0; i < live; i++) {
							lives_alp[i] = 255;
						}
						score = 0;
						period_init = true;
						time_init = SDL_GetTicks();
						pauseFlag = false;
						pause_duration = 0;
						time_total_paused = 0;
						status = SINGLE_1;
						enlargeFlag = false;
						forwardFlag = false;

						initpac = { 16 * l_grid + l_grid / 2, 22 * l_grid + l_grid / 2 };
						ghostc[0] = { 15 * l_grid, (10 + y_down) * l_grid + l_grid / 2 };
						while (map1[initpac.y / l_grid][initpac.x / l_grid] == 0 || dist(initpac, ghostc[0], l_grid * l_grid * 40)) {
							initpac = { (rand() % 30) * l_grid + l_grid / 2, (rand() % 33) * l_grid + l_grid / 2 };
						}
					}
					else if (mode == 2) {
						Mix_PlayMusic(beginning, 0);
						live = 3;
						for (int i = 0; i < live; i++) {
							lives_alp[i] = 255;
						}
						score = 0;
						period_init = true;
						time_init = SDL_GetTicks();
						pauseFlag = false;
						pause_duration = 0;
						time_total_paused = 0;
						status = DOUBLE_1;
						enlargeFlag = false;
						forwardFlag = false;

						initpac = { 16 * l_grid + l_grid / 2, 22 * l_grid + l_grid / 2 };
						initpac2 = { 16 * l_grid + l_grid / 2, 4 * l_grid + l_grid / 2 };
						ghostc[0] = { 15 * l_grid, (10 + y_down) * l_grid + l_grid / 2 };
						while (map1[initpac.y / l_grid][initpac.x / l_grid] == 0 || dist(initpac, ghostc[0], l_grid * l_grid * 40)) {
							initpac = { (rand() % 30) * l_grid + l_grid / 2, (rand() % 33) * l_grid + l_grid / 2 };
						}
						while (map1[initpac2.y / l_grid][initpac2.x / l_grid] == 0 || dist(initpac2, ghostc[0], l_grid * l_grid * 40)) {
							initpac2 = { (rand() % 30) * l_grid + l_grid / 2, (rand() % 33) * l_grid + l_grid / 2 };
						}
					}
					break;
				case 2:
					int ord;
					int trash;
					fp1 = fopen("files.dat", "rb");
					fseek(fp1, sizeof(int) * (M * N * (fileorder + 1) - 1), SEEK_SET);
					fread(&trash, sizeof(int), 1, fp1);
					ord = fileorder;
					while (!feof(fp1)) {
						for (int i = 0; i < M; i++) {
							for (int j = 0; j < N; j++) {
								fread(&(files[ord][i][j]), sizeof(int), 1, fp1);
							}
						}
						ord++;
					}
					fclose(fp1);

					filenum--;
					if (fileorder >= filenum && filenum>0) {
						fileorder--;
						fileaimpos -= (int)((N + 4) * 0.8 * l_grid);
					}
					remove("files.dat");
					fp1 = fopen("files.dat", "wb");
					for (int i = 0; i < filenum; i++) {
						for (int j = 0; j < M; j++) {
							for (int k = 0; k < N; k++) {
								fwrite(&(files[i][j][k]), sizeof(int), 1, fp1);
							}
						}
					}
					fclose(fp1);
					alpha = 225;
					break;
				}
			}
		}
		else
		{
			textColor[i].r = 255;
			textColor[i].g = 255;
			textColor[i].b = 255;
			size[i] = 30;
		}
	}
	textColor[3] = { 225, 25, 25 };
	text[0] = loadTextTexture("back", "../fonts/akabara-cinderella.ttf", size[0], textColor[0].r, textColor[0].g, textColor[0].b, BLENDED, NULL, NULL, NULL);
	text[1] = loadTextTexture("next", "../fonts/akabara-cinderella.ttf", size[1], textColor[1].r, textColor[1].g, textColor[1].b, BLENDED, NULL, NULL, NULL);
	text[2] = loadTextTexture("delete", "../fonts/akabara-cinderella.ttf", size[2], textColor[2].r, textColor[2].g, textColor[2].b, BLENDED, NULL, NULL, NULL);
	text[3] = loadTextTexture("deleted", "../fonts/akabara-cinderella.ttf", size[3], textColor[3].r, textColor[3].g, textColor[3].b, BLENDED, NULL, NULL, NULL);


	double mag = 0.8;
	SDL_Rect view1;
	view1.x = 60;
	view1.y = 30;
	view1.w = (N+6) * mag * l_grid;
	view1.h = M * mag * l_grid;
	SDL_RenderSetViewport(renderer, &view1);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);

	for (int k = -1; k <= 1; k++) {
		if (k + fileorder >= 0 && k+fileorder<filenum) {
			stdwall(files[k + fileorder], map2);
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < N; j++) {
					imgRender(renderer, wall, (fileorder + k) * (N + 4) * mag * l_grid - filepos + (3 + j) * mag * l_grid, i * l_grid * mag, map2[i][j], NULL, NULL, NULL, no, 255, mag, mag);
				}
			}
		}
	}
	cout << filenum <<" "<< fileorder << " " << fileaimpos << " " << filepos << endl;
	map = map1 = files[fileorder];
	stdwall(map1, map2);

	SDL_Rect fullview;
	fullview.x = 0;
	fullview.y = 0;
	fullview.w = WIDTH;
	fullview.h = HEIGHT;
	SDL_RenderSetViewport(renderer, &fullview);

	SDL_Rect d[2] = { { 10,200, 40, 40 }, { 75 + (N + 6) * mag * l_grid, 200, 40, 40 } };

	for (int i = 0; i < 2; i++) {
		if (mouseX > d[i].x && mouseX < d[i].x + d[i].w && mouseY > d[i].y && mouseY < d[i].y + d[i].h) {
			SDL_SetRenderDrawColor(renderer, 0xC0, 0xC0, 0x30, 0xFF);
			if (mouseState == LB_SC || mouseState == LB_DC) {
				switch (i)
				{
				case 0:
					if (fileorder > 0) {
						fileorder--;
						fileaimpos -= (int)((N + 4) * mag * l_grid);
					}
					break;
				case 1:
					if (fileorder < filenum-1 ) {
						fileorder++;
						fileaimpos += (int)((N + 4) * mag * l_grid);
					}
					break;
				}
			}
		}
	}

	if (e.type == SDL_KEYDOWN  && e.key.repeat == 0) {
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			if (fileorder > 0 && filepos - fileaimpos < (int)((N/2) * mag * l_grid)) {
				fileorder--;
				fileaimpos -= (int)((N + 4) * mag * l_grid);
			}
			break;
		case SDLK_RIGHT:
			if (fileorder < filenum - 1 && fileaimpos - filepos < (int)((N / 2) * mag * l_grid)) {
				fileorder++;
				fileaimpos += (int)((N + 4) * mag * l_grid);
			}
			break;
		}
	}

	SDL_SetRenderDrawColor(renderer, 0x50, 0xC0, 0x50, 0xFF);
	SDL_RenderFillRects(renderer, d, 2);
	filledTrigonRGBA(renderer, d[0].x + 10, d[0].y + 20, d[0].x + 30, d[0].y + 30, d[0].x + 30, d[0].y + 10, 0, 0, 0, 225);
	filledTrigonRGBA(renderer, d[1].x + 10, d[1].y + 10, d[1].x + 10, d[1].y + 30, d[1].x + 30, d[1].y + 20, 0, 0, 0, 225);

	for (int i = 0; i < 3; i++)
		textRender(renderer, text[i], textPos[i].x - text[i].width / 2, textPos[i].y - text[i].height / 2, NULL, NULL, NULL, no, 255);
	
	if (Mix_PlayingMusic() == 0)
		Mix_PlayMusic(intermission, -1);

	SDL_Rect s = { 200, 580, 300, 10 };
	if (mouseX > s.x && mouseX < s.x + s.w && mouseY > s.y - 15 && mouseY < s.y + s.h + 15) {
		if (mouseState == LB_SC || mouseState == LB_DC || e.type == SDL_MOUSEBUTTONDOWN) {
			slider[2] = 100 * (mouseX - s.x) / s.w + 1;
		}
	}
	SDL_Rect b = { s.x + (slider[2]) * (s.w / 100) - s.w / 200 - 5 , s.y - 10, 10, 30 };
	slow = slow_list[(slider[2] - 1) / 10];

	char sign[2][100] = { "speed\0", "\0" };
	sprintf_s(sign[1], "%d", (slider[2] - 1) / 10 + 1);
	for (int i = 0; i < 2; i++) {
		set_sign[i] = loadTextTexture(sign[i], "../fonts/TaipeiSansTCBeta-Regular.ttf", 28, 255, 255, 255, SHADED, 0, 0, 0);
	}

	SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
	SDL_RenderFillRect(renderer, &s);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &b);
	textRender(renderer, set_sign[0], 180 - set_sign[0].width, 570, NULL, NULL, NULL, no, 255);
	textRender(renderer, set_sign[1], 520, 570, NULL, NULL, NULL, no, 255);

	if (filenum <= 14) {
		for (int i = 0; i < filenum; i++) {
			if (i == fileorder)
				filledCircleColor(renderer, WIDTH / 2 - 150 + 300 * i / filenum + 150 / filenum, 530, 5, 0xFF33EEFF);
			aacircleColor(renderer, WIDTH / 2 - 150 + 300 * i / filenum + 150 / filenum, 530, 5, 0xFFFFFFFFF);
		}
	}
	else {
		for (int i = 0; i < filenum; i++) {
			if (i == fileorder)
				filledCircleColor(renderer, WIDTH / 2 - filenum*20/2 + 20*i + 5, 530, 5, 0xFF33EEFF);
			aacircleColor(renderer, WIDTH / 2 - filenum * 20 / 2 + 20 * i + 5, 530, 5, 0xFFFFFFFFF);
		}
	}
	textRender(renderer, text[3], textPos[3].x - text[3].width / 2, textPos[3].y - text[3].height / 2, NULL, NULL, NULL, no, alpha);
	SDL_RenderPresent(renderer);
}

void drawcreatemap() {
	textPos[0] = { WIDTH / 6, 660 };
	textPos[1] = { 5 * WIDTH / 6, 660 };
	textPos[2] = { WIDTH / 2, HEIGHT / 2 };
	textPos[3] = { WIDTH / 2, HEIGHT / 2 };
	textPos[4] = { WIDTH / 2, HEIGHT / 2 };
	textColor[2] = { 225, 25, 25 };
	textColor[3] = { 225, 225, 25 };
	textColor[4] = { 25, 225, 25 };
	static int tips=0;
	int size[5] = { 30,30,100,100,100 };
	for (int i = 0; i < 2; i++) {
		if (mouseX > textPos[i].x - text[i].width / 2 && mouseX < textPos[i].x + text[i].width / 2 && mouseY > textPos[i].y - text[i].height / 2 && mouseY < textPos[i].y + text[i].height / 2)
		{
			textColor[i].r = 255;
			textColor[i].g = 0;
			textColor[i].b = 0;
			size[i] = 40;
			if ((mouseState == LB_SC || mouseState == LB_DC))
			{
				switch (i)
				{
				case 0:
					status = MENU;
					break;
				case 1:
					alpha = 225;
					for (int i = 0; i < bi.size(); i++) {
						map[bi[i].y][bi[i].x] = 3;
					}
					map1 = map;
					check_map(map);
					if (!validMap) {
						tips = 2;
					}
					else {
						int ma[M][N];
						bool repeat = false;
						fp1 = fopen("files.dat", "rb");
						while (!feof(fp1) && !repeat) {
							cout << "repeat\n";
							tips = 3;
							repeat = true;
							for (int i = 0; i < M && repeat; i++) {
								for (int j = 0; j < N && repeat; j++) {
									fread(&(ma[i][j]), sizeof(int), 1, fp1);
									if (map1[i][j] != ma[i][j]) {
										repeat = false;
										fseek(fp1, sizeof(int) * (M * N - i * N - j - 2), SEEK_CUR);
									}
								}
							}
							fread(&(ma[0][0]), sizeof(int), 1, fp1);
						}
						fclose(fp1);
						if (!repeat) {
							cout << "save" << endl;
							tips = 4;
							fp1 = fopen("files.dat", "ab");
							for (int i = 0; i < M; i++) {
								for (int j = 0; j < N; j++) {
									fwrite(&(map1[i][j]), sizeof(int), 1, fp1);
								}
							}
							fclose(fp1);
						}
					}
					break;
				}
			}
		}
		else
		{
			textColor[i].r = 255;
			textColor[i].g = 255;
			textColor[i].b = 255;
			size[i] = 30;
		}
	}

	text[0] = loadTextTexture("back", "../fonts/akabara-cinderella.ttf", size[0], textColor[0].r, textColor[0].g, textColor[0].b, BLENDED, NULL, NULL, NULL);
	text[1] = loadTextTexture("save", "../fonts/akabara-cinderella.ttf", size[1], textColor[1].r, textColor[1].g, textColor[1].b, BLENDED, NULL, NULL, NULL);
	text[2] = loadTextTexture("unconnected", "../fonts/akabara-cinderella.ttf", size[2], textColor[2].r, textColor[2].g, textColor[2].b, BLENDED, NULL, NULL, NULL);
	text[3] = loadTextTexture("repeated", "../fonts/akabara-cinderella.ttf", size[3], textColor[3].r, textColor[3].g, textColor[3].b, BLENDED, NULL, NULL, NULL);
	text[4] = loadTextTexture("saved", "../fonts/akabara-cinderella.ttf", size[4], textColor[4].r, textColor[4].g, textColor[4].b, BLENDED, NULL, NULL, NULL);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);

	for (int i = 0; i < 2; i++)
		textRender(renderer, text[i], textPos[i].x - text[i].width / 2, textPos[i].y - text[i].height / 2, NULL, NULL, NULL, no, 255);
	

	imgRender(renderer, wall3, 50, 20, 0, NULL, NULL, NULL, no, 255, 1, 1);
	if (button == 2 && ((mp.x < 4 || mp.x > 5) || mp.y !=4)) {
		if (mv.x == 0 && mv.y == 1) {
			if ((mp.x < 4 || mp.x > 5) || (mp.y + 1 + M / 3) % (M / 3) != 4) {
				m[mp.y][mp.x] |= 8;
				mp.y = (mp.y + 1 + M / 3) % (M / 3);
				m[mp.y][mp.x] |= 2;
			}
			else mp.y = (mp.y + 1 + M / 3) % (M / 3);
		}
		else if (mv.x == 0 && mv.y == -1) {
			if ((mp.x < 4 || mp.x > 5) || (mp.y - 1 + M / 3) % (M / 3) != 4) {
				m[mp.y][mp.x] |= 2;
				mp.y = (mp.y - 1 + M / 3) % (M / 3);
				m[mp.y][mp.x] |= 8;
			}
			else mp.y = (mp.y - 1 + M / 3) % (M / 3);
		}
		else if (mv.x == 1 && mv.y == 0 ) {
			if ((mp.x + 1 + N / 3) % (N / 3) < 4 || (mp.x + 1 + N / 3) % (N / 3) > 5 || mp.y != 4) {
				m[mp.y][mp.x] |= 1;
				mp.x = (mp.x + 1 + N / 3) % (N / 3);
				m[mp.y][mp.x] |= 4;
			}
			else mp.x = (mp.x + 1 + N / 3) % (N / 3);
		}
		else if (mv.x == -1 && mv.y == 0) {
			if ((mp.x - 1 + N / 3) % (N / 3) < 4 || (mp.x - 1 + N / 3) % (N / 3) > 5 || mp.y != 4) {
				m[mp.y][mp.x] |= 4;
				mp.x = (mp.x - 1 + N / 3) % (N / 3);
				m[mp.y][mp.x] |= 1;
			}
			else mp.x = (mp.x - 1 + N / 3) % (N / 3);
		}
	}
	else {
		if (mv.x == 0 && mv.y == 1) {
			mp.y = (mp.y + 1 + M / 3) % (M / 3);
		}
		else if (mv.x == 0 && mv.y == -1) {
			mp.y = (mp.y - 1 + M / 3) % (M / 3);
		}
		else if (mv.x == 1 && mv.y == 0) {
			mp.x = (mp.x + 1 + N / 3) % (N / 3);
		}
		else if (mv.x == -1 && mv.y == 0) {
			mp.x = (mp.x - 1 + N / 3) % (N / 3);
		}
		if (button == 0 && ((mp.x<3 || mp.x>6) || (mp.y<3 || mp.y>5))) {
			m[mp.y][mp.x] = 0;
			m[(mp.y + 1 + M / 3) % (M / 3)][mp.x] &= 13;
			m[(mp.y - 1 + M / 3) % (M / 3)][mp.x] &= 7;
			m[mp.y][(mp.x + 1 + N / 3) % (N / 3)] &= 11;
			m[mp.y][(mp.x - 1 + N / 3) % (N / 3)] &= 14;
		}
	}
	
	mv = { 0, 0 };
	SDL_Rect r = { 50 + mp.x * l_grid*3 + 3*l_grid/2 -10 , 20 + mp.y*l_grid*3 + 3*l_grid/2 -10 , 20, 20 };
	SDL_Rect but[3] = { { 2 * WIDTH / 6 - 20, 640, 40, 40 }, { 3 * WIDTH / 6 - 20, 640, 40, 40 }, { 4 * WIDTH / 6 - 20, 640, 40, 40 } };
	SDL_Color col[3] = { { 0x4F, 0x10, 0x10, 0xFF }, { 0x50, 0x50, 0x50, 0xFF }, { 0x10, 0x4F, 0x10, 0xFF } };
	for (int i = 0; i < 3; i++) {
		if (mouseX > but[i].x && mouseX < but[i].x + but[i].w && mouseY > but[i].y && mouseY < but[i].y + but[i].h) {
			if (mouseState == LB_SC || mouseState == LB_DC || e.type == SDL_MOUSEBUTTONDOWN) {
				button = i;
			}
		}
	}
	col[button] = { col[button].r *= 3, col[button].g *= 3, col[button].b *= 3, 0xFF };
	but[button] = { but[button].x - 5, but[button].y - 5, but[button].w + 10, but[button].h + 10 };
	for (int i = 0; i < 3; i++) {
		SDL_SetRenderDrawColor(renderer, col[i].r, col[i].g, col[i].b, col[i].a);
		SDL_RenderFillRect(renderer, &but[i]);
	}

	fillmap(map, m);
	stdwall(map, map2);
	for (int i = 0; i < M/3; i++)
		for (int j = 0; j < N/3; j++)
			if(m[i][j]!=-1)
				for (int k = 0; k < 3; k++) 
					for (int l = 0; l < 3; l++)
						imgRender(renderer, wall, 50 + (j*3+l) * l_grid, 20 + (i*3+k) * l_grid, map2[i*3+k][j*3+l], NULL, NULL, NULL, no, 255, 1, 1);
	bool br = false;
	if (mouseX > 50 && mouseX < 50 + N * l_grid && mouseY > 20 && mouseY < 20 + M * l_grid ) {
		if (mouseState == LB_SC || mouseState == LB_DC) {
			for (int i = 0; i != bi.size(); i++) {
				if ((bi[i].x == (mouseX - 50) / l_grid && bi[i].y == (mouseY - 20) / l_grid )) {
					bi.erase(bi.begin() + i);
					i--;
					br = true;
				}
			}
			if (!br && map[(mouseY - 20) / l_grid][(mouseX - 50) / l_grid] > 0) bi.push_back(tmpbi = { (mouseX - 50) / l_grid, (mouseY - 20) / l_grid }), cout << "ji\n";
		}
	}
	for (int i = 0; i != bi.size(); i++) {
		if (m[bi[i].y/3][bi[i].x/3]==0 || map[bi[i].y][bi[i].x]==0) {
			bi.erase(bi.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < bi.size(); i++) {
		imgRender(renderer, wall, 50 + bi[i].x * l_grid, 20 + bi[i].y * l_grid, 8, NULL, NULL, NULL, no, 255, 1, 1);
	}
	SDL_SetRenderDrawColor(renderer, 0xF0, 0xF0, 0x50, 0xFF);
	SDL_RenderFillRect(renderer, &r);
	if (tips > 0) textRender(renderer, text[tips], textPos[tips].x - text[tips].width / 2, textPos[tips].y - text[tips].height / 2, NULL, NULL, NULL, no, alpha);

	SDL_RenderPresent(renderer);
}

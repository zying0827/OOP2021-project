void game_initialize() {
	pacc = initpac;
	pacp = { pacc.x / l_grid, pacc.y / l_grid };
	pacc2 = initpac2;
	pacp2 = { pacc2.x / l_grid, pacc2.y / l_grid };
	dir = 0;
	dir2 = 0;
	pv = { 0,0 };
	pv2 = { 0,0 };
	ghostc[0] = { 15 * l_grid, (10 + y_down) * l_grid + l_grid / 2 };
	ghostc[1] = { 13 * l_grid + l_grid / 2, (13 + y_down)* l_grid + l_grid / 2 };
	ghostc[2] = { 15 * l_grid + l_grid / 2, (13 + y_down)* l_grid + l_grid / 2 };
	ghostc[3] = { 17 * l_grid + l_grid / 2, (13 + y_down)* l_grid + l_grid / 2 };
	for (int i = 0; i < 4; i++) {
		ghostp[i] = { ghostc[i].x / l_grid, ghostc[i].y / l_grid };
		gv[i] = { 0,-1 };
		ghost_isolated[i] = true;
		ghost_eaten[i] = false;
		ghost_eatening[i] = false;
		ghost_frightened[i] = false;
	}
	gv[0] = { 1,0 };
	ghost_isolated[0] = false;
	ghost_alp = 255;
	pac_alp = 255;
	pac2_alp = 255;
	die_alp = 0;
//	time_isolated = SDL_GetTicks() + time_total_paused;
	period_die = false;
	period_die2 = false;
	period_frightened = false;
	period_frightened_end = false;
	period_eatghost = false;
	period_paceaten = false;
	period_pac2eaten = false;
	period_dissolve = false;
	period_dissolve2 = false;
	period_disappear = false;
	period_end = false;
	cnt = 0;
}
void drawClassic()
{
	hint = loadTextTexture(" ", "../fonts/TaipeiSansTCBeta-Regular.ttf", 24, 255, 0, 0, SHADED, 0, 0, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);
	char score_str[100] = "score: \0";
	char tmp_str[100] = "\0";
	sprintf_s(tmp_str, "%d", score);
	strcat(score_str, tmp_str);
	score_text = loadTextTexture(score_str, "../fonts/TaipeiSansTCBeta-Regular.ttf", 28, 255, 255, 0, SHADED, 0, 0, 0);
	int timer = SDL_GetTicks() - time_init - time_total_paused;
	if (period_init)
	{
		game_initialize();
		hint_alp = 255;
		hint = loadTextTexture("READY?", "../fonts/TaipeiSansTCBeta-Regular.ttf", 24, 255, 0, 0, SHADED, 0, 0, 0);
		if (timer > 4500) {
			period_init = false;
			time_isolated = SDL_GetTicks();
		}
	}
	else
	{
		if (Mix_PlayingMusic() == 0 && !period_die && !passFlag && !period_eatghost) {
			Mix_PlayMusic(woooo, -1);
			cout << "play_woooo\n";
		}

		hint_alp = 0;
		int dot = 0;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				if (map1[i][j] == 1)
					dot++;
		if (dot == 0 && !passFlag)
		{
			passFlag = true;
			time_pass = SDL_GetTicks();
			ghost_alp = 0;
			pac_alp = 0;
			die_alp = 0;
		}
		if (passFlag && SDL_GetTicks() - time_pass > 1500)
		{
			map1 = map;
			period_init = true;
			time_init = SDL_GetTicks();
			pause_duration = 0;
			time_total_paused = 0;
			passFlag = false;
			Mix_PlayMusic(beginning, 0);
			cout << "play_beginning\n";
		}
		if (!period_die && !period_eatghost && live > 0)
		{
			gmove(0, 10);
			gmove(1, 0);
			gmove(2, 0);
			gmove(3, 0);

			pacmove();
			if ((map1[pacp.y][pacp.x] == 1))
			{
				eeat = true;
				map1[pacp.y][pacp.x] = 2;
				score += 10;
			}
			if ((map1[pacp.y][pacp.x] == 3))
			{
				Mix_PlayMusic(frighten, -1);
				cout << "play_frighten\n";
				time_frightened = timer;
				period_frightened = true;
				period_frightened_end = false;
				for (int i = 0; i < 4; i++) {
					if (!ghost_isolated[i] && !ghost_eaten[i]) {
						ghost_frightened[i] = true;
					}
				}
				map1[pacp.y][pacp.x] = 2;
				printf("frightened\n");
			}

			for (int i = 0; i < 4; i++) {
				if (dist(pacc, ghostc[i], l_char * l_grid) && !ghost_frightened[i] && !period_die && !ghost_eaten[i])
				{
					printf("dead\n");
					period_die = true;
					period_paceaten = true;
					time_die = timer;
					diec = pacc;
					live--;
					playDeathMusic = true;
				}
			}
		}
		if (period_frightened)
		{
			period_eatghost = false;
			for (int i = 0; i < 4; i++)
			{
				if (ghost_eaten[i] && timer - time_ghost_eaten[i] > 600) {
					ghost_eatening[i] = false;
				}
				if (dist(pacc, ghostc[i], l_char * l_grid) && ghost_frightened[i] && !ghost_eaten[i])
				{
					ghost_eaten[i] = true;
					ghost_eatening[i] = true;
					time_ghost_eaten[i] = timer;
					cnt++;
					score += cnt * 200;
					Mix_PlayChannel(2, eatghost, 0);
					Mix_HaltMusic();
					cout << "haltmusic\n";
				}
				if (ghost_eatening[i]) {
					period_eatghost = true;
				}
			}
			if (timer - time_frightened > 6000) {
				period_frightened_end = true;
			}
			if (timer - time_frightened > 8000) {
				period_eatghost = false;
				period_frightened = false;
				period_frightened_end = false;
				for (int i = 0; i < 4; i++) {
					ghost_frightened[i] = false;
					ghost_eatening[i] = false;
				}
				cnt = 0;
				Mix_HaltMusic();
			}
		}

		if (period_die)
		{
			period_frightened = false;
			if (timer - time_die < 500) {
				period_paceaten = true;
				die_alp = 0;
				dieIndex[0] = 0;
			}
			else if (timer - time_die < 1600)
			{
				period_paceaten = false;
				period_dissolve = true;
				pac_alp = 0;
				die_alp = 255;
				ghost_alp = 0;
				if (playDeathMusic)
				{
					Mix_PlayMusic(death, 0);
					cout << "play_death\n";
					playDeathMusic = false;
				}
			}
			else if (timer - time_die < 2000)
			{
				period_dissolve = false;
				period_disappear = true;
				lives_alp[live] = 0;
				pac_alp = 0;
				pv = { 1,0 };
				die_alp = 0;
				ghost_alp = 0;
			}
			else if (timer - time_die < 4500)
			{
				period_end = true;
				period_disappear = false;
				if (live == 0) {
					hint = loadTextTexture("GAME OVER", "../fonts/TaipeiSansTCBeta-Regular.ttf", 24, 255, 0, 0, SHADED, 0, 0, 0);
					hint_alp = 255;
				}
			}
			else if (timer - time_die > 5500) {
				if (live == 0) {
					if (score > r[4].score)
					{
						status = ENTER_NAME;
						strcpy(inputString, " ");
					}
					else
					{
						status = MENU;
						Mix_HaltMusic();
						time_animation = SDL_GetTicks();
					}
					period_die = false;
				}
				else {
					period_init = true;
					time_init = SDL_GetTicks();
					Mix_PlayMusic(beginning, 0);
					cout << "play_beginning\n";
					pause_duration = 0;
					time_total_paused = 0;
				}
			}
		}
	}
	SDL_Rect r[5] = { {580, 20, 50, 50}, {580, 80, 50, 50}, {580, 140, 50, 50}, {580, 200, 50, 50}, {580, 260, 50, 50} };
	if (mouseX > r[0].x && mouseX < r[0].x + r[0].w && mouseY > r[0].y && mouseY < r[0].y + r[0].h)
		if (mouseState == LB_SC || mouseState == LB_DC)
		{
			pauseFlag = true;
			pausedisplay = false;
			Mix_PauseMusic();
			Mix_Pause(-1);
			time_pause = SDL_GetTicks();
		}
	if (mouseX > r[1].x && mouseX < r[1].x + r[1].w && mouseY > r[1].y && mouseY < r[1].y + r[1].h)
		if (mouseState == LB_SC || mouseState == LB_DC)
		{
			pauseFlag = true;
			pausedisplay = true;
			Mix_PauseMusic();
			Mix_Pause(-1);
			time_pause = SDL_GetTicks();
		}
	static int tips=2;
	if (mouseX > r[2].x && mouseX < r[2].x + r[2].w && mouseY > r[2].y && mouseY < r[2].y + r[2].h)
		if (mouseState == LB_SC || mouseState == LB_DC){
			enlargeFlag = false;
			forwardFlag = false;
			tips = 2;
		}
	if (mouseX > r[3].x && mouseX < r[3].x + r[3].w && mouseY > r[3].y && mouseY < r[3].y + r[3].h)
		if (mouseState == LB_SC || mouseState == LB_DC) {
			enlargeFlag = true;
			forwardFlag = false;
			tips = 3;
		}
	if (mouseX > r[4].x && mouseX < r[4].x + r[4].w && mouseY > r[4].y && mouseY < r[4].y + r[4].h)
		if (mouseState == LB_SC || mouseState == LB_DC) {
			forwardFlag = true;
			enlargeFlag = false;
			tips = 4;
		}
	
	for (int i = 0; i < 5; i++) {
		if(i>1 && i!=tips)
			imgRender(renderer, images[i], r[i].x, r[i].y, 0, NULL, NULL, NULL, no, 100, 1, 1);
		else
			imgRender(renderer, images[i], r[i].x, r[i].y, 0, NULL, NULL, NULL, no, 255, 1, 1);
	}
	if (!enlargeFlag && !forwardFlag) tips = 2;
	else if (enlargeFlag) tips = 3;
	else if (forwardFlag) tips = 4;
	stdwall(map1, map2);
	if ((!forwardFlag) && (!enlargeFlag))
	{
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++) {
				if (passFlag && wallchange % 10 < 5)
					imgRender(renderer, wall4, padding + j * l_grid, padding + i * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, 1, 1);
				else
					imgRender(renderer, wall, padding + j * l_grid, padding + i * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, 1, 1);
			}
		imgRender(renderer, pac, pacc.x, pacc.y, pacIndex[0], NULL, NULL, NULL, no, pac_alp, 1, 1);
		imgRender(renderer, die, diec.x, diec.y, dieIndex[0], NULL, NULL, NULL, no, die_alp, 1, 1);
		for(int i=0;i<4;i++)
			imgRender(renderer, ghost[i], ghostc[i].x, ghostc[i].y, ghostIndex[i], NULL, NULL, NULL, no, ghost_alp, 1, 1);
		SDL_Rect fillRects[4] = { { 0, 0, l_grid*N + padding, padding }, { 0, padding + l_grid*M, l_grid * N + padding, padding }, { 0, 0, padding, l_grid * M + padding}, { padding + l_grid * N, 0, padding, l_grid * N + padding} };
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderFillRects(renderer, fillRects, 4);
	}
	else if(forwardFlag){
		SDL_Rect view1;
		view1.x = padding;
		view1.y = padding;
		view1.w = N * l_grid;
		view1.h = M * l_grid;
		SDL_RenderSetViewport(renderer, &view1);

		Point cent = { N * l_grid / 2 - l_char / 2, M * l_grid / 2 - l_char / 2 };
		Points coop;
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = -1; k < 2; k++) {
					for (int l = -1; l < 2; l++) {
						coop = { ((padding + (j + k * N) * l_grid + l_grid/2) - (pacc.x+l_char/2))*magnitude , ((padding + (i + l * M) * l_grid + l_grid / 2) - (pacc.y + l_char / 2)) * magnitude };
						if (passFlag && wallchange % 10 < 5)
							imgRender(renderer, wall4, cent.x - magnitude * l_grid/2 + coop.x * cos(theta * M_PI / 180) - coop.y * sin(theta * M_PI / 180), cent.y - magnitude * l_grid / 2 + coop.x * sin(theta * M_PI / 180) + coop.y * cos(theta * M_PI / 180), map2[i][j], l_grid / 2, l_grid / 2, theta, no, 255, magnitude, magnitude);
						else
							imgRender(renderer, wall, cent.x - magnitude * l_grid / 2 + coop.x * cos(theta * M_PI / 180) - coop.y * sin(theta * M_PI / 180), cent.y - magnitude * l_grid / 2 + coop.x * sin(theta * M_PI / 180) + coop.y * cos(theta * M_PI / 180), map2[i][j], l_grid / 2, l_grid / 2, theta, no, 255, magnitude, magnitude);
					}
				}
			}
		}
		imgRender(renderer, pac, cent.x - l_char / 2, cent.y - l_char / 2, pacIndex[0], l_char / 2, l_char / 2, theta, no, pac_alp, magnitude, magnitude);
		imgRender(renderer, die, cent.x - l_char / 2, cent.y - l_char / 2, dieIndex[0], l_char / 2, l_char / 2, theta, no, die_alp, magnitude, magnitude);
		for (int i = 0; i < 4; i++) {
			for (int k = -1; k < 2; k++) {
				for (int l = -1; l < 2; l++) {
					coop = {((ghostc[i].x - l_char/2 + k * N * l_grid) - (pacc.x - l_char/2)) * magnitude, ((ghostc[i].y - l_char/2 + l * M * l_grid) - (pacc.y - l_char / 2)) * magnitude };
					imgRender(renderer, ghost[i], cent.x - magnitude * l_char/2 + coop.x * cos(theta * M_PI / 180) - coop.y * sin(theta * M_PI / 180) , cent.y - magnitude * l_char / 2 + coop.x * sin(theta * M_PI / 180) + coop.y * cos(theta * M_PI / 180), ghostIndex[i], l_char / 2, l_char / 2, 0, no, 255, magnitude, magnitude);
				}
			}
		}
	}

	else
	{
		SDL_Rect view1;
		view1.x = padding;
		view1.y = padding;
		view1.w = N*l_grid;
		view1.h = M*l_grid;
		SDL_RenderSetViewport(renderer, &view1);

		Point cent = { N * l_grid / 2 - l_char / 2, M * l_grid / 2 - l_char / 2 };
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (passFlag && wallchange % 10 < 5) {
					imgRender(renderer, wall4, cent.x - magnitude * (pacc.x - padding) + j * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + i * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
					imgRender(renderer, wall4, cent.x - magnitude * (pacc.x - padding) + (j - N) * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + i * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
					imgRender(renderer, wall4, cent.x - magnitude * (pacc.x - padding) + (j + N) * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + i * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
					imgRender(renderer, wall4, cent.x - magnitude * (pacc.x - padding) + j * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + (i - M) * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
					imgRender(renderer, wall4, cent.x - magnitude * (pacc.x - padding) + j * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + (i + M) * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
					imgRender(renderer, wall4, cent.x - magnitude * (pacc.x - padding) + (j - N) * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + (i - M) * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
					imgRender(renderer, wall4, cent.x - magnitude * (pacc.x - padding) + (j - N) * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + (i + M) * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
					imgRender(renderer, wall4, cent.x - magnitude * (pacc.x - padding) + (j + N) * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + (i - M) * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
					imgRender(renderer, wall4, cent.x - magnitude * (pacc.x - padding) + (j + N) * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + (i + M) * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
				}
				else {
					imgRender(renderer, wall, cent.x - magnitude * (pacc.x - padding) + j * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + i * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
					imgRender(renderer, wall, cent.x - magnitude * (pacc.x - padding) + (j - N) * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + i * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
					imgRender(renderer, wall, cent.x - magnitude * (pacc.x - padding) + (j + N) * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + i * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
					imgRender(renderer, wall, cent.x - magnitude * (pacc.x - padding) + j * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + (i - M) * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
					imgRender(renderer, wall, cent.x - magnitude * (pacc.x - padding) + j * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + (i + M) * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
					imgRender(renderer, wall, cent.x - magnitude * (pacc.x - padding) + (j - N) * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + (i - M) * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
					imgRender(renderer, wall, cent.x - magnitude * (pacc.x - padding) + (j - N) * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + (i + M) * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
					imgRender(renderer, wall, cent.x - magnitude * (pacc.x - padding) + (j + N) * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + (i - M) * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);
					imgRender(renderer, wall, cent.x - magnitude * (pacc.x - padding) + (j + N) * magnitude * l_grid, cent.y - magnitude * (pacc.y - padding) + (i + M) * magnitude * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, magnitude, magnitude);

				}

			}
		imgRender(renderer, pac, cent.x, cent.y, pacIndex[0], NULL, NULL, NULL, no, pac_alp, magnitude, magnitude);
		imgRender(renderer, die, cent.x, cent.y, dieIndex[0], NULL, NULL, NULL, no, die_alp, magnitude, magnitude);
		for (int i = 0; i < 4; i++)
		{
			imgRender(renderer, ghost[i], cent.x - magnitude * (pacc.x - ghostc[i].x), cent.y - magnitude * (pacc.y - ghostc[i].y), ghostIndex[i], NULL, NULL, NULL, no, ghost_alp, magnitude, magnitude);
			imgRender(renderer, ghost[i], cent.x - magnitude * (pacc.x - ghostc[i].x) - N * magnitude * l_grid, cent.y - magnitude * (pacc.y - ghostc[i].y), ghostIndex[i], NULL, NULL, NULL, no, ghost_alp, magnitude, magnitude);
			imgRender(renderer, ghost[i], cent.x - magnitude * (pacc.x - ghostc[i].x) + N * magnitude * l_grid, cent.y - magnitude * (pacc.y - ghostc[i].y), ghostIndex[i], NULL, NULL, NULL, no, ghost_alp, magnitude, magnitude);
			imgRender(renderer, ghost[i], cent.x - magnitude * (pacc.x - ghostc[i].x), cent.y - magnitude * (pacc.y - ghostc[i].y) - M * magnitude * l_grid, ghostIndex[i], NULL, NULL, NULL, no, ghost_alp, magnitude, magnitude);
			imgRender(renderer, ghost[i], cent.x - magnitude * (pacc.x - ghostc[i].x), cent.y - magnitude * (pacc.y - ghostc[i].y) + M * magnitude * l_grid, ghostIndex[i], NULL, NULL, NULL, no, ghost_alp, magnitude, magnitude);
			imgRender(renderer, ghost[i], cent.x - magnitude * (pacc.x - ghostc[i].x) - N * magnitude * l_grid, cent.y - magnitude * (pacc.y - ghostc[i].y) - M * magnitude * l_grid, ghostIndex[i], NULL, NULL, NULL, no, ghost_alp, magnitude, magnitude);
			imgRender(renderer, ghost[i], cent.x - magnitude * (pacc.x - ghostc[i].x) + N * magnitude * l_grid, cent.y - magnitude * (pacc.y - ghostc[i].y) + M * magnitude * l_grid, ghostIndex[i], NULL, NULL, NULL, no, ghost_alp, magnitude, magnitude);
			imgRender(renderer, ghost[i], cent.x - magnitude * (pacc.x - ghostc[i].x) - N * magnitude * l_grid, cent.y - magnitude * (pacc.y - ghostc[i].y) - M * magnitude * l_grid, ghostIndex[i], NULL, NULL, NULL, no, ghost_alp, magnitude, magnitude);
			imgRender(renderer, ghost[i], cent.x - magnitude * (pacc.x - ghostc[i].x) + N * magnitude * l_grid, cent.y - magnitude * (pacc.y - ghostc[i].y) + M * magnitude * l_grid, ghostIndex[i], NULL, NULL, NULL, no, ghost_alp, magnitude, magnitude);

		}
	}
	SDL_Rect fullview;
	fullview.x = 0;
	fullview.y = 0;
	fullview.w = WIDTH;
	fullview.h = HEIGHT;
	SDL_RenderSetViewport(renderer, &fullview);

	for (int i = 0; i < 3; i++)
		imgRender(renderer, lives[i], padding + l_char * i + l_grid / 2, padding + l_grid * M + l_grid / 2, 1, NULL, NULL, NULL, no, lives_alp[i], 1, 1);
	textRender(renderer, hint, padding + 15 * l_grid - hint.width / 2, padding + 17 * l_grid + l_grid / 2 - hint.height / 2, NULL, NULL, NULL, no, hint_alp);
	textRender(renderer, score_text, padding + l_char * 11, padding + l_grid * M + l_grid / 2, NULL, NULL, NULL, no, 255);
	SDL_RenderPresent(renderer);
}
void drawDouble()
{
	hint = loadTextTexture(" ", "../fonts/TaipeiSansTCBeta-Regular.ttf", 24, 255, 0, 0, SHADED, 0, 0, 0);
	stdwall(map1, map2);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);
	char score_str[100] = "score: \0";
	char tmp_str[100] = "\0";
	sprintf_s(tmp_str, "%d", score);
	strcat(score_str, tmp_str);
	score_text = loadTextTexture(score_str, "../fonts/TaipeiSansTCBeta-Regular.ttf", 28, 255, 255, 0, SHADED, 0, 0, 0);
	int timer = SDL_GetTicks() - time_init - time_total_paused;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (passFlag && wallchange % 10 < 5)
				imgRender(renderer, wall4, padding + j * l_grid, padding + i * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, 1, 1);
			else
				imgRender(renderer, wall, padding + j * l_grid, padding + i * l_grid, map2[i][j], NULL, NULL, NULL, no, 255, 1, 1);
		}
	}
	
	if (period_init)
	{
		game_initialize();
		hint_alp = 255;
		hint = loadTextTexture("READY?", "../fonts/TaipeiSansTCBeta-Regular.ttf", 24, 255, 0, 0, SHADED, 0, 0, 0);
		if (SDL_GetTicks() - time_init > 4500) {
			period_init = false;
			time_isolated = SDL_GetTicks();
		}
	}
	else
	{
		if (Mix_PlayingMusic() == 0 && !period_die && !period_die2 && !period_eatghost) {
			Mix_PlayMusic(woooo, -1);
			cout << "play_woooo\n";
		}

		hint_alp = 0;
		int dot = 0;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				if (map1[i][j] == 1)
					dot++;
		if (dot == 0 && !passFlag)
		{
			passFlag = true;
			time_pass = SDL_GetTicks();
			ghost_alp = 0;
			pac_alp = 0;
			pac2_alp = 0;
			die_alp = 0;
		}
		if (passFlag && SDL_GetTicks() - time_pass > 1500)
		{
			map1 = map;
			period_init = true;
			time_init = SDL_GetTicks();
			pause_duration = 0;
			time_total_paused = 0;
			passFlag = false;
			Mix_PlayMusic(beginning, 0);
			cout << "play_beginning\n";
		}
		if (!period_die && !period_die2 && !period_eatghost && live > 0)
		{
			gmove(0, 10);
			gmove(1, 0);
			gmove(2, 0);
			gmove(3, 0);

			pacmove();
			pac2move();

			if ((map1[pacp.y][pacp.x] == 1))
			{
				eeat = true;
				map1[pacp.y][pacp.x] = 2;
				score += 10;
			}
			if ((map1[pacp2.y][pacp2.x] == 1))
			{
				eeat = true;
				map1[pacp2.y][pacp2.x] = 2;
				score += 10;
			}

			if ((map1[pacp.y][pacp.x] == 3))
			{
				Mix_PlayMusic(frighten, -1);
				cout << "play_frighten\n";
				time_frightened = timer;
				period_frightened = true;
				period_frightened_end = false;
				for (int i = 0; i < 4; i++) {
					if (!ghost_isolated[i] && !ghost_eaten[i]) {
						ghost_frightened[i] = true;
					}
				}
				map1[pacp.y][pacp.x] = 2;
				printf("frightened\n");
			}
			if ((map1[pacp2.y][pacp2.x] == 3))
			{
				Mix_PlayMusic(frighten, -1);
				cout << "play_frighten\n";
				time_frightened = timer;
				period_frightened = true;
				period_frightened_end = false;
				for (int i = 0; i < 4; i++) {
					if (!ghost_isolated[i] && !ghost_eaten[i]) {
						ghost_frightened[i] = true;
					}
				}
				map1[pacp2.y][pacp2.x] = 2;
				printf("frightened\n");
			}

			for (int i = 0; i < 4; i++) {
				if (dist(pacc, ghostc[i], l_char * l_grid) && !ghost_frightened[i] && !period_die && !period_die2 && !ghost_eaten[i])
				{
					printf("dead\n");
					period_die = true;
					period_paceaten = true;
					time_die = timer;
					diec = pacc;
					live--;
					playDeathMusic = true;
				}
			}

			for (int i = 0; i < 4; i++) {
				if (dist(pacc2, ghostc[i], l_char * l_grid) && !ghost_frightened[i] && !period_die && !period_die2 && !ghost_eaten[i])
				{
					printf("dead2\n");
					period_die2 = true;
					period_pac2eaten = true;
					time_die2 = timer;
					diec2 = pacc2;
					live--;
					playDeathMusic = true;
				}
			}
		}
		if (period_frightened)
		{
			period_eatghost = false;
			for (int i = 0; i < 4; i++)
			{
				if (ghost_eaten[i] && timer - time_ghost_eaten[i] > 600) {
					ghost_eatening[i] = false;
				}
				if (dist(pacc, ghostc[i], l_char * l_grid) && ghost_frightened[i] && !ghost_eaten[i])
				{
					ghost_eaten[i] = true;
					ghost_eatening[i] = true;
					time_ghost_eaten[i] = timer;
					cnt++;
					score += cnt * 200;
					Mix_PlayChannel(2, eatghost, 0);
					Mix_HaltMusic();
					cout << "haltmusic\n";
				}
				else if (dist(pacc2, ghostc[i], l_char * l_grid) && ghost_frightened[i] && !ghost_eaten[i])
				{
					ghost_eaten[i] = true;
					ghost_eatening[i] = true;
					time_ghost_eaten[i] = timer;
					cnt++;
					score += cnt * 200;
					Mix_PlayChannel(2, eatghost, 0);
					Mix_HaltMusic();
					cout << "haltmusic\n";
				}
				if (ghost_eatening[i]) {
					period_eatghost = true;
				}
			}
			if (timer - time_frightened > 6000) {
				period_frightened_end = true;
			}
			if (timer - time_frightened > 8000) {
				period_eatghost = false;
				period_frightened = false;
				period_frightened_end = false;
				for (int i = 0; i < 4; i++) {
					ghost_frightened[i] = false;
					ghost_eatening[i] = false;
				}
				cnt = 0;
				Mix_HaltMusic();
			}
		}

		if (period_die)
		{
			period_frightened = false;
			if (timer - time_die < 500) {
				period_paceaten = true;
				die_alp = 0;
				dieIndex[0] = 0;
			}
			else if (timer - time_die < 1600)
			{
				period_paceaten = false;
				period_dissolve = true;
				pac_alp = 0;
				pac2_alp = 0;
				die_alp = 255;
				die2_alp = 0;
				ghost_alp = 0; 
				if (playDeathMusic)
				{
					Mix_PlayMusic(death, 0);
					cout << "play_death\n";
					playDeathMusic = false;
				}
			}
			else if (timer - time_die < 2000)
			{
				period_dissolve = false;
				period_disappear = true;
				lives_alp[live] = 0;
				pac_alp = 0;
				pv = { 1,0 };
				pv2 = { 1,0 };
				die_alp = 0;
				ghost_alp = 0;
			}
			else if (timer - time_die < 4500)
			{
				period_end = true;
				period_disappear = false;
				if (live == 0) {
					hint = loadTextTexture("GAME OVER", "../fonts/TaipeiSansTCBeta-Regular.ttf", 24, 255, 0, 0, SHADED, 0, 0, 0);
					hint_alp = 255;
				}
			}
			else if (timer - time_die > 5500) {
				if (live == 0) {
					if (score > r[4].score)
					{
						status = ENTER_NAME;
						strcpy(inputString, " ");
					}
					else
					{
						status = MENU;
						Mix_HaltMusic();
						time_animation = SDL_GetTicks();
					}
					period_die = false;
				}
				else {
					period_init = true;
					time_init = SDL_GetTicks();
					Mix_PlayMusic(beginning, 0);
					cout << "play_beginning\n";
					pause_duration = 0;
					time_total_paused = 0;
				}
			}
		}
		else if (period_die2)
		{
			period_frightened = false;
			if (timer - time_die2 < 500) {
				period_pac2eaten = true;
				die2_alp = 0;
				die2Index[0] = 0;
			}
			else if (timer - time_die2 < 1600)
			{
				period_pac2eaten = false;
				period_dissolve = true;
				pac_alp = 0;
				pac2_alp = 0;
				die_alp = 0;
				die2_alp = 255;
				ghost_alp = 0;
				if (playDeathMusic)
				{
					Mix_PlayMusic(death, 0);
					cout << "play_death\n";
					playDeathMusic = false;
				}
			}
			else if (timer - time_die2 < 2000)
			{
				period_dissolve = false;
				period_disappear = true;
				lives_alp[live] = 0;
				pac_alp = 0;
				pac2_alp = 0;
				pv = { 1,0 };
				pv2 = { 1,0 };
				die_alp = 0;
				die2_alp = 0;
				ghost_alp = 0;
			}
			else if (timer - time_die2 < 4500)
			{
				period_end = true;
				period_disappear = false;
				if (live == 0) {
					hint = loadTextTexture("GAME OVER", "../fonts/TaipeiSansTCBeta-Regular.ttf", 24, 255, 0, 0, SHADED, 0, 0, 0);
					hint_alp = 255;
				}
			}
			else if (timer - time_die2 > 5500) {
				if (live == 0) {
					if (score > r[4].score)
					{
						status = ENTER_NAME;
						strcpy(inputString, " ");
					}
					else
					{
						status = MENU;
						Mix_HaltMusic();
						time_animation = SDL_GetTicks();
					}
					period_die2 = false;
				}
				else {
					period_init = true;
					time_init = SDL_GetTicks();
					Mix_PlayMusic(beginning, 0);
					cout << "play_beginning\n";
					time_total_paused = 0;
				}
			}
		}
	}
	SDL_Rect r[2] = { {580, 20, 50, 50}, {580, 80, 50, 50} };
	if (mouseX > r[0].x && mouseX < r[0].x + r[0].w && mouseY > r[0].y && mouseY < r[0].y + r[0].h)
		if (mouseState == LB_SC || mouseState == LB_DC)
		{
			pauseFlag = true;
			pausedisplay = false;
			Mix_PauseMusic();
			Mix_Pause(-1);
			time_pause = SDL_GetTicks();
		}
	if (mouseX > r[1].x && mouseX < r[1].x + r[1].w && mouseY > r[1].y && mouseY < r[1].y + r[1].h)
		if (mouseState == LB_SC || mouseState == LB_DC)
		{
			pauseFlag = true;
			pausedisplay = true;
			Mix_PauseMusic();
			Mix_Pause(-1);
			time_pause = SDL_GetTicks();
		}
	for (int i = 0; i < 2; i++) {
		imgRender(renderer, images[i], r[i].x, r[i].y, 0, NULL, NULL, NULL, no, 255, 1, 1);
	}

	imgRender(renderer, pac, pacc.x, pacc.y, pacIndex[0], NULL, NULL, NULL, no, pac_alp, 1, 1);
	imgRender(renderer, pac2, pacc2.x, pacc2.y, pac2Index[0], NULL, NULL, NULL, no, pac2_alp, 1, 1);
	imgRender(renderer, die, diec.x, diec.y, dieIndex[0], NULL, NULL, NULL, no, die_alp, 1, 1);
	imgRender(renderer, die2, diec2.x, diec2.y, die2Index[0], NULL, NULL, NULL, no, die2_alp, 1, 1);
	for (int i = 0; i < 4; i++)
		imgRender(renderer, ghost[i], ghostc[i].x, ghostc[i].y, ghostIndex[i], NULL, NULL, NULL, no, ghost_alp, 1, 1);
	for (int i = 0; i < 3; i++)
		imgRender(renderer, lives[i], padding + l_char * i + l_grid / 2, padding + l_grid * M + l_grid / 2, 1, NULL, NULL, NULL, no, lives_alp[i], 1, 1);

	textRender(renderer, hint, padding + 14 * l_grid - hint.width / 2, padding + 17 * l_grid + l_grid / 2 - hint.height / 2, NULL, NULL, NULL, no, hint_alp);
	textRender(renderer, score_text, padding + l_char * 11, padding + l_grid * M + l_grid / 2, NULL, NULL, NULL, no, 255);

	SDL_RenderPresent(renderer);
}
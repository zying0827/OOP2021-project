void back_to_center(vector<Point>& v, int j) {
	vector<vector<bool>> vis(M, vector<bool>(N, false));
	Point mapdir[4] = { {0,1},{1,0},{-1,0},{0,-1} };
	Point seq[M][N];
	Point tmp = { 0,0 };
	Point g, p, tmp2;
	g.x = ghostp[j].y;
	g.y = ghostp[j].x;
	p.x = 13 + y_down;
	p.y = 14;
	if (g.x == p.x && (g.y == p.y || g.y == p.y+1)) {
		ghost_eaten[j] = false;
		ghost_frightened[j] = false;
		for (int i = 0; i < 4; i++) {
			if (ghost_eaten[i]) break;
			if (i == 3 && period_frightened) {
				Mix_PlayMusic(frighten, -1);
				cout << "play_frighten\n";
			}
		}
		return;
	}
	v.push_back(g);
	while (!v.empty()) {
		Point now, next;
		now = v.front();
		v.erase(v.begin());
		int r = rand();
		for (int i = 0; i < 4; i++) {
			next.x = now.x + mapdir[i].x;
			next.y = now.y + mapdir[i].y;
			if (next.x < 0 || next.x >M - 1) next.x = (next.x + M) % M;
			if (next.y < 0 || next.y >N - 1) next.y = (next.y + N) % N;
			if ((map1[next.x][next.y] > 0 || ((next.x>10)&&(next.x<14)&&(next.y>13)&&(next.y<16))) && vis[next.x][next.y] == false) {
				v.push_back(next);
				vis[next.x][next.y] = true;
				seq[next.x][next.y] = mapdir[i];
			}
			if (next.x == p.x && next.y == p.y) {
				v.clear();
				tmp = p;
				while (tmp.x != g.x || tmp.y != g.y) {
					v.push_back(seq[tmp.x][tmp.y]);
					tmp2 = tmp;
					tmp.x -= seq[tmp2.x][tmp2.y].x;
					tmp.y -= seq[tmp2.x][tmp2.y].y;
					if (tmp.x<0 || tmp.x>M - 1) tmp.x = (tmp.x + M) % M;
					if (tmp.y<0 || tmp.y>N - 1) tmp.y = (tmp.y + N) % N;
				}
				return;
			}
		}
	}
}
void fright(int j) {
	Point mapdir[4] = { {0,1},{1,0},{-1,0},{0,-1} };
	Point p = { ghostp[j].y, ghostp[j].x };
	for (int i = 0; i < 4; i++) {
		Point next = { (p.x + mapdir[i].x + M) % M, (p.y + mapdir[i].y + N) % N };
		if (map[next.x][next.y] > 0 && (mapdir[i].x != gv[j].y || mapdir[i].y != gv[j].x)) {
			gv[j].x = mapdir[i].y;
			gv[j].y = mapdir[i].x;
			return;
		}
	}

	return;
}
void blinky(vector<Point>& v) {
	vector<vector<bool>> vis(M, vector<bool>(N, false));
	Point mapdir[4] = { {0,1},{1,0},{-1,0},{0,-1} };
	Point seq[M][N];
	Point tmp, tmp2;
	Point g, p;
	g.x = ghostp[0].y;
	g.y = ghostp[0].x;
	p.x = pacp.y;
	p.y = pacp.x;
	v.push_back(g);
	while (!v.empty()) {
		Point now, next;
		now = v.front();
		v.erase(v.begin());
		for (int i = 0; i < 4; i++) {
			next.x = (now.x + mapdir[i].x + M) % M;
			next.y = (now.y + mapdir[i].y + N) % N;
			if (map1[next.x][next.y] > 0 && vis[next.x][next.y] == false) {
				v.push_back(next);
				vis[next.x][next.y] = true;
				seq[next.x][next.y] = mapdir[i];
			}
			if (next.x == p.x && next.y == p.y) {
				v.clear();
				tmp = p;
				while (tmp.x != g.x || tmp.y != g.y) {
					v.push_back(seq[tmp.x][tmp.y]);
					tmp2 = tmp;
					tmp.x = (tmp.x - seq[tmp2.x][tmp2.y].x + M) % M;
					tmp.y = (tmp.y - seq[tmp2.x][tmp2.y].y + N) % N;
				}
				return;
			}
		}
	}
}

void pinky(vector<Point>& v) {
	vector<vector<bool>> vis(M, vector<bool>(N, false));
	Point mapdir[4] = { {-1,0},{0,-1},{0,1},{1,0} };
	Point seq[M][N];
	Point tmp, tmp2;
	Point g, p;
	g.x = ghostp[1].y;
	g.y = ghostp[1].x;
	p.x = (pacp.y + pv.y * 4 + rand() % 5 - 2 + M) % M;
	p.y = (pacp.x + pv.x * 4 + rand() % 5 - 2 + N) % N;
	bool br = false;
	if (map1[p.x][p.y] == 0) {
		for (int i = 1; i < 20 && !br; i++) {
			for (int j = -i; j <= i && !br; j += 2 * i) {
				for (int k = -i; k <= i && !br; k++) {
					if (map1[(p.x + j + M) % M][(p.y + k + N) % N] > 0) {
						p = { (p.x + j + M) % M , (p.y + k + N) % N };
						br = true;
					}
				}
			}
			for (int j = -i; j <= i && !br; j++) {
				for (int k = -i; k <= i && !br; k += 2 * i) {
					if (map1[(p.x + j + M) % M][(p.y + k + N) % N] > 0) {
						p = { (p.x + j + M) % M , (p.y + k + N) % N };
						br = true;
					}
				}
			}
		}
	}
	v.push_back(g);
	while (!v.empty()) {
		Point now, next;
		now = v.front();
		v.erase(v.begin());
		for (int i = 0; i < 4; i++) {
			next.x = (now.x + mapdir[i].x + M) % M;
			next.y = (now.y + mapdir[i].y + N) % N;
			if (map1[next.x][next.y] > 0 && vis[next.x][next.y] == false) {
				v.push_back(next);
				vis[next.x][next.y] = true;
				seq[next.x][next.y] = mapdir[i];
			}
			if (next.x == p.x && next.y == p.y) {
				v.clear();
				tmp = p;
				while (tmp.x != g.x || tmp.y != g.y) {
					v.push_back(seq[tmp.x][tmp.y]);
					tmp2 = tmp;
					tmp.x = (tmp.x - seq[tmp2.x][tmp2.y].x + M) % M;
					tmp.y = (tmp.y - seq[tmp2.x][tmp2.y].y + N) % N;
				}
				return;
			}
		}
	}
}
void inky(vector<Point>& v) {
	vector<vector<bool>> vis(M, vector<bool>(N, false));
	Point mapdir[4] = { {-1,0},{0,-1},{0,1},{1,0} };
	Point seq[M][N];
	Point tmp, tmp2;
	Point g, p;
	g.x = ghostp[2].y;
	g.y = ghostp[2].x;
	p.x = (2 * (pacp.y + pv.y * 2) - ghostp[0].y + 2*M) % M;
	p.y = (2 * (pacp.x + pv.x * 2) - ghostp[0].x + 2*N) % N;
	bool br = false;
	if (map1[p.x][p.y] == 0) {
		for (int i = 1; i < 17 && !br; i++) {
			for (int j = -i; j <= i && !br; j += 2 * i) {
				for (int k = -i; k <= i && !br; k++) {
					if (map1[(p.x + j + M) % M][(p.y + k + N) % N] > 0) {
						p = { (p.x + j + M) % M , (p.y + k + N) % N };
						br = true;
					}
				}
			}
			for (int j = -i; j <= i && !br; j++) {
				for (int k = -i; k <= i && !br; k += 2 * i) {
					if (map1[(p.x + j + M) % M][(p.y + k + N) % N] > 0) {
						p = { (p.x + j + M) % M , (p.y + k + N) % N };
						br = true;
					}
				}
			}
		}
	}
	v.push_back(g);
	while (!v.empty()) {
		Point now, next;
		now = v.front();
		v.erase(v.begin());
		for (int i = 0; i < 4; i++) {
			next.x = (now.x + mapdir[i].x + M) % M;
			next.y = (now.y + mapdir[i].y + N) % N;
			if (map1[next.x][next.y] > 0 && vis[next.x][next.y] == false) {
				v.push_back(next);
				vis[next.x][next.y] = true;
				seq[next.x][next.y] = mapdir[i];
			}
			if (next.x == p.x && next.y == p.y) {
				v.clear();
				tmp = p;
				while (tmp.x != g.x || tmp.y != g.y) {
					v.push_back(seq[tmp.x][tmp.y]);
					tmp2 = tmp;
					tmp.x = (tmp.x - seq[tmp2.x][tmp2.y].x + M) % M;
					tmp.y = (tmp.y - seq[tmp2.x][tmp2.y].y + N) % N;
				}
				return;
			}
		}
	}
}
void clyde(vector<Point>& v) {
	if (dist(ghostc[3], pacc, l_grid * l_grid * 100)) {
		Point mapdir[4] = { {-1,0},{0,-1},{1,0},{0,1} };
		Point g;
		g.x = ghostp[3].y;
		g.y = ghostp[3].x;
		Point tmp = g;
		int r = rand() % 4;
		for (int i = 0; i < 4; i++) {
			tmp.x = (g.x + mapdir[(r+i)%4].x + M) % M;
			tmp.y = (g.y + mapdir[(r+i)%4].y + N) % N;
			if (map1[tmp.x][tmp.y] > 0 && (notdir.x != mapdir[(r + i) % 4].x || notdir.y != mapdir[(r + i) % 4].y)) {
				notdir = mapdir[(r + i + 2) % 4];
				v.push_back(mapdir[(r+i)%4]);
				return;
			}
		}
		v.push_back(notdir);
		notdir = { -notdir.x, -notdir.y };
		return;
	}
	else {
		vector<vector<bool>> vis(M, vector<bool>(N, false));
		Point mapdir[4] = { {-1,0},{0,-1},{0,1},{1,0} };
		Point seq[M][N];
		Point tmp, tmp2;
		Point g, p;
		g.x = ghostp[3].y;
		g.y = ghostp[3].x;
		p.x = pacp.y;
		p.y = pacp.x;
		v.push_back(g);
		while (!v.empty()) {
			Point now, next;
			now = v.front();
			v.erase(v.begin());
			for (int i = 0; i < 4; i++) {
				next.x = (now.x + mapdir[i].x + M) % M;
				next.y = (now.y + mapdir[i].y + N) % N;
				if (map1[next.x][next.y] > 0 && vis[next.x][next.y] == false) {
					v.push_back(next);
					vis[next.x][next.y] = true;
					seq[next.x][next.y] = mapdir[i];
				}
				if (next.x == p.x && next.y == p.y) {
					v.clear();
					tmp = p;
					while (tmp.x != g.x || tmp.y != g.y) {
						v.push_back(seq[tmp.x][tmp.y]);
						notdir = { -seq[tmp.x][tmp.y].x, -seq[tmp.x][tmp.y].y };
						tmp2 = tmp;
						tmp.x = (tmp.x - seq[tmp2.x][tmp2.y].x + M) % M;
						tmp.y = (tmp.y - seq[tmp2.x][tmp2.y].y + N) % N;
					}
					return;
				}
			}
		}
	}
}

void(*gf[4])(vector<Point>&) = { blinky, pinky, inky, clyde };

void gmove(int i, int delay) {
	vector<Point> path;
	if (ghostc[i].x % l_grid == l_grid / 2 && ghostc[i].y % l_grid == l_grid / 2)
	{
		if (ghost_isolated[i]) {
			if(ghostc[i].y / l_grid == 12 + y_down || ghostc[i].y / l_grid == 14 + y_down)
			gv[i].y = -gv[i].y;
			ghost_leave[i] = true;
		}
		else if (ghost_eaten[i]) {
			back_to_center(path, i);
			if (!path.empty()) {
				gv[i].x = 2 * path.back().y;
				gv[i].y = 2 * path.back().x;
			}
			ghost_leave[i] = true;
		}
		else if (ghost_leave[i]) {
			gv[i] = { 0,0 };
			if (ghostp[i].x > 15) gv[i].x = -1;
			else if (ghostp[i].x < 14) gv[i].x = 1;
			else if (ghostp[i].y > 10 + y_down) gv[i].y = -1;
			if (ghostp[i].y == 11 + y_down) ghost_leave[i] = false;
		}
		else {
			(*gf[i])(path);
			if (!path.empty()) {
				gv[i].x = path.back().y;
				gv[i].y = path.back().x;
			}
			if (ghost_frightened[i]) {
				fright(i);
			}
		}
	}
	if (ghost_frightened[i] && !ghost_eaten[i]) delay = ghost_frightened_dalay;
	if ((delay == 0 || rand() % (100 / delay) != 0) || ghost_isolated[i] || ghost_eaten[i]) {
		ghostc[i].x += gv[i].x * v_gh;
		ghostc[i].y += gv[i].y * v_gh;
		if (ghost_eaten[i]) {
			if (ghostc[i].x < 0) ghostc[i].x = l_grid * N - 3;
			else if (ghostc[i].x >= l_grid * N) ghostc[i].x = 3;
			if (ghostc[i].y < 0) ghostc[i].y = l_grid * M - 3;
			else if (ghostc[i].y >= l_grid * M) ghostc[i].y = 3;
		}
		else {
			if (ghostc[i].x < 0) ghostc[i].x = l_grid * N - v_gh;
			else if (ghostc[i].x >= l_grid * N) ghostc[i].x = 0;
			if (ghostc[i].y < 0) ghostc[i].y = l_grid * M - v_gh;
			else if (ghostc[i].y >= l_grid * M) ghostc[i].y = 0;
		}
		ghostp[i].x = ghostc[i].x / l_grid;
		ghostp[i].y = ghostc[i].y / l_grid;
	}
}

void pacmove()
{
	if (pacc.x % l_grid == l_grid / 2 && pacc.y % l_grid == l_grid / 2)
	{
		if (map1[((pacp.y + pv.y)+M) % M][((pacp.x + pv.x)+N) % N] == 0) {
			pv.x = 0;
			pv.y = 0;
		}
		switch (dir)
		{
		case 0:
			if (map1[pacp.y][(pacp.x + 1) % N] != 0) {
				pv.x = 1;
				pv.y = 0;
			}
			break;
		case 90:
			if (map1[(pacp.y - 1 + M) % M][pacp.x] != 0) {
				pv.x = 0;
				pv.y = -1; 
			}
			break;
		case 180:
			if (map1[pacp.y][(pacp.x - 1 + N) % N] != 0) {
				pv.x = -1;
				pv.y = 0;
			}
			break;
		case 270:
			if (map1[(pacp.y + 1) % M][pacp.x] != 0) {
				pv.x = 0;
				pv.y = 1;
			}
			break;
		}
	}
	pacc.x += pv.x * v_pac;
	pacc.y += pv.y * v_pac;
	if (pacc.x < 0) pacc.x = l_grid * N - v_pac;
	else if (pacc.x >= l_grid * N ) pacc.x = 0;
	if (pacc.y < 0) pacc.y = l_grid * M - v_pac;
	else if (pacc.y >= l_grid * M ) pacc.y =  0;
	pacp.x = pacc.x / l_grid;
	pacp.y = pacc.y / l_grid;
}
void pac2move()
{
	if (pacc2.x % l_grid == l_grid / 2 && pacc2.y % l_grid == l_grid / 2)
	{
		if (map1[(pacp2.y + pv2.y + M) % M][(pacp2.x + pv2.x + N) % N] == 0) {
			pv2.x = 0;
			pv2.y = 0;
		}
		switch (dir2)
		{
		case 0:
			if (map1[pacp2.y][(pacp2.x + 1) % N] != 0) {
				pv2.x = 1;
				pv2.y = 0;
			}
			break;
		case 90:
			if (map1[(pacp2.y - 1 + M) % M][pacp2.x] != 0) {
				pv2.x = 0;
				pv2.y = -1;
			}
			break;
		case 180:
			if (map1[pacp2.y][(pacp2.x - 1 + N) % N] != 0) {
				pv2.x = -1;
				pv2.y = 0;
			}
			break;
		case 270:
			if (map1[(pacp2.y + 1) % M][pacp2.x] != 0) {
				pv2.x = 0;
				pv2.y = 1;
			}
			break;
		}
	}
	pacc2.x += pv2.x * v_pac;
	pacc2.y += pv2.y * v_pac;
	if (pacc2.x < 0) pacc2.x = l_grid * N - v_pac;
	else if (pacc2.x >= l_grid * N) pacc2.x = 0;
	if (pacc2.y < 0) pacc2.y = l_grid * M - v_pac;
	else if (pacc2.y >= l_grid * M) pacc2.y = 0;
	pacp2.x = pacc2.x / l_grid;
	pacp2.y = pacc2.y / l_grid;

}
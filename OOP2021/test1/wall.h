#include<iostream>
#include<vector>
using namespace std;

// 0 : wall
// 1 : road (dot)
// 2 : road (empty)
// 3 : big dot
// 4 :

/*
0:     1:     2:     3:     4:     5:     6:     7:     8:     9:     10:    11:    12:    13:    14:    15:   
0 0 0  0 0 0  0 1 0  0 1 0  0 0 0  0 0 0  0 1 0  0 1 0  0 0 0  0 0 0  0 1 0  0 1 0  0 0 0  0 0 0  0 1 0  0 1 0
0 0 0  0 1 1  0 1 0  0 1 1  1 1 0  1 1 1  1 1 0  1 1 1  0 1 0  0 1 1  0 1 0  0 1 1  1 1 0  1 1 1  1 1 0  1 1 1
0 0 0  0 0 0  0 0 0  0 0 0  0 0 0  0 0 0  0 0 0  0 0 0  0 1 0  0 1 0  0 1 0  0 1 0  0 1 0  0 1 0  0 1 0  0 1 0
*/
int sel(vector<vector<int>> &a, int i, int j)
{
	bool valid[16];
	for (int k = 0; k < 16; k++)
		valid[k] = true;
	valid[0] = valid[1] = valid[2] = valid[4] = valid[8] = false; 
	int up = a[(i + (M / 3) - 1) % (M / 3)][j];
	int down = a[(i + 1) % (M / 3)][j];
	int left = a[i][(j + (N / 3) - 1) % (N / 3)];
	int right = a[i][(j + 1) % (N / 3)];

	//左邊有路
	if (left % 2 == 1 && left>=0)
	{
		valid[0] = valid[1] = valid[2] = valid[3] = valid[8] = valid[9] = valid[10] = valid[11] = false;
	}
	//左邊沒路
	else if (left % 2 == 0 && left>=0)
	{
		valid[4] = valid[5] = valid[6] = valid[7] = valid[12] = valid[13] = valid[14] = valid[15] = false;
		
	}
	//右邊有路
	if ((right % 8) / 4 == 1 && right>=0)
	{
		valid[0] = valid[2] = valid[4] = valid[6] = valid[8] = valid[10] = valid[12] = valid[14] = false;
	}
	//右邊沒路
	else if ((right % 8) / 4 == 0 && right>=0)
	{
		valid[1] = valid[3] = valid[5] = valid[7] = valid[9] = valid[11] = valid[13] = valid[15] = false;
	}
	//上面有路 
	if ((up % 16) / 8 == 1 && up>=0)
	{
		valid[0] = valid[1] = valid[4] = valid[5] = valid[8] = valid[9] = valid[12] = valid[13] = false;
	}
	//上面沒路
	else if ((up % 16) / 8 == 0 && up>=0)
	{
		valid[2] = valid[3] = valid[6] = valid[7] = valid[10] = valid[11] = valid[14] = valid[15] = false;
	}
	//下面有路 
	if ((down % 4) / 2 == 1 && down>=0)
	{
		valid[0] = valid[1] = valid[2] = valid[3] = valid[4] = valid[5] = valid[6] = valid[7] = false;
	}
	//下面沒路
	else if ((down % 4) / 2 == 0 && down >=0)
	{
		valid[8] = valid[9] = valid[10] = valid[11] = valid[12] = valid[13] = valid[14] = valid[15] = false;
	}
	int t;
	if (valid[0] == false && valid[3] == false && valid[5] == false && valid[6] == false && valid[7] == false && valid[9] == false && valid[10] == false && valid[11] == false && valid[12] == false && valid[13] == false && valid[14] == false && valid[15] == false) {
		validMap = false;
		return -1;
	}
	do
	{
		t = rand() % 16;
	} while (!valid[t]);
	return t;
}
void fillmap(vector<vector<int>>& map, vector<vector<int>> a)
{
	for (int i = 0; i < M / 3; i++)
	{
		for (int j = 0; j < N / 3; j++)
		{
			switch (a[i][j])
			{
			case 0:
				map[3 * i][3 * j] = 0;
				map[3 * i][3 * j + 1] = 0;
				map[3 * i][3 * j + 2] = 0;
				map[3 * i + 1][3 * j] = 0;
				map[3 * i + 1][3 * j + 1] = 0;
				map[3 * i + 1][3 * j + 2] = 0;
				map[3 * i + 2][3 * j] = 0;
				map[3 * i + 2][3 * j + 1] = 0;
				map[3 * i + 2][3 * j + 2] = 0;
				break;
			case 1:
				map[3 * i][3 * j] = 0;
				map[3 * i][3 * j + 1] = 0;
				map[3 * i][3 * j + 2] = 0;
				map[3 * i + 1][3 * j] = 0;
				map[3 * i + 1][3 * j + 1] = 1;
				map[3 * i + 1][3 * j + 2] = 1;
				map[3 * i + 2][3 * j] = 0;
				map[3 * i + 2][3 * j + 1] = 0;
				map[3 * i + 2][3 * j + 2] = 0;
				break;
			case 2:
				map[3 * i][3 * j] = 0;
				map[3 * i][3 * j + 1] = 1;
				map[3 * i][3 * j + 2] = 0;
				map[3 * i + 1][3 * j] = 0;
				map[3 * i + 1][3 * j + 1] = 1;
				map[3 * i + 1][3 * j + 2] = 0;
				map[3 * i + 2][3 * j] = 0;
				map[3 * i + 2][3 * j + 1] = 0;
				map[3 * i + 2][3 * j + 2] = 0;
				break;
			case 3:
				map[3 * i][3 * j] = 0;
				map[3 * i][3 * j + 1] = 1;
				map[3 * i][3 * j + 2] = 0;
				map[3 * i + 1][3 * j] = 0;
				map[3 * i + 1][3 * j + 1] = 1;
				map[3 * i + 1][3 * j + 2] = 1;
				map[3 * i + 2][3 * j] = 0;
				map[3 * i + 2][3 * j + 1] = 0;
				map[3 * i + 2][3 * j + 2] = 0;
				break;
			case 4:
				map[3 * i][3 * j] = 0;
				map[3 * i][3 * j + 1] = 0;
				map[3 * i][3 * j + 2] = 0;
				map[3 * i + 1][3 * j] = 1;
				map[3 * i + 1][3 * j + 1] = 1;
				map[3 * i + 1][3 * j + 2] = 0;
				map[3 * i + 2][3 * j] = 0;
				map[3 * i + 2][3 * j + 1] = 0;
				map[3 * i + 2][3 * j + 2] = 0;
				break;
			case 5:
				map[3 * i][3 * j] = 0;
				map[3 * i][3 * j + 1] = 0;
				map[3 * i][3 * j + 2] = 0;
				map[3 * i + 1][3 * j] = 1;
				map[3 * i + 1][3 * j + 1] = 1;
				map[3 * i + 1][3 * j + 2] = 1;
				map[3 * i + 2][3 * j] = 0;
				map[3 * i + 2][3 * j + 1] = 0;
				map[3 * i + 2][3 * j + 2] = 0;
				break;
			case 6:
				map[3 * i][3 * j] = 0;
				map[3 * i][3 * j + 1] = 1;
				map[3 * i][3 * j + 2] = 0;
				map[3 * i + 1][3 * j] = 1;
				map[3 * i + 1][3 * j + 1] = 1;
				map[3 * i + 1][3 * j + 2] = 0;
				map[3 * i + 2][3 * j] = 0;
				map[3 * i + 2][3 * j + 1] = 0;
				map[3 * i + 2][3 * j + 2] = 0;
				break;
			case 7:
				map[3 * i][3 * j] = 0;
				map[3 * i][3 * j + 1] = 1;
				map[3 * i][3 * j + 2] = 0;
				map[3 * i + 1][3 * j] = 1;
				map[3 * i + 1][3 * j + 1] = 1;
				map[3 * i + 1][3 * j + 2] = 1;
				map[3 * i + 2][3 * j] = 0;
				map[3 * i + 2][3 * j + 1] = 0;
				map[3 * i + 2][3 * j + 2] = 0;
				break;
			case 8:
				map[3 * i][3 * j] = 0;
				map[3 * i][3 * j + 1] = 0;
				map[3 * i][3 * j + 2] = 0;
				map[3 * i + 1][3 * j] = 0;
				map[3 * i + 1][3 * j + 1] = 1;
				map[3 * i + 1][3 * j + 2] = 0;
				map[3 * i + 2][3 * j] = 0;
				map[3 * i + 2][3 * j + 1] = 1;
				map[3 * i + 2][3 * j + 2] = 0;
				break;
			case 9:
				map[3 * i][3 * j] = 0;
				map[3 * i][3 * j + 1] = 0;
				map[3 * i][3 * j + 2] = 0;
				map[3 * i + 1][3 * j] = 0;
				map[3 * i + 1][3 * j + 1] = 1;
				map[3 * i + 1][3 * j + 2] = 1;
				map[3 * i + 2][3 * j] = 0;
				map[3 * i + 2][3 * j + 1] = 1;
				map[3 * i + 2][3 * j + 2] = 0;
				break;
			case 10:
				map[3 * i][3 * j] = 0;
				map[3 * i][3 * j + 1] = 1;
				map[3 * i][3 * j + 2] = 0;
				map[3 * i + 1][3 * j] = 0;
				map[3 * i + 1][3 * j + 1] = 1;
				map[3 * i + 1][3 * j + 2] = 0;
				map[3 * i + 2][3 * j] = 0;
				map[3 * i + 2][3 * j + 1] = 1;
				map[3 * i + 2][3 * j + 2] = 0;
				break;
			case 11:
				map[3 * i][3 * j] = 0;
				map[3 * i][3 * j + 1] = 1;
				map[3 * i][3 * j + 2] = 0;
				map[3 * i + 1][3 * j] = 0;
				map[3 * i + 1][3 * j + 1] = 1;
				map[3 * i + 1][3 * j + 2] = 1;
				map[3 * i + 2][3 * j] = 0;
				map[3 * i + 2][3 * j + 1] = 1;
				map[3 * i + 2][3 * j + 2] = 0;
				break;
			case 12:
				map[3 * i][3 * j] = 0;
				map[3 * i][3 * j + 1] = 0;
				map[3 * i][3 * j + 2] = 0;
				map[3 * i + 1][3 * j] = 1;
				map[3 * i + 1][3 * j + 1] = 1;
				map[3 * i + 1][3 * j + 2] = 0;
				map[3 * i + 2][3 * j] = 0;
				map[3 * i + 2][3 * j + 1] = 1;
				map[3 * i + 2][3 * j + 2] = 0;
				break;
			case 13:
				map[3 * i][3 * j] = 0;
				map[3 * i][3 * j + 1] = 0;
				map[3 * i][3 * j + 2] = 0;
				map[3 * i + 1][3 * j] = 1;
				map[3 * i + 1][3 * j + 1] = 1;
				map[3 * i + 1][3 * j + 2] = 1;
				map[3 * i + 2][3 * j] = 0;
				map[3 * i + 2][3 * j + 1] = 1;
				map[3 * i + 2][3 * j + 2] = 0;
				break;
			case 14:
				map[3 * i][3 * j] = 0;
				map[3 * i][3 * j + 1] = 1;
				map[3 * i][3 * j + 2] = 0;
				map[3 * i + 1][3 * j] = 1;
				map[3 * i + 1][3 * j + 1] = 1;
				map[3 * i + 1][3 * j + 2] = 0;
				map[3 * i + 2][3 * j] = 0;
				map[3 * i + 2][3 * j + 1] = 1;
				map[3 * i + 2][3 * j + 2] = 0;
				break;
			case 15:
				map[3 * i][3 * j] = 0;
				map[3 * i][3 * j + 1] = 1;
				map[3 * i][3 * j + 2] = 0;
				map[3 * i + 1][3 * j] = 1;
				map[3 * i + 1][3 * j + 1] = 1;
				map[3 * i + 1][3 * j + 2] = 1;
				map[3 * i + 2][3 * j] = 0;
				map[3 * i + 2][3 * j + 1] = 1;
				map[3 * i + 2][3 * j + 2] = 0;
				break;
			}
		}
	}
}
void generateRandWall(vector<vector<int>>& map)
{
	vector<vector<int>> a(M / 3, vector<int>(N / 3));
	validMap = true;
	for (int i = 0; i < M / 3; i++)
		for (int j = 0; j < N / 3; j++)
			a[i][j] = -1;
	a[0][0] = 9;
	a[0][N / 3 - 1] = 12;
	a[M / 3 - 1][0] = 3;
	a[M / 3 - 1][N / 3 - 1] = 6;


	a[3][3] = 9;	a[3][4] = 7;	a[3][5] = 7;	a[3][6] = 12;
	a[4][3] = 14;	a[4][4] = 0;	a[4][5] = 0;	a[4][6] = 11;
	a[5][3] = 3;	a[5][4] = 13;	a[5][5] = 13;	a[5][6] = 6;

	for (int i = 0; i < M / 3; i++){
		for (int j = 0; j < N / 3; j++) {
			if (a[i][j] == -1) a[i][j] = sel(a, i, j);
			if (!validMap) return;
		}
	}
	fillmap(map, a);

	vector<Point> b;
	Point tmp;
	bool conti;
	for (int i = 0; i < (slider[3]-1)/10; i++)
	{
		int m, n;
		do
		{
			conti = false;
			m = rand() % M;
			n = rand() % N;
			tmp = { m * l_grid, n * l_grid };
			for (int j = 0; j < b.size(); j++) {
				if (dist(b[j], tmp, 50 * l_grid * l_grid)) conti =true;
			}
		} while (conti || map[m][n] != 1 ||  (m == 16 && n == 22) || (m == 16 && n == 4));
		map[m][n] = 3;
		b.push_back(tmp);
	}


	/*for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ", map[i][j]);
			if (j % 3 == 2)
				printf(" ");
		}
		printf("\n");
		if (i % 3 == 2)
			printf("\n");
	}*/
}
void dfs(int x, int y, vector<vector<int>>& map, vector<vector<bool>> &vis, int &count, int l) {
	if (l > lop) lop = l;
	vis[x][y] = true;
	count++;
	int ntx, nty;
	int sou=0;
	for (int i = 0; i < 4; i++) {
		ntx = (x + mapdir[i].x + M) % M;
		nty = (y + mapdir[i].y + N) % N;
		if (map[ntx][nty] != 0)
			sou++;
	}
	if (sou == 2) l++;
	else l = 0;
	for (int i = 0; i < 4; i++) {
		ntx = (x + mapdir[i].x + M) % M;
		nty = (y + mapdir[i].y + N) % N;
		if (!vis[ntx][nty] && map[ntx][nty] != 0)
			dfs(ntx, nty, map, vis, count, l);
	}
}

void bfs(int x, int y, vector<vector<int>>& map, vector<vector<bool>>& vis, vector<Point> &v, vector<vector<int>> &dis, Point &end) {
	v.push_back({ x,y });
	dis[x][y] = 0;
	vis[x][y] = true;
	Point now, next;
	int d;
	while (!v.empty()) {
		now = v.front();
		end = now;
		d = dis[now.x][now.y];
		if (length < d) length = d;
		v.erase(v.begin());
		for (int i = 0; i < 4; i++) {
			next = { (now.x + mapdir[i].x + M) % M, (now.y + mapdir[i].y + N) % N };
			if (map[next.x][next.y] != 0 && !vis[next.x][next.y]) {
				vis[next.x][next.y] = true;
				dis[next.x][next.y] = d + 1;
				v.push_back(next);
			}
		}
	}
}
void check_map(vector<vector<int>>&map) {
	vector<vector<bool>> vis(M, vector<bool>(N, false));
	vector<vector<bool>> vis2(M, vector<bool>(N, false));
	vector<vector<bool>> vis3(M, vector<bool>(N, false));
	vector<Point> v;
	vector<vector<int>> dis(M, vector<int>(N, 0));
	vector<vector<int>> dis2(M, vector<int>(N, 0));
	Point end;
	int dot = 0;
	int count = 0;
	lop = 0;
	length = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] != 0) {
				if (dot==0) {
					dfs(i, j, map, vis, count, 0);
					bfs(i, j, map, vis2, v, dis, end);
				}
				dot++;
			}
		}
	}
	bfs(end.x, end.y, map, vis3, v, dis2, end);
	if (count != dot) validMap = false;
	else validMap = true;
}

/*vector<vector<int>> map = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
	{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
	{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
	{0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0},
	{0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,3,1,1,1,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,3,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,3,1,1,1,1,1},
	{0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,1,1,1,3,1,1,1,1,1,1,1,3,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
	{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0},
	{0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0},
	{0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
	{0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0},
	{0,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0},
	{0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
	{0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};*/
struct Point {
	int x;
	int y;
};
struct Points {
	double x;
	double y;
};

bool dist(Point &a, Point &b, int d) {
	if (((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)) < d) return true;
	if (((a.x + N * l_grid - b.x) * (a.x + N * l_grid - b.x) + (a.y - b.y) * (a.y - b.y)) < d) return true;
	if (((a.x - N * l_grid - b.x) * (a.x - N * l_grid - b.x) + (a.y - b.y) * (a.y - b.y)) < d) return true;
	if (((a.x - b.x) * (a.x - b.x) + (a.y + M * l_grid - b.y) * (a.y + M * l_grid - b.y)) < d) return true;
	if (((a.x - b.x) * (a.x - b.x) + (a.y + M * l_grid - b.y) * (a.y + M * l_grid - b.y)) < d) return true;
	return false;
}

int dir = 1; //pacman initial direction
int dir2 = 1; //pacman initial direction
int dirr;
Point pacc = { 14 * 15 + 6, 23 * 15 + 6 };
Point pacp = { pacc.x / 15, pacc.y / 15 };
Point pacc2 = { 14 * 15 + 6, 5 * 15 + 6 };
Point pacp2 = { pacc2.x / 15, pacc2.y / 15 };
Point diec = { 14 * 15 + 6, 17 * 15 + 6 };
Point diec2 = { 14 * 15 + 6, 5 * 15 + 6 };
Point pv = { 0,0 };
Point pv2 = { 0,0 };

//Point ghostc[4] = { { 14 * 15 + 6, 11 * 15 + 6 }, {14* 15 + 6, 15 * 15 + 6}, {12 * 15 + 6, 15 * 15 + 6}, {16 * 15 + 6, 15 * 15 + 6} };
Point ghostc[4] = { { 14 * 15 + 6, 11 * 15 + 6 }, {26 * 15 + 6, 26 * 15 + 6}, {26 * 15 + 6, 1 * 15 + 6}, {1 * 15 + 6, 1 * 15 + 6} };
Point ghostp[4] = { {ghostc[0].x / 15, ghostc[0].y / 15}, {ghostc[1].x / 15, ghostc[1].y / 15},{ghostc[2].x / 15, ghostc[2].y / 15},{ghostc[3].x / 15, ghostc[3].y / 15} };
Point gv[4];
bool ghostpaths[M][N];
Point notdir = { 0,0 };
Point mapdir[4] = { {1,0}, {0,1}, {-1,0}, {0,-1} };
Point mp;
Point mv;
Point tmpbi;
vector<Point> bi;
Point initpac;
Point initpac2;
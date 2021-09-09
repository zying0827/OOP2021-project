#include<iostream>
#include<vector>
using namespace std;

void loadwall(vector<vector<int>>& v)
{
    FILE* fp;
    fp = fopen("wall.txt", "r");
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            fscanf_s(fp, "%d ", &v[i][j]);
    fclose(fp);
}

void stdwall(vector<vector<int>>& a, vector<vector<int>>& b) { //a xhange to b

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (a[i][j] == 3) b[i][j] = (big_sign <= 10) ? 30 : 33; // big dot
            if (a[i][j] == 2) b[i][j] = 20; // road (empty)
            if (a[i][j] == 1) b[i][j] = 13; // road (dot)
            if (a[i][j]) continue;
            int sum = 0;
            if (i > 0 && a[(i - 1+M)%M][j]) sum += 1;
            if (i < M - 1 && a[(i + 1)%M][j]) sum += 2;
            if (j > 0 && a[i][j - 1]) sum += 4;
            if (j < N - 1 && a[i][j + 1]) sum += 8;

            if (sum > 0) {
                b[i][j] = sum;
            }
            else {
                if (i > 0 && j > 0 && a[i - 1][j - 1]) sum += 10;
                if (i > 0 && j < N - 1 && a[i - 1][j + 1]) sum += 6;
                if (i < M - 1 && j>0 && a[i + 1][j - 1]) sum += 9;
                if (i < M - 1 && j < N - 1 && a[i + 1][j + 1]) sum += 5;
                b[i][j] = sum;
            }
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (b[i][j] == 2 || b[i][j] == 1 || b[i][j] == 3|| b[i][j] == 7 || b[i][j] == 11) b[i][j] = 4; //left right
            else if (b[i][j] == 4 || b[i][j] == 8 || b[i][j] == 12) b[i][j] = 1; //up down
            else if (b[i][j] == 5) b[i][j] = 2; // right down
            else if (b[i][j] == 9) b[i][j] = 3; // left down
            else if (b[i][j] == 10) b[i][j] = 6; // left up
            else if (b[i][j] == 6) b[i][j] = 5; // right up
            else if (b[i][j] == 20 || b[i][j] == 0 || b[i][j] == 33) b[i][j] = 0; // empty
            else if (b[i][j] == 13) b[i][j] = 7; // dot
            else if (b[i][j] == 30) b[i][j] = 8; // big dot
        }
    }
    if (a[11][15] == 0) y_down = 0;
    else y_down = 1;
    b[11 + y_down][N / 2] = 9;
    b[11 + y_down][N / 2 - 1] = 9;
    b[11 + y_down][N / 2 + 1] = 4;
    b[11 + y_down][N / 2 - 2] = 4;
    big_sign++;
    big_sign %= 20;
    //printf("%d\n", t);
    return;
}

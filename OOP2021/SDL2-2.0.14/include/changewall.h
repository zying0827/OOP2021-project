void imgwall(vector<vector<int>> &a, vector<vector<int>> &b){ //a xhange to b
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            if(a[i][j]) continue;
            int sum=0;
            if(i>0&&a[i-1][j]) sum+=1;
            if(i<M-1&&a[i+1][j]) sum+=2;
            if(j>0&&a[i][j-1]) sum+=4;
            if(j<N-1&&a[i][j+1]) sum+=8;

            if(sum>0){
                b[i][j]=sum;
            } else{
            if(i>0&&j>0&&a[i-1][j-1]) sum+=10;
            if(i>0&&j<N-1&&a[i-1][j+1]) sum+=6;
            if(i<M-1&&j>0&&a[i+1][j-1]) sum+=9;
            if(i<M-1&&j<N-1&&a[i+1][j+1]) sum+=5;
                b[i][j]=sum;
            }
        }
    }
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            if(b[i][j]==2||b[i][j]==1) b[i][j]=4;
            else if(b[i][j]==4||b[i][j]==8) b[i][j]=1;
            else if(b[i][j]==5) b[i][j]=2;
            else if(b[i][j]==9) b[i][j]=3;
            else if(b[i][j]==10) b[i][j]=5;
            else if(b[i][j]==6) b[i][j]=6;
        }
    }
    return;
}

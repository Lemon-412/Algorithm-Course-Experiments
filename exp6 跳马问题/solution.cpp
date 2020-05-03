#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

int vis[10][10]; // minimal time to get there (-1: unvisited)
int d[8][2]={2,1,2,-1,-2,1,-2,-1,1,2,1,-2,-1,2,-1,-2}; // 8 directions

inline bool can_vis(int x,int y){ // check if the chess is out of the board
    if (x<0||x>=8) return false;
    if (y<0||y>=8) return false;
    return true;
}

int main(){
    int x1,x2,y1,y2,curx,cury,nxtx,nxty;
    char in[5];
    while (fgets(in,10,stdin)){ // scan until it reaches '\n'
        x1=in[0]-'a'; // transfer to number
        x2=in[1]-'1';
        y1=in[3]-'a';
        y2=in[4]-'1';
        memset(vis,-1,sizeof(vis)); // set all the places unvisited
        queue<pair<int,int>> que; // a queue for BFS
        que.emplace(x1,x2);
        vis[x1][x2]=0;
        while (!que.empty()){
            curx=que.front().first; // current position x
            cury=que.front().second; // current position y
            que.pop();
            if (curx==y1&&cury==y2){ // already at the destination
                printf("%c%d==>%c%d: %d moves\n",'a'+x1,x2,'a'+y1,y2,vis[curx][cury]);
                break;
            }
            for (int i=0;i<8;++i){ // try to get a next step
                nxtx=curx+d[i][0]; // next position x
                nxty=cury+d[i][1]; //next position y
                if (!can_vis(nxtx,nxty)) continue; // out of the board
                if (vis[nxtx][nxty]!=-1) continue; // already visited
                vis[nxtx][nxty]=vis[curx][cury]+1;
                que.emplace(nxtx,nxty);
            }
        }
    }
    return 0;
}

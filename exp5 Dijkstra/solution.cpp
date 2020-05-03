#include <iostream>
using namespace std;

const int maxn=55;
const int inf=0x3f3f3f3f;

struct node{
    int dis,len,pre;
    node(){}
    node(int d,int l,int p):dis(d),len(l),pre(p){}
    void init(){
        dis=len=pre=inf;
    }
    bool operator<(const node &qmh) const{
        if (dis!=qmh.dis) return dis<qmh.dis;
        if (len!=qmh.len) return len<qmh.len;
        return pre<qmh.pre;
    }
}path[maxn];

bool vis[maxn];
int G[maxn][maxn];

void dijkstra(int n,int s){
    for (int i=1;i<=n;++i){
        vis[i]=false;
        path[i].init();
    }
    vis[s]=true;
    path[s]={0,0,-1};
    for (int i=1;i<=n;++i){
        if (G[s][i]!=-1){
            path[i]={G[s][i],1,s};
        }
    }
    while (true){
        int next=-1;
        for (int i=1;i<=n;++i){
            if (!vis[i]&&(next==-1||path[i].dis<path[next].dis)){
                next=i;
            }
        }
        if (next==-1) break;
        vis[next]=true;
        for (int i=1;i<=n;++i){
            if (vis[i]||G[next][i]==-1) continue;
            node update(path[next].dis+G[next][i],path[next].len+1,next);
            if (update<path[i]){
                path[i]=update;
            }
        }
    }
}

void get_path(int p){
    if (path[p].pre==-1){
        cout<<p<<endl;
        return;
    }
    cout<<p<<"->";
    get_path(path[p].pre);
}

int main(){
    int n,t1,t2,kase=0;
    while (cin>>n){
        for (int i=1;i<=n;++i){
            for (int j=1;j<=n;++j){
                cin>>G[j][i];
            }
        }
        cin>>t1>>t2;
        dijkstra(n,t2);
        cout<<"Case "<<++kase<<endl;
        cout<<"The least distance from "<<t1<<"->"<<t2<<" is "<<path[t1].dis<<endl;
        cout<<"the path is ";
        get_path(t1);
    }
    return 0;
}

/*
8
-1 2 5 -1 -1 -1 -1 100
-1 -1 -1 8 -1 -1 -1 -1
-1 -1 -1 5 -1 -1 -1 -1
-1 -1 -1 -1 3 -1 3 -1
-1 -1 -1 -1 -1 3 -1 -1
-1 -1 -1 -1 -1 -1 -1 3
-1 -1 -1 -1 -1 -1 -1 6
-1 -1 -1 -1 -1 -1 -1 -1
1 8
*/

#include <iostream>
#include <iomanip>
using namespace std;

int cur;
int ans[1025][1025];

// left, upper, scale, the position of the missing block
void dfs(int L,int U,int n,int x,int y){
    int tmp=++cur;
    if (n==2){ // sub problem is in a solvable scale
        for (int i=0;i<2;++i){
            for (int j=0;j<2;++j){
                if (L+i!=x||U+j!=y) ans[L+i][U+j]=tmp;
            }
        }
        return;
    }
    n/=2; // the scale of the sub problem is n/2
    if (x<L+n&&y<U+n)   //top left
        dfs(L,U,n,x,y);
    else{
        dfs(L,U,n,L+n-1,U+n-1);
        ans[L+n-1][U+n-1]=tmp;
    }
    if (x>=L+n&&y<U+n)  //top right
        dfs(L+n,U,n,x,y);
    else{
        dfs(L+n,U,n,L+n,U+n-1);
        ans[L+n][U+n-1]=tmp;
    }
    if (x<L+n&&y>=U+n)  // bottom left
        dfs(L,U+n,n,x,y);
    else{
        dfs(L,U+n,n,L+n-1,U+n);
        ans[L+n-1][U+n]=tmp;
    }
    if (x>=L+n&&y>=U+n) //bottom right
        dfs(L+n,U+n,n,x,y);
    else{
        dfs(L+n,U+n,n,L+n,U+n);
        ans[L+n][U+n]=tmp;
    }
}

int main(){
    int n,x,y,kase=0;
    while (cin>>n>>x>>y){
        n=(1<<n);
        cout<<"Case "<<++kase<<": n="<<n<<endl;
        ans[x][y]=0;
        cur=0;
        dfs(1,1,n,x,y);
        for (int i=1;i<=n;++i){
            for (int j=1;j<=n;++j){
                if (ans[i][j]==0){
                    cout<<"   #";
                }
                else{
                    cout<<setw(4)<<ans[i][j];
                }
            }
            cout<<endl;
        }
    }
    return 0;
}

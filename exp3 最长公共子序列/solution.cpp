#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <bitset>
using namespace std;

string ans;
int from[55][55]; // Graph is created reversed to get more speed.
char a[55],b[55];         // since there all at most three kinds of froms, use integer to save them
int dp[55][55];

void dfs(int x,int y){ // to find all the LCSs
    if (x==0&&y==0){ // print and return if it get the answer
        for (int i=ans.length()-1;i>=0;--i){ // print in the reversed order
            cout<<ans[i]<<' ';
        }
        cout<<endl;
        return;
    }
    if (from[x][y]&1){            // however not all the froms in the original graph end to [m,n]
        dfs(x-1,y);
    }
    if (from[x][y]&2){
        dfs(x,y-1);
    }
    if (from[x][y]&4){
        ans.push_back(a[x]);
        dfs(x-1,y-1);
        ans.erase(--ans.end()); // to save time
    }
}

int main(){
    int T,kase=0,n,m;
    cin>>T;
    while (T--){
        cin>>m>>n;
        for (int i=0;i<=m;++i){ // initialization
            for (int j=0;j<=n;++j){
                dp[i][j]=0;
            }
        }
        for (int i=1;i<=m;++i){
            from[i][0]=1; // required for tracing back
            cin>>a[i];
        }
        for (int i=1;i<=n;++i){
            from[0][i]=2; // required for tracing back
            cin>>b[i];
        }
        for (int i=1;i<=m;++i){
            for (int j=1;j<=n;++j){
                dp[i][j]=a[i]==b[j]?dp[i-1][j-1]+1:max(dp[i][j-1],dp[i-1][j]);
                from[i][j]=0;
                if (dp[i][j]==dp[i-1][j]){
                    from[i][j]|=1;  // from[i][j]==1: [i,j]->[i-1,j]
                }
                if (dp[i][j]==dp[i][j-1]){
                    from[i][j]|=2; // from[i][j]==-1: [i,j]->[i,j-1]
                }
                if (dp[i][j]==dp[i-1][j-1]+1&&a[i]==b[j]){
                    from[i][j]|=4;  // from[i][j]==0: [i,j]->[i-1,j-1]
                }
            }
        }
        cout<<endl<<"Case "<<++kase<<endl;
        cout<<"LCS(X, Y) = "<<dp[m][n]<<endl<<endl;;
        ans="";
        dfs(m,n);
        cout<<endl;
        for (int i=0;i<=m;++i){
            for (int j=0;j<=n;++j){
                cout<<setw(3)<<dp[i][j];
            }
            cout<<endl;
        }
        cout<<endl;
        for (int i=0;i<=m;++i){
            for (int j=0;j<=n;++j){
                cout<<setw(4)<<((bitset<3>)from[i][j]);
            }
            cout<<endl;
        }
        cout<<endl;
    }
    return 0;
}
/*
1
10 10
a a a a a a a a a a
b b b b b b b b b b
*/

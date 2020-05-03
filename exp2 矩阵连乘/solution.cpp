#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
#define x first
#define y second
#define INF 10000000 // big enough for this problem

pair<int,int> a[30]; // represents the size of each matrix
pair<int,int> lfa[30][30]; // {a,b}=lfa[x][y] means the optimized left parent of matrix[x to y] is matrix[a to b]
pair<int,int> rfa[30][30]; // {c,d}=rfa[x][y] means the optimized right parent of matrix[x to y] is matrix[c to d]
// apparently a==x && d==y
int L[30],R[30]; // the amount of "["s and "]"s before each matrix
int dp[30][30]; // dp[x][y] equals to the optimized cost to merge matrix[x to y]
int n;

void init(){
    for (int i=0;i<30;++i)
        for (int j=0;j<30;++j)
            dp[i][j]=INF;
    for (int i=0;i<30;++i)
        dp[i][i]=0; // the cost of a single matrix is 0
    for (int i=0;i<n-1;++i)
        dp[i][i+1]=a[i].x*a[i].y*a[i+1].y; // the cost of two connect matrix
    for (int i=0;i<30;++i)
        for (int j=0;j<30;++j)
            lfa[i][j]=rfa[i][j]=make_pair(i,j); // update where the answer is from
    memset(L,0,sizeof(L));
    memset(R,0,sizeof(R));
    --L[0];--R[n-1]; // remove the abundant outer "[]"
}

void dfs(pair<int,int> a){ // dfs to get the answer
    int l=a.x,r=a.y;
    if (l!=r){
        ++L[l];++R[r];
    }
    if (lfa[l][r]!=a) dfs(lfa[l][r]); // a is a single matrix == ( lfa[a.x][a.y]==a )
    if (rfa[l][r]!=a) dfs(rfa[l][r]);
//    printf("(%d,%d)\n",l,r);
}

int main(){
    int T,tmp,kase=0;
    while (~scanf("%d",&n)){ // scanf returns -1 if it reaches EOF, ~(-1)==0==false
        memset(a,0,sizeof(a));
        scanf("%d",&a[0].x);
        for (int i=0;i<n;++i){
            scanf("%d",&a[i].y);
            a[i+1].x=a[i].y;
        }
        a[n].x=0;
        init();
        for (int i=2;i<=n;++i){
            for (int j=0;j+i<n;++j){
                for (int k=0;k<=i-1;++k){
//                    dp[j to j+i] =====> min (dp[j to j+k] + dp[j+k+1 to j+i] + cost) for each k
                    tmp=dp[j][j+i];
                    dp[j][j+i]=min(dp[j][j+i],dp[j][j+k]+dp[j+k+1][j+i]+(a[j].x)*(a[j+k].y)*(a[j+i].y));
                    if (dp[j][j+i]!=tmp){ // update if the cost changes
                        lfa[j][j+i]=make_pair(j,j+k);
                        rfa[j][j+i]=make_pair(j+k+1,j+i);
                    }
                }
            }
        }
        dfs(make_pair(0,n-1)); // get the final answer
        printf("Case %d\n%d ",++kase,dp[0][n-1]);
        for (int i=0;i<n;++i){
            for (int j=0;j<L[i];++j) putchar('(');
            printf("A%d",i+1);
            for (int j=0;j<R[i];++j) putchar(')');
        }
        putchar('\n');
//        for (int j=0;j<n;++j){
//            for (int k=0;k<n;++k){
//                if (dp[j][k]==INF) printf("     .");
//                else printf("%6d",dp[j][k]);
//            }
//            putchar('\n');
//        }
    }
    return 0;
}

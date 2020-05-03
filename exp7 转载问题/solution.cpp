#include <iostream>
#include <string>
using namespace std;

int n,w1,w2,bestw; // w1,w2: the weight the boats can take currently
int a[25];
string ans,bestans; // string that takes the answer

void dfs(int p,int sum){
    if (p==n){
        if (sum>bestw){ // if sum==bestw then the lexicographical order must be lower
            bestw=sum;
            bestans=ans;
        }
        cout<<"answer: "<<sum<<' '<<ans<<endl; // a feasible answer (not necessarily the best)
        return;
    }
    if (a[p]<=w1){ // boat 1 takes
        w1-=a[p];
        ans.push_back('1'); // add 1
        dfs(p+1,sum+a[p]);
        ans.erase(--ans.end()); // delete the 1
        w1+=a[p];
    }
    if (a[p]<=w2){ // boat 2 takes
        w2-=a[p];
        ans.push_back('0');
        dfs(p+1,sum);
        ans.erase(--ans.end());
        w2+=a[p];
    }
}

int main(){
    int kase=0;
    while (cin>>n){ // do until EOF
        int sum=0;
        for (int i=0;i<n;++i){
            cin>>a[i];
            sum+=a[i];
        }
        cin>>w1>>w2;
        cout<<"Case "<<++kase<<endl;
        if (sum>w1+w2){ // obviously "No"
            cout<<"No"<<endl;
            continue;
        }
        bestw=-1;
        ans=bestans="";
        dfs(0,0); // O(2^n) to find all the solutions
        if (bestw==-1){
            cout<<"No"<<endl; // still possible that there is no solution existing
        }
        else{
            cout<<"Best answer: "<<bestw<<' '<<bestans<<endl; // else output the best solution
        }
    }
    return 0;
}

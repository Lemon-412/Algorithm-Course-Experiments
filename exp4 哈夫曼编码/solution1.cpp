#include <cstdio>
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

int cnt;
int num[100];
stack<int> sta[100];  // the answer of each input

struct node{
    int v,id; //v: the value of the tree; id: the time order of the tree
    vector<int> content; // collapse its subtree to a vector
    void init(){
        content.clear();
    }
    bool operator <(const node& qmh) const{ // for priority queue
        if (v==qmh.v) return id<qmh.id;
        return v>qmh.v; // value is for the first priority
    }
};

priority_queue<node> que; // the current forest in ascending order

node merge(node a,node b){// merge two trees into a new one
    node ret;
    ret.v=a.v+b.v; // value accumulates
    ret.id=cnt++; // time order
    for (auto& i:a.content){
        ret.content.push_back(i);
        sta[i].push(1); // left child push 1
    }
    for (auto& i:b.content){
        ret.content.push_back(i);
        sta[i].push(0); // right child push 0
    }
    return ret;
}

int main(){
    int T,n;
    scanf("%d",&T);
    node tmp,t1,t2;
    for (int kase=1;kase<=T;++kase){
        cnt=0;
        scanf("%d",&n);
        while (!que.empty()) que.pop();
        for (int i=0;i<n;++i){
            tmp.init();
            while (!sta[i].empty()) sta[i].pop();
            scanf("%d",&num[i]);
            tmp.v=num[i];
            tmp.id=cnt++;
            tmp.content.push_back(i); // a new tree
            que.push(tmp);
        }
        while (true){
            t1=que.top();que.pop();
            if (que.empty()) break; // mere tree remain, mission done
            t2=que.top();que.pop();
            que.push(merge(t1,t2)); // more than one tree, merge and push
        }
        printf("Case %d\n",kase);
        for (int i=0;i<n;++i){ // output each answer
            printf("%d ",num[i]);
            while (!sta[i].empty()){
                printf("%d",sta[i].top());
                sta[i].pop();
            }
            putchar('\n');
        }
        putchar('\n');
    }
    return 0;
}

#include <iostream>
#include <queue>
#include <cassert>
using namespace std;

class Huffman_Tree_Node{
public:
    int value,id; // only leaves use id to represent the input order
    Huffman_Tree_Node *left_child,*right_child;
    Huffman_Tree_Node(int v=0,Huffman_Tree_Node *l=NULL,Huffman_Tree_Node *r=NULL):value(v),left_child(l),right_child(r){}
    inline void set_id(int x){
        id=x;
    }
};

class Huffman_Tree{
protected:
    int depth,id; // id represents the time order of the tree
    Huffman_Tree_Node *root; // the root of the tree

    void clear(Huffman_Tree_Node *p){ // release memory
        if (p==NULL) return;
        clear(p->left_child);
        clear(p->right_child);
        delete p;p=NULL;
    }

public:
    ~Huffman_Tree(){clear();}

    Huffman_Tree(int value,int c){ // create a tree with an only root
        root=new Huffman_Tree_Node(value);
        root->set_id(c);
        depth=1;id=c;
    }

    Huffman_Tree(Huffman_Tree *l,Huffman_Tree *r,int c){ // create a tree with two subtrees
        assert(l!=NULL);assert(r!=NULL);
        root=new Huffman_Tree_Node(l->get_value()+r->get_value(),l->root,r->root);
        depth=max(l->depth,r->depth)+1;id=c;
    }

    inline int get_depth()const{
        return depth;
    }

    inline int get_value() const{
        assert(root!=NULL);
        return root->value;
    }

    inline Huffman_Tree_Node* get_root() const{
        assert(root!=NULL);
        return root;
    }

    void clear(){
        clear(root);
        root=NULL;
        depth=-1;
    }

    bool operator<(const Huffman_Tree& qmh) const{ // for use of priority queue
        if (get_value()==qmh.get_value()) return id<qmh.id;
        return get_value()>qmh.get_value(); // value of the whole tree is of the first priority
    }
};

struct cmp{
    bool operator()(const Huffman_Tree* a,const Huffman_Tree* b) const{
        return (*a)<(*b);
    }
};

priority_queue<Huffman_Tree*,vector<Huffman_Tree*>,cmp> que;

Huffman_Tree* merge(int &cnt){
    Huffman_Tree *l,*r,*p;
    while (true){
        l=que.top();que.pop(); // left subtree
        if (que.empty()) return l; // return if the task is done
        r=que.top();que.pop(); // right subtree
        p=new Huffman_Tree(l,r,cnt++); // push a new merged tree
        que.push(p);
    }
}

int num[100];
string ans[100];

void dfs(Huffman_Tree_Node* p,string& cur){ // dfs to get ans, uses & to save time
    if (p->left_child==NULL){
        assert(p->right_child==NULL); // the property of a Huffman tree
        ans[p->id]=cur;
    }
    else{
        assert(p->right_child!=NULL);
        cur.push_back('1'); // right subtree push one
        dfs(p->left_child,cur);
        cur.erase(--cur.end()); // erase it
        cur.push_back('0');  // left subtree push zero
        dfs(p->right_child,cur);
        cur.erase(--cur.end()); // erase it
    }
}

void get_ans(Huffman_Tree* t,int kase,int n){
    cout<<"Case "<<kase<<endl;
    string cur="";
    dfs(t->get_root(),cur); // dfs to get the answers
    for (int i=0;i<n;++i){ // print the answers
        cout<<num[i]<<' '<<ans[i]<<endl;
    }
    cout<<endl;
}

int main(){
    int T,n,x,kase=0;
    cin>>T;
    while (T--){
        int cnt=0;
        cin>>n;
        for (int i=0;i<n;++i){
            cin>>num[i];
            Huffman_Tree* p=new Huffman_Tree(num[i],cnt++); // create a new tree
            que.push(p);
        }
        Huffman_Tree* result=merge(cnt); // merge to get final results
        get_ans(result,++kase,n);
        result->clear(); // release memory
    }
    return 0;
}

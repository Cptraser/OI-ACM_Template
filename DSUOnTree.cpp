#include <bits/stdc++.h>
using namespace std;

namespace IO{
    #define I inline
    I char tc(){static char tr[10000],*A=tr,*B=tr;return A==B&&(B=(A=tr)+fread(tr,1,10000,stdin),A==B)?EOF:*A++;}
    I void read(int &x){char c;for(;(c=tc())<48||c>57;);for(x=c-'0';(c=tc())>47&&c<58;x=(x<<1)+(x<<3)+c-'0');}
//    I void read(int &x){scanf("%d",&x);}
    #undef I
}using namespace IO;

const int N = 1e5+5;

int n,m,root,P,a[N];
//树上启发式合并维护子树信息
class DSUOnTree{
    #define N 100005
    typedef long long LL;
    private:
        int CntCol;
        int head[N],nxt[N<<1],to[N<<1],Cnt;
        int fa[N],siz[N],hvson[N];
        int id[N],rev[N],t[N],idcnt;
        void dfs1(int x,int f){//处理出每个节点的父节点、子树大小和重儿子
            fa[x]=f,siz[x]=1,id[x]=++idcnt,rev[idcnt]=x;
            int mxsiz=0;
            for(int i=head[x];~i;i=nxt[i])if(to[i]^f){
                dfs1(to[i],x);
                siz[x]+=siz[to[i]];
                if(mxsiz<siz[to[i]])mxsiz=siz[to[i]],hvson[x]=to[i];
            }
        }
        void Add(int x){
            if(!t[c[x]])++CntCol;
            ++t[c[x]];
        }
        void Del(int x){
            --t[c[x]];
            if(!t[c[x]])--CntCol;
        }
        void dfs2(int x,int fa,int Opt){
            //优先计算轻儿子的答案
            for(int i=head[x];~i;i=nxt[i])if(to[i]^fa&&to[i]^hvson[x]){
                dfs2(to[i],x,1);
            }
            if(hvson[x])dfs2(hvson[x],x,0);//计算重儿子答案
            for(int i=head[x];~i;i=nxt[i])if(to[i]^fa&&to[i]^hvson[x]){
                for(int j=id[to[i]];j<=id[to[i]]+siz[to[i]]-1;++j)Add(rev[j]);
            }//暴力统计子树信息，不统计重儿子信息是因为重儿子的信息会在子树内保留
            Add(x);
            Ans[x]=CntCol;
            if(Opt){//如果当前节点是轻儿子，就删除子树的贡献
                for(int i=id[x];i<=id[x]+siz[x]-1;++i)Del(rev[i]);
            }
        }
    public:
        int c[N],Ans[N];
        void init(int _n,int _root){
            n=_n,root=_root;
            Cnt=idcnt=CntCol=0;
            memset(head,-1,sizeof(head));
            memset(hvson,0,sizeof(hvson));
            memset(id,0,sizeof(id));
            memset(t,0,sizeof(t));
        }
        void AddEdge(int u,int v){
            nxt[Cnt]=head[u],to[Cnt]=v,head[u]=Cnt++;
        }
        void Solve(void){
            dfs1(root,0);
            dfs2(root,0,1);
        }
    #undef N
}T;

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("1.in","r",stdin);
        freopen("1.out","w",stdout);
    #endif
    read(n);
    T.init(n,1);
    for(int i=1,x,y;i<n;++i)read(x),read(y),T.AddEdge(x,y),T.AddEdge(y,x);
    for(int i=1;i<=n;++i)read(T.c[i]);
    T.Solve();
    for(read(m);m;--m){
        int x;read(x);
        printf("%d\n",T.Ans[x]);
    }
    
}
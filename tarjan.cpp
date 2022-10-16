#include <bits/stdc++.h>
using namespace std;

class Tarjan{
    private:
        #define N 1000005
        vector<int>A[N];
        queue<int>Q;
        int n,m;
        int tim,dfn[N],low[N];
        int st[N],top;
        int vis[N],clo[N],clt;
        int head[N],nxt[N],to[N],Cnt,x,y,dg[N];
        #undef N
        void tarjan(int x){
            st[++top]=x,dfn[x]=low[x]=++tim,vis[x]=1;
            for(int i=head[x];~i;i=nxt[i]){
                if(!dfn[to[i]])tarjan(to[i]),low[x]=min(low[x],low[to[i]]);
                else if(vis[to[i]])low[x]=min(low[x],dfn[to[i]]);
            }
            if(dfn[x]==low[x]){
                ++clt;do{
                    int p=st[top];clo[p]=clt;vis[p]=0;
                }while(st[top--]^x);
            }
        }
    public:
        void init(int _n,int _m){
            n=_n,m=_m;
            Cnt=top=clt=0;
            memset(head,-1,sizeof(head));
            memset(dfn,0,sizeof(dfn));
            memset(low,0,sizeof(low));
            memset(vis,0,sizeof(vis));
            memset(dg,0,sizeof(dg));
        }
        void AddEdge(int u,int v){
            nxt[Cnt]=head[u],to[Cnt]=v,head[u]=Cnt++;
        }
        void ShrinkSpot(){
	        for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
            for(int i=1;i<=n;i++)
                for(int j=head[i];j;j=nxt[j])if(clo[i]^clo[to[j]]){
                    A[clo[i]].push_back(clo[to[j]]),++dg[clo[to[j]]];
                }
        }
};

int main(){

}
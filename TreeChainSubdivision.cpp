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
class TreeChainSubdivision{
    #define N 100005
    typedef long long LL;
    private:
        int n,root;
        int head[N],nxt[N<<1],to[N<<1],Cnt;
        int dep[N],fa[N],siz[N],hvson[N];
        int id[N],idcnt,na[N],top[N];
        LL Seg[N<<2],lazy[N<<2];
        void update(int Node){Seg[Node]=Seg[Node<<1]+Seg[Node<<1|1];}
        void PushDown(int Node,int L,int R){
            if(!lazy[Node])return ;
            lazy[Node<<1]+=lazy[Node];
            lazy[Node<<1|1]+=lazy[Node];
            Seg[Node<<1]+=lazy[Node]*L;
            Seg[Node<<1|1]+=lazy[Node]*R;
            lazy[Node]=0;
        }
        void Build(int Node,int L,int R){
        	if(L==R)return (void)(Seg[Node]=na[L]);
        	int Mid=L+R>>1;
        	Build(Node<<1,L,Mid);
        	Build(Node<<1|1,Mid+1,R);
        	update(Node);
        	return ;
		}
        LL QuerySection(int Node,int L,int R,int Ql,int Qr){
            if(L>R)return 0;
            if(Ql<=L&&R<=Qr)return Seg[Node];
            int Mid=L+R>>1;
			long long res=0;
            PushDown(Node,Mid-L+1,R-Mid);
            if(Mid>=Ql)res+=QuerySection(Node<<1,L,Mid,Ql,Qr);
            if(Mid< Qr)res+=QuerySection(Node<<1|1,Mid+1,R,Ql,Qr);
            update(Node);
            return res;
        }
        void ModifySection(int Node,int L,int R,int Ml,int Mr,int v){
            if(L>R)return ;
            if(Ml<=L&&R<=Mr){
                lazy[Node]+=v;
                Seg[Node]+=1ll*v*(R-L+1);
                return ;
            }
            int Mid=L+R>>1;
            PushDown(Node,Mid-L+1,R-Mid);
            if(Mid>=Ml)ModifySection(Node<<1,L,Mid,Ml,Mr,v);
            if(Mid< Mr)ModifySection(Node<<1|1,Mid+1,R,Ml,Mr,v);
            update(Node);
            return ;
        }
        void dfs1(int x,int f,int deep){//处理出每个节点的深度、父节点、子树大小和重儿子
            dep[x]=deep,fa[x]=f,siz[x]=1;
            int mxsiz=0;
            for(int i=head[x];~i;i=nxt[i])if(to[i]^f){
                dfs1(to[i],x,deep+1);
                siz[x]+=siz[to[i]];
                if(mxsiz<siz[to[i]])mxsiz=siz[to[i]],hvson[x]=to[i];
            }
        }
        void dfs2(int x,int Ltop){//按dfs序标号、处理每条链,Ltop表示链的顶端
            id[x]=++idcnt;
            na[idcnt]=a[x];
            top[x]=Ltop;
            if(!hvson[x])return ;
            dfs2(hvson[x],Ltop);
            for(int i=head[x];~i;i=nxt[i])if(to[i]^hvson[x]&&to[i]^fa[x]){
                dfs2(to[i],to[i]);
            }
        }
    public:
        int a[N];
        void init(int _n,int _root){//初始化函数，n点数，root树根
            n=_n,root=_root;
            Cnt=idcnt=0;
            memset(head,-1,sizeof(head));
        }
        void AddEdge(int u,int v){//前向星加边
            nxt[Cnt]=head[u],to[Cnt]=v,head[u]=Cnt++;
        }
        void Solve(void){//主体函数
        	dfs1(root,0,1),dfs2(root,root),Build(1,1,n);
		}
        int LCA(int x,int y){//求LCA
            while(top[x]^top[y]){
                if(dep[top[x]]<dep[top[y]])swap(x,y);
                x=fa[top[x]];
            }
            return dep[x]>dep[y]?y:x;
        }
        LL QueryRoute(int x,int y){//查询两点路径信息
            LL res=0;
            while(top[x]^top[y]){//x、y不在一条链上
                if(dep[top[x]]<dep[top[y]])swap(x,y);//让x所在链作为深度更深的点
                res+=QuerySection(1,1,n,id[top[x]],id[x]);
                x=fa[top[x]];
            }
            if(dep[x]>dep[y])swap(x,y);
            res+=QuerySection(1,1,n,id[x],id[y]);
            return res;
        }
        void ModifyRoute(int x,int y,int c){//维护两点路径信息
            while(top[x]^top[y]){
                if(dep[top[x]]<dep[top[y]])swap(x,y);
                ModifySection(1,1,n,id[top[x]],id[x],c);
                x=fa[top[x]];
            }
            if(dep[x]>dep[y])swap(x,y);
            ModifySection(1,1,n,id[x],id[y],c);
        }
        LL QuerySubtree(int x){//查询子树信息
            return QuerySection(1,1,n,id[x],id[x]+siz[x]-1);
        }
        void ModifySubtree(int x,int c){//修改子树信息
            return (void)(ModifySection(1,1,n,id[x],id[x]+siz[x]-1,c));
        }
        int GetDis(int x,int y){//查询两点简单路径距离
            return dep[x]+dep[y]-2*dep[LCA(x,y)];
        }
    #undef N
}T;

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("1.in","r",stdin);
        freopen("1.out","w",stdout);
    #endif
    read(n),read(m),read(root);
    T.init(n,root);
    for(int i=1;i<=n;++i)read(T.a[i]);
    for(int i=1,x,y;i<n;++i){
        read(x),read(y);
        T.AddEdge(x,y),T.AddEdge(y,x);
    }
    T.Solve();
    for(int opt,x,y,c;m;--m){
        read(opt);
        switch(opt){
            case 1:read(x),read(y),read(c);T.ModifyRoute(x,y,c);break;
            case 2:read(x),read(y);printf("%lld\n",T.QueryRoute(x,y));break;
            case 3:read(x),read(c);T.ModifySubtree(x,c);break;
            case 4:read(x);printf("%lld\n",T.QuerySubtree(x));break;
        }
    }
}
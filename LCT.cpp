// luogu-judger-enable-o2
#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;

char tc(){static char tr[10000],*A=tr,*B=tr;return A==B&&(B=(A=tr)+fread(tr,1,10000,stdin),A==B)?EOF:*A++;}
void read(int &x){char c;for(;!isdigit(c=tc()););for(x=c-48;isdigit(c=tc());x=(x<<1)+(x<<3)+c-48);}

const int Size=1<<19;

class LinkCutTree{
    typedef long long LL;
    #define N 300005
    #define P 51061
    private:
        int Fa[N],tr[N][2],st[N],Lazy1[N],Lazy2[N],sz[N];
        bool r[N];
        bool nroot(int x){return tr[Fa[x]][0]==x||tr[Fa[x]][1]==x;}
        void PushUp(int x){s[x]=(s[tr[x][0]]+s[tr[x][1]]+v[x])%P;sz[x]=sz[tr[x][0]]+sz[tr[x][1]]+1;}
        void PushRev(int x){swap(tr[x][0],tr[x][1]),r[x]^=1;}
        void PushAdd(int x,int c){s[x]+=(LL)c*sz[x]%P,s[x]%=P;Lazy1[x]+=c,Lazy1[x]%=P;v[x]+=c,v[x]%=P;}
        void PushMul(int x,int c){Lazy2[x]=(LL)Lazy2[x]*c%P;Lazy1[x]=(LL)Lazy1[x]*c%P;s[x]=(LL)s[x]*c%P;v[x]=(LL)v[x]*c%P;}
        void PushDown(int x){
            if(Lazy2[x]!=1)PushMul(tr[x][0],Lazy2[x]),PushMul(tr[x][1],Lazy2[x]),Lazy2[x]=1;
            if(Lazy1[x])   PushAdd(tr[x][0],Lazy1[x]),PushAdd(tr[x][1],Lazy1[x]),Lazy1[x]=0;
            if(r[x]){
                if(tr[x][0])PushRev(tr[x][0]);
                if(tr[x][1])PushRev(tr[x][1]);
                r[x]=0;
            }
        }
        int Getson(int x){return x==tr[Fa[x]][1];}
        void Rotate(int x){
            int y=Fa[x],z=Fa[y],k=Getson(x),w=tr[x][k^1];
            if(nroot(y))tr[z][tr[z][1]==y]=x;
            tr[x][k^1]=y,tr[y][k]=w;
            if(w)Fa[w]=y;Fa[y]=x,Fa[x]=z;
            PushUp(y),PushUp(x);
        }
        void Splay(int x){
            int y=x,top=0;st[++top]=y;
            while(nroot(y))st[++top]=y=Fa[y];
            while(top)PushDown(st[top--]);
            for(int S;S=Fa[x],nroot(x);Rotate(x))if(nroot(S))
                Rotate(Getson(x)==Getson(S)?S:x);
            PushUp(x);
        }
        void access(int x){for(int y=0;x;x=Fa[y=x])Splay(x),tr[x][1]=y,PushUp(x);}
        void makeroot(int x){access(x),Splay(x),PushRev(x);}//in truely-tree
        int findroot(int x){access(x),Splay(x);while(tr[x][0])PushDown(x),x=tr[x][0];Splay(x);return x;}
        void Split(int x,int y){makeroot(x),access(y),Splay(y);}
    public:
        int v[N],s[N];
        int QueryRoute(int x,int y){Split(x,y);return s[y];}//查询两点路径上的维护值(此处为路径点权和)
        void Link(int x,int y){makeroot(x);if(findroot(y)^x)Fa[x]=y;}//连接两个点
        void Cut(int x,int y){makeroot(x);if(findroot(y)==x&&Fa[y]==x&&!tr[y][0])Fa[y]=tr[x][1]=0,PushUp(x);}//分离两个点
        void AddRoute(int x,int y,int c){Split(x,y),PushAdd(y,c);}//路径加
        void MulRoute(int x,int y,int c){Split(x,y),PushMul(y,c);}//路径减
        // void ModifyDist(int x,int y){Splay(x),v[x]=y;}//将x点的权值改为y
    #undef N
    #undef P
}T;





int n,m;
int main()
{

}
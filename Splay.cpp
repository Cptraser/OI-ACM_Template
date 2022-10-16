#include <cstdio>
#include <cstring>
using namespace std;

int read()
{
    char c;while(c=getchar(),(c<'0'||c>'9')&&c!='-');
    int x=0,y=1;c=='-'?y=-1:x=c-'0';
    while(c=getchar(),c>='0'&&c<='9')x=x*10+c-'0';
    return x*y;
}

int N;

class Splay{
	#define N 1000005
	private:
	    int tr[N][2],tot[N];
	    int f[N],fa[N],cnt,dist;
	    void clear(int x){tr[x][0]=tr[x][1]=f[x]=fa[x]=tot[x]=v[x]=0;}//清除节点信息
	    void up(int x){f[x]=f[tr[x][0]]+f[tr[x][1]]+tot[x];}//更新节点信息
	    int get(int x){return tr[fa[x]][1]==x;}//which son of father
	    void rotate(int &x){
	        int ol=fa[x],olol=fa[ol],to=get(x);
	        tr[ol][to]=tr[x][to^1];fa[tr[x][to^1]]=ol;
	        fa[ol]=x;tr[x][to^1]=ol;
	        fa[x]=olol;
	        if(olol)//如果该节点的父亲的父亲存在
	            tr[olol][tr[olol][1]==ol]=x;
	        up(ol);up(x);//这里一定要先更新ol，在更新x，想想为什么
	    }	    
		void splay(int x){
	        for(int S;S=fa[x];rotate(x))//先旋x
	            if(fa[S])//S不为根
	                rotate((get(x)==get(S)?S:x));//判断是否三点一线
	        root=x;
	    }	    
		void insert(int &x,int val,int pos){
	        if(!x){//插入
	            x=++cnt;
	            f[x]=tot[x]=1,v[x]=val,fa[x]=pos;
	            dist=x;//记录节点
	            return ;
	        }
	        if(val==v[x]){dist=x,tot[x]++;return ;}//有一样的数
	        insert(tr[x][val>v[x]],val,x);
	        up(x);//更新
	        return ;
	    }
	    void pre(int x,int val){//前驱
	        if(!x)return ;
	        if(val<=v[x])return pre(tr[x][0],val);
	        else dist=x,pre(tr[x][1],val);
	    }
	    void bac(int x,int val){//后继
	        if(!x)return ;
	        if(v[x]<=val)bac(tr[x][1],val);
	        else dist=x,bac(tr[x][0],val);
	    }
	public:
		int root,v[N];
	    void init(){
	        memset(tr,0,sizeof tr);
	        memset(v,0,sizeof v);
	        memset(tot,0,sizeof tot);
	        memset(f,0,sizeof f);
	        cnt=root=dist=0;
	    }//初始化
		void Insert(int x){insert(root,x,0),splay(dist);}//插入一个点
	    int QueryX(int x,int val){//查询x的排名
	        if(!x)return 0;
	        if(val==v[x])return f[tr[x][0]]+1;
	        int to=val>v[x];
	        return QueryX(tr[x][to],val)+(to?f[tr[x][0]]+tot[x]:0); 
	    }
	    int QueryK(int x,int kth){//查询排名为K的数
	        if(!x)return 0;
	        if(kth<=f[tr[x][0]])return QueryK(tr[x][0],kth);
	        if(kth>f[tr[x][0]]+tot[x])return QueryK(tr[x][1],kth-(f[tr[x][0]]+tot[x]));
	        return v[x];
	    }
		int FindPre(int x){dist=0;pre(root,x);return dist;}//查询前驱
		int FindBac(int x){dist=0;bac(root,x);return dist;}//查询后继
	    int find(int x,int val){//在del之前先找节点，记录，并Splay
	        if(!x)return 0;
	        if(v[x]==val){splay(x);return x;}//找到
	        int to=val>v[x];
	        return find(tr[x][to],val);
	    }
	    void del(int x){//删除
	        int kkk=find(root,x);
	        if(!kkk)return ;//不存在
	        if(tot[root]>1){
	            tot[root]--,up(root);
	            return ;
	        }
	        if(!tr[root][0]&&!tr[root][1]){
	            clear(root),root=0;
	            return ;
	        }
	        if(!(tr[root][0]*tr[root][1])){
	            int rt=root;
	            root=tr[root][0]+tr[root][1];
	            fa[root]=0,clear(rt);//细节是要先记录root，再更新root，再将原来的root clear
	            return ;
	        }
	        int ok=root;//原来的root
	        pre(root,x);//求前驱
	        splay(dist);//Splay到根
	        fa[tr[ok][1]]=root;
	        tr[root][1]=tr[ok][1];
	        clear(ok);up(root);fa[root]=0;//clear，更新，细节是要把新根的fa清零
	        return ;
	    }
	#undef N
}W;

int main()
{
    N=read();
        while(N--){
            int o=read(),x;
                switch(o){
                    case 1:W.Insert(read());break;
                    case 2:W.del(read());break;
                    case 3:printf("%d\n",W.QueryX(W.root,read()));break;
                    case 4:printf("%d\n",W.QueryK(W.root,read()));break;
                    case 5:printf("%d\n",W.FindPre(read()));break;
                    case 6:printf("%d\n",W.FindBac(read()));break;
                }
        }
}
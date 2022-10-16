#include <cstdio>
#include <cstdlib>
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

class Treap{
	#define N 100005
	private:
	    int tr[N][2],cnt,ks[N],tot[N];
	    int f[N],dist;
	    void rotate(int &x,int o){//旋转
	        int k=tr[x][o];
	        tr[x][o]=tr[k][o^1];
	        tr[k][o^1]=x;
	        f[k]=f[x];//更新
	        f[x]=f[tr[x][0]]+f[tr[x][1]]+tot[x];
	        x=k;
	    }	    
		void pre(int x,int val){//前驱
	        if(!x)return ;
	        if(v[x]>=val)pre(tr[x][0],val);
	        else{
	            dist=x;
	            pre(tr[x][1],val);
	        }
	    }
	    void bac(int x,int val){//后继
	        if(!x)return ;
	        if(v[x]<=val)bac(tr[x][1],val);
	        else{
	            dist=x;
	            bac(tr[x][0],val);
	        }
	    }
	public:
		int root,v[N];
	    void init(){//初始化函数
	        memset(tr,0,sizeof tr);
	        memset(ks,0,sizeof ks);
	        memset(v,0,sizeof v);
	        cnt=dist=0;
	    }
	    void Insert(int &x,int val){//插入节点
	        if(!x){
	            x=++cnt;
	            ks[x]=rand();
	            v[x]=val;
	            tot[x]=1;//当前节点共有几个相同的值
	            f[x]=1;
	            return ;
	        }f[x]++;//统计当前这个节点的子树共有几个节点
	        if(val==v[x]){tot[x]++;return ;}
	        int to=val>v[x];
	        Insert(tr[x][to],val);
	        if(ks[tr[x][to]]>ks[x])rotate(x,to);//不满足堆的性质，Rotate
	        return ;
	    }
	    void Delete(int &x,int val){//删除
	        if(!x)return ;
	        if(val==v[x]){
	            if(tot[x]>1){tot[x]--;f[x]--;return ;}
	            if(!tr[x][0]&&!tr[x][1]){v[x]=tot[x]=ks[x]=0;x=0;return ;}
	            if(!(tr[x][0]*tr[x][1])){
	                x=tr[x][0]+tr[x][1];
	                return ;
	            }
	            rotate(x,0);
	            Delete(x,val);//递归向下
	            return ;
	        }
	        int to=val>v[x];
	        f[x]--;//减去总结点数
	        Delete(tr[x][to],val);
			f[x]=f[tr[x][0]]+f[tr[x][1]]+tot[x];
	        return ;
	    }
	    int QueryX(int x,int val){//查询X的排名
	        if(!x)return 0;
	        if(v[x]==val)return f[tr[x][0]]+1;//小细节，可以直接return左子树总结点+1
	        int to=val>v[x];
	        return QueryX(tr[x][to],val)+(to?(f[tr[x][0]]+tot[x]):0);//如果是访问右子树retun之后要加上f[tr[x][0]]+tot[x]
	    }
	    int QueryK(int x,int kth){//查询排名为X的数
	        if(!x)return 0;
	        if(kth<=f[tr[x][0]])return QueryK(tr[x][0],kth);//在左子树
	        if(kth>f[tr[x][0]]+tot[x])return QueryK(tr[x][1],kth-(f[tr[x][0]]+tot[x]));//在右子树
	        return v[x];
	    }
		int FindPre(int x){dist=0;pre(root,x);return dist;}//查询前驱
		int FindBac(int x){dist=0;bac(root,x);return dist;}//查询后继
	#undef N
}T;

int main()
{
    int W=19260817;
    srand(W);
    N=read();
    while(N--){
        int o=read(),x=read();
        switch(o){
            case 1:T.Insert(T.root,x);break;
            case 2:T.Delete(T.root,x);break;
            case 3:printf("%d\n",T.QueryX(T.root,x));break;
            case 4:printf("%d\n",T.QueryK(T.root,x));break;
            case 5:printf("%d\n",T.FindPre(x));break;
            case 6:printf("%d\n",T.FindBac(x));break;
        }
    }
}
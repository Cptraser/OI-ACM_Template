#include <bits/stdc++.h>
using namespace std;

class Manacher{
    private:
        string S,P;
        int Mx,j,MaxR;
        void init(void){//下标从0开始
            char c;
            S=P="";
            len=Mx=j=MaxR=0;
            while((c=getchar())>='a'&&c<='z'){
                ++len,S+=c;
            }
        }
        #define max(x,y) ((x)>(y)?(x):(y))
        void GetFn(){
            init(),j=0;
            P+="&#";for(int i=0;i<S.size();i++)P+=S[i],P+='#';P+='~';
            for(int i=1;i<P.size()-1;i++){
                f[i]=Mx>i?min(Mx-i,f[(j<<1)-i]):1;
                while(P[i+f[i]]==P[i-f[i]]&&i+f[i]<P.size())f[i]++;
                if(i+f[i]>Mx)Mx=i+f[i],j=i;
                MaxR=max(MaxR,f[i]);
            }
        }
        #undef max
    public:
        #define N 1000005
        int len,f[N<<1];
        #undef N
        void Solve(void){GetFn();}
        int GetF(int x){return f[x+1<<1]>>1;}//下标从0开始的最大半径(有中心点字符)，无中心点字符需要自行枚举。
        int GetMaxR(void){return MaxR-1;}//返回最大半径
}S;

int main()
{
    S.Solve();
    for(int i=0;i<S.len;++i)printf("%d ",S.GetF(i));puts("");
}
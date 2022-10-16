#include <cstdio>
using namespace std;

class inverse{
    #define N 3000005
    public:
        void GetInvOn(int n,int Mod){
            inv[0]=inv[1]=1;
            for(int i=2;i<=n;++i){
                inv[i]=1ll*(Mod-Mod/i)*inv[Mod%i]%Mod;
            }
        }
        int GetInvOlogn(int x,int P){
            return ksm(x,P-2,P);
        }
        void write_ans(int n){
            for(int i=1;i<=n;i++)printf("%d\n",inv[i]);
        }
    private:
        int inv[N],Mod;
        int ksm(int x,int y,int P){
            int res=1;
            for(;y;y>>=1){
                if(y&1)res=1ll*res*x%P;
                x=1ll*x*x%P;
            }
            return res;
        }
     #undef N
}Inv;

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("1.txt","w",stdout);
    #endif 
    Inv.GetInvOn(100,998244357);
    Inv.write_ans(100);
}
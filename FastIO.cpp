#include <bits/stdc++.h>
using namespace std;
namespace IO{
    #define I inline
    I char tc(){static char tr[10000],*A=tr,*B=tr;return A==B&&(B=(A=tr)+fread(tr,1,10000,stdin),A==B)?EOF:*A++;}
    I void read(int &x){
        char c;int y=1;x=0;
        while(((c=tc())<'0'||c>'9')&&c!='-');c=='-'?y=-1:x=c-'0';
        while((c=tc())>='0'&&c<='9')x=(x<<1)+(x<<3)+c-'0';
        x*=y;
    }
    // I void read(int &x){scanf("%d",&x);}
    #undef I
}using namespace IO;


int main()
{

}
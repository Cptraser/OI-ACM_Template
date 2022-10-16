#include<bits/stdc++.h>
using namespace std;

class KMP{
    public:
        int* GetNext(char* S){
            int j=0,k=-1,n=strlen(S);
            int *next=(int*)malloc(n*sizeof(int));
            next[0]=-1;
            while (j<n-1) {
                if(k==-1 || S[j]==S[k])next[++j]=++k;
                else k=next[k];
            }
            return next;
        }
        void Print(int *nxt,char *s1,char *s2){
            int n,m;
            n=strlen(s1),m=strlen(s2);
            for(int i=0,j=0;i<n;){
                if(j<0||s1[i]==s2[j])++i,++j;
                else j=nxt[j];
                if(j==m)printf("%d\n",i-m+1),j=nxt[j];//输出所有能相匹配的起始点位置
            }
        }
    private:

};

int main()
{
    
}
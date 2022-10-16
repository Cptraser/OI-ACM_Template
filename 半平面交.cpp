#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

void read(int &x){ scanf("%d",&x); }
int read(){ int x;scanf("%d",&x);return x; }

const double EPS = 1e-6, LIM = 10000;
const int N = 1e5+5;
int double_check(double x){ return x>EPS?1:(x<-EPS?-1:0); }//判断x与0的关系
struct Vector{
    double x, y;
    Vector(double X = 0, double Y = 0){ x = X, y = Y; }

    bool operator == (const Vector&b)const
    {
        return double_check(x - b.x)==0 && double_check(y - b.y)==0;
    }
    double angle(void)//求向量对应角度
    {
        return atan2(y,x);
    }
};
typedef Vector Point;
Vector operator + (Vector a, Vector b){ return Vector(a.x+b.x, a.y+b.y); }
Vector operator - (Vector a, Vector b){ return Vector(a.x-b.x, a.y-b.y); }
Vector operator * (Vector a, double b){ return Vector(a.x*b, a.y*b); }
Vector operator / (Vector a, double b){ return Vector(a.x/b, a.y/b); }

struct Line
{
    Point s, t;
    double angle;
    Line(Point X = Vector(), Point Y = Vector())
    {
        s = X, t = Y, angle = (Y-X).angle();
    }
};
typedef Line Segment;
double dot(Vector a, Vector b){ return a.x*b.x + a.y*b.y; }//点积
double cross(Vector a, Vector b){ return a.x*b.y - a.y*b.x; }//叉积
bool is_parallel(Line a,Line b)//判断a,b直线是否平行
{
	return double_check(cross(a.t-a.s,b.t-b.s))==0;
}
Point intersection(Line a,Line b)//求出a,b的交点
{
	return a.s+(a.t-a.s)*(cross(b.t-b.s,a.s-b.s)/cross(a.t-a.s,b.t-b.s));
}
double area(Point *p,int n)//求出多边形的面积
{
	double res=0;
	p[n+1]=p[1];
	for(int i=1; i<=n; ++i){
        res+=cross(p[i],p[i+1]);
    }
	return fabs(res/2);
}
bool operator < (const Line &a,const Line &b)//极角排序，如果极角相同则，选择最靠左的直线
{
	double r=a.angle-b.angle;
	if(double_check(r)!=0)return double_check(r)==-1;
	return double_check(cross(a.t-a.s, b.t-a.s))==-1;
}
bool OnRight(Line a,Point b)//检查b是否在a直线的右边
{
	return double_check(cross(a.t-a.s,b-a.s))==-1;
}
bool SI(Line *l,int n,Point *s,int &m)//增量法求半平面交
{
	static Line que[N];
	static Point que2[N];//两个双端队列
	int head=0,tail=0;
	sort(l+1,l+1+n);
	que[0]=l[1];
	for(int i=2;i<=n;i++)
	if(double_check(l[i].angle-l[i-1].angle)!=0)//极角相等的直线，取一个
	{
		if(head<tail&&(is_parallel(que[head],que[head+1])||is_parallel(que[tail],que[tail-1])))return false;//如果两个直线共线，但是极角不同，则没有半平面交
		while(head<tail&&OnRight(l[i],que2[tail-1]))tail--;//如果在直线右边，删除点
		while(head<tail&&OnRight(l[i],que2[head]))head++;
		que[++tail]=l[i];
		if(head<tail)que2[tail-1]=intersection(que[tail],que[tail-1]);//加入新点
	}
	while(head<tail&&OnRight(que[head],que2[tail-1]))tail--;//删去多余点
	while(head<tail&&OnRight(que[tail],que2[head]))head++;
	if(tail-head<=1)return false;//只有一个点或零个点，没有半平面交
	que2[tail]=intersection(que[head],que[tail]);//加入最后一条边，和第一条边的交点
	m=0;
	for(int i=head;i<=tail;i++)s[++m]=que2[i];
	return true;
}
int n,m;
Line l[N];
Point p[N];
double Solve(void){
    Point a = Point(0,0), b = Point(LIM, 0), c = Point(LIM, LIM), d = Point(0, LIM);
    l[++n] = Line(a, b), l[++n] = Line(b, c), l[++n] = Line(c, d), l[++n] = Line(d, a);
    if(!SI(l,n,p,m))return 0;
    return area(p,m);
}
int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; ++i){
        double a, b, c, d;
        scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
        l[i] = Line(Point(a, b),Point(c, d));
    }
    printf("%.1f\n",Solve());
}
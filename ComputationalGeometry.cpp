#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;
const int N = 1e5+5;

/*---------------------------Point-&-Vector-----------------------------*/
int double_check(double x){ return x>EPS?1:(x<-EPS?-1:0); }//判断x与0的关系
struct Vector{
    double x, y;
    Vector(double X = 0, double Y = 0){ x = X, y = Y; }

    bool operator == (const Vector&a)const
    {
        return double_check(x - a.x)==0 && double_check(y - a.y)==0;
    }
    bool operator < (const Vector&a)const//先按照横坐标再按照纵坐标排序 
    {
        return x!=a.x ? x<a.x : y<a.y;
    }
    double angle(void)//求向量对应角度
    {
        return atan2(y,x);
    }
    double length(void)//求向量长度
    {
        return sqrt(x*x+y*y);
    }
};
typedef Vector Point;
Vector operator + (Vector a, Vector b){ return Vector(a.x+b.x, a.y+b.y); }
Vector operator - (Vector a, Vector b){ return Vector(a.x-b.x, a.y-b.y); }
Vector operator * (Vector a, double b){ return Vector(a.x*b, a.y*b); }
Vector operator / (Vector a, double b){ return Vector(a.x/b, a.y/b); }
double distance(Point x, Point y)//求两点的欧几里得距离
{
    return sqrt((x.x-y.x)*(x.x-y.x) + (x.y-y.y)*(x.y-y.y));
}
Vector rotate(Vector a, double rad)//逆时针旋转向量
{
    return Vector(a.x*cos(rad)-a.y*sin(rad),a.x*sin(rad)+a.y*cos(rad));
}

/*---------------------------Line-&-Segment-----------------------------*/
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
bool operator < (const Line &a, const Line &b)//极角排序，如果极角相同则，选择最靠左的直线
{
    double r=a.angle-b.angle;
    if(double_check(r)!=0)return double_check(r)==-1;
    return double_check(cross(a.t-a.s, b.t-a.s))==-1;
}
bool is_parallel(Line a, Line b)//判断a,b直线是否平行
{
	return double_check(cross(a.t-a.s,b.t-b.s))==0;
}
bool is_on_segment(Line a, Point b)//判断点是否在线段上
{
	return double_check(cross(b-a.s, a.t-a.s))==0 && ((a.s.x<=b.x&&b.x<=a.t.x)||(a.s.x>=b.x&&b.x>=a.t.x)); 
}
Point intersection(Line a, Line b)//求出a,b的交点
{
	return a.s+(a.t-a.s)*(cross(b.t-b.s,a.s-b.s)/cross(a.t-a.s,b.t-b.s));
}
bool SegmentProperIntersection(Segment s1, Segment s2)//两线段规范相交、即每条线段的端点分别在另一条一段的两侧 
{
    Point a1 = s1.s, b1 = s1.t, a2 = s2.s, b2 = s2.t;
    double c1=cross(b1-a1,a2-a1),c2=cross(b1-a1,b2-a1);
    double c3=cross(b2-a2,a1-a2),c4=cross(b2-a2,b1-a2);
    return double_check(c1)*double_check(c2)<0 && double_check(c3)*double_check(c4)<0;
}
bool on_which_side(Line a, Point b, int opt)//检查点b是否在直线a的右边(-1),左边(1),直线上(0)
{
	return double_check(cross(a.t-a.s,b-a.s))==opt;
}
double Point_distance_to_Line(Point P, Line L)//点到直线的有向距离（距离加绝对值） 
{
    Vector AB = L.t - L.s, AP = P-L.s;
    return cross(AB, AP) / AB.length();
}


/*-----------------------------------Polygon----------------------------------*/
double triangle_area(Point a, Point b, Point c)//根据三点坐标求三角形面积
{
    return fabs(cross(a-c, b-c)*0.5);
}
double polygon_area(Point *p, int n)//求出多边形的面积(逆时针)
{
	double res=0;
	p[n+1]=p[1];
	for(int i=1; i<=n; ++i){
        res+=cross(p[i],p[i+1]);
    }
	return fabs(res/2);
}
bool is_Point_in_Polygon(Point p, Point *poly, int n)//点在凸多边形内的判定 
{
    int wn=0;
    poly[n+1]=poly[1];
    for(int i=1; i<=n; ++i){
        if(is_on_segment(Segment(poly[i],poly[i+1]), p))return -1;
        int k=double_check(cross(poly[i+1]-poly[i],p-poly[i]));
        int d1=double_check(poly[i].y-p.y);
        int d2=double_check(poly[i+1].y-p.y);
        if(k>0 && d1<=0 && d2>0)wn++;
        if(k<0 && d2<=0 && d1>0)wn--;
    }
    if(wn!=0)return 1;
    return 0;
}
void ConvexHull(Point *p, int n, Point *ch, int &m)//构造逆时针凸包(Andrew)
{
    sort(p+1,p+n+1);//先按照横坐标再按照纵坐标排序 
    m=0;
    for(int i=1; i<=n; ++i){
        while(m>1 && cross(ch[m]-ch[m-1],p[i]-ch[m-1])<=0)m--;
        ch[++m]=p[i];
    }
    int k=m;
    for(int i=n-1; i; i--){
        while(m>k && cross(ch[m]-ch[m-1],p[i]-ch[m-1])<=0)m--;
        ch[++m]=p[i];
    }
    if(n>1)m--;
    return ;
}
const int LIM = 1e3;
bool HalfplaneIntersection(Line *l, int n, Point *s, int &m)//增量法求半平面交
{
    //使用时需要得到在多边形上逆时针顺序的向量组，或者确定向量方向
    //逆时针: 向量右侧; 顺时针: 向量左侧
    Point a = Point(-LIM,-LIM), b = Point(LIM, -LIM), c = Point(LIM, LIM), d = Point(-LIM, LIM);
    l[++n] = Line(a, b), l[++n] = Line(b, c), l[++n] = Line(c, d), l[++n] = Line(d, a);
	static Line que[N];
	static Point que2[N];//两个双端队列
	int head=0, tail=0;
	sort(l+1,l+1+n);
	que[0]=l[1];
	for(int i=2; i<=n; ++i)
	if(double_check(l[i].angle-l[i-1].angle)!=0)//极角相等的直线，取一个
	{
		if(head<tail&&(is_parallel(que[head],que[head+1])||is_parallel(que[tail],que[tail-1])))return false;//如果两个直线共线，但是极角不同，则没有半平面交
		while(head<tail&&on_which_side(l[i], que2[tail-1], -1))tail--;//如果在直线右边，删除点
		while(head<tail&&on_which_side(l[i],que2[head], -1))head++;
		que[++tail]=l[i];
		if(head<tail)que2[tail-1]=intersection(que[tail],que[tail-1]);//加入新点
	}
	while(head<tail&&on_which_side(que[head], que2[tail-1], -1))tail--;//删去多余点
	while(head<tail&&on_which_side(que[tail], que2[head], -1))head++;
	if(tail-head<=1)return false;//只有一个点或零个点，没有半平面交
	que2[tail]=intersection(que[head],que[tail]);//加入最后一条边，和第一条边的交点
	m=0;
	for(int i=head; i<=tail; ++i)s[++m]=que2[i];
	return true;
}
double get_Diameter(Point *p, int n)//旋转卡壳求直径 
{
    int j=2;
    double res = 0;
    for(int i=1; i<=n; ++i){
        while(double_check(cross(p[i+1]-p[i],p[j+1]-p[j]))>0)
        {
            j++;
            j=(j-1)%n+1;
        }
        res = max(res, max(distance(p[i], p[j]), distance(p[i+1], p[j])));
    }
    return res;
}
int main(){
    double a, b, c, d, a0, b0;
    int T, _n, n = 0, m;
    Line *l = new Line[520];
    Point *core = new Point[520];
    for(scanf("%d",&T);T;--T){
        scanf("%d",&_n);
        scanf("%lf%lf",&a,&b);
        a0 = a, b0 = b;
        for(int i=n+1; i<n+_n; ++i){
            scanf("%lf%lf",&c,&d);
            l[i] = Line(Point(a, b),Point(c, d));
            a = c, b = d;
        }
        n+=_n;
        l[n] = Line(Point(a, b),Point(a0, b0));       
    }
    printf("%.3lf", HalfplaneIntersection(l, n, core, m) ? polygon_area(core, m) : 0.0);
}
#include<stdio.h>

#define A1 2.0 //iphone広告戦略(企業力)
#define A2 1 //
#define B1 6 //android広告戦略(企業力)
#define B2 1 //
#define X 0.6 //iphoneのリピート率
#define Y 0.6 //androidのリピート率
#define m 0.7 //androidに比べてiphoneの方がどれだけ魅力的かの定数
//#define f 0.8 //スマホ普及率(固定)

double x1(double x,double y);//新規顧客のiphoneの販売台数(普及率は一旦無視)

double y1(double x,double y);//新規顧客のandroidの販売台数(普及率は一旦無視)

double x1(double x,double y){
    if((A1*m*x - A2*(1-m)*y) > 0){//前回の販売台数が今回の販売台数に影響を受ける
        return ( A1*m*x - A2*(1-m)*y );
    }else{
        return 0;
    }
}

double y1(double x,double y){
    if((B1*(1-m)*y - B2*m*x) > 0){
        return ( B1*(1-m)*y - B2*m*x );
    }else{
        return 0;
    }
}


int main(){
    FILE  *fp;
    double x;
    double y;
    double dtdx;
    double dtdy;
    double sf;//普及率
    double h;//スマホの性能
    double v1;//iphoneの価格上昇率
    double v2;//androidの価格上昇率
    double t;
    double dt;
    double k1[2],k2[2],k3[2],k4[2];

    x = 100.0;
    y = 100.0;
    sf = 0.3;
    h =1.0;
    dt = 1.0;
    fp =fopen("data1.txt","w");
    

    for( t=2007; t<=2017.5; t+=dt ){
        
        fprintf(fp,"%f %lf %lf\n",t, x, y);
        printf("%f %lf %lf %f %f %f\n",t, x, y,sf,h,sf*h*( k1[0] + 2.0*k2[0] + 2.0*k3[0] + k4[0] ) / 6.0);
        
        sf +=0.025;
        h +=0.05;
        
        //４次ルンゲクッタ法
        k1[0] = dt * x1( x, y );
        k1[1] = dt * y1( x, y );

        k2[0] = dt * x1( x+x/2.0, y+y/2.0 );
        k2[1] = dt * y1( x+x/2.0, y+y/2.0 );

        k3[0] = dt * x1( x+x/2.0, y+y/2.0 );
        k3[1] = dt * y1( x+x/2.0, y+y/2.0 );

        k4[0] = dt * x1( x, y );
        k4[1] = dt * y1( x, y );

        x = X*x + sf*h*( k1[0] + 2.0*k2[0] + 2.0*k3[0] + k4[0] ) / 6.0;
        y = Y*y + sf*h*( k1[1] + 2.0*k2[1] + 2.0*k3[1] + k4[1] ) / 6.0;

        // オイラー法
        //y = y + dt*dydt(x,y);
        //x = x + dt*dxdt(x,y);
        }
    fclose(fp);
    return 0;
}

#include <stdio.h>
double f1(double,double,double);
double f2(double,double,double);

int main(){
    double t=0.0,x,y,y1,y2,dt,tmax;
    double k1[2],k2[2],k3[2],k4[2];
    x=1.0
    y=1.0
    y1=0.3;
    y2=0.2;
    dt=0.01;
    tmax=20.0;
    printf("%lf %lf %lf\n",t,y1,y2);
    for(t=0;t<tmax;t+=dt) {
        k1[0]=dt*f1(t,y1,y2);
        k1[1]=dt*f2(t,y1,y2);
        k2[0]=dt*f1(t+dt/2.0,y1+k1[0]/2.0,y2+k1[1]/2.0);
        k2[1]=dt*f2(t+dt/2.0,y1+k1[0]/2.0,y2+k1[1]/2.0);
        k3[0]=dt*f1(t+dt/2.0,y1+k2[0]/2.0,y2+k2[1]/2.0);
        k3[1]=dt*f2(t+dt/2.0,y1+k2[0]/2.0,y2+k2[1]/2.0);
        k4[0]=dt*f1(t+dt,y1+k3[0],y2+k3[1]);
        k4[1]=dt*f2(t+dt,y1+k3[0],y2+k3[1]);
        y1=y1+(k1[0]+2.0*k2[0]+2.0*k3[0]+k4[0])/6.0;
        y2=y2+(k1[1]+2.0*k2[1]+2.0*k3[1]+k4[1])/6.0;
        printf("%lf %lf %lf\n",t+dt,y1,y2);
    }
    return 0;
}

double f1(double t,double y1,double y2){
    double ALPHA=1.5,BETA=1.0;
    return y1*(ALPHA-BETA*y2);
}

double f2(double t,double y1,double y2){
    double GAMMA=3.0,DELTA=1.0;
    return y2*(DELTA*y1-GAMMA);
}

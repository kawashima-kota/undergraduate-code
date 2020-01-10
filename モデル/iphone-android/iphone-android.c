

#include<stdio.h>
#include<math.h>
#define X 0.20 //iphoneのリピート率
#define Y 0.10 //androidのリピート率
#define m 0.70//androidに比べてiphoneの方がどれだけ魅力的かの定数(ブランド力・使い勝手の良さ・見た目)（主観）
#define e 0.20//裕福な人の割合

double dxdt(double ,double ,double,double,double,double,double,double,double);
double dydt(double ,double ,double,double,double,double,double,double,double);

int main(){
    FILE  *fp;
	double x;
    double y;
    double x1;
    double y1;
    double Sx;
    double Sy;
    double M1;
    double M2;
	double sf;//普及率
    double h;//スマホの性能
    double v1;//iphoneの価格
    double v2;//andoidの価格
	double t;
	double dt;
	double k1[2],k2[2],k3[2],k4[2];
    
    //iphone-android以外のスマホ
    //人口
    //VR・AR商品の市場参入
    
    //初期値（2007年）
	x = 370.0;
    y = 100.0;
    M1 = 0.40;
    M2 = 0.50;
	sf = 0.08;
    h = 1.0;
    v1 = 1.0;
    v2 =1.0;
	dt = 1.0;
    
    fp =fopen("data.txt","w");

    for( t=2007; t<=2020; t+=dt ){
        
        Sx = x/(x+y)*100;
        Sy = y/(x+y)*100;
        
		if(x>=0 && y>=0){
            fprintf(fp,"%4.0f %lf %lf %f %f\n",t, x, y,Sx,Sy);
			printf("%f %lf %lf %f %f %f %f\n",t ,x, y,Sx,Sy,M1,M2);
		}
        sf +=0.04;//毎年普及率が4%上がる
		h += 0.2;//毎年スマホの性能(スマホでできること)(10年で3倍)(主観)
        
        if(Sx > 80){
            M1 -= 0.05;
        }else if(Sx < 80 && Sx >70){
            M1 -= 0.025;
        }else if(Sx < 30 && Sx > 20){
            M1 +=0.025;
        }else if(Sx < 20){
            M1 +=0.05;
        }else{
            M1 =M1;
        }
        
        if(M1<=0.25){
            M1=0.25;
        }else if(M1 >=0.7){
            M1=0.7;
        }else{
            M1=M1;
        }
        
        if(Sy > 80){
            M2 -= 0.05;
        }else if(Sy <80 && Sy >70){
            M2 -= 0.025;
        }else if(Sy < 30 && Sy> 20){
            M2 +=0.025;
        }else if(Sy < 20){
            M2 +=0.05;
        }else{
            M2=M2;
        }
        
        if(M2<=0.25){
            M2=0.25;
        }else if(M2 >=0.50){
            M2=0.50;
        }else{
            M2=M2;
        }
        
        if(v1 < 2 && v1 > 1){
            v1 *= 1.10;
        }else if(v1 >=1.5 && v1<2){
            v1 *=1.075;
        }else if(v1 >=2 && v1<2.5){
            v1 += 1.05;
        }else{
            v1 *=1.025;
        }
        v2 *= 1.00;
        
		k1[0] = dt * dxdt( t,x, y ,M1,M2,sf,h,v1,v2);
		k1[1] = dt * dydt( t,x, y,M1,M2,sf,h ,v1,v2);

		k2[0]=dt*dxdt(t+dt/2.0,x+k1[0]/2.0,y+k1[1]/2.0,M1,M2,sf,h,v1,v2);
        k2[1]=dt*dydt(t+dt/2.0,x+k1[0]/2.0,y+k1[1]/2.0,M1,M2,sf,h,v1,v2);
        
        k3[0]=dt*dxdt(t+dt/2.0,x+k2[0]/2.0,y+k2[1]/2.0,M1,M2,sf,h,v1,v2);
        k3[1]=dt*dydt(t+dt/2.0,x+k2[0]/2.0,y+k2[1]/2.0,M1,M2,sf,h,v1,v2);
        
        k4[0]=dt*dxdt(t+dt,x+k3[0],y+k3[1],M1,M2,sf,h,v1,v2);
        k4[1]=dt*dydt(t+dt,x+k3[0],y+k3[1],M1,M2,sf,h,v1,v2);
        
        x=x+(k1[0]+2.0*k2[0]+2.0*k3[0]+k4[0])/6.0;
        y=y+(k1[1]+2.0*k2[1]+2.0*k3[1]+k4[1])/6.0;
        
	}	 
    fclose(fp);
	return 0;
}

double dxdt(double t,double x,double y,double M1,double M2,double sf,double h,double v1,double v2){
    
		return ( X*x+M1*m*sqrt(x*y)/v1-M2*(1-m)*sqrt(x*y)/v2+M1*(e/sf)*h/v1*x);
    
}

double dydt(double t,double x,double y,double M1,double M2,double sf,double h,double v1,double v2){
    
		return ( Y*y-M1*m*sqrt(x*y)/v1+M2*(1-m)*sqrt(x*y)/v2+M2*(e/sf)*h/v2*y);
    
}


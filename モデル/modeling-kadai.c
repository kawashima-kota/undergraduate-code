#include<stdio.h>
#include<math.h>
#define M1 0.7 //広告戦略に力を入れている割合→変数へ
#define M2 1.6//広告戦略→androidは複数の企業で使える
#define X 0.50 //iphoneのリピート率→長持ちするかどうかの値
#define Y 0.35 //androidのリピート率
#define m 0.61 //androidに比べてiphoneの方がどれだけ魅力的かの定数（ブランド力の比　android/iphone）
#define v1 0.88//前年度のiphoneの価格/今年度
#define v2 1.10//前年度androidの価格/今年度→格安スマホが登場したため>1とした
#define ss 4//一般大衆がスマホに求める性能値

double dxdt(double ,double ,double,double,double);
double dydt(double ,double ,double,double,double);

int main(){
    FILE  *fp;
	double x;
    double y;
    double Sx;
    double Sy;
	double sf;//普及率
    double h;//スマホの性能
	double t;
	double dt;
	double k1[2],k2[2],k3[2],k4[2];
    
    //iphone-android以外のスマホ
    //人口
    //貧富の格差
    //VR・AR商品の市場参入
    
    //初期値（2007年）
	x = 370.0;
	y = 70.0;
	sf = 0.08;
    h = 1.0;
	dt = 1.0;
    
    fp =fopen("data.txt","w");

	for( t=2007; t<=2020; t+=dt ){
		
        Sx = x/(x+y)*100;
        Sy = y/(x+y)*100;
        
		if(x>=0 && y>=0){
            fprintf(fp,"%4.0f %lf %lf %f %f\n",t, x, y,Sx,Sy);
			printf("%f %lf %lf %f %f\n",t ,x, y,Sx,Sy);
		}else if(x<0 && y>=0){
			x=0;
            fprintf(fp,"%f %lf %lf\n",t, x, y);
			printf("%lf %lf\n", x, y );
		}else if(x>=0 && y<0){
			y=0;
            fprintf(fp,"%f %lf %lf\n",t, x, y);
			printf("%lf %lf\n", x, y );
		}else{
			x=0;
			y=0;
            fprintf(fp,"%f %lf %lf\n",t, x, y);
			printf("%lf %lf\n", x, y );
		}		
		sf +=0.04;//毎年普及率が4%上がる
		h *=sqrt(2);//毎年スマホの性能が2年で2倍になる(ムーアの法則)
		k1[0] = dt * dxdt( t,x, y ,sf,h); 
		k1[1] = dt * dydt( t,x, y,sf,h ); 

		k2[0]=dt*dxdt(t+dt/2.0,x+k1[0]/2.0,y+k1[1]/2.0,sf,h);
        k2[1]=dt*dydt(t+dt/2.0,x+k1[0]/2.0,y+k1[1]/2.0,sf,h);
        
        k3[0]=dt*dxdt(t+dt/2.0,x+k2[0]/2.0,y+k2[1]/2.0,sf,h);
        k3[1]=dt*dydt(t+dt/2.0,x+k2[0]/2.0,y+k2[1]/2.0,sf,h);
        
        k4[0]=dt*dxdt(t+dt,x+k3[0],y+k3[1],sf,h);
        k4[1]=dt*dydt(t+dt,x+k3[0],y+k3[1],sf,h);
        
        x=x+(k1[0]+2.0*k2[0]+2.0*k3[0]+k4[0])/6.0;
        y=y+(k1[1]+2.0*k2[1]+2.0*k3[1]+k4[1])/6.0;
        
	}	 
    fclose(fp);
	return 0;
}

double dxdt(double t,double x,double y,double sf,double h){
    if(h < ss){
		return ( X*x+M1*m*sqrt(x*y)-M2*(1-m)*sqrt(x*y)+(1/(sf*100))*exp(h)*v1*x );
    }else{
        return ( X*x+M1*m*sqrt(x*y)-M2*(1-m)*sqrt(x*y)+(1/(sf*100))*log(h)*v1*x );
    }
}

double dydt(double t,double x,double y,double sf,double h){
    if(h < ss){
		return ( Y*y-M1*m*sqrt(x*y)+M2*(1-m)*sqrt(x*y)+(1/(sf*100))*exp(h)*v2*y);
    }else{
        return ( Y*y-M1*m*sqrt(x*y)+M2*(1-m)*sqrt(x*y)+(1/(sf*100))*log(h)*v2*y);
    }
}


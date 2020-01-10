#include<stdio.h>
#include<math.h>

void main(){
	int i,j,k,kk,n;
	float lmd,alp,bet,pi,h,dt,r,the,x,t,a,b,c;
	float d[100],g[100],er[100];
	float v[100],u[100][100],ue[100][100],m[100];
	FILE *fp;

	for(i=0;i<100;i++){
		d[i]=0.0;
		g[i]=0.0;
		er[i]=0.0;
		v[i]=0.0;
		m[i]=0.0;
		for(j=0;j<100;j++){
			u[i][j]=0.0;
			ue[i][j]=0.0;
		}
	}

	lmd=1.0;
	alp=0.0;
	bet=0.0;
	pi=3.14159;

	n=9;
	h=0.1;
	dt=1.0/600.0;
	kk=4;
	r=lmd*dt/h/h;
	the=1.0;
	a=1.0+2.0*r*the;
	b=-r*the;
	c=-r*the;

	d[0]=a;
	for(i=1;i<n;i++){
		m[i]=c/d[i-1];
		d[i]=a-m[i]*b;
	}

	for(j=0;j<n;j++){
		x=h*(float)(j+1);
		u[j+1][0]=sin(pi*x);
	}
	for(k=0;k<kk+1;k++){
		u[0][k+1]=alp;
		u[n+1][k+1]=bet;
		for(j=1;j<n+1;j++){
			g[j-1]=r*(1.0-the)*u[j-1][k]
				+(1.0-2.0*r*(1.0-the))*u[j][k]
				+r*(1.0-the)*u[j+1][k];
		}
		v[0]=g[0];
		for(i=1;i<n;i++)
			v[i]=g[i]-m[i]*v[i-1];
		u[n][k+1]=v[n-1]/d[n-1];
		for(i=n-1;i>0;i--){
			u[i][k+1]=(v[i-1]-b*u[i+1][k+1])/d[i-1];
		}
	}
	for(k=0;k<kk+1;k++){
		t=k*dt;
		for(j=0;j<n+2;j++){
			x=h*(float)j;
			ue[j][k]=exp(-pi*pi*t)*sin(pi*x);
		}
	}

	for(j=0;j<n;j++){
		if(ue[j][kk]!=0){//’Ç‰Á
			er[j]=fabs(u[j][kk]-ue[j][kk])/ue[j][kk];//ƒ[ƒŠ„ƒGƒ‰[
		}	
	}

	fp=fopen("result_in.txt","w");
	fprintf(fp,"  k         ");
	for(k=0;k<kk+1;k++)
		fprintf(fp,"%2d        ",k);
	fprintf(fp,"‰ðÍ‰ð(k=4)\n");
	for(j=0;j<n+2;j++){
		fprintf(fp,"j=%2d    ",j);
		for(k=0;k<kk+1;k++){
			fprintf(fp,"%8.4f",u[j][k]);
		}
		fprintf(fp,"%8.4f\n",ue[j][kk]);
	}
	fclose(fp);
	
	for(k=0;k<kk+1;k++)
		printf("  i=%2d  u=%7.4f  exact=%7.4f\n",k,u[5][k],exp(-pi*pi*dt*(float)k));
}
			
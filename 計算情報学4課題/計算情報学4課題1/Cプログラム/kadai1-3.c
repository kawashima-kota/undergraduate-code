#include <stdio.h>
#include <math.h>

int main(){
        int i,j,n;
        float p,q,f,alp,bet,h;
        float a[100],b[100],c[100],d[100],g[100];
        float v[100],u[100],m[100],k[100],r[100];
        float gosa,sum,ave;

        p=1.0;
        q=-1;
        f=0.0;
        alp=1.0;
        bet=0.0;

for(n=2;n<100;n++){
        sum=0;
        h=1/((float)n+1);

        for(j=0;j<n;j++)
                a[j]=p+p+h*h*q;
        for(j=0;j<n-1;j++){
                b[j]=-p;
                c[j+1]=b[j];
        }
        g[0]=p*alp+h*h*f;
        for(j=1;j<n-1;j++)
                g[j]=h*h*f;
        g[n-1]=p*bet+h*h*f;

        d[0]=a[0];
        for(i=1;i<n;i++){
                m[i]=c[i]/d[i-1];
                d[i]=a[i]-m[i]*b[i-1];
    }

        v[0]=g[0];
        for(i=1;i<n;i++)
                v[i]=g[i]-m[i]*v[i-1];
        u[n-1]=v[n-1]/d[n-1];
        for(i=n-2;i>=0;i--)
                u[i]=(v[i]-b[i]*u[i+1])/d[i];

        for(i=0;i<=n;i++){

                r[i]=cos(h*(i+1))-sin(h*(i+1))/tan(1);
        }
        printf("分割数%2dの時の",n+1);
        for(i=0;i<n;i++){
                sum+=fabs(u[i]-r[i]);
                }
        ave=sum/n;
        printf("誤差平均:%9.6f\n" ,ave);
}
}

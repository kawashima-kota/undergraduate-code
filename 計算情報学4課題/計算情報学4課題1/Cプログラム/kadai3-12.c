#include <stdio.h>
#include <math.h>

int main(){
        FILE*fp;
        int i,j,n;
        float p,q,f,alp,bet,h;
        float a[100],b[100],c[100],d[100],g[100];
        float v[100],u[100],m[100],k[100];
        
        p=1.0;
        q=16.0;
        alp=0.0;
        bet=0.0;

        n=9;
        h=(float)1/(n+1);
        fp =fopen("kadai3-12.txt","w");

        for(j=0;j<n;j++)
                a[j]=p+p+h*h*q;
        for(j=0;j<n-1;j++){
                b[j]=-p;
                c[j+1]=b[j];
        }
        g[0]=p*alp+h*h*h;
        for(j=1;j<n-1;j++)
                g[j]=h*h*h*(j+1);
        g[n-1]=p*bet+h*h*h*(n-1+1);

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

                k[i]=(h*(i+1)-(exp(4*h*(i+1))-exp(-4*h*(i+1)))/(exp(4)-exp(-4)))/16;
        }
        for(i=0;i<n;i++){
                fprintf(fp,"%2d %7.4f  %2d %7.4f  ", i+1,u[i],i+1,k[i]);
                fprintf(fp,"誤差:%9.6f\n" ,fabs(u[i]-k[i]));
        }
        fclose(fp);
        return 0;
}

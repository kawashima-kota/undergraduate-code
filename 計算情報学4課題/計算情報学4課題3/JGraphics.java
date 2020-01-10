import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import java.net.URL;

public class JGraphics{
	Graphics g;
	int non,noe,wx,wy;
	double x[]=new double[non];
	double y[]=new double[non];
	double f[]=new double[non];
	double fmax,fmin,df;
	int jmax,jmid,jmin,nt;
	
	public JGraphics(int wx,int wy,Graphics g){
		this.wx=wx;
		this.wy=wy;
		this.g=g;
	}
	
	public void Contour(double f[],int e[][],double x[],double y[],int noe,Graphics g){
	
	
		double Maxf=f[1];
		double Minf=f[1];
		double fx;
	
		for(int i=2;i<=noe;i++){
			if(Maxf<f[i]) Maxf=f[i];
			if(Minf>f[i]) Minf=f[i];
		}
		df=(Maxf-Minf)/10;
		
		for(int i=1;i<=noe;i++){
			jmax=1; jmin=1;jmid=1;
			fmax=f[e[i][1]];fmin=fmax;
			for(int j=2;j<=3;j++){
				fx=f[e[i][j]];
				if(fx>fmax){
					fmax=fx;
					jmax=j;
				}
				if(fx<fmin){
					fmin=fx;
					jmin=j;
				}
			}
			
			nt=(int)(fmax/df)-(int)(fmin/df);
			if(nt<=0) continue;
			for(int j=1;j<=3;j++){
				if(j!=jmax && j!=jmin) jmid=j;
			}
			jmax=e[i][jmax];
			jmid=e[i][jmid];
			jmin=e[i][jmin];
			draw(x,y,f,g);
		}
		for(int i=1;i<=noe;i++){
			jmax=1;jmin=1;jmid=1;
			fmax=f[e[i][1]];fmin=fmax;
			for(int j=2;j<=4;j++){
				if(j==2) continue;
				fx=f[e[i][j]];
				if(fx>fmax){
					fmax=fx;
					jmax=j;
				}
				if(fx<fmin){
					fmin=fx;
					jmin=j;
				}
			}
			nt=(int)(fmax/df)-(int)(fmin/df);
			if(nt<=0) continue;
		
			for(int j=1;j<=4;j++){
				if(j==2) continue;
				if(j!=jmax && j!=jmin) jmid=j;
			}
			jmax=e[i][jmax];
			jmid=e[i][jmid];
			jmin=e[i][jmin];
			draw(x,y,f,g);
		}
	}
	
	public void draw(double x[],double y[], double f[],Graphics g){
	
		int l;
		double xx1,xx2,yy1,yy2,fx=0;
		
		for(int k=1;k<=nt;k++){
			l=(int)(fmin/df)+k;
			fx=l*df;
			if(l<=1){	g.setColor(Color.black);
			}else if(l==2){g.setColor(Color.gray);
			}else if(l==3){g.setColor(Color.blue);
			}else if(l==4){g.setColor(Color.cyan);
			}else if(l==5){g.setColor(Color.green);
			}else if(l==6){g.setColor(Color.pink);
			}else if(l==7){g.setColor(Color.red);
			}else if(l==8){g.setColor(Color.magenta);
			}else if(l==9){g.setColor(Color.orange);
			}else if(l==10){g.setColor(Color.yellow);
			}
		
			xx1=((fmax-fx)*x[jmin]+(fx-fmin)*x[jmax])/(fmax-fmin);
			yy1=((fmax-fx)*y[jmin]+(fx-fmin)*y[jmax])/(fmax-fmin);
			if(fx>f[jmid]){
				xx2=((fmax-fx)*x[jmid]+(fx-f[jmid])*x[jmax])/(fmax-f[jmid]);
				
				yy2=((fmax-fx)*y[jmid]+(fx-f[jmid])*y[jmax])/(fmax-f[jmid]);
				
				}else{
					xx2=((f[jmid]-fx)*x[jmin]+(fx-fmin)*x[jmid])/(f[jmid]-fmin);
					
					yy2=((f[jmid]-fx)*y[jmin]+(fx-fmin)*y[jmid])/(f[jmid]-fmin);
					
				}
				g.drawLine((int)(xx1),(int)(yy1),(int)(xx2),(int)(yy2));
			}	
		}
	}
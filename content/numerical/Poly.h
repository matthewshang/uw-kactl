/**
 * Author: Kaiyuan Liu
 * Date: 2017-03-14
 * Description: Poly
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once
const int Mod=998244353;
struct Poly:vector<int>{
	Poly(int n=0){ resize(n); }
	Poly(int n,int x){ resize(n); rep(i,0,n-1) (*this)[i]=x; }
};
Poly resize(Poly f,int n){ f.resize(n); return f; }
int Pow(int x,int y){
	int res=1;
	for(y=(y%(Mod-1)+Mod-1)%(Mod-1);y;y&1?res=1ll*res*x%Mod:0,y>>=1,x=1ll*x*x%Mod);
	return res;
}
namespace Fourier{
	const int G=3,N=(1<<22)+5;
	int rev[N];
	int Getrev(int n){
		int lim=1,len=0;
		for(lim=1,len=0;lim<=n;lim<<=1,len++);
		rep(i,0,lim-1) rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));
		return lim;
	}
	void NTT(int *f,int lim,int type){
		rep(i,1,lim-1) if(i<rev[i]) swap(f[i],f[rev[i]]);
		for(int i=1;i<lim;i<<=1){
			int wn=Pow(G,type*(Mod-1)/(i<<1));
			for(int j=0;j<lim;j+=(i<<1)){
				for(int k=0,w=1;k<i;k++,w=1LL*w*wn%Mod){
					int x=f[j+k]%Mod,y=1LL*w*f[i+j+k]%Mod;
					f[j+k]=(x+y)%Mod;
					f[i+j+k]=(x-y+Mod)%Mod;
				}
			}
		}
		if(type==-1){
			int x=Pow(lim,Mod-2);
			rep(i,0,lim-1) f[i]=1LL*f[i]*x%Mod;
		}
	}
}
using Fourier::Getrev;
using Fourier::NTT;
Poly operator +(Poly a,Poly b){
	int n=b.size(); a.resize(max(a.size(),b.size()));
	rep(i,0,n-1) a[i]=(a[i]+b[i])%Mod;
	return a;
}
Poly operator -(Poly a,Poly b){
	int n=b.size(); a.resize(max(a.size(),b.size()));
	rep(i,0,n-1) a[i]=(a[i]+Mod-b[i])%Mod;
	return a;
}
Poly operator *(Poly a,int b){
	int n=a.size();
	rep(i,0,n-1) a[i]=1ll*a[i]*b%Mod;
	return a;
}
Poly operator *(Poly a,Poly b){
	if(a.empty()||b.empty()) return Poly();
	int n=a.size()+b.size()-1,lim=Getrev(n);
	a.resize(lim); b.resize(lim);
	NTT(&a[0],lim,1),NTT(&b[0],lim,1);
	rep(i,0,lim-1) a[i]=1ll*a[i]*b[i]%Mod;
	NTT(&a[0],lim,-1);
	return resize(a,n);
}
Poly operator <<(Poly a,int x){
	int n=a.size()+x; a.resize(n);
	per(i,n-1,x) a[i]=a[i-x];
	rep(i,0,x-1) a[i]=0;
	return a;
}
Poly operator >>(Poly a,int x){
	int n=a.size()-x;
	rep(i,0,n-1) a[i]=a[i+x];
	return resize(a,n);
}
Poly Inv(Poly a){
	if(a.size()==1) return Poly(1,Pow(a[0],Mod-2));
	int n=a.size(),lim;
	Poly b=Inv(resize(a,n+1>>1));
	lim=Getrev(n+2*b.size());
	Poly c=resize(b,lim),d=resize(a,lim);
	NTT(&c[0],lim,1); NTT(&d[0],lim,1);
	rep(i,0,lim-1) c[i]=(2-1ll*c[i]%Mod*d[i]%Mod+Mod)%Mod*c[i]%Mod;
	NTT(&c[0],lim,-1);
	return resize(c,n);
}
Poly Derivative(Poly a){
	int n=a.size();
	rep(i,1,n-1) a[i-1]=1ll*a[i]*i%Mod;
	return resize(a,n-1);
}
Poly Integral(Poly a){
	int n=a.size(); a.push_back(0);
	per(i,n,1) a[i]=1ll*a[i-1]*Pow(i,Mod-2)%Mod;
	a[0]=0;
	return a;
}
Poly Ln(Poly a){ return Integral(resize(Derivative(a)*Inv(a),(int)a.size()-1)); }
Poly Exp(Poly a){
	if(a.size()==1) return Poly(1,1);
	int n=a.size();
	Poly b=Exp(resize(a,n+1>>1));
	return resize(b+b*(a-Ln(resize(b,n))),n);
}
Poly operator /(Poly a,Poly b){
	int n=a.size(),m=b.size();
	if(n<m) return Poly();
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	a=resize(resize(a,n-m+1)*Inv(resize(b,n-m+1)),n-m+1);
	reverse(a.begin(),a.end());
	return a;
}
Poly operator %(Poly a,Poly b){ return resize(a-a/b*b,(int)b.size()-1); }
Poly Pow(Poly a,int k){
	int p=0,n=a.size();
	for(;p<n&&!a[p];p++);
	if(1ll*p*k>=n) return Poly(n);
	Poly b; rep(i,p,n-1) b.push_back(a[i]);
	int w=b[0],inv=Pow(w,Mod-2),wk=Pow(w,k);
	b=Exp(Ln(b*inv)*k)*wk;
	Poly c(p*k+(int)b.size());
	rep(i,0,(int)b.size()-1) c[i+p*k]=b[i];
	return resize(c,n);
}
namespace Eval_Inter{
	const int N=(1<<20)+5;
	int n; Poly prod[N],f;
	typedef vector<int> vi;
	vi x,y;
	void Getprod(int p,int l,int r){
		if(l==r){
			prod[p].resize(2);
			prod[p][0]=Mod-x[l],prod[p][1]=1;
			return ;
		}
		int mid=l+r>>1;
		Getprod(p<<1,l,mid); Getprod(p<<1|1,mid+1,r);
		prod[p]=prod[p<<1]*prod[p<<1|1];
	}
	void Eval(int p,int l,int r,Poly f){
		f=resize(f%prod[p],prod[p].size()-1);
		if(l==r) return (void)(y[l]=f[0]);
		int mid=l+r>>1;
		Eval(p<<1,l,mid,f); Eval(p<<1|1,mid+1,r,f);
	}
	vi Eval(Poly _f,vi _x){
		n=_x.size(),x=_x,f=_f;
		if(!n) return Poly();
		y.resize(n);
		Getprod(1,0,n-1);
		Eval(1,0,n-1,f);
		return y;
	}
	Poly Inter(int p,int l,int r){
		if(l==r) return Poly(1,y[l]);
		int mid=l+r>>1;
		return Inter(p<<1,l,mid)*prod[p<<1|1]+Inter(p<<1|1,mid+1,r)*prod[p<<1];
	}
	Poly Inter(vector<pair<int,int> >a){
		n=a.size(); y.resize(n); x.resize(n);
		if(!n) return Poly();
		rep(i,0,n-1) x[i]=a[i].first;
		Getprod(1,0,n-1);
		Poly m=Derivative(prod[1]);
		Eval(1,0,n-1,m);
		rep(i,0,n-1) y[i]=1ll*a[i].second*Pow(y[i],Mod-2)%Mod;
		return Inter(1,0,n-1);
	}
}
using Eval_Inter::Eval;
using Eval_Inter::Inter;

namespace Cipolla{
	typedef pair<int,int> pii;
	#define fir first
	#define sec second
	int w,t;
	pii operator *(pii a,pii b){
		int x=0,y=0;
		x=(1ll*a.fir*b.fir%Mod+1ll*a.sec*b.sec%Mod*w%Mod)%Mod;
		y=(1ll*a.fir*b.sec%Mod+1ll*a.sec*b.fir%Mod)%Mod;
		return make_pair(x,y);
	}
	pii PPow(pii x,int y){
		pii res=make_pair(1,0);
		for(;y;x=x*x,y>>=1) if(y&1) res=res*x;
		return res;
	}
	int Sqrt(int x){
		if(x==0) return 0;
		if(Pow(x,(Mod-1)/2)!=1) return -1;
		do{
			t=1ll*rand()*rand()%(Mod-1)+1;
			w=(1ll*t*t+Mod-x)%Mod;
		}while(Pow(w,(Mod-1)/2)==1);
		pii res=PPow(make_pair(t,1),(Mod+1)/2);
		return min(res.fir,Mod-res.fir);
	}
	#undef fir
	#undef sec
}
using Cipolla::Sqrt;
Poly Sqrt(Poly a){
	if(a.size()==1) return Poly(1,Sqrt(a[0]));
	int n=a.size();
	Poly b=resize(Sqrt(resize(a,n+1>>1)),n);
	return resize((b+a*Inv(b))*(Mod+1>>1),n);
}
Poly Sp_Mod(long long n,Poly &a){
	if(n<(int)a.size()-1){
		Poly res(n+1);
		res[n]=1;
		return res;
	}
	Poly b=Sp_Mod(n>>1,a);
	b=b*b;
	if(n&1) b=b<<1;
	return b%a;
}
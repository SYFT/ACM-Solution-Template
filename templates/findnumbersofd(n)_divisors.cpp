const int N = 2002;
int f[N],g[N*N];
bool ip[N];
int mu[N],p[N],nt[N];
void init_mu(){
    mu[1]=1;ip[2]=true;p[0]=2;
    for(int i=1;i<N;i+=2)   ip[i]=true;
    for(int i = 3,cnt = 1;i<N;i+=2){
        if(ip[i]){
            p[cnt++] = i;
            mu[i] = -1;
        }
        for(int j = 1,t;j<cnt&&(t= i * p[j])<N;++j){
            ip[t] = false;
            if(i % p[j] == 0)   break;
            mu[t] = -mu[i];
        }
    }
    for(int i=2;i<N;i+=4)  mu[i]=-mu[i>>1];
}
int getsum(int n){
    int sum = 0;
    for(int i=1,j;i<=n;i=j+1){
        j = n/(n/i);
        sum += (j-i+1)*(n/i);
    }
    return sum;
}
void init(){
    for(int i=0;i<N;++i)       f[i]=getsum(i);    init_mu();
    int last = 1;
    for(int i=2;i<N;++i){
        if(mu[i]==0)    continue;
        nt[last]=i;
        last = i;
    }
    nt[last]=N;
}
void getg(int a,int b,int c){
    int n = a*b;
    for(int i=0;i<=n;++i)   g[i]=0;
    for(int i=1;i<=n&&i<=c;i=nt[i]){ // n^2 \log n
        for(int j=i,t=mu[i]*f[c/i];j<=n;j+=i)   g[j]+=t;
    }
}
LL getf(int a,int b,int d){
    LL res = 0;
    for(int i=1;i<=a;++i){
        for(int j=1;j<=b;++j){
            res+=(a/i)*(b/j)*g[i*j*d];
        }
    }
    return res;
}
int main(){
//        freopen("/Users/dna049/Desktop/AC/in","r",stdin);
    //    freopen("/Users/dna049/Desktop/AC/out","w",stdout);
    init();
    int a,b,c;
    while(~scanf("%d%d%d",&a,&b,&c)){
        getg(a,b,c);
        int ab = min(a,b);
        LL res = 0;
        for(int i=1;i<=ab;i=nt[i]){
            res+=mu[i]*getf(a/i,b/i,i*i);
        }
        printf("%d\n",int(res%(1<<30)));
    }
    return 0;
}

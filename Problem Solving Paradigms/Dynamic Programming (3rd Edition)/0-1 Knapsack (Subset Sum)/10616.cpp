#include<bits/stdc++.h>
#define all(v) (v).begin(),(v).end()
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ri(x) scanf("%d",&(x))
#define ri2(x,y) scanf("%d %d",&(x),&(y))
#define ri3(x,y,z) scanf("%d %d %d",&(x),&(y),&(z))
#define rll(x) scanf("%lld",&(x))
#define rll2(x,y) scanf("%lld %lld",&(x),&(y))
#define rll3(x,y,z) scanf("%lld %lld %lld",&(x),&(y),&(z))
#define rc(x) scanf("%c",&(x))
using namespace::std;

const long double PI = acos(-1);
const int MOD = 1000000000 +7;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<ll,pll> tll;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<tll> vtll;
typedef vector<string> vs;
typedef set<int> si;
typedef set<ii> sii;
typedef set<iii> siii;

ll gcd(ll a, ll b){ return b==0?a:gcd(b,a%b);}

int add(ll a, ll b){ return (a%MOD + b%MOD+2*MOD)%MOD;}

int mul(ll a, ll b){ return ((a%MOD+MOD)*(b%MOD+MOD))%MOD;}

ll pow_mod(ll a, ll b){
	ll res = 1LL;
	a = add(a,0);
	while(b){
		if(b&1) res = mul(res,a);
		b >>= 1;
		a = mul(a,a);
	}
	return res;
}

ll fastexp(ll a, ll b){
	ll res = 1LL;
	while(b){
		if(b&1) res = res*a;
		b >>= 1;
		a *= a;
	}
	return res;
}

int gcdExtendido(int a, int b, int *x, int *y){
	if(a == 0){
		*x = 0;
		*y = 1;
		return b;
	}
	int x1, y1;
	int gcd = gcdExtendido(b%a,a,&x1,&y1);
	
	*x = y1-(b/a)*x1;
	*y = x1;
	return gcd;
};

int modInverso(int a, int m){
	int x, y;
	int g = gcdExtendido(a,m,&x,&y);
	if(g!=1) return -1;
	else return (x%m + m)%m;
}

/****************************************
*************P*L*A*N*T*I*L*L*A************
*****************************************/

const int N = 205;

struct BigInteger{
	int len;
	vi number;
	BigInteger(){
		len = 0;
	};
	void use(int x){
		len = 0;
		while(x){
			number.pb(x%10);
			x /= 10;
			len +=1;
		}
	}
	void add(BigInteger b){
		int l = max(len,b.len);
		for(int i=0; i<min(len,b.len); i++){
			number[i] += b.number[i];
		}
		if(len < b.len){
			for(int i=len; i<b.len; i++){
				number.pb(b.number[i]);
			}
		}
		for(int i=0; i<l; i++){
			if(number[i]>9){
				if(i+1<l) number[i+1] +=1 ;
				else number.pb(1);
				number[i]%= 10;
			}	
		}
		len = number.size();
	}
	void print(){
		if(len){
			for(int i=len-1; i>=0; i--) putchar(number[i]+'0');
		}
		else{
			putchar('0');
		}
	}
};

int n,q;
int d,m;
ll v[N];
BigInteger UNO, ZERO;
BigInteger memo[N][30][11];
bool vis[N][30][11];

BigInteger DP(int pos, int r, int left){
	if(pos == n){
		return (r==0 and left==0)?UNO:ZERO;
	}
	if(left == 0){
		return r==0?UNO:ZERO;
	}
	if(vis[pos][r][left]) return memo[pos][r][left];
	BigInteger ans = DP(pos+1,r,left);
	if(left > 0) ans.add(DP(pos+1,(r+v[pos]%d+2*d)%d,left-1));
	vis[pos][r][left] = true;
	return memo[pos][r][left] = ans;
}

int main(){
	int t = 1;
	UNO.use(1);
	ZERO.use(0);
	/*int a, b;
	cin >> a >> b;
	BigInteger A, B;
	A.use(a);
	B.use(b);
	cout << a+b << " ";
	A.add(B);
	A.print();
	puts("");*/
	while(ri2(n,q)==2 and (n+q!=0)){
		for(int i=0; i<n; i++){
			rll(v[i]);
		}
		printf("SET %d:\n",t++);
		int query = 1;
		while(q--){
			ri2(d,m);
			memset(vis,0,sizeof vis);
			printf("QUERY %d: ",query++);
			BigInteger ans = DP(0,0,m);
			ans.print();
			puts("");
		}
	}
	return 0;
}

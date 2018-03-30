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

const int MAX = 1000+5;
const int MAXP = 301;
const int N = 200+5;

int n, t;
int len;
bool p[MAX];
vi primos;
int max_times[N];
string s[N];
string memo[N][MAX][20];
bool vis[N][MAX][20];
int choice[N];

bool minimo(string a, string b){
	int p1 = a.size()-1;
	int p2 = b.size()-1;
	while(p1 >= 0 and p2 >= 0 and a[p1] == b[p2]){
		p1 -= 1;
		p2 -= 1;
	}
	if(p1 == -1) return true;
	if(p2 == -1) return false;
	return a[p1] < b[p2];
}

bool maximo(string a, string b){
	int p = 0;
	while(p < min(int(a.size()),int(b.size())) and a[p]==b[p]){
		p+=1;
	}
	if(p == a.size()) return false;
	if(p == b.size()) return true;
	return a[p] > b[p];
}

string DP(int pos, int left, int t_left){
	if(pos == -1){
		return left==0 and t_left==0?" ":"}";
	}
	if(vis[pos][left][t_left]) return memo[pos][left][t_left];
	string ans = DP(pos-1,left,t_left);
	int val = primos[pos];
	string add = "";
	add = add + '+' + s[pos];
	choice[pos] = 0;
	for(int i=1; i<=max_times[pos]; i++){
		if(left >= val and t_left >= i){
			string candidate = DP(pos-1,left-val,t_left-i) + add;
			if(candidate[0]!='}' and minimo(candidate,ans)){
				ans = candidate;
				choice[pos] = i;
			}
		}
		val += primos[pos];
		add = add + '+' + s[pos];
	}
	vis[pos][left][t_left] = true;
//	cout << pos << " " << left << " " << t_left << " " << ans << endl;
	return memo[pos][left][t_left] = ans;
}

string to_s(int x){
	if(x == 0) return "0";
	string ans = "";
	while(x){
		ans = ans + char(x%10+'0');
		x /= 10;
	}
	reverse(all(ans));
	return ans;
}

void init(){
	for(int i=2; i*i<=MAXP; i++){
		if(!p[i]){
			for(int j=i*i; j<MAXP; j+=i) p[j] = true;
		}
	}
	for(int i=2; i<MAXP; i++){
		if(!p[i]) primos.pb(i);
	}
}

bool comp(int x, int y){
	return maximo(to_s(x),to_s(y));
}

int main(){
	init();
	len = primos.size();
	sort(all(primos),comp);
	int caso = 1;
	for(int i=0; i<len; i++){
		max_times[i] = primos[i]==2?1:2;
	}
	for(int i=0; i<len; i++){
		s[i] = to_s(primos[i]);
		reverse(all(s[i]));
	}
	string ans;
	while(ri2(n,t)==2 and n+t>0){
		if(n&1){
			ans = DP(len-1,n,t);
		}
		else{
			ans = DP(len-1,n,t);
		}
		int siz = ans.size();
		printf("CASE %d:\n",caso++);
		if(ans[0]!='}'){
			for(int i=siz-1; i>=2; i--) putchar(ans[i]);
			putchar('\n');
		}
		else puts("No Solution.");	
	}
	return 0;
}

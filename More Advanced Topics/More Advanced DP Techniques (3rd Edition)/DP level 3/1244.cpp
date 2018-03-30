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

const int N = 50+5;

int n;
string d[N];
string memo[N][N];
bool vis[N][N];

bool menor(string a, string b){
	int len = a.size();
	int pos = 0;
	while(pos < len and a[pos] == b[pos]) pos += 1;
	return pos==len?false:a[pos] < b[pos];
}

bool palindrome(string s){
	int len = s.size();
	for(int i=0; 2*i < len; i++){
		if(s[i]!=s[len-1-i]) return false;
	}
	return true;
}

string DP(int i, int j){
	if(i == j){
		string ans = "";
		return ans;
	}
	if(i+1 == j){
		string ans = "";
		ans = ans + d[i][j];
		return ans;
	}
	if(vis[i][j]) return memo[i][j];
	string ans = "";
	ans = ans + d[i][j];
	for(int c1 = i; c1 < j; c1++){
		for(int c2=c1; c2<j; c2++){
			if(i < c1 and c1 <= c2 and c2 < j and d[i][c1] == d[c2][j]){
				string candidate = "";
				candidate = candidate + d[i][c1] + DP(c1,c2) + d[c2][j];
				if(candidate.size() > ans.size()) ans = candidate;
				else if(candidate.size() == ans.size()){
					if(menor(candidate,ans)) ans = candidate;
				}
			}
		}
	}
	vis[i][j] = true;
	return memo[i][j] = ans;
}

int main(){
	int t;
	ri(t);
	char x;
	while(t--){
		ri(n);
		for(int i=0; i<n; i++){
			cin >> d[i];
		}
		memset(vis,0,sizeof vis);
		printf("%s\n",DP(0,n-1).c_str());
	}	
	return 0;
}

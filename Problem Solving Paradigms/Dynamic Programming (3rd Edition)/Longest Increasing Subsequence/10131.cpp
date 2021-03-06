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

int n;
viii v;
vi parent;
vi LIS;

bool comp(iii &a, iii &b){
	if(a.second.first < b.second.first) return true;
	if(a.second.first > b.second.first) return false;
	return a.second.second > b.second.second;
}

int main(){
	int w,s;
	n = 0;
	while(ri2(w,s)==2){
		v.pb(mp(n++,mp(w,s)));
	}
	sort(all(v),comp);
	LIS.pb(1);
	parent.pb(-1);
	int maxlen = 1;
	int start = 0;
	for(int i=1; i<n; i++){
		LIS.pb(1);
		parent.pb(-1);
		for(int j=0; j<i; j++){
			if(v[j].second.first < v[i].second.first and v[j].second.second > v[i].second.second){
				if(LIS[i] < LIS[j]+1){
					LIS[i] = LIS[j]+1;
					parent[i] = j;
				}
			}
		}
		if(maxlen < LIS[i]){
			maxlen = LIS[i];
			start = i;
		}
	}
	printf("%d\n",maxlen);
	stack<int> S;
	while(start!=-1){
		S.push(v[start].first+1);
		start = parent[start];
	}
	while(!S.empty()){
		printf("%d\n",S.top());
		S.pop();
	}
	return 0;
}

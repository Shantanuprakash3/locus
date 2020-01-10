#include<bits/stdc++.h>
#include<string>
using namespace std;


typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

#define s(n)                        scanf("%d",&n)
#define s2(q,w)                        scanf("%d %d",&q,&w)
#define s3(q,w,e)                        scanf("%d %d %d",&q,&w,&e)
#define pb(x)            push_back(x)

#define INF                         (int)1e9
#define EPS                         1e-9

#define checkbit(n,b)                ( (n >> b) & 1)

int mod = 1e9+7;

long long pwr(long long a,long long b,long long mod)
{
  if(b==0)
    return 1;
  long long temp=pwr(a,b/2,mod);
  temp=(temp*temp)%mod;
  if(b&1)
    temp=(temp*a)%mod;
  return temp;
}
long long pwr(long long a,long long b)
{
  if(b==0)
    return 1;
  long long temp=pwr(a,b/2);
  temp=(temp*temp);
  if(b&1)
    temp=(temp*a);
  return temp;
}
bool* isPrime;
void generatePrimeSieve(const int lim)
{
  isPrime=(bool *)malloc(lim+1);
  memset(isPrime,true,lim+1);
  isPrime[0]=false;
  isPrime[1]=false;
  for(int i=2;i<=lim;++i)
    if(isPrime[i])
      for(int j=i+i;j<=lim;j+=i)
        isPrime[j]=false;
}
#define matrix vector<vector<int> >
matrix identityMatrix;
matrix mul(const matrix &a,const matrix &b)
{
  int n=a.size();
  matrix ans(n,vector<int> (n) );
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      for (int k = 0; k < n; ++k)
      {
        ans[i][j]+= ((long long)a[i][k]*b[k][j])%mod;
        ans[i][j]%=mod;
      }
    }
  }
  return ans;
} 
matrix pwr(const matrix &a,long long n)
{
    if(n==0)
    {
      /*define identity */
      assert(false);
      return identityMatrix;
    }
    if(n==1)
     return a;
    matrix tmp=pwr(a,n/2);
    tmp=mul(tmp,tmp);
    if(n&1)
      tmp=mul(a,tmp);
    return tmp;
}
long long gcd(long long a,long long b)
{
  return b==0?a:gcd(b,a%b);
}
long long lcm(long long a,long long b)
{  
  return (a/gcd(a,b))*b;
}
long long modularInverse(long long a,long long m)
{
      return pwr(a,m-2,m);
}

map<string,int> wordmap;
map<string,bool> mp;

map<int,int> numbermap;

vector<string> NT;
vector<string> T;

vector<int> rule[1000];

int glnt=1000;
int glt=0;




int main()
{
  freopen("Grammer.txt","r",stdin);
  char s[100];
  char allowed[100];
  char first[100];
  // char [100];

  // scanf("<%[^>]",s);
  while((scanf(" %[^a-zA-Z_0-9]%[a-zA-Z_0-9]",first,first))!=EOF)
  {
    // cout<<first<<" -> ";
    if(mp[first]==false)
    {
      NT.pb(first);
      mp[first]=true;
      wordmap[first]=glnt;
      glnt++;
    }


    while((scanf("%[^a-zA-Z0-9_.]%[a-zA-Z0-9_.]",s,s)!=EOF && (s[strlen(s)-1]!='.')))
    {

      if(s[0]=='E')
      {
        mp[s] = true;
        wordmap[s] = 50;
      }

      if(mp[s]==false && s[0]=='t' && s[1]=='k')
      {
        T.pb(s);
        mp[s] = true;
        wordmap[s]=glt;
        glt++;
      }
    }
  }

  wordmap["E"] = glt;


  // cout<<"terminals:-\n";
  // for (int i = 0; i < T.size(); ++i)
  // {
  //   cout<<i<<" "<<T[i]<<"\n";
  // }
  // cout<<"\n\n\n";

  // cout<<"non terminals:-\n";
  // for (int i = 0; i < NT.size(); ++i)
  // {
  //   // cout<<"\""<<NT[i]<<"\",";
  //   cout<<i<<" "<<NT[i]<<"\n";
    

  // }

  freopen("Grammer.txt","r",stdin);

  int n=0;
  while((scanf(" %[^a-zA-Z_0-9]%[a-zA-Z_0-9]",first,first))!=EOF)
  {
  
    while((scanf("%[^a-zA-Z_.0-9]%[a-zA-Z_.0-9]",s,s)!=EOF && (s[strlen(s)-1]!='.')))
    {
      rule[n].pb(wordmap[s]);
    }
    n++;
  }

  for (int i = 0; i < n ; ++i)
  {

    for (int j = 0; j < rule[i].size(); ++j)
    {
      printf("rule[%d][%d]=%d ;",i,j,rule[i][j]);

    }
    cout<<endl;


  }




}

#include <cstdio>
#include <cassert>
#include <vector>
#include <functional>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <cstdlib>
const int N_MAX = 80000;
const int PERIOD_MAX = 1000;
using namespace std;
struct d{
	int number;
	int Kw;
};
struct p{
	int period_index;
	double cost;
};
struct period_container{
	vector <int> myList;
	int Capa;
};
d Data[N_MAX];
d Data2[N_MAX];
d Best[N_MAX];
double best_result = 987987987;
p period_cost[PERIOD_MAX];
int Capa[PERIOD_MAX];
int n, m;
int Data_len;
int Cap_limit;
bool Check[N_MAX][PERIOD_MAX];
bool compare(p &s, p &t){
	if(s.cost < t.cost) return true;
	else if(s.cost == t.cost){
		if(s.period_index > t.period_index) return true;
		else return false;
	}
	else return false;
}
bool compare_d(d &s, d &t){
	if(s.Kw > t.Kw) return true;
	else if(s.Kw == t.Kw){
		if(s.number > t.number) return true;
		else return false;
	}
	else return false;
}
bool compare_result(period_container &s, period_container &t){
	return s.Capa > t.Capa;
}
int main(){
	int permu[PERIOD_MAX] = {0,};
	period_container result[PERIOD_MAX];
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	srand(time(NULL));
	scanf("%d %d %d",&n, &m, &Cap_limit); 
	Data_len = 1;
	double value = 0;
	for(int i=1;i<=n;i++){
		int f, w;
		scanf("%d %d",&f, &w);
		for(int j=1;j<=f;j++){
			Data[Data_len].number = i;
			Data[Data_len++].Kw = w; 
		}
	}
	n = Data_len-1;
	for(int i=1;i<=m;i++){
		scanf("%lf",&period_cost[i].cost);
		period_cost[i].period_index = i;
	}
	sort(period_cost+1, period_cost+1+m, compare);
	sort(Data+1, Data+1+n, compare_d);
	for(int i=1;i<=m;i++){
		result[i].myList.clear();
		result[i].Capa = 0;
	}
	for(int i=1;i<=n;i++){
		bool flag = false;
		for(int j=1;j<=m;j++){
			flag = false;
			if(Capa[j] + Data[i].Kw <= Cap_limit && Check[Data[i].number][j] == false){
				Check[Data[i].number][j] = true;
				Capa[j] = Capa[j] + Data[i].Kw;
				result[j].myList.push_back(Data[i].number);
				result[j].Capa += Data[i].Kw;
				flag = true;
				break;
			}
		}
		assert(flag == true);
	}
	memset(Check, 0, sizeof(Check));
	sort(result+1, result+1+m, compare_result);
	for(int i=1;i<=m;i++){
		permu[period_cost[i].period_index] = i;
		value += result[i].Capa * period_cost[i].cost;
	}
	for(int i=1;i<=m;i++){
		printf("Bin %d, Cost %lf : \n",i, period_cost[permu[i]].cost);
		for(int j=0;j<result[permu[i]].myList.size();j++) printf("%d ",result[permu[i]].myList[j]);
		printf("\n");
	}

	printf("total cost : %lf\n",value);
	return 0;
}

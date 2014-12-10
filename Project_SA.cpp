#include <cstdio>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <cstdlib>
const int N_MAX = 9005;
const int PERIOD_MAX = 300;
using namespace std;
struct d{
	int number;
	int Kw;
};
struct p{
	int period_index;
	double cost;
};
d Data[N_MAX];
d Data2[N_MAX];
d Best[N_MAX];
double best_result = 987987987;
p period_cost[PERIOD_MAX];
int n, m;
int Data_len;
int Cap;
	bool Check[N_MAX][PERIOD_MAX] = {0,};
double get_cost(){
	memset(Check, 0, sizeof(Check));
	int Cap_list[PERIOD_MAX] = {0,};
	int i, cost_inx = 1;
	int limit = 0;
	double return_value = 0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(Cap_list[j] + Data[i].Kw <= Cap && Check[Data[i].number][j] == false){
				Check[Data[i].number][j] = true;
				Cap_list[j] += Data[i].Kw;
				return_value += (Data[i].Kw * period_cost[j].cost);
				break;
			}
			else if(Cap_list[j] + Data[i].Kw > Cap) limit++;
		}
	}
	return return_value;
}
bool compare(p &s, p &t){
	if(s.cost < t.cost) return true;
	else if(s.cost == t.cost){
		if(s.period_index > t.period_index) return true;
		else return false;
	}
	else return false;
}
void print_result(){
	memset(Check, 0, sizeof(Check));
	int permu[PERIOD_MAX] = {0,};
	int Cap_list[PERIOD_MAX] = {0,};
	int i, cost_inx = 1;
	int limit = 1;
	double return_value = 0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(Cap_list[j] + Best[i].Kw <= Cap && Check[Best[i].number][j] == false){
				Check[Best[i].number][j] = true;
				Cap_list[j] += Best[i].Kw;
				return_value += (Best[i].Kw * period_cost[j].cost);
				break;
			}
			else if(Cap_list[j] + Best[i].Kw > Cap) limit++;
		}
	}
	for(int i=1;i<=m;i++) permu[period_cost[i].period_index] = i;
	
	/*
	for(int i=1;i<=m;i++){
		printf("Bin %d, Cost %lf : \n",i, period_cost[permu[i]].cost);
		for(int j=1;j<=n;j++){
			if(Check[j][permu[i]] == true)
				printf("%d ",j);
		}
		printf("\n");
	}
	*/
	 
	printf("total cost : %lf\n",return_value);
	return;
}
int main(int argc, char** argv){
	int begin, end;
	begin = clock();
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	srand(time(NULL));
	scanf("%d %d %d",&n, &m, &Cap); 
	Data_len = 1;
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
	int L = atoi(argv[1]);
	double T = L / sqrt((double)n);
	while(T >= 0.001){
		for(int j=1;j<=L;j++){
			double initial = get_cost();
			int one = 0, two = 0;
			while(1){
				one = rand() % n + 1;
				two = rand() % n + 1;
				if(one != two && Data[one].number != Data[two].number) break;
			}
			d Temp = Data[one];
			Data[one] = Data[two];
			Data[two] = Temp;
			double after = get_cost();
			double temp = exp(-(after - initial)/T);
			double choice = (double)rand() / RAND_MAX;
 			if(temp >= choice){
				if(best_result >= after){
					for(int k=1;k<=n;k++) Best[k] = Data[k];
					best_result = after;
				}
				// select new solution
			}
			else{
				d Temp = Data[one];
				Data[one] = Data[two];
				Data[two] = Temp;
			}
		}
		T = 0.95 * T;
	}
	end = clock();
	print_result();
	printf("elapsed time : %d\n",(int)((end - begin) / double(CLOCKS_PER_SEC)*1000));
	return 0;
}

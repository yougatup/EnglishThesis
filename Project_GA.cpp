#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
const int N_MAX = 8005;
const int PERIOD_MAX = 300;
const int GENE_CNT = 1000;
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
vector <int> Best;
double best_result = 987987987;
p period_cost[PERIOD_MAX];
int n, m;
int Data_len;
int Cap;
int gene_cnt = 100;
vector <int> Gene[N_MAX];
double get_cost(const vector <int> &permu){
	bool Check[N_MAX][PERIOD_MAX] = {0,};
	int Cap_list[PERIOD_MAX] = {0,};
	int cost_inx = 1;
	int limit = 0;
	double return_value = 0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(Cap_list[j] + Data[permu[i]].Kw <= Cap && Check[Data[permu[i]].number][j] == false){
				Check[Data[permu[i]].number][j] = true;
				Cap_list[j] += Data[permu[i]].Kw;
				return_value += (Data[permu[i]].Kw * period_cost[j].cost);
				break;
			}
			else if(Cap_list[j] + Data[permu[i]].Kw > Cap) limit++;
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
	bool Check[N_MAX][PERIOD_MAX] = {0,};
	int permu[PERIOD_MAX] = {0,};
	int Cap_list[PERIOD_MAX] = {0,};
	int i, cost_inx = 1;
	int limit = 1;
	double return_value = 0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(Cap_list[j] + Data[Best[i]].Kw <= Cap && Check[Data[Best[i]].number][j] == false){
				Check[Data[Best[i]].number][j] = true;
				Cap_list[j] += Data[Best[i]].Kw;
				return_value += (Data[Best[i]].Kw * period_cost[j].cost);
				break;
			}
			else if(Cap_list[j] + Data[Best[i]].Kw > Cap) limit++;
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
int get_index(double prob[]){
	double random_number = (double)rand() / RAND_MAX;
	for(int i=1;i<=gene_cnt;i++){
		if(prob[i] >= random_number)
			return i;
	}
}
vector <int> crossover(const vector<int> &A, const vector<int> &B, int crossover_point){
	vector <bool> position(n+1);
	vector <int> return_value(n+1);
	for(int i=1;i<=crossover_point-1;i++) return_value[i] = A[i];
	for(int i=crossover_point;i<=n;i++) position[A[i]] = true;
	int index = crossover_point;
	for(int i=1;i<=n;i++){
		if(position[B[i]] == true)
			return_value[index++] = B[i];
	}
	return return_value;
}
void Mutation(vector <int>& A){
	int random_number = rand() % 10;
	if(random_number == 0){
		int inx1 = rand() % n + 1;
		int inx2 = rand() % n + 1;
		int temp = A[inx1];
		A[inx1] = A[inx2];
		A[inx2] = temp;
	}
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
	for(int i=1;i<=gene_cnt;i++){
		vector <int> Temp;
		Temp.resize(n);
		Gene[i].resize(n+1);
		for(int i=0;i<Temp.size();i++) Temp[i] = i+1;
		random_shuffle(Temp.begin(), Temp.end());
		for(int j=1;j<=n;j++) Gene[i][j] = Temp[j-1];
	}
	vector <int> Temp;
	int it = atoi(argv[1]);
	for(int t=1;t<=it;t++){
		vector <int> temp_gene[GENE_CNT];
		int temp_gene_index = 1;
		double Cost[GENE_CNT] = {0,};
		double prob[GENE_CNT] = {0,}, sum = 0;
		for(int i=1;i<=gene_cnt;i++){
			Cost[i] = get_cost(Gene[i]);
			sum += Cost[i];
			if(Cost[i] <= best_result){
				best_result = Cost[i];
				Best = Gene[i];
			}
		}
		for(int i=1;i<=gene_cnt;i++) prob[i] = prob[i-1] + (Cost[i] / sum);
		for(int i=1;i<=gene_cnt/2;i++){
			int inx1 = get_index(prob);
			int inx2 = get_index(prob);
			int crossover_point = rand() % n + 1;
			Temp = crossover(Gene[inx1], Gene[inx2], crossover_point);
			Mutation(Temp);
			temp_gene[temp_gene_index++] = Temp;
			Temp = crossover(Gene[inx2], Gene[inx1], crossover_point);
			Mutation(Temp);
			temp_gene[temp_gene_index++] = Temp;
		}
		for(int i=1;i<=gene_cnt;i++) Gene[i] = temp_gene[i];
	}
	end = clock();
	print_result();
	printf("elapsed time : %d\n",(int)((end - begin) / double(CLOCKS_PER_SEC)*1000));
	return 0;
}

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
int main(){
	srand(time(NULL));
	freopen("output.txt","w",stdout);
	int n = 800, m = 250, c = 179;

	printf("%d %d %d\n",n, m, c);
	for(int i=0;i<n;i++){
		int a, b;
		a = rand() % 9 + 1;
		b = rand() % 100 + 1;

		printf("%d %d\n",a, b);
	}
	for(int i=0;i<m;i++){
		double a = (double)rand() / RAND_MAX;
		printf("%lf\n",a);
	}
	return 0;
}

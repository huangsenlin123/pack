#include<iostream>
using namespace std;
const int MAX = 9999;

void backpack(int V, int U, int a[], int b[], int w[], int n[], int N) {
	int i, j, k, l, *x, ***dp;

	//��ʼ��
	dp = (int ***) malloc(sizeof(int **) * (N + 1));
	for (i = 0; i <= N; ++i) {
		dp[i] = (int **) malloc(sizeof(int *) * (V + 1));
		for (j = 0; j <= V; ++j) {
			dp[i][j] = (int *) malloc(sizeof(int) * (U + 1));
		}
	}
	for (i = 0; i <= N; ++i) {
		for (j = 0; j <= V; ++j) {
			memset(dp[i][j], 0, sizeof(int) * (U + 1));
		}
	}
	x = (int *) malloc(sizeof(int) * N); //��ӡ����
	memset(x, 0, sizeof(int) * N);

	//���
	for (i = 1; i <= N; ++i) {
		for (j = a[i - 1]; j <= V; ++j) {
			for (k = b[i - 1]; k <= U; ++k) {
				dp[i][j][k] = dp[i - 1][j][k];
				for (l = 1; l <= n[i - 1]; ++l) {
					if (l * a[i - 1] <= j && l * b[i - 1] <= k) {
						dp[i][j][k] =
							dp[i][j][k]
										> (dp[i - 1][j - l * a[i - 1]][k
											- l * b[i - 1]] + l * w[i - 1]) ?
											dp[i][j][k] :
										(dp[i - 1][j - l * a[i - 1]][k
											- l * b[i - 1]] + l * w[i - 1]);
					} else {
						break;
					}
				}
			}
		}
	}

	//��ӡ
	j = V;
	k = U;
	for (i = N; i > 0; --i) {
		if (dp[i][j][k] > dp[i - 1][j][k]) {
			for (l = 1; l * a[i - 1] <= j && l * b[i - 1] <= k; ++l) {
				if (dp[i][j][k]
				== (dp[i - 1][j - l * a[i - 1]][k - l * b[i - 1]]
				+ l * w[i - 1])) {
					x[i - 1] = l;
					j -= l * a[i - 1];
					k -= l * b[i - 1];
					break;
				}
			}
		}
	}
	printf("best value:%d\n", dp[N][V][U]);
	printf("best solution:");
	for (i = 0; i < N; ++i)
	{
		n[i] = n[i] - x[i];
		printf("%d ", x[i]);}
	printf("\n");
}
int main()
{
	int N = 10;//N�����͵������
	int V = 56;//�ܳ�������cpu����
	int U = 125;//�ܳ��ص������ڴ���
	int a[10] = {1,1,1,2,2,4,4,4,8,8};
	int b[10] = {1,2,4,4,8,4,8,16,6,16};
	int w[10] = {1,1,1,2,2,4,4,4,8,8};
	int n[10] = {1,2,1,2,2,9,8,8,5,4};
	bool Flag ;//�Ƿ��������û�в���ı�־����Ϊfalse��ʾ�Ѿ�û�������δ����Ϊtrue���������������
	do
	{
		backpack(V,U,a,b,w,n,N);
		Flag = false;
		for(int i=0;i<N;i++)
		{
			if(n[i]!=0)
				Flag = Flag || true;
		}
	}while (Flag);

	getchar();
	return 0;
}
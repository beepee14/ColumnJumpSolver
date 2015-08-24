#include <algorithm>
#include <iostream>
#define MOD 1298307964911120440ULL
using namespace std;

void getInitialConfiguration(vector<vector<int> > &initialConfiguration, int &numColors, int &dimMatrix)
{
	cin>>dimMatrix;
	cin>>numColors;
	for(int i = 0;i < dimMatrix; i++){
		vector<int> tempVec;
		for(int j = 0;j < dimMatrix; j++){
			int tempVal;
			cin>>tempVal;
			tempVec.push_back(tempVal);
		}
		initialConfiguration.push_back(tempVec)
	}
}
int getNumberOfDistinctColors(vector<vector<int> > & mat,int dimMatrix)
{
	set<int> distinctColors;
	for(int i=0;i<dimMatrix;i++)
	{
		for(int j=0;j<dimMatrix;j++)
		{
			distinctColors.insert(mat[i][j]);
		}
	}
	return (int)distinctColors.size();
}
int getHash(vector<vector<int> > &mat,int numColors,int dimMatrix)
{
	lli base = numColors;
	lli hashVal = 0 ;
	lli powBase = 1;
	for(int i=0;i<dimMatrix;i++)
	{
		for(int j=0;j<dimMatrix;j++)
		{
			powBase = (powBase * base)%MOD;
			powBase = (powBase * mat[i][j]) % MOD;
			hashVal = (hashVal + powBase)%MOD;
		}
	}
}
int main()
{
	freopen("input.txt","r",stdin);
	vector<vector<int> > initialConfiguration;
	int numColors, dimMatrix;
	getInitialConfiguration(initialConfiguration,numColors,dimMatrix);

}
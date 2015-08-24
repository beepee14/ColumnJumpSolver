#include <algorithm>
#include <iostream>
#define MOD 1298307964911120441ULL
using namespace std;

map<lli, vector<vector<int> > > hashStore;
map<lli, lli> parent;
map<lli, int> dist; 
map<lli, pair<pair<int,int > > > parentJump;
int numColors, dimMatrix;

int dirx[4] = {0,1,0,-1};
int diry[4] = {1,0,-1,0};

bool validMove(int x,int y)
{
	if(x>=0 and y>=0 and x<dimMatrix and y<dimMatrix)
		return true;
	return false;
}

void getInitialConfiguration(vector<vector<int> > &initialConfiguration)
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

int getNumberOfDistinctColors(vector<vector<int> > & mat)
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

bool checkSolutionFound(vector<vector<int> > &mat)
{
	int counter = 0;
	for(int i=0;i<dimMatrix; i++)
	{
		for(int j=0;j<dimMatrix; j++)
		{
			if(mat[i][j]!=0)
				counter+=1;
		}
	}
	if(counter==1)
		return true;
	return false;
}

int getHash(vector<vector<int> > &mat)
{
	lli base = numColors;
	lli hashVal = 0 ;
	lli powBase = 1;
	for(int i=0;i<dimMatrix;i++)
	{
		for(int j=0;j<dimMatrix;j++)
		{
			powBase = (powBase * base)%MOD;
			lli val = (powBase * mat[i][j]) % MOD;
			hashVal = (hashVal + val)%MOD;
		}
	}
	hashStore[hashVal] = mat;
	return hashVal;
}

lli addMoves(vector<vector<int> > &config, priority_queue<pair<int, lli> > nextMoves)
{

	for(int i=0;i<dimMatrix;i++)
	{
		for(int j=0;j<dimMatrix;j++)
		{
			for(int k=0;k<4;k++)
			{
				int valid = false;
				int currX=i + dirx[k],currY = j + diry[k];
				if(!validMove(currX,currY) || config[currX][currY] == 0 || config[currX][currY] == config[i][j])
					continue;
				while(true)
				{
					if(!validMove(currX + dirx[k],currY + diry[k]))
						break;
					if(config[currX + dirx[k]][currY + diry[k] ] == 0)
					{
						valid=1;
						break;
					}
					if(config[currX + dirx[k]][currY + diry[k] ] != config[currX][currY])
						break;
					currX += dirx[k];
					currY += diry[k];
				}
				if(valid)
				{
					vector<vector<int> > newConfig = config;
					currX=i; currY = j;
					while(config[currX][currY]!=0)
					{
						newConfig[currX][currY] = 0;
						currX += dirx[k];
						currY += diry[k];
					}

					lli newHashVal = getHash(newConfig);
					lli origHashVal = getHash(config);
					parentJump[newHashVal] = make_pair(make_pair(i+1,j+1),make_pair(currX+1,currY+1));
					dist[newHashVal] = dist[origHashVal] + 1;
					parent[newHashVal] = origHashVal;
					lli distinctColors = getNumberOfDistinctColors(newConfig) - 1;
					nextMoves.push(make_pair(distinctColors + dist[newHashVal]));
					if(checkSolutionFound(newConfig))
						return newHashVal;
				}
			}
		}
	}
	return -1;
}
void printSolution(lli finalState)
{
	vector<pair<pair<int,int> > > ans;
	while(parent[finalState] != -1)
	{
		ans.push_back(parentJump[finalState]);
		finalState = parent[finalState]; 
	}
	reverse(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++)
	{
		cout<<"("<<ans[i].first.first<<","<<ans[i].first.second<<") ("<<ans[i].second.first<<","<<ans[i].second.second<<")\n";
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	vector<vector<int> > initialConfiguration;
	priority_queue<pair<int, lli>, greater<pair<int, lli> > > nextMoves;
	lli finalState;
	getInitialConfiguration(initialConfiguration);
	lli hashVal = getHash(initialConfiguration);
	parent[hashVal] = -1;
	dist[hashVal] = 0;
	int distinctColors = getNumberOfDistinctColors(initialConfiguration) - 1;
	nextMoves.push(mp(distinctColors, hashVal));
	while(!nextMoves.empty())
	{
		pair<int,lli> topElement = nextMoves.top();
		nextMoves.pop();
		finalState = addMoves(hashStore[topElement.second], nextMoves);
		if(finalState != -1)
			break;
	}
	printSolution(finalState);
}

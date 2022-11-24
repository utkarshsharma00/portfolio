#include <bits/stdc++.h>
#include <unordered_map> 
#include <ctime>
#include<chrono>

using namespace std;

float Tmax;
int ritvik=0;
int max_hill_climbs=0;
int **costMatrix;
unordered_map<char, int> charIndex; 
unordered_map<int, char> indexChar;

int dashCost;
int charCount;
void printList(vector<vector<int> > s){
	for(int i=0; i<s.size(); i++){
		for(int j=0; j<s[i].size();j++)
			cout<<s[i][j]<<" ";
		cout<<endl;
	}
	return;
}

void printChar(vector<vector<char> > s){
	for(int i=0; i<s.size(); i++){
		for(int j=0; j<s[i].size();j++)
			cout<<s[i][j]<<" ";
		cout<<endl;
	}
	return;
}

vector<vector<int> > readFile(int &k, int &dashCost,char *file){

	
	int s_len;
	// int k = 0; //max length of any string
	
	ifstream inFile;
	inFile.open(file);

	if (!inFile.is_open()) 
	{
		cout<<"file doesn't open"<<endl;
		vector<vector<int> > v = {{0}};
		return v ;
	}

	inFile >> Tmax;
	// cout << Tmax <<endl;
	inFile >> charCount;
	// cout << charCount <<endl;
	int word;
	int index = 1;
	char c;
	char comma;
	charIndex['-'] = 0;
	indexChar[0] = '-';
	for(int i=0; i<charCount; i++){
		inFile >> c;
		// cout << c <<", ";
		if(i!= charCount-1) inFile >> comma;
		charIndex[c] = i+1;
		indexChar[i+1] = c;
	}

	// cout<< endl;
	inFile >> s_len;
	// inFile >> s_len;
	// cout<<"s_len "<<s_len<<endl;
	vector<string> s(s_len);
	k = 0;
	for(int i=0; i<s_len; i++){
		inFile >> s[i];
		if(k<s[i].size()) k = s[i].size();
		// cout << s[i] <<endl;
	}

	inFile >> dashCost;
	// cout<<dashCost<<endl;
	costMatrix = (int**)malloc(sizeof(int*)*(charCount+1));

	for(int i=0 ;i<(charCount+1); i++){
		costMatrix[i] = (int*)malloc(sizeof(int)*(charCount+1));
	}

	for(int i=0 ;i<(charCount+1); i++){
		for(int j=0; j<(charCount+1); j++){
			inFile >> costMatrix[i][j];
			// cout << costMatrix[i][j]<<" ";
		}
		// cout<<endl;
	}

	inFile.close();
	
	vector<vector<int> > vect(s_len);
	int val=0;
	for(int i=0; i<s_len; i++){
		for(int j=0; j<s[i].size(); j++){
			val = (charIndex[s[i][j]]);
			vect[i].push_back(val);
		}
	}
	s.clear();
	// cout<<endl;
	// cout<<"Converted string input is:" <<endl;
	// printList(vect);
	return vect ;
}


vector<vector<char> > convertBack(vector<vector<int> > v){
	vector<vector<char> > str(v.size(),vector<char>(v[0].size()));

	for(int i=0; i<v.size(); i++){
		for(int j=0 ; j<v[0].size(); j++){
			str[i][j] = indexChar.at(v[i][j]);
		}
	}

	return str;
}

int costNode(vector<vector<int> > arr, int lastMax){
	int costN = 0;
	int pnt=0;
	int r,c;
	while(pnt<arr[0].size()){
		for(int i=0; i<arr.size(); i++){
			if(arr[i][pnt]==0) 
				costN = costN + dashCost;
			if(costN>lastMax) break;
			for(int j=i+1; j<arr.size(); j++){

				if(arr[i][pnt]==0 && arr[j][pnt]!=0)
					costN = costN + costMatrix[charCount][arr[j][pnt]-1];

				else if(arr[j][pnt]==0 && arr[i][pnt]!=0)
					costN = costN + costMatrix[arr[i][pnt]-1][charCount];

				else if(arr[j][pnt]==0 && arr[i][pnt]==0)
					costN = costN + costMatrix[charCount][charCount];

				else costN = costN + costMatrix[arr[i][pnt]-1][arr[j][pnt]-1];

				if(costN>lastMax) break;
			}
		}	
		if(costN>lastMax) break;
		pnt++;
	}
	// cout<<"done \n";
	return costN;
}

vector<vector<int> > random_start(vector<vector<int> > vect, int k){
	// srand (time(NULL));
	int zeroes = 0;
	int random = 0;

	for(int i=0; i<vect.size(); i++){
		zeroes = k-vect[i].size();
		for(int j=0; j<zeroes; j++){
			random = rand()%vect[i].size();
			vect[i].insert(vect[i].begin()+random,0);
		}
	}

	return vect;
}

int oneStep(vector<vector<int> > &v, int ind, int prev_cost){  //oneStep returns a new bect vect if its cost is better than
	bool changed = false;								   //already calculated prev_cost
	// srand(time(NULL));
	int minCost = prev_cost;
	vector<vector<int> > bestVect = v;
	vector<vector<int> > sample;
	int temp=0;

	for(int i=0; i<v[ind].size(); i++){
		if(i!=v[ind].size()-1){
			if(v[ind][i]==0 && v[ind][i+1]!=0){
				sample = v;
				temp = sample[ind][i];
				sample[ind][i] = sample[ind][i+1];
				sample[ind][i+1] = temp;
				int c = costNode(sample, minCost);
				if( minCost > c){
					bestVect = sample;
					minCost = c;
				}
				sample.clear();
			}
		}
		if(i!=0){
			if(v[ind][i]==0 && v[ind][i-1]!=0){
				sample = v;
				temp = sample[ind][i];
				sample[ind][i] = sample[ind][i-1];
				sample[ind][i-1] = temp;
				int c = costNode(sample, minCost);
				if( minCost > c){
					bestVect = sample;
					minCost = c;
				}
				sample.clear();
			}
		}
	}
	v = bestVect;
	bestVect.clear();
	return minCost;

}

void randomJump(vector<vector<int> > &vect){
	int t=0;
	int temp=0;
	int zeroInd = 0;
	for(int ind=0; ind<vect.size(); ind++){
		t = rand()%10;
		if(t<5){
			zeroInd = rand()%(vect[ind].size()-2)+1;
			int count=0;
			while(!(vect[ind][zeroInd]==0 && (vect[ind][zeroInd+1]!=0 || vect[ind][zeroInd-1]!=0)) && count<vect[ind].size()){
				zeroInd = rand()%(vect[ind].size()-2)+1;
				count++;
			}
			if(vect[ind][zeroInd]==0){
				if(vect[ind][zeroInd+1]!=0){
				temp = vect[ind][zeroInd];
				vect[ind][zeroInd] = vect[ind][zeroInd+1];
				vect[ind][zeroInd+1] = temp;
				}
				else if(vect[ind][zeroInd-1]!=0){
					temp = vect[ind][zeroInd];
					vect[ind][zeroInd] = vect[ind][zeroInd-1];
					vect[ind][zeroInd-1] = temp;
				}
			}
		}
	}
	return;
}


int local_search(vector<vector<int> > &vect, int prev_cost){

	int counter=0;
	int curr_cost=prev_cost;
	int initiate = rand()%vect.size();
	vector<vector<int> > vect2=vect;  //change
	vector<vector<int> > best = vect;
	for(int i=0; i<vect.size(); i++){
		vect2 = vect;    
		int c = oneStep(vect2,(initiate+i)%vect.size(), curr_cost);
		if(curr_cost > c){
			best = vect2;
			curr_cost = c;
			if(vect[0].size()>1000)
				break;	
		}	
		vect2.clear();
	}
	// cout<<"Best till now:"<<curr_cost<<endl;
	// printChar(convertBack(best));
	// cout<<endl;
	if((vect[0].size()>1000 && max_hill_climbs<50) || vect[0].size()<1000){
		if(best!=vect){
			max_hill_climbs++;
			curr_cost = local_search(best, curr_cost);
			vect=best;
		}	
	}
	best.clear();
	return curr_cost;	

}

int main(int argc,char *argv[]){
	
	char *in_file = argv[1];
	char *output_file = argv[2];

	int k=0;

	vector<vector<int> > vect = readFile (k, dashCost, in_file);
	vector<vector<char> > output_matrix;

	// vector<vector<int> > v = {{2, 4, 7, 4, 7, 8, 7, 4},
	// 							{3, 0, 0, 8, 0, 0, 0, 3},
	// 							{6, 0, 0, 0, 7, 8, 8, 1},
	// 							{5, 0, 0, 0, 8, 0, 0, 2}};

	// cout<<"cost node: "<<costNode(v, INT_MAX);
	// printChar(convertBack(v));
	// return 0;

	auto start = chrono::high_resolution_clock::now();
	vector<vector<int> > vect_rand;
	srand (time(0));

	int bestCost = INT_MAX;
	int extraLen = 0;
	int time_len = 10;
	float timer2=0;				////////////////////////////////////
	vector<vector<int> > bestVect;
	ofstream output(output_file);

	while(extraLen < time_len){
		int lenBest = INT_MAX;
		vector<vector<int> > lenVect;
		vect_rand = random_start(vect, k+extraLen);
		for(int i=0; i<1000; i++){
			auto curr = chrono::high_resolution_clock::now();
			auto sec = curr - start;
			// cout<<"Before Rand Jump:"<<endl;
			// printList(vect_rand);

			float timer=(sec.count()*1e-9);
			// cout << timer << endl;
			// cout << "Tmax" << Tmax << endl;
			if(timer+timer2>((Tmax*60)-1)){								//////////////////////////////////////
				// cout << "Time Out" << endl;
				cout<<costNode(lenVect,INT_MAX);
				for(int i=0;i<lenVect.size();i++){
					for(int j=0;j<lenVect[i].size();j++){
						output << output_matrix[i][j];
					}
					output << endl;
				} 
				curr = chrono::high_resolution_clock::now();
				sec = curr - start;
				timer=(sec.count()*1e-9);
				cout<<"timer out"<<timer<<endl;
			return 0;
			}

			if (rand()%10 < 5) vect_rand = random_start(vect, k+extraLen);
			else randomJump(vect_rand);
			// cout<<"After Rand Jump:"<<endl;
			// printList(vect_rand);
			// cout<<"random start: "<<endl;
			// printList(vect_rand);
			int initial_cost = costNode(vect_rand,INT_MAX);
			max_hill_climbs = 0;
			// cout<<"cost: "<<initial_cost<<endl;
			int localCost = local_search(vect_rand, initial_cost);							
			curr = chrono::high_resolution_clock::now();									/////////////////////////
			sec = curr - start;																///////////////////////
			timer2=(sec.count()*1e-9);													//////////////////////////////
			cout << "Cost after local search is " << localCost << " time "<<timer2-timer << endl; 
			// cout << "Output matrix:" <<endl;
			// printChar(convertBack(vect_rand));
			// printList(vect_rand);
			if(lenBest > localCost){
				lenBest = localCost;
				lenVect = vect_rand;
			} 
			output_matrix = convertBack(lenVect);
		    
		}
		extraLen++;
		// cout<<"len best "<<extraLen-1<<" cost: "<<lenBest<<endl;
		if(bestCost > lenBest){
			bestCost = lenBest;
			bestVect = lenVect;
		} 
		lenVect.clear();
		vect_rand.clear();

	}
	// cout<<endl<<endl;
	cout<<"BEST Cost: "<<bestCost<<endl;
	// printChar(output_matrix);
	output_matrix = convertBack(bestVect);	

	for(int i=0;i<bestVect.size();i++){
		for(int j=0;j<bestVect[i].size();j++){
			output << output_matrix[i][j];
		}
		output << endl;
	} 


	auto end = chrono::high_resolution_clock::now(); 

    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); 
  
    time_taken *= 1e-9; 
 
    // cout << "Time taken by program is : " << fixed << time_taken << setprecision(9); 
    // cout << " sec" << endl;

	return 0;
}	

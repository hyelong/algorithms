#include <iostream>
#include <vector>
using namespace std;

struct Radar{
	Radar* father;
	int rank;
	double low;
	double high;
	double x;
	double y;
	double r;
	Radar(double _x, double _y, double _r):x(_x),y(_y),r(_r){
		rank = 0;
		father = NULL;
		low = y-r;
		high = y+r;
	}
};

bool overlaped(Radar*& radar1, Radar*& radar2){
	double dis = (radar1->x - radar2->x)*(radar1->x - radar2->x) + 
								(radar1->y - radar2->y)*(radar1->y - radar2->y);
	if(dis <= (radar1->r + radar2->r)*(radar1->r + radar2->r)) return true;
	return false;
}

Radar* find(Radar*& radar){
	if(!radar->father) return radar;
	return radar->father = find(radar->father);
}

void uion(Radar*& radar1, Radar*& radar2){
	Radar* r1 = find(radar1);
	Radar* r2 = find(radar2);
	
	if(r1==r2) return;
	
	if(r2->rank < r1->rank){
		radar1->father = r2;
		r1->rank++;
		//only need to update the root
		r2->low = min(r1->low, r2->low);
		r2->high = max(r1->high, r2->high);
	}
	else{
		radar2->father = r1;
		r1->rank++;
		//only need to update the root
		r1->low = min(r1->low, r2->low);
		r1->high = max(r1->high, r2->high);
	}
	
	
}

bool canPass(vector<Radar*>& radars){
	for(int i=0;i<radars.size();i++){
		if(radars[i]->low<=0 && radars[i]->high>=1) return false;
	}
	
	for(int i = 0; i<radars.size(); i++){
		for(int j = i+1; j<radars.size(); j++){
			if(overlaped(radars[i], radars[j])){
				uion(radars[i], radars[j]);
			}
		}
	}
	
	for(Radar* radar : radars){
		if(radar->low <= 0 && radar->high >= 1) return false;
	}
	return true;
}

int main(){
	vector<Radar*> radars;
	radars.push_back(new Radar(0.1, 0.2, 0.3));
	radars.push_back(new Radar(0.2, 0.2, 0.3));
	radars.push_back(new Radar(0.3, 0.5, 0.4));
	radars.push_back(new Radar(0.4, 0.8, 0.1));
	
	radars.push_back(new Radar(10, 0.3, 0.4));
	radars.push_back(new Radar(10, 0.6, 0.4));
	
	bool res = canPass(radars);
	cout<<res<<endl;
	
	cout<<"-------------"<<endl;
	for(Radar* r : radars){
		cout<< r->low <<":"<<r->high<<", "<<r->rank<<endl;
	}
	return 0;
}



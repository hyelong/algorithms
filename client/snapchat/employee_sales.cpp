#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

struct Employee{
    string name;
    int sold;
    string offset;
    vector<Employee*> subs;

    Employee(string s) :  name(s) {};
};

struct Relation{
    string name;
    string boss;
    int sold;
    Relation(string n, string b, int s) : name(n), boss(b), sold(s) {}
};

class Solution{
public:
    Employee* buildTree(vector<Relation> records){
        for(auto& relation : records){
            if(!m.count(relation.name)){
                m[relation.name] = new Employee(relation.name);
            }
            if(!m.count(relation.boss)){
                m[relation.boss] =  new Employee(relation.boss);
            }
        
            m[relation.name]->sold = relation.sold;
            m[relation.boss]->subs.push_back(m[relation.name]);
        }
        return m[""]->subs[0]; 
    }

    int updateTotal(Employee* root){
        if(root->subs.empty()) return root->sold;

        for(auto& sub : root->subs){
            root->sold += updateTotal(sub);
        }
        return root->sold;
    }

    void preorderPrint(Employee* root){
        cout << root->offset << root->name << " " << root->sold << endl;
        for(auto it = root->subs.begin(); it!=root->subs.end(); it++){
            (*it)->offset = root->offset + "   ";
            preorderPrint(*it);
        }
    }
    
    void print_tree(Employee*& root, string ancestor, Employee*& ori_root){
    	  cout << root->offset << ((root==ori_root)?"":"-") <<root->name << " " << root->sold << endl;
        for(auto it = root->subs.begin(); it!=root->subs.end(); it++){
        	if(it+1 == root->subs.end()){
        		(*it)->offset = ancestor + " \\";
        		print_tree(*it, ancestor + "  ", ori_root);
        	}
        	else{
        		(*it)->offset = ancestor + " |";
        		print_tree(*it, ancestor + " |", ori_root);
        	}
        }
    }
    

private:
    unordered_map<string, Employee*> m;
};

int main(){
    Solution sol;
    vector<Relation> records = {
                {"Carol","Bob",2},
                {"David","Bob",3},
                {"Bob","Alice",3},
                {"Richard","Carol",5},
                {"Tom","Carol",5},
                {"Ferris","Eve",1},
                {"FerrisC","Ferris",1},
                {"Kim","Richard",5},
                {"Eve","Alice",2},
                {"Alice","",5}
    };
    auto ceo = sol.buildTree(records);
    int t = sol.updateTotal(ceo);
    sol.print_tree(ceo, "", ceo);
}

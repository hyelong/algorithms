#include <iostream>
using namespace std;


struct Employee{
	string name;
	Employee* employee1=NULL;
	Employee* employee2=NULL;
	Employee(string s):name(s){}
};

Employee* helper(Employee* employee, Employee* manager, Employee* e1, Employee* e2){
	if(!employee) return employee;
	if(employee==e1 || employee==e2) return manager;
	Employee *left = NULL, *right = NULL;
	left = helper(employee->employee1, employee, e1, e2);
	right = helper(employee->employee2, employee, e1, e2);
	if(!left) return right;
	if(!right) return left;
	return employee;
}


Employee* find_common_manager(Employee* employee, Employee* e1, Employee* e2){
	if(!employee) return employee;
	return helper(employee, NULL, e1, e2);
}


int main(){
	Employee *ceo = new Employee("ceo");
	ceo->employee1 = new Employee("manager1");
	ceo->employee2 = new Employee("manager2");
	ceo->employee1->employee1 = new Employee("manager11");
	ceo->employee1->employee2 = new Employee("manager12");
	ceo->employee2->employee1 = new Employee("manager21");
	ceo->employee2->employee2 = new Employee("manager22");
	Employee* res = find_common_manager(ceo, ceo->employee1, ceo->employee1->employee2);
	
	cout<<res->name<<endl;
	return 0;
}

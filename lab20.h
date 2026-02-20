#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<iomanip>

using namespace std;

class Equipment{
	int hpmax;
	int atk;
	int def;
	public:
		Equipment(int h,int a,int d){
			hpmax = h;
			atk = a;
			def = d;
		}
		vector<int> getStat(){
			vector<int> stat;
			stat.push_back(hpmax);
			stat.push_back(atk);
			stat.push_back(def);
			return stat;
		}			
};

class Unit{
	string name;
	string type;		
	int hp;
	int hpmax;
	int atk;
	int def;
	bool guard_on;
	bool dodge_on; 
	Equipment *equipment; 

public:			
	Unit(string,string); 
	void showStatus();
	void newTurn();
	int attack(Unit &);
	int ultimateAttack(Unit &); 
	int beAttacked(int);
	int heal();	
	void guard();
	void dodge(); 
	bool isDead();
	void equip(Equipment *);  
};

Unit::Unit(string t,string n){ 
	type = t;
	name = n;

	if(type == "Hero"){
		hpmax = rand()%20+120;
		atk = rand()%5+14;
		def = rand()%3+9;
	}
	else if(type == "Monster"){
		hpmax = rand()%20+250;
		atk = rand()%5+25;
		def = rand()%3+5;
	}

	hp = hpmax;	
	guard_on = false;
	dodge_on = false;
	equipment = NULL;
}

void Unit::showStatus(){
	cout << "---------------------------------------" << endl;
	cout << name << endl;
	cout << "HP: " << hp << "/" << hpmax
		 << "\tATK: " << atk
		 << "\t\tDEF: " << def << endl;
	cout << "---------------------------------------" << endl;
}


void Unit::newTurn(){
	guard_on = false;
	dodge_on = false;
}

int Unit::attack(Unit &opp){
	return opp.beAttacked(atk);
}

int Unit::ultimateAttack(Unit &opp){
	return opp.beAttacked(atk*2);
}

int Unit::beAttacked(int oppatk){
	int dmg = 0;

	if(oppatk > def){
		dmg = oppatk - def;

		if(guard_on){
			dmg /= 3;
		}

		if(dodge_on){
			if(rand()%2 == 0){
				dmg = 0;
			}
			else{
				dmg *= 2;
			}
		}
	}

	hp -= dmg;
	if(hp < 0) hp = 0;

	return dmg;
}

int Unit::heal(){
	int h = rand()%21 + 10;

	if(hp + h > hpmax)
		h = hpmax - hp;

	hp += h;
	return h;
}

void Unit::guard(){
	guard_on = true;
}

void Unit::dodge(){
	dodge_on = true;
}

bool Unit::isDead(){
	return hp <= 0;
}

void Unit::equip(Equipment *eq){

	if(equipment != NULL){
		vector<int> oldStat = equipment->getStat();
		hpmax -= oldStat[0];
		atk   -= oldStat[1];
		def   -= oldStat[2];
	}

	equipment = eq;

	vector<int> newStat = eq->getStat();
	hpmax += newStat[0];
	atk   += newStat[1];
	def   += newStat[2];

	if(hp > hpmax){
		hp = hpmax;
	}
}

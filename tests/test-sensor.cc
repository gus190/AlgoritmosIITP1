#include <classes/Sensor.h>
#include <iostream>

int main(){
	char ch;
	string name;
	size_t count=0;
	double daux;
	Package pkg;
	Sensor s;
	Range rg;
	size_t minrg,maxrg;
	while (cin >> ch) {
		switch (ch){
			case 'A':
			// Add elements to sensor
				while(cin >> ch && ch == ','){
					if(cin >> daux){
						pkg.set(count,count+1,daux);
						s + pkg;
						count++;
					}else{
						cout << "Bad input parse. ex.: S,20,10,12,13;" << endl;
						cout << "Bad input parse" << endl;
						s.clear();
						break;
					}
				}
				s.buildTree();
				break;
			case 'C': 
			// clear st
				s.clear();
				count = 0;
				break;
			case 'N': 
			// set name
				cin >> ch;
				cin >> name;
				s.name(name);
				break;
			case 'Q':
			//query
				if(cin >> ch && ch == ',' && cin >> minrg && cin >> ch && ch== ',' && cin >> maxrg){
					rg.range(minrg,maxrg);
					pkg = s.query(0,rg);
					pkg.printStd(cout);
				}else{
					cout << "Bad query"<<endl;
				}
				break;
			case 'P': 
			// print st
				cout << s << endl;
				break;
			default:
				cout << "error: unknown command (";
				cout << ch;
				cout << ")";
				cout << endl;
				break;
		}
	}
}
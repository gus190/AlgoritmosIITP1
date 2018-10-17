#include <classes/Package.h>
#include <classes/Range.h>
#include <classes/SegmentTree.h>
#include <iostream>

using namespace std;

int main(){
	char ch;
	size_t count;
	double daux;
	Package pkg;
	Array<Package> arr;
	SegmentTree st;

	while (cin >> ch) {
		switch (ch){
		case 'S':{ 
		// Set elements to array
			arr.clear();
			count = 0;
			while(cin >> ch && ch == ','){
				if(cin >> daux){
					pkg.set(count,count+1,daux);
					arr.push_back(pkg);
					count++;
				}else{
					cout << "Bad input parse. ex.: S,20,10,12,13;" << endl;
					cout << "Bad input parse" << endl;
					arr.clear();
					break;
				}
			}
			cout << endl << arr;
			break;
		}
		case 'B': 
		// Build st from array
			{ 
			SegmentTree saux(arr);
			st = saux;
			break;
			}
		case 'C': 
		// clear st
			st.clear();
			break;
		case 'P': 
		// print st
			cout << st << endl;
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
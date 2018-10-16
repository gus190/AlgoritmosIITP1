#include <Package.h>
#include <Range.h>
#include <SegmentTree.h>
#include <iostream>

using namespace std;

int main(){
	char ch;
	size_t count;
	double daux;
	Package pkg;
	Range rg;
	Array<Package> arr;
	SegmentTree st;

	while (cin >> ch) {
		switch (ch){
		case 'S':{ // Set elements to array
			arr.clear();
			count = 0;
			while(cin >> ch){
				if(ch != ','){
					break;
				}
				if(cin >> daux){
					pkg.range(count,count+1);
					pkg.min(daux);
					pkg.max(daux);
					pkg.avg(daux);
					pkg.count(1);
					pkg.exist(true);
					arr.push_back(pkg);
					count++;
				}else{
					cout << "Bad input parse. ex.: A,20,10,12,13,E" << endl;
					cout << "Bad input parse" << endl;
					arr.clear();
					break;
				}
			}
			cout << arr;
			break;
		}
		case 'B': // Build st from array
			{ 
			SegmentTree saux(arr);
			st = saux;
			break;
			}
		case 'C': // clear st
			st.clear();
			break;
		case 'P': // print st
			cout << st;
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
#include <classes/Package.h>
#include <classes/Range.h>
#include <classes/SegmentTree.h>
#include <iostream>

using namespace std;

int main(){
	char ch;
	size_t count=0;
	double daux;
	Package pkg;
	SegmentTree st;

	while (cin >> ch) {
		switch (ch){
			case 'A':
			// Add elements to st
				while(cin >> ch && ch == ','){
					if(cin >> daux){
						pkg.set(count,count+1,daux);
						st + pkg;
						count++;
					}else{
						cout << "Bad input parse. ex.: S,20,10,12,13;" << endl;
						cout << "Bad input parse" << endl;
						st.clear();
						break;
					}
				}
				break;
			case 'C': 
			// clear st
				st.clear();
				count = 0;
				break;
			case 'P': 
			// print st
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
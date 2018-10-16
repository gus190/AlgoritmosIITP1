#include <Package.h>
#include <Range.h>
#include <iostream>

using namespace std;

int main(){
	char ch;
	double min,max,avg;
	Range r;
	size_t rgmin,rgmax,count;
	Package A;
	Package B;
	Package aux;
	while (cin >> ch) {
		switch (ch) {
		case 'A': // set A
			if(cin>>ch && ch==',' && cin>>rgmin && cin>>ch && ch==',' &&
				cin>>rgmax && cin>>ch && ch==',' && cin>>min && cin>>ch && ch==',' && cin>>max
				&& cin>>ch && ch==',' && cin>>avg
				&& cin>>ch && ch==',' && cin>>count){
					A.range(rgmin,rgmax);
					A.min(min);
					A.max(max);
					A.avg(avg);
					A.count(count);
					A.exist(true);
			}else{
				A.clear();
				cout << "Bad pkg parse. ex.: A,0,1,10,20,15,2" << endl;
				cout << "where input: <pkg>,<rgmin>,<rgmax>,<min>,<max>,<avg>,<count>" << endl;
			}
			break;
		case 'B': // set B
			if(cin>>ch && ch==',' && cin>>rgmin && cin>>ch && ch==',' &&
				cin>>rgmax && cin>>ch && ch==',' && cin>>min && cin>>ch && ch==',' && cin>>max
				&& cin>>ch && ch==',' && cin>>avg
				&& cin>>ch && ch==',' && cin>>count){
					B.range(rgmin,rgmax);
					B.min(min);
					B.max(max);
					B.avg(avg);
					B.count(count);
					B.exist(true);
			}else{
				B.clear();
				cout << "Bad pkg parse. ex.: A,0,1,10,20,15,2" << endl;
				cout << "where input: <pkg>,<rgmin>,<rgmax>,<min>,<max>,<avg>,<count>" << endl;
			}
			break;
		case 'C': // clear
			if(cin >> ch && ch == 'A'){
				A.clear();
			}else if(ch == 'B'){
				B.clear();
			}else {
				cout << "bad parameter for Clear C(A or B)";
			}
			cout << endl;
			break;
		case 'P': // print
			if(cin >> ch && ch == 'A'){
				cout << A;
			}else if(ch == 'B'){
				cout << B;
			}else {
				cout << "bad parameter for Print P(A or B)";
			}
			cout << endl;
			break;
		case 'M': // Merge A and B, store in A (print 3 different forms)
			aux = A;
			aux.merge(B);
			cout << "Forma 1: merge(pkg) = "<< aux;
			aux.merge(A,B);
			cout << "Forma 2: merge(pkg1,pkg2) = "<< aux;
			aux = A+B;
			cout << "Forma 3: suma usada como merge = "<< aux;
			A = aux;
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
}
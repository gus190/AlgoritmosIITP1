
#include <range.h>
#include <iostream>

using namespace std;

int main(){
	char ch;
	int rgmax,rgmin;
	Range A;
	Range B;
	Range aux;
	while (cin >> ch) {
		switch (ch) {
		case 'A': // set A
			if(cin>>ch && ch==',' && cin>>rgmin && cin>>ch && ch==',' &&
				cin>>rgmax){
					A.setRange(rgmin,rgmax);
					aux = A;
					cout << aux;
			}else{
				A.clear();
				cout << "Bad range parse . "<< rgmin << A << endl;
			}
			cout << endl;
			break;
		case 'B': // set B
			if(cin>>ch && ch==',' && cin>>rgmin && cin>>ch && ch==',' &&
				cin>>rgmax){
				B.setRange(rgmin,rgmax);
				aux = B;
				cout << aux;
			}else{
				B.clear();
				cout << "Bad range parse. "  << B << endl;
			}
			cout << endl;
			break;
		case 'C': // clear
			if(cin >> ch && ch == 'A'){
				A.clear();
				cout << A;
			}else if(ch == 'B'){
				B.clear();
				cout << B;
			}else {
				cout << "bad parameter for Clear C(A or B)";
			}
			cout << endl;
			break;
		case 'n': // A n B
			aux = A;
			aux.intersection(B);
			cout << aux;
			cout << endl;
			break;
		case 'u': // A u B
			aux = A + B;
			cout << aux;
			cout << endl;
			break;
		case 'E': // is empty?
			cout << "A is empty? " ;
			if(A.empty())
				cout << "true";
			else 
				cout << "false";
			cout << endl;
			break;
		case 'D': // A is different from B ?
			cout << "A != B? " << (A != B);
			cout << endl;
			break;
		case 'I': // A inside B?.
			cout << "Ac=B? " << A.isInside(B);
			cout << endl;
			break;
		case 'P':
			// print
			cout << "A:" << A << ",B:" << B;
			cout << endl;
			break;
		case 'N':
			// A intersects B?.
			cout << "A intersects B?: " << A.intersects(B);
			cout << endl;
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
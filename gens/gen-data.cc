	#include <cstdlib>
	#include <gens/gen-data.h>
	#include <classes/Cmdline.h>
	
	using namespace std;

	#define DEFAULTNUM  3;
	#define DEFAULTSAMPLES 10;
	#define DEFAULTMIN 15;
	#define DEFAULTMAX 55;
	#define DEFAULTRAND 0;
	
	static size_t number = 0;
	static size_t samples = 0;
	static int randNodata = 0;
	static int minRange = 0;
	static int maxRange = 0;
	static ostream *oss = NULL;		// Output Stream
	static fstream ofs;				// Output File Stream

	static option_t options[] = {
		{1, "n", "number", "-", opt_number, OPT_DEFAULT},
		{1, "s", "samples", "-", opt_samples, OPT_DEFAULT},
		{1, "r", "range", "-", opt_range, OPT_DEFAULT},
		{1, "o", "output", "-", opt_output, OPT_DEFAULT},
		{1, "nd", "nodata", "-", opt_nodata, OPT_DEFAULT},
		{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
		{0, },
	};

	static void opt_number(string const &arg){
		if (arg == "-") {	//Por defecto
			number = DEFAULTNUM;
		}
		else {				// si no 
			stringstream argStream;
			argStream.str(arg);
			if(argStream >> number){
				
			}
			else{
				cerr << "cannot parse sensor cuantity "
					 << arg
					 << "."
					 << endl;
				exit(2);
			}
		}
	}
	static void opt_samples(string const &arg){
		if (arg == "-") {	//Por defecto
			samples = DEFAULTSAMPLES;
		}
		else {				// si no 
			stringstream argStream;
			argStream.str(arg);
			if(argStream >> samples){
				
			}
			else{
				cerr << "cannot parse sample cuantity "
					 << arg
					 << "."
					 << endl;
				exit(2);
			}
		}
	}
	static void opt_nodata(string const &arg){
		if (arg == "-") {	//Por defecto
			randNodata = DEFAULTRAND;
		}
		else {				// si no 
			stringstream argStream;
			argStream.str(arg);
			if(argStream >> randNodata && randNodata <= 100 && randNodata >= 0){
				
			}
			else{
				cerr << "cannot parse random data erase [0,100] value was: "
					 << arg
					 << "."
					 << endl;
				exit(2);
			}
		}
	}
	static void opt_range(string const &arg){
		if (arg == "-") {	//Por defecto
			minRange = DEFAULTMIN;
			maxRange = DEFAULTMAX;
		}
		else {				// si no 
			stringstream argStream;
			char ch;
			argStream.str(arg);
			if(argStream >> minRange && 
				argStream >> ch && 
				ch == ',' && 
				argStream >> maxRange && 
				maxRange >= minRange ){
				
			}
			else{
				cerr << "cannot parse sample cuantity "
					 << arg
					 << "."
					 << endl;
				exit(2);
			}
		}
	}

	static void opt_output(string const &arg){

		if (arg == "-") {	// por defecto
			oss = &cout;	// cout como salida
		} else {			// si no
			ofs.open(arg.c_str(), ios::out);
			oss = &ofs;		// archivo como salida
		}
		// Verificamos que el archivo se halla abierto.
		if (!oss->good()) {
			cerr << "cannot open output file"
			     << arg
			     << "."
			     << endl;
			exit(1);
		}
	}

	static void opt_help(string const &arg){
		// ayuda
		cout << "program -n [number of sensors] -s [number of samples] -r [min],[max] -nd [porcentage of no data] -o <output file>" << endl;
		exit(0);
	}

	
	// ---- main ---- //
	int main(int argc, char * const argv[]){
		//parseo de la entrada
		cmdline cmdl(options);
		cmdl.parse(argc, argv);
		
		for(size_t i = 0;i<number;i++){
			if(i == 0){
				*oss << "Sensor" << i;
			}else{
				*oss << ',' << "Sensor" << i;
			}
		}
		*oss << endl;
		for(size_t j=0;j<samples;j++){
			for(size_t i=0;i<number;i++){
				if(i == 0){
					if((rand() % 100) >= randNodata){
						*oss << minRange + static_cast <int> (rand()) /( static_cast <int> (RAND_MAX/(maxRange-minRange)));
					}else{
					
					}
				}else{
					if((rand() % 100) >= randNodata){
						*oss << ',' << minRange + static_cast <int> (rand()) /( static_cast <int> (RAND_MAX/(maxRange-minRange)));
					}else{
						*oss << ',';
					}
				}
			}
			*oss << endl;
		}
		
		return 0;
	}
	
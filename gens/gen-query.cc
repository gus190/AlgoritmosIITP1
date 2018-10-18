	#include <cstdlib>
	#include <gens/gen-query.h>
	#include <classes/cmdline.h>
	
	using namespace std;

	#define DEFAULTNUM  3
	#define DEFAULTSAMPLES 10
	#define DEFAULTMAX 60
	#define DEFAULTRAND 0

	static size_t number = 0;
	static size_t samples = 0;
	static int randNodata = 0;
	static size_t maxRange = 0;
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
	static void opt_range(string const &arg){
		if (arg == "-") {	//Por defecto
			maxRange = DEFAULTMAX;
		}
		else {				// si no 
			stringstream argStream;
			argStream.str(arg);
			if(argStream >> maxRange){
				
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
			if(argStream >> randNodata){
				
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
		cout << "program -n [number of sensors] -s [number of samples] -r [max] -nd [porcentage of no sensor id] -o <output file>" << endl;
		exit(0);
	}

	
	// ---- main ---- //
	int main(int argc, char * const argv[]){
		
		// Input parse
		cmdline cmdl(options);
		cmdl.parse(argc, argv);
		
		// Query generation
		for(size_t i = 0;i<samples;i++){
			if(rand() % 100 >= randNodata){ // Random chance of no sensor ID (average)
				*oss << "Sensor" << (rand() % number);
			}
			*oss << << ',';
			size_t min = (rand() % maxRange); // Random min range from 0 to maxrange
			*oss << min << ','; 
			size_t max = (rand() % (maxRange - min)) + min; // Random max range from min to maxrange
			*oss << max;
			*oss << endl;
		}
		
		// Special cases
		*oss << "asfkhagflajsf"<< endl; // invalid input
		*oss << " "	<< endl;			 // space
		*oss << "asfa,0,5000"<< endl;	 // unknown ID
		*oss << "sensor0,676765,5665" << endl;
		*oss << "Sensor0,100,1"<< endl;  // min > max
		*oss << "Sensor0,1,1"<< endl;	 // min = max
		*oss << "Sensor0," << maxRange << maxRange << endl; // min == max in the border
		*oss << "Sensor0," << maxRange-1 << maxRange+1 << endl; // min max in the border
		*oss << "Sensor0," << maxRange << maxRange+1<< endl; // min max in the border
		*oss << ",,"<< endl; 			//no input standar
		
		return 0;
	}
	
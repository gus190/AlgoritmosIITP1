#include <main.h>

using namespace std;

static istream *iss = NULL;		// Input Stream 
static ostream *oss = NULL;		// Output Stream
static istream *idss = NULL;	// Data Input Stream
static fstream ifs; 			// Input File Stream
static fstream ofs;				// Output File Stream
static fstream idfs;			// Data file stream

static option_t options[] = {
	{1, "d", "data", NULL, opt_data, OPT_MANDATORY},
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static void opt_input(string const &arg){
	if (arg == "-") {	//Por defecto
		iss = &cin;		// Entrada cin
	}
	else {				// si no 
		ifs.open(arg.c_str(), ios::in);
		iss = &ifs;		//abro archivo
	}
	// Verificamos que el archivo se halla abierto.
		if (!iss->good()) {
			cerr << "cannot open querry input"
				 << arg
				 << "."
				 << endl;
			exit(2);
		}
	
}

static void opt_data(string const &arg){
	
	idfs.open(arg.c_str(), ios::in);	// archivo mandatorio
	idss = &idfs;
	// Verificamos que el archivo se halla abierto.
	if (!idss->good()) {
		cerr << "cannot open data input"
			 << arg
			 << "."
			 << endl;
		exit(1);
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
	cout << "tp0 -i [inputfile] -o [outputfile] -d [datafile](mandatory)" << endl;
	exit(0);
}

// ---- main ---- //
int main(int argc, char * const argv[]){

	// Input parse
	cmdline cmdl(options);
	cmdl.parse(argc, argv);
	cout << "Input parse complete" << endl;
	
	// Data parse
	SensorNet sensors;
	*idss >> sensors;
	cout << "Data parse complete" << endl;
	
	// Query parse and process
	Query query;
	query.process(*iss,sensors,*oss);
	cout << "Query process complete" << endl;
	
	return 0;
}

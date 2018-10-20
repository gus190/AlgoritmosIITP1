#include <cstdlib>
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

// funcion readData que lee datos del archivo y los almacena en los objetos
/* void readData(istream& input, Array <Sensor> & sensores){
	// variables utilizadas
	string line,token;
	istringstream lineStr;
	Sensor sensorAux;
	
	// parseo de la primera linea (nombres)
	getline(input,line);					//obtengo linea del input
	lineStr.str(line);						// la streameo
	while(getline(lineStr,token,',')){		//obtengo los valuees separados por coma
		sensorAux = token;					//asigno el nombre al objeto sensor auxiliar
		sensores.push_back(sensorAux);		//pusheo al array el nuevo objeto
	}
	
	// parseo del resto de las lineas (temperaturas)
	while(getline(input,line)){	//mientras hayan lineas
		int count = 0;
		lineStr.clear();
		lineStr.str(line);
		while(getline(lineStr,token,',')){	// dato entre comas o /n
			if (!token.empty()){
				sensores[count] + atof(token.c_str()); // pusheo el dato
			}else{
				Data d;
				sensores[count] + d;
			}
			count++;
		}
	}
} */

/* void querryData(istream& input, Array <Sensor> & sensores,ostream& output){
	//variables
	string line,token;
	int pos;
	size_t min,max;
	char ch;
	bool good = false;
	
	// Leo el querry linea por linea y hago las consultas
	while(getline(input,line)){
		Sensor sAux;
		istringstream lineStr;
		lineStr.str(line);
		// leo primer variable (nombre)
		getline(lineStr,token,',');
		// leo minimo y maximo, checkeando si esta bien
		if(lineStr >> min &&
			lineStr >> ch && ch == ',' &&
			lineStr >> max){
				good = true;	
		} else {
			good = false;
		}
		// si no hay nombre en la consulta, se hace un promedio de los sensores
		if(good && token.empty()){		
			for (size_t i = 0; i < sensores[0].size(); i++){
				Data value;
				int count=0;
				for(size_t j=0;j<sensores.size();j++){
					if(sensores[j].getData(i).exist()){
						value = sensores[j].getData(i) + value;
						count++;
					}
				}
					value = value/count; 
					sAux + value;	
			}
			sAux.querry(output,min,max);
		// si hay nombre en la consulta
		}else if(good){
			sAux = token;
			pos = sensores.linear_search(sAux);
			//si no encuentra posicion
			if(pos == -1){
				output << "UNKNOWN ID" << endl;
				continue;
			}
			sensores[pos].querry(output, min, max);
		//si hay mal parseo
		}else{
			output << "BAD QUERRY" << endl;
		}
	}
} */

// ---- main ---- //
int main(int argc, char * const argv[]){

	// Input parse
	Cmdline cmdl(options);
	cmdl.parse(argc, argv);
	
	// Data parse
	SensorNet sensors();
	sensors << *idss;
	
	// Query parse and process
	Query query;
	query.process(*iss,sensors,*oss);
	
	
	return 0;
}

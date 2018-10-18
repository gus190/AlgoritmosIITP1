#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <classes/Cmdline.h>

using namespace std;

static void opt_number(string const &);
static void opt_samples(string const &);
static void opt_range(string const &);
static void opt_output(string const &);
static void opt_nodata(string const &);
static void opt_help(string const &);
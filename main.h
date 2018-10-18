#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <classes/Cmdline.h>
#include <classes/Range.h>
#include <classes/Package.h>
#include <classes/Array.h>
#include <classes/SegmentTree.h>
#include <classes/Sensor.h>

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_data(string const &);
static void opt_help(string const &);
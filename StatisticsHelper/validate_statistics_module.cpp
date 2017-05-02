//
// Created by Pirmin Schmid on 23.04.17.
//

#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>

#include "utils/StatisticsHelper.h"

using namespace std;
using namespace toolbox;

/**
 * This test suite is adapted from the validation tests for benchmarkC
 * https://github.com/pirminschmid/benchmarkC
 * (has MIT license)
 *
 * and some additional corner case tests.
 *
 * v1.0 2017-04-23 Pirmin Schmid
 */


//--- data set 1 - random values, normal distribution --------------------------
//    generator settings: mean = 1'000'000, sd = 100'000, n = 101
//    use a denominator = 1

static const vector<double> data1 = {
		996741,
		1042651,
		757072,
		1078921,
		919322,
		1038198,
		935586,
		837703,
		874305,
		1058255,
		1060602,
		945072,
		811022,
		984377,
		1009921,
		917695,
		1111104,
		1160768,
		986824,
		1088920,
		955952,
		1196703,
		1018870,
		916257,
		907630,
		1040466,
		1069042,
		918638,
		997844,
		1052655,
		855711,
		1074501,
		1072637,
		898349,
		997692,
		1155499,
		1040669,
		1017868,
		1226173,
		891234,
		1067356,
		1043179,
		872030,
		1047991,
		1066673,
		974536,
		1073497,
		1218791,
		964708,
		1055225,
		1089842,
		995410,
		740516,
		1011374,
		1024122,
		1121446,
		919776,
		1069853,
		1045024,
		1007487,
		1023407,
		1163792,
		959350,
		1049170,
		1094754,
		938595,
		942773,
		885211,
		811808,
		952822,
		968111,
		1122784,
		1149973,
		1114145,
		1110608,
		792954,
		1008669,
		925160,
		1018784,
		970606,
		1114745,
		1138732,
		1017553,
		965294,
		1094759,
		989196,
		1035290,
		952470,
		857766,
		910864,
		819845,
		991630,
		878751,
		766477,
		963790,
		1084276,
		1002248,
		1155900,
		1012169,
		1090662,
		1057084
};

static double denominator1 = 1.0;

// see PDF file with reference values
static StatisticsHelper::Summary reference1 = {
		.count       =     101,

		/* robust */
		.min         =  740516.0000,
		.q1          =  937842.7500,
		.median      = 1011374.0000,
		.q3          = 1070549.0000,
		.max         = 1226173.0000,

		/* parametric (assume normal distribution) */
		.mean        = 1002289.7228,
		.sd          =  102380.3052,
		.sem         =   10187.2211,
		.ci95_a      =  982078.5662,
		.ci95_b      = 1022500.8793
};


//--- data set 2 - random values, normal distribution --------------------------
//    generator settings: mean = 1'000'000, sd = 300'000, n = 31
//    use a denominator = 32

static const vector<double> data2 = {
		816470,
		1238486,
		966711,
		977648,
		606973,
		1183548,
		742549,
		918595,
		1283970,
		1100167,
		960535,
		982734,
		1119218,
		1028509,
		1014213,
		1255995,
		783184,
		715697,
		1176160,
		847037,
		603338,
		1057617,
		327444,
		931031,
		914510,
		1036230,
		1120600,
		894320,
		1219739,
		962894,
		702271
};

static double denominator2 = 32.0;

// see PDF file with reference values
static StatisticsHelper::Summary reference2 = {
		.count       =      31,

		/* robust */
		.min         =   10232.6250,
		.q1          =   25753.4922,
		.median      =   30209.7188,
		.q3          =   34826.7266,
		.max         =   40124.0625,

		/* parametric (assume normal distribution) */
		.mean        =   29726.2026,
		.sd          =    6811.9025,
		.sem         =    1223.4538,
		.ci95_a      =   27227.5766,
		.ci95_b      =   32224.8286
};

//--- data set 3 - a corner case -----------------------------------------------
//    use a denominator = 1

static const vector<double> data3 = {
		1,
		2,
		3,
		4
};

static double denominator3 = 1.0;

// see PDF file with reference values
static StatisticsHelper::Summary reference3 = {
		.count       =       4,

		/* robust */
		.min         =       1.0000,
		.q1          =       1.5000,
		.median      =       2.5000,
		.q3          =       3.5000,
		.max         =       4.0000,

		/* parametric (assume normal distribution) */
		.mean        =       2.5000,
		.sd          =       1.2910,
		.sem         =       0.6455,
		.ci95_a      =       0.4457,
		.ci95_b      =       4.5543
};


//--- additional corner cases --------------------------------------------------

static const vector<double> cc0 = {};

static double denominator_cc0 = 1.0;

static StatisticsHelper::Summary ref_cc0 = {
		.count       =       0,

		/* robust */
		.min         =       0.0000,
		.q1          =       0.0000,
		.median      =       0.0000,
		.q3          =       0.0000,
		.max         =       0.0000,

		/* parametric (assume normal distribution) */
		.mean        =       0.0000,
		.sd          =       0.0000,
		.sem         =       0.0000,
		.ci95_a      =       0.0000,
		.ci95_b      =       0.0000
};

static const vector<double> cc1 = {
		3.1415
};

static double denominator_cc1 = 1.0;

// note: q1 and q3 are not really calculated and do not make sense with this small number
// (need n=4 for true calculation)
// however with given monotonous order min <= q1 <= median <= q3 <= max,
// q1 and q3 are clear, as much as min, median, and max are clear, too.
// however, they are not printed in the print function on purpose.
// It just does not make sense.
static StatisticsHelper::Summary ref_cc1 = {
		.count       =       1,

		/* robust */
		.min         =       3.1415,
		.q1          =       3.1415,
		.median      =       3.1415,
		.q3          =       3.1415,
		.max         =       3.1415,

		/* parametric (assume normal distribution) */
		.mean        =       3.1415,
		.sd          =       0.0000,
		.sem         =       0.0000,
		.ci95_a      =       0.0000,
		.ci95_b      =       0.0000
};


static const vector<double> cc2 = {
		1.0,
		2.0
};

static double denominator_cc2 = 1.0;

// note: q1 and q3 are not really calculated and do not make sense with this small number
// (need n=4 for true calculation)
// however with given monotonous order min <= q1 <= median <= q3 <= max,
// q1 == min and q3 == max are returned (as in reference statistics program.
// however, they are not printed in the print function on purpose
// It just does not make sense.
static StatisticsHelper::Summary ref_cc2 = {
		.count       =       2,

		/* robust */
		.min         =       1.0000,
		.q1          =       1.0000,
		.median      =       1.5000,
		.q3          =       2.0000,
		.max         =       2.0000,

		/* parametric (assume normal distribution) */
		.mean        =       1.5000,
		.sd          =       0.7071,
		.sem         =       0.5000,
		.ci95_a      =      -4.8531,
		.ci95_b      =       7.8531
};


static const vector<double> cc3 = {
		1.0,
		2.0,
		3.0
};

static double denominator_cc3 = 1.0;

// note: q1 and q3 are not really calculated and do not make sense with this small number
// (need n=4 for true calculation)
// however with given monotonous order min <= q1 <= median <= q3 <= max,
// q1 == min and q3 == max are returned (as in reference statistics program.
// however, they are not printed in the print function on purpose
// It just does not make sense.
static StatisticsHelper::Summary ref_cc3 = {
		.count       =       3,

		/* robust */
		.min         =       1.0000,
		.q1          =       1.2500,
		.median      =       2.0000,
		.q3          =       2.7500,
		.max         =       3.0000,

		/* parametric (assume normal distribution) */
		.mean        =       2.0000,
		.sd          =       1.0000,
		.sem         =       0.5774,
		.ci95_a      =      -0.4841,
		.ci95_b      =       4.4841
};
//--- compare data -------------------------------------------------------------

// narrow relative tolerance 0.00001 (check for 0.001 % difference)
// arithmetics should work nicely
static constexpr double kRelativeTolerance_narrow = 0.00001;

// wide relative tolerance 0.001 (check for 0.1 % difference)
// see potential difference in Student t values (rounding in table)
// and also only 4 significant digits in reference
static constexpr double kRelativeTolerance_wide = 0.001;

static void printDouble(const string &title, double value, double reference, double rtol) {
	string ok_str;
	if (fabs(value - reference) <= fabs(rtol * reference)) {
		ok_str = "  OK  ";
	} else {
		ok_str = " WRONG";
	}

	cout << fixed << setprecision(4)
		 << "val = " << value << " ref = " << reference
		 << ok_str
		 << scientific
		 << "(rtol = " << rtol << ") :: ";
	// gcc 4.9 does not support defaultfloat; thus this workaround by Martin Bonner on
	// http://stackoverflow.com/questions/35173482/mingw-do-not-support-stddefaultfloat-how-to-lead-with-it?answertab=votes#tab-top
	cout.unsetf(std::ios_base::floatfield);
	cout << setprecision(15)
		 << title << endl;
}

static void printInt(const string &title, StatisticsHelper::count_type value, StatisticsHelper::count_type reference) {
	string ok_str;
	if (value == reference) {
		ok_str = "  OK  ";
	} else {
		ok_str = " WRONG";
	}

	// gcc 4.9 does not support defaultfloat; thus this workaround by Martin Bonner on
	// http://stackoverflow.com/questions/35173482/mingw-do-not-support-stddefaultfloat-how-to-lead-with-it?answertab=votes#tab-top
	cout.unsetf(std::ios_base::floatfield);
	cout << setprecision(15)
		 << "val = " << value << " ref = " << reference
		 << ok_str
		 << " :: "
		 << title << endl;
}

static void runComparison(const string &title, const vector<double> &values, double denominator, const StatisticsHelper::Summary &ref) {
	cout << endl << "Running test: " << title << endl;

	// the division by denominator is a residual from the original version in benchmarkC
	// however, using ratios of integers is also a convenient way to safely store floating point numbers
	vector<double> adj_values;
	adj_values.reserve(values.size());
	for (double v : values) {
		adj_values.push_back(v / denominator);
	}

	// gcc 4.9 does not support defaultfloat; thus this workaround by Martin Bonner on
	// http://stackoverflow.com/questions/35173482/mingw-do-not-support-stddefaultfloat-how-to-lead-with-it?answertab=votes#tab-top
	cout.unsetf(std::ios_base::floatfield);
	cout << setprecision(15);

	StatisticsHelper::Summary stat = StatisticsHelper::calcSummary(adj_values);
	StatisticsHelper::printSummary(&cout, "Results", stat);

	// actual comparison
	cout << endl << "Comparison:" << endl;
	printInt("count", stat.count, ref.count);
	cout << "robust" << endl;
	printDouble("min", stat.min, ref.min, kRelativeTolerance_narrow);
	printDouble("q1", stat.q1, ref.q1, kRelativeTolerance_narrow);
	printDouble("median", stat.median, ref.median, kRelativeTolerance_narrow);
	printDouble("q3", stat.q3, ref.q3, kRelativeTolerance_narrow);
	printDouble("max", stat.max, ref.max, kRelativeTolerance_narrow);
	cout << "parametric" << endl;
	printDouble("mean", stat.mean, ref.mean, kRelativeTolerance_narrow);
	printDouble("sd", stat.sd, ref.sd, kRelativeTolerance_narrow);
	printDouble("sem (wider RTOL)", stat.sem, ref.sem, kRelativeTolerance_wide);
	printDouble("ci95_a (wider RTOL)", stat.ci95_a, ref.ci95_a, kRelativeTolerance_wide);
	printDouble("ci95_b (wider RTOL)", stat.ci95_b, ref.ci95_b, kRelativeTolerance_wide);
}

//--- main ---------------------------------------------------------------------

int main() {
	cout << "Validation of the statistics module by comparison of results with values of a professional statistics software" << endl;
	cout << "and also testing some additional corner cases" << endl;

	// data from validation test with MedCalc
	runComparison("Test 1.", data1, denominator1, reference1);
	runComparison("Test 2. wider SD, fewer values.", data2, denominator2, reference2);
	runComparison("Test 3. corner case n=4.", data3, denominator3, reference3);

	// additional corner cases
	runComparison("Corner case 0. n=0.", cc0, denominator_cc0, ref_cc0);
	runComparison("Corner case 1. n=1.", cc1, denominator_cc1, ref_cc1);
	runComparison("Corner case 2. n=2.", cc2, denominator_cc2, ref_cc2);
	runComparison("Corner case 3. n=3.", cc3, denominator_cc3, ref_cc3);
	return 0;
}

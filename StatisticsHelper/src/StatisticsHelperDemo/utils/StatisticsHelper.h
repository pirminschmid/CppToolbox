//
// Created by Pirmin Schmid on 13.04.17.
//

#ifndef TOOLBOX_UTILS_STATISTICSHELPER_H_
#define TOOLBOX_UTILS_STATISTICSHELPER_H_

#include <cstdint>
#include <ostream>
#include <vector>

namespace toolbox {

	/**
	 * Some basic descriptive statistics functions.
	 *
	 * This code is based on former code published on
	 * https://github.com/pirminschmid/benchmarkC
	 * (has MIT license)
	 *
	 * References:
	 * - Press et al. Numerical recipes in C++ 2nd ed. Cambridge University Press
	 * - Schoonjans F. https://www.medcalc.org/manual
	 * - Schoonjans F, De Bacquer D, Schmid P. Estimation of population percentiles
	 *   Epidemiology 2011;22(5):750-1
	 *
	 * v1.0 2017-04-23 Pirmin Schmid
	 */

	class StatisticsHelper {
	public:
		typedef uint64_t count_type;

		struct Summary {
			// robust
			count_type count;
			double min;
			double q1;
			double median;
			double q3;
			double max;

			// parametric (assume normal distribution)
			double mean;
			double sd;     // mean +/- sd
			double sem;    // standard error of the mean
			double ci95_a; // 95% confidence interval [a,b] for the mean
			double ci95_b;
		};

		enum SummaryPrintStyle { kFull, kRobust, kParametric };

		static double median(const std::vector<double> &values);

		static double mean(const std::vector<double> &values);

		static Summary calcSummary(const std::vector<double> &values);

		/**
		 * note: the output uses the floating point output settings of the provided std::ostream.
		 * Adjust precision and number output style before calling this method.
		 */
		static void printSummary(std::ostream *out, const std::string &title,
								 const Summary &stat, SummaryPrintStyle style = kFull);


		/**
		 * in case the values are not needed anymore
		 */
		static void calcAndPrintSummary(std::ostream *out, const std::string &title,
										const std::vector<double> &values, SummaryPrintStyle style = kFull);


	private:

		/**
		 *  calculates percentile value as described in https://www.medcalc.org/manual/summary_statistics.php
		 *  see Lentner C (ed). Geigy Scientific Tables, 8th edition, Volume 2. Basel: Ciba-Geigy Limited, 1982
		 *      Schoonjans F, De Bacquer D, Schmid P. Estimation of population percentiles. Epidemiology 2011;22:750-751.
		 *  percentile must be in range (0,1) here and not in (0, 100)
		 *  and 1/n <= percentile <= (n-1)/n
		 *  for n = sorted_values.size()
		 *  i.e. n must be at least 4 for percentiles 0.25 (q1) and 0.75 (q3)
		 *                          2 for percentile 0.5 (median)
		 */
		static double getPercentile(const std::vector<double> &sorted_values, double percentile);

		static constexpr double kPercentileAbsoluteTolerance = 0.001;

		/**
		 *
		 * @param df : degree of freedom
		 * @return
		 */
		static double getTValue(count_type df);

		struct Distr {
			count_type df;
			double t_value;
		};

		// values of t-distribution (two-tailed) for 100*(1-alpha)% = 95% (alpha level 0.05)
		// from https://www.medcalc.org/manual/t-distribution.php

		static constexpr count_type kTableInfinity{1024}; // arbitrary value

		static const std::vector<Distr> t_table_;
	};

}

#endif //TOOLBOX_UTILS_STATISTICSHELPER_H_

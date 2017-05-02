//
// Created by Pirmin Schmid on 13.04.17.
//

#include "StatisticsHelper.h"

#include <cassert>
#include <cmath>
#include <algorithm>
#include <limits>


namespace toolbox {

	double StatisticsHelper::median(const std::vector<double> &values) {
		const unsigned long n = values.size();
		if (n == 0) {
			return 0.0;
		}

		std::vector<double> sorted_values(values);
		std::sort(sorted_values.begin(), sorted_values.end());

		const unsigned long m = n / 2;

		if (n % 2 == 0) {
			return 0.5 * (sorted_values[m - 1] + sorted_values[m]);
		} else {
			return sorted_values[m];
		}
	}

	double StatisticsHelper::mean(const std::vector<double> &values) {
		if (values.size() == 0) {
			return 0.0;
		}

		const double n = static_cast<double>(values.size());

		double sum = 0.0;
		for (double v : values) {
			sum += v;
		}
		return sum / n;
	}

	StatisticsHelper::Summary StatisticsHelper::calcSummary(const std::vector<double> &values) {
		Summary result = {};

		// n
		count_type n = values.size();
		if (n == 0) {
			return result;
		}
		result.count = n;

		// mean, min, max
		double sum = 0.0;
		double min = std::numeric_limits<double>::max();
		double max = 0.0;
		for (double v : values) {
			sum += v;

			if (v < min) {
				min = v;
			}

			if (v > max) {
				max = v;
			}
		}

		const double mean = sum / static_cast<double>(n);
		result.mean = mean;
		result.min = min;
		result.max = max;

		// robust, continued: median and quartiles
		if (1 < n) {
			std::vector<double> sorted_values(values);
			std::sort(sorted_values.begin(), sorted_values.end());
			result.median = getPercentile(sorted_values, 0.5);

			if (2 < n) {
				// just the bare minimum to work
				// of course these quartiles will have large 95% confidence intervals by themselves
				// thus: choose larger n for meaningful results, of course
				result.q1 = getPercentile(sorted_values, 0.25);
				result.q3 = getPercentile(sorted_values, 0.75);
			} else {
				result.q1 = result.min;
				result.q3 = result.max;
			}

		} else {
			result.median = result.min;
			result.q1 = result.min;
			result.q3 = result.max;
		}

		// parametric (assuming normal distribution)
		if (1 < n) {
			// this is just the bare minimum to avoid div/0
			double s2 = 0.0;
			for (double v : values) {
				const double delta = v - mean;
				s2 += delta * delta;
			}

			const double variance_estimate = s2 / static_cast<double>(n - 1);
			const double sd = std::sqrt(variance_estimate);
			result.sd = sd;
			const double sem = sd / std::sqrt(static_cast<double>(n));
			result.sem = sem;

			const double ci95_delta = getTValue(n - 1) * sem;
			result.ci95_a = mean - ci95_delta;
			result.ci95_b = mean + ci95_delta;
		}

		return result;
	}

	void StatisticsHelper::printSummary(std::ostream *out, const std::string &title,
										const Summary &stat, StatisticsHelper::SummaryPrintStyle style) {

		*out << std::endl << title << std::endl;

		bool printRobust = style == kFull || style == kRobust;
		bool printParametric = style == kFull || style == kParametric;

		switch (stat.count) {
			case 0:
				*out << "n = 0" << std::endl;
				return;

			case 1:
				*out << "value =  " << stat.mean
					 << ", n = " << stat.count << std::endl;
				return;

			case 2:
			case 3:
				if (printRobust) {
					*out << "- robust:       "
						 << "median " << stat.median
						 << ", min " << stat.min
						 << ", max " << stat.max
						 << ", n = " << stat.count << std::endl;
				}
				break;

			default:
				if (printRobust) {
					*out << "- robust:       "
						 << "median " << stat.median
						 << ", IQR [" << stat.q1 << ", " << stat.q3
						 << "], min " << stat.min
						 << ", max " << stat.max
						 << ", n=" << stat.count << std::endl;
				}

		}

		if (printParametric) {
			*out << "- normal dist.: "
				 << "mean " << stat.mean
				 << ", SD " << stat.sd
				 << ", 95% CI for the mean [" << stat.ci95_a << ", " << stat.ci95_b
				 << "], n = " << stat.count << std::endl;
		}
	}

	void StatisticsHelper::calcAndPrintSummary(std::ostream *out, const std::string &title,
											   const std::vector<double> &values,
											   StatisticsHelper::SummaryPrintStyle style) {

		printSummary(out, title, calcSummary(values), style);
	}


	//--- private helper functions ---------------------------------------------

	double StatisticsHelper::getPercentile(const std::vector<double> &sorted_values, double percentile) {
		const double n = static_cast<double>(sorted_values.size());

		const double r_p = 0.5 + percentile * n;
		const double r_floor = std::floor(r_p);
		const double r_frac = r_p - r_floor; // in range [0, 1), also == abs(f_floor - r_p)

		if (r_frac < kPercentileAbsoluteTolerance) {
			// integer number: use (r_floor - 1) as array index and return value
			const count_type r_index = static_cast<count_type>(r_floor) - 1;
			return sorted_values[r_index];
		} else {
			// use linear interpolation for fractional part
			// benefits and limitations -> see mentioned paper
			const count_type r_index = static_cast<count_type>(r_floor) - 1;
			const count_type r_index2 = r_index + 1;
			double result = (1.0 - r_frac) * sorted_values[r_index]; // the closer to 0.0, the more weight
			result += r_frac * sorted_values[r_index2];              // the closer to 1.0, the more weight
			return result;
		}
	}

	double StatisticsHelper::getTValue(count_type df) {
		if (df < 1) {
			return -1.0;
		}

		for (const auto &item : t_table_) {
			if (df >= item.df) {
				return item.t_value;
			}
		}

		// will not happen
		return -1.0;
	}


	const std::vector<StatisticsHelper::Distr> StatisticsHelper::t_table_ = {
			{StatisticsHelper::kTableInfinity, 1.960},
			{500, 1.965},
			{300, 1.968},
			{200, 1.972},
			{150, 1.976},
			{120, 1.980},
			{100, 1.984},
			{90, 1.987},
			{80, 1.990},
			{70, 1.994},
			{60, 2.000},
			{50, 2.009},
			{48, 2.011},
			{46, 2.013},
			{44, 2.015},
			{42, 2.018},
			{40, 2.021},
			{39, 2.023},
			{38, 2.024},
			{37, 2.026},
			{36, 2.028},
			{35, 2.030},
			{34, 2.032},
			{33, 2.035},
			{32, 2.037},
			{31, 2.040},
			{30, 2.042},
			{29, 2.045},
			{28, 2.048},
			{27, 2.052},
			{26, 2.056},
			{25, 2.060},
			{24, 2.064},
			{23, 2.069},
			{22, 2.074},
			{21, 2.080},
			{20, 2.086},
			{19, 2.093},
			{18, 2.101},
			{17, 2.110},
			{16, 2.120},
			{15, 2.131},
			{14, 2.145},
			{13, 2.160},
			{12, 2.179},
			{11, 2.201},
			{10, 2.228},
			{9, 2.262},
			{8, 2.306},
			{7, 2.365},
			{6, 2.447},
			{5, 2.571},
			{4, 2.776},
			{3, 3.182},
			{2, 4.303},
			{1, 12.706}
	};

}

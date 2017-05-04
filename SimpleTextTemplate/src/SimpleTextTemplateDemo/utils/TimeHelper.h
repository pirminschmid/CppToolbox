//
// Created by Pirmin Schmid on 22.04.17.
//

#ifndef TOOLBOX_UTILS_TIMEHELPER_H_
#define TOOLBOX_UTILS_TIMEHELPER_H_

#include <chrono>

/**
 * Basically a convenience wrapper for chrono of the C++ standard library.
 */

namespace toolbox {

	class TimeHelper {
	public:

		typedef std::chrono::high_resolution_clock clock_type;
		typedef std::chrono::time_point<clock_type> time_point_type;
		typedef std::chrono::duration<double> seconds_type;

		static time_point_type now();

		static double seconds(const time_point_type &start, const time_point_type &end);

	};

}

#endif //TOOLBOX_UTILS_TIMEHELPER_H_

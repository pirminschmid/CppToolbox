//
// Created by Pirmin Schmid on 22.04.17.
//

#include "TimeHelper.h"

namespace toolbox {

	TimeHelper::time_point_type TimeHelper::now() {
		return clock_type::now();
	}

	double TimeHelper::seconds(const TimeHelper::time_point_type &start,
							   const TimeHelper::time_point_type &end) {

		return seconds_type(end - start).count();
	}

}

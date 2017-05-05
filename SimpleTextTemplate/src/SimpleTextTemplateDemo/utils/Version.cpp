//
// Created by Pirmin Schmid on 13.04.17.
//

#include "Version.h"

namespace toolbox {

	void Version::print(std::ostream *out) {
		*out << name_ << " v" << major_ << "." << minor_ << "." << patch_ << " (" << date_ << ") " << std::endl;
	}

}

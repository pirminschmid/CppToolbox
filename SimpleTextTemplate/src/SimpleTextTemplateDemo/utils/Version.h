//
// Created by Pirmin Schmid on 13.04.17.
//

#ifndef TOOLBOX_UTILS_VERSION_H_
#define TOOLBOX_UTILS_VERSION_H_

#include <ostream>
#include <string>

namespace toolbox {

	class Version {
	public:
		Version(const std::string &name, int major, int minor, int patch, const std::string &date) :
				name_(name), major_(major), minor_(minor), patch_(patch), date_(date) {}

		void print(std::ostream *out);

	private:
		std::string name_;
		int major_;
		int minor_;
		int patch_;
		std::string date_;
	};

}

#endif //TOOLBOX_UTILS_VERSION_H_

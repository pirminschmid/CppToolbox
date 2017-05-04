//
// Created by Pirmin Schmid on 12.04.17.
//

#include <functional>
#include <memory>
#include <string>
#include <iostream>

#include "utils/LinkedMap.h"

using namespace std;
using namespace toolbox;

class Dataset {
public:

	Dataset(const string &name, bool keeper) : name_(name), keeper_(keeper) {}

	Dataset(int i, bool keeper) : name_(string("Dataset " + to_string(i))), keeper_(keeper) {}

	const string &getName() const { return name_; }

	bool isKeeper() const { return keeper_; }

private:
	string name_;
	bool keeper_;
};


using lm_type = LinkedMap<string, unique_ptr<Dataset>>;


/**
 *  This program is just show-casing some basic features of the LinkedMap class and
 *  does not really make much sense, of course.
 */
int main(int argc, char *argv[]) {
	cout << endl << "Sample program for LinkedMap implementation. Map capacity 15." << endl;

	 lm_type lm(15, false);

	// add some elements
	cout << endl << "Adding 15 elements 0-14; even numbered datasets are labeled 'keepers' and will not be replaced ";
	for (int i = 0; i < 15; ++i) {
		unique_ptr<Dataset> d = make_unique<Dataset>(i, i % 2 == 0);
		lm.add(d->getName(), move(d));
	}
	lm.printList(&cout);

	// replace some using a predicate indicating whether it is ok to replace the item
	cout << endl << endl << "Replacing 30 elements 100-129; no keepers. Map size remains constant.";
	auto predicate = [](const unique_ptr<Dataset> &d) -> bool {
		return !d->isKeeper();
	};

	for (int i = 100; i < 130; ++i) {
		unique_ptr<Dataset> d = make_unique<Dataset>(i, false);
		lm_type::ID_type id = lm.findFirstWithPredicate(predicate, false, 1);
		if (id == lm_type::kNone) {
			lm.add(d->getName(), move(d));
		} else {
			lm.replace(id, d->getName(), move(d));
		}
	}
	lm.printList(&cout);

	cout << endl << endl << "test some refreshs: ";
	cout << "refresh the LRU" << endl;
	lm.refreshWithId(lm.getLruId());
	lm.printList(&cout);

	cout << endl;
	cout << "refresh the MRU (should stay the same)";
	lm.refreshWithId(lm.getMruId());
	lm.printList(&cout);
	return 0;
}

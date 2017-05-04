//
// Created by Pirmin Schmid on 03.05.17.
//

#include <iostream>

#include "utils/TextTemplate.h"
#include "utils/KeyValueStore.h"

using namespace std;
using namespace toolbox;

int main() {
	cout << endl << "Small demo program of SimpleTextTemplate" << endl;

	KeyValueStore s;
	s.setString("intro", "Lorem ipsum");
	s.setString("what", "carpe diem");
	s.setString("author1", "Quintus Horatius Flaccus");
	s.setString("author2", "Homer");
	s.setString("outro", "Everything will be all right in the end.\n"
			"If it's not all right, then it's not yet the end.\n"
			"(Sonny, Best Exotic Marigold Hotel, 2011)");

	TextTemplate t1(TextTemplate::kDoubleBracketsStyle);
	t1.readFile("template1.txt");
	cout << "***** Style kDoubleBracketsStyle: before *****" << endl;
	t1.print(&cout);

	t1.substituteWith(s);
	cout << endl << "***** after substitution *****" << endl;
	t1.print(&cout);

	TextTemplate t2(TextTemplate::kDollarSignStyle);
	t2.readFile("template2.txt");
	cout << "***** Style kDollarStyle: before *****" << endl;
	t2.print(&cout);

	t2.substituteWith(s);
	cout << endl << "***** after substitution *****" << endl;
	t2.print(&cout);

	cout << endl << endl;
	return 0;
}

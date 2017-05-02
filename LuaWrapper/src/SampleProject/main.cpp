/**
 * Sample program for LuaWrapper.
 *
 */

#include <iostream>

#include "utils/LuaWrapper.h"

using namespace std;
using namespace lua;

int main(int argc, char *argv[]) {
	cout << "Sample program for LuaWrapper v1.0" << endl << endl;
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <lua script>" << endl;
		cout << "Function: loads a lua script and then calls some functions of this script." << endl;
		exit(1);
	}

	LuaWrapper l;
	if (!l.loadFile(argv[1])) {
		cout << "error while loading lua file " << argv[1] << endl;
		exit(1);
	}

	cout << l.callString2String("hello", "C++ sends Hello");
	cout << endl << endl;

	cout << "n = " << l.getInt("n") << endl;
	l.setInt("n", 99);
	cout << "n again = " << l.getInt("n") << endl << endl;

	cout << "text = " << l.getString("text") << endl;
	l.setString("text", "more specific");
	cout << "text again = " << l.getString("text") << endl << endl;

	cout << "pi = " << l.getDouble("pi") << endl;
	l.setDouble("pi", 3.1415);
	cout << "pi again = " << l.getDouble("pi") << endl << endl;

	// format YYYY-MM-DD HH:MM
	std::string date = "2016-02-22 12:00";
	std::string format = "%Y-%m-%d %H:%M";
	std::string later = l.callStringString2String("add_one_week", date, format);
	cout << "Output after running the function: date " << date << " (YYYY-MM-DD HH:MM) changed to "
		 << later << " (leap year)" << endl << endl;

	date = "2017-02-22 12:00";
	later = l.callStringString2String("add_one_week", date, format);
	cout << "Output after running the function: date " << date << " (YYYY-MM-DD HH:MM) changed to "
		 << later << " (no leap year)" << endl << endl;
	return 0;
}

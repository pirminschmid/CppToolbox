/*------------------------------------------------------------------------------
 * CppToolbox: FileSystemHelper
 * https://github.com/pirminschmid/CppToolbox
 *
 * Copyright (c) 2017, Pirmin Schmid, MIT license
 *----------------------------------------------------------------------------*/

#include <iostream>

#include "toolbox/FileSystemHelper.h"

using namespace std;
using namespace toolbox;


int main(int argc, char *argv[]) {
	cout << "Sample program: recursive file listing." << endl << endl;
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <path>" << endl;
		exit(1);
	}

	cout << "given path: " << argv[1] << endl;

	int count = 0;
	auto print = [&count](const std::string &name,
					const std::string &rel_path,
					const std::string &full_path) {
		++count;
		cout << "file " << count << ": " << name << ", path: " << full_path << endl;
	};

	FileSystemHelper::readDir(argv[1], print, true);


	cout << endl << "Check getDirname() to keep input string constant:" << endl;
	std::string path = "/path/to/file.txt";
	cout << "- before: " << path << endl;
	cout << "- path:   " << FileSystemHelper::getDirname(path) << endl;
	cout << "- after:  " << path << endl;

	cout << endl << "Basename of 'file.txt': '" << FileSystemHelper::getBasename("file.txt") << "'" << endl;
	cout << "Path (dirname) of 'file.txt': '" << FileSystemHelper::getDirname("file.txt") << "'" << endl;

	cout << endl << "Basename of empty string: '" << FileSystemHelper::getBasename("") << "'" << endl;
	cout << "Path (dirname) of empty string: '" << FileSystemHelper::getDirname("") << "'" << endl;

	return 0;
}

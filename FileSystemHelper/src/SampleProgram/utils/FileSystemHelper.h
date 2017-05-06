//
// Created by Pirmin Schmid on 13.04.17.
//

#ifndef TOOLBOX_UTILS_FILESYSTEMHELPER_H_
#define TOOLBOX_UTILS_FILESYSTEMHELPER_H_

#include <functional>
#include <string>

namespace toolbox {

	/**
	 * some convenience file system methods. Limited to POSIX file systems at the moment.
	 * Prefer TS Filesystem that comes with C++17 if working with C++17.
	 */
	class FileSystemHelper {
	public:

		typedef std::function<bool(const std::string &name)> predicate_type;

		/**
		 * default predicate function
		 * @param name
		 * @return true for all names
		 */
		static bool acceptAll(const std::string &name);


		/**
		 * arguments: name, relative path from given path, full path including given path
		 * note: full path is based on given input path. No additional absolute path resolution!
		 */
		typedef std::function<void(const std::string &name,
								   const std::string &rel_path,
								   const std::string &full_path)> handle_file_type;

		/**
		 * @param path
		 * @param callback
		 * @param include_sub_dirs
		 * @param accept_function  predicate to select files for inclusion
		 */
		static void readDir(const std::string &path,
							handle_file_type callback,
							bool include_sub_dirs,
							predicate_type accept_function = FileSystemHelper::acceptAll);


		/**
		 * A simple test for file existence.
		 *
		 * @param path
		 * @return true/false
		 */
		static bool fileExists(const std::string &path);


		/**
		 * removes a file in filesystem
		 * @param path
		 */
		static void rmFile(const std::string &path);


		/**
		 * @return file basename of path
		 */
		static std::string getBasename(const std::string &path);


		/**
 		 * @return folder part of path
 		 */
		static std::string getDirname(const std::string &path);

	private:
		static void readDirRecursive(const std::string &path,
							handle_file_type callback,
							bool include_sub_dirs,
							predicate_type accept_function,
							const std::string &sub_dir);
	};

}

#endif //TOOLBOX_UTILS_FILESYSTEMHELPER_H_

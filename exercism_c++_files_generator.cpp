#include <ctime>
#include <filesystem>
#include <fstream>
// #include <iostream>
#include <sstream>
#include <string>


/**
 * Returns the current date in the format "YYYY-MM-DD".
 *
 * @return The current date.
 */
std::string get_current_date() {
	std::ostringstream oss;

	std::time_t now = std::time(0);
	std::tm* time_info = std::localtime(&now);

	oss << std::put_time(time_info, "%Y-%m-%d");

	return oss.str();
}

/**
 * Creates a file with the given file name, content, and path.
 *
 * @param file_name The name of the file to be created.
 * @param content The content to be written to the file.
 * @param path The path where the file should be created.
 */
void create_file(const std::string &file_name, const std::string &content, const std::string &path) {
	std::ofstream file(path);
	file << content;
	file.close();
}

/**
 * Deletes all occurrences of a specified character from a given string.
 *
 * @param string The input string.
 * @param character The character to be deleted.
 * @return The resulting string after deleting all occurrences of the specified character.
 */
std::string delete_character(const std::string &string, const char &character) {
	std::string result;

	for (int i = 0; i < (int) string.length(); i++)
		if (string[i] != character)
			result += string[i];

	return result;
}

/**
 * Replaces specified characters in a string with a new character.
 *
 * @param string The input string.
 * @param old_characters The characters to be replaced.
 * @param new_character The new character to replace the old characters with.
 * @return The resulting string after replacing the characters.
 */
std::string replace_character(const std::string &string, std::string old_characters, const char &new_character) {
	std::string result;

	for (int i = 0; i < (int) string.length(); i++) {
		char character = string[i];

		if (old_characters.find(character) == std::string::npos)
			result += character;
		else
			result += new_character;
	}

	return result;
}

/**
 * Converts a string to lowercase.
 *
 * @param string The input string to be converted.
 * @return The converted string in lowercase.
 */
std::string to_lower(const std::string &string) {
	std::string result;

	for (int i = 0; i < (int) string.length(); i++)
		result += tolower(string[i]);

	return result;
}

/**
 * Converts a string to uppercase.
 *
 * @param string The input string to be converted.
 * @return std::string The converted string in uppercase.
 */
std::string to_upper(const std::string &string) {
	std::string result;

	for (int i = 0; i < (int) string.length(); i++)
		result += toupper(string[i]);

	return result;
}

/**
 * Creates a header file for a given exercise.
 *
 * This function generates the content of the header file, including the URL of the exercise,
 * the date, and the include guards. It then creates the file with the specified exercise name
 * and saves it to the provided path.
 *
 * @param exercise_name The name of the exercise.
 * @param date The date of creation.
 * @param path The path where the file will be saved.
 */
void create_header_file(const std::string &exercise_name, const std::string &url, const std::string &date, const std::string &path) {
	std::string include_guards = to_upper(replace_character(exercise_name, " ", '_')) + "_H";

	std::string content =
		url + " DATE: " + date + "\n\n"
		"#ifndef " + include_guards + "\n"
		"#define " + include_guards + "\n\n\n"
		"namespace " + exercise_name + " {\n\n"
		"}\n\n#endif\n";

	create_file(exercise_name, content, path + '\\' + exercise_name + ".h");
}

/**
 * Creates a cpp file for a given exercise.
 *
 * @param exercise_name The name of the exercise.
 * @param date The date of creation.
 * @param path The path where the file will be created.
 */
void create_cpp_file(const std::string &exercise_name, const std::string url, const std::string &date, const std::string &path) {
	std::string content =
		url + " DATE: " + date + "\n\n"
		"#include \"" + exercise_name + ".h\"\n\n";

	create_file(exercise_name, content, path + '\\' + exercise_name + ".cpp");
}

/**
 * Creates exercise files for a given exercise number and name.
 *
 * @param exercise_number The number of the exercise.
 * @param exercise_name The name of the exercise.
 */
void create_exercise_files(const int &exercise_number, const std::string &exercise_name) {
	std::string folder_name = replace_character(exercise_name, " ", '_');
	std::string folder_path = "G:/programming/personal/Exercism/C++/" + std::to_string(exercise_number) + '-' + folder_name;

	std::string url = "// URL: https://exercism.org/tracks/cpp/exercises/" + delete_character(to_lower(replace_character(exercise_name, " ", '-')), '\'');
	std::string current_date = get_current_date();

	std::string files_name = delete_character(to_lower(replace_character(exercise_name, " -",'_')), '\'');

	// std::cout << "folder name: " << folder_name << '\n';
	// std::cout << "folder path: " << folder_path << '\n';
	// std::cout << "url: " << url << '\n';
	// std::cout << "files name: " << files_name << '\n';

	std::filesystem::create_directory(folder_path);
	create_header_file(files_name, url, current_date, folder_path);
	create_cpp_file(files_name, url, current_date, folder_path);
}

int main(int argc, char* argv[]) {
	int exercise_number = std::stoi(argv[1]);
	std::string exercise_name = argv[2];

	create_exercise_files(exercise_number, exercise_name);

	return 0;
}

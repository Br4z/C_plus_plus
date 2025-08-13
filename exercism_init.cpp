#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <cctype>


namespace fs = std::filesystem;


/**
 * Returns the current date in the format "YYYY-MM-DD".
 *
 * @return the current date.
 * @note Requires C++20 version.
 */
std::string get_current_date() {
	const auto now = std::chrono::system_clock::now();
	return std::format("{:%Y-%m-%d}", now);
}

/**
 * Creates a file with the given file path and content.
 *
 * @param file_path The path of the file to be created.
 * @param content The content to be written to the file.
 * @note It overwrites the file if it already exists.
 */
void create_file(const fs::path &file_path, const std::string &content) {
	if (std::ofstream file(file_path); file)
		file << content;
	else
		std::cerr << "Error: Could not open file for writing: " << file_path << '\n';
}

/**
 * Replaces specified characters in a string with a new character.
 *
 * @param input The input string.
 * @param old_characters The characters to be replaced.
 * @param new_character The new character to replace the old characters with.
 * @return the resulting string after replacing the characters.
 */
std::string replace_characters(std::string_view input, std::string_view old_chars, char new_char) {
	std::string result(input);
	std::ranges::for_each(result, [&](char &c) {
		if (old_chars.find(c) != std::string_view::npos)
			c = new_char;
	});
	return result;
}

/**
 * Converts a string to lowercase.
 *
 * @param input The input string to be converted.
 * @return the converted string in lowercase.
 */
std::string to_lower(std::string_view input) {
	std::string result(input);
	std::transform(result.begin(), result.end(), result.begin(),
					[](unsigned char c){ return std::tolower(c); });
	return result;
}

/**
 * Creates a header file for a given exercise.
 *
 * This function generates the content of the header file, including the URL of the exercise,
 * the date, and the include guards. It then creates the file with the specified exercise name
 * and saves it to the provided path.
 *
 * @param exercise_name_formatted The formatted name of the exercise.
 * @param url The Exercism URL of the exercise.
 * @param dir_path The path where the file will be saved.
 */
void create_header_file(const std::string &exercise_name_formatted, const std::string &url, const fs::path &dir_path) {
	std::string include_guards = replace_characters(exercise_name_formatted, "-", '_');
	std::transform(include_guards.begin(), include_guards.end(), include_guards.begin(), ::toupper);
	include_guards += "_H";

	std::string content =
		url + " DATE: " + get_current_date() + "\n\n"
		"#ifndef " + include_guards + "\n"
		"#define " + include_guards + "\n\n\n"
		"namespace " + replace_characters(exercise_name_formatted, "-", '_') + " {\n\n"
		"}\n\n#endif\n";

	create_file(dir_path / (exercise_name_formatted + ".h"), content);
}

/**
 * Creates a cpp file for a given exercise.
 *
 * @param exercise_name_formatted The formatted name of the exercise.
 * @param url The Exercism URL of the exercise.
 * @param dir_path The path where the file will be saved.
 */
void create_cpp_file(const std::string &exercise_name_formatted, const std::string &url, const fs::path &dir_path) {
	std::string content =
		url + " DATE: " + get_current_date() + "\n\n"
		"#include \"" + exercise_name_formatted + ".h\"\n\n";

	create_file(dir_path / (exercise_name_formatted + ".cpp"), content);
}

/**
 * Creates exercise files for a given exercise number and name.
 *
 * @param number The number of the exercise.
 * @param name The name of the exercise.
 * @param base_path The folder path where you want to create the exercise files.
 */
void create_exercise_files(int number, const std::string &name, const fs::path &base_path) {
	std::string formatted_name = to_lower(name);
	formatted_name.erase(std::remove(formatted_name.begin(), formatted_name.end(), '\''),
							formatted_name.end());

	std::string file_name_base = replace_characters(formatted_name, " ", '_');
	std::string url_slug = replace_characters(formatted_name, " ", '-');

	fs::path dir_path = base_path / (std::to_string(number) + "-" + file_name_base);
	std::string url = "// URL: https://exercism.org/tracks/cpp/exercises/" + url_slug;

	try {
		fs::create_directory(dir_path);
		std::cout << "Created directory: " << dir_path << '\n';
		create_header_file(file_name_base, url, dir_path);
		create_cpp_file(file_name_base, url, dir_path);
		std::cout << "Successfully created boilerplate files." << '\n';
	} catch (const fs::filesystem_error &e) {
		std::cerr << "Filesystem error: " << e.what() << '\n';
	}
}


int main(int argc, char* argv[]) {
	if (argc < 4) {
		std::cerr << "Usage: " << argv[0] << " <exercise_number> \"<exercise name>\" <base_path>" << '\n';
		return 1;
	}

	try {
		int exercise_number = std::stoi(argv[1]);
		std::string exercise_name = argv[2];
		fs::path base_path = argv[3];

		if (!fs::is_directory(base_path)) {
			std::cerr << "Error: Provided path is not a valid directory: " << base_path << '\n';
			return 1;
		}

		create_exercise_files(exercise_number, exercise_name, base_path);
	} catch (const std::exception &e) {
		std::cerr << "An error occurred: " << e.what() << '\n';
		return 1;
	}

	return 0;
}

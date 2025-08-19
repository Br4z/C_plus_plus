#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace Tokens {
	constexpr const char* MD_HORIZONTAL_RULE = "---";
	constexpr const char* MD_MATH_DELIMITER = "$$";
	constexpr const char* MD_CODE_DELIMITER = "```";
	constexpr const char* LATEX_ALIGN_BEGIN = "\\begin{align}";
	constexpr const char* LATEX_ALIGN_END = "\\end{align}";
	constexpr const char* YAML_REVIEWED_ON = "reviewed_on:";
}

/* ---------------------------- HELPER FUNCTIONS ---------------------------- */

/**
 * Trims whitespace from the left (start) of a string, in-place.
 *
 * @param s The string to trim.
 * @return a reference to the modified string.
 */
std::string& ltrim(std::string& s) {
	s.erase(0, s.find_first_not_of(" \t\n\r\f\v"));
	return s;
}

/**
 * Trims whitespace from the right (end) of a string, in-place.
 *
 * @param s The string to trim.
 * @return A reference to the modified string.
 */
std::string& rtrim(std::string& s) {
	s.erase(s.find_last_not_of(" \t\n\r\f\v") + 1);
	return s;
}

/**
 * Trims whitespace from both sides of a string and returns a new copy.
 * @param s The string to trim.
 * @return A new string with leading/trailing whitespace removed.
 */
std::string trim(std::string s) {
	return ltrim(rtrim(s));
}

/**
 * Checks if a string contains only whitespace characters.
 * @param s The string to check.
 * @return True if the string is empty or contains only whitespace, false otherwise.
 */
bool is_empty(const std::string& s) {
	return s.find_first_not_of(" \t\n\r\f\v") == std::string::npos;
}

/* -------------------------------------------------------------------------- */

/**
 * Checks if a line is a Markdown list item (ordered or unordered).
 * Also flags the use of '*' for unordered lists as a style violation.
 *
 * @param line The full line to check.
 * @param violations A vector to which violation messages will be added.
 * @return True if the line is a list item, false otherwise.
 */
bool is_list_item(const std::string& trimmed_line, std::vector <std::string>& violations) {
	if (trimmed_line.empty())
		return false;

	// Check for unordered lists made with "*"
	if (trimmed_line.find("* ") == 0) {
		violations.push_back("A unordered list item should be declared with \"-\"");
		return true;
	}

	// Check for unordered lists (-)
	if (trimmed_line.find("- ") == 0)
		return true;

	size_t dot_pos = trimmed_line.find(". ");
	if (dot_pos != std::string::npos || dot_pos > 0) {
		std::string number_part = trimmed_line.substr(0, dot_pos);
		if (!number_part.empty() && std::all_of(number_part.begin(), number_part.end(), [](unsigned char c){ return std::isdigit(c); }))
			return true;
	}

	return false;
}

/* ------------------------------ RULE CHECKERS ----------------------------- */

/**
 * Checks header lines for capitalization and emptiness.
 *
 * @param trimmed_line The trimmed content of the line to check.
 * @param violations A vector to which violation messages will be added.
 */
void check_header(const std::string& trimmed_line, std::vector <std::string>& violations) {
	if (trimmed_line.empty() || trimmed_line[0] != '#')
		return;

	size_t first_char_pos = trimmed_line.find_first_not_of("# ");
	if (first_char_pos == std::string::npos) {
		violations.push_back("Empty header");
		return;
	}

	if (trimmed_line[first_char_pos] == '`' || trimmed_line[first_char_pos] == '$' ||
			std::isdigit(static_cast <unsigned char>(trimmed_line[first_char_pos])))
		return;

	if (!std::isupper(static_cast <unsigned char>(trimmed_line[first_char_pos])))
		violations.push_back("A header should start with an uppercase letter");
}

/**
 * Checks if paragraphs and list items end with a period, a question mark or a colon.
 *
 * @param line The full line to check.
 * @param violations A vector to which violation messages will be added.
 */
void check_punctuation(const std::string& trimmed_line, std::vector <std::string>& violations) {
	// Check if it is empty or a header
	if (trimmed_line.empty() || trimmed_line[0] == '#')
		return;

	char last_char = trimmed_line.back();
	if (last_char != '.' && last_char != '?' && last_char != ':')
		violations.push_back("A line should end with a period, a question mark or colon");
}

/**
 * Checks for required spacing around non-escaped braces in LaTeX math.
 *
 * @param line The full line to check.
 * @param violations A vector to which violation messages will be added.
 */
void check_brace_spacing(const std::string& trimmed_line, std::vector <std::string>& violations) {
	size_t trimmed_line_length = trimmed_line.length();
	int text_brace_level = 0;
	for (size_t i = 0; i < trimmed_line_length; i++) {
		if (i + 5 < trimmed_line_length && trimmed_line.substr(i, 6) == "\\text{") {
			text_brace_level = 1;
			i += 5; // Skip the "\text{" part
			continue;
		}

		if (text_brace_level > 0) {
			if (trimmed_line[i] == '{')
				text_brace_level++;
			else if (trimmed_line[i] == '}')
				text_brace_level--;
			continue;
		}

		if (trimmed_line[i] == '{') {
			// Escaped brace
			if (i > 0 && trimmed_line[i - 1] == '\\')
				continue;

			if (i + 1 >= trimmed_line_length || trimmed_line[i + 1] != ' ')
				violations.push_back("\"{\" is missing a following space");

		} else if (trimmed_line[i] == '}') {
			if (i > 0 && trimmed_line[i - 1] == '\\')
				continue;

			if (i == 0 || trimmed_line[i - 1] != ' ')
				violations.push_back("\"}\" is missing a following space");
		}
	}
}

/**
 * Checks for multiple consecutive spaces in a line.
 *
 * @param line The full line to check.
 * @param violations A vector to which violation messages will be added.
 */
void check_spaces(const std::string& line, std::vector <std::string>& violations) {
	if (line.find("  ") != std::string::npos)
		violations.push_back("multiple spaces in a row");
}

/**
 * Checks formatting rules for lines within a LaTeX align environment.
 *
 * @param line The full line to check.
 * @param violations A vector to which violation messages will be added.
 */
void check_align(const std::string& line, std::vector <std::string>& violations) {
	if (line.find("\t& ") == std::string::npos)
		violations.push_back("invalid align environment item");

	if (line.find("\\\\") != std::string::npos && line.find(" \\\\") == std::string::npos)
		violations.push_back("a space is missing between \"\\\\\" and the align item");
}

/* ---------------------------------- MAIN ---------------------------------- */

/**
 * Main processing function. Reads a file line by line and applies format checks.
 *
 * @param filename The path to the Markdown file to be checked.
 */
void check_markdown_note(const std::string& filename) {
	std::ifstream file(filename);

	if (!file.is_open())
		throw std::runtime_error("Error: could not open file " + filename);

	std::string line;
	int line_number = 0;
	std::string prev_line = "";
	bool math_mode = false;
	bool code_mode = false;
	bool align_mode = false;

	while (std::getline(file, line)) {
		line_number++;
		std::vector <std::string> violations;
		std::string trimmed_line = trim(line);

		if (trimmed_line.find(Tokens::MD_HORIZONTAL_RULE) != std::string::npos ||
			trimmed_line.find(Tokens::YAML_REVIEWED_ON) != std::string::npos ||
			trimmed_line[0] == '!') {
			prev_line = line;
			continue;

		} else if (trimmed_line.find(Tokens::MD_MATH_DELIMITER) != std::string::npos) {
			math_mode = !math_mode;
			prev_line = line;
			continue;
		} else if (trimmed_line.find(Tokens::MD_CODE_DELIMITER) != std::string::npos) {
			code_mode = !code_mode;
			prev_line = line;
			continue;
		}

		bool current_is_empty = is_empty(line);
		bool prev_is_empty = is_empty(prev_line);

		if (math_mode) {
			if (trimmed_line.find(Tokens::LATEX_ALIGN_BEGIN) != std::string::npos) {
				align_mode = true;
				continue;
			} else if (trimmed_line.find(Tokens::LATEX_ALIGN_END) != std::string::npos) {
				align_mode = false;
				continue;
			}

			if (align_mode)
				check_align(line, violations);
			else
				check_spaces(line, violations);

			check_brace_spacing(trimmed_line, violations);
		} else if (!code_mode) {
			if (current_is_empty && prev_is_empty)
				violations.push_back("More than one empty line between elements");

			if (!current_is_empty && !prev_is_empty)
				violations.push_back("Missing empty line between elements");

			check_header(trimmed_line, violations);
			check_punctuation(trimmed_line, violations);
			check_spaces(line, violations);
		} else // Code mode
			check_spaces(line, violations);

		if (!violations.empty()) {
			std::cout << "Line " << line_number << ": " << line << '\n';
			for (const auto& v : violations)
				std::cout << '\t' << v << '\n';
		}

		prev_line = line;
	}
}

// TODO: Markdown tables and LaTex arrays
int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " FILENAME.md" << '\n';
		return 1;
	}

	try {
		std::string filename = argv[1];
		check_markdown_note(filename);
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}

	return 0;
}

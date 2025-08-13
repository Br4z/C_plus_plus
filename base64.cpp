#include <array>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>


static constexpr std::string_view BASE64_CHARS =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


std::string encode_base64(std::string_view input) {
	std::string output;
	int intput_length = input.length();
	output.reserve((intput_length / 3 + 1) * 4);

	int i = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (i < intput_length) {
		char_array_3[0] = input[i++];
		char_array_3[1] = (i < intput_length) ? input[i++] : 0;
		char_array_3[2] = (i < intput_length) ? input[i++] : 0;

		// Combine 3 8-bit into one 24-bit integer
		uint32_t triple = (char_array_3[0] << 16) + (char_array_3[1] << 8) + char_array_3[2];

		// Split the 24-bit integer into four 6-bit chunks
		// The bitwise AND with 0x3F (binary 00111111) isolates the 6 bits
		char_array_4[0] = (triple >> 18);
		char_array_4[1] = (triple >> 12) & 0x3F;
		char_array_4[2] = (triple >> 6) & 0x3F;
		char_array_4[3] = triple & 0x3F;

		for (int j = 0; j < 4; j++)
			output += BASE64_CHARS[char_array_4[j]];
	}

	// Add padding
	int padding_count = intput_length % 3;
	if (padding_count != 0) {
		int output_length = output.length();
		for (int j = 0; j < (3 - padding_count); j++)
			output[output_length - 1 - j] = '=';
	}

	return output;
}

std::string decode_base64(std::string_view input) {
	// Create a reverse lookup table for O(1) decoding
	static std::array <int, 256> lookup_table;
	static bool table_initialized = false;
	if (!table_initialized) {
		for (int i = 0; i < 64; i++)
			lookup_table[BASE64_CHARS[i]] = i;
		table_initialized = true;
	}

	int input_length = input.length();
	std::string output;
	output.reserve(input_length / 4 * 3);

	for (int i = 0; i < input_length; i += 4) {
		uint32_t a = (input[i] == '=') ? 0 : lookup_table[input[i]];
		uint32_t b = (input[i + 1] == '=') ? 0 : lookup_table[input[i + 1]];
		uint32_t c = (input[i + 2] == '=') ? 0 : lookup_table[input[i + 2]];
		uint32_t d = (input[i + 3] == '=') ? 0 : lookup_table[input[i + 3]];

		uint32_t triple = (a << 18) + (b << 12) + (c << 6) + d;

		// Extract the three 8-bit bytes from the 24-bit integer
		// The bitwise AND with 0xFF (binary 11111111) isolates each byte
		output += (triple >> 16);
		if (input [i + 2] != '=')
			output += (triple >> 8) & 0xFF;
		if (input [i + 3] != '=')
				output += triple& 0xFF;
	}

	return output;
}


int main() {
	std::string text_1 = "any carnal pleasure.";
	std::string text_2 = "any carnal pleasure";
	std::string text_3 = "any carnal pleasur";

	std::cout << "Original: " << text_1 << '\n';
	std::cout << "Encoded:  " << encode_base64(text_1) << '\n';
	std::cout << "Decoded:  " << decode_base64(encode_base64(text_1)) << '\n' << '\n';

	std::cout << "Original: " << text_2 << '\n';
	std::cout << "Encoded:  " << encode_base64(text_2) << '\n';
	std::cout << "Decoded:  " << decode_base64(encode_base64(text_2)) << '\n' << '\n';

	std::cout << "Original: " << text_3 << '\n';
	std::cout << "Encoded:  " << encode_base64(text_3) << '\n';
	std::cout << "Decoded:  " << decode_base64(encode_base64(text_3)) << '\n';

	return 0;
}

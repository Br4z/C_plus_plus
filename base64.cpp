#include <iostream>
#include <string>


const std::string BASE64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string encode_base64(std::string input) {
	const int input_length = input.length();
	std::string output = "";

	for (int i = 0; i < input_length; i += 3) { // Blocks of 3 Bytes
		std::string block = input.substr(i, 3);
		int block_length = block.length();
		int block_value = 0;

		for (int j = 0; j < block_length; j++)
			block_value += block[j] << (8 * (2 - j)); // block_value = (input[i] << 16) + (input[i + 1] << 8) + input[i + 2];

		for (int j = 0; j < 4; j++) { // Encode the block into 4 characters
			int index = (block_value >> ((3 - j) * 6)) & 0x3F; // 0x3F = 63 = 111111
			output += BASE64_CHARS[index];
		}
	}

	int output_length = output.length();
	int padding = input_length % 3;

	if (padding)
		for (int i = 0; i < (3 - padding); i++)
			output[output_length - i - 1] = '=';

	return output;
}

std::string decode_base64(std::string input) {
	const int input_length = input.length();
	std::string output = "";

	for (int i = 0; i < input_length - 1; i += 4) {
		std::string block = input.substr(i, 4);
		int block_length = block.length();
		int block_value = 0;

		for (int j = 0; j < block_length; j++)
				if (block[j] != '=')
					block_value += BASE64_CHARS.find(block[j]) << (6 * (3 - j)); // (BASE64_CHARS.find(input[i]) << 18) + (BASE64_CHARS.find(input[i + 1]) << 12) +
						// (BASE64_CHARS.find(input[i + 2]) << 6) + BASE64_CHARS.find(input[i + 3]);
				else
					continue;

		for (int j = 0; j < 3; j++) {
			char byte = (block_value >> ((2 - j) * 8)) & 0xFF; // 0xFF = 255 = 11111111
			output += byte;
		}
	}

	return output;
}


int main() {
	std::string input = " ";

	std::string encoded_input = encode_base64(input);
	std::string decoded_test = decode_base64(encoded_input);


	std::cout << encoded_input << std::endl;
	std::cout << decoded_test << std::endl;
	std::cout << (int) ' ' << std::endl;

	return 0;
}

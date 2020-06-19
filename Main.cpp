#include "AES128Encrypt.h"

int main(int argc, char* argv[])
{

	// filepath passed in on the command line
	std::string src_filepath = argv[1];

	// destination is filepath as the source with a ".enc" filename extension
	std::string enc_filepath = src_filepath.substr(0, src_filepath.find_last_of('.')) + ".enc";
	const char* dst_filepath = enc_filepath.c_str();

	AES128Encrypt AES_Encrypt = AES128Encrypt();

	// 16 bytes taken from the user as hex digits with nothing echoed in the terminal
	unsigned char key[33];

	std::cout << "Please Enter Your 32 Digit Hex Value Key: 0x";
	std::cin >> std::hex >> key;
	key[32] = '\0';

	// precalc all round-keys
	unsigned char key_schedule[176];
	AES_Encrypt.get_key_schedule(key, key_schedule);

	//C: file I/O stuff https://www.programiz.com/c-programming/c-file-input-output
	FILE* dst_fptr = fopen(dst_filepath, "wb");						//open the plaintext file
	FILE* src_fptr = fopen(argv[1], "rb");									//open the new ciphertext


	//Calculations for PKCS5 Padding
	struct stat st;
	stat(argv[1], &st);
	long int size = st.st_size;
	int read = size / 16;
	int padding = size % 16;

	unsigned char buffer[16];		// a buffer of 16 bytes

	//AES 128-bits ECB Encryption
	int c;
	for (int i = 0; i < read; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if ((c = fgetc(src_fptr)) != EOF)
				buffer[j] = c;
		}
		AES_Encrypt.encrypt(buffer, key_schedule);
		fwrite(buffer, sizeof(char), 16, dst_fptr);

	}

	//PKCS5 Padding
	int pad = 16 - padding;
	for (int j = 0; j < padding; j++)
	{
		if ((c = fgetc(src_fptr)) != EOF)
			buffer[j] = c;
	}

	for (int j = 0; j < pad; j++)
	{
		buffer[padding + j] = pad;
	}

	//Encrypting last block with padding
	AES_Encrypt.encrypt(buffer, key_schedule);
	fwrite(buffer, sizeof(char), 16, dst_fptr);

	fclose(src_fptr);
	fclose(dst_fptr);

	std::cout << "Finished AES 128-bit (ECB) Encryption\n";

	return 0;
}
#pragma once
#ifndef AES128ENCRYPT_H
#define AES128ENCRYPT_H
#include <iostream>
#include <iomanip>
#include <sys/stat.h>

class AES128Encrypt
{
public:
	AES128Encrypt() {};
	~AES128Encrypt() {}

	void encrypt(unsigned char plaintext[], unsigned char key_schedule[]);
	void sub_bytes(unsigned char text[]);
	void shift_rows(unsigned char text[]);
	void mixColumns(unsigned char* input);
	void g(unsigned char w3[], unsigned char result[], int round);

	void get_key_schedule(unsigned char* key, unsigned char key_schedule[]);
	int charToHex(char c);

private:

};

#endif
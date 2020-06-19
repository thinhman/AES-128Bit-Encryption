#include "AES128Encrypt.h"
#include "AES AES128 Constants.h"

void AES128Encrypt::encrypt(unsigned char plaintext[], unsigned char key_schedule[])
{
	//Key Addition Layer: k0
	for (int i = 0; i < 16; i++)
	{
		plaintext[i] = plaintext[i] ^ key_schedule[i];
	}

	//AES Round: 1 ~ 9
	for (int round = 1; round < 10; round++)
	{
		sub_bytes(plaintext);		// byte-substitution layer (use sbox map)
		shift_rows(plaintext);		// shiftrow layer
		mixColumns(plaintext);		// shiftcol layer

		//Key Addition Layer
		for (int i = 0; i < 16; i++)
		{
			plaintext[i] = plaintext[i] ^ key_schedule[i + (16 * round)];
		}
	}

	//AES Round: 10
	sub_bytes(plaintext);
	shift_rows(plaintext);

	//Key Addition Layer
	for (int i = 0; i < 16; i++)
	{
		plaintext[i] = plaintext[i] ^ key_schedule[i + (16 * 10)];
	}

}
void AES128Encrypt::sub_bytes(unsigned char text[])
{
	for (int i = 0; i < 16; i++)
	{
		text[i] = sbox[text[i]];
	}
}

void AES128Encrypt::shift_rows(unsigned char text[])
{
	unsigned char temp = text[1];
	unsigned char temp1 = text[13];

	//One position left shift
	text[1] = text[5];
	text[13] = temp;
	temp = text[9];
	text[9] = temp1;
	text[5] = temp;

	//Two position left shift
	temp = text[2];
	text[2] = text[10];
	text[10] = temp;
	temp = text[6];
	text[6] = text[14];
	text[14] = temp;

	//Three position left shift
	temp = text[3];
	temp1 = text[7];
	text[3] = text[15];
	text[7] = temp;
	temp = text[11];
	text[11] = temp1;
	text[15] = temp;

}

void AES128Encrypt::mixColumns(unsigned char* input) {
	unsigned char tmp[16];
	int i;
	for (i = 0; i < 4; ++i) {
		tmp[(i << 2) + 0] = (unsigned char)(mul2[input[(i << 2) + 0]] ^ mul_3[input[(i << 2) + 1]] ^ input[(i << 2) + 2] ^ input[(i << 2) + 3]);
		tmp[(i << 2) + 1] = (unsigned char)(input[(i << 2) + 0] ^ mul2[input[(i << 2) + 1]] ^ mul_3[input[(i << 2) + 2]] ^ input[(i << 2) + 3]);
		tmp[(i << 2) + 2] = (unsigned char)(input[(i << 2) + 0] ^ input[(i << 2) + 1] ^ mul2[input[(i << 2) + 2]] ^ mul_3[input[(i << 2) + 3]]);
		tmp[(i << 2) + 3] = (unsigned char)(mul_3[input[(i << 2) + 0]] ^ input[(i << 2) + 1] ^ input[(i << 2) + 2] ^ mul2[input[(i << 2) + 3]]);
	}

	for (i = 0; i < 16; ++i)
		input[i] = tmp[i];

}

int AES128Encrypt::charToHex(char c)
{
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	else if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	else if (c >= '0' && c <= '9')
		return c - '0';

	throw std::invalid_argument("Not A Hex Value!");
}

void AES128Encrypt::get_key_schedule(unsigned char* key, unsigned char key_schedule[])
{
	if (key == nullptr)
		return;

	//Convert Inital Key to Hex
	int index = 0;
	while (index < 16)
	{
		uint16_t temp = 0;
		int left = charToHex(*key);
		key++;
		int right = charToHex(*key);
		key++;

		temp = ((temp | left) << 4) | right;
		key_schedule[index] = temp;
		index++;
	}

	index = 15;
	//Start 10 rounds of Key Schedule
	for (int round = 1; round < 11; round++)
	{

		unsigned char result[4];
		g(key_schedule, result, round);

		//w0
		index++;
		key_schedule[index] = result[0] ^ key_schedule[index - 16];
		index++;
		key_schedule[index] = result[1] ^ key_schedule[index - 16];
		index++;
		key_schedule[index] = result[2] ^ key_schedule[index - 16];
		index++;
		key_schedule[index] = result[3] ^ key_schedule[index - 16];

		//w1
		index++;
		key_schedule[index] = key_schedule[index - 4] ^ key_schedule[index - 16];
		index++;
		key_schedule[index] = key_schedule[index - 4] ^ key_schedule[index - 16];
		index++;
		key_schedule[index] = key_schedule[index - 4] ^ key_schedule[index - 16];
		index++;
		key_schedule[index] = key_schedule[index - 4] ^ key_schedule[index - 16];

		//w2
		index++;
		key_schedule[index] = key_schedule[index - 4] ^ key_schedule[index - 16];
		index++;
		key_schedule[index] = key_schedule[index - 4] ^ key_schedule[index - 16];
		index++;
		key_schedule[index] = key_schedule[index - 4] ^ key_schedule[index - 16];
		index++;
		key_schedule[index] = key_schedule[index - 4] ^ key_schedule[index - 16];

		//w3
		index++;
		key_schedule[index] = key_schedule[index - 4] ^ key_schedule[index - 16];
		index++;
		key_schedule[index] = key_schedule[index - 4] ^ key_schedule[index - 16];
		index++;
		key_schedule[index] = key_schedule[index - 4] ^ key_schedule[index - 16];
		index++;
		key_schedule[index] = key_schedule[index - 4] ^ key_schedule[index - 16];

	}

}

void AES128Encrypt::g(unsigned char w3[], unsigned char result[], int round)
{
	result[3] = sbox[w3[12 + (16 * (round - 1))]];
	result[0] = sbox[w3[13 + (16 * (round - 1))]];
	result[1] = sbox[w3[14 + (16 * (round - 1))]];
	result[2] = sbox[w3[15 + (16 * (round - 1))]];

	result[0] = result[0] ^ rcon[round];
}
#AES 128-Bit Encryption

Instructions to run program files:

1. Make sure you have a c++ compiler installed. (ex. mingw)

2. Open the command line.

3. Change directory to folder that contains the code through the command line.

	Windows Example: 
		cd [absolute folder path]
		cd C:\"your directory"\Nguyen_Thinh_cs4600p1

4. Once in the folder, Compile: Main.cpp, AES128Encrypt.cpp -> AES128Encrypt.exe
This creates the object for the program.

	Windows Example:
		"g++ Main.cpp AES128Encrypt.cpp -o AES128Encrypt.exe"


5. Run the program by typing: "AES128Encrypt [Absolute filepath for file to be encrypted]"

6. The program will then prompt you to enter Hex Key for encryption.

	If successful you should see:
		"Finished AES 128-bit (ECB) Encryption"

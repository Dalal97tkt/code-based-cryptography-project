# code-based-cryptography-project
Implementation of ISD decoding and BIKE2
## Notes concerning the `ISD.c` file:
Gauss inversion is included in the ISD algorithm.
For ISD I generated a random parity check matrix and put it inside PC, first line contains the number of lines and the second number of columns and followed by matrix elements
I used Char type to benefit from smaller size and included changes to use correct format
## Notes concerning the `MDPC_...` files:
To be able to run the code with error a file has to be included in the same directory ( for the encryption we need message.txt, for decryption we need cipher.txt), the inside of these files is irrelevant.

# Cipher
There are different versions depending on the operating system you have. The Windows version is pre-compiled, and comes in a zip, so that my non-coding friends don't have to figure all that out. The linux version is not compiled so you can see the code. Heres the usage:
./[executable] [-flag] [full file path to message] [key1] [key2]

There are 3 options for flags: -e; -d; -g.

-e is for encrypting a file, -d is for decrypting a file, -g is for generating a key.

There are 27 valid characters: capitol A-Z, and _ for spaces. No punctuation, numbers, or lowercase.
Key1 must be relatively prime to 27, as this uses affine cipher as part of it's encryption. I know this isn't the most secure cipher of all time, and can be brute forced, but this is made just for fun. Plus there are other encryptions, including an ascii shift, and random characters, that make it more secure. Key2 can be any number between 1-1000. Here is an example of what a valid argument may look like:

./output.exe -e ~/Downloads/message.txt 8 420

If you pass a -g flag, put in random, but valid values for the filepath, Key1, and Key2. It won't affect your document, it just needs all 5 args to properly run. Heres an example:
./[executable] -g ~/Documents/randomfile.txt 4 473        (last 2 are random numbers)

Feel free to edit the code for ease of use.

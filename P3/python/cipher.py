from Crypto.Cipher import DES3
if __name__ == '__main__':
	with open('key', mode='rb') as file: # b is important -> binary
		key = file.read()
		cipher = DES3.new(key, DES3.MODE_CBC)
		plaintext = b'We are no longer the knights who say ni!'
		msg = cipher.iv + cipher.encrypt(plaintext)
		print(plaintext)
		print(msg)
		newFileByteArray = bytearray(msg)
		with open("./ciphertext", "wb") as binary_file:
			binary_file.write(newFileByteArray)

from Crypto.Cipher import DES3
if __name__ == '__main__':
	with open('key', mode='rb') as file: # b is important -> binary
		key = file.read()
		with open('ciphertext', mode='rb') as file: # b is important -> binary
			cipher = DES3.new(key, DES3.MODE_CBC)
			ciphertext = file.read()
			plaintext = cipher.decrypt(ciphertext)
			print(plaintext)
"""
	* @ date: 15/05/2022
	* @ author: Almanza Martínez Francisco Alejadro
	* @ subject: Criptography
	* @ teacher: Sandra Diaz Santiago
	* @ Description: Practice 5. AES encryption. Usage python aes.py <operation_mode>
	*	0: "CBC"
	*	1: "CTR"
	*	2: "OFB"
	*	3: "CFB"
	*	
"""
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad
import base64, os, sys

if __name__ == '__main__':
	if not len(sys.argv) > 1:
		print("[E] Operation mode is missing: 0: CBC, 1: CTR, 2: OFB, 3: CFB")
		exit()
	op_mode = int(sys.argv[1])
	key = get_random_bytes(16)

	f = open(f"./keys/AES_key{sys.argv[1]}.txt", "wb")
	b64_key = base64.b64encode(key)
	f.write(b64_key)
	f.close()
	random_bytes_file = open('/dev/random', 'rb')
	padding = random_bytes_file.read(1000000)
	random_bytes_file.close()

	if op_mode == 0:
		cipher = AES.new(key, AES.MODE_CBC)
	if op_mode == 1:
		cipher = AES.new(key, AES.MODE_CTR)
		nonce = cipher.nonce
	if op_mode == 2:
		cipher = AES.new(key, AES.MODE_OFB)
	if op_mode == 3:
		cipher = AES.new(key, AES.MODE_CFB)

	f = open(f"./messages/AES_message{sys.argv[1]}.txt", "wb")
	plaintext = b"The name of the ship was the Billy of tea... "

	ciphertext = cipher.encrypt(pad(plaintext, 256))

	b64 = base64.b64encode(ciphertext)
	padding = base64.b64encode(padding)
	f.write(b64+padding)
	f.close()

	print(plaintext)
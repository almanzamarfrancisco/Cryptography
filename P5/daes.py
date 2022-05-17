"""
	* @ date: 15/05/2022
	* @ author: Almanza Martínez Francisco Alejadro
	* @ subject: Criptography
	* @ teacher: Sandra Diaz Santiago
	* @ Description: Practice 5. AES encryption. Usage python daes.py <operation_mode>
	*	0: "CBC"
	*	1: "CTR"
	*	2: "OFB"
	*	3: "CFB"
	*	
"""
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import unpad
import base64, sys

if __name__ == '__main__':
	if not len(sys.argv) > 1:
		print("[E] Operation mode is missing: 0: CBC, 1: CTR, 2: OFB, 3: CFB")
		exit()
	op_mode = int(sys.argv[1])
	read_file = open(f"./keys/AES_key{sys.argv[1]}.txt", 'rb')
	b64_key = read_file.read()
	key = base64.b64decode(b64_key)
	read_file.close()
	if op_mode == 0:
		cipher = AES.new(key, AES.MODE_CBC)
	if op_mode == 1:
		cipher = AES.new(key, AES.MODE_CTR)
	if op_mode == 2:
		cipher = AES.new(key, AES.MODE_OFB)
	if op_mode == 3:
		cipher = AES.new(key, AES.MODE_CFB)
	read_file = open(f"./messages/AES_message{sys.argv[1]}.txt", 'rb')
	b64_ciphertext = read_file.read(128)
	read_file.close()
	ciphertext = base64.b64decode(b64_ciphertext)
	msg = cipher.decrypt(ciphertext)
	try:
		msg = unpad(msg, 256)
	except Exception as e:
		pass
	print(msg)
"""
	* @ date: 15/05/2022
	* @ author: Almanza Martínez Francisco Alejadro
	* @ subject: Criptography
	* @ teacher: Sandra Diaz Santiago
	* @ Description: Practice 5. 3DES encryption. Usage python des3.py <operation_mode>
	*	0: "CBC"
	*	1: "CTR"
	*	2: "OFB"
	*	3: "CFB"
	*	
"""
from Crypto.Cipher import DES3
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad
import base64, os, sys

if __name__ == '__main__':
	if not len(sys.argv) > 1:
		print("[E] Operation mode is missing: 0: CBC, 1: CTR, 2: OFB, 3: CFB")
		exit()
	op_mode = int(sys.argv[1])
	sec = os.urandom(24)
	# Avoid Option 3
	while True:
		try:
			key = DES3.adjust_key_parity(sec)
			f = open(f"./keys/DES3_key{sys.argv[1]}.txt", "wb")
			b64_key = base64.b64encode(key)
			f.write(b64_key)
			f.close()
			random_bytes_file = open('/dev/random', 'rb')
			padding = random_bytes_file.read(1000000)
			random_bytes_file.close()
			break
		except ValueError:
			pass
	if op_mode == 0:
		cipher = DES3.new(key, DES3.MODE_CBC)
	if op_mode == 1:
		cipher = DES3.new(key, DES3.MODE_CTR)
	if op_mode == 2:
		cipher = DES3.new(key, DES3.MODE_OFB)
	if op_mode == 3:
		cipher = DES3.new(key, DES3.MODE_CFB)
	f = open(f"./messages/DES3_message{sys.argv[1]}.txt", "wb")
	plaintext = b"There once a ship that put to sea..."
	msg = cipher.iv + cipher.encrypt(pad(plaintext, 256))
	b64 = base64.b64encode(msg)
	padding = base64.b64encode(padding)
	f.write(b64+padding)
	f.close()
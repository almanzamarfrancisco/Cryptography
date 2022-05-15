from Crypto.Cipher import DES3
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import unpad
import base64

if __name__ == '__main__':
	read_file = open('./keys/key.txt', 'rb')
	b64_key = read_file.read()
	key = base64.b64decode(b64_key)
	read_file.close()
	# print(key)
	cipher = DES3.new(key, DES3.MODE_CFB)
	read_file = open('./messages/message.txt', 'rb')
	b64_ciphertext = read_file.read(128)
	read_file.close()
	ciphertext = base64.b64decode(b64_ciphertext)
	msg = cipher.decrypt(ciphertext)
	try:
		msg = unpad(msg, 256)
	except Exception as e:
		pass
	print(msg)
from Crypto.Cipher import DES3
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad
import base64
import os

if __name__ == '__main__':
	sec = os.urandom(24)
	# Avoid Option 3
	while True:
		try:
			key = DES3.adjust_key_parity(sec)
			f = open("./keys/key.txt", "wb")
			b64_key = base64.b64encode(key)
			f.write(b64_key)
			f.close()
			random_bytes_file = open('/dev/random', 'rb')
			padding = random_bytes_file.read(1000000)
			random_bytes_file.close()
			break
		except ValueError:
			pass
	cipher = DES3.new(key, DES3.MODE_CFB)
	f = open("./messages/message.txt", "wb")
	plaintext = b"There once a ship that put to sea..."
	msg = cipher.iv + cipher.encrypt(pad(plaintext, 256))
	b64 = base64.b64encode(msg)
	padding = base64.b64encode(padding)
	f.write(b64+padding)
	f.close()
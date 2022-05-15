from Crypto.Cipher import DES3
from Crypto.Random import get_random_bytes
import base64
import math, os, sys

sec = os.urandom(24)
# Avoid Option 3
while True:
	try:
		key = DES3.adjust_key_parity(sec)
		f = open("./keys/key.txt", "wb")
		f.write(key)
		f.close()
		break
	except ValueError:
		pass
cipher = DES3.new(key, DES3.MODE_CFB)
f = open("./messages/message.txt", "wb")
plaintext = b'All I need is your love tonigth'
b64 = base64.b64encode(plaintext)
msg = cipher.iv + cipher.encrypt(b64)
f.write(msg)
f.close()
from Crypto.Cipher import DES3
from Crypto.Random import get_random_bytes
import base64


read_file = open('./keys/key.txt', 'rb')
key = read_file.read()
read_file.close()
# print(key)
cipher = DES3.new(key, DES3.MODE_CFB)
read_file = open('./messages/message.txt', 'rb')
ciphertext = read_file.read()
read_file.close()
b64 = cipher.iv + cipher.decrypt(ciphertext)
msg = base64.b64decode(b64)
print(msg)
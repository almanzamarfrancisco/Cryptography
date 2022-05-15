from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
import base64

message = "Python is fun and this is secret"
message_bytes = message.encode('ascii')
base64_bytes = base64.b64encode(message_bytes)
base64_message = base64_bytes.decode('ascii')

key = get_random_bytes(16)
print(key)
cipher = AES.new(key, AES.MODE_EAX)
ciphertext, tag = cipher.encrypt_and_digest(bytes(base64_message, 'utf-8'))

file_out = open("AES-encrypted.bin", "wb")
[ file_out.write(x) for x in (cipher.nonce, tag, ciphertext) ]
file_out.close()
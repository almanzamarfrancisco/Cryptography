from Crypto.Cipher import AES
import base64

file_in = open("AES-encrypted.bin", "rb")
nonce, tag, ciphertext = [ file_in.read(x) for x in (16, 16, -1) ]

# let's assume that the key is somehow available again
key = b",\xe9'\n\xe1\x1d\xbe\x1c9`2\x85\x84 1X"
cipher = AES.new(key, AES.MODE_EAX, nonce)
data = cipher.decrypt_and_verify(ciphertext, tag)

message_bytes = base64.b64decode(data)
message = message_bytes.decode('ascii')

print(message)

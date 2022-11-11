from Crypto.Cipher import DES3
from Crypto.Random import get_random_bytes
# Avoid Option 3
if __name__ == '__main__':
    while True:
        try:
            key = DES3.adjust_key_parity(get_random_bytes(24))
            break
        except ValueError:
            pass
    newFileByteArray = bytearray(key)
    with open("./key", "wb") as binary_file:
        binary_file.write(newFileByteArray)
    
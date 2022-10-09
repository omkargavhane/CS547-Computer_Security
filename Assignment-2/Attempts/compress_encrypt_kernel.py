#7d491e7df182aaed9b20b3e94b3ff042d317d260a25b8551a95fc7e9e2160e7e45ee9e0d42851b062c713dfbeacee8b0c5f280efa27a8054e8758be22ba8d140
import pickle
import zlib
from cryptography.fernet import Fernet
with open("./core/key","rb") as fp:
    key=pickle.load(fp)
aes=Fernet(key)
decrypted=aes.decrypt(b"gAAAAABiDOKK2BxwFIvKEnMIJG0uNLqiOVLYvYV7sxO4u13If4oDPH86zqQSIDanPA2mhLXBDmNh_n4uxf5CVolhUDGafj5OP3dAyuG00vt9GMXYteaPCRZx0_ktI8IEfExTgQJ2FAUWMDjBl7x-JheLb8uLQYxqoE448qfHmvddAqwoAUB4iNirpqTNhGkyVejiN82JynujdLcS74x-qAl5QkB6RGW9Dy8H87G8tiVsKF-ug0vWzzd38ABYbiE6RBISR9nv9HOk3ya9w03FLJO2mLuh7HT6GNkHIS83daa9p7DJe-IZzwbYnnva4paG16Y1Sg6TSy39QhwbXhQnItV4VAaLNjfiwC4WgZQ9F35E4ldyj_Enfn6-OC3n8rLkFUfG67coCmTYQF6Hw2W-2SXGysaAYS1tNVXqRAjZJjnEzQJwHrrNUkKyXfrxBT4Zl7NZJSkTgR68aCzB3zMEkdVkjy8lBRKHf6wDgS56itE2aRzUTEX2iGA9gPPgyI3RwhzWB6yv7N3_7FyTr3IudbtiMiSLbi_KgN-vYMv7nULVkjzHonYfMMKjjWVX-jX1tAq6MbiSb6QVAoEXoP1m05AERO6F_dLiiPd5cZm6Q21ClDmP6q5dSQYwJK8jzSTKVHY8Dz6jTyE8n2Li9PMvtAO0YuuD4kEM_g==")
decompressed=zlib.decompress(decrypted)
print(decompressed.decode())
exec(decompressed.decode())
#7d491e7df182aaed9b20b3e94b3ff042d317d260a25b8551a95fc7e9e2160e7e45ee9e0d42851b062c713dfbeacee8b0c5f280efa27a8054e8758be22ba8d140
import pickle
import zlib
from cryptography.fernet import Fernet

def compress():
    #compress the kernel.py file and return that compressed string
    with open("kernel.py","r") as fp:
        ic=fp.read()
    compressed_code=zlib.compress(ic.encode())
    return compressed_code

def encryption(compressed_code):
    '''encrypt the compressed code using key present in key file and return encrypted code
    here encryption algo is AES'''
    with open("key","rb") as fp:
        key=pickle.load(fp)
    aes=Fernet(key)
    #Encryption
    encrypted_code=aes.encrypt(compressed_code)
    return encrypted_code

def write(encrypted_code):
    #writing encrypted code to ce_kernel file
    with open("ce_kernel","wb") as fp:
        fp.write(encrypted_code)

def read():
    with open("ce_kernel","rb") as fp:
        encrypted_code=fp.read()
    return encrypted_code

def decryption(encrypted_code):
    with open("key","rb") as fp:
        key=pickle.load(fp)
    aes=Fernet(key)
    #Decryption
    decrypted_code=aes.decrypt(encrypted_code)
    return decrypted_code

def decompress(decrypted_code):
    #Decompression
    decompress_code=zlib.decompress(decrypted_code)
    print(decompress_code)

write(encryption(compress()))
#decompress(decryption(read()))


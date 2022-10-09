import os
import csv
def signature_based():
    potential_threat=[]
    signatures=["decrypt","hash","compress","decompress","key","exec"]
    for root,dirs,files in os.walk("."):
        for file in files:
            with open(root+"/"+file,"r") as fp:
                for signature in signatures:
                    if signature in fp.read():
                        potential_threat.append(root+"/"+file)
    print("[Signature_based]Files with potential threat")
    for e in potential_threat:
        print(e)

def get_status():
    status=[]
    for root,dirs,files in os.walk("."):
        for file in files:
            fsize=os.path.getsize(root+"/"+file)
            fmtime=os.path.getmtime(root+"/"+file)
            status.append([file,fsize,fmtime])
    return status

def write_status(status):
    with open("status.csv","w") as fp:
        obj=csv.writer(fp)
        obj.writerows(status)
def heuristics_based():
    potential_threat=[]
    status=get_status()
    with open("status.csv","r") as fp:
        obj=csv.reader(fp)
        for eo in list(obj):
            for ei in status:
                if eo[0]==ei[0]:
                    if float(eo[1])!=float(ei[1]) or float(eo[2])!=float(ei[2]):
                        potential_threat.append(eo[0])
    print("[heuristic_based]Files with potential threat")
    for e in potential_threat:
        print(e)


status=get_status()
#write_status(status)
signature_based()
heuristics_based()

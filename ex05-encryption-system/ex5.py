import json, os

global flag
flag = False

class CaesarCipher:
    def __init__(self, m_key):
        self.m_key = m_key

    def encrypt(self, str):
        result_str = ""

        for letter in str:
            if letter.isupper():
                temp = (ord(letter) + self.m_key - ord('A')) % 26
                result_str += chr(temp + ord('A'))

            elif letter.islower():
                temp = (ord(letter) + self.m_key - ord('a')) % 26
                result_str += chr(temp + ord('a'))
            else: 
                result_str += letter

        return result_str

    def decrypt(self , str):
        result_str = ""
        self.m_key *= -1
        result_str = self.encrypt(str)
        self.m_key *= -1
        return result_str
    

class VigenereCipher():
    def __init__(self, m_list):
        self.m_list = m_list
        global i
        i = 0

    def encrypt(self , str):
        if flag:
            global i
        else:
            i = 0
        keyList = []
        result_str = ""
        for key in self.m_list:
            keyList.append(CaesarCipher(key))
        
        for s in str:
            if not s.islower() and not s.isupper():
                result_str += s
                continue
            
            result_str += keyList[i % len(keyList)].encrypt(s)
            i+=1
        
        return result_str

    def decrypt(self , str):

        for j in range(len(self.m_list)):
            self.m_list[j] *= -1


        result_str = self.encrypt(str)
        
        for j in range(len(self.m_list)):
            self.m_list[j] *= -1


        return result_str
    
    def updateList(self):
        global i,flag
        flag = True
        i = 0


def getKey(string):
    list = []

    for s in string:
        if type(s) != type("string") or (not s.islower() and not s.isupper()):
            continue
        elif s.islower():
            list.append(ord(s) - ord('a'))
        elif s.isupper():
            list.append(ord(s) - ord('A'))

    return list

def getVigenereFromStr(string):
    return VigenereCipher(getKey(string))



def loadEncryptionSystem(dir_path):
    with open(os.path.join(dir_path,'config.json'),'r') as f:
        loadedDict = json.load(f)
    

    eType = loadedDict["type"]
    encrypt = loadedDict["encrypt"]
    key = loadedDict["key"]


    if(eType == "Vigenere"):
        sys = getVigenereFromStr(key)
    else:
        sys = CaesarCipher(key)


    for file in os.listdir():
        name, extension = os.path.splitext(file)
        if extension == ".txt":
            with open(os.path.join(dir_path,file)) as f:
                with open(os.path.join(dir_path,name + '.enc'),'w') as out:
                    sys.updateList()
                    for line in f:
                        if encrypt:
                            out.write(sys.encrypt(line))
                        else:
                            out.write(sys.decrypt(line))
                    global flag
                    flag = False
                            




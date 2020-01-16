class Caeser(object):
  def __init__(self,shift=3):
    self.shift = shift
    self.alpha = {}
    
    for i in range(26):
      key = chr(i+65)
      val = chr((i+self.shift) % 26 + 65)
      self.alpha[key] = val
    print(self.alpha)
      
  def Encrypt(self,plain_text):
    cipher_text  =''
    for i in plain_text.upper():
      if i in self.alpha:
        cipher_text += self.alpha[i]
    return cipher_text
  
  def Decrypt(self,cipher_text):
    plain_text = ''
    for i in cipher_text:
      for k,v in self.alpha.items():
        if v == i:
          plain_text += k
    return plain_text
  
cipher = Caeser(5)
cipherText = cipher.Encrypt("hello world")
print(cipherText)
plainText = cipher.Decrypt(cipherText )
print(plainText)

class ShiftCipher(object):
	def __init__(self):
		self.plainText = None
		self.cipherText = None
		self.cleanText = None
		self.shift = 3
	
	def setMessage(self,message,encrypted=False):
		if(not encrypted):
			self.plainText = message
			self.__encrypt()
		else:
			self.cipherText = message
			self.__decrypt()
	
	def getCipherText(self):
		return self.cipherText
		
	def getPlainText(self):
		return self.plainText

	def setShift(self,shift):
		self.shift = shift
	
	def getShift(self):
		return self.shift
		
	def cleanData(self):
		self.cleanText = ''
		for letter in self.plainText:
			if ord(letter) > 96:
				self.cleanText += chr(ord(letter)-32)
			else:
				self.cleanText += letter

	"""
	Encrypts plaintext not ciphertext
	"""
	def __encrypt(self):
		self.cleanData()
		if(not self.cleanText):
			return
		
		
	
	"""
	Decrypts ciphertext not plaintext
	"""
	def __decrypt(self):
		pass


alice = ShiftCipher()
alice.setMessage("hello world")
print(alice.getPlainText())

bob = ShiftCipher()
bob.setMessage(alice.getCipherText(),True)



# plain_text = "Hello world. Please encrypt me."
# cipher_text = ""

# LETTERS = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'


# def encrypt(letter,key):
#     letter = ord(letter)
#     letter = letter - 65
#     letter = (letter + key) % 26
#     letter = letter + 65
#     return letter
    
# print(plain_text)

# key = 0

# for i in range(len(plain_text)):
#     if plain_text[i].upper() in LETTERS:
#         cipher_text = cipher_text + chr((ord(plain_text[i].lower())+key) % 26)
#         print(ord(plain_text[i].upper())-65)
#         print(encrypt(plain_text[i],key))
#     else:
#         cipher_text = cipher_text + plain_text[i]
    
# print(cipher_text)


import random

class Dice(object):
	def __init__(self,num_sides=6):
		self.NumSides = num_sides
		
	def Roll(self):
		return random.randint(1,self.NumSides)
		
class Pig(object):
	def __init__(self,num_dice=1,dice_sides=6):
		self.NumDice = num_dice
		self.DiceSides = dice_sides
		self.DiceList = []
		for i in range(self.NumDice):
			self.DiceList.append(Dice(self.DiceSides))
		
	def Roll(self):
		scores = []
		for d in self.DiceList:
			scores.append(d.Roll())
		return scores

#Goal is get to 100
#If player rolls a 1 they lose a turn 
#Player will roll from 1 to random number of times

class Game(object):
	
	def __init__(self,num_dice,players=None):
		
		self.Players = {}
		self.NumDice = num_dice
		
		self.p = Pig(self.NumDice)
		
		for p in players:
			self.Players[p] = 0
			

		while not self.Winner():
			for p,s in self.Players.items():
				proll = self.PigRoll(7)

				self.Players[p] += proll
				if self.Winner():
					break
				
				print(self.Players)
			print(self.Players)
	
	def PigRoll(self,number_rolls):
		total = 0
		for i in range(random.randint(1,number_rolls)):
			nums = self.p.Roll()
			if 1 in nums:
				return 0 
			else:
				total += sum(nums)
		return total
		
		
	def Winner(self):
		for p,s in self.Players.items():
			if s >= 100:
				return True
		return False
		
	

d = Dice()

p = Pig(10)

print(p.Roll())

players = ['bob','sue','bill','ann']

g = Game(1,players)

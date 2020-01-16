# This text is a huge chunk we scraped from the web
myBook = "Doubtless I shall tell this tale but poorly, since I have no skill of writing or rhetoric and must, for the most part, proceed by blunt sentences and short one-syllable words to the end that I be understood. This record is worth while, I think, for it exhibits the growth of favor for the Union within the General’s breast; and to be corollary thereunto, his wrath against States Rights as a doctrine, together with a hatred of Calhoun, its champion, and what other folk were found to uphold the Vice-President’s hands in those ill courses of nullification and separation and secession he laid down for national misguidance. I myself had been with the General, war and peace, for thirty years on end. He was like an elder brother to me, and I apprehended no man better. And knowing him thus well--having his thought and feeling and emotion of politics at my mental finger-ends--it is in my strong belief that not until he came and made oath as chief magistrate, did he conclude his position touching this claim of right on a state’s part to nullify general law and strike her name from the roll of our common sisterhood. I was with him, I say, when the seed of the General’s determination to stand for a union, one and indivisible, was planted; and I witnessed its quick upgrowing and broadening until it sheltered and shadowed with wide safety the very integrity of the country. We had arrived at a fork in the road; the ways were about to part. Calhoun would have led us to the left where no man could be sure of national continuance over night. But the General ruled; he was for the right hand. By his iron courage, and the brisk, white clearness of his mental lights, the General was to triumph. As descendant of such victory the States were to be unified and secession beaten down. Nor shall that hour find its morning in all time when the mighty excellences of the General’s labors are not to have their evidence, and the tree he planted bear into the hands of men its fruits upon the earth. He was a tremendous mechanic of state, was General Jackson; and the world in its construction will wear his hammer-marks with those of Cromwell and Napoleon while the ages keep to their procession. And yet, as may the Amazon have ultimate well-head in some rivulet as thin as a thread, or a spring so little that a gourd might serve for its exhaustion, so did the General come to select his place in this business of upholding the Union against those who would pull it down, as incident to bucklering a woman--poor and slight and feeble, she was; the beautiful Peg O’Neal!--who for her loveliness was envied and for her goodness was hated and for her origin as a tavern-keeper’s daughter was contemned by those proud folk who named themselves the nation’s court of fashion. The General was a sentimentalist; justice and to do right were with him instincts, and came not as grist ground coldly in the mills of calculated selfishness and reason. Scotch-Irish he was in his strain; but more Irish than the Irish and more Scotch than the Scotch, he in a manner wonderful could in the same moment be cool and warm, and cautious and headlong, and prudent and reckless, and close and frank--at once a Fabius and a Scipio. In a glow of sentiment made molten hot by the recent death of his wife--to him the Goddess of his worship--the General would extend the power of his place and name to be a refuge for the tearful, beautiful Peg, whom, as a child, his wife had known and loved, and whom he now found evilly crushed beneath the social wheel. And in a rush of feeling he rescues her and sets her high among the highest. Still, while it owns its hot inception to impulse wholly Irish, this rescue; the carrying out thereof, when now the General goes about it, turns to be all Scotch in the cautious yet indomitable character of its execution. Also, for that the General is ardent and prone to mix private passion with his public thought, he arrives at a hatred of nullification, finding it a prime principle among those enemies whom he faces for the sake of poor Peg O’Neal. It is the great fire kindled of a small thing, this, the General’s war to sustain the Union against ones who already searched for its life. He rides into the lists for a woman’s name, and all unknowingly he bears the country’s future on the point of his spear. And so comes this story; to the purpose and the hope that what in this good way the General did, and why and how he did it, may not die and disappear upon the memories of men."


class BookHist(object):
  def __init__(self,text):

    self.myList = text.split()
    
    # Create a dictionary so we can count the words
    self.wordCount = {}
    
    # loop through the list: "myList" 
    for word in self.myList:
      # Remove bad characters by 'replacing' them with nothing.
      word = word.lower().replace(',','').replace(';','').replace('.','').replace("’",'').replace('--','')
      # if the word were reading on this loop iteration is NOT in our dictionary yet
      # then place the word in the dictionary.
      if not word in self.wordCount:
          self.wordCount[word] = 0 
      # If the word IS in the dictionary, than just increment the count
      self.wordCount[word] += 1

  def getMax(self):
    maxword = ''
    maxcount = 0 
    for key,val in self.wordCount.items():
      if val > maxcount:
        maxcount = val
        maxword = key
    return (maxword,maxcount)
    

# listCount = BookHist(myBook)
# print(listCount.getMax())




dict = {}

dict['2143'] = {
  'student 1': [88,99,33],
  'student 2': [66,77,88],
  'student 3': [22,22,22]
  }
dict['1063'] = {
  'student 1': [88,99,33],
  'student 2': [66,77,88],
  'student 3': [22,22,22]
  }
  
print(dict['2143']['student 1'])

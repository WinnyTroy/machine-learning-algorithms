# KIRAGU WINNIE WANGECHI
# LEXER IMPLEMENTATION




content = []  # list storing all read content from file
row_list = []
lines = 0		# number of lines


# file to be read line by line. Opened with read parameter.
with open("lexical.c","r") as f:
    for row in f:
        content.append(row)
        lines += 1
print("Number of read lines from file: ",lines)



def check_op(char,pos):
	operators = ['.','+','-','/','*','=','%','==','->','!=','>=','<=','<','>','!','++','--','&&','&','|','||','<<','>>','~','^','?','+=','-=','*=','/=','%=','(',')','{','}','[',']',',','#','%d','%s','%f']
	token_type = 'Operator'
	if char in operators:
		print_tokens(char,token_type,pos)


# function that checks for keywords in grammar
def check_keyword(word,pos):
	keywords = ['auto','break','case','char','const','continue','default','do','double','else','enum','extern','float','for','goto','if','inline','int','long','register','restrict','return','short','signed','sizeof','static','struct','switch','typedef','union','unsigned','void','volatile','while','printf','scanf','include','main']
	token_type = 'Keyword'
	token_type2 = 'Identifier'
	for i in keywords:
		if i in word:
			print_tokens(word,token_type,pos)
			return 0
		else:
			flag = 1
	if(flag == 1):
		if(word != ''):
			print_tokens(word,token_type2,pos)



#print headers to file

with open('tokens.txt', 'w') as f:
		print("{:20} {:20} {:20}".format('TOKEN', 'TOKEN TYPE', 'LINE'),file = f)
		print("{:20} {:20} {:20}".format('TOKEN', 'TOKEN TYPE', 'LINE'))


# function to print to file (appends)

def print_tokens(token,token_type,line):
	with open('tokens.txt', 'a') as f:
		print("{:20} {:20} {:5}".format(token,token_type,line),file = f)
		print("{:20} {:20} {:5}".format(token,token_type,line))


#read characters line by line
chars = []
pos = 0
for row in content:
	prev = ''		#resets per row
	word = []
	String = []
	string_flag = 1
	letter = ''
	letter_counter = 1
	for char,next in zip(row[0::1],row[1::1]): 

		#check words
		if(char.isalpha()):
			letter = letter + char
			letter_counter += 1
		elif((char == '_' or char.isdigit()) and letter_counter != 1):
			letter = letter + char
			letter_counter += 1
		else:
			word.append(letter)
			flag = 0
			if(word[0].isdigit()):		#check numbers
				token_type = "Number"
				print_tokens(word[0],token_type,pos + 1)
			else:
				if(string_flag != 1 and word[0] != ''):	#strings
					token_type = "String"
					print_tokens(word[0],token_type,pos + 1)
				else:
					check_keyword(word[0],pos + 1)
			#print(word[0])
			word = []
			letter ='' 
			#check strings	
		if(char == '"'):
			string_flag = -(string_flag)
			
		#check operators
		oper = ['=','+','-','&','|','<','>']
		prev_oper  = ['+','-','/','*','=','%','<','>','!','&','|','^',]
		if next in oper:
			chars = char + next
			check_op(chars,pos + 1)
		elif prev not in prev_oper:
			check_op(char,pos + 1)
		prev = char 	#store prev char to avoid re-read

	pos += 1			#line count

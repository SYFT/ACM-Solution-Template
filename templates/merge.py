import os

fileDir = '.'
resultName = 'template.txt'
resultFile = os.path.join(fileDir, resultName)

with open(resultFile, 'w') as result :
	for fName in os.listdir(fileDir) :
		if fName.find('.cpp') != len(fName) - 4 :
			continue
		result.write(fName + "\n")
	for fName in os.listdir(fileDir) :
		if fName.find('.cpp') != len(fName) - 4 :
			continue

		result.write(fName + ':\n')
		fName = os.path.join(fileDir, fName)
		template = open(fName, 'r')
		content = template.read()
		template.close()
		result.write(content)
		result.write('\n\n\n')


result.close()

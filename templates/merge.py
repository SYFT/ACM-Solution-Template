# coding=utf-8
import os, sys
reload(sys) 
sys.setdefaultencoding('utf-8')
fileDir = '.'
resultName = 'template_.tex'
resultFile = os.path.join(fileDir, resultName)

with open(resultFile, 'wb') as result :
	for fName in os.listdir(fileDir) :
		if fName.find('.cpp') != len(fName) - 4 :
			continue
                result.write(r'\section{%s}' % fName)
                result.write('\n')
                result.write(r'\begin{lstlisting}[language=c++]')
                result.write('\n')
                T = open(fName, 'rb')
		content = T.read()
		T.close()
                result.write(content + '\n')
                result.write(r'\end{lstlisting}')
                result.write('\n')

result.close()

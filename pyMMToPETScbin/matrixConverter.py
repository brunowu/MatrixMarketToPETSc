import scipy.io
import fnmatch
import os
import sys
import re

dirs = os.environ['PETSC_DIR']
sys.path.insert(0, dirs+'/bin/pythonscripts/')
sys.path.insert(0, dirs+'/bin/')

import PetscBinaryIO

converted = 'converted'

def grep(path, regex):
    regObj = re.compile(regex)
    res = []
    for root, dirs, fnames in os.walk(path):
        for fname in fnames:
            if regObj.match(fname):
                res.append(os.path.join(root, fname))
    return res

if(len(sys.argv)!=2):
	print 'Usage : python '+sys.argv[0]+' pathToMatrixFiles'
	exit(1)

matrixFileList = []
for root, dirnames, filenames in os.walk(sys.argv[1]):
  for filename in fnmatch.filter(filenames, '*.mtx'):
      matrixFileList.append(os.path.join(root, filename))

for matrix in matrixFileList:
	print 'Matrix to convert '+matrix

if not os.path.exists(converted):
    os.makedirs(converted)

for matrixFile in matrixFileList:
	matName = matrixFile.replace("/",".")
	matName= matName.split(".")[-2]
	A = scipy.io.mmread(matrixFile)
	try:
		if A.shape[1]!=1:
			outputfile = converted+'/'+matName+'_'+str(A.shape[0])+'x'+str(A.shape[1])+'.dat'
			print 'Outputing : '+outputfile
			mfile = open(outputfile,'w')
			PetscBinaryIO.PetscBinaryIO().writeMatSciPy(mfile, A)
		else:

			outputfile = converted+'/'+matName+'_'+str(A.shape[0])+'.dat'
			print 'Outputing : '+outputfile
			mfile = open(outputfile,'w')
			PetscBinaryIO.PetscBinaryIO().writeVec(mfile, A)

	
		
		

	except Exception, e:
		print 'Error Creating file '+outputfile
		if os.path.isfile(outputfile):
			os.remove(outputfile)
			print 'File has been removed'

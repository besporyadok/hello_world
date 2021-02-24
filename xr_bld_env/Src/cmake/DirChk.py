# DirChk.py

import sys
import os
import re
import glob
import xml.etree.ElementTree as ET

usage = 'Source folder checker\n%s <src_dir> <prj_name>\n\t \
<src_dir> - source code directory\n\t<prj_name> - project name (*.vcproj)'

PRJ_LST = 1
DIR_LST = 2
FIN_LST = 3

def dump(lstType, lst):
    if lstType == DIR_LST:
        f = open('dir_lst.log', 'w')
    elif lstType == PRJ_LST:
        f = open('prj_lst.log', 'w')
    elif lstType == FIN_LST:
        f = open('Out.log', 'w')
    else:
        print '\n[ERR]:\tIncorrect list type!'
        return
    
    if lstType != FIN_LST:
        for el in lst:
            f.write(el + '\n')
    else:
        base = 'exclude_from_build("${PROJECT_SOURCE_DIR}/%s")\n'
        lst = [el.replace('\\', '/') for el in lst]
        
        for el in lst:
            f.write(base % el)
    
    f.close()
    
def run():
    if not(len(sys.argv) > 2):
        sys.exit(usage % sys.argv[0])

    prj_name = os.path.join(os.path.abspath(sys.argv[1]), sys.argv[2])
    src_in_prj = []
    src_in_dir = []
    src_fin = []
    
    if not(os.path.exists(prj_name) and os.path.isfile(prj_name)):
        sys.exit('\n[ERR]:\tCan\'t find project name: %s.' % sys.argv[2])

    tree = ET.parse(prj_name)
    root = tree.getroot()
    
    files = root.find('Files')
    for item in files.iter():
        if item.tag == 'File':
            fname = item.get('RelativePath') # Ignore case & dot in path (xrGame hello xD)?
            exclude = item.get('ExcludedFromBuild') # What ?!
            ext = os.path.splitext(fname)[1]
            
            if (ext == '.cpp' or ext == '.c' or ext == '.cxx') and (exclude != 'TRUE'):
                src_in_prj.append(fname)
    
    for i in range(len(src_in_prj)):
        tmp = re.sub(r'^.\\', '', src_in_prj[i])
        src_in_prj[i] = tmp
    
    src_in_dir = glob.glob(os.path.join(sys.argv[1], '*\\*.cpp'))
    src_in_dir.extend(glob.glob(os.path.join(sys.argv[1], '*.cpp')))
    
    src_in_dir = [os.path.abspath(el) for el in src_in_dir]
    src_in_dir = [el.replace(os.path.abspath(sys.argv[1])+'\\', '') for el in src_in_dir]

#    dump(DIR_LST, src_in_dir)
#    dump(PRJ_LST, src_in_prj)

    src_fin = list(set(src_in_dir) - set(src_in_prj))
    src_fin.sort()

    dump(FIN_LST, src_fin)
    
if __name__ == '__main__':
    run()
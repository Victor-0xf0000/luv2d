import os, shutil

bfn = ""

if os.path.exists("build/"):
    bfn = "build/"
elif os.path.exists("bin/"):
    bfn = "bin/"

# note: I don't nothing much about python, lol
try:
    os.remove(bfn+"CMakeCache.txt")
except:
    pass
try:
    os.remove(bfn+"Makefile")
except:
    pass
try:
    os.remove(bfn+"cmake_install.cmake")
except:
    pass
shutil.rmtree(bfn+"lib/")
shutil.rmtree(bfn+"CMakeFiles/")

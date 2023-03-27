import os, shutil

bfn = ""

if os.path.exists("build/"):
    bfn = "build/"
elif os.path.exists("bin/"):
    bfn = "bin/"

# note: I don't nothing about python, lol

def remove_file(path):
    try:
        os.remove(bfn+path)
    except:
        pass

remove_file("CMakeCache.txt")
remove_file("Makefile")
remove_file("cmake_install.cmake")

shutil.rmtree(bfn+"lib/")
shutil.rmtree(bfn+"CMakeFiles/")

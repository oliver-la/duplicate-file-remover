# Duplicate File Remover

This is a C++ program to remove duplicate files in a given directory.

Comparison is made with MD5 checksums. Keep in mind that MD5 is known for collisions. No guarantee is given, run this program at your own risk.

To see if the program is working in the correct directory, you can use the "-test" flag. (It's only ONE dash!)

````
Usage: [options] --dir <directory>

Available options are:
  -test        Don't delete anything (dry-run)
````

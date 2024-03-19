A command line program to convert RGBA888 image files into RGBA222 files.

Usage: rgb2 [filename]

Output: filename.RGB2

If no filename is given then the entire current working directory of files will be converted.
It is assumed that source files have a length divible by 4, which any valid RGBA8888 file whould have.

Created by Richard Turnnidge on 15/03/2024.
Intended for use on Mac, but may work on other platforms.

Copy program to /usr/local/bin
with:
sudo cp rgb2 /usr/local/bin

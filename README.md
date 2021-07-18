# tgs2animated(With Python support)

Converts animated Telegram stickers (*.tgs) to animated WEBPs (.webp)
## Building from source

1. Make sure you have g++, make and cmake installed
2. Clone this repository
   
```
git clone --recursive https://github.com/0xNima/tgs2animated.git
```
3. Build

```
cd tgs2animated
mkdir build
cd build
cmake ..
make -j 2
```
### Convert
Pass an input tgs and an output webp
```
$ ./tgs2animated -i ./sticker.tgs -o ./animation.webp
```
### <span id="cli">CLI arguments</span>
```
$ ./tgs2animated -help
Usage:
 tgs2animated [options] -i tgs_file -o webp_file
  -i <tgs_file>............. input tgs file[Required]
  -o <webp_file>............ output webp file[Required]
Options:
  -h / -help ............... this help
  -q <float> ............... quality factor (0:small..100:big)
  -m <int> ................. compression method (0=fast, 6=slowest)
  -min_size ................ minimize size
  -wh <int>................. Width and height in px

  -version ................. print version number and exit

```

## Using in Python
4. modify `setup.py` to consider your desire python's `include directory`. The default is `/usr/include/python3.7`.
5. run following commands:
 ```
 pythonX setup.py build
 pythonX setup.y install
 ```
which X indicates version of your python.

6. now you can use this module in your python:
```
Python 3.7.11 (default, Jul  3 2021, 17:58:19) 
[GCC 9.3.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> import tgs
>>> tgs.convert("inputfile", "outputfile")
True
```
Note that [CLI arguments](#cli) are set to deafult for now. If you want to change any of them, you should modify `tgsmodule.cpp` and repeat step 5.

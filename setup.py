from distutils.core import setup, Extension
module = Extension('tgs',
		include_dirs = [
			'/usr/include/python3.7', 
			'libs/rlottie/inc', 
			'libs/libwebp', 
			'libs/libwebp/src',
			'libs/zstr/src',
			# 'libs/rlottie/vs2019',
			# 'libs/rlottie/src/vector',
			# 'libs/rlottie/src/vector/pixman',
			# 'libs/rlottie/src/vector/freetype'
		],
		libraries = ['pthread', 'dl', 'rlottie', 'webp', 'zlib'],
		library_dirs = ['build'],
		sources = ['tgsmodule.cpp', 'data/data_holder.cpp', 'webp/render.cpp', 'webp/webp_builder.cpp', 'webp/utils.cpp'])
setup (name = 'tgs',
	version = '1.2',
	description = 'Python Binding of tgs2animated tool',
	author = "0xNima",
	url = "-",
	ext_modules = [module])

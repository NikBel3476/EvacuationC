from skbuild import Extension, setup
from Cython.Build import cythonize

link_args = [
    '-Lthirdparty/arraylist'
]

setup(
    ext_modules = cythonize([
        Extension("evacuation_c", ["evacuation_c.pyx"],
            include_dirs=['thirdparty/arraylist']
        )
    ])
)

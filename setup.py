from skbuild import setup
# from setuptools import setup, Extension
# from setuptools.command.build_ext import build_ext as build_ext
# import subprocess
# import sys

# BUILD_DIR = 'build'
# BUILD_TYPE = 'Release'
# class  evacuation_c_build_ext(build_ext):
#     def _build_evacuation_c(self):
#         subprocess.run([
#             'cmake', '-S', '.', '-B', BUILD_DIR, f'-DCMAKE_BUILD_TYPE={BUILD_TYPE}'
#         ], check=True)
#
#         subprocess.run(['cmake', '--build', BUILD_DIR, '--config', BUILD_TYPE])
#
#     def build_extension(self, ext):
#         self._build_evacuation_c()
#
#         lib_path = f'{BUILD_DIR}/libEvacuationC_shared'
#         if sys.platform.startswith('linux'):
#             lib_path += '.so'
#         elif sys.platform.startswith('win32'):
#             lib_path += '.dll'
#         else:
#             raise NotImplementedError(f'The system \'{sys.platform}\' is not supported')
#
#         ext.extra_objects.extend([lib_path])
#         super().build_extension(ext)


setup(
    name="EvacuationC",
    version="0.1.0",
    description="EvacuationC",
    author="",
    license="Apache 2.0",
    packages=["EvacuationC"],
    # cmdclass={'build_ext': evacuation_c_build_ext},
    # ext_modules=[Extension(
    #     'EvacuationC',
    #     sources=['EvacuationC/evacuation_c.pyx'],
    #     language='c'
    # )],
    python_requires=">=3.8"
)

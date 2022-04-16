from setuptools import setup, find_packages

setup(
    name='my_package',
    version='0.1.0',
    packages=find_packages(include=['my_package', 'my_package.*', 'my_package.data', 'my_package.data.*', 'my_package.data.transforms', 'my_package.data.transforms.*', 'my_package.analysis', 'my_package.analysis.*'])
)
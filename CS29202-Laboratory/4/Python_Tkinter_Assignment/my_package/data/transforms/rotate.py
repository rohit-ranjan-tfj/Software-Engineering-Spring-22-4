#Imports
import numpy as np
from PIL import Image

class RotateImage(object):
    '''
        Rotates the image about the centre of the image.
    '''

    def __init__(self, degrees):
        '''
            Arguments:
            degrees: rotation degree.
        '''
        
        self.degrees = degrees

    def __call__(self, sample):
        '''
            Arguments:
            image (numpy array or PIL image)

            Returns:
            image (numpy array or PIL image)
        '''
        if (type(sample).__module__ == np.__name__):
            sample = Image.fromarray(sample)
            
        return sample.rotate(self.degrees)
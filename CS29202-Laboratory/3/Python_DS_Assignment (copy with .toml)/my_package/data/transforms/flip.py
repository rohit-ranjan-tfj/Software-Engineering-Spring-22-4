#Imports
import numpy as np
from PIL import Image

class FlipImage(object):
    '''
        Flips the image.
    '''

    def __init__(self, flip_type='horizontal'):
        '''
            Arguments:
            flip_type: 'horizontal' or 'vertical' Default: 'horizontal'
        '''

        self.flip_type= flip_type

        
    def __call__(self, image):
        '''
            Arguments:
            image (numpy array or PIL image)

            Returns:
            image (numpy array or PIL image)
        '''
        if (type(image).__module__ == np.__name__):
            image = Image.fromarray(image)

        if (self.flip_type == 'horizontal'):
            method=Image.FLIP_LEFT_RIGHT
        elif (self.flip_type == 'vertical'):
            method=Image.FLIP_TOP_BOTTOM
            
        return image.transpose(method = method)
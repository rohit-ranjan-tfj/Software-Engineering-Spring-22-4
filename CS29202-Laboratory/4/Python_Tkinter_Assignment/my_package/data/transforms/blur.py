#Imports
import numpy as np
from PIL import Image, ImageFilter


class BlurImage(object):
    '''
        Applies Gaussian Blur on the image.
    '''

    def __init__(self, radius):
        '''
            Arguments:
            radius (int): radius to blur
        '''

        self.radius = radius
        

    def __call__(self, image):
        '''
            Arguments:
            image (numpy array or PIL Image)

            Returns:
            image (numpy array or PIL Image)
        '''
        if (type(image).__module__ == np.__name__):
            image = Image.fromarray(image)
                    
        return image.filter(ImageFilter.GaussianBlur(radius = self.radius))

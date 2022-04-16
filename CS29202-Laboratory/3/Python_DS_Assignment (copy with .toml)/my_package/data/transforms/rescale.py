#Imports
import numpy as np
from PIL import Image

class RescaleImage(object):
    '''
        Rescales the image to a given size.
    '''

    def __init__(self, output_size):
        '''
            Arguments:
            output_size (tuple or int): Desired output size. If tuple, output is
            matched to output_size. If int, smaller of image edges is matched
            to output_size keeping aspect ratio the same.
        '''

        self.output_size = output_size

    def __call__(self, image):
        '''
            Arguments:
            image (numpy array or PIL image)

            Returns:
            image (numpy array or PIL image)

            Note: You do not need to resize the bounding boxes. ONLY RESIZE THE IMAGE.
        '''
        if (type(image).__module__ == np.__name__):
            image = Image.fromarray(image)
        
        if (type(self.output_size) != "tuple"):
            width = image.size[0]
            height = image.size[1]
            aspect = width/height
            
            if (width<height):
                width = self.output_size
                height = (int)(width/aspect)
            else:
                height = self.output_size
                width = (int)(height * aspect)
                
            self.output_size = tuple((width,height))
        
        return image.resize(self.output_size)
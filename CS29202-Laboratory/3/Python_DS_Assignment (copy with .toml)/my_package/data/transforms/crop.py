# Imports
import numpy as np
from PIL import Image

class CropImage(object):
    '''
        Performs either random cropping or center cropping.
    '''

    def __init__(self, shape, crop_type='center'):
        '''
            Arguments:
            shape: output shape of the crop (h, w)
            crop_type: center crop or random crop. Default: center
        '''
        self.shape = shape
        self.crop_type = crop_type


    def __call__(self, image):
        '''
            Arguments:
            image (numpy array or PIL image)

            Returns:
            image (numpy array or PIL image)
        '''
        if (type(image).__module__ == np.__name__):
            image = Image.fromarray(image)

        width = image.size[0]
        height = image.size[1]
        
        if (self.crop_type == "center"):
            (left, upper, right, lower) = (width/2 - self.shape[0]/2, height/2 - self.shape[1]/2, width/2 + self.shape[0]/2, height/2 + self.shape[1]/2)
        elif (self.crop_type == "random"):
            left = np.random.randint(0,width-self.shape[0])
            upper = np.random.randint(0,height-self.shape[1])
            right = left + self.shape[0]
            lower = upper + self.shape[1]
            
        return image.crop((left, upper, right, lower))
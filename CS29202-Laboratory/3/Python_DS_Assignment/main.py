#Imports
from my_package import analysis
from my_package.model import InstanceSegmentationModel
from my_package.data import Dataset
from my_package.analysis import plot_visualization
from my_package.data.transforms import FlipImage, RescaleImage, BlurImage, CropImage, RotateImage
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

def experiment(annotation_file, segmentor, transforms, outputs):
    '''
        Function to perform the desired experiments

        Arguments:
        annotation_file: Path to annotation file
        segmentor: The image segmentor
        transforms: List of transformation classes
        outputs: path of the output folder to store the images
    '''

    #Create the instance of the dataset.
    exp_dataset = Dataset(annotation_file,transforms)

    #Iterate over all data items.
    #Get the predictions from the segmentor.
    for data_row in exp_dataset:
        pred_boxes, pred_masks, pred_class, pred_score = segmentor(data_row['image'])
        #Draw the segmentation maps on the image and save them.
        plot_visualization(data_row['image'],pred_boxes,pred_masks,pred_class,outputs)

    #Do the required analysis experiments.
    analysis_im = Image.open('./output/output_6.png','r')
    fig, axs = plt.subplots(7,figsize=(50,37))
    fig.suptitle('Subplots from Analysis Step')

    axs[0].imshow(analysis_im)
    axs[0].set_title('Original image with segmentation masks')

    obj1 = FlipImage(flip_type='horizontal')
    axs[1].imshow(obj1(analysis_im))
    axs[1].set_title('Horizontal Flip')

    obj2 = BlurImage(radius = 1)
    axs[2].imshow(obj2(analysis_im))
    axs[2].set_title('Blurred')

    obj3 = RescaleImage((int)(analysis_im.size[0] * 2))
    axs[3].imshow(obj3(analysis_im))
    axs[3].set_title('Rescaled to 2X')

    obj4 = RescaleImage((int)(analysis_im.size[0] * 0.5))
    axs[4].imshow(obj4(analysis_im))
    axs[4].set_title('Rescaled to 0.5X')

    obj5 = RotateImage(90)
    axs[5].imshow(obj5(analysis_im))
    axs[5].set_title('Rotated 90 degrees')

    obj6 = RotateImage(45)
    axs[6].imshow(obj6(analysis_im))
    axs[6].set_title('Rotated 45 degrees')

    fig.savefig('./output_subplot.png')


def main():
    segmentor = InstanceSegmentationModel()
    experiment('./data/annotations.jsonl', segmentor, [BlurImage(0)], './output') 


if __name__ == '__main__':
    main()

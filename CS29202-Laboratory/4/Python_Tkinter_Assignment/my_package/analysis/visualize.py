#Imports
import numpy as np
from PIL import Image,ImageDraw, ImageFont

def plot_visualization(image,bboxes,masks,classes,output_folder): # Write the required arguments

  # The function should plot the predicted segmentation maps and the bounding boxes on the images and save them.
  # Tip: keep the dimensions of the output image less than 800 to avoid RAM crashes.
    if not hasattr(plot_visualization, "name_counter"):
      plot_visualization.name_counter = 0
    image1 = image.copy()
    image2 = image.copy()
    counter = 0
    for mask in masks:
      if(counter>=3):
        break
      counter = counter + 1

      mask = np.where(mask<0.5,0,image1[counter-1])
      image1[counter-1,:,:]=np.where(mask<0.05,image1[counter-1,:,:],1)

    image1 = Image.fromarray((image1.transpose((1,2,0))*255).astype(np.uint8))
    image1.save(output_folder+'/output_mask_temp'+'.png',"PNG")

    image2 = Image.fromarray((image2.transpose((1,2,0))*255).astype(np.uint8))
    counter = 0
    for i in range(len(bboxes)):
      bbox = bboxes[i]
      if(counter>=3):
        break
      counter = counter + 1
      (x0,y0),(x1,y1) = bbox
      img1 = ImageDraw.Draw(image2)  
      img1.rectangle((x0,y0,x1,y1))
      img1.text((x0, y0), str(classes[i]), font=ImageFont.truetype("arial",24))

    image2.save(output_folder+'/output_box_temp'+'.png',"PNG")
    plot_visualization.name_counter = plot_visualization.name_counter + 1
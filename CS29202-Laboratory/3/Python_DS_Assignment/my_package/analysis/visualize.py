#Imports
import numpy as np
from PIL import Image,ImageDraw, ImageFont

def plot_visualization(image,bboxes,masks,classes,output_folder): # Write the required arguments

  # The function should plot the predicted segmentation maps and the bounding boxes on the images and save them.
  # Tip: keep the dimensions of the output image less than 800 to avoid RAM crashes.
    if not hasattr(plot_visualization, "name_counter"):
      plot_visualization.name_counter = 0

    counter = 0
    for mask in masks:
      if(counter>=3):
        break
      counter = counter + 1

      masked_img = np.ones_like(image)
      mask = np.where(mask<0.5,0,1)
      masked_img[0,:,:]=mask
      masked_img[1,:,:]=mask
      masked_img[2,:,:]=mask
      image = np.where(masked_img == 1,0,image)

    image = Image.fromarray((image.transpose((1,2,0))*255).astype(np.uint8))

    counter = 0
    for i in range(len(bboxes)):
      bbox = bboxes[i]
      if(counter>=3):
        break
      counter = counter + 1
      (x0,y0),(x1,y1) = bbox
      img1 = ImageDraw.Draw(image)  
      img1.rectangle((x0,y0,x1,y1))
      img1.text((x0, y0), str(classes[i]), font=ImageFont.truetype("arial"))

    image.save(output_folder+'/output_'+str(plot_visualization.name_counter)+'.png',"PNG")
    plot_visualization.name_counter = plot_visualization.name_counter + 1

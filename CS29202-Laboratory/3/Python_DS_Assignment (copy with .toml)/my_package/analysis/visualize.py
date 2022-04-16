#Imports
from PIL import ImageDraw, ImageFont

def plot_visualization(image,bboxes,output_folder): # Write the required arguments

  # The function should plot the predicted segmentation maps and the bounding boxes on the images and save them.
  # Tip: keep the dimensions of the output image less than 800 to avoid RAM crashes.
    counter = 0
    for bbox in bboxes:
        if(counter>=3):
            break
        counter = counter + 1
        (x0,y0,x1,y1) = bbox[1:]
        img1 = ImageDraw.Draw(image)  
        img1.rectangle((x0,y0,x1,y1))
        img1.text((x1, y1), str(bbox[0]), font=ImageFont.truetype("arial"))

    image.save(output_folder+'/output',"PNG")
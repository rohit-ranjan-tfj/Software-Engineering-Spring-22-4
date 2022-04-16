# Python Tkinter Assignment
# Software Engineering Laboratory
# Name - Rohit Ranjan
# Roll number - 20CS30066

####### REQUIRED IMPORTS FROM THE PREVIOUS ASSIGNMENT #######
from my_package.model import InstanceSegmentationModel
from my_package.data import Dataset
from my_package.analysis import plot_visualization
from my_package.data.transforms import FlipImage, RescaleImage, BlurImage, CropImage, RotateImage
from PIL import Image

####### ADD THE ADDITIONAL IMPORTS FOR THIS ASSIGNMENT HERE #######
import os, shutil
from tkinter import Label, OptionMenu, ttk, Entry, StringVar, Tk, filedialog, END
from PIL import ImageTk, Image

# Define the function you want to call when the filebrowser button is clicked.
def fileClick(clicked, dataset, segmentor):

	####### CODE REQUIRED (START) #######
	# This function should pop-up a dialog for the user to select an input image file.
	# Once the image is selected by the user, it should automatically get the corresponding outputs from the segmentor.
	# Hint: Call the segmentor from here, then compute the output images from using the `plot_visualization` function and save it as an image.
	# Once the output is computed it should be shown automatically based on choice the dropdown button is at.
	# To have a better clarity, please check out the sample video.
	filename = filedialog.askopenfilename(initialdir = ".", title = "Select a File")
	basename = os.path.basename(filename)
	if filename:
		label.configure(text=""+filename)
		e.delete(0,END)
		e.insert(0,label.cget("text"))
		print("%s is being worked upon..." % basename)
		pred_boxes, pred_masks, pred_class, pred_score = segmentor(dataset[int(basename[:-4])]['image'])
		plot_visualization(dataset[int(basename[:-4])]['image'],pred_boxes,pred_masks,pred_class,"./outputs")
	process(clicked)
	####### CODE REQUIRED (END) #######

# `process` function definition starts from here.
# will process the output when clicked.
def process(clicked):

	####### CODE REQUIRED (START) #######
	# Should show the corresponding segmentation or bounding boxes over the input image wrt the choice provided.
	# Note: this function will just show the output, which should have been already computed in the `fileClick` function above.
	# Note: also you should handle the case if the user clicks on the `Process` button without selecting any image file.
	global orig
	global mask
	global box
	global counter
	if (label.cget("text")!="Click the Button to browse the Files"):
		width = 400
		orig = Image.open(label.cget("text"))
		orig = orig.resize((width,int((orig.size[1]/orig.size[0])*width)), Image.ANTIALIAS)
		box = Image.open("./outputs/output_box_temp.png")
		box = box.resize((width,int((box.size[1]/box.size[0])*width)), Image.ANTIALIAS)
		mask = Image.open("./outputs/output_mask_temp.png")
		mask = mask.resize((width,int((mask.size[1]/mask.size[0])*width)), Image.ANTIALIAS)
		if(counter>0):
			panel.config(image='')
			panel1.config(image='')
		img = ImageTk.PhotoImage(orig)
		panel.config(image = img)
		panel.image = img
		img_mask = ImageTk.PhotoImage(mask)
		img_box = ImageTk.PhotoImage(box)
		if(clicked.get()=="Segmentation"):
			panel1.config(image = img_mask)
			panel1.image = img_mask
		else:
			panel1.config(image = img_box)
			panel1.image = img_box
		counter = counter+1
		print("Processing complete.\nOutput is displayed.")
	else:
		print("Select an image file to process using the Browse menu.")
	####### CODE REQUIRED (END) #######


# `main` function definition starts from here.
if __name__=='__main__':
	global counter
	counter=0
	try:
		os.mkdir('./outputs/')
	except:
		pass
	####### CODE REQUIRED (START) ####### (2 lines)
	# Instantiate the root window.
	root = Tk()
	# Provide a title to the root window.
	root.title('Image Viewer GUI v_1.0')
	####### CODE REQUIRED (END) #######

	# Setting up the segmentor model.
	annotation_file = './data/annotations.jsonl'
	transforms = []
	# Instantiate the segmentor model.
	segmentor = InstanceSegmentationModel()
	# Instantiate the dataset.
	dataset = Dataset(annotation_file, transforms=transforms)
	# Declare the options.
	options = ["Segmentation", "Bounding-box"]
	clicked = StringVar()
	clicked.set(options[0])

	####### CODE REQUIRED (START) #######
	# Declare the file browsing button
	ttk.Button(root, text="Browse", command= lambda: fileClick(clicked, dataset, segmentor)).grid(row=0,column=1)
	# Add a Label widget
	label = Label(root, text="Click the Button to browse the Files", font=('Georgia 13'))
	e = Entry(root, width=70)
	e.grid(row=0, column=0)
	e.insert(0,label.cget("text"))
	panel = Label(root, image = "")
	panel.grid(row=3,column=0)
	panel1 = Label(root, image = "")
	panel1.grid(row=3,column=4)
	####### CODE REQUIRED (END) #######

	####### CODE REQUIRED (START) #######
	# Declare the drop-down button
	drop = OptionMenu( root , clicked , *options )
	drop.grid(row=0,column=2)
	####### CODE REQUIRED (END) #######

	# This is a `Process` button, check out the sample video to know about its functionality
	ttk.Button(root, text="Process", command= lambda: process(clicked)).grid(row=0,column=3)

	####### CODE REQUIRED (START) ####### (1 line)
	# Execute with mainloop()
	root.mainloop()
	####### CODE REQUIRED (END) #######
	try:
		shutil.rmtree('./outputs/')
	except:
		pass
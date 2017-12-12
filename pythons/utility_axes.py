#!/usr/bin/python
######################################################################
# Name:         ALaDyn_plot_utilities_axes.py
# Author:
# Date:			2014-05-05
# Purpose:      it saves ALaDyn outputs in ASCII format
# Source:       python
#####################################################################

### ---------------------------------------------------- ###
### loading shell commands
import os, os.path, sys
###>>>
home_path = os.path.expanduser('~')
sys.path.append(os.path.join(home_path,'Codes/ALaDyn_Code/tools-ALaDyn/pythons'))
###>>>
### --- ###
from read_ALaDyn_bin import *
from utilities_1 import *

### --- ###




def save_moving_window_coordinates(path,frame):

	s='%2.2i'%frame 				#conversion to 2-character-long-string
	file_name = 'Bdenout'+s+'.bin'
	matrix,  x,y,z = read_ALaDyn_bin(path,file_name,'grid')

	#--- axis coordinates of the moving window ---#


	print('saving moving window axes')


	np.savetxt( os.path.join(path,'data','axes',('x_'+('%2.2i'%frame)+'.dat')) ,x,fmt='%15.14e')
	np.savetxt( os.path.join(path,'data','axes',('y_'+('%2.2i'%frame)+'.dat')) ,y,fmt='%15.14e')
	np.savetxt( os.path.join(path,'data','axes',('z_'+('%2.2i'%frame)+'.dat')) ,z,fmt='%15.14e')

	# np.savetxt( os.path.join(path,'data','Moving_window_axes',('moving_window_axes_'+('%2.2i'%frame)+'.dat')) ,np.column_stack([np.array(x),np.array(y),np.array(z)]),fmt=['%15.14e','%15.14e','%15.14e'])

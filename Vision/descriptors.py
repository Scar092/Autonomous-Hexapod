import numpy
import scipy
imlort os


""" This file contains functions to find and recognise
local descriptors on the camera snapshots. Also there are
some functions to test the results (not for users :D). 
The descriptors recognition is based on sift method and
unfortunately of course uses some API."""

def calc_desc (snap_name, resultname):
     if snap_name [-3:] != 'pmg':
          snap = Image.open(snap_name).convert('L')
          snap.save ('snapshot.pgm')
          snap_name = "snapshot.pgm"
     sift = str ("sift "+snap_name+" --output= "+resultname+" --edge-thresh 10 --peak-thresh 5")
     os.system (sift)
     print ("Done! Descriptors in ", resultname)


def read_desc (file):
     desc = loadtxt (file)
     return desc[:,:4], desc[:,4:]


def plot_desc (image, desc, area = False):
     imshow (image)
     if area:
          for i in desc:
               t = arange(0, 0.01, 0.1)*2*pi
               x = i[2]*cos(t)+i[:2][0]
               y = i[2]*sin(t)+i[:2][1]
               plot (x, y, 'b', linewidth=2)
     else:
          plot (desc[:,0], desc[:,1], 'ob')
     axis ('off')


def match (desc1, desc2):
     desc1 = array([d/linalg.norm(d) for d in desc1])
     desc2 = array([d/linalg.norm(d) for d in desc2])
     dist_ratio = 0.6

     decs1_size =decs1.shape
     matchscores = zeros((decs1_size[0], 1), 'int')
     
     decs2t = decs2.T

     for i in range(decs1_size[0]):
          dotprods = dot(decs1[i,:], decs2t)
          dotprods = 0.9999*dotprods

          index = argsort(arccos(dotprods))
          if arccos(dotprods)[index[0]]<dist_ratio*arccos(dotprods)[index[1]]:
               matchscores[i] = int(index[0])
     return matchscores



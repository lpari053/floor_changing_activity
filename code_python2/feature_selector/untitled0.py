import os
import pandas as pd
import numpy as np


data=pd.read_csv('txt_comparaison.txt',header=0,delimiter=';')

data=data.sort_values(by=['topcroissant'])
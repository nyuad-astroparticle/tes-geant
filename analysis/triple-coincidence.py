#Include modules
import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from tqdm import tqdm
from functools import wraps


# Read the files

# Parameters
run         = 'run0'
header      = ['EventID','TrackID','Particle','EnergyDeposited','XPosition','YPosition','ZPosition','LocalTime','Volume']
PROCESSES   = os.cpu_count()-1

# Find the files
foldername  = f'./output'
filenames   = os.listdir(foldername)


def loadfile(filename):
    return pd.read_csv(os.path.join(foldername,filename),skiprows=14,names=header)

def filter(x):
    check_cases = [['physPaddleTop'],['physPaddleBottom'],['physSiliconSubstrate','physSiliconOxide','physSiliconNitride']]
    return all([x['Volume'].isin(keys).any() for keys in check_cases])

def filter_file(file):
    data = file[file.groupby(['EventID','TrackID'])['TrackID'].transform('count')  >= 3]
    data = data[data.groupby(['EventID','TrackID'])['Volume'].transform('nunique') >= 3]
    return data.groupby(['EventID','TrackID']).filter(filter)


def get_muons(data):
    return data.loc[data['Particle'].str.contains('mu') & data['Volume'].str.contains('Silicon')]


    
if __name__=='__main__':
    from multiprocessing import Pool
    def parallel(func, data):
        with Pool(PROCESSES) as p:
            return list(tqdm(p.imap(func, data), total = len(data)))
    
    files           = parallel(loadfile, filenames)
    triple_events   = pd.concat(parallel(filter_file, files))
    events          = pd.concat(parallel(get_muons, files))

    print(len(events.groupby(['EventID','TrackID']))/len(triple_events.groupby(['EventID','TrackID'])))

    energy_data = events.groupby(['EventID','TrackID'])['EnergyDeposited'].sum().reset_index()
    fig = plt.figure(figsize=(10,5))
    ax  = fig.add_subplot(111)
    ax.hist(energy_data.EnergyDeposited,bins=170,color = 'darkred',density=True);

    ax.set_xlim(0,7.5)
    ax.set_xlabel('Energy Deposited on TES Substrate [MeV]')
    ax.set_ylabel('Density')
    plt.savefig('./figure')

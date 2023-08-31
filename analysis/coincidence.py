import  os
import  pandas as pd
from    tqdm import tqdm
import  numpy as np
from    multiprocessing import get_context as context

# Read the files

# Parameters


header      = ['EventID','TrackID','Particle','EnergyDeposited','XPosition','YPosition','ZPosition','LocalTime','Volume', 'Initial Energy', 'Origin Volume', 'MigrantID']
PROCESSES   = os.cpu_count()-1
Pool        = context("fork").Pool

# Find the files
foldername  = f'./build1/output'
os.system(f'rm -rf ./build1/output/.ipynb_checkpoints')
filenames   = os.listdir(foldername)

print(f'Found {len(filenames)} data files in {foldername}')

def parallel(function):
    def inner(input_array):
        # Parallelize excecution them
        with Pool(PROCESSES) as pool:
            output = list(tqdm(pool.imap(function, input_array),total=len(input_array)))
        return output 
    return inner

# Function to load a single file
def loadfile(filename):
    df = pd.read_csv(os.path.join(foldername,filename),skiprows=16,names=header)
    df.insert(0, 'Filename', filename)
    return df


def process_file(file):
    data = file.groupby(['Filename', 'EventID', 'Volume'])['EnergyDeposited'].sum().reset_index()
    data = data[data['EnergyDeposited'] > 0.2]
    data = data.groupby(['Filename', 'EventID'])['Volume'].unique().reset_index()

    tripleEvents = 0
    quadrupleEvents = 0
    tesHits = 0
    
    for line in data.Volume:
        for volume in line:
            if 'Silicon' in volume:
                tesHits += 1
                continue
            
        if not set(line).issuperset({'phys1','phys2','phys4'}): continue
        tripleEvents += 1
        if not tesHits: continue
        quadrupleEvents += 1

    return (tesHits, tripleEvents, quadrupleEvents)

loadfiles           = parallel(loadfile)
process_files       = parallel(process_file)

files               = loadfiles(filenames)
processed           = process_files(files)
processed           = np.array(processed).T

tesHits             = sum(processed[0])
tripleEvents        = sum(processed[1])
quadrupleEvents     = sum(processed[2])

print("TES Hits =", tesHits, "; Triple Coincidences =", tripleEvents, "; Quadruple Coincidences =", quadrupleEvents)
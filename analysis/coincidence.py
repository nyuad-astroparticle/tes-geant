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
foldername  = f'../build1/output'
os.system(f'rm -rf ../build1/output/.ipynb_checkpoints')
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
    return df


def process_file(filename):
    file = loadfile(filename)
    data = file.groupby(['EventID', 'Volume'])['EnergyDeposited'].sum().reset_index()
    data = data[((data.Volume.str.contains('Silicon')) & data.EnergyDeposited > 0.000010) | (data.EnergyDeposited > 0.2)]
    data = data.groupby(['EventID'])['Volume'].unique().reset_index()

    tripleEvents = 0
    quadrupleEvents = 0
    tesHits = 0
    
    for event in data.Volume:
        tesHit = 0
        for volume in event:
            if 'Silicon' in volume:
                tesHit += 1
                break
        tesHits += tesHit
        if not set(event).issuperset({'phys1','phys2','phys4'}): continue
        tripleEvents += 1
        if not tesHit: continue
        quadrupleEvents += 1

    return (tesHits, tripleEvents, quadrupleEvents)

process_files       = parallel(process_file)
processed           = process_files(filenames)
processed           = np.array(processed).T

tesHits             = sum(processed[0])
tripleEvents        = sum(processed[1])
quadrupleEvents     = sum(processed[2])

content = f"TES Hits = {tesHits}; Triple Coincidences = {tripleEvents}; Quadruple Coincidences = {quadrupleEvents}"
print(content)

# Save the content to a file
output_filename = "output_results.txt"
with open(output_filename, "w") as output_file:
    output_file.write(content)

print(f"Results saved to {output_filename}")
# A set of methods and decorators to be used to accellerate processes
import os
from pandas import concat as CONCUT
from multiprocessing import Pool
from tqdm.auto import tqdm

def parallel(function):
    def inner(input_array):
        # Parallelize excecution them
        with Pool(os.cpu_count()-1) as pool:
            output = list(tqdm(pool.imap(function, input_array),total=len(input_array)))
        return output 

    return inner

def concat(function):
    def inner(*args,**kwargs):
        return CONCUT(function(*args,**kwargs))
    
    return inner
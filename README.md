# RAMC
Random Ass Music Creator, for creating randomly generated music in less than a second.
RAMC is a tool written in C for Linux (but should work on other UNIX systems) which utilizes SoX to generating music randomly.  RAMC does not use any AI to generate its music, just randomness at its peak. Although it is extremely random, you do have the choice of selecting its random seed, tempo (notes/beats per second),whether it plays an intro and/or outro beat, how many times it plays an alternative beat in the
middle of the song, if you just want to play the main beat once or twice, the main beat’s length, the range of musical notes, and of course the destination/output file.

## INSTALL (SoX must be installed)
1. Clone the repository & cd into it  
```
git clone https://github.com/CatPeep/RAMC.git && cd RAMC
```  
  
2. Compile (gcc must be installed)  
```
make
```  
  
3. Install (Run as root)  
```
make install
```  
  
## RUNNING
```ramc [option] [argument]``` 

## FULL DOCUMENTATION
```man ramc```


# Neuronal network
***
<b>Short description</b> : This project aims to model a neuron network, implementing different types of neurons (each neuron has its specificities). The simulation must be launched from a terminal and the results can be observed with a Rscript command. Several different options can be entered by the user when executing the program, by writing the command line. It is fully documented with Doxygen and contains unit tests.
Project status : completed.

## Requirements
***
A list of technologies used within the project:
* [doxygen]: Version 1.9.0
* [cmake]: Version 3.10.2
* [Rscript]: Version 3.4.4
* [googletest]: Version 1.10.0

## Installation
***
A little intro about the installation and steps to get appropriate result (without options)
```
$ git clone https://gitlab.epfl.ch/sv_cpp_projects/team_9
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./neuron_network
$ Rscript ../Rasterplots.R spikes.txt
```

### Options and default values
***
The command ./neuron_network -h make visible all possible options for the program, however default parameters are applied for all fields.
* -c (choice for having supplementary output files)
* -m 'b' (model for neuron connection, b for basic, c for constant and o for overdispersed)
* -o "spikes.txt" (output file name)
* -L 20 (mean intensity of a connection)
* -l 10 (mean connectivity between the neurons)
* -p 0.8 (percentage of excitatory neurons in the network) Is replaced by the -T option if it is given. 
* -T "" (repartition of all neuron types) If nothing is given, the parameter -p is used.
* -N 10 000 (number of neurons in the network)
* -t 500 (time of simulation in ms)
* -d 0.05 (small number to define neuron parameters creation)

The option for other files can be launched with the following instructions :
```
$ ./neuron_network -c
$ Rscript ../Rasterplots.R spikes.txt samples.txt parameters.txt
```

### Author rights
***
This code was written by Aline Brunner, Florence Crozat, Justin Mapanao, Claire Payoux.

#### Logo rights
***
[neuronal network](https://www.freepng.fr/png-4j8gg0/)
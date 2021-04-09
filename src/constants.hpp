// * Default parameter values *

#define _END_TIME_ 500
#define _DELTA_T_ .5
#define _NB_ 10000
#define _PERC_ .8
#define _TYPE_ "FS:0.8"
#define _LAMB_ 10
#define _INT_ 20
#define _MOD_ 'b'
#define _DEL_ .05
#define _OPT_ false
#define _DISCHARGE_T_ 30
#define _NB_TEST_ 6
#define _SPIKES_ "spikes"
#define _PARAMETERS_ "parameters"
#define _SAMPLES_ "samples"
#define _PATH_OUTFILE_ "../"
#define _EXTENSION_ ".txt"
#define _PATH_TEST_ "test/"

#define _INIT_V_ -65

#define _EXCIT_W_ 5
#define _EXCIT_FACTOR_ .5

#define _RS_A_ .02
#define _RS_B_ .2
#define _RS_C_ -65.
#define _RS_D_ 8.

#define _IB_A_ .02
#define _IB_B_ .2
#define _IB_C_ -55.
#define _IB_D_ 4.

#define _CH_A_ .02
#define _CH_B_ .2
#define _CH_C_ -50.
#define _CH_D_ 2.

#define _TC_A_ .02
#define _TC_B_ .25
#define _TC_C_ -65.
#define _TC_D_ .05

#define _RZ_A_ .1
#define _RZ_B_ .26
#define _RZ_C_ -65.
#define _RZ_D_ 2.

#define _INHIB_W_ 2
#define _INHIB_FACTOR_ -1

#define _LTS_A_ .02
#define _LTS_B_ .25
#define _LTS_C_ -65.
#define _LTS_D_ 2.

#define _FS_A_ .1
#define _FS_B_ .2
#define _FS_C_ -65.
#define _FS_D_ 2.


// *text messages *

#define _TIME_TEXT_ "Simulation end time"
#define _NEURON_NUMBER_ "Number of neuron in the simulation"
#define _PERCENT_ACTIVE_ "Percentage of exciting neurons.\nNeeds to be between 0 and 1"
#define _TYPE_TEXT_ "Proportion of differents neurons.\nTypes: IB,CH,LTS,FS,TC,RZ the remaining propotion will be RS.\n Sum (including RS) is 1 \n Format is TYPE1:proportion,TYPE2:proportion,..."
#define _LAMBDA_ "Mean connectivity between the neurons"
#define _INTENSITY_ "Mean intensity of a connection"
#define _PRGRM_TEXT_ "Neuron simulation"
#define _OFILE_TEXT_ "Output file name"
#define _MODEL_TEXT_ "Model for neuron connections,'b' for basic, 'c' for constant and 'o' for overdispersed"
#define _D_TEXT_ "Tunable number for neuron parameters creation"
#define _OPTION_TEXT_ "Choice of optional output of supplementary files parameters and sample"

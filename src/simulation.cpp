#include "simulation.hpp"
#include "constants.hpp"
#include <tclap/CmdLine.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

Simulation::Simulation(const std::string& outfile)
    : _time(_END_TIME_), _net( new Network(_MOD_, _NB_, _PERC_, _INT_, _LAMB_, _DEL_)), _outfile(outfile), _options(false) {}

Simulation::Simulation(int argc, char** argv)
    {
        try {
            std::string def (", by default : ");
            std::string ex(" , for instance : ");
            TCLAP::CmdLine cmd(_PRGRM_TEXT_);
            TCLAP::ValueArg<std::string> ofile("o", "outptut", (_OFILE_TEXT_ + def + _SPIKES_ + _EXTENSION_), false, _SPIKES_, "string");
            cmd.add(ofile);
		    std::vector<char> allowed = {'o', 'b', 'c'};
		    TCLAP::ValuesConstraint<char> allowedVals(allowed);
            TCLAP::ValueArg<char> model("m", "model", (_MODEL_TEXT_ + def + _MOD_), false, _MOD_, &allowedVals);
            cmd.add(model);
            TCLAP::ValueArg<std::string> type("T", "type",( _TYPE_TEXT_ + ex + _TYPE_), false, "", "string");
            cmd.add(type);
            TCLAP::ValueArg<double> perc("p", "p_E",( _PERCENT_ACTIVE_ + ex + std::to_string(_PERC_)), false, _PERC_, "double");
            cmd.add(perc);
            TCLAP::ValueArg<double> delta("d", "delta", (_D_TEXT_ + def + std::to_string(_DEL_)), false, _DEL_, "double");
            cmd.add(delta);
            TCLAP::ValueArg<double> inten("L", "intensity", (_INTENSITY_ + def + std::to_string(_INT_)), false, _INT_, "double");
            cmd.add(inten);
            TCLAP::ValueArg<double> lambda("l", "lambda", (_LAMBDA_ + def + std::to_string(_LAMB_)), false, _LAMB_, "double");
            cmd.add(lambda);
            TCLAP::ValueArg<int> time("t", "time", (_TIME_TEXT_ + def + std::to_string(_END_TIME_)), false, _END_TIME_, "int");            
            cmd.add(time);
            TCLAP::ValueArg<int> number("N", "number", (_NEURON_NUMBER_ + def + std::to_string(_NB_)), false, _NB_, "int");
            cmd.add(number);
            TCLAP::SwitchArg option("c", "options", (_OPTION_TEXT_ + def + _SAMPLES_ + _EXTENSION_ + " and " + _PARAMETERS_ + _EXTENSION_), false);
            cmd.add(option);
            cmd.parse(argc, argv);

            if(time.getValue() <= 0) throw std::domain_error("The running time of the simulation must be positive and greater than 0");
            if(number.getValue() <= 0) throw std::domain_error("The number of neuron must be positive or greater than 0");
            if(lambda.getValue() < 0) throw std::domain_error("The mean connection between neurons must be positive and not exceed the number of neuron");
            if(inten.getValue() <= 0) throw  std::domain_error("The mean intensity of a connection must be positive and greater than 0");
            
            if ((number.getValue()*lambda.getValue()) > 1e8) throw std::domain_error("The computer probably won't have the memory necessary to deal with a network as large as this one. "
                                                                                      "Please reduce the number of neurons or the mean connectivity (lambda)");
            _time = time.getValue();
            _options = option.getValue();
            std::string filename(ofile.getValue());
            _filename = ofile.getValue();
            if (filename.find(_EXTENSION_, (filename.size() - 4)) == std::string::npos) {
                _filename += _EXTENSION_;
            }
            if (argc == 1) {
                std::cerr << "Warning : For information on the usage of this program type ./neuron_network -h in the command line" << std::endl;
            }
            double tmp = (number.getValue() - 1);
            if (lambda.getValue() > tmp) {
                std::cerr << "Warning: The value of lambda must be strictly less than the number of neurons. "
                             "The value of lambda has been replaced by " << tmp << "." << std::endl;
            }
            if(delta.getValue() < 0 or delta.getValue() > 1) {
                throw std::domain_error("The value of delta should be between 0 and 1");
            }  
            if(type.isSet() and perc.isSet()) {
                throw std::domain_error("Only the percentage of excitating neurons (p) or the proportion of different types (T) should be given");
            }
            else if (perc.isSet() or (not perc.isSet() and not type.isSet())) {
                _net = new Network(model.getValue(), number.getValue(), perc.getValue(), inten.getValue(),
                                   std::min(lambda.getValue(), tmp), delta.getValue());
                if (_options) {
                    initializeSample(perc.getValue());
                }
            } 
            else if(type.isSet()) {
                double FS(0), IB(0), RZ(0), LTS(0), TC(0), CH(0);
                readLine(type.getValue(), FS, IB, RZ, LTS, TC, CH);
                _net = new Network(model.getValue(), number.getValue(), FS, IB, RZ, LTS, TC, CH,inten.getValue(),
                                    std::min(lambda.getValue(), tmp), delta.getValue());
                if (_options) {
                    initializeSample(FS, LTS, IB, RZ, TC, CH);
                }
            }
            _outfile.open(_filename);
            
        } catch(const std::exception& e) {
            std::cerr << e.what() << std::endl;
            throw e;
        }
    } 

Simulation::~Simulation() {
    delete _net;
}

int Simulation::run() {
    time_t ex_time = time(NULL);
    struct tm * ptm;
    double running_time(0);
    int index = 1;
    if (_options) {
        std::ofstream samples;
        std::string file = _SAMPLES_;
        samples.open(file + _EXTENSION_, std::ios::app);
        while (running_time < _time) {
            running_time += 2*_DELTA_T_;
            _net->update();
            print(index);
            samples << index;
            samplePrint(samples);
            index += 1;
        }
        samples.close();
        paramPrint();
    } 
    else {
        while (running_time < _time) {
            running_time += 2*_DELTA_T_;
            _net->update();
            print(index);
            index += 1;
        }
    }
    _outfile.close();
    ex_time = time(NULL);
    ptm = gmtime(&ex_time);
    return ptm->tm_sec;
}

void Simulation::print(int index) {
    std::ostream *outstr = &std::cout;
    if (_outfile.is_open()){
        outstr = &_outfile;
    } 
    std::vector<bool> matrix = _net->getCurrentstatus();
    *outstr << index << " "; 
    for(auto neuron : matrix) {
        *outstr << neuron << " ";
    }
    *outstr << "\n";
}

void Simulation::paramPrint() {
    std::ostream *outstr = &std::cout;
    std::ofstream param;
    std::string file = _PARAMETERS_;
    param.open(file + _EXTENSION_);
    if (param.is_open()) {
        outstr = &param;
    }
    std::vector<Neuron*> netw(_net->getNet());
    std::vector<std::map<Neuron*, double>> con(_net->getCon());
    std::vector<double> attributs;
    int inhib(0);
    *outstr << "\t a\t b\t c\t d\t Inhibitory\t degree\t valence\n";
    for(size_t i(0); i<netw.size(); ++i) {
        attributs = netw[i]->getAttributs();
        *outstr << netw[i]->getType()<< "\t ";
        for (size_t j(0); j<attributs.size(); ++j) {
            *outstr << attributs[j] << "\t";
        }
        if (netw[i]->getW() == 2) {
            inhib = 1;
        }
        else {
            inhib = 0;
        }
        *outstr << inhib << "\t" << con[i].size() << "\t" << _net->getValence(i) << "\n";
    }
    param.close();
}

void Simulation::samplePrint(std::ofstream& file) {
    std::ostream *outstr = &std::cout; 
    if (file.is_open()) {
        outstr = &file;
    }
    std::vector<double> attributs;
    for (size_t k(0); k < _net->getNeuronsOutput().size(); k++) {
        if (_net->getNeuronsOutput()[k] != nullptr) {
            attributs = (_net->getNeuronsOutput()[k])->getVariables();
            for (size_t j(0); j < attributs.size(); ++j) {
                *outstr << "\t" << attributs[j];
            }
        }
    }
    *outstr << "\n";
}

void Simulation::readLine(std::string& line,  double& fs, double& ib, double& rz, double& lts, double& tc, double& ch) 
{
    std::string value, key;
    line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
    std::stringstream ss(line);
    while (std::getline(ss, key, ':')) {
        if (key.empty()) continue;
        std::getline(ss, value, ',');
        std::transform(key.begin(), key.end(), key.begin(), ::toupper);
        if (key == "FS") fs = stod(value);
        if (key == "LTS") lts = stod(value);
        if (key == "IB") ib = stod(value);
        if (key == "RZ") rz = stod(value);
        if (key == "TC") tc = stod(value);
        if (key == "CH") ch = stod(value);
    }
    if ((fs+ib+rz+lts+tc+ch) > 1 + 1e-10) {
        throw std::logic_error("The sum of all proportions is greater than 1");
    }
}

void Simulation::initializeSample(double p_E)
{
    std::ofstream samples;
    std::string file = _SAMPLES_;
    samples.open(file + _EXTENSION_); 
    if (p_E == 0) {
        samples << "FS.v\t FS.u\t FS.I\n";
    } else if (p_E == 1) {
        samples << "RS.v\t RS.u\t RS.I\n";
    } else {
        samples << "FS.v\t FS.u\t FS.I\t RS.v\t RS.u\t RS.I\n";
    }
    samples.close();
}

void Simulation::initializeSample(double p_FS, double p_LTS, double p_IB, double p_RZ, double p_TC, double p_CH)
{
    std::ofstream samples;
    std::string file = _SAMPLES_;
    samples.open(file + _EXTENSION_);
    std::string headers;
    if (p_FS > 0) {
        headers += "FS.v\t FS.u\t FS.I";
    }
    if (p_LTS > 0) {
        headers += "\t LTS.v\t LTS.u\t LTS.I";
    }
    if (p_IB > 0) {
        headers += "\t IB.v\t IB.u\t IB.I";
    }
    if (p_RZ > 0) {
        headers += "\t RZ.v\t RZ.u\t RZ.I";
    }
    if (p_TC > 0) {
        headers += "\t TC.v\t TC.u\t TC.I";
    }
    if (p_CH > 0) {
        headers += "\t CH.v\t CH.u\t CH.I";
    }
    if ((p_FS + p_IB + p_RZ + p_LTS + p_TC + p_CH) < 1 - 1e-10) {
        headers += "\t RS.v\t RS.u\t RS.I";
    }
    headers += "\n";
    samples << headers;
    samples.close();
}

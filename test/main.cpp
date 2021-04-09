#include <gtest/gtest.h>
#include "../src/random.hpp"
#include "../src/simulation.hpp"
#include "../src/constants.hpp"
#include "../src/excitatoryNeuron.hpp"
#include "../src/inhibitoryNeuron.hpp"
#include <cmath>
#include <vector>
#include <map>
#include <fstream>
#include <string>

Random* _RNG = new Random(23948710923);

TEST(Random, distributions) {
    double mean = 0;
    double input_mean(1.35), input_sd(2.8);
    std::vector<double> res;
    res.resize(10000);
    double delta = input_sd*sqrt(3.0);
    double lower = input_mean-delta, upper = input_mean+delta;
    _RNG->uniform_double(res, lower, upper);
    for (auto I : res) {
        EXPECT_GE(I, lower);
        EXPECT_LT(I, upper);
        mean += I*1e-4;
    }
    EXPECT_NEAR(input_mean, mean, 3e-2*input_sd);
    _RNG->normal(res, input_mean, input_sd);
    mean = 0;
    for (auto I : res) mean += I*1e-4;
    EXPECT_NEAR(input_mean, mean, 2e-2*input_sd);
    _RNG->poisson(res, input_mean);
    mean = 0;
    for (auto I : res) mean += I*1e-4;
    EXPECT_NEAR(input_mean, mean, 2e-2*input_mean);
}

TEST(Network, connections) {
    Network net(_MOD_, _NB_TEST_, _PERC_, _INT_, _LAMB_, _DEL_);
    std::vector<Neuron*> netw(net.getNet());
    std::vector<std::map<Neuron*, double>> con(net.getCon());

    //test création Network
    EXPECT_FALSE(netw.empty());
    EXPECT_FALSE(con.empty());

    //test bon nombre neurones crées
    EXPECT_EQ(_NB_TEST_, netw.size());
    EXPECT_EQ(con.size(), netw.size());

    //test association map/neurone
    int problems(0);
    for (size_t i(0); i<netw.size(); ++i) {
        for (auto pair : con[i]) {
            if(pair.first == netw[i]) ++problems;
        }   
    }
    EXPECT_EQ(problems, 0);

    //test pas nullptr
    int sumNull(0);
    for (size_t i(0); i<netw.size(); ++i) {
        if (netw[i]==nullptr) ++sumNull;
    }
    EXPECT_EQ(sumNull, 0);
    sumNull = 0;
    for (size_t i(0); i<con.size(); ++i) {
        for (auto& pair : con[i]) {
            if (pair.first == nullptr) ++sumNull;
        }
    }
    EXPECT_EQ(sumNull, 0);
    
}

TEST(Network, current) {
    Network net(_MOD_, _NB_TEST_, _PERC_, _INT_, _LAMB_, _DEL_);
    double variables = 0.0;
    double variables_updated = 0.0;
    for(size_t i(0); i<net.getNet().size(); ++i) {
        if(net.getNet()[i]->isFiring()) {
            for (auto link : net.getCon()[i]) {
                variables = link.first->getVariables().back();
                net.synapticCurrent(i);
                variables_updated = link.first->getVariables().back();
                EXPECT_FALSE(variables == variables_updated);
            }
        }
    }
}

TEST(Simulation, output) {
    Simulation sim(_SPIKES_);
    int result = sim.run();
    EXPECT_LE(result, 60);

    std::ifstream myfile;
    std::string print;

    myfile.open(_SPIKES_);
    if (myfile.is_open()) {
        EXPECT_FALSE(myfile.eof());
        int i(0);
        while (std::getline(myfile, print)) {
            print.erase(print.begin(), print.begin() + print.find(' '));
            print.erase(std::remove_if(print.begin(), print.end(), isspace), print.end());
            i += 1;
            EXPECT_EQ(print.size(), _NB_);
            for(auto neuron : print) {
                EXPECT_TRUE(neuron == '1' or neuron == '0');
            }
        }
        EXPECT_EQ(i, _END_TIME_);
    }

    myfile.close();
}

TEST(Simulation, readLine) {
    Simulation sim(_SPIKES_);
    double FS(0.), IB(0.), RZ(0.), LTS(0.), TC(0.), CH(0.);
    std::string proportions = "FS:0.1, IB:0.2, RZ:0.1, LTS:0.1, TC:0.2, CH:0.1";
    sim.readLine(proportions, FS, IB, RZ, LTS, TC, CH);
    EXPECT_NE(FS, 0);
    EXPECT_NE(IB, 0);
    EXPECT_NE(RZ, 0);
    EXPECT_NE(LTS, 0);
    EXPECT_NE(TC, 0);
    EXPECT_NE(CH, 0);

}

TEST(Neuron, attributs){
    double r=1.0;
    ExcitatoryNeuron* excitatory_RS = new ExcitatoryNeuron(r, "RS");
    ExcitatoryNeuron* excitatory_IB = new ExcitatoryNeuron(r, "IB");
    ExcitatoryNeuron* excitatory_CH = new ExcitatoryNeuron(r, "CH");
    InhibitoryNeuron* inhibitory_LTS = new InhibitoryNeuron(r, "LTS");
    InhibitoryNeuron* inhibitory_FS = new InhibitoryNeuron(r, "FS");
    std::vector<double> excit_attributs_RS = {_RS_A_, _RS_B_, _RS_C_, _RS_D_};
    std::vector<double> excit_attributs_IB = {_IB_A_, _IB_B_, _IB_C_, _IB_D_};
    std::vector<double> excit_attributs_CH = {_CH_A_, _CH_B_, _CH_C_, _CH_D_};
    std::vector<double> inhib_attributs_LTS = {_LTS_A_, _LTS_B_, _LTS_C_, _LTS_D_};
    std::vector<double> inhib_attributs_FS = {_FS_A_, _FS_B_, _FS_C_, _FS_D_};
    for(size_t i(0);i<excit_attributs_RS.size();++i){
        EXPECT_NEAR(excitatory_RS->getAttributs()[i], excit_attributs_RS[i], std::abs(excit_attributs_RS[i]*r));
        EXPECT_NEAR(excitatory_IB->getAttributs()[i], excit_attributs_IB[i], std::abs(excit_attributs_IB[i]*r));
        EXPECT_NEAR(excitatory_CH->getAttributs()[i], excit_attributs_CH[i], std::abs(excit_attributs_CH[i]*r));
        EXPECT_NEAR(inhibitory_LTS->getAttributs()[i], inhib_attributs_LTS[i], std::abs(inhib_attributs_LTS[i]*r));
        EXPECT_NEAR(inhibitory_FS->getAttributs()[i], inhib_attributs_FS[i], std::abs(inhib_attributs_FS[i]*r));
    }
}

TEST(Neuron, update){
    double r=0.5;
    ExcitatoryNeuron* excitatory = new ExcitatoryNeuron(r);
    InhibitoryNeuron* inhibitory = new InhibitoryNeuron(r);
    std::vector<double> excit_variablesInitial = excitatory->getVariables();
    std::vector<double> inhib_varaiblesInitial = inhibitory->getVariables();
    excitatory->update();
    inhibitory->update();
    for(size_t i(0); i < (excit_variablesInitial.size()-1); ++i){
        EXPECT_NE(excit_variablesInitial[i], excitatory->getVariables()[i]);
        EXPECT_NE(inhib_varaiblesInitial[i], inhibitory->getVariables()[i]);
    }
}

int main(int argc,char **argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
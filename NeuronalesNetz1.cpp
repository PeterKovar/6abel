/*Programm Neuronales Netz
  (c) KOVA 24.04.2024*/
# include <iostream>
//Neuronenklasse
class Neuron{
  public:
    double weight; //Neuronenbeitrag
    double output;
    Neuron() : weight(0.5), output(0.0) {}
};
//Layerklasse
class Layer{
  public:
    Neuron *neurons;  // Zeiger auf die Neuronenklasse
    int numNeurons;   // Anzahl der Neuronen
    int numInputs;    // Anzahl der Eingaenge
    Layer() {}
    void makeNeurons() {
        neurons = new Neuron[numNeurons]; //Neuronen erzeugen
    }
    ~Layer() {        // Destruktor
        delete[] neurons;  //Speicher freigeben
    }
};

class NeuronNet{
  public:
    Layer *layers;
    int numLayers;
    NeuronNet(int *layer_struc, int maxLayer){
       numLayers = maxLayer;
       //Layers erzeugen
       layers = new Layer [numLayers];
       //Neuronen in den einzelnen Layer erzeugen
       for (int i=0; i<numLayers; ++i); {
        layers[i].numNeurons = layer_struc[i]; //Anzahl Neuronen über übernehmen
        layers[i].makeNeurons(); //Neuronen erzeugen
        if (i==0) layers[i].numInputs = 0; //Layer 0 kein Input
        else layers[i].numInputs = layers[i-1].numNeurons;
       }
    }
    ~NeuronNet(){
      delete [] layers;   //Speicher freigeben
    }
    void forward (double *input) {

    }
     
};


int main(int argc, char **argv) {

    int layer_struc[] = {2, 3, 1};
    std::cout << sizeof(layer_struc)/sizeof(int) << "\n";
    NeuronNet net(layer_struc, sizeof(layer_struc)/sizeof(int));
    double input [] = {0.5, 0.8};
    //Forward durchführen
    net.forward(input);
    return 0;
}
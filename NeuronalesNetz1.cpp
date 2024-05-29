/*Programm Neuronales Netz
  (c) KOVA 24.04.2024*/
# include <iostream>
# include <cmath>
double sigmod(double s) {
  return 1.0 / (1.0 + exp(-s));
}
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
       for (int i=0; i<numLayers; ++i) {
        layers[i].numNeurons = layer_struc[i]; //Anzahl Neuronen über übernehmen
        layers[i].makeNeurons(); //Neuronen erzeugen
        if (i==0) layers[i].numInputs = 0; //Layer 0 kein Input
        else layers[i].numInputs = layers[i-1].numNeurons;
       }
    }
    ~NeuronNet(){
      delete [] layers;   //Speicher freigeben
    }
    //Vorwaertsfunktion
    void forward (double *input) {
        // Setzen der Werte in den Eingangslayer
        for (int i=0;i<layers[0].numNeurons; ++i){
          layers[0].neurons[i].output = input[i];
        }
        //Berechnen der Ausgaben für jede Schicht
        for(int i=1; i < numLayers; ++i) {
          for(int j=0; j<layers[i].numNeurons; ++j){
            double sum = 0.0;
            for (int k=0; k < layers[i].numInputs; ++k) {
              //Alle Eing. mit dem Gewicht mult. und summieren
              sum += layers[i-1].neurons[k].output *
                     layers[i].neurons[j].weight;
            }
            layers[i].neurons[j].output = sigmod(sum);
          }
        }
    }
     
};


int main(int argc, char **argv) {

    int layer_struc[] = {2, 3, 1};
    //std::cout << sizeof(layer_struc)/sizeof(int) << "\n";
    NeuronNet net(layer_struc, sizeof(layer_struc)/sizeof(int));
    double input [] = {0.5, 0.8};
    //Forward durchführen
    net.forward(input);
    std::cout << net.layers[2].neurons[0].output;
    return 0;
}

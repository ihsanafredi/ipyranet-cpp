/**
 * ipyranet-cpp
 * 
 * Copyright (C) 2012 Alessio Placitelli
 *
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without 
 * restriction, including without limitation the rights to use, 
 * copy, modify, merge, publish, distribute, sublicense, and/or sell 
 * copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _IPyraNet1DLayer_h_
#define _IPyraNet1DLayer_h_

#include "IPyraNetLayer.h"
#include <vector>

template<class OutType>
class IPyraNet1DLayer : public IPyraNetLayer<OutType> {
public:
    
    IPyraNet1DLayer();
    IPyraNet1DLayer(int numberNeurons, IPyraNetActivationFunction<OutType>* activationFunc = NULL);
    virtual ~IPyraNet1DLayer();
    
    LayerType getLayerType() const { return Layer1D; }
    OutType getErrorSensitivity(int dimensions, int* neuronLocation, OutType multiplier);
    OutType getNeuronOutput(int dimensions, int* neuronLocation);    
    int getDimensions() const;
    void getSize(int* size);

    OutType getNeuronWeight(int dimensions, int* neuronLocation);
    void setNeuronWeight(int dimensions, int* neuronLocation, OutType value);
    OutType getNeuronBias(int dimensions, int* neuronLocation);
    void setNeuronBias(int dimensions, int* neuronLocation, OutType value);

    void setParentLayer(IPyraNetLayer<OutType>* parent, bool init);

    void saveToXML(pugi::xml_node& node);
    void loadFromXML(pugi::xml_node& node);

private:
    unsigned int neurons;    // number of neurons (size of the layer in 1D)

    // in 1D layers weights are per-connection, not per neuron.
    // so we have a inputs * neurons weights
    std::vector<std::vector<OutType> > weights;

    // one bias per neuron/output
    std::vector<OutType> biases;

    OutType getWeightedSumInput(int dimensions, int* neuronLocation);
    void initWeights();
    void initBiases();
};

#endif // _IPyraNet1DLayer_h_
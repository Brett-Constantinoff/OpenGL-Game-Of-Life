#include "LayerStack.h"

LayerStack::LayerStack(){

}

LayerStack::~LayerStack(){
    for(Layer* layer : m_layers){
        delete layer;
    }
}

void LayerStack::push(Layer* layer){
    layer->onAttach();
    m_layers.insert(m_layers.begin(), layer);
}

void LayerStack::pop(){
    m_layers[m_layers.size() - 1]->onDetach();
    m_layers.pop_back();
}
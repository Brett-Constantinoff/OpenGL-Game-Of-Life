#include "LayerStack.h"

LayerStack::LayerStack()
{

}

//cleanup
LayerStack::~LayerStack()
{
    for(Layer* layer : m_layers){
        delete layer;
    }
}

void LayerStack::push(Layer* layer, Window* win)
{
    layer->onAttach(win);
    m_layers.insert(m_layers.begin(), layer);
}

void LayerStack::pop()
{
    m_layers[m_layers.size() - 1]->onDetach();
    m_layers.pop_back();
}
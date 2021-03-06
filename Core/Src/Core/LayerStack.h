#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#include <vector>
#include "Layer.h"
#include "Window.h"

class LayerStack
{
    public:
        LayerStack();
        ~LayerStack();

        void push(Layer* layer, Window* win);
        void pop();

        std::vector<Layer*>::iterator begin() {
            return m_layers.begin();
        }
        std::vector<Layer*>::iterator end(){
            return m_layers.end();
        }

        private:
            std::vector<Layer*> m_layers;
};

#endif
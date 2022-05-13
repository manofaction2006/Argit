#include "pch.h"
#include "LayerStack.h"
#include <algorithm>

namespace Argit {
	LayerStack::LayerStack(): m_layers({})
	{

	}

	void LayerStack::PushLayerBack(const Reference<Layer>& layer)
	{
		m_layers.push_back(layer);
		layer->OnAttach();
	}
	void LayerStack::PopLayerBack()
	{
		(*m_layers.end())->OnDetach();
		m_layers.pop_back();
	}

	void LayerStack::Push(const Reference<Layer>& layer, uint32_t index)
	{
		std::vector<Reference<Layer>>::iterator i;
		std::advance(i, index);
		m_layers.insert(i, layer);
		layer->OnAttach();
	}
	void LayerStack::Pop(const Reference<Layer>& layer)
	{
		std::vector<Reference<Layer>>::iterator i = std::find(m_layers.begin(), m_layers.end(), layer);
		m_layers.erase(i);
		layer->OnDetach();
	}

	void LayerStack::UpdateAllLayers(float deltaTime)
	{
		std::for_each(m_layers.rbegin(), m_layers.rend(), [&](Reference<Layer> elem) {
			elem->OnUpdate(deltaTime);
		});
	}
	void LayerStack::PassEventToAllLayers(Event& e)
	{
		std::for_each(m_layers.rbegin(), m_layers.rend(), [&](Reference<Layer> elem) {
			elem->OnEvent(e);
		});
	}

	LayerStack::~LayerStack()
	{
		std::for_each(m_layers.rbegin(), m_layers.rend(), [&](Reference<Layer> elem) {
			elem->OnDetach();
		});
		m_layers.clear();
	}

}
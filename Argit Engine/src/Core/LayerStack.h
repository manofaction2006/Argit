#pragma once
#include "Base.h"
#include "Layer.h"
#include <vector>

namespace Argit {
	class LayerStack final {
	public:
		LayerStack();

		void PushLayerBack(const Reference<Layer>& layer);
		void PopLayerBack();

		void Push(const Reference<Layer>& layer, uint32_t index);
		void Pop(const Reference<Layer>& layer);

		void UpdateAllLayers(float deltaTime);
		void PassEventToAllLayers(Event& e);

		~LayerStack();
	private:
		std::vector<Reference<Layer>> m_layers;
	};
}
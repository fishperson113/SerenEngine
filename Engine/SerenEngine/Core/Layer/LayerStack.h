#pragma once
#include "Layer.h"
#include"Core/Type/RTTI.h"
namespace SerenEngine
{
	using LayerList = std::vector<Layer*>;
	class SEREN_API LayerStack
	{
	public:
		DECLARE_RTTI

		class SEREN_API ReversedIterator {
		public:
			ReversedIterator() = default;
			explicit ReversedIterator(LayerList::reverse_iterator iter) : mCurrentIter(iter) {
			}
			ReversedIterator& operator++() {
				++mCurrentIter;
				return *this;
			}
			ReversedIterator& operator--() {
				--mCurrentIter;
				return *this;
			}
			bool operator!=(const ReversedIterator& other) const {
				return mCurrentIter != other.mCurrentIter;
			}
			Layer* operator*() const { return *mCurrentIter; }
			Layer* operator->() const { return *mCurrentIter; }
		private:
			LayerList::reverse_iterator mCurrentIter;
		};

	public:
		LayerStack();
		~LayerStack();

		void Push(Layer* layer);
		void PushOverlay(Layer* layer);
		void Pop(Layer* layer);
		void PopOverlay(Layer* layer);

		LayerList::iterator begin() { return mLayers.begin(); }
		LayerList::iterator end() { return mLayers.end(); }
		ReversedIterator rbegin() { return ReversedIterator(mLayers.rbegin()); }
		ReversedIterator rend() { return ReversedIterator(mLayers.rend()); }
	private:
		LayerList mLayers;
		uint8_t mIndex;
	};
}
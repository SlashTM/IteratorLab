#include "List.h"

ListIterator* List::createIterator(Iterators it_, bool (*predicate_)(int)) const
{
	if (it_ == Iterators::PREDICATE)
		return new ListIteratorPredicate(this, predicate_);
	return nullptr;
}

ListIterator* List::createIterator(Iterators it_, const int step_) const {
	if (it_ == Iterators::STEP)
		return new ListIteratorStep(this, step_);
	if (it_ == Iterators::VALUE)
		return new ListIteratorValue(this, step_);
	return nullptr;
}
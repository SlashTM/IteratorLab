#pragma once
#include <list>
using namespace std;
class ListIterator;

enum class Iterators {
	STEP,
	VALUE,
	PREDICATE
};

class List
{
public:
	list <int> list_;
	list <int>::iterator rear;
public:
	friend class ListIterator;

	List(size_t aSize) {
		list_.resize(aSize);
		rear = list_.begin();
	}

	virtual ~List() {}

	bool append(int a) {
		if (rear == list_.end())
			return false;
		list_.emplace(rear, a);
		rear++;
		if (rear == list_.end()){
			list <int>::iterator temp = rear;
			temp--;
			list_.erase(temp);
			return true;
		}
		list <int>::iterator del = rear;
		del++;
		list_.erase(rear);
		rear = --del;
		return true;
	}

	bool remove() {
		if (rear == list_.begin())
			return false;
		list_.erase(--rear);
		list_.resize(list_.size() + 1);
		return true;
	}
	ListIterator* createIterator(Iterators it_, const int step_) const;
	
	ListIterator* createIterator(Iterators it_, bool (*predicate_)(int)) const;
};

class ListIterator
{
protected:
	friend class List;
	const List* List_;
	list <int>::iterator temp;
	virtual int currentValue()
	{
		return *(temp);
	}
	virtual bool first() = 0;
	virtual bool next() = 0;
public:
	ListIterator(const List* aList) : List_(aList), temp(List_->rear)
	{
		if (List_->rear != List_->list_.begin())
		{
			temp--;
			if (List_->rear == List_->list_.end())
				temp--;
		}
		else
			throw exception("Error. List is empty.");

	}
	bool operator++()
	{
		return next();
	}
	int operator*()
	{
		return currentValue();
	}
	bool operator()()
	{
		return first();
	}
};

class ListIteratorStep : public ListIterator
{
private:
	int step;

	bool first() override {
		temp = List_->rear;
		temp--;
		auto i = 0;

		while (i < step)
		{
			i++;
			if (temp == List_->list_.begin())
				return false;
			temp--;
		}
		return true;
	}
	bool next() override
	{
		if (temp == List_->list_.begin())
			return false;
		temp--;
		auto i = 0;

		while (i < step)
		{
			i++;
			if (temp == List_->list_.begin())
				return false;
			temp--;
		}
		return true;
	}
public:
	ListIteratorStep(const List* aList, int aStep = 1) : ListIterator(aList)
	{
		if (aStep <= 0)
			throw exception("Error. Wrong step");
		step = aStep - 1;
	}

	int getStep() const
	{
		return step;
	}
};

class ListIteratorPredicate : public ListIterator
{
private:
	bool (*predicate)(int);
	bool first() override {
		temp = List_->rear;
		temp--;
		while (!predicate(*temp))
		{
			if (temp == List_->list_.begin())
				return false;
			temp--;
		}
		return true;
	}
	bool next() override
	{
		if (temp == List_->list_.begin())
			return false;
		temp--;
		while (!predicate(*temp))
		{
			if (temp == List_->list_.begin())
				return false;
			temp--;
		}
		return true;
	}
public:
	ListIteratorPredicate(const List* aPList, bool aPredicate(int)) : ListIterator(aPList)
	{
		predicate = aPredicate;
	}

};

class ListIteratorValue : public ListIterator
{
private:
	int value;

	bool first() override
	{
		temp = List_->rear;
		temp--;
		while (*temp != value)
		{
			if (temp == List_->list_.begin())
				return false;
			temp--;
		}
		return true;
	}
	bool next() override
	{
		if (temp == List_->list_.begin())
			return false;
		temp--;
		while (*temp != value)
		{
			if (temp == List_->list_.begin())
				return false;
			temp--;
		}
		return true;
	}
public:
	
	int getValue() const
	{
		return value;
	}

	ListIteratorValue(const List* aList, int value_) : ListIterator(aList)
	{
		value = value_;
	}
};

#include "List.h"
#include <iostream>
#include <time.h>
using namespace std;

bool predicatePositive(int a)
{
    return a >= 3;
}


unsigned counting(ListIterator* li)
{
    unsigned cnt = 0;
    if (li->operator()())
        do {
            cnt++;
            cerr << li->operator*() << " ";
        } while (li->operator++());
        cerr << endl;
        return cnt;
}

int main()
{
    srand((unsigned)time(0));
    unsigned capacity, count;
    cout << "Enter list capacity: ";
    cin >> capacity;
    while (capacity < 1)
    {

        cout << "Wrong capacity. Try Again: ";
        cin >> capacity;
    }
    try
    {
        cout << "Enter number of elements to fill the list: ";
        cin >> count;
        List list(count);
        for (auto i = 0; i < count; i++) {
            int x = rand() % 5;
            list.append(x);
            cout << x << ' ';
        }
        cout << endl;

        int itStep;
        int itValue;

        cout << "Enter step-iterator: ";
        cin >> itStep;

        ListIterator* litS3 = list.createIterator(Iterators::STEP, itStep);
        
        cout << "Enter value-iterator: ";
        cin >> itValue;

        ListIterator* litV4 = list.createIterator(Iterators::VALUE, itValue);
        ListIterator* litPred = list.createIterator(Iterators::PREDICATE, predicatePositive);

        cout << "Number of elements in step-list (step " << ((ListIteratorStep*)litS3)->getStep() << "): " << counting((ListIteratorStep*)litS3) << endl;

        cout << "Number of elements in that list that equal " << ((ListIteratorValue*)litV4)->getValue() << " : " << counting((ListIteratorValue*)litV4) << endl;

        cout << "Number of elements whose value is higher or equals 3: " << counting((ListIteratorPredicate*)litPred) << endl;
    }

    catch (exception e)
    {
        cout << e.what() << endl;
    }

}



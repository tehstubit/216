#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>


using namespace std;

// So, roughly, how quicksort works:
//
// Each step of the process, we work on a sub-vector (first
// call uses the whole vector, of course).  In that sub-vector,
// we pick a pivot element, and then ensure (by swapping elements
// in the vector) that all elements that evaluate to less than
// the pivot value are before it in the vector, and all elements
// that are greater are after it in the vector.  Then we split
// the vector into two sub-vectors, and do the same thing.
// Eventually, we run out of vectors with more than one element,
// and we're done.
//
// Quick sort has the same average case performance as merge sort
// (both are O(n log n)), but quick sort has considerably worse
// worst case behavior -- O(n^2), while merge sort is still
// O(n log n).
//
// Don't panic if you don't follow the sorting algorithm here;
// while quick sort is pretty quick to implement (in terms of
// raw lines of code), it is (at least in my opinion) much
// more confusing than merge sort.  While quick sort is unlikely
// to show up later in the class, it's worthwhile to understand
// how it works -- and, as always, good practice to read through
// the code to understand what's going on.
//
// The main thing you need to do for this exercise is to pick
// out the (single) comparison; the only things you will need
// to modify in the bodies of these functions is the single
// comparison and the calls to quickSortInternal.
//
// Note: this implementation is specifically simple, largely to
// avoid multiple comparisons per run (as to make the practicum
// a bit easier) -- the choice of the initial element as the
// pivot value is known to cause degenerate behavior if quick
// sort encounters an already sorted vector.  This implementation,
// however, does maintain good performance in sorting randomly
// generated vectors.  Better behavior in already-sorted vectors
// (without really impacting performance in random vectors) can
// be attained by better pivot value selection, but that makes 
// the implementation slightly more complex, and makes it hard
// to do without adding more comparison calls...

bool alphaSort(string first, string second)
{
	return first < second;
}

bool reverseAlphaSort (string first, string second)
{
	return first > second;
}

bool lastCharSort (string first, string second)
{
	return first.back() < second.back();
}

void quickSortInternal(vector<string> & vStrings, int iStartIndex, int iEndIndex,
	 function<bool(string, string)> compare) 
{
	// Test to make sure we actually have sorting to do...
    if(iStartIndex < iEndIndex)
    {
		// We need to keep track of a pivot value and
		// location; once we choose the value, it won't
		// change, but the location can (as we'll be swapping
		// it during the process)

		int iPivot = iStartIndex;

		string sPivotValue = vStrings[iPivot];

		// So, we pick, arbitrarily (and probably poorly, see above)
		// the first element of the sub-vector as the pivot.  sPivotValue
		// holds the string value of the pivot element, and iPivot holds
		// the index for the pivot.
 
		// And then, for each element in this sub-vector...
		for( int i = iStartIndex + 1 ; i <= iEndIndex; i++ )
		{
			// If the element is less than the pivot, we need to make sure
			// it shows up before the pivot in the sorted sub-vector, sooo...
			if(compare( vStrings[i],  sPivotValue) )
			{
				// So, right now, what we've got is:
				//
				// i - current index we're iterating through
				//
				// vStrings[iStartIndex] - contains the pivot value
				//                       - (doesn't change until
				//                       -  we're done with the loop)
				//
				// vStrings[i] - a value in the vector that's less
				//             - than the pivot value, known because
				//             - of the if statement immediately
				//             - above.
				//
				// iPivot - the highest index that we *know* will
				//        - contain the pivot value or a lesser
				//        - value. 
				//
				// vStrings[iPivot] - A string that is the pivot
				//                  - value or less

				// So we know that we've got an extra element that's
				// less than the pivot, so we have to make room;
				// we'll do so by incrementing the pivot location

				iPivot++;

				// With this change:
				//
				// iPivot - Where we'd put the pivot value if we were
				//        - done with the loop
				//
				// vStrings[iPivot] - Don't know yet...


				// So, to make sure the newly found lesser value
				// (vStrings[i]) is in the vector before the pivot
				// location, we swap it with the pivot location.

				swap(vStrings[i], vStrings[iPivot]);


				// And now we have:
				//
				// vStrings[iPivot] - contains a value less than the pivot
				//                    value

				// And all of the rest still applies, so vStrings[iStartIndex]
				// still holds the pivot value, and every element between there
				// and iPivot holds a lesser value.

			}  // closing brace of if statement

		} // closing brace of for loop

		// So, after that loop, we've still got the pivot value in
		// vStrings[iStartIndex].  We know vStrings[iPivot] is less
		// than the pivot value, and furthermore, we know that
		// every element between index iStartIndex+1 and iPivot is
		// less than the pivot value, so know we know that we can just
		// pop the pivot value into vStrings[iPivot], and it will be
		// in the correct place -- we have to do a swap, of course,
		// to make sure we keep the value that was in vStrings[iPivot]
		// up until this point...

		swap(vStrings[iPivot], vStrings[iStartIndex]);

		// And now we have a pivot (which is in its correct and
		// final place) and two sub-vectors (which, while not
		// fully sorted, are either all less or all greater than
		// the pivot value...


		// So we recursively call quickSortInternal on those
		// sub-vectors.
        quickSortInternal(vStrings, iStartIndex, iPivot - 1, compare);
        quickSortInternal(vStrings, iPivot + 1, iEndIndex, compare);
    }
}


// Helper function to keep the code a little bit cleaner
void quickSort(vector<string> & vStrings, function<bool (string,string)> compare)
{
	quickSortInternal(vStrings, 0, vStrings.size() - 1, compare);
}


// Aaand the main function...
int main(int argc, char * argv[])
{
	// Seed the random number generator
	// (feel free to consider this line to be magic for at least
	// a few more weeks...)
	srand(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));

	// Allocate the vector
	vector<string> vVals;

	// Generate some random string values
	for( int i = 0; i < 12; i++ )
	{
		string s;

		for( int j = 0; j < 5; j++ )
		{
			char c = (rand() % 26) + 'a';
			s.push_back(c);
		}

		vVals.push_back(s);
	}

	// Display original vector

	cout << "String vector before: " << endl;

	for( auto it = vVals.begin(); it != vVals.end(); it++ )
	{
		cout << "  " << *it << endl;
	}

	cout << endl;

    // Now actually call the sort

	quickSort(vVals, alphaSort);

    cout << "String vector after: " << endl;

    for( auto it = vVals.begin(); it != vVals.end(); it++ )
    {
            cout << "  " << *it << endl;
    }

	quickSort(vVals, reverseAlphaSort);

    cout << "String vector after reverse: " << endl;

    for( auto it = vVals.begin(); it != vVals.end(); it++ )
    {
            cout << "  " << *it << endl;
    }

	quickSort(vVals, lastCharSort);

    cout << "String vector after last char sort: " << endl;

    for( auto it = vVals.begin(); it != vVals.end(); it++ )
    {
            cout << "  " << *it << endl;
    }

	return 0;
}


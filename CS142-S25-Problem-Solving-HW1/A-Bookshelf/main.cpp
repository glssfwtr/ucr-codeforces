#include <iostream>
#include <vector>

std::pair<int, int> FindShelfWidthConstraints(const std::vector<std::size_t> &book_thicknesses, std::size_t n)
{
  std::size_t minimum_width = 0;
  std::size_t maximum_width = 0;

  // find the thickest single book
  minimum_width = book_thicknesses.at(0);
  for ( std::size_t i = 0; i < n; ++i )
  {
    if ( book_thicknesses.at(i) > minimum_width )
    {
      minimum_width = book_thicknesses.at(i);
    }
  }

  // calculate thickest shelf width of all combined thickness
  for ( std::size_t i = 0; i < n; ++i )
  {
    maximum_width += book_thicknesses.at(i);
  }

  return {minimum_width, maximum_width};
}

bool IsFittingShelfWidth(const std::vector<std::size_t> &book_thicknesses, std::size_t n, std::size_t k, std::size_t selected_shelf_width)
{
  std::size_t current_shelf_width = 0;
  std::size_t current_shelf_level = 0;


  /*
    check if each book can fit into given width in the first place

    if above checks out, then check if some more books can fit into some same shelf, then increase level placement accordingly
  */

  for ( std::size_t i = 0; i < n; ++i )
  {
    if ( book_thicknesses.at(i) > selected_shelf_width ) // individual shelf must be able to contain thickest
    {
      return false;
    }

    if ( (current_shelf_width + book_thicknesses.at(i)) <= selected_shelf_width ) // add to current shelf normally
    {
      current_shelf_width += book_thicknesses.at(i);
    }
    else // exceed shelf width, need to increase shelf level
    {
      ++current_shelf_level;

      if ( current_shelf_level >= k )
      {
        return false;
      }

      current_shelf_width = book_thicknesses.at(i);
    }

  }

  return true;
}

std::size_t FindMinimalWidth(const std::vector<std::size_t> &book_thicknesses, std::size_t n, std::size_t k, std::pair<std::size_t, std::size_t> shelf_width_constraints)
{
  std::size_t left = shelf_width_constraints.first;
  std::size_t right = shelf_width_constraints.second;
  std::size_t minimal_width_result = 0;

  // standard binary search operation but with shelf width validation as the L R conditions
  while ( left <= right )
  {
    std::size_t middle = left + (right - left) / 2;
    /*
      check which shelf width per single book can be used to fit all books across k shelves.
      if some middle width fits, then anything bigger must also fit, and either current or some even smaller may be optimal.book_thicknesses
      Another case being that if width doesn't fit, then anything smaller won't fit either, so try something bigger instead, until former branching condition gives results.
    */
    if ( IsFittingShelfWidth(book_thicknesses, n, k, middle) ) // if it fits, try going lower than current middle
    {
      minimal_width_result = middle;
      right = middle - 1;
    }
    else // if it doesn't fit, try going higher than current middle
    {
      left = middle + 1;
    }

  }

  return minimal_width_result;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  std::size_t n;
  std::size_t k;
  std::size_t book_thickness_input;
  std::vector<std::size_t> book_thicknesses;
  std::pair<std::size_t, std::size_t> shelf_width_constraints{0, 0}; // lower (smallest width still containing one book) upper (largest width containing all books)

  std::cin >> n;
  std::cin >> k;

  for ( std::size_t i = 0; i < n; ++i )
  {
    std::cin >> book_thickness_input;
    book_thicknesses.push_back(book_thickness_input);
  }

  // find lower and upper bound constraints of shelf width
  shelf_width_constraints = FindShelfWidthConstraints(book_thicknesses, n);

  // std::cout << shelf_width_constraints.first << " "
  //           << shelf_width_constraints.second << "\n";

  std::cout << FindMinimalWidth(book_thicknesses, n, k, shelf_width_constraints);

  return 0;
}

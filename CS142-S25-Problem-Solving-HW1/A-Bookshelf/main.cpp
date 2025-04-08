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
    if (book_thicknesses.at(i) > minimum_width)
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

bool IsFittingShelfWidth(const std::vector<std::size_t> &book_thicknesses, std::size_t n, std::size_t selected_shelf_width)
{


  return true;
}

std::size_t FindMinimalWidth(const std::vector<std::size_t> &book_thicknesses, std::size_t n, std::size_t k, std::pair<std::size_t, std::size_t> shelf_width_constraints)
{
  std::size_t left = shelf_width_constraints.first;
  std::size_t right = shelf_width_constraints.second;
  std::size_t minimal_width_result = 0;

  while (left <= right)
  {
    std::size_t middle = left + (right - left) / 2;
  }



  return 0;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  std::size_t n;
  std::size_t k;
  std::size_t book_thickness_input;
  std::vector<std::size_t> book_thicknesses;
  std::pair<std::size_t, std::size_t> shelf_width_constraints{0, 0};

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

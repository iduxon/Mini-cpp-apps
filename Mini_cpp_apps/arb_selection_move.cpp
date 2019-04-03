#include "function_declarations.h"

bool is_selected(const std::string &item) { return item[0] == '*'; }

template <typename IT, typename Pred>
void move_selection(IT first, IT last, IT destination, Pred predicate) {
  std::stable_partition(first, destination, [predicate](const auto &item) {
    return !predicate(item);
  });
  std::stable_partition(destination, last, predicate);
}

void arb_selection_move() {
  // The grocery items are selected by using a '*' in this case
  std::vector<std::string> items{"bread", "butter", "*tomatto", "*ketchup",
                                 "mayo",  "hummus", "*meat"};
  /*
    unsigned int num_of_selected = 0;
    std::accumulate(std::begin(items), std::end(items), num_of_selected,
                    [&](std::string &item) {
                      return is_selected(item) ? num_of_selected++ : 0;
                    });
  */
  // move the selected items in front
  move_selection(std::begin(items), std::end(items), std::begin(items),
                 is_selected);

  std::copy(std::begin(items), std::end(items),
            std::ostream_iterator<std::string>(std::cout, "\n"));
}

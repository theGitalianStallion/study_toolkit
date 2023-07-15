#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
// #include <windows.h>
// #include <conio.h>
#include <limits>
#include <fstream>
#include <algorithm>
#include <iterator>
using namespace std;

int user_choice_int {0}; // int value for users choice of action
int display_on {1}; // display tree option for certain functions/actions
std::vector<std::vector<string>> matrix_trees (3, std::vector<string> {"+----+----+", "+----+----+", "+----+----+", "+----+----+", "+----+----+"}); // tree matrix
std::vector<std::vector<string>> matrix_cards (1, std::vector<string> { "+----+----+", "+----+----+", "+----+----+"}); // cards matrix
std::vector<std::vector<string>> matrix_table (5, std::vector<string> {"+----+----+", "+----+----+", "+----+----+", "+----+----+", "+----+----+"}); // table matrix
std::vector<string> cell_full {"xXxXxXxXxXx", "xXxXxXxXxXx", "xXxXxXxXxXx", "xXxXxXxXxXx", "xXxXxXxXxXx"}; // full cell?
int column_width {25}; // default, editable so shouldn't be local to displayFunction 
std::vector<std::vector<string>> tableCSV; // necessary for table CSV function

string removeSpaces(string input) { // this function removes spaces 
  input.erase(std::remove(input.begin(), input.end(), ' '), input.end()); // removes spaces b/w beginning and end of string given
  return input; // returns the value without spaces
} 
int userChoiceFunction() { // this is input validation for user choice int input
  std::string user_choice {" "};
  int user_choice_int_temp {0};
  do {
    std::cout << "Select an option:" << std::endl;
    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\t" << std::endl;
    std::cout << "Tree diagrams\t" << std::endl;
    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\t" << std::endl;
    std::cout << "1. Add\t";
    std::cout << "2. Edit\t";
    std::cout << "3. Insert\t";
    std::cout << "4. Swap\t";
    std::cout << "5. Delete\t";
    std::cout << "6. Import\t";
    std::cout << "7. Export\t";
    std::cout << "8. Display\t" << std::endl;
    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\t" << std::endl;
    std::cout << "Flashcards\t" << std::endl;
    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\t" << std::endl;
    std::cout << "9. Add\t";
    std::cout << "10. Edit\t";
    std::cout << "11. Insert\t";
    std::cout << "12. Swap\t";
    std::cout << "13. Delete\t";
    std::cout << "14. Import\t";
    std::cout << "15. Export\t";
    std::cout << "16. Display\t";
    std::cout << "17. Create flashcards from a tree node." << std::endl;
    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\t" << std::endl;
    std::cout << "Revision table\t" << std::endl;
    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\t" << std::endl;
    std::cout << "18. Add\t";
    std::cout << "19. Edit\t";
    std::cout << "20. Delete\t";
    std::cout << "21. Insert\t";
    std::cout << "22: Swap\t";
    std::cout << "23. Import\t";
    std::cout << "24. Export\t";
    std::cout << "25. Display\t";
    std::cout << "26. Create table from a tree node." << std::endl;
    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\t" << std::endl;
    std::cout << "Settings\t" << std::endl;
    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────\t" << std::endl;
    std::cout << "27. Change column width\t";
    std::cout << "28. Toggle display\t";
    std::cout << "29. Toggle Autosave\t";
    std::cout << "29. Toggle display current node only\t" << std::endl;
    getline(cin, user_choice, '\n') ;
    if (user_choice == "1" || "2" || "3" || "4" || "5" || "6" || "7" || "8" || "9" || "10" 
       || "11" || "12" || "13" || "14" || "15" || "16" || "17" || "18" || "19" || "20"
       || "21" || "22" || "23" || "24" || "25" || "26" || "27" || "28" || "29") { 
      user_choice_int_temp = atoi(user_choice.c_str());
    }
  } while (user_choice_int_temp < 1 || user_choice_int_temp > 29);
  return user_choice_int_temp;
}
std::vector<int> inputValidation(string type_of_matrix) { // this is a generic input validation function for strings
  string type_of_matrix_temp = type_of_matrix;
  int row_constraint {999};
  int column_constraint {50};
  if (type_of_matrix_temp == "tree") {
    column_constraint = {50};
  } else if (type_of_matrix_temp == "cards") {
    column_constraint = {2};
  } else if (type_of_matrix_temp == "table") {
    column_constraint = {4};
  }
  int node_x_int {0}; 
  int node_y_int {0}; 
  while (node_x_int < 1  || node_y_int < 1 || node_x_int > column_constraint) {
    std::string node_x {" "};
    std::string node_y {" "};
    std::cout << "Child node of which parent ?" << endl;
    std::cin >> node_x ;
    getline(std::cin, node_y, '\n') ;   
    node_y = removeSpaces(node_y);        
    for (int i = 1 ; i < row_constraint ; ++i) {
      std::string input_string = std::to_string(i);
      if (node_x_int != 0 && node_y_int != 0) { break; }
      if (input_string == node_x) {
        node_x_int = atoi(node_x.c_str());
      } if (input_string == node_y) {
        node_y_int = atoi(node_y.c_str());
      }
    }
  } std::vector<int> temp_x_y_vec {};
  temp_x_y_vec.push_back(node_x_int);
  temp_x_y_vec.push_back(node_y_int);
  return temp_x_y_vec;
};
void displayFunction() { // creates a temp matrix so that cells can be formatted for display, adds rows for strings that are too long
  std::vector<std::vector<string>> display_matrix = matrix_trees; // initializes the temp matrix
  int rows_display = display_matrix.size();
  int cols_display = display_matrix[0].size();
  int num_rows_inserted_into_this_table {0};
  for (int row = 0 ; row < rows_display; ++row) {
    int rows_inserted_to_this_vec {0};
    for (int col = 0 ; col < cols_display; ++col) {
      int rows_to_insert {0}; 
      std:: string cell_string = display_matrix[row + num_rows_inserted_into_this_table][col]; // sets temp str to cell strings value.
      int str_len = cell_string.length();
      for (int rows_to_insert_temp = 0 ; rows_to_insert_temp <= 9 ; ++rows_to_insert_temp) { // iterating through cell_full string's length to find number of rows/lines to allocate to the string.
        int substr_start = 0 + (rows_to_insert_temp*column_width); // sets start of substring for each row
        int substr_end = column_width + (rows_to_insert_temp*column_width); // sets end of substring for each row
        (substr_start < str_len && str_len <= substr_end) ? rows_to_insert = 1*rows_to_insert_temp : rows_to_insert=rows_to_insert; // set num of lines for the string, rows_to_insert=rows_to_insert just filling space for ternary.
        } display_matrix[row + num_rows_inserted_into_this_table][col] = cell_string.substr(0, column_width); // setting first row to first portion of the string.
        if (rows_to_insert > rows_inserted_to_this_vec) { // if number of lines to add is greater than 1 or num of rows added so far by previous columns (if previous columns added rows)
          for (int rows_inserted = 0 ; rows_inserted < rows_to_insert ; ++rows_inserted) { // iterate through the string for the number of row(s) needed
            std::vector<string> new_blank_row {"   ", "           ", "           ", "           ", "           "}; // this adds a blank row for strings that take up more than one line
            display_matrix.insert(display_matrix.begin() + row + 1 + rows_inserted + num_rows_inserted_into_this_table, new_blank_row); // add a row on each iteration to the temp output matrix_trees
            display_matrix[row + 1 + rows_inserted + num_rows_inserted_into_this_table][col] = cell_string.substr(column_width*(1 + rows_inserted), column_width); // insert appropriate substring into new temp output cell
            rows_inserted_to_this_vec += 1;
          }
        } else if (0 < rows_to_insert && rows_to_insert <= rows_inserted_to_this_vec) { // if number of lines is greater than rows AND less than the number of rows added by previous columns within this row...
          for (int substrings_inserted = 0 ; substrings_inserted < rows_to_insert ; ++substrings_inserted) { // iterate through the string for the number of row(s) needed
            display_matrix[row + 1 + substrings_inserted + num_rows_inserted_into_this_table][col] = cell_string.substr(column_width*(1 + substrings_inserted), column_width); // insert appropriate substring into new temp output cell
          } 
        }
      } num_rows_inserted_into_this_table += rows_inserted_to_this_vec; // this should be fine.
    }
  rows_display = display_matrix.size();
  cols_display = display_matrix[0].size();
  std::cout << "Tree Diagram: " << std::endl;
  for (int row = 0 ; row < rows_display; ++row) {
    for (int col = 0 ; col < cols_display; ++col) {
      std::string display_divider {""};
      if (row == 0) { display_divider = "";
      } else if (col == 0) { display_divider = "";
      } else if (row == 1 && col == 1) {display_divider = "";
      } else if (display_matrix[row][col] == "+----+----+") { display_divider = "";
      } else if (display_matrix[row][col] == "xXxXxXxXxXx" && display_matrix[row][col-1] == "xXxXxXxXxXx") { display_divider = "│  ";
      } else if (display_matrix[row][col] == "           " && display_matrix[row][col-1] == "           ") { display_divider = "│  ";
      } else if (display_matrix[row][col] == "           ") { display_divider = "";   
    //   } else if (display_matrix[row][col-1] != "xXxXxXxXxXx" && display_matrix[row][col] != "xXxXxXxXxXx" && display_matrix[row][col] != "+----+----+") {
    //             display_divider = "|";
      } else if (display_matrix[row][col-1] == "           " ) { display_divider = "│  ";
      } else if (display_matrix[row][col-1] != "xXxXxXxXxXx" && display_matrix[row][col] != "xXxXxXxXxXx" && display_matrix[row][col] != "+----+----+") {
        display_divider = "┬──";
      } else if (display_matrix[row][col] != "+----+----+" && display_matrix[row][col] != "xXxXxXxXxXx" && display_matrix[row+1][col-1] != "xXxXxXxXxXx") { // check if child node and check if last child node
        display_divider = "├──";
      } else if (display_matrix[row][col] != "+----+----+" && display_matrix[row][col] != "xXxXxXxXxXx") { display_divider = "├──"; // └
      } else { display_divider = "";}
      if (col == 0) { 
        std::cout << setw(0) << std::left << display_divider << setw(5) << std::right << display_matrix[row][col];
      } else
        std::cout << setw(3) << std::left << display_divider << setw(column_width) << std::right << display_matrix[row][col];
    } std::cout << std::endl;
  }
}
string stringInput(){
    std::string node {""}; // nodes
    std::string node_temp {""};  // node indexing, x and y coordinates
    cin >> node_temp; // this inputs the first word
    node.append(node_temp); // this appends the first word to the string output
    getline(cin, node_temp, '\n'); // this gets the rest of the input
    node.append(node_temp); // appends the rest of the input to the string output
    return node;
}
void createNode(string what_to_add_to) {
  std::vector<int> input_validation_matrix_temp = inputValidation(what_to_add_to); 
  int node_x_int = input_validation_matrix_temp[0];
  int node_y_int = input_validation_matrix_temp[1];
    
  if (matrix_trees[node_y_int][node_x_int+1] == "+----+----+") {//check if y coordinate is empty
    int node_x_int_add = node_x_int + 1;
    if (matrix_trees[0].size() <= node_x_int_add) {
      matrix_trees[0].push_back(to_string(node_x_int + 1) + ", 0");
      for (int i = 1 ; i < matrix_trees.size() ; i++) {
        matrix_trees[i].push_back("+----+----+");
      } cell_full.push_back("xXxXxXxXxXx");
    } else{}
    if ((matrix_trees[node_y_int][node_x_int]) == "+----+----+" // // or parent cell_full is not equal to string
      || ((matrix_trees[node_y_int][node_x_int]) == "xXxXxXxXxXx")) {
      cout << "Parent node empty, make a sibling node." << endl; // Prompt user
      cin.get();
    } else if (((matrix_trees[node_y_int][node_x_int+1]) == ("+----+----+")) // and input cell_full is equal to sibling string
      || ((matrix_trees[node_y_int][node_x_int+1]) == ("xXxXxXxXxXx"))) { // and parent cell_full is not equal to empty string, verifies cell_full is empty to prevent accidental overwrites.
      cout << "What is the node called ?" << endl; // prompt user
      matrix_trees[node_y_int][node_x_int+1] = stringInput(); // send input to temp card
    } else {
      cout << "Node full, edit node." << endl; // Prompt user
      cin.get();
    }
  } else {
    int node_x_int_add = node_x_int + 1;
    if (matrix_trees[0].size() <= node_x_int_add) {
      matrix_trees[0].push_back(to_string(node_y_int) + ", 0");
      for (int i = 1 ; i < matrix_trees.size() ; i++) {
        matrix_trees[i].push_back("xXxXxXxXxXx");
      } cell_full.push_back("xXxXxXxXxXx");
    } else {}
    cout << "What is the node called ?" << endl;
   // stringInput();
    if (node_x_int > matrix_trees[0].size()) { cout << "Node is empty, create a node first." << endl;}
    else if (node_y_int > matrix_trees.size()) { cout << "Node is empty, create a node first." << endl;}
    else if (matrix_trees[node_y_int][node_x_int] == "xXxXxXxXxXx") { cout << "Cell is reserved, choose another node." << endl;}       
    else if (matrix_trees[node_y_int][node_x_int + 1] == "+----+----+") { cout << "Node has no children, create a child node first." << endl; }
    else {
      std::string str_temp = {""};
      int node_y_int_add = 1;
      for (int i = 1; i <= matrix_trees.size() ; i++) {// iterate over all rows, starting at node y until the end of the column.
        if (matrix_trees[node_y_int + i][node_x_int] == "xXxXxXxXxXx" && // and check each child in that column to see if it is part of the parent nodes litter.
        matrix_trees[node_y_int + i][node_x_int+1] != "+----+----+") {
          node_y_int_add = node_y_int_add +1; // if the node is, add one to node_y_int_add
        } else { break; }
      }
      std::cout << "There were: " << to_string(node_y_int_add) << " children" << std::endl; // has an output of number of children nodes found
      node_y_int = node_y_int + node_y_int_add;
      matrix_trees.insert(matrix_trees.begin() + node_y_int, cell_full);  // this adds the row to the matrix_trees
      str_temp = "0," + to_string(node_y_int); // this creates the string for the new rows row and column index
      str_temp.erase(std::remove(str_temp.begin(), str_temp.end(), ' '), str_temp.end()); // this erases spaces in the new rows row and column index
      matrix_trees[node_y_int][0] = str_temp; // this sends the new rows row/column index to the matrix_trees
      matrix_trees[node_y_int][node_x_int + 1] = stringInput(); // this sets the 
      for (int i = 1 ; i <= matrix_trees.size() ; i++) {  // iterates through rows, if the cell_full to the right of the entry is xXx, it gets set to +--+ format
        if (matrix_trees[node_y_int][node_x_int + 1 + i] == "xXxXxXxXxXx") {
          matrix_trees[node_y_int][node_x_int + 1 + i] = "+----+----+";
      } else { break; }
      } for (int i = 1 ; i <= matrix_trees.size() ; i++) {
        if ((matrix_trees[node_y_int + i][0]) == (matrix_trees[node_y_int + i - 1][0])) {
          int i_temp = {0};
          i_temp = node_y_int + i;
          std::string i_cell_stringing {""};
          i_cell_stringing = to_string(i_temp);
          str_temp = "0," + i_cell_stringing;
          str_temp.erase(std::remove(str_temp.begin(), str_temp.end(), ' '), str_temp.end());
          matrix_trees[node_y_int + i][0] = str_temp;
        } else { break; }
      }
    }
  }
}
void displayFlashcards() {
    system("cls"); std::cout << "Flashcards:" << std::endl;
    for ( const auto &row : matrix_cards) {
        for ( const auto &s : row) std::cout << setw(10) << s << "\t";
        std::cout << std::endl;
    } cin.get();
}
int changeDisplayWidth() {
  std::string changeDisplayWidth_option {" "};
  int display_on_temp {1};
  cin.get();
  cout << "\t\t" << "would you like to turn the display off? Y/N";
  cin >> changeDisplayWidth_option ;
  if (changeDisplayWidth_option != "Y" && changeDisplayWidth_option != "N") {
    std::cout << "Invalid Response. Display is on.";
  } else if (changeDisplayWidth_option == "N") {
    display_on_temp = 1;
  } else if (changeDisplayWidth_option == "Y") {
    display_on_temp = 0;
  } return display_on_temp;
};
enum class CSVState {
  UnquotedField,
  QuotedField,
  QuotedQuote
};
std::vector<std::string> readCSVRow(const std::string &row) {
  CSVState state = CSVState::UnquotedField;
  std::vector<std::string> fields {""};
  size_t i = 0; // index of the current field
  for (char c : row) {
    switch (state) {
      case CSVState::UnquotedField:
        switch (c) {
          case '\n':
            fields.erase(fields.end());
            break;
          case ',': // end of field
            fields.push_back(""); i++;
            break;
          case '"': state = CSVState::QuotedField;
            break;
          default:  fields[i].push_back(c);
            break; }
        break;
      case CSVState::QuotedField:
        switch (c) {
          case '"': state = CSVState::QuotedQuote;
            break;
          default:  fields[i].push_back(c);
            break; }
        break;
      case CSVState::QuotedQuote:
        switch (c) {
          case '\n':
            fields.erase(fields.end());
            break;
          case ',': // , after closing quote
            fields.push_back(""); i++;
            state = CSVState::UnquotedField;
            break;
          case '"': // "" -> "
            fields[i].push_back('"');
            state = CSVState::QuotedField;
            break;
          default:  // end of quote
            state = CSVState::UnquotedField;
            break; }
        break;
    }
  } fields.erase(fields.end() - 1);
  return fields;
}
std::vector<std::vector<std::string>> readCSV(std::istream &in) { /// Read CSV file, Excel dialect. Accept "quoted fields ""with quotes"""
  std::vector<std::vector<std::string>> table;
  std::string row;
  while (!in.eof()) {
    std::getline(in, row);
    if (in.bad() || in.fail()) {
      break;
    } auto fields = readCSVRow(row);
    table.push_back(fields);
  } tableCSV = table;
  return table;
}
void importFunction() {
  std::string in_file_name {" "};
  std::string line {""};
  std::ifstream in_file {" "};
  matrix_trees.clear(); //// Wrote this and didn't check it, good idea to check here first if broken.
  std::cout << "What is the name of the file?" << std::endl; // prompt user for file name
  std::cin >> in_file_name;
  removeSpaces(in_file_name);
  in_file.open("../" + in_file_name + ".csv"); // import the file
  matrix_trees = readCSV(in_file);
  displayFunction();
  cin.get();
  in_file.close();
}
void exportFunction() {
  std::string out_file_status {" "};
  std::string out_file_name {" "};
  std::cout << "save as: " << std::endl; // prompt user for new file name
  std::cin >> out_file_name;
  removeSpaces(out_file_name);
  std::ofstream trunc_file {"../" + out_file_name + ".csv", std::ios::trunc}; // open file, truncate it, 
  std::ofstream out_file {"../" + out_file_name + ".csv", std::ios::app}; // then set the same file to append mode.
  for ( const auto &row : matrix_trees) { // outputting each cell to the matrix_trees file
    for ( const auto &s : row) { 
      out_file <<"\""<< s << "\"" << ",";
    } out_file << "\n";
  } out_file.close(); // close the open instance of the file
}
void createFlashcard() {
    std::vector<string> new_flash_card {""};
    std::string fc {""};
    string fc_temp {""};
    int fc_count {0};
    system("cls");
    fc.clear();
    //new_flash_card.clear();
    fc_temp.clear();
    fc_count = matrix_cards.size(); // set first row
    fc = std::to_string(fc_count) + ".";
    new_flash_card.push_back(fc);
    fc.clear(); // clear this variable for next function
    std::cout << "What is on the front of the flash card ?" << std::endl; // prompt user
    std::cin >> fc_temp ;
    fc.append(fc_temp); // format input
    getline(cin , fc_temp, '\n');
    fc.append(fc_temp);
    new_flash_card.push_back(fc);
    system("cls"); // clear these variables and screen
    fc.clear();
    fc_temp.clear();
    std::cout << "What is on the back of the flash card ?" << std::endl; // prompt user
    std::cin >> fc_temp ;
    fc.append(fc_temp); // format input
    getline(cin, fc_temp, '\n');
    fc.append(fc_temp);
    new_flash_card.push_back(fc);
    matrix_cards.push_back(new_flash_card); // insert inputs into matrix_trees
}
void createCardsOrTableFromTree(string what_to_create_from) {
  std::string fc_x {""};
  std::string fc_y {""};
  std::vector<int> input_validation_vector_temp = inputValidation(what_to_create_from);
  int fc_x_int = input_validation_vector_temp[0];
  int fc_y_int = input_validation_vector_temp[1];
  matrix_cards.clear();
  for (int iter_of_rows = fc_y_int ; iter_of_rows < fc_x_int ; ++iter_of_rows) {
    std::string entry {};
    std::vector<string> row {};
    row.clear();
    if (matrix_trees[iter_of_rows][fc_x_int] != "+----+----+" && matrix_trees[iter_of_rows][fc_x_int] != "xXxXxXxXxXx") { // this line below probably broke something, needs to be constrained to children nodes of a specific cell_full. (e.g. each 1st gen child node of a chapter)
      row.clear();
      entry = matrix_trees[iter_of_rows][fc_x_int];
      row.push_back(entry);
      row.push_back("+----+----+");
      matrix_cards.push_back(row);
    } else { break; }
  }
}
void setColumnDisplayWidth() {
  std::string display_width_string {""};
  std::string input_string {" "};
  int prev_col_width {25};
  while (column_width == prev_col_width || column_width < 1 || column_width > 70) {
    display_width_string = {""};
    input_string = {" "};
    cout << "Display width (1-100):" << endl;
    cin >> display_width_string;
    for (int i = 1 ; i <= 100 ; i++) {
      input_string = std::to_string(i);
      if (input_string == display_width_string) {   
        column_width = atoi(display_width_string.c_str());
        break;   
      }
    }
  } if (input_string == display_width_string) {
    prev_col_width = column_width;
  }
}
void editNode(string what_to_edit) {
  std::vector<int> input_validation_matrix_temp = inputValidation(what_to_edit);
  int node_x_int = input_validation_matrix_temp[0];
  int node_y_int = input_validation_matrix_temp[1];
  if (what_to_edit == "tree") {
    cout << "What will the node be replaced with ?" << endl; // prompt user
    matrix_trees[node_y_int][node_x_int] = stringInput();
  } else if (what_to_edit == "cards") {
    std::cout << "What is on the front of the flash card ?" << std::endl; // prompt user
      matrix_cards[node_y_int][0] = stringInput();
    std::cout << "What is on the back of the flash card ?" << std::endl; // prompt user
      matrix_cards[node_y_int][1] = stringInput();
  }
}
void deleteNode(string what_to_delete) {
  std::string node {""}; // nodes
  std::string node_temp {""};  // node indexing, x and y coordinates
  string str_temp = {""};
  std::string test_if_cell_empty = {"+----+----+"};
  std::vector<int> input_validation_matrix_temp = inputValidation(what_to_delete);
  int node_x_int = input_validation_matrix_temp[0];
  int node_y_int = input_validation_matrix_temp[1];
  matrix_trees.erase(matrix_trees.begin() + node_y_int);
  for (int i = 1 ; i < 3 ; i++) {
    if ( matrix_trees[node_y_int][node_x_int] != test_if_cell_empty // if child cell_full is not equal to xXx val
    && matrix_trees[node_y_int][node_x_int] != cell_full[0]) {
      cout << "Choose another cell_full" << endl;
    } else if (matrix_trees[node_y_int][node_x_int+1] != cell_full[0] // and if child cell_full is not equal to empty 
    && matrix_trees[node_y_int][node_x_int+1] != test_if_cell_empty // and if parent cell_full is equal to xXx
    && matrix_trees[node_y_int][node_x_int] == cell_full[0] // and if parent cell_full is equal to empty
    && matrix_trees[node_y_int][node_x_int] == test_if_cell_empty) {
      matrix_trees.erase(matrix_trees.begin() + node_y_int);
    } else if (matrix_trees[node_y_int][node_x_int+2] != cell_full[0] // and if child cell_full is not equal to empty 
    && matrix_trees[node_y_int][node_x_int+2] != test_if_cell_empty // and if parent cell_full is equal to xXx
    && matrix_trees[node_y_int][node_x_int+1] == cell_full[0] // and if parent cell_full is equal to empty
    && matrix_trees[node_y_int][node_x_int+1] == test_if_cell_empty) {
      matrix_trees.erase(matrix_trees.begin() + node_y_int);
    }
  } for ( const auto &row : matrix_trees) {
    str_temp.erase(std::remove(str_temp.begin(), str_temp.end(), ' '), str_temp.end());
    matrix_trees[node_y_int][0] = str_temp;
  } for (int i = 1 ; i < 999 ; i++) {
    if ((matrix_trees[node_y_int + i][0]) == (matrix_trees[node_y_int + i - 1][0])) {
      int i_temp = {0};
      i_temp = node_y_int + i;
      std::string i_cell_stringing {""};
      i_cell_stringing = to_string(i_temp);
      str_temp= "0," + i_cell_stringing;
      str_temp.erase(std::remove(str_temp.begin(), str_temp.end(), ' '), str_temp.end());
      matrix_trees[node_y_int + i][0] = str_temp;
    } else { break; }
  }
}
void deleteFlashcard() {
  std::string fc_y {""};
  std::vector<std::vector<int>> temp_matrix_cards {};
  int fc_y_d {0};
  fc_y.clear();  
  matrix_cards.erase(matrix_cards.begin() + fc_y_d); // erase flashcard
  for ( const auto &row : matrix_cards) {
    matrix_cards[fc_y_d][0] = fc_y;
  }
}
int main() {  
  matrix_trees[0][0] = "0,0"; matrix_trees[0][1] = "1,0"; matrix_trees[0][2] = "2,0"; matrix_trees[0][3] = "3,0"; matrix_trees[0][4] = "4,0"; // defaults for tree
  matrix_trees[1][0] = "0,1"; matrix_trees[1][1] = "Root";
  matrix_cards[0][1] = "Front"; matrix_cards[0][2] = "Back"; // defaults for cards 
  while (1==1) {
    user_choice_int = userChoiceFunction();  
    switch (user_choice_int) {
    case 1: // create a node
      (display_on == 1) ? displayFunction() : displayFunction();
      createNode("tree");
      break; 
    case 2: // set column display width
      (display_on == 1) ? displayFunction() : displayFunction();
      setColumnDisplayWidth();
      break;
    case 3: // edit a node
      (display_on == 1) ? displayFunction() : displayFunction();
      editNode("tree");
      break;
    case 4: // delete a node/row
      (display_on == 1) ? displayFunction() : displayFunction();
      break;
    case 5: // import tree
      break;
    case 6: // save tree
      importFunction();
      break;
    case 7: // display tree diagram
      exportFunction();
      cin.get();
      break;
    case 8: // Create a flash card
      break;
    case 9: // Edit a flash card
      (display_on == 1) ? displayFunction() : displayFunction();
      break;
    case 10: // display flashcards
      break;
    case 11: // delete flashcard
      (display_on == 1) ? displayFunction() : displayFunction() ;
      break;
    case 12: // import a set of flashcards
      break;
    case 13: // save a set of flashcards
      break;
    case 14: // create flashcards from a column
      break;
    case 15: { system ("cls"); break; }
    case 16: {system ("cls"); break; }
    case 17: // import a table
      break;
    case 18: {system ("cls"); break; }
    case 19: { system ("cls"); break; }
    case 20: // create a table from a column 
      break;
    case 21: { break; }
    }
  } return 0;
}
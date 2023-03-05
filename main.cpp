#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>

using namespace std;
/*------------------------*/
const int NMISP = 5;
const int RNG_RANGE = 100;
/*------------------------*/
vector<string> split_string(const string& split)
{
  vector<string> words;
  string word = "";
  for (int i = 0; i < split.size(); i++){
    if (split.at(i) == ' '){
      words.push_back(word);
      word = "";
    } else{
      word = word + split.at(i);
    }
  }
  words.push_back(word);
  return words;
}
/*------------------------*/
void display_header(const int ndict, const int nmiss)
{
  cout << "*** Typing Tutor" << endl;
  cout << "There are " << ndict << " words in the dictionary." << endl;
  cout << "There are " << nmiss << " commonly misspelled words." << endl;
}
/*------------------------*/
void display_menu_options()
{
    cout << endl << "*** Select a menu option:" << endl
         << "1. Spell commonly misspelled words" << endl
         << "2. Type random words from the full dictionary" << endl
         << "3. Display some words from one of the lists" << endl
         << "4. Use binary search to lookup a word in the dictionary" << endl
         << "5. Exit the program." << endl
         << "Your choice: ";
}
/*------------------------*/
vector<int> randn(const int n, const int max)
{
  vector<int> temp;
  int random;
  for (int i = 0; i < n; i++){
    random = rand() % (max + 1);
    temp.push_back(random);
  }
  return temp;
}
/*------------------------*/
ifstream open(const string& src_file)
{
    ifstream src{src_file};
    if (!src.is_open()) {
        cout << "Could not find file " << src_file << "." << endl;
        exit(1);
    }
    return src;
}
/*------------------------*/
void extract_dict(vector<string>& dst, const string& src_file)
{
  ifstream file(src_file);
  for (string word; getline(file,word);){
    dst.push_back(word);
  }
}
/*------------------------*/
void extract_misspelled(vector<string>& misspelled, vector<string>& correct, const string& src_file)
{
  ifstream file(src_file);
  string word;
  vector<string> line, split;
  while(!file.eof()){
    getline(file,word);
    split = split_string(word);
    for (int i = 0; i < split.size(); i++){
      line.push_back(split.at(i));
    }
  }
  for (int j = 0; j < line.size(); j++){
    if (j%2 == 0){
      misspelled.push_back(line.at(j));
    } else{
      correct.push_back(line.at(j));
    }
  }
}
/*------------------------*/
void display_elems(const vector<string>& src, const vector<int>& positions)
{
  for (int i = 0; i < positions.size() - 1; i++){
    cout << src.at(positions.at(i)) << ' ';
  }
  cout << src.at(positions.at(positions.size() - 1)) << endl;
}
/*------------------------*/
void extract_spelling_answers(vector<string>& dst, const vector<string>& correct, const vector<int> positions)
{
  for (int i = 0; i <= positions.size() - 1; i++){
    dst.push_back(correct.at(positions.at(i)));
  }
}
/*------------------------*/
void extract_spelling_mistakes(vector<string>& dst, const string& to_grade, const vector<string>& correct)
{
  vector<string> input = split_string(to_grade);
  string mistake;
  for (int i = 0; i < input.size(); i++){
    if (input.at(i) != correct.at(i)){
      mistake = input.at(i) + " -> " + correct.at(i);
      dst.push_back(mistake);
    }
  }
}
/*------------------------*/
void report_misspell_mistakes(const vector<string>& mistakes, const int num_words)
{
  int incorrect = mistakes.size();
  int correct = num_words - incorrect;
  if (incorrect > 0){
    cout << "Misspelled words:" << endl;
    for (int i = 0; i < mistakes.size(); i++){
      string mistake = mistakes.at(i);
      cout << "    " << mistake << endl;
    }
  } else{
    cout << "No misspelled words!" << endl;
  }
  cout << (3 * correct) << " points: " << correct << " spelled correctly x 3 points for each." << endl;
  cout << (6 * incorrect) << " point penalty: " << incorrect << " spelled incorrectly x -6 points for each." << endl;
  cout << "Score: " << ((3 * correct) - (6 * incorrect)) << endl;
}
/*------------------------*/
void evaluate_user_misspells(const vector<string>& src, const vector<int>& positions)
{
  string input;
  getline(cin, input);
  vector<string> answers;
  vector<string> mistakes;
  extract_spelling_answers(answers, src, positions);
  extract_spelling_mistakes(mistakes, input, answers);
  report_misspell_mistakes(mistakes, answers.size());
}
/*------------------------*/
void misspelled(const vector<string>& mspelled, const vector<string>& correct)
{
  cout << endl << "*** Using commonly misspelled words." << endl;
  vector<int> random = randn(NMISP, mspelled.size());
  display_elems(mspelled, random);
  cout << "Type the words above with the correct spelling:" << endl;
  evaluate_user_misspells(correct, random);
}
/*------------------------*/
void full_dict(const vector<string>& dict)
{
  int input1;
  int input2;
  cout << "*** Enter the start and end indices between 0 and 263532: ";
  cin >> input1 >> input2;
  if (input1 >= 0 && input2 < dict.size() && input1 <= input2){
    for (int i = input1; i <= input2; i++){
      cout << i << ". " << dict.at(i) << endl;
    }
  } else{
    cout << "The end index must come after the start, and the indices must be in range." << endl;
  }
}
/*------------------------*/
void display_words_prompt()
{
    // This displays the data set choices for menu option 3
    cout << endl << "*** Displaying word list entries." << endl
         << "Which words do you want to display?" << endl
         << "A. Dictionary of all words" << endl
         << "B. Commonly misspelled words (wrongly spelled)" << endl
         << "C. Commonly misspelled words (correctly spelled)" << endl
         << "Your choice: ";
}
/*------------------------*/
void print_range(const vector<string>& data)
{
}
/*------------------------*/
void display_in_range(const vector<string>& dict, const vector<string>& mspelled, const vector<string>& correct)
{
}
/*------------------------*/
void bsearch(const vector<string>& data)
{
  string input;
  cout << "*** Enter word to search: ";
  getline(cin, input);
  int high = data.size() - 1;
  int low = 0;
  int count = 0;
  while (low <= high){
    count += 1;
    int mid = (high + low + 1) / 2;
    cout << setw(4) << count << ". Comparing to: " << data.at(mid) << endl;
    if (input == data.at(mid)){
      cout << input << " was found." << endl;
      break;
    } else if (input > data.at(mid)){
        low = mid + 1;
    } else if (input < data.at(mid)){
        high = mid - 1;
    } else{
      cout << input << " was NOT found." << endl;
      break;
    }
  }
}
/*------------------------*/
void extract_all_data(vector<string>& dict, vector<string>& mspelled, vector<string>& correct)
{
    extract_dict(dict, "dictionary.txt");
    extract_misspelled(mspelled, correct, "misspelled.txt");
}
/*------------------------*/
int main()
{
    vector<string> dict, mspelled, correct;
    extract_all_data(dict, mspelled, correct);
    display_header(dict.size(), correct.size());
    unsigned int choice;
    do {
        display_menu_options();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
        case 1:
            misspelled(mspelled, correct);
            break;
        case 2:
            full_dict(dict);
            break;
        case 3:
            display_in_range(dict, mspelled, correct);
            break;
        case 4:
            bsearch(dict);
            break;
        case 5:
            cout << "Exiting." << endl;
            break;
        default:
            cout << "No menu option " << choice << ". "
                 << "Please try again." << endl;
        }
    } while ((choice != 5) && !cin.eof());

    return 0;
}
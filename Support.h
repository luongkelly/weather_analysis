/*
Kelly Luong
This is a header file that declares everything in the structs and classes
*/

#include <string> 
using namespace std;

struct location {
  string city;
  string state;
  string geocode;

  int num();

  bool operator<(const location &) const;
  bool operator==(const location &) const;
};

struct data {
  int month;
  float precip;
  int temp;
};

class list {
  struct node {
    node(const location &);
    ~node();

    void incorp(const data &);
	  void print_station();
    void print_data();

    location station;

    int *N;

    float *total_precip;
    float *max_precip;
    float *min_precip;

    int *total_temp;
    int *max_temp;
    int *min_temp;

    node *next;
  };

  public:
    list();
    ~list();

	void insert(const location &, const data &);
    void print(const char *);

  private:
    node *head;
};

string month_name(int);

/*
 * CS106L Assignment 5: TreeBook
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

#include <iostream>
#include <string>

class User
{
public:
  User(const std::string& name);
  void add_friend(const std::string& name);
  std::string get_name() const;
  size_t size() const;
  void set_friend(size_t index, const std::string& name);


//_______ Copy Constructor_____________

  User(const User& other); 
 //___________destructor _____________

  ~User();
  
  User(User&&) = delete;
  User& operator=(User&&) = delete;
  
  //______________Copy Assignment Operator _______________

  User& operator=(const User& other); 
  
  //______________ operator<< ________________

  friend std::ostream& operator<<(std::ostream& os, const User& user); 

  //___________operator+=_____________

  User& operator+=(User& other);

  //________operator<___________

  bool operator<(const User& other) const;;


  
  
private:
  std::string _name;
  std::string* _friends;
  size_t _size;
  size_t _capacity;
};
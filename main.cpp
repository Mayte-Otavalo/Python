#include <algorithm>
#include <type_traits>
#include <vector>
#include <optional>
#include <string> 
#include "autograder/utils.hpp"
 
 /**
  * A course. This should be familiar from Assignment 1!
  */
struct Course{
  std::string title;
  std::string number_of_units;
  std::string quarter;


bool operator==(const Course& other) const{
  return title == other.title && number_of_units == other.number_of_units &&
    quarter == other.quarter;
  }
};
 
class CourseDatabase{
  public:
    CourseDatabase(std::string filename){
      auto lines = read_lines(filename);
      std::transform(lines.begin(),
                    lines.end(),
                    std::back_inserter(courses),
                    [](std::string line) {
                      auto parts = split(line, ',');
                      return Course{ parts[0], parts[1], parts[2] };
                    });
}

std::optional<Course> find_course(std::string course_title){
     auto it = std::find_if(courses.begin(), courses.end(),
                           [&course_title](const Course& c) {
                             return c.title == course_title;
                           });
     
     if (it != courses.end()) {
       return *it;
     }
     return std::nullopt;
}
 
  private:
    std::vector<Course> courses;
 };
 
 int main(int argc, char* argv[]){
   static_assert(
     !std::is_same_v<std::invoke_result_t<decltype (&CourseDatabase::find_course), 
                       CourseDatabase, std::string>,
                     FillMeIn>,
     "You must change the return type of CourseDatabase::find_course to "
     "something other than FillMeIn.");
 
   if (argc == 2) {
     CourseDatabase db("autograder/courses.csv");
     auto course = db.find_course(argv[1]);
     
     std::string output = course ? 
       "Found course: " + course->title + "," + course->number_of_units + "," + course->quarter
       : "Course not found.";
     
     /********************************************************
      DO NOT MODIFY ANYTHING BELOW THIS LINE PLEASE
     ********************************************************/
 
     std::cout << output << std::endl;
     return 0;
   }
   
   return run_autograder();
}
#include "ZappyData.hpp"

int	main()
{
  std::string	toto("{toto, titi titi titi, tata tata}");
  std::vector<std::vector<std::string> > vec;
  
  vec = ZappyData::deserialize(toto);
  for (std::vector<std::vector<std::string> >::iterator it = vec.begin(); it != vec.end(); ++it)
    {
      for (std::vector<std::string>::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2)
	{
	  std::cout << "item: " << *it2 << std::endl;
	}
      std::cout << std::endl;
    }
}

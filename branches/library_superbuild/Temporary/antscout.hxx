#ifndef ANTSCOUT_HXX
#define ANTSCOUT_HXX

#include<ostream>

namespace ants
{

class antsCout : public std::ostream
{
public:
  explicit antsCout():usercout(NULL)
  {
  }
  ~antsCout()
  {
  }

  // set the output stream
  void set_ostream( std::ostream* ostrm )
  {
    // accept the stream if it is not null
    if( !(bool)usercout )
      {
	usercout = ostrm ;
      }
  }

  // insertion operator
  template< typename T >
  antsCout& operator<< ( T t )
  {
    if( usercout != NULL )
      {
	(*usercout) << t ;
      }
    return (*this) ;
  }
  // insertion operator for 'std::endl' like types
  antsCout& operator<< ( std::ostream& (*fptr)( std::ostream& ) )
  {
    if( usercout != NULL )
      {
	(*usercout) << fptr ;
      }
    return (*this) ;
  }
private:
  std::ostream* usercout ;
};

antsCout antscout ;

} // namespace ants

#endif // ANTSCOUT_HXX

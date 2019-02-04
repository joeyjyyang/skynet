// Generated by gencpp from file location_monitor/LandmarkDistance.msg
// DO NOT EDIT!


#ifndef LOCATION_MONITOR_MESSAGE_LANDMARKDISTANCE_H
#define LOCATION_MONITOR_MESSAGE_LANDMARKDISTANCE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace location_monitor
{
template <class ContainerAllocator>
struct LandmarkDistance_
{
  typedef LandmarkDistance_<ContainerAllocator> Type;

  LandmarkDistance_()
    : name()
    , distance(0.0)  {
    }
  LandmarkDistance_(const ContainerAllocator& _alloc)
    : name(_alloc)
    , distance(0.0)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _name_type;
  _name_type name;

   typedef double _distance_type;
  _distance_type distance;





  typedef boost::shared_ptr< ::location_monitor::LandmarkDistance_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::location_monitor::LandmarkDistance_<ContainerAllocator> const> ConstPtr;

}; // struct LandmarkDistance_

typedef ::location_monitor::LandmarkDistance_<std::allocator<void> > LandmarkDistance;

typedef boost::shared_ptr< ::location_monitor::LandmarkDistance > LandmarkDistancePtr;
typedef boost::shared_ptr< ::location_monitor::LandmarkDistance const> LandmarkDistanceConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::location_monitor::LandmarkDistance_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::location_monitor::LandmarkDistance_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace location_monitor

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'location_monitor': ['/home/joey/catkin_ws/src/location_monitor/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::location_monitor::LandmarkDistance_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::location_monitor::LandmarkDistance_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::location_monitor::LandmarkDistance_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::location_monitor::LandmarkDistance_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::location_monitor::LandmarkDistance_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::location_monitor::LandmarkDistance_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::location_monitor::LandmarkDistance_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e2f8ddf8c9e39a28149179429f5ae342";
  }

  static const char* value(const ::location_monitor::LandmarkDistance_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe2f8ddf8c9e39a28ULL;
  static const uint64_t static_value2 = 0x149179429f5ae342ULL;
};

template<class ContainerAllocator>
struct DataType< ::location_monitor::LandmarkDistance_<ContainerAllocator> >
{
  static const char* value()
  {
    return "location_monitor/LandmarkDistance";
  }

  static const char* value(const ::location_monitor::LandmarkDistance_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::location_monitor::LandmarkDistance_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string name # Name of the landmark\n\
float64 distance # Distance to the landmark, in meters.\n\
";
  }

  static const char* value(const ::location_monitor::LandmarkDistance_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::location_monitor::LandmarkDistance_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.name);
      stream.next(m.distance);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct LandmarkDistance_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::location_monitor::LandmarkDistance_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::location_monitor::LandmarkDistance_<ContainerAllocator>& v)
  {
    s << indent << "name: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.name);
    s << indent << "distance: ";
    Printer<double>::stream(s, indent + "  ", v.distance);
  }
};

} // namespace message_operations
} // namespace ros

#endif // LOCATION_MONITOR_MESSAGE_LANDMARKDISTANCE_H

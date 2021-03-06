#ifndef Dh_DDMM_IceRay_type_ray__trace_HPP_
 #define Dh_DDMM_IceRay_type_ray__trace_HPP_
// GS_DDMRM::S_IceRay::S_type::S_ray::GC_trace


 #include "../basic/size.hpp"
#include "IceRay/geometry/_type/state.hpp"


 #include "./simple.hpp"

 namespace GS_DDMRM
  {
   namespace S_IceRay
    {
     namespace S_type
      {
       namespace S_ray
        {

         class GC_trace
          : public GS_DDMRM::S_IceRay::S_type::S_ray::GC_simple
          {
           public:
             typedef GS_DDMRM::S_IceRay::S_geometry::S__type::GC_state  T_state;

             enum Ee_type1
              {
                En_type1_Unknown,
                En_type1Eye
               ,En_type1Light
               ,En_type1Reflected
               ,En_type1Refracted
               ,En_type1Teleported
               ,En_type1Broken  //! Pass to thin object like plane. Same medium but different direction.
              };

             enum Ee_status
              {
                 En_statusActive
                ,En_statusDiscarded
              };

             typedef GS_DDMRM::S_IceRay::S_type::GT_size               T_size;
             typedef GS_DDMRM::S_IceRay::S_type::GT_uint64             T_uint64;
             typedef GS_DDMRM::S_IceRay::S_type::GT_scalar             T_scalar;

             typedef GS_DDMRM::S_IceRay::S_type::S_ray::GC_line   T_line;
             typedef GS_DDMRM::S_IceRay::S_type::S_ray::GC_simple T_simple;

           public:
             GC_trace()
              :GC_trace( T_simple( T_line{} ), En_type1_Unknown )
              {
              }

             explicit GC_trace( T_line const& P_line )
              :GC_trace( T_simple( P_line ), En_type1_Unknown )
              {
              }

             explicit GC_trace( T_simple const& P_simple )
              :GC_trace( P_simple, En_type1_Unknown )
              {
              }

             GC_trace( T_simple const& P_simple, Ee_type1 const& P_type  )
              :T_simple( P_simple )
              ,M_depth( 0 )
              ,M_type( P_type )
              ,M_coefficient( 1 )
              ,M_ior( 1.000277 )
              {
               M_status = En_statusActive;
              }

             GC_trace const& operator=( T_simple const& P_simple )
              {
               (T_simple)*this = P_simple;
               return *this;
              }

           public:
             T_size    M_depth;
             T_uint64  M_UID;
             Ee_type1  M_type;
             Ee_status M_status;

             T_scalar  M_ior;
             T_scalar  M_coefficient;
             T_state   M_state;
             T_size    M_geometryID;
          };

        }
      }
    }
  }

#endif


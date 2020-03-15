#ifndef _DDMRM_IceRAY_geometry_blobby_vacuum_HPP_
 #define _DDMRM_IceRAY_geometry_blobby_vacuum_HPP_

#include "./_element.hpp"


 namespace GS_DDMRM
  {
   namespace S_IceRay
    {
     namespace S_geometry
      {
       namespace S_blobby
        {

         class GC_vacuum
         : public GS_DDMRM::S_IceRay::S_geometry::S_blobby::GC__element
          {
           public:
             typedef GS_DDMRM::S_IceRay::S_type::GT_scalar                       T_scalar;
             typedef GS_DDMRM::S_IceRay::S_type::S_coord::GT_scalar              T_coord;
             typedef GS_DDMRM::S_IceRay::S_geometry::S__pure::GC__base           T_geometry;

           public:
             GC_vacuum( );
             GC_vacuum( T_coord  const& P_lo, T_coord  const& P_hi );
             GC_vacuum( T_box const& P_box );
            ~GC_vacuum( );

           public:
             void Fv_reset( T_state &P_intersect )const;
             T_size Fv_weight( )const;

           public:
             bool        Fv_intersect( T_scalar &P_lambda, T_state &P_intersect, T_ray const& P_ray )const;
             void        Fv_normal   ( T_coord &P_normal, T_coord const& P_point, T_state const& P_state )const;
             T_location  Fv_inside   ( T_coord const& P_point/*, T_state const&P_intersect*/ )const;

           public:
             bool     Fv_coefficient( T_coefficient::T_typedef & P_coefficient, T_state const& P_state, T_ray const& P_ray )const;
             T_scalar Fv_intensity( T_coord const& P_poin )const;
           private:
             struct C_intersect;
          };
        }
      }
    }
  }

#endif

#ifndef _DDMM_IceRAY_geometry_transfrom_identity_H_
 #define _DDMM_IceRAY_geometry_transfrom_identity_H_

#include "../../type/basic/scalar.hpp"
#include "../../type/math/coord.hpp"




#include "../_pure/_base.hpp"
#include "../_pure/cluster.hpp"
#include "../_pure/intersect.hpp"
#include "../_pure/normal.hpp"
#include "../_pure/inside.hpp"
#include "../_pure/distance.hpp"
#include "../_pure/uvw.hpp"
#include "../_pure/transform.hpp"


#include "../volumetric/vacuum.hpp"



 namespace GS_DDMRM
  {
   namespace S_IceRay
    {
     namespace S_geometry
      {
       namespace S_transform
        {

         class GC_identity
          : public GS_DDMRM::S_IceRay::S_geometry::S__pure::GC_cluster
          , public GS_DDMRM::S_IceRay::S_geometry::S__pure::GC_intersect
          , public GS_DDMRM::S_IceRay::S_geometry::S__pure::GC_normal
          , public GS_DDMRM::S_IceRay::S_geometry::S__pure::GC_inside
          , public GS_DDMRM::S_IceRay::S_geometry::S__pure::GC_distance
          , public GS_DDMRM::S_IceRay::S_geometry::S__pure::GC_uvw
          {
           public:
             typedef GS_DDMRM::S_IceRay::S_type::GT_scalar              T_scalar;
             typedef GS_DDMRM::S_IceRay::S_type::S_coord::GT_scalar     T_coord;
             typedef GS_DDMRM::S_IceRay::S_type::S_matrix::GT_matrix    T_matrix;

             typedef GS_DDMRM::S_IceRay::S_geometry::S__pure::GC__base  T_geometry, T__base;

           public:
             GC_identity( );
             explicit GC_identity(  T__base *P_child );
            ~GC_identity( );

           public:
             void    Fv_reset( T_state &P_state )const;
             T_size  Fv_weight( )const;
             T_size const& Fv_id( T_state const&P_state )const;

           public:
             T_size const&    Fv_quantity()const;
             T__base*         Fv_base( T_size const& P_index )const;
             bool             Fv_fragment( T_fragment & P_fragment, T_state const& P_state )const;
             bool             Fv_intersect( T_scalar &P_lambda, T_state &P_state, T_ray const& P_ray  )const;
             void             Fv_normal   ( T_coord &P_normal, T_coord const& P_point,  T_state const& P_state )const;
             T_location       Fv_inside( T_coord const& P_point/*, T_state const&P_state*/ )const;
             T_scalar         Fv_distance( T_coord const& P_point )const;
             bool             Fv_uvw( T_coord & P_uvw, T_coord const& P_point, T_state const& P_state)const;

           public:
             bool  F_child( T__base *P_child );
           //TODO T__base* F_child( );
           private:
             typedef GS_DDMRM::S_IceRay::S_geometry::S__pure::GC_intersect    T2_intersect;
             typedef GS_DDMRM::S_IceRay::S_geometry::S__pure::GC_normal       T2_normal;
             typedef GS_DDMRM::S_IceRay::S_geometry::S__pure::GC_inside       T2_inside;
             typedef GS_DDMRM::S_IceRay::S_geometry::S__pure::GC_distance     T2_distance;
             typedef GS_DDMRM::S_IceRay::S_geometry::S__pure::GC_uvw          T2_uvw;

           private:
             struct C2_geometry
              {
               T__base      *M2__base;
               T2_intersect *M2_intersect;
               T2_normal    *M2_normal;
               T2_inside    *M2_inside;
               T2_distance  *M2_distance;
               T2_uvw       *M2_uvw;
              };

             C2_geometry  M2_geometry;

           public:
             typedef GS_DDMRM::S_IceRay::S_geometry::GC_vacuum T_vacuum;
             static T_vacuum & Fs_vacuum();
           private:
             struct C_intersect;
          };

        }
      }
    }
  }

#endif

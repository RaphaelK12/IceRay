#ifndef Dh_DDMRM_Iceray_material_compute_transmission_blossom_hexagon_HPP_
 #define Dh_DDMRM_Iceray_material_compute_transmission_blossom_hexagon_HPP_

// GS_DDMRM::S_IceRay::S_material::S_compute::S_transmission::S_blossom::GC_hexagon

#include "../../instruction.hpp"
#include "IceRay/utility/random.hpp"
#include "IceRay/utility/table/hexagon.hpp"
#include "math/geometry/deg2rad.hpp"

 namespace GS_DDMRM
  {
   namespace S_IceRay
    {
     namespace S_material
      {
       namespace S_compute
        {
         namespace S_transmission
          {
           namespace S_blossom
            {

             class GC_hexagon
              : public GS_DDMRM::S_IceRay::S_material::S_compute::GC_instruction
              {
               public:
                 typedef GS_DDMRM::S_IceRay::S_type::GT_scalar             T_scalar;
                 typedef GS_DDMRM::S_IceRay::S_type::S_coord::GT_scalar    T_coord;
                 typedef GS_DDMRM::S_IceRay::S_type::S_coord::GT_scalar2D  T_coord2D;
                 typedef GS_DDMRM::S_IceRay::S_type::S_color::GT_scalar    T_color;

                 typedef GS_DDMRM::S_IceRay::S_material::S_compute::GC_memory   T_memory;

                 enum Ee_input
                  {
                    En_inCoord_Normal = 1
                   ,En_inSize_Leader = 1
                   ,En_inSize_Count   = 0
                   ,En_inScalar_Angle = 0
                   ,En_inScalar_Gauss = 1
                  };
                 enum Ee_output
                  {
                    En_outSize_RayCount=0
                   ,En_outRay_out=1
                  };

               public:
                 GC_hexagon
                  (
                    T_size const& P_normal    = 1
                   ,T_size const& P_inLeader = 0
                   ,T_size const& P_inCount   = 1
                   ,T_size const& P_inAngle   = 0
                   ,T_size const& P_inGauss   = 1
                  )
                  {
                   static auto dummy = F2s_init();

                   F_input<T_coord>(   En_inCoord_Normal,  P_normal    );
                   F_input<T_size>(    En_inSize_Leader,   P_inLeader );
                   F_input<T_size>(    En_inSize_Count,    P_inCount   );
                   F_input<T_scalar>(  En_inScalar_Angle,  P_inAngle   );
                   F_input<T_scalar>(  En_inScalar_Gauss,  P_inGauss   );

                 //F_output<T_size>( En_outSize_RayCount,     P_outSize_RayCount );
                  }

               public:
                 bool    Fv_execute( T_beam &P_next, T_pigment::T_intersect const& P_intersect, T_state const& P_state )const
                  {
                   T_coord  const& I_normal   = M2_memoryCoord->Fv_load(  F_input<T_coord >( En_inCoord_Normal ) );
                   T_size   const& I_leader   = M2_memorySize->Fv_load(   F_input<T_scalar>( En_inSize_Leader   ) );
                   T_size   const& I_count    = M2_memorySize->Fv_load(   F_input<T_size  >( En_inSize_Count   ) );
                   T_scalar const& I_angle    = M2_memoryScalar->Fv_load( F_input<T_scalar>( En_inScalar_Angle ) );
                   T_scalar const& I_gauss    = M2_memoryScalar->Fv_load( F_input<T_scalar>( En_inScalar_Gauss ) );

                   auto      & I_original = P_next.Fv_expose( I_leader );
                   F_execute
                    (
                      P_next
                     ,I_normal
                     ,I_original
                     ,I_count
                     ,I_angle
                     ,I_gauss
                    );
                   I_original.M_status = T_ray::En_statusDiscarded;
                   return true;
                  }

               public:
                 T_size F_execute
                 (
                   T_beam        & P_next
                  ,T_coord  const& P_normal
                  ,T_ray    const& P_heading
                  ,T_size   const& P_count
                  ,T_scalar const& P_angle
                  ,T_scalar const& P_gauss
                  )const
                  {
                   T_size const I_count = M2s_table.F_index()[ P_count ];

                   T_coord I_y = P_heading.M_direction;
                   T_coord I_x; ::math::linear::vector::cross( I_x, I_y, P_normal ); ::math::linear::vector::length( I_x, T_scalar( 1 ) );
                   T_coord I_z; ::math::linear::vector::cross( I_z, I_x, I_y );      ::math::linear::vector::length( I_z, T_scalar( 1 ) );

                   auto I_bounce = ::math::linear::vector::angle( P_heading.M_direction, P_normal );

                   if( ::math::geometry::deg2rad( 90 ) < I_bounce )
                    {
                     I_bounce = ::math::geometry::deg2rad( 180 ) - I_bounce;
                    }

                   T_scalar I_fix = P_angle/T_scalar(2) + I_bounce - ::math::geometry::deg2rad( 90 );

                   if( T_scalar(0) < I_fix )
                    { // Need correction
                     T_scalar a = cos( I_fix ), b = sin( I_fix );
                     T_coord I_newY;

                     ::math::linear::vector::combine( I_newY, a, I_y, b, I_z  );
                     ::math::linear::vector::length( I_y, I_newY, T_scalar( 1 ) );

                     ::math::linear::vector::cross( I_z, I_x, I_y );
                     ::math::linear::vector::length( I_z, T_scalar( 1 ) );
                    }

                   T_scalar I_radius = sin( P_angle/T_scalar( 2 ) );
                   ::math::linear::vector::length( I_x, I_radius );
                   ::math::linear::vector::length( I_z, I_radius );
                   I_radius *= I_radius;

                   auto I_perimeter = M2s_table.F_radius()[ P_count ];
                   T_coord I_direction;
                   for( T_size I_index=0; I_index < I_count; ++I_index )
                    {
                     T_coord2D I_disc2d;
                     ::math::linear::vector::scale( I_disc2d, T_scalar(1)/I_perimeter, M2s_table.F_spot()[ I_index ] );

                     T_scalar I_height = sqrt( T_scalar( 1 ) - I_radius * ::math::linear::vector::dot( I_disc2d, I_disc2d ) );
                     ::math::linear::vector::combine( I_direction, I_disc2d[0], I_x, I_height, I_y, I_disc2d[1], I_z );
                     ::math::linear::vector::length( I_direction, T_scalar( 1 ) );

                      T_scalar I_check = ::math::linear::vector::dot( I_direction, P_normal );
                      if( I_check < T_scalar(0) )
                       {
                        I_check = I_check;
                        continue;
                       }
                     {
                      P_next.Fv_push();
                      auto & I_ray = P_next.Fv_top();

                      I_ray.M_geometryID = P_heading.M_geometryID;
                      I_ray.M_depth  = P_heading.M_depth;
                      I_ray.M_origin = P_heading.M_origin;
                      I_ray.M_state = P_heading.M_state;
                      I_ray.M_direction = I_direction;
                      I_ray.M_type = P_heading.M_type;
                      I_ray.M_ior  = P_heading.M_ior;
                      I_ray.M_intesity = P_heading.M_intesity/ I_count;  //!< todo Not optimised
                      I_ray.M_coefficient = T_scalar(1)/ I_count;     //!< todo Not optimised
                     }

                    }

                  //M2_memoryRay->Fv_store(  F_output<T_size>(En_outRay_Reflected), I_rectified );
                  //M2_memorySize->Fv_store( F_output<T_size>(En_outSize_RayCount), 1 );
                  return I_count;
                 }

               private:

               private:
                 typedef GS_DDMRM::S_IceRay::S_material::S_compute::S_data::GC__base<T_size>    T2_memorySize;
                 typedef GS_DDMRM::S_IceRay::S_material::S_compute::S_data::GC__base<T_coord>   T2_memoryCoord;
                 typedef GS_DDMRM::S_IceRay::S_material::S_compute::S_data::GC__base<T_scalar>  T2_memoryScalar;
                 typedef GS_DDMRM::S_IceRay::S_material::S_compute::S_data::GC__base<T_color>   T2_memoryColor;

               public:
                 void    Fv_memory( T_memory * P_memory  )
                  {
                   F1_memory() = P_memory;
                   M2_memorySize   = dynamic_cast<T2_memorySize * >( P_memory->F_get<T_size>() );
                   M2_memoryCoord  = dynamic_cast<T2_memoryCoord* >( P_memory->F_get<T_coord>() );
                   M2_memoryColor  = dynamic_cast<T2_memoryColor* >( P_memory->F_get<T_color>() );
                   M2_memoryScalar = dynamic_cast<T2_memoryScalar* >( P_memory->F_get<T_scalar>() );
                  }
               private:
                 T2_memorySize     *M2_memorySize;
                 T2_memoryCoord    *M2_memoryCoord;
                 T2_memoryColor    *M2_memoryColor;
                 T2_memoryScalar   *M2_memoryScalar;
               private:
                 static bool F2s_init(){ M2s_table.F_init( 130 ); return true; }

                 static GS_DDMRM::S_IceRay::S_utility::S_table::GC_hexagon    M2s_table;
              };

            }
          }
        }
      }
    }
  }

#endif
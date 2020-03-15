#ifndef Dh_DDMRM_Iceray_material_compute_transmission_refract_one_HPP_
 #define Dh_DDMRM_Iceray_material_compute_transmission_refract_one_HPP_

 #include <tuple>
 #include <limits>

 #include "../../instruction.hpp"


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
           namespace S_refract
            {

               class GC_one
                : public GS_DDMRM::S_IceRay::S_material::S_compute::GC_instruction
                {
                 public:
                   typedef GS_DDMRM::S_IceRay::S_type::GT_scalar             T_scalar;
                   typedef GS_DDMRM::S_IceRay::S_type::S_coord::GT_scalar    T_coord;
                   typedef GS_DDMRM::S_IceRay::S_type::S_color::GT_scalar    T_color;

                   typedef GS_DDMRM::S_IceRay::S_material::S_compute::GC_memory   T_memory;

                   enum Ee_input
                    {
                      En_inCoord_Point  = 0
                     ,En_inCoord_Normal = 1
                     ,En_inColor_Transmittance = 0
                     ,En_inScalar_IOR   = 0
                    };
                   enum Ee_output
                    {
                      En_outSize_RayCount=0
                     ,En_outRay_refracted=1
                    };

                 public:
                   GC_one
                    (
                      T_size const& P_point     = 0
                     ,T_size const& P_normal    = 1
                     ,T_size const& P_transmittance   = 0
                     ,T_size const& P_ior       = 0
                   //,T_size const& P_outSize_rayCount = 0,
                   //,T_size const& P_outRay_refracted = 1
                    )
                    {
                     F_input<T_coord>(  En_inCoord_Point,       P_point     );
                     F_input<T_coord>(  En_inCoord_Normal,      P_normal    );
                     F_input<T_color>(  En_inColor_Transmittance,     P_transmittance   );
                     F_input<T_scalar>( En_inScalar_IOR,        P_ior       );

                   //F_output<T_size>( En_outSize_RayCount,     P_outSize_RayCount );
                   //F_output<T_ray>(  En_outRay_refracted,     P_outRay_refracted );
                    }

                 public:
                   bool    Fv_execute( T_beam &P_next, T_pigment::T_intersect const& P_intersect, T_state const& P_state )const
                    {


                     auto const&  I_incoming = P_intersect.M_incoming;
                     auto const&  I_intersect = P_intersect.M_intersection;
                     T_coord  const& I_point    = M2_memoryCoord->Fv_load( F_input<T_coord>(  En_inCoord_Point ) );
                     T_coord  const& I_normal   = M2_memoryCoord->Fv_load( F_input<T_coord>(  En_inCoord_Normal) );
                     T_scalar const& I_IOR      = M2_memoryScalar->Fv_load( F_input<T_scalar>( En_inScalar_IOR  ) );
                     T_color  const& I_transmittance  = M2_memoryColor->Fv_load( F_input<T_color>(  En_inColor_Transmittance ) );


                     T_scalar I_air = 1.000277;
                     T_scalar I_watter = I_IOR;

                     if( 1.000277 != I_incoming.M_ior )
                      {
                       I_air = I_IOR;
                       I_watter = 1.000277;
                      }

                     P_next.Fv_push();
                     auto &I_refracted = P_next.Fv_top();
                     I_refracted.M_depth = I_incoming.M_depth + 1;
                     I_refracted.M_origin = I_point;
                     I_refracted.M_state = I_intersect.M_state;
                     I_refracted.M_geometryID = I_intersect.M_geometryID;

                     switch( ::math::linear::vector::refract( I_refracted.M_direction, I_incoming.M_direction, I_normal, I_air, I_watter ) )
                      {
                       case( 0 ):
                       case( -1 ):
                        {
                         ::math::linear::vector::reflect( I_refracted.M_direction, I_incoming.M_direction, I_normal );
                          ::math::linear::vector::length( I_refracted.M_direction, T_scalar(1) );
                         I_refracted.M_type = T_ray::En_type1Reflected;
                         I_refracted.M_ior  = I_air;
                        }break;
                       case( +1 ):
                        {
                         I_refracted.M_type = T_ray::En_type1Refracted;
                         I_refracted.M_ior  = I_watter;
                        }break;
                      }

                     ::math::linear::vector::length( I_refracted.M_direction, T_scalar(1) );

                      ::color::operation::multiply( I_refracted.M_intesity, I_transmittance, I_incoming.M_intesity );

                     I_refracted.M_coefficient = T_scalar(1);


                     //M2_memoryRay->Fv_store( F_output()[ T_memory::En_size][ En_outRay_Rayrefracted ], I_refracted );
                     //M2_memorySize->Fv_store( F_output()[ T_memory::En_size][ En_outSize_RayCount ], 1 );

                     return true;
                    }

                 private:
                   typedef GS_DDMRM::S_IceRay::S_material::S_compute::S_data::GC__base<T_size>    T2_memorySize;
                   typedef GS_DDMRM::S_IceRay::S_material::S_compute::S_data::GC__base<T_coord>   T2_memoryCoord;
                   typedef GS_DDMRM::S_IceRay::S_material::S_compute::S_data::GC__base<T_color>   T2_memoryColor;
                   typedef GS_DDMRM::S_IceRay::S_material::S_compute::S_data::GC__base<T_scalar>  T2_memoryScalar;
                 //typedef GS_DDMRM::S_IceRay::S_material::S_compute::S_data::GC__base<T_ray>     T2_memoryRay;

                 public:
                   void    Fv_memory( T_memory * P_memory  )
                    {
                     F1_memory() = P_memory;
                     M2_memorySize   = dynamic_cast<T2_memorySize * >( P_memory->F_get<T_size>(    ) );
                     M2_memoryCoord  = dynamic_cast<T2_memoryCoord* >( P_memory->F_get( T_memory::En_coord3D ) );
                     M2_memoryColor  = dynamic_cast<T2_memoryColor* >( P_memory->F_get<T_color>(   ) );
                     M2_memoryScalar = dynamic_cast<T2_memoryScalar* >( P_memory->F_get<T_scalar>(   ) );
                   //M2_memoryRay    = dynamic_cast<T2_memoryRay  * >( P_memory->F_get( T_memory::En_ray     ) );
                    }

                 private:
                   T2_memorySize     *M2_memorySize;
                   T2_memoryCoord    *M2_memoryCoord;
                   T2_memoryColor    *M2_memoryColor;
                   T2_memoryScalar   *M2_memoryScalar;
                 //T2_memoryRay      *M2_memoryRay;
                 //T_medium          *M2_medium;
                };

            }
          }
        }
      }
    }
  }

#endif
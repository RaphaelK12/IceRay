#ifndef Dh_DDMRM_Iceray_material_compute_light_swarm0_HPP_
 #define Dh_DDMRM_Iceray_material_compute_light_swarm0_HPP_


 #include "../../../type/basic/size.hpp"
 #include "../../../type/color.hpp"
 #include "../../../type/math/coord.hpp"
 #include "../../../light/_pure.hpp"
 #include "../../../light/type/spot.hpp"
 #include "../../../geometry/_pure/intersect.hpp"

 #include "../instruction.hpp"


 namespace GS_DDMRM
  {
   namespace S_IceRay
    {
     namespace S_material
      {
       namespace S_compute
        {
         namespace S_light
          {

           class GC_swarmB// Create spots from light from common memory. Do cull optionally
            : public GS_DDMRM::S_IceRay::S_material::S_compute::GC_instruction
            {
             public:

               typedef GS_DDMRM::S_IceRay::S_type::GT_bool               T_bool;
               typedef GS_DDMRM::S_IceRay::S_type::GT_size               T_size;
               typedef GS_DDMRM::S_IceRay::S_type::S_coord::GT_scalar    T_coord;
               typedef GS_DDMRM::S_IceRay::S_type::GT_scalar             T_scalar;

               typedef GS_DDMRM::S_IceRay::S_light::S_type::GC_spot      T_spot;
               typedef GS_DDMRM::S_IceRay::S_light::GC__pure             T_light;

               typedef GS_DDMRM::S_IceRay::S_geometry::S__type::GC_state      T_state;
               typedef GS_DDMRM::S_IceRay::S_geometry::S__pure::GC_intersect T_geometry;

               typedef GS_DDMRM::S_IceRay::S_material::S_compute::GC_memory      T_memory;
               typedef GS_DDMRM::S_IceRay::S_material::S_compute::GC_instruction T_instruction;

               enum Ee_input
                {
                  En_inLight_Light    = 0
                 ,En_inCoord_Point    = 0
                 ,En_inCoord_Normal   = 1
                 ,En_inSpot_Begin     = 0
                 ,En_inBool_Cull      = 0
                };
               enum Ee_output{ En_outSize_SpotCount = 0 };

             public:
               explicit GC_swarmB
                (
                  T_size const& P_outSpot_Count    = 0
                 ,T_size const& P_inLight_Light    = 0
                 ,T_size const& P_inCoord_Point    = 0
                 ,T_size const& P_inCoord_Normal   = 0
                 ,T_size const& P_inSpot_Begin     = 0
                 ,T_size const& P_inBool_Cull      = 0
                )
                {
                 F_output<T_size>( En_outSize_SpotCount, P_outSpot_Count );

                 F_input<T_light>( En_inLight_Light,  P_inLight_Light  );
                 F_input<T_coord>( En_inCoord_Point,  P_inCoord_Point  );
                 F_input<T_coord>( En_inCoord_Normal, P_inCoord_Normal );
                 F_input<T_spot>(  En_inSpot_Begin,   P_inSpot_Begin   );
                 F_input<T_bool>(  En_inBool_Cull,    P_inBool_Cull    );
                }

             public:
               bool    Fv_execute( T_beam &P_next, T_pigment::T_intersect const& P_intersect, T_state const& P_state )const
                {
                 auto const&  I_incoming = P_intersect.M_incoming;
               //T_ray     const&   I_ray      = M2_memoryRay->Fv_load( F_input()[ T_memory::En_ray ][ En_inRay_incoming] );

                 T_light const* I_light  = M2_memoryLight->Fv_load( F_input()[ T_memory::En_light ][ En_inLight_Light ] );
                 T_coord const& I_point  = M2_memoryCoord->Fv_load( F_input<T_coord>( En_inCoord_Point ) );
                 T_coord        I_normal = M2_memoryCoord->Fv_load( F_input<T_coord>( En_inCoord_Normal ) );
                 T_size  const& I_start  = F_input<T_spot>( En_inSpot_Begin );
                 T_bool  const& I_cull   = M2_memoryBool->Fv_load( F_input()[ T_memory::En_bool][ En_inBool_Cull ] );

                 M2_swarm.F_clear();
                 I_light->Fv_swarm( M2_swarm, I_point /*,P_state*/ );

                 T_size I_count = 0;

                 T_coord I_2light;
                 for( auto const& I_spot : M2_swarm )
                  {
                   if( true == I_cull )
                    {
                     ::math::linear::vector::subtraction( I_2light, I_spot.F_center(), I_point );
                   //::math::linear::vector::length( I_2light, T_scalar(1) );

                     if( ::math::linear::vector::dot( I_2light, I_normal ) < 0 )
                      {
                       continue;
                      }
                    }

                   M2_memorySpot->Fv_store( I_start + I_count, I_spot );
                   ++I_count;
                  }

                 M2_memorySize->Fv_store( F_output<T_size>( En_outSize_SpotCount ), I_count );
                 return true;
                }

               mutable T_light::T_swarm M2_swarm;

             private:
               typedef GS_DDMRM::S_IceRay::S_material::S_compute::S_data::GC__base<T_bool>   T2_memoryBool;
               typedef GS_DDMRM::S_IceRay::S_material::S_compute::S_data::GC__base<T_size>   T2_memorySize;
               typedef GS_DDMRM::S_IceRay::S_material::S_compute::S_data::GC__base<T_coord>  T2_memoryCoord;
               typedef GS_DDMRM::S_IceRay::S_material::S_compute::S_data::GC__base<T_spot>   T2_memorySpot;
               typedef GS_DDMRM::S_IceRay::S_material::S_compute::S_data::GC__base<T_light*> T2_memoryLight;

             public:
               void    Fv_memory( T_memory * P_memory  )
                {
                 T_instruction::Fv_memory( P_memory );
                 M2_memoryBool  = dynamic_cast<T2_memoryBool * >( P_memory->F_get<T_bool>(  ) );
                 M2_memorySize  = dynamic_cast<T2_memorySize * >( P_memory->F_get<T_size>(  ) );
                 M2_memoryCoord = dynamic_cast<T2_memoryCoord* >( P_memory->F_get( T_memory::En_coord ) );
                 M2_memorySpot  = dynamic_cast<T2_memorySpot * >( P_memory->F_get( T_memory::En_spot  ) );
                 M2_memoryLight = dynamic_cast<T2_memoryLight* >( P_memory->F_get( T_memory::En_light ) );
                }

             private:
               T2_memoryBool     *M2_memoryBool;
               T2_memorySize     *M2_memorySize;
               T2_memoryCoord    *M2_memoryCoord;
               T2_memorySpot     *M2_memorySpot;
               T2_memoryLight    *M2_memoryLight;
           };

          }
        }
      }
    }
  }

#endif
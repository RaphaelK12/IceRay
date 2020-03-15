#ifndef Dh_IceRay_material_illumination_beckmann_hpp_
 #define Dh_IceRay_material_illumination_beckmann_hpp_

 #include "../../type/basic/scalar.hpp"
 #include "../../type/color.hpp"
 #include "../../type/math/coord.hpp"


 namespace  GS_DDMRM
  {
   namespace S_IceRay
    {
     namespace S_material
      {
       namespace S_illumination
        {
   
         class GC_beckmann
          //: public S_IceRay::S_material::S_illumination::S__base::GC_data
          {
           public:
               typedef GS_DDMRM::S_IceRay::S_type::GT_scalar             T_scalar;
               typedef GS_DDMRM::S_IceRay::S_type::S_color::GT_scalar    T_color;
               typedef GS_DDMRM::S_IceRay::S_type::S_coord::GT_scalar    T_coord;
   
             public:
             GC_beckmann( T_color const&  P_specular, T_color const&  P_roughness )
              : M2_specular( P_specular )
              , M2_roughness( P_roughness )
              {
              }
   
           public:
             bool F_process
              (
               T_color      & P_result,
               T_color const& P_light,
               T_coord const& P_normal,
               T_coord const& P_half
              )
              {
               static T_scalar Is_phi  = ::math::constants::PHI;

               T_scalar I_cos   = ::math::linear::vector::dot( P_normal, P_half );
               T_scalar I_alpha = acos( I_cos );

               T_scalar I_x = tan( I_alpha );
               I_x *= -I_x;

               T_scalar I_y =  Is_phi * pow( I_cos, 4 );

               P_result.set( 0, P_light[0] * M2_specular[0] * exp( I_x / M2_roughness[0] / M2_roughness[0]) / ( I_y * M2_roughness[0] * M2_roughness[0] ) );
               P_result.set( 1, P_light[1] * M2_specular[1] * exp( I_x / M2_roughness[1] / M2_roughness[1]) / ( I_y * M2_roughness[1] * M2_roughness[1] ) );
               P_result.set( 2, P_light[2] * M2_specular[2] * exp( I_x / M2_roughness[2] / M2_roughness[2]) / ( I_y * M2_roughness[2] * M2_roughness[2] ) );
               return true;
              }
   
           private:
             T_color const& M2_specular;
             T_color const& M2_roughness;
          };
   
        }
      }
    }
  }

#endif
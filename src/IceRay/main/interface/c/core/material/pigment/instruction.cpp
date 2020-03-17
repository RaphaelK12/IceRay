#include "./instruction.h"

#include "IceRay/material/compute/compute.hpp"
#include "../../type/size.h"
#include "../../../util/internal.hpp"


void IceRayC_Material_Pigment_Instruction_Release( IceRayC_Material_Pigment_InstructionHandle P_this )
 {
  IceRayC__Internal_Release
    <
      IceRayC_Material_Pigment_InstructionHandle
     ,GS_DDMRM::S_IceRay::S_material::S_compute::GC_instruction
    >( P_this );

  //typedef  GS_DDMRM::S_IceRay::S_material::S_compute::GC_instruction Tf__instruction;
  //auto I_this = reinterpret_cast<Tf__instruction*> ( P_this );
  //delete I_this;
 }

IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Ambient0( IceRayC_TypeSize P_result, IceRayC_TypeSize P_emmision )
 {
  typedef GS_DDMRM::S_IceRay::S_material::S_compute::GC_instruction              Tf__instruction;
  typedef GS_DDMRM::S_IceRay::S_material::S_compute::S_illumination::GC_ambient  Tf_ambient;

  auto Ir_result = new Tf_ambient{ P_result, P_emmision };
  return reinterpret_cast<IceRayC_Material_Pigment_InstructionHandle>( dynamic_cast< Tf__instruction *> ( Ir_result ) );
 }

/*
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Geometry_Cluster( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Geometry_Distance( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Geometry_Intersect( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Geometry_Normal( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Geometry_Uvw( )
 
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Illumination_Alp( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Illumination_As_Diffuse( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Illumination_As_Specular( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Illumination_Beckmann( )
*/

// IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Illumination_Blinn0();

/*
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Illumination_Gaussian( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Illumination_Hs_Lambert( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Illumination_Hs_Normal( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Illumination_Hs_Phong( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Illumination_Lambert( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Illumination_On_F29( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Illumination_On_P44( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Illumination_Phong( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Illumination_Ward_Approx( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Illumination_Ward_Isotropic( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Illumination_Ward_Real( )
 
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Light_Generator( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Light_SpotCull( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Light_SpotSwarm( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Light_Spotuvw( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Light_Swarm0( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Light_Swarm1( )
 
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Operation_Binary( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Operation_Switch( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Operation_Ternary( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Operation_Unary( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Pattern_Constant( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Pattern_Function( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Pattern_Uvw( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Processor( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Program( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Surface( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Transmission_Blossom_Grid( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Transmission_Blossom_Hexagon( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Transmission_Blossom_Random( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Transmission_Blossom_Vdc( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Transmission_Corrector( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Transmission_Jitter( )
 
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Transmission_Reflect_One( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Transmission_Reflect_Schlick( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Transmission_Refract_Arbitrary( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Transmission_Refract_Fresnel( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Transmission_Refract_Multi( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Transmission_Refract_One( )
IceRayC_Material_Pigment_InstructionHandle IceRayC_Material_Pigment_Instruction_Transmission_Refract_Schlick( )
*/

#include "../../../def_submodule.hpp"

#include "IceRay/material/compute/instruction.hpp"
#include "IceRay/material/compute/illumination/ward_approx.hpp"


void expose_IceRay_material_illumination_ward_approx()
 {
typedef GS_DDMRM::S_IceRay::S_type::GT_size               GTs_size;
typedef GS_DDMRM::S_IceRay::S_type::GT_scalar             GTs_scalar;
typedef GS_DDMRM::S_IceRay::S_type::S_color::GT_scalar    GTs_color;
typedef GS_DDMRM::S_IceRay::S_type::S_coord::GT_scalar3D  GTs_coord3D;


typedef GS_DDMRM::S_IceRay::S_material::S_compute::GC_instruction                       GTs_instruction;
typedef GS_DDMRM::S_IceRay::S_material::S_compute::S_illumination::S_ward::GC_approx    GTs_wardApprox;

  //MAKE_SUBMODULE( IceRay );
  MAKE_SUBMODULE( core );
  MAKE_SUBMODULE( material );
  MAKE_SUBMODULE( illumination );

  typedef  bool                (GTs_wardApprox::*Tf_setScalar   )( GTs_scalar const& );
  typedef  GTs_scalar const&   (GTs_wardApprox::*Tf_getScalar   )( void ) const;
  typedef  bool                (GTs_wardApprox::*Tf_setColor    )( GTs_color const& );
  typedef  GTs_color const&    (GTs_wardApprox::*Tf_getColor    )( void ) const;
  typedef  bool                (GTs_wardApprox::*Tf_setCoord3D  )( GTs_coord3D const& );
  typedef  GTs_coord3D const&  (GTs_wardApprox::*Tf_getCoord3D  )( void ) const;

  typedef boost::python::class_<GTs_wardApprox, boost::python::bases< GTs_instruction > > Tf_this;

  boost::python::object I_this = Tf_this( "MaterialIlluminationWardApprox" )
    .def( boost::python::init<>() )
    .def( boost::python::init<GTs_size,GTs_size,GTs_size,GTs_size,GTs_size,GTs_size,GTs_size,GTs_size>() )
    //.def( "interval", &GTs_wardApprox::F_get, boost::python::return_value_policy<boost::python::copy_const_reference>() )
    //.def( "interval", &GTs_wardApprox::F_set )
  ;

  boost::python::scope I_scope = I_this;

  boost::python::enum_<GTs_wardApprox::Ee_input>( "Input" )
    .value( "LightCount",     GTs_wardApprox::En_inSize_LightCount  )
    .value( "Specular",       GTs_wardApprox::En_inColor_Specular   )
    .value( "AlphaX",         GTs_wardApprox::En_inColor_AlphaX     )
    .value( "AlphaY",         GTs_wardApprox::En_inColor_AlphaY     )
    .value( "point",          GTs_wardApprox::En_inCoord_Point      )
    .value( "normal",         GTs_wardApprox::En_inCoord_Normal     )
    .value( "direction",      GTs_wardApprox::En_inCoord_Direction  )
    .export_values()
   ;

  boost::python::enum_<GTs_wardApprox::Ee_output>( "Output" )
    .value( "result",     GTs_wardApprox::En_outColor_result   )
    .export_values()
   ;

 }
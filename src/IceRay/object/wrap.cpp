
#include "../material/compute/surface.hpp"

#include "./wrap.hpp"

#include "IceRay/material/medium/exponential.hpp"
#include "IceRay/material/medium/linear.hpp"

using namespace GS_DDMRM::S_IceRay::S_object;


GC_wrap::GC_wrap()
 :GC_wrap( &Fs_vacuum() )
 {
 }

GC_wrap::GC_wrap( T_geometry * P_geometry )
 {
  M2_pigment = nullptr;
  M2_medium = &GC_wrap::Fs_transparent();
  M2_geometry = nullptr;
   M2_intersect = nullptr;
   M2_normal = nullptr;
   M2_inside = nullptr;
   M2_distance = nullptr;
   M2_uvw = nullptr;
   M2_cluster = nullptr;
  F_geometry( P_geometry );
 }

GC_wrap::GC_wrap( T_geometry * P_geometry,  T_pigment * P_pigment )
 :GC_wrap()
 {
  F_geometry( P_geometry );
  F_pigment( P_pigment );
 } 

GC_wrap::GC_wrap( T_geometry * P_geometry,  T_pigment * P_pigment, T_medium * P_medium )
 :GC_wrap()
 {
  F_geometry( P_geometry );
  F_pigment( P_pigment );
  F_medium( P_medium );
 }

GC_wrap::~GC_wrap()
 {
 }

bool  GC_wrap::Fv_color( T_color & P_color, T_beam &P_next, T_pigment::T_intersect const& P_intersect, T_state const& P_state )const
 {
  if( nullptr != M2_cluster )
   {
    T_cluster::C_fragment I_fragment;
    if( true == M2_cluster->Fv_fragment( I_fragment, P_state ) )
     {
      auto const& I_pigment = M2_marbles[ I_fragment.M_index ].M_pigment;
      if( nullptr != I_pigment )
       {
        return I_pigment->Fv_color( P_color, P_next, P_intersect, I_fragment.M_state );
       }
     }
   }

  if( nullptr != M2_pigment )
   {// No transform. This is as is.
    return M2_pigment->Fv_color( P_color, P_next, P_intersect, P_state );
   }

  return false;
 }

bool GC_wrap::Fv_attenuate( T_color & P_result, T_color & P_deplete, T_coord const& P_start, T_coord const& P_end, T_state const& P_state )const
 {
  if( nullptr != M2_cluster )
   {
    T_cluster::C_fragment I_fragment;
    if( true == M2_cluster->Fv_fragment( I_fragment, P_state ) )
     {
      auto const& I_medium = M2_marbles[ I_fragment.M_index ].M_medium;
      if( nullptr != I_medium )
       {
        if( true ==  I_medium->Fv_attenuate( P_result, P_deplete, P_start, P_end, I_fragment.M_state ) )
         {
          return true;
         }
       }
     }
   }

  return M2_medium->Fv_attenuate( P_result, P_deplete, P_start, P_end, P_state );
 }

GC_wrap::T_size const& GC_wrap::Fv_maxNextRays()const
 {
  static T_size Ir_zero = 0;
  if( nullptr == M2_pigment )
   {
    return Ir_zero;
   }
  return M2_pigment->Fv_maxNextRays();
 }

void GC_wrap::Fv_reset( T_state &P_intersect )const
 {
  M2_geometry->Fv_reset( P_intersect );
 }

GC_wrap::T_size GC_wrap::Fv_weight( )const
 {
  return  M2_geometry->Fv_weight( );
 }

bool   GC_wrap::Fv_intersect( T_scalar &P_lambda, T_state &P_state, T_intersect::T_ray const& P_ray )const
 {
  return M2_intersect->Fv_intersect( P_lambda, P_state, P_ray );
 }

void        GC_wrap::Fv_normal   ( T_coord &P_normal, T_coord const& P_point,  T_state const& P_state )const
 {
  return  M2_normal->Fv_normal( P_normal, P_point,  P_state  );
 }

GC_wrap::T_location  GC_wrap::Fv_inside(    T_coord const& P_point/*, T_state &P_state */ )const
 {
  return  M2_inside->Fv_inside( P_point/*, P_state */ );
 }

GC_wrap::T_scalar    GC_wrap::Fv_distance(  T_coord const& P_point )const
 {
  return  M2_distance->Fv_distance( P_point );
 }

bool        GC_wrap::Fv_uvw(       T_coord & P_uvw, T_coord const& P_point, T_state const& P_state)const
 {
  return  M2_uvw->Fv_uvw( P_uvw, P_point, P_state);
 }

bool        GC_wrap::F_geometry( T_geometry * P_geometry )
 {
   M2_geometry = P_geometry;
   M2_marbles.clear();
   M2_cluster = dynamic_cast< T_cluster *>( M2_geometry );
   if( nullptr != M2_cluster )
    {
     M2_marbles.resize( M2_cluster->Fv_quantity() );
     for( T_size I_index = 0 ; I_index < M2_cluster->Fv_quantity(); ++I_index )
      {
       M2_marbles[ I_index ].M_pigment = dynamic_cast< T_pigment* >( M2_cluster->Fv_base( I_index ) );
       M2_marbles[ I_index ].M_medium  = dynamic_cast< T_medium* >(  M2_cluster->Fv_base( I_index ) );
      }
    }

   M2_intersect      = dynamic_cast<T_intersect*>( M2_geometry ); if( nullptr == M2_intersect ) M2_intersect = & Fs_vacuum();
   M2_normal         = dynamic_cast<T_normal   *>( M2_geometry ); if( nullptr == M2_normal    ) M2_normal    = & Fs_vacuum();
   M2_inside         = dynamic_cast<T_inside   *>( M2_geometry ); if( nullptr == M2_inside    ) M2_inside    = & Fs_vacuum();
   M2_distance       = dynamic_cast<T_distance *>( M2_geometry ); if( nullptr == M2_distance  ) M2_distance  = & Fs_vacuum();
   M2_uvw            = dynamic_cast<T_uvw      *>( M2_geometry ); if( nullptr == M2_uvw       ) M2_uvw       = & Fs_vacuum();

   Fv_box( P_geometry->F_box() );
   return true;
 }

bool   GC_wrap::F_pigment( T_pigment * P_pigment )
 {
  M2_pigment = P_pigment;
  F1_maxRayPerHit() = M2_pigment->Fv_maxNextRays();

  for( auto & I_fragment : M2_marbles )
   {
    if( nullptr == I_fragment.M_pigment )
     {
      continue;
     }
    T_size I_me = Fv_maxNextRays();
    T_size I_other = I_fragment.M_pigment->Fv_maxNextRays();

    F1_maxRayPerHit() = std::max<T_size>( I_me, I_other );
   }
  return true;
 }

bool  GC_wrap::F_medium( T_medium * P_medium )
 {
  M2_medium = P_medium;
  return true;
 }

GC_wrap::T_vacuum & GC_wrap::Fs_vacuum()
 {
  static T_vacuum Is_vacuum;
  return Is_vacuum;
 }

#include "../material/medium/transparent.hpp"
#include "../material/medium/linear.hpp"

GC_wrap::T_medium & GC_wrap::Fs_transparent()
 {
  static GS_DDMRM::S_IceRay::S_material::S_medium::GC_transparent Is_transparent; return Is_transparent;
  //static  GS_DDMRM::S_IceRay::S_material::S_medium::GC_linear     Is_linear;   return Is_linear;
 }
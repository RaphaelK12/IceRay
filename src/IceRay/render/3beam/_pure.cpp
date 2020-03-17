#include "_pure.hpp"

#include "../4ray/distance.hpp"

using namespace GS_DDMRM::S_IceRay::S_render::S_beam;

GC__pure::GC__pure()
 :M2_ray( nullptr )
 {
  Fv_ray( &Fs_ray() );
 }

GC__pure::~GC__pure()
 {
 }

void GC__pure::Fv_ray( T_ray * P_ray )
 {
  M2_ray = P_ray;
  if( nullptr == M2_ray )
   {
    M2_ray = &Fs_ray();
   }
 }

GC__pure::T_ray & GC__pure::Fs_ray()
 {
  static GS_DDMRM::S_IceRay::S_render::S_ray::GC_distance Irs_distance;
  return Irs_distance;
 }

#ifndef Dh_DDMRM_Iceray_utility_table_hexagon_HPP_
 #define Dh_DDMRM_Iceray_utility_table_hexagon_HPP_

 // GS_DDMRM::S_IceRay::S_utility::S_table::GC_hexagon

#include "IceRay/type/basic/size.hpp"
#include "IceRay/type/math/coord.hpp"


 namespace GS_DDMRM
  {
   namespace S_IceRay
    {
     namespace S_utility
      {
       namespace S_table
        {

         class GC_hexagon
          {
           public:
             typedef GS_DDMRM::S_IceRay::S_type::GT_size               T_size;
             typedef GS_DDMRM::S_IceRay::S_type::GT_scalar             T_scalar;
             typedef GS_DDMRM::S_IceRay::S_type::S_coord::GT_scalar    T_coord;
             typedef GS_DDMRM::S_IceRay::S_type::S_coord::GT_scalar2D  T_coord2D;

           public:
             explicit GC_hexagon( T_size const& P_size = 10 )
              {
               F_init( P_size );
              }
           public:
             bool F_init( T_size const& P_size )
              {
               T_size I_grid = P_size;
               T_scalar I_perimeter = I_grid/2 - 2;
               M2_spot.reserve( I_grid * I_grid );
               T_scalar I_offset = T_scalar(1)/T_scalar(2);
               T_scalar I_height = sqrt(T_scalar(3))/T_scalar(2);

               for( T_size I_v =0; I_v < I_grid; ++ I_v )
               for( T_size I_u =0; I_u < I_grid; ++ I_u )
                {
                 T_coord2D I_spot;
                 I_spot[0] = ( I_u - T_scalar(I_grid/2) ) + I_offset * abs( ( int(I_v) - int(I_grid/2) )%2 ) ;
                 I_spot[1] = ( I_v - T_scalar(I_grid/2) ) *I_height ;

                 if( I_perimeter < ::math::linear::vector::length( I_spot ) )
                  {
                   continue;
                  }
                 M2_spot.push_back( I_spot );
                }

               std::sort
                 (
                   M2_spot.begin(),
                   M2_spot.end(),
                   [](auto const& a, auto const& b)
                    {
                     return ::math::linear::vector::dot(a,a) < ::math::linear::vector::dot(b,b);
                    }
                );

               M2_index.push_back( 0 );
               M2_radius.push_back( 0 );

               for( auto const& I_spot: M2_spot )
                {
                 auto I_radius = ::math::linear::vector::length( I_spot );
                 if( I_radius < M2_radius.back() + 0.000001 )
                  {
                   ++M2_index.back();
                   continue;
                  }
                 M2_index.push_back(1+M2_index.back() );
                 M2_radius.push_back( I_radius );
                }
               //std::cout << "Max hexagon size: " << M2_index.size() << std::endl;
               return true;
              }

           public:
             std::vector<T_size> const& F_index()const{ return M2_index; }
           private:
             std::vector<T_size>    M2_index;
           public:
             std::vector<T_scalar> const& F_radius()const{ return M2_radius; }
           private:
             std::vector<T_scalar>  M2_radius;
           public:
             std::vector<T_coord2D> const& F_spot()const{ return M2_spot; }
           private:
             std::vector<T_coord2D> M2_spot;

          };

        }
      }
    }
  }
#endif

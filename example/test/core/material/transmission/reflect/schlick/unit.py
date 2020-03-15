import IceRayCpp


def make(
    P_light,
    P_IOR = 1.5,
    P_ambient      = IceRayCpp.GraphTypeColorRGB().fill( 0.0 )
):
    surface = IceRayCpp.MaterialSurface()

    cargo = {}
    cargo['1'] = IceRayCpp.MaterialLightGenerator( P_light['this'], 0 )
    #MaterialLightSpotSwarm( [coord]point, [light]light, [spot]start, [size]count  )
    cargo['2A'] = IceRayCpp.MaterialLightSpotSwarm( 0, 0, 0, 0 )
    #MaterialLightSpotCull( [coord]point, [coord]normal, [spot]start, [size]count  )
    cargo['2B'] = IceRayCpp.MaterialLightSpotCull( 0, 1, 0, 0 )

    cargo['3'] = IceRayCpp.MaterialPatternScalarConstant( P_IOR, 1 )
    #MaterialTransmissionReflectOne( [coord]point, [coord]normal, [color]IOR )
    cargo['4'] = IceRayCpp.MaterialTransmissionReflectSchlick( 0, 1, 1 )

    #cargo['8'] = IceRayCpp.MaterialPatternColorConstant( IceRayCpp.GraphTypeColorRGB().load( 1.4, 1.5, 1.6 ), 1 )
    #cargo['9'] = IceRayCpp.MaterialPatternColorConstant( IceRayCpp.GraphTypeColorRGB().load( 40, 50, 60 ), 2 )
    ##MaterialIlluminationPhong( [color]result, [color]specular, [color]shininess, [size]spotCount )
    #cargo['A'] = IceRayCpp.MaterialIlluminationPhong( 0, 1, 2, 0 )

    cargo['F'] = IceRayCpp.MaterialPatternColorConstant( P_ambient, 0 )

    surface.append( cargo['1'] )
    surface.append( cargo['2A'] )
    surface.append( cargo['2B'] )
    surface.append( cargo['3'] )
    surface.append( cargo['4'] )
    #surface.append( cargo['8'] )
    #surface.append( cargo['9'] )
    #surface.append( cargo['A'] )
    surface.append( cargo['F'] )

    return { 'this' : surface, 'cargo': cargo, 'light': P_light  }
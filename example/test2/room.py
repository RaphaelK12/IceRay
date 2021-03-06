import IceRayPy

Coord3D = IceRayPy.type.math.coord.Scalar3D


def vacuum( P_dll, P_config = None, P_light = None, P_exponat = None ):
    geometry = IceRayPy.core.geometry.volumetric.Vacuum( P_dll )

    wrapper = IceRayPy.core.object.Wrapper( P_dll )
    wrapper.geometrySet( geometry )
    return wrapper

def plate( P_dll, P_config = { 'level':  - 1.01, 'size' : 3, 'shadow': False, 'pigment': None }, P_light = None, P_exponat = None ):

    level = -1.00001;
    if( 'level' in P_config ):
        level = P_config['level']
    size = 3;
    if( 'size' in P_config ):
        size = P_config['size']

    geometry = IceRayPy.core.geometry.simple.Box( P_dll )
    geometry.box(        Coord3D(  -size, -size, level - 0.1) , Coord3D( size,      size, level ) )

    wrapper = IceRayPy.core.object.Wrapper( P_dll )

    I_scene = { 'light': P_light, 'barrier' : P_exponat   }
    if( 'shadow' in P_config ):
        if( False == P_config['shadow'] ):
            I_scene['barrier'] = IceRayPy.core.geometry.volumetric.Vacuum( P_dll )

    pigment = IceRayPy.utility.material.illumination.Lambert( P_dll, I_scene, IceRayPy.type.color.RGB( 0.5, 0.5, 0.5 ) )
    if( 'pigment' in P_config ):
        pigment = P_config['pigment'] #utility.material.pattern.Checker( P_dll, I_scene )

    #pigment = IceRayPy.utility.material.pattern.Checker( P_dll, I_scene )

    wrapper.pigment( pigment )

    wrapper.geometrySet( geometry )

    return wrapper


def plane( P_dll, P_config = { 'level':  - 1.001, 'shadow': False, 'pigment': None }, P_light = None, P_exponat = None ):

    level = -1.0001;
    if( 'level' in P_config ):
        level = P_config['level']
    geometry = IceRayPy.core.geometry.simple.Plane( P_dll )
    geometry.origin( Coord3D(0,   0, level ) )

    wrapper = IceRayPy.core.object.Wrapper( P_dll )

    I_scene = { 'light': P_light, 'barrier' : P_exponat }
    if( 'shadow' in P_config ):
        if( False == P_config['shadow'] ):
            I_scene['barrier'] = IceRayPy.core.geometry.volumetric.Vacuum( P_dll )

    pigment = IceRayPy.utility.material.illumination.Lambert( P_dll, I_scene, IceRayPy.type.color.RGB( 0.5, 0.5, 0.5 ) )
    if( 'pigment' in P_config ):
        pigment = P_config['pigment'] #utility.material.pattern.Checker( P_dll, I_scene )

    #pigment = IceRayPy.utility.material.pattern.Checker( P_dll, I_scene )
    wrapper.pigment( pigment )

    wrapper.geometrySet( geometry )

    return wrapper

def cornel( P_dll, P_config = None, P_light = None, P_exponat = None ):
    move = [ 0,0, 5 ]
    I_dimension = [ 12, 12, 12 ]
    wall = 0.1

    lo = Coord3D()
    lo[0] = -I_dimension[0]/2 + move[0]
    lo[1] = -I_dimension[1]/2 + move[1]
    lo[2] = -I_dimension[2]/2 + move[2]

    hi = Coord3D()
    hi[0] = +I_dimension[0]/2 + move[0]
    hi[1] = +I_dimension[1]/2 + move[1]
    hi[2] = +I_dimension[2]/2 + move[2]

    left = IceRayPy.core.geometry.simple.Box( P_dll )
    left.box(        Coord3D(  lo[0]-wall, lo[1], lo[2]) , Coord3D(lo[0],      hi[1], hi[2]) )

    right = IceRayPy.core.geometry.simple.Box( P_dll )
    right.box(       Coord3D( hi[0],      lo[1], lo[2]) ,  Coord3D(hi[0]+ wall,hi[1], hi[2]) )

    background = IceRayPy.core.geometry.simple.Box( P_dll )
    background.box(  Coord3D( lo[0], lo[1]-wall, lo[2] ) , Coord3D( hi[0], lo[1], hi[2] ) )

    foreground = IceRayPy.core.geometry.simple.Box( P_dll )
    foreground.box(  Coord3D( lo[0], hi[1],  lo[2] ),      Coord3D( hi[0], hi[1] + wall, hi[2] ) )

    floor = IceRayPy.core.geometry.simple.Box( P_dll )
    floor.box(       Coord3D( lo[0], lo[1], lo[2]-wall ) , Coord3D( hi[0], hi[0], lo[2] ) )

    ceil = IceRayPy.core.geometry.simple.Box( P_dll )
    ceil.box(        Coord3D( lo[0], lo[1], hi[2] ),       Coord3D( hi[0], hi[1], hi[2] + wall ) )

    rtss = IceRayPy.core.geometry.rtss.Object( P_dll )

    l = IceRayPy.core.geometry.rtss.List( P_dll )

    rtss.rtss( l )

    rtss.push( left )
    rtss.push( right )
    rtss.push( floor )
    rtss.push( ceil )
    rtss.push( background )
    rtss.push( foreground )

    wrapper = IceRayPy.core.object.Wrapper( P_dll )
    wrapper.geometrySet( rtss )
    return wrapper

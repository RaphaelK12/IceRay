
class Constant:
    def __init__(self, P_dll, P_value = None, P_deplete = None ):
        self.m_cargo = {}
        self.m_cargo['dll'] = P_dll
        self.m_cargo['this'] = self.m_cargo['dll'].IceRayC_Material_Medium_Constant0()

    def __del__(self):
        self.m_cargo['dll'].IceRayC_Material_MediumRelease( self.m_cargo['this'] )

    def value( self, P_deplete ):
        pass

    def deplete( self, P_deplete ):
        pass

class Linear:
    def __init__(self, P_dll, P_value = None, P_c0 = None, P_c1 = None ):
        self.m_cargo = {}
        self.m_cargo['dll'] = P_dll
        self.m_cargo['this'] = self.m_cargo['dll'].IceRayC_Material_Medium_Linear0()

    def __del__(self):
        self.m_cargo['dll'].IceRayC_Material_MediumRelease( self.m_cargo['this'] )

class Quadratic:
    def __init__(self, P_dll, P_value = None, P_c0 = None, P_c1 = None, P_c2 = None ):
        self.m_cargo = {}
        self.m_cargo['dll'] = P_dll
        self.m_cargo['this'] = self.m_cargo['dll'].IceRayC_Material_Medium_Quadratic0()

    def __del__(self):
        self.m_cargo['dll'].IceRayC_Material_MediumRelease( self.m_cargo['this'] )

class Exponential:
    def __init__(self, P_dll, P_half = None ):
        self.m_cargo = {}
        self.m_cargo['dll'] = P_dll
        self.m_cargo['this'] = self.m_cargo['dll'].IceRayC_Material_Medium_Exponential0()

    def __del__(self):
        self.m_cargo['dll'].IceRayC_Material_MediumRelease( self.m_cargo['this'] )



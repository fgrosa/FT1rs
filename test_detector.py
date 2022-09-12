'''
Simple script for ITS3 studies with FAT tool
'''

import ROOT

def compile_classes():
    '''
    Helper method to compile FAT tool classes
    '''

    # pylint: disable=no-member
    ROOT.gInterpreter.ProcessLine('.L DetectorK.cxx+g')
    ROOT.gInterpreter.ProcessLine('.L HistoManager.cxx+g')
    ROOT.gInterpreter.Declare('#include "DetectorK.h"')
    ROOT.gInterpreter.Declare('#include "HistoManager.h"')
    ROOT.gSystem.Load('DetectorK_cxx.so')
    ROOT.gSystem.Load('HistoManager_cxx.so')

# pylint: disable=too-many-locals, too-many-statements
def test_detector(mass=0.14, output='grsav', **kwargs):
    '''
    Method to perform fast simulation

    Parameters
    ---------------------------
    mass: float
        mass value in GeV/c2
    output: str
        root output file without .root extension
    **kwargs: dict
        optional and non-positional arguments:
        - layerskill: list
            list of number of the layer to kill (default=list())
        - x0_ib: float
            radiation length for inner barrel (default=0.0005)
        - x0_ob: float
            radiation length for outer barrel (default=0.0035)
        - xrho_ib: float
            surface density for inner barrel (default=1.1646e-02)
        - xrho_ob: float
            surface density for outer barrel (default=1.1646e-01)
        - res_rphi_ib: float
            resolution in rphi for inner barrel in cm (default=0.0006)
        - res_z_ib: float
            resolution in z for inner barrel in cm (default=0.0006)
        - res_rphi_ob: float
            resolution in rphi for inner barrel in cm (default=0.0006)
        - res_z_ob: float
            resolution in z for inner barrel in cm (default=0.0006)
        - eff: float
            single-layer efficiency (default=0.98)
        - add_tpc: bool
            flag to add TPC
        - add_trd: bool
            flag to add TRD
    '''

    its = ROOT.DetectorK('ALICE', 'ITS')  # pylint: disable=no-member
    its.SetBField(0.2)

    # set parameters from kwargs or default if not provided
    x0_ib = kwargs.get('x0_ib', 0.0005)
    x0_ob = kwargs.get('x0_ob', 0.0035)
    xrho_ib = kwargs.get('x0_ob', 1.1646e-02)
    xrho_ob = kwargs.get('x0_ob', 1.1646e-01)

    res_rphi_ib = kwargs.get('res_rphi_ib', 0.0006)
    res_z_ib = kwargs.get('res_z_ib', 0.0006)
    res_rphi_ob = kwargs.get('res_rphi_ob', 0.0006)
    res_z_ob = kwargs.get('res_z_ob', 0.0006)
    eff = kwargs.get('eff', 0.98)

    layerskill = kwargs.get('layerskill', list())
    add_tpc = kwargs.get('add_tpc', False)
    add_trd = kwargs.get('add_trd', False)

    its.AddLayer('vertex', 0, 0)
    its.AddLayer('bpipe', 1.6, 0.0022)

    its.AddLayer("ddd1", 1.8, x0_ib, xrho_ib, res_rphi_ib, res_z_ib, eff)
    its.AddLayer("foam1", 1.8 + 9.370 * x0_ib, 0.0008) # Foam spacer
    its.AddLayer("ddd2", 2.4, x0_ib, xrho_ib, res_rphi_ib, res_z_ib, eff)
    its.AddLayer("foam2", 2.4 + 9.370 * x0_ib, 0.0008) # Foam spacer
    its.AddLayer("ddd3", 3.0, x0_ib, xrho_ib, res_rphi_ib, res_z_ib, eff)
    its.AddLayer("foam3", 3.0 + 9.370 * x0_ib, 0.0008) # Foam spacer
    its.AddLayer("ddd4", 19.4, x0_ob, xrho_ob, res_rphi_ob, res_z_ob, eff)
    its.AddLayer("ddd5", 24.7, x0_ob, xrho_ob, res_rphi_ob, res_z_ob, eff)
    its.AddLayer("ddd6", 35.3, x0_ob, xrho_ob, res_rphi_ob, res_z_ob, eff)
    its.AddLayer("ddd7", 40.5, x0_ob, xrho_ob, res_rphi_ob, res_z_ob, eff)
    for layerkill in layerskill:
        print(f"ddd{layerkill}")
        its.KillLayer(f"ddd{layerkill}")

    its.SetParticleMass(mass)
    its.SetBField(0.5)
    its.SetAvgRapidity(0.5)
    its.SetAtLeastHits(4)
    its.SetAtLeastCorr(4)
    its.SetAtLeastFake(1)
    if add_tpc:
        its.AddTPC(0.1, 0.1)
    if add_trd:
        its.AddTRD(0.02, 2.5)

    its.PrintLayout()
    its.SolveViaBilloir(0)

    if not add_tpc and not add_trd:
        output += '_ITS.root'
        its.MakeStandardPlots(0, 2, 1, output)
    else:
        output += '_GLO.root'
        its.MakeStandardPlots(1, 1, 1, output)

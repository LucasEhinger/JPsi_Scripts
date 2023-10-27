Workflow

filterAll:
    Adds definitions.

    Performs cuts:
        Fiducial

        Unused tracks/showers:
            0: No unused tracks or showers allowed
            1: 1 unused track allowed
            2: 1 unused shower allowed
            3: 1 unused track and 1 unused shower allowed

        preShower:
            preforms preBCal shower cut, based on inupt parameter

        PoverE:
            performs pOverE cut, based on input parameters (+ & - sigma bounds).
                Note: minus sigma bound should be negative.

        EMiss:
        Cuts on missing energy, assuming stationary proton.

    Saves all information to a tree.
    Currently doesn't create any histograms. I will implement this later.

makeHists:
    make histograms for p, em, ep, jpsi, as well as other histograms of interest.

    Easily extendable to make different cuts (E_gamma, pt, etc.), and make histograms for those too.
    I haven't implemented this yet.
////////////////////////////////////////////////////////////////////////////////
// STEPS - STochastic Engine for Pathway Simulation
// Copyright (C) 2005-2007 Stefan Wils. All rights reserved.
// 
// This file is part of STEPS.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301, USA
//
// $Id:kproc.hpp 64 2007-08-20 06:25:41Z stefan $
////////////////////////////////////////////////////////////////////////////////

#ifndef STEPS_TETEXACT_SOLVER_CORE_KPROC_HPP
#define STEPS_TETEXACT_SOLVER_CORE_KPROC_HPP 1

// Autotools definitions.
#ifdef HAVE_CONFIG_H
#include <steps/config.h>
#endif

// Standard library & STL headers.
#include <cassert>
#include <set>
#include <vector>

// STEPS headers.
#include <steps/common.h>
#include <steps/tetexact/solver_core/sched.hpp>

// Forward declarations.
class State;
class Tet;
class Tri;

////////////////////////////////////////////////////////////////////////////////

class KProc;

typedef KProc *                         KProcP;
typedef std::vector<KProcP>             KProcPVec;
typedef KProcPVec::iterator             KProcPVecI;
typedef KProcPVec::const_iterator       KProcPVecCI;

////////////////////////////////////////////////////////////////////////////////

class KProc
{

public:

    ////////////////////////////////////////////////////////////////////////
    // OBJECT CONSTRUCTION & DESTRUCTION
    ////////////////////////////////////////////////////////////////////////

    KProc(void);
    virtual ~KProc(void);
    
    ////////////////////////////////////////////////////////////////////////

    uint schedIDX(void) const
    { return pSchedIDX; }

    void setSchedIDX(SchedIDX idx)
    { pSchedIDX = idx; }
    
    ////////////////////////////////////////////////////////////////////////
    // VIRTUAL INTERFACE METHODS
    ////////////////////////////////////////////////////////////////////////
    
    /// This function is called when all kproc objects have been created,
    /// allowing the kproc to pre-compute its SchedIDXVec.
    ///
    virtual void setupDeps(void) = 0;
        
    /// Returns true if the occurence of this kproc depends on the number 
    /// of molecules of some species (specified by its global index sidx) 
    /// in a given tetrahedron. False otherwise.
    ///
    virtual bool depSpecTet(uint gidx, Tet * tet) = 0;
    
    /// Returns true if the occurence of this kproc depends on the number
    /// of molecules of some species in a given triangle. False otherwise.
    ///
    virtual bool depSpecTri(uint gidx, Tri * tri) = 0;
    
    /// Reset this Kproc.
    ///
    virtual void reset(void) = 0;
    
    /// Compute the rate for this kproc (its propensity value).
    ///
    virtual double rate(void) const = 0;
    
    /// Apply a single discrete instance of the kinetic process, returning
    /// a vector of kproc schedule indices that need to be updated as a
    /// result.
    ///
    virtual SchedIDXVec const & apply(State * s) = 0;
    
    ////////////////////////////////////////////////////////////////////////
    
private:

    ////////////////////////////////////////////////////////////////////////
    
    SchedIDX                    pSchedIDX;

};

////////////////////////////////////////////////////////////////////////////////

#endif
// STEPS_TETEXACT_SOLVER_CORE_KPROC_HPP

// END

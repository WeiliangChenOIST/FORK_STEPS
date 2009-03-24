////////////////////////////////////////////////////////////////////////////////
// STEPS - STochastic Engine for Pathway Simulation
// Copyright (C) 2005-2008 Stefan Wils. All rights reserved.
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
// $Id$
////////////////////////////////////////////////////////////////////////////////

#ifndef STEPS_CONSOLE_CHANNEL_HPP
#define STEPS_CONSOLE_CHANNEL_HPP 1

// Autotools definitions.
#ifdef HAVE_CONFIG_H
#include <steps/config.h>
#endif

// STEPS headers.
#include <steps/common.h>

// Standard library & STL headers.
#include <cassert>
#include <sstream>
#include <string>

START_NAMESPACE(steps)
START_NAMESPACE(console)

////////////////////////////////////////////////////////////////////////////////

/// Auxiliary structure to easily flush/commit messages.
///
class EndMsg { };

////////////////////////////////////////////////////////////////////////////////

/// The base class for the information channels offered by namespace
/// steps::console. Currently, there are only two channels (channel
/// 'info' for neutral information and warnings, and channel 'debug'
/// for debugging purposes). Neither of them needs special functionality
/// so they are just instances of this base class.
///
/// The pointers to ostream objects that are passed to this class are 
/// not owned or managed by this class. It's the caller's responsibility
/// to clean up.
///
class Channel
: public std::ostringstream
{
    
public:
    
    ////////////////////////////////////////////////////////////////////////
    // OBJECT CREATION & DESTRUCTION
    ////////////////////////////////////////////////////////////////////////
    
    /// Default constructor. Connects to std::cerr.
    /// 
    Channel(void);
    
    /// Constructor. 
    ///
    Channel(std::ostream * os);
    
    /// Destructor.
    ///
    virtual ~Channel(void);
    
    /// Tie the console object to some output stream for dumping its
    /// messages. 
    ///
    void setStream(std::ostream * os);
    
    ////////////////////////////////////////////////////////////////////////
    // MESSAGE GENERATION
    ////////////////////////////////////////////////////////////////////////

    /// Output (or 'commit') the current message to whatever stream the
    /// console is currently tied to. The method is provided to be able 
    /// to commit to the console from within Python. From C++ code, you
    /// can also use the steps::console::endm object for this:
    ///
    ///     myconsole << endm;
    ///
    virtual void commit(void);
    
    ////////////////////////////////////////////////////////////////////////
    
private:
    
    ////////////////////////////////////////////////////////////////////////
    
    /// Output stream.
    ///
    std::ostream                      * pStream;
    
    ////////////////////////////////////////////////////////////////////////
    
};

////////////////////////////////////////////////////////////////////////////////

STEPS_EXTERN
Channel & operator<< (Channel & c, EndMsg const & e);

////////////////////////////////////////////////////////////////////////////////

END_NAMESPACE(console)
END_NAMESPACE(steps)

#endif
// STEPS_CONSOLE_CHANNEL_HPP

// END
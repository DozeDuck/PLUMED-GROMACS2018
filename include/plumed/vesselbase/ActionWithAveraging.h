/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   Copyright (c) 2016-2019 The plumed team
   (see the PEOPLE file at the root of the distribution for a list of names)

   See http://www.plumed.org for more information.

   This file is part of plumed, version 2.

   plumed is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   plumed is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with plumed.  If not, see <http://www.gnu.org/licenses/>.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
#ifndef __PLUMED_vesselbase_ActionWithAveraging_h
#define __PLUMED_vesselbase_ActionWithAveraging_h

#include "core/ActionPilot.h"
#include "core/ActionWithValue.h"
#include "core/ActionAtomistic.h"
#include "core/ActionWithValue.h"
#include "core/ActionWithArguments.h"
#include "ActionWithVessel.h"
#include "AveragingVessel.h"

namespace PLMD {
namespace vesselbase {

/**
\ingroup INHERIT
This abstract base class should be used if you are writing some method that calculates an "average" from a set of
trajectory frames.  Notice that we use the word average very broadly here and state that even dimensionality
reduction algorithms calculate an "average."  In other words, what we mean by average is that the method is going
to take in data from each trajectory frame and only calculate the final quantity once a certain amount of data has
been collected.
*/

class ActionWithAveraging :
  public ActionPilot,
  public ActionAtomistic,
  public ActionWithArguments,
  public ActionWithValue,
  public ActionWithVessel
{
  friend class AveragingVessel;
private:
/// The vessel which is used to compute averages
  AveragingVessel* myaverage;
/// The weights we are going to use for reweighting
  std::vector<Value*> weights;
/// Are we accumulated the unormalized quantity
  enum {t,f,ndata} normalization;
protected:
/// This ensures runAllTasks is used
  bool useRunAllTasks;
/// The frequency with which to clear the grid
  unsigned clearstride;
/// The current weight and its logarithm
  double lweight, cweight;
/// Set the averaging action
  void setAveragingAction( AveragingVessel* av_vessel, const bool& usetasks );
/// Check if we are using the normalization condition when calculating this quantity
  bool noNormalization() const ;
public:
  static void registerKeywords( Keywords& keys );
  explicit ActionWithAveraging( const ActionOptions& );
  void lockRequests();
  void unlockRequests();
  void calculateNumericalDerivatives(PLMD::ActionWithValue*);
  virtual unsigned getNumberOfDerivatives() { return 0; }
  unsigned getNumberOfArguments() const ;
/// Overwrite ActionWithArguments getArguments() so that we don't return the bias
  std::vector<Value*> getArguments();
  void update();
/// This does the clearing of the action
  virtual void clearAverage();
/// This is done before the averaging comences
  virtual void prepareForAveraging() {}
/// This does the averaging operation
  virtual void performOperations( const bool& from_update );
/// This is done once the averaging is finished
  virtual void finishAveraging() {}
};

inline
unsigned ActionWithAveraging::getNumberOfArguments() const {
  return ActionWithArguments::getNumberOfArguments() - weights.size();
}

inline
std::vector<Value*> ActionWithAveraging::getArguments() {
  std::vector<Value*> arg_vals( ActionWithArguments::getArguments() );
  for(unsigned i=0; i<weights.size(); ++i) arg_vals.erase(arg_vals.end()-1);
  return arg_vals;
}

inline
bool ActionWithAveraging::noNormalization() const {
  return normalization==f;
}

}
}
#endif

#ifndef GEMValidation_GEMRecHitMatcher_h
#define GEMValidation_GEMRecHitMatcher_h

/**\class RecHitMatcher

 Description: Matching of RecHits for SimTrack in GEM

 Original Author:  "Vadim Khotilovich"
 $Id: GEMRecHitMatcher.h,v 1.1 2013/02/11 07:33:07 khotilov Exp $
*/

#include "GEMCode/GEMValidation/src/BaseMatcher.h"

#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Common/interface/DetSetVector.h"
#include <DataFormats/GEMRecHit/interface/GEMRecHit.h>
#include "DataFormats/GEMRecHit/interface/GEMRecHitCollection.h"

#include <vector>
#include <map>
#include <set>

class SimHitMatcher;
class GEMGeometry;

class GEMRecHitMatcher : BaseMatcher
{
public:

  GEMRecHitMatcher(SimHitMatcher& sh);
  
  ~GEMRecHitMatcher();

  // partition GEM detIds with rechits
  std::set<unsigned int> detIds() const;

  // chamber detIds with rechits
  std::set<unsigned int> chamberIds() const;

  // superchamber detIds with rechits
  std::set<unsigned int> superChamberIds() const;

  // GEM recHits from a particular partition, chamber or superchamber
  const GEMRecHitCollection& recHitsInDetId(unsigned int) const;
  const GEMRecHitCollection& recHitsInChamber(unsigned int) const;
  const GEMRecHitCollection& recHitsInSuperChamber(unsigned int) const;

  // #layers with recHits from this simtrack
  int nLayersWithRecHitsInSuperChamber(unsigned int) const;

  /// How many recHits in GEM did this simtrack get in total?
  int nRecHits() const;

  std::set<int> stripNumbersInDetId(unsigned int) const;

  // what unique partitions numbers with recHits from this simtrack?
  std::set<int> partitionNumbers() const;

private:

  void init();

  void matchRecHitsToSimTrack(const GEMRecHitCollection& recHits);

  edm::InputTag gemRecHitInput_;

  const SimHitMatcher* simhit_matcher_;
  const GEMGeometry* gem_geo_;

  int minBXGEM_, maxBXGEM_;

  int matchDeltaStrip_;

  std::map<unsigned int, GEMRecHitCollection> detid_to_recHits_;
  std::map<unsigned int, GEMRecHitCollection> chamber_to_recHits_;
  std::map<unsigned int, GEMRecHitCollection> superchamber_to_recHits_;

  const GEMRecHitCollection no_recHits_;
};

#endif

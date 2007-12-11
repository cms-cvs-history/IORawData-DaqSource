#ifndef DaqSource_DaqSource_H
#define DaqSource_DaqSource_H

/** \class DaqSource
 *  An input service for raw data. 
 *  The actual source can be the real DAQ, a file, a random generator, etc.
 *
 *  $Date: 2007/12/03 00:43:40 $
 *  $Revision: 1.6 $
 *  \author N. Amapane - S. Argiro'
 */

#include <memory>
#include "boost/shared_ptr.hpp"
#include "FWCore/Framework/interface/InputSource.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

class DaqBaseReader;

namespace edm {
  class ParameterSet;
  class Timestamp;
  class InputSourceDescription;
  class EventPrincipal;


  class DaqSource : public InputSource {

   public:
    explicit DaqSource(const ParameterSet& pset, 
  		     const InputSourceDescription& desc);
  
    virtual ~DaqSource();
  
   private:
  
    virtual std::auto_ptr<EventPrincipal> readEvent_(boost::shared_ptr<LuminosityBlockPrincipal>);
    virtual boost::shared_ptr<LuminosityBlockPrincipal> readLuminosityBlock_();
    virtual boost::shared_ptr<RunPrincipal> readRun_();
    virtual std::auto_ptr<EventPrincipal> readIt(EventID const& eventID);
    virtual void skip(int offset);
    virtual void setLumi(LuminosityBlockNumber_t lb);
    virtual void setRun(RunNumber_t r);
    virtual InputSource::ItemType getNextItemType();
  
    DaqBaseReader*  reader_;
    unsigned int    lumiSegmentSizeInEvents_; //temporary kludge, LS# will come from L1 Global record
    bool            fakeLSid_;
  
    RunNumber_t runNumber_;
    LuminosityBlockNumber_t luminosityBlockNumber_;
    bool noMoreEvents_;
    bool newRun_;
    bool newLumi_;
    std::auto_ptr<EventPrincipal> ep_;
  };
  
}
  
#endif

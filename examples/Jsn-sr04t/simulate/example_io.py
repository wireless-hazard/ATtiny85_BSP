# Python Script
from sys import argv
from os.path import splitext, basename

import pysimulavr
from ex_utils import SimulavrAdapter

class XPin(pysimulavr.Pin):
  
  def __init__(self, dev, name, state = None):
    pysimulavr.Pin.__init__(self)
    self.name = name
    if state is not None: self.SetPin(state)
    # hold the connecting net here, it have not be destroyed, if we leave this method
    self.__net = pysimulavr.Net()
    self.__net.Add(self)
    self.__net.Add(dev.GetPin(name))
    
  def SetInState(self, pin):
    pysimulavr.Pin.SetInState(self, pin)
    #print(f"{self.name}='{pin.toChar()}' (t={sim.getCurrentTime()}ns)")

if __name__ == "__main__":

  proc, elffile = argv[1].split(":")
  
  sim = SimulavrAdapter()
  sim.dmanSingleDeviceApplication()
  dev = sim.loadDevice(proc, elffile)

  sigs = ("IRQ.VECTOR9", "PORTB.B0-Out", "PORTB.B1-Out","PORTB.B2-Out", "PORTB.B3-Out")
  sim.setVCDDump("result.vcd", sigs)
  
  a7 = XPin(dev, "B2", "L")

  uptime_string = (296750, 607000,908438,1152000, 1413000, 1648800)
  
  sim.dmanStart()
  for uptime in uptime_string:
    sim.doRun(sim.getCurrentTime() + 15000000)
    a7.SetPin("H")
    sim.doRun(sim.getCurrentTime() + uptime) # 1 ms
    a7.SetPin("L")
    sim.doRun(sim.getCurrentTime() + 200000)
    counter = sim.getWordByName(dev, "distance")
    print(f"Counter: {counter}")

  sim.dmanStop()  

  del dev
  
# EOF

# PIC32MK1024MCM100_Signal_Processing
<h1>Description</h1>
This project is for learning signal processing basics with general purpose C-code. Most DSP algorithm are written in assembly instruction, so that the time needed for the processing is less. But before someone can become an expert in DSP, he/ she can learn basic concepts by writing the code in C and floating point and still see the expected output from the code. The code will not be optimized (in time/ memory/ performance), but still gives a good learning to someone trying new.

 - The trials and experiments are tried on PIC32MK1024MCM100 32-bit microcontroller on a [PIC32MK1024MCM100 Curiosity Pro board](https://www.microchip.com/en-us/development-tool/EV31E34A).
 - For viewing the input and output waveforms of signal, X2CScope tool is used. For more info, refer to [this page](https://mu.microchip.com/using-x2cscope-to-simply-motor-control-development-and-debugging).
 
 <h1>Hardware Connection</h1>
 
  - While the "PIC32MK1024MCM100 Curiosity Pro board" can be powered and programmed/ debugged over micro USB cable, the same cable also acts as a UART connection to computer (appears as COM port on computer, device manager).
  - But for feeding external signal, a prototype HW board is used. The HW board takes input from computer audio jack (3.5mm connector) and adds a DC offset before feeding to the ADC inputs (AN0 and AN7) of PIC32MK1024MCM100. The diagrams and pictures below describes the board in details.
  
  <h1>Schematic diagram</h1>	
  - Following schematic shows how an opamp is used to generated buffered DC voltage (typically 1.65V, which is half of 3.3V), which is then added as DC offset to both left and right audio output of laptop using 2 identical sections of non-inverting summing amplifier.
  
  ![Schematic](/hw/non_inverting_summing.png)
  
  <h1>Top view of the prototype board</h1>	
  - Following picture shows the top view of proto board.
  
  ![Top View](/hw/Top.jpg)
  
  <h1>Bottom view of the prototype board</h1>	
  - Following picture shows the bottom view of proto board.
  
  ![Bottom View](/hw/Bottom.jpg)
  
  <h1>Prototype board mounted on Curiosity Pro board</h1>	
  - Following picture shows the Prototype board mounted on Curiosity Pro board with audio cable connected.
  
  ![Bottom View](/hw/Curiosity.jpg)  
  
  <h1>Use of Prototype board</h1>
  Computer sound card is a practical and low cost complex frequency generator. Its frequency is limited to audio range, but that is acceptable for learning purposes. Python scripts can be written to generated combination of multiple frequencies, which will then be fed to PIC32MK1024MCM100 through the audio cable and prototype board as input to PIC32MK1024MCM100. This input signal is then sampled by analog input AN0 or AN7 and further signal processing is performed. Both input and output signals can be viewed over X2CScope plots.

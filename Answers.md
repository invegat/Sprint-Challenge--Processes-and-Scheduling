1. a and c, each points to a seperate chunk of 32,000 byte long memory


2. 
   R  running 
   r  on run queue waiting to be scheduled
   D  uninterruptible sleep (usually IO)
   S  interruptible sleep (waiting for an event to complete)
   Z  defunct/zombie, terminated but not reaped by its parent
   T  stopped, either by a job control signal or because
      it is being traced


3. "write" takes approximately 4.8 times more time than printf.


4. Without any new lines printf buffers it's output to more closely match a multiple of the mass storage     device sector size while "write" usually writes a fraction of sector and then has to deal with            appending partial sectors.   The larger buffered printf writes also means fewer "write" calls than        calling "write" directly.

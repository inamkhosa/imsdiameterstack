#How To Build Diameter Stack 

Checkout : 
git clone https://github.com/inamkhosa/imsdiameterstack.git
Compile Diameter App Common library which is pre-requisite for Diameter Stack : 
cd diameterstack/appcommon
Execute the script autogen.sh to generate makefiles from autotools : 
# ./autogen.sh --prefix=/usr –datarootdir=/etc 
For debugging with gdb, following command may be used: 
# ./autogen.sh --prefix=/usr --enable-debug=yes 
For release compilation, following command may be used: 
# ./autogen.sh --prefix=/usr --enable-debug=no --enable-opt=8
Compile the Diameter App Common library : 
# make
Install the compiled Diameter App Common library by using the command: 
# make install
Build and Install Diameter Stack: 
cd diameterstack/baseprotocol
Execute the script autogen.sh to generate makefiles from autotools : 
# ./autogen.sh --prefix=/usr –datarootdir=/etc
Compile the Diameter library :
# make
Install the compiled Diameter App Common library by using the command: 
# make install
* Default installation path of diameter library is /usr/local/lib.
Thats all ! , you are done with the compilation and installation of the diameterstack. the shared library can be found in the above mentioned directory.


 
# imsmrf is licensed under Creative Common License (https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode). 
You can look at https://creativecommons.org/licenses/by-nc-sa/4.0/ for non-commercial usage. 

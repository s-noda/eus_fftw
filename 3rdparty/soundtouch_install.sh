sudo apt-get install automake autoconf libtool build-essential
wget http://www.surina.net/soundtouch/soundtouch-1.8.0.zip
unzip soundtouch-1.8.0.zip
cd soundtouch
./bootstrap
./configure
make
sudo make install

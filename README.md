# Temp3000
Temperature monitoring GUI using libsensors api.
Start from cli using command: temp3000

#Installation
Chips:
sudo apt-get install lm-sensor
sudo sensors-detect

HDDs:
sudo apt-get install hddtemp
sudo dpkg-reconfigure hddtemp
(Leave everything default, interval between checks to user specification).
service hddtemp restart/start

CLI:
nano ~/.bashrc
alias temp3000='/home/<user>/temp3000-build/temp3000'

#Deployment
linuxdeployqt:
chmod a+x /home/<user>/Downloads/linuxdeployqt-continuous-x86_64.AppImage 
export PATH=/home/<user>/Qt5.7.0/5.7/gcc_64/bin/:$PATH
/home/<user>/Downloads/linuxdeployqt-continuous-x86_64.AppImage /home/<user>/build-temp3000-Desktop_Qt_5_7_0_GCC_64bit-Debug/temp3000


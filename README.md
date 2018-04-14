# Temp3000
Temperature monitoring GUI using libsensors api.  
Start from cli using command: temp3000  
Note:  
When running sensors-detect, hit enter for every prompt.  
When configuring hddtemp, leave everything as default except for interval between checks (set to 1).

## Setup
The following steps assume the build is a folder called temp3000-build located in "/home/User/".  
Chips:  
sudo apt-get install lm-sensor  
sudo sensors-detect  

HDDs:  
sudo apt-get install hddtemp  
sudo dpkg-reconfigure hddtemp  
(Leave everything default, interval between checks to user specification).
service hddtemp restart  

CLI:  
nano ~/.bashrc  
alias temp3000='/home/<user>/temp3000-build/temp3000'  
save file  
restart terminal  

Right-click the temp3000 application, select Properties the Permissions.  
Make sure the box titled "Allow executing file as program" is ticked.  

## Deployment
This is assuming Qt5.7.0 is installed in /home/User and the temp3000 folder comtaining the source code is located in /home/User.  

Qt:  
Build the project under Debug in Qt Creator.  

linuxdeployqt:  
Download linuxdeployqt to the Downloads folder.  
chmod a+x /home/User/Downloads/linuxdeployqt-continuous-x86_64.AppImage   
export PATH=/home/User/Qt5.7.0/5.7/gcc_64/bin/:$PATH  
/home/User/Downloads/linuxdeployqt-continuous-x86_64.AppImage /home/User/build-temp3000-Desktop_Qt_5_7_0_GCC_64bit-Debug/temp3000  

Rename the build folder to temp3000-build.  

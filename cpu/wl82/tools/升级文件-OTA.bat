@echo off

@echo *********************************************************************
@echo 			    AC791N SDK ���������ļ�����
@echo *********************************************************************
@echo %date%

::��ִ��download.bat�����ļ�
call .\download.bat

if exist upgrade\*.ufw del upgrade\*.ufw

if not exist upgrade md upgrade

if exist upgrade\readme(����ǰ���Ķ�).txt del upgrade\readme(����ǰ���Ķ�).txt

echo.                               ��Ҫ˵��                                                      >> upgrade\readme(����ǰ���Ķ�).txt
echo. ע������һ��                                                                                >> upgrade\readme(����ǰ���Ķ�).txt
echo. BR22_TWS_VERSIONΪ�̼��汾�ţ���ÿ����Ҫ���豸��������ʱ����Ҫ����ֵ��1��                   >> upgrade\readme(����ǰ���Ķ�).txt
echo. ������¼ʱ��ֵΪBR22_TWS_VERSION=0����Ҫ���豸��������ʱ����Ҫ����ֵ��1��                   >> upgrade\readme(����ǰ���Ķ�).txt
echo. ����ʱBR22_TWS_VERSION=1��Ȼ��������������̼����豸�����������Դ����ƣ�                    >> upgrade\readme(����ǰ���Ķ�).txt
echo. ��Ҫ�ٴζ��豸������ʱ����ֵ��ԭ���Ļ����Ͻ��е���1����˶���������ֵ                     >> upgrade\readme(����ǰ���Ķ�).txt
echo. Ӧ�����ε�����0��1��2��3�������������������һ��������豸����OTA֮��                      >> upgrade\readme(����ǰ���Ķ�).txt
echo. ��ʹ��SM01-DFU.exe���߶��豸��¼bin�ļ�ʱ��������豸���еĻ��Ǿɳ���������               >> upgrade\readme(����ǰ���Ķ�).txt
echo. ��ΪһЩ���߻����õ�������ò�����                                                          >> upgrade\readme(����ǰ���Ķ�).txt
echo. ����ʱ���ڶ�Ӧ ``cpu/(wl80��wl82)/tools/isd_config_rule.c``�ļ����޸�BR22_TWS_VERSION������ >> upgrade\readme(����ǰ���Ķ�).txt
echo.                                                                                             >> upgrade\readme(����ǰ���Ķ�).txt
echo.                                                                                             >> upgrade\readme(����ǰ���Ķ�).txt
echo. ע���������                                                                                >> upgrade\readme(����ǰ���Ķ�).txt
echo. �Ѿ������Ĳ�Ʒ��Ҫ���п�汾�������磺1.0.3.10�汾������1.1.0������������ʧ��ʱ�����Խ�     >> upgrade\readme(����ǰ���Ķ�).txt
echo. �°汾��tools�滻�ɾɰ汾��tools���г��ԡ����ڲ�ͬ�汾uboot���ڲ��죬���ܻ���ֿ�汾����   >> upgrade\readme(����ǰ���Ķ�).txt
echo. ʱ�ļ�У��ʧ�ܵ������                                                                      >> upgrade\readme(����ǰ���Ķ�).txt
echo.                                                                                             >> upgrade\readme(����ǰ���Ķ�).txt
echo.                                                                                             >> upgrade\readme(����ǰ���Ķ�).txt
echo. ���Ķ��ĵ���https://doc.zh-jieli.com/AC79/zh-cn/master/module_example/system/update.html    >> upgrade\readme(����ǰ���Ķ�).txt

::�ٸ����ļ�
copy db_update_files_data.bin upgrade\update-ota.ufw

echo.
echo.
echo �����ļ��Ѿ��ڵ�ǰupgradeĿ¼�����ɣ������ļ����ƣ�update-ota.ufw������OTA�����������ɣ�2���Ӻ��Զ��رմ��ڣ�
echo.
choice /t 2 /d y /n >nul 

pause
::exit
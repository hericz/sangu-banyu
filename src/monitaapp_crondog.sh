#!/bin/bash

#Comand untuk merestart monitaapp, dipanggil via cron
#herry@daunbiru.com
#5 mei 2009

## KETERANGAN ##
#Ganti dulu path dengan yang bersesuaian
#dir_path: path direktori monitaapp
#log_path: path untuk menaruh log file

mon_path=/home/herry/Monita/src/
log_path=/home/herry/Monita/cron_log.txt
pm_path=/home/herry/program/pm_server/src/

#Panduan setting cron
# -Ketik 'crontab -e', lalu kopi paste teks berikut ke cron editor 
# -Hapus '#' pertama di tiap baris)
# -Ganti path dengan di baris terakhir lokasi file ini berada

#=======CRONTAB EDIT SAMPLE======
#$crontab -e
## m h  dom mon dow   command
## jadi begini lho
## A crontab file consists of lines of six fields each.
## The fields are separated by spaces or tabs.
##   1.  minute (0-59),
##   2. hour (0-23),
##   3. day of the month (1-31),
##   4. month of the year (1-12),
##   5. day of the week (0-6 with 0=Sunday).
## minute <spasi> jam <spasi> tanggal <spasi> bulan <spasi> hari-dlm-minggu <spa$
#0 0 * * * /home/monita/MonitaApp/monitaapp_crondog.sh 
#=======EOF CRONTAB EDIT SAMPLE======



date >> $log_path
echo Jalankan Cron >> $log_path

#secara brutal, matikan aplikasi monitaapp yang masih berjalan
pkill monitaapp

#pause 2 detik
`sleep 2`


#pindah ke direktori path
cd $mon_path  >> $log_path

pwd >> $log_path

#jalankan monitaapp
export DISPLAY=:0 && ./monitaapp & 

echo Script Selesai >> $log_path


#sh

date >> /home/herry/cron_log.txt
echo jalankan cron >> /home/herry/cron_log.txt
pkill monitaapp

cd /home/herry/Monita/src  >> /home/herry/cron_log.txt
/home/herry/Monita/src/monitaapp & >> /home/herry/cron_log.txt
echo script selesai >> /home/herry/cron_log.txt

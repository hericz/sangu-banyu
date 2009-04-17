- Jika mau mengupdate copy file *.php, *.js, *.css
- 

Menggunakan web Monita :
- instal LAMP
- kopi semua data ini ke /var/www
- Edit config.php, sesuaikan dengan kondisi setempat
- Ada variabel yang sifatnya STATIS, makanya perlu diubah manual
	(ini karena belum dibuat dinamis atau sengaja dibuat statis)
	> untuk menjalankan data random, buka /var/www/tes/putData.php
		Ubah baris ke 24, sesuaikan dengan no equipment PLTD ente.
	> Jalankan localhost/tes/insert.php



9 Feb 09
--------------
Monita Web server  versi 1.0.0.1
mesin diganti : dari full javascript ke (php & js)
	> loading lebih cepet
tampilan masih sama dengan versi 0.x.x
+ : - cookies
	- fitur milih dept & perusahaan
	-
	
Progres :
9 Feb 09
---------
- fetch sql di php udah kelar
- tampilin grafik beres


10 Feb 09
---------
- bikin css tampilan umum, menu
- 


16 Feb 09
------------------------
Buat dns dengan nama : datamonita.com
Konfigurasi :
- Buat file bernama datamonita di direktori /etc/apache2/site-available
	isi :
		<VirtualHost *>
		ServerName datamonita.com
		ServerAlias www.datamonita.com
		ServerAdmin afrendy@daunbiru.com
		DocumentRoot /var/www/monitaKantor/
		#DocumentRoot /media/sda5/ProjDB/webmonita/DataWeb/
		</VirtualHost>
- di file /etc/hosts, tambahkan : 127.0.0.1 datamonita.com
- Jalankan : sudo a2ensite datamonita && sudo /etc/init.d/apache2 restart




<?php
/*
	Copyleft 2008 Afrendy Bayu / DBE / v1.0.0
	Helwin, lombok timur ketika ditemani kholis dan tetangga baru, devi dan dia sekarang pindah, hiks
//*/

/*/
	No fetch :
	1. ambil menu dan sub menu
	2. identitas perusahaan
	3. menu kiri bawah, menampilkan equipment departemen 
	4. menu kiri atas, menampilkan kelompok titik ukur
	5. isi isi isi isi isi isi per Kelompok pengukuran
	6. isi per mesin 
	7. isi KW tiap mesin untuk Home
	8. data isi histori
	9. opsi histori
	
//*/
//Send some headers to keep the user's browser from caching the response.
header("Expires: Mon, 26 Jul 2008 05:00:00 GMT" ); 
header("Last-Modified: " . gmdate( "D, d M Y H:i:s" ) . "GMT" ); 
header("Cache-Control: no-cache, must-revalidate" ); 
header("Pragma: no-cache" );
header("Content-Type: text/xml; charset=utf-8");

require_once('database.php');


$xml = '<?xml version="1.0" encoding="utf-8"?><rss version="2.0"><channel>';		// ?xml version="1.0" encoding="utf-8"?
$xml .= '<title>daunbiruengineering</title>';
$xml .= '<agenda>bersenang-senang di lombok</agenda>';
//*
if (isset($_GET['fetchMenu']) && $_GET['fetchMenu'] != '') {
	if ($_GET['fetchMenu'] == 1) {		// Isi Home
		$sql  =	"select id_titik,nama_titik " .
				",(select `data` from data_jaman where id_titik = titik_ukur.id_titik order by id_jaman desc limit 0,1) as nilai " .
				",(select `waktu` from data_jaman where id_titik = titik_ukur.id_titik order by id_jaman desc limit 0,1) as waktu " .
				",(select curtime()) as saiki " . 
				"from titik_ukur where id_group_titik_ukur = 64";
		$data = db_query($sql) or die(mysql_error());
		$n = 1;
		while ($message_array = db_fetch_array($data)) {
			$xml .= '<pesan id="' . $n . '">';
			$xml .= '<titik>'  . htmlspecialchars($message_array['id_titik']) . '</titik>';
			$xml .= '<nama>'  . htmlspecialchars($message_array['nama_titik']) . '</nama>';
			$xml .= '<nilai>'  . htmlspecialchars($message_array['nilai']) . '</nilai>';
			$xml .= '<waktu>' . htmlspecialchars($message_array['waktu'])  . '</waktu>';
			$xml .= '<saiki>' . htmlspecialchars($message_array['saiki'])  . '</saiki>';
			$xml .= '</pesan>';
			$n++;
		}
		mysql_free_result($data);

	}
}


$xml .= '</channel></rss>';
echo $xml;
?>

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
require_once('config.php');

global $equipment;
$bulan = array("Jan","Feb","Mar","Apr","Mei","Jun","Jul","Agt","Sep","Okt","Nov","Des");

$xml = '<?xml version="1.0" encoding="utf-8"?><rss version="2.0"><channel>';		// ?xml version="1.0" encoding="utf-8"?
$xml .= '<title>daunbiruengineering</title>';
$xml .= '<agenda>bersenang-senang di lombok</agenda>';
//*
if (isset($_GET['fetchMenu']) && $_GET['fetchMenu'] != '') {
	if ($_GET['fetchMenu'] == 1) {		// Isi Home
		//*
		$data = $_GET['arIdEq'];
		$arIdEq = preg_split ("/[~]+/",$data);		//echo "Jml Array : ". count($arIdEq);
		$data =  "('".join($arIdEq,"','")."')";		//echo "<br>Isi Array : ". $data;
		//*/
		
		//*
		$sql  =	"select id_titik,nama_titik " .
				",(select `data` from data_jaman where id_titik = titik_ukur.id_titik order by id_jaman desc limit 0,1) as nilai " .
				",(select `waktu` from data_jaman where id_titik = titik_ukur.id_titik order by id_jaman desc limit 0,1) as waktu " .
				",(select curtime()) as saiki " . 
				"FROM titik_ukur where kode_titik = 'kw' and id_equipment in ".$data;
				//"FROM titik_ukur where kode_titik = 'kw' and id_equipment in ('22', '23')";
		$data = db_query($sql) or die(mysql_error());
		$n = 1;
		while ($message_array = db_fetch_array($data)) {
			$xml .= '<pesan id="' . $n . '">';
			$xml .= '<titik>'  . htmlspecialchars($message_array['id_titik']) . '</titik>';
			$xml .= '<nama>'  . htmlspecialchars($message_array['nama_titik']) . '</nama>';
			$xml .= '<nilai>'  . htmlspecialchars($message_array['nilai']) . '</nilai>';
			$xml .= '<waktu>' . ubahwaktu(htmlspecialchars($message_array['waktu']))  . '</waktu>';
			$xml .= '<saiki>' . htmlspecialchars($message_array['saiki'])  . '</saiki>';
			$xml .= '</pesan>';
			$n++;
		}
		mysql_free_result($data);
		//*/
		//$xml .= '<pesan id="3"><titik>229</titik><nama>Daya</nama><nilai>5209</nilai><waktu>27 Feb 2009 9:00:12</waktu><saiki>09:00:12</saiki></pesan>
		//		 <pesan id="3"><titik>230</titik><nama>Daya</nama><nilai>5209</nilai><waktu>27 Feb 2009 9:00:12</waktu><saiki>09:00:12</saiki></pesan>';
		
	} elseif ($_GET['fetchMenu'] == 2) {		// Isi data Mesin
		//*		
		$sql  =	"select id_titik,nama_titik ".
				",(select `data` from data_jaman where id_titik = titik_ukur.id_titik order by id_jaman desc limit 0,1) as nilai ".
				",(select `waktu` from data_jaman where id_titik = titik_ukur.id_titik order by id_jaman desc limit 0,1) as waktu ".
				",(select curtime()) as saiki ";
				//"FROM titik_ukur where id_equipment = 22";
		if (isset($_GET['idEq']) && $_GET['idEq'] != '')
			$sql  .= "FROM titik_ukur where id_equipment = ".$_GET['idEq'];
		elseif (isset($_GET['idGr']) && $_GET['idGr'] != '')
			$sql  .= "FROM titik_ukur where id_group_titik_ukur = ".$_GET['idGr'];

		$data = db_query($sql) or die(mysql_error());
		$n = 1;
		while ($message_array = db_fetch_array($data)) {
			$xml .= '<pesan id="' . $n . '">';
			$xml .= '<titik>'  . htmlspecialchars($message_array['id_titik']) . '</titik>';
			$xml .= '<nama>'  . htmlspecialchars($message_array['nama_titik']) . '</nama>';
			$xml .= '<nilai>'  . htmlspecialchars($message_array['nilai']) . '</nilai>';
			$xml .= '<waktu>' . ubahwaktu(htmlspecialchars($message_array['waktu']))  . '</waktu>';
			$xml .= '<saiki>' . htmlspecialchars($message_array['saiki'])  . '</saiki>';
			$xml .= '</pesan>';
			$n++;
		}
		mysql_free_result($data);
		//*/
		
		/*
		$xml .= '<pesan id="1"><titik>227</titik><nama>Suhu Charge Air Kiri</nama><nilai>55.313598632812</nilai><waktu>27 Feb 2009 9:00:12</waktu><saiki>09:00:12</saiki></pesan>
		<pesan id="2"><titik>228</titik><nama>Suhu Charge Air Kanan</nama><nilai>51.654216766357</nilai><waktu>27 Feb 2009 9:00:12</waktu><saiki>09:00:12</saiki></pesan>
		<pesan id="3"><titik>229</titik><nama>Daya</nama><nilai>5209</nilai><waktu>27 Feb 2009 9:00:12</waktu><saiki>09:00:12</saiki></pesan>
		<pesan id="4"><titik>231</titik><nama>Tekanan Charge Air Kiri</nama><nilai>6.478223323822</nilai><waktu>27 Feb 2009 9:00:12</waktu><saiki>09:00:12</saiki></pesan>
		<pesan id="5"><titik>232</titik><nama>Tekanan Charge Air Kanan</nama><nilai>5.0257029533386</nilai><waktu>27 Feb 2009 9:00:12</waktu><saiki>09:00:12</saiki></pesan>
		<pesan id="6"><titik>233</titik><nama>Suhu Lub Oil Kiri</nama><nilai>63.170803070068</nilai><waktu>27 Feb 2009 9:00:12</waktu><saiki>09:00:12</saiki></pesan>
		<pesan id="7"><titik>234</titik><nama>Suhu Lub Oil Kanan</nama><nilai>53.798816680908</nilai><waktu>27 Feb 2009 9:00:12</waktu><saiki>09:00:12</saiki></pesan>
		<pesan id="8"><titik>235</titik><nama>Tekanan Lub Oil Kiri</nama><nilai>5.5916266441345</nilai><waktu>27 Feb 2009 9:00:12</waktu><saiki>09:00:12</saiki></pesan>
		<pesan id="9"><titik>236</titik><nama>Tekanan Lub Oil Kanan</nama><nilai>5.6201009750366</nilai><waktu>27 Feb 2009 9:00:12</waktu><saiki>09:00:12</saiki></pesan>
		<pesan id="10"><titik>237</titik><nama>Tegangan R</nama><nilai>154</nilai><waktu>27 Feb 2009 9:00:12</waktu><saiki>09:00:12</saiki></pesan>';
		//*/
	} elseif ($_GET['fetchMenu'] == 3) {
		$sql  =	"select id_titik,nama_titik ".
				",(select `data` from data_jaman where id_titik = titik_ukur.id_titik order by id_jaman desc limit 0,1) as nilai ".
				",(select `waktu` from data_jaman where id_titik = titik_ukur.id_titik order by id_jaman desc limit 0,1) as waktu ".
				",(select curtime()) as saiki ".
				//"FROM titik_ukur where id_equipment = 22";
				"FROM titik_ukur where id_equipment = ".$_GET['idEq'];
		$data = db_query($sql) or die(mysql_error());
		$n = 1;
		while ($message_array = db_fetch_array($data)) {
			$xml .= '<pesan id="' . $n . '">';
			$xml .= '<titik>'  . htmlspecialchars($message_array['id_titik']) . '</titik>';
			$xml .= '<nama>'  . htmlspecialchars($message_array['nama_titik']) . '</nama>';
			$xml .= '<nilai>'  . htmlspecialchars($message_array['nilai']) . '</nilai>';
			$xml .= '<waktu>' . ubahwaktu(htmlspecialchars($message_array['waktu']))  . '</waktu>';
			$xml .= '<saiki>' . htmlspecialchars($message_array['saiki'])  . '</saiki>';
			$xml .= '</pesan>';
			$n++;
		}
		mysql_free_result($data);		
	} elseif ($_GET['fetchMenu'] == 10) {
		$wektu = "20080905-050018";
		$xml .= '<pesan><jml>'.count($equipment).'  </jml><bayu>'.ubahwaktu($wektu).'</bayu></pesan>';
	}
}


$xml .= '</channel></rss>';
echo $xml;

//	20080905-050018
function ubahwaktu($wektu) {
	global $bulan;
	$tgl = intval(substr($wektu,6,2));
	$bln = intval(substr($wektu,4,2));
	$jam = intval(substr($wektu,9,2));
	$isi = "$tgl ".($bulan[$bln-1])." ".substr($wektu,0,4)." $jam:".substr($wektu,11,2).":".substr($wektu,13,2);
	return $isi;
}
?>

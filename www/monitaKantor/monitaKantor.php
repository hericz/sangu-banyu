<html><head>
</head><body>

<div id="tahuIsi">
<table id="tabelIsiTahu" border="1" bordercolor="black" cellpadding="0" cellspacing="0" width="530"><thead>
<tr align="center"><th width="200"><b>Nama</b></th><th width="100"><b>Status</b></th><th><b>Update</b></th></tr></thead>

<?php 

require("email/kirimEmail.php");
require("database.php");

	global $pintu;
	$pintu = array();

	$sql =	'select id_titik,nama_titik ' .
			',(select `data` from data_jaman where id_titik = titik_ukur.id_titik order by id_jaman desc limit 0,1) as nilai ' .
			',(select `waktu` from data_jaman where id_titik = titik_ukur.id_titik order by id_jaman desc limit 0,1) as waktu ' .
			'from titik_ukur where id_group_titik_ukur = 64';
	
	$data = db_query($sql) or die(mysql_error());
	while ($message_array = db_fetch_array($data)) {
		//$i=0;
		$idtitik = htmlspecialchars($message_array['id_titik']);
		$nama = htmlspecialchars($message_array['nama_titik']);
		$nilai = htmlspecialchars($message_array['nilai']);
		$waktu = htmlspecialchars($message_array['waktu']);

		$isi  = array("id_pintu" => $idtitik, "nama" => $nama, "nilai" => $nilai, "waktu" => $waktu);
		array_push($pintu, $isi);
		//$i++;
	}
	mysql_free_result($data);

function isiWaktu($nilai) {
	$nilai = trim($nilai);
	return substr($nilai,0,4)."-".substr($nilai,4,2)."-".(substr($nilai,6,2). " " .substr($nilai,9,2).":".substr($nilai,11,2).":".substr($nilai,13,2));
}
	
	if (count($pintu)) {
		for($i=0; $i<count($pintu); $i++) {
			echo '<tr><td>' . $pintu[$i]["nama"] . '</td>';
			if($pintu[$i]["nilai"] > 200) $status = "terbuka"; else $status = "tertutup";
			echo "<td><div id='status$i'>$status</div></td>";
			//echo "<td><div id='waktu$i'>" .  $pintu[$i]["waktu"]. "</div></td></tr>";
			echo "<td><div id='waktu$i'>" .  isiWaktu($pintu[$i]["waktu"]) . "</div></td></tr>";
		}
	}

	if (count($pintu)) {
		$isi = "<br>##isidata<br>";		
		for($i=0; $i<count($pintu); $i++) {
			//echo '<tr><td>' . $pintu[$i]["nama"] . '</td>';
			//if($pintu[$i]["nilai"] > 200) $status = "terbuka"; else $status = "tertutup";
			if($pintu[$i]["nilai"] > 200) $status = "0 terbuka"; else $status = "1 tertutup";
			//echo "<td><div id='status$i'>$status</div></td>";
			//echo "<td><div id='waktu$i'>" .  $pintu[$i]["waktu"]. "</div></td></tr>";
			//echo "<td><div id='waktu$i'>" .  isiWaktu($pintu[$i]["waktu"]) . "</div></td></tr>";
			$isi .= $pintu[$i]["nama"]." * ".$status." * ".isiWaktu($pintu[$i]["waktu"])."<br>";	//isiWaktu($pintu[$i]["waktu"])		//date("Y-m-d G:i:s")
		}
		$isi .= "##<br>\n";
	}

$judul = "data " . date("Y-m-d G:i:s");
echo "jdl : $judul<br>\n";
echo $isi;

//*/
if(kirimImel($judul, $isi)) {
	echo "<br>Sudah terkirim";
}
//*/


?>

</table></div>

</body></html>

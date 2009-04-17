<script language="javascript" type="text/javascript">
<?php
	//echo '		var rek = '.$_GET["rek"].";\n";
	//echo '		var tf  = '.$_GET["tf"].";\n";
	/*
	if ($_COOKIE["id_dept"]) $c_id_dept = $_COOKIE["id_dept"];
	if ($_COOKIE["jmlRekHome"]) 
		$rek = $_COOKIE["jmlRekHome"];
	if ($_COOKIE["timeRefresh"]) 
		$tf = $_COOKIE["timeRefresh"];
	//*/
	echo '		var rek = '.$rek.";\n";
	echo '		var tf  = '.$tf.";\n";
?>
		</script>	
	
	
<div id="tahuIsi">
<!-- jika di home  -->
	<div id="gedebug"></div>
<?php
	
	//echo "Data update sekarang belum dibuat";
	global $gabung;
	$gabung = array();
	$gabTtk = array();
	
	if ($_GET["idEq"]) {
		$idEq = $_GET["idEq"];
		//echo "ini urusan Equipment no ".$_GET["idEq"];
		/*
			Tabel data parameter satu mesin 
			semua titik dan semua grup titik ukur
			tanpa grafik
		*/

		$sql =	'select id_titik, id_group_titik_ukur '. 
				', (select nama_equipment from equipment where id_equipment = '.$idEq.') as nmEq '.
				', (select nama_group from group_titik_ukur where id_group = id_group_titik_ukur) as nmgroup '.
				', kode_titik, nama_titik, satuan '.
				'from titik_ukur where id_equipment = '.$idEq.' order by nmgroup asc, nama_titik asc';
		
		$data = db_query($sql) or die(mysql_error());
		while ($message_array = db_fetch_array($data)) {
			$i=0;
			$idtitik = htmlspecialchars($message_array['id_titik']);
			$nmEq	 = htmlspecialchars($message_array['nmEq']);
			$idgroup = htmlspecialchars($message_array['id_group_titik_ukur']);
			$nmgroup = htmlspecialchars($message_array['nmgroup']);
			$kdtitik = htmlspecialchars($message_array['kode_titik']);
			$nmtitik = htmlspecialchars($message_array['nama_titik']);
			$satuan	 = htmlspecialchars($message_array['satuan']);

			$isi  = array("idtitik" => $idtitik, "idgroup" => $idgroup, "nmgroup" => $nmgroup, 
					"kdtitik" => $kdtitik, "nmtitik" => $nmtitik, "satuan" => $satuan, "nmEq" => $nmEq);
			array_push($gabung, $isi);
			$i++;
		}
		
		mysql_free_result($data);
		
		if (count($gabung)) {
?>

	<script language="javascript" type="text/javascript">
		tahuIsiMesin(<?php echo $idEq ?>);
	</script>
	
			<h2 class="title"><strong>Parameter <?php echo $gabung[1]["nmEq"] ?></strong></h2>
			<table id="tabelIsiTahu" border="1" bordercolor="black" cellpadding="0" cellspacing="0" width="530">
				<thead>
					<tr align="center">
						<th width="300"><b>Nama</b></th>
						<th width="100"><b>Nilai</b></th>
						<th><b>Update</b></th>
					</tr>
				</thead>
<?php
			$namagroup = "";
			for($i=0; $i<count($gabung); $i++) {
				if ($namagroup != $gabung[$i]["nmgroup"]) {
					echo '<tr align="center"><td align="left" colspan="3">'.
						'<b><a href="home.php?idGr='.$gabung[$i]["idgroup"].
						'" title="'.$gabung[$i]["nmgroup"]." ".$gabung[1]["nmEq"].'" ">'.
						$gabung[$i]["nmgroup"]."</a></b></td></tr>\n";
					$namagroup = $gabung[$i]["nmgroup"];
				}
				echo '<tr align="center"><td align="left"> ' . $gabung[$i]["nmtitik"] . "</td>\n";
				echo '<td><span id="nilaiM'.$gabung[$i]["idtitik"].'">0</span> '.$gabung[$i]["satuan"]."</td>\n";
				echo '<td><div id="waktuM'.$gabung[$i]["idtitik"].'">now</div></td></tr>'."\n";
			}
			echo "</table><br />";
		} else {
			echo "<h2 class='title'><strong>Titik ukur tidak ada</strong></h2>";
		}		
	} elseif ($_GET["idGr"]) {
		$idGr = $_GET["idGr"];
		//echo "ini urusan Group titik ukur no ".$_GET["idGr"];
		/*
			Tabel data parameter
			titik ukur dalam grup titik ukur
			dengan grafik
		*/
		
		$sql =	'select id_titik, kode_titik, id_equipment '.
				', (select nama_equipment from equipment where id_equipment = titik_ukur.id_equipment) as nmEq '.
				', (select nama_group from group_titik_ukur where  id_group = '.$idGr.') as nmgroup '.
				', nama_titik, satuan '.
				'from titik_ukur where id_group_titik_ukur = '.$idGr.' order by nama_titik asc';
		
		
		$data = db_query($sql) or die(mysql_error());
		while ($message_array = db_fetch_array($data)) {
			$i=0;
			$idtitik = htmlspecialchars($message_array['id_titik']);
			$kdtitik = htmlspecialchars($message_array['kode_titik']);
			$nmEq	 = htmlspecialchars($message_array['nmEq']);
			$idEq	 = htmlspecialchars($message_array['id_equipment']);
			$nmgroup = htmlspecialchars($message_array['nmgroup']);
			$nmtitik = htmlspecialchars($message_array['nama_titik']);
			$satuan	 = htmlspecialchars($message_array['satuan']);

			$isi  = array("idtitik" => $idtitik, "idEq" => $idEq, "nmgroup" => $nmgroup, 
					"kdtitik" => $kdtitik, "nmtitik" => $nmtitik, "satuan" => $satuan, "nmEq" => $nmEq);
			array_push($gabung, $isi);
			$i++;
		}
		
		mysql_free_result($data);
		
		if (count($gabung)) {
?>
	<script language="javascript" type="text/javascript">
		tahuIsiGroup(<?php echo $idGr ?>);
	</script>

			<h2 class="title">
				<strong><?php echo "Parameter ".$gabung[1]["nmgroup"]." pada ".$gabung[1]["nmEq"] ?></strong></h2>
			<table id="tabelIsiTahu" border="1" bordercolor="black" cellpadding="0" cellspacing="0" width="530">
				<thead>
					<tr align="center">
						<th width="300"><b>Nama</b></th>
						<th width="100"><b>Nilai</b></th>
						<th><b>Update</b></th>
					</tr>
				</thead>
<?php
			for($i=0; $i<count($gabung); $i++) {
				echo '<tr align="center"><td align="left"> ' . $gabung[$i]["nmtitik"] . "</td>\n";
				echo "<td><span id='nilaiGp".$gabung[$i]["idtitik"]."'></span> ".$gabung[$i]["satuan"]."</td>\n";
				echo "<td><div id='waktuGp".$gabung[$i]["idtitik"]."'>".$gabung[$i]["satuan"]."</div></td></tr>\n";
			}
?>			

			</table><br />

			<h2 class='title'><strong>Grafik Detail</strong></h2>	
			<table id="tabelIsiTahu" border="1" bordercolor="black" cellpadding="0" cellspacing="0" width="530">
<?php
			for($i=0; $i<count($gabung); $i++) {
				echo "<tr><td valign='top' width='400' height='190'><div id='grafik".$gabung[$i]["idtitik"]."'></div></td>";
				$ket = $gabung[$i]["nmtitik"]."<br> ".$gabung[$i]["satuan"];
				echo "<td valign='center' align='center'><div id='ket".$gabung[$i]["idtitik"]."'>".$ket."</div></td></tr>\n";
				array_push($gabTtk, $gabung[$i]["idtitik"]);
			}
			
			echo '<script language="javascript" type="text/javascript">';
			echo 'var n = new Array("', join($gabTtk,'","'), '");';
?>			
			<!--			
				exampleData = [];
				var obj = {};
				
				for (j=0; j<rek; j++) {
					isi = (10+j*10);
					//isi = 0;
					obj = {no: j+1, nama:"blavla", nilai:isi, waktu:"0"};
					exampleData.push(obj);
				}
				
				for(i=0; i<n.length; i++) {
					grafikKWz(exampleData, "grafik"+n[i], 300, 0, "", 1, 15, 10, " (x"+(tf/1000)+" detik yg lalu)");
				}
			//-->
			</script>
<?php
			echo "</table>";
		} else {
			echo "<h2 class='title'><strong>Titik ukur tidak ada</strong></h2>";
		}
	} elseif ($c_id_dept) {
	//} elseif ($_GET["id"]) { 	/*$c_id_dept*/
		/*
			Tabel dan grafik beban semua mesin
			halaman muka sebagai home
		*/
		$gabTtk = array();
		$sql =	'select id_titik, id_equipment, nama_titik, satuan '.
				', (select nama_equipment from equipment where id_equipment = titik_ukur.id_equipment) as nmEq '.
				'from titik_ukur where kode_titik = "kW" and '.
				'((select id_dept from equipment where id_equipment = titik_ukur.id_equipment)="'.$c_id_dept.
				'") order by nmEq asc';	
		
		$data = db_query($sql) or die(mysql_error());
		while ($message_array = db_fetch_array($data)) {
			$i=0;
			$idtitik = htmlspecialchars($message_array['id_titik']);
			$nmEq	 = htmlspecialchars($message_array['nmEq']);
			$idEq	 = htmlspecialchars($message_array['id_equipment']);
			$nmtitik = htmlspecialchars($message_array['nama_titik']);
			$satuan = htmlspecialchars($message_array['satuan']);

			$isi  = array("idtitik" => $idtitik, "nmtitik" => $nmtitik, "satuan" => $satuan, 
				"idEq" => $idEq, "nmEq" => $nmEq);
			array_push($gabTtk, $idEq);
			array_push($gabung, $isi);
			$i++;
		}
		
		$jmlArr = count($gabung);
		mysql_free_result($data);
		if ($jmlArr) {
?>
		<script language="javascript" type="text/javascript">
			<?php 
				echo 'var arIdEq = "'.join($gabTtk,'~').'";';
				//echo 'var idEq = ["'.join($gabTtk,'","').'"];';
				//setCookie("arIdEq", idEq, 365);
				//echo 'var arIdEq=["23","36"];';
				//echo 'document.getElementById("gedebug").innerHTML += "'.join($gabTtk,' ').'";';
				//echo 'tahuIsiHome(arIdEq);';
				echo 'tahuIsiHome(arIdEq);';
			?>
			//document.getElementById("gedebug").innerHTML += "isi idEq : "+idEq;
			
		</script>

			<h2 class="title">
				<strong>Beban Mesin</strong></h2>
			<table id="tabelIsiTahu" border="1" bordercolor="black" cellpadding="0" cellspacing="0" width="530">
				<thead>
					<tr align="center">
						<th width="300"><b>Nama</b></th>
						<th width="100"><b>Nilai</b></th>
						<th><b>Update</b></th>
					</tr>
				</thead>
<?php
			for($i=0; $i<$jmlArr; $i++) {
				echo '<tr align="center"><td class="namaTitik" align="left"> ' . $gabung[$i]["nmEq"] . "</td>\n";
				echo "<td><span id='nilai".$gabung[$i]["idtitik"]."'>0</span> ".$gabung[$i]["satuan"]."</td>\n";
				echo "<td><div id='waktu".$gabung[$i]["idtitik"]."'>sekarang</div></td></tr>\n";
			}
			//echo '<tr align="center"><td><b>Total Daya</b></td><td><b>Nilai</b></td><td><b>Update</b></td></tr>';
?>
		<tr align="center">
			<td><b>Total Daya</b></td>
			<td><b><span id="totalDaya">Nilai</span> kW</b></td>
			<td><div id="totalUpdate">Update</div></td>
		</tr>
		</table><br />

		<h2 class='title'><strong>Grafik Detail</strong></h2>	
			<table id="tabelIsiTahu" border="1" bordercolor="black" cellpadding="0" cellspacing="0" width="530">

<?php
		
			$gabTtk = array();
			for($i=0; $i<$jmlArr; $i++) {
				echo "<tr><td valign='top' width='400' height='190'><div id='grafik".$gabung[$i]["idtitik"]."'>&nbsp;</div></td>\n";
				$ket =	"Daya<br>".$gabung[$i]["nmEq"].
						"<br><span id='nilaiG".$gabung[$i]["idtitik"]."'>0</span> ".$gabung[$i]["satuan"].
						"<div id='waktuG".$gabung[$i]["idtitik"]."'></div>";
				echo "<td valign='center' align='center'><div id='ket".$gabung[$i]["idtitik"]."'>".$ket."</div></td></tr>\n";
				array_push($gabTtk, $gabung[$i]["idtitik"]);
			}
			//echo 'var n = new Array("', join($gabTtk,'","'), '");';
			//echo 'var rek = $_GET["rek"]';
		}
			echo '<script language="javascript" type="text/javascript">';
			echo 'var n = new Array("', join($gabTtk,'","'), '");';
?>
		<!--
			exampleData = [];
			var obj = {};
			for (j=0; j<rek; j++) {
				//isi = (10+j*10);
				isi = 0;
				obj = {no: j+1, nama:"blavla", nilai:isi, waktu:"0"};
				exampleData.push(obj);
			}
			for(i=0; i<n.length; i++) {
				//grafikKWz(dataChart, lokasi, hmax, hmin, labelY, periode, posX, posY, selang)
				grafikKWz(exampleData, "grafik"+n[i], 8000, 0, "", 1, 15, 10, " (x"+(tf/1000)+" detik yg lalu)")
			}
		//-->
<?php
		echo '</script>';		
		echo '</table>';
	}else {
		//echo "ga berurusan";
		echo '<h2 class="title"><strong>Data tidak valid</strong></h2><br /><br />';
		echo 'Silakan berkunjung ke <a href="index.html">Home</a>';
	}
?>
	

</div> <!-- end div tahuisi -->

<?php

function isiWaktu($nilai) {
	$nilai = trim($nilai);
	return (substr($nilai,6,2) . " " . substr($nilai,4,2) . " " . substr($nilai,0,4) . " " . substr($nilai,9,2) . ":" . substr($nilai,11,2) . ":" . substr($nilai,13,2));
}

?>



<?php
	$nama_produk = "Sistem Monitoring Online";
	
	require_once("database.php");
	global $dept;
	$equipment = array();
	
	if ($c_id_dept) {
		
		$sql =	"select * from equipment where id_dept=" . $c_id_dept . " order by no_urut asc";
		$data = db_query($sql) or die(mysql_error());
		while ($message_array = db_fetch_array($data)) {
			$i=0;
			$idEq  = htmlspecialchars($message_array['id_equipment']);
			$nama  = htmlspecialchars($message_array['nama_equipment']);
			$jnsEq = htmlspecialchars($message_array['jenis_equipment']);
			$isi  = array("id_Eq" => $idEq, "nama" => $nama, "jns_eq" => $jnsEq);
			array_push($equipment, $isi);
			$i++;
		}
		mysql_free_result($data);
		//*
		//echo "jml eq : " . count($equipment) . "<br>";
		//for($i=0; $i<count($equipment); $i++) {
			//echo $equipment[$i]["nama"] . " " . $equipment[$i]["id_Eq"] . "  <br>";
			//echo "isi : " . $equipment[$i]["nama"] . "  <br>";
		//}
	}
	
	if (count($equipment)>0) {
	//*/
		$group = array();
		$sql =	"select * from group_titik_ukur where ";
		for ($j=0; $j<(count($equipment)); $j++) {
			$sql = $sql . " id_equipment=" . $equipment[$j]["id_Eq"];
			if ($j+1 != (count($equipment))) 
				$sql = $sql . " or ";
		}
		$sql .= " order by id_equipment asc, nama_group asc";
		//echo $sql;
		
		$data = db_query($sql) or die(mysql_error());
		while ($message_array = db_fetch_array($data)) {
			$i=0;
			$idGr  = htmlspecialchars($message_array['id_group']);
			$nama  = htmlspecialchars($message_array['nama_group']);
			$idEq = htmlspecialchars($message_array['id_equipment']);
			$isi  = array("id_gr" => $idGr, "nama" => $nama, "id_eq" => $idEq);
			array_push($group, $isi);
			$i++;
		}
		mysql_free_result($data);
	} else {
		//echo "tidak ada Equipment<br>";
	}
	/*
	echo "<br>";
	for($i=0; $i<count($group); $i++) {
		echo $group[$i]["id_eq"] . " " . $group[$i]["id_gr"] . " " . $group[$i]["nama"] . "  <br>";
		//echo $group[$i]["nama"] . "  ";
	}
	//*/
?>

<div id="header">
	<div class="idclass">
		<div id="identitas"><h1><?php echo $nama_produk ?></h1><br><h1><?php "dsda" ?></h1></div>
		<div class="wktclass">
			<div id="mongso"></div>
				<div class="menuclass">
				<!--div id="menuatas"></div></div>
			</div>
		</div>
		</div-->

				
				
<div id="menuatas"><ul id="nav">
<li><a href="index.html">Home</a></li>
<li><a href="cookie.html">Setting</a></li>
<?php
	if (count($equipment)>0) {
		for($i=0; $i<count($equipment); $i++) {
			//echo $equipment[$i]["nama"] . " " . $equipment[$i]["id_Eq"] . "  <br>";
			//echo "<li>" . $equipment[$i]["nama"] . "<ul>";
			$tulis = '<li><a href="detail.php?idEq=%d" >%s</a><ul>';
			printf($tulis, $equipment[$i]["id_Eq"], $equipment[$i]["nama"] );
			for ($j=0; $j<(count($group)); $j++) {
				if ($equipment[$i]["id_Eq"] == $group[$j]["id_eq"]) {
					$tulis = '<li><a href="detail.php?idGr=%d" >%s</a></li>';
					printf($tulis, $group[$j]["id_gr"], $group[$j]["nama"]);
					//echo '<li><a href="?">' . $group[$j]["nama"] . '</a></li>';
				}
			}
			echo "</ul></li>";
		}
	}
	
	$iki = "bebek adus";
	//echo $iki;
?>
</ul></div>
</div></div></div>
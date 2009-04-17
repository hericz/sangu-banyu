
<?php
	
	$nama_dept	 = "";
	$nama_pers	 = "";
	
	//require_once("database.php");
	global $dept;
	$equipment = array();
	
	if ($c_id_dept) {
		
		//$sql =	"select * from equipment where id_dept=" . $c_id_dept . " order by no_urut asc";
		$sql =	'select id_equipment, id_dept, nama_equipment, kode_equipment, no_urut '.
				', (select nama_dep from departemen where id_dep = id_dept) as nmdept '.
				', (select nama_pers from perusahaan where id_pers = '.
				'(select id_pers from departemen where id_dep = id_dept)) as nmpers '.
				'from equipment where id_dept = '.$c_id_dept.' order by nama_equipment asc';
		
		$data = db_query($sql) or die(mysql_error());
		while ($message_array = db_fetch_array($data)) {
			$i=0;
			$idEq   = htmlspecialchars($message_array['id_equipment']);
			$nama   = htmlspecialchars($message_array['nama_equipment']);
			$jnsEq  = htmlspecialchars($message_array['jenis_equipment']);
			$nmdept = htmlspecialchars($message_array['nmdept']);
			$nmpers = htmlspecialchars($message_array['nmpers']);
			$isi  = array("id_Eq" => $idEq, "nama" => $nama, "jns_eq" => $jnsEq);
			$nama_dept = $nmdept;
			$nama_pers = $nmpers;

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
	<div id="identitas"><h1><?php echo $nama_produk."<br>". $nama_dept."<br>".$nmpers ?></h1></div>
	<div id="mongso">saiki wektu</div>
				
	<div id="menu">
	<ul><li><a href="index.html"><h2>Home</h2></a></li></ul>
	<ul><li><a href="setting.html"><h2>Setting</h2></a></li></ul>
<?php
	if (count($equipment)>0) {
		for($i=0; $i<count($equipment); $i++) {
			//echo $equipment[$i]["nama"] . " " . $equipment[$i]["id_Eq"] . "  <br>";
			//echo "<li>" . $equipment[$i]["nama"] . "<ul>";
			$tulis = '<ul><li><a href="home.php?idEq=%d"><h2>%s</h2></a>'."\n";
			printf($tulis, $equipment[$i]["id_Eq"], $equipment[$i]["nama"] );

			$jmlAnak = count($group);
			if ($jmlAnak) {
				echo "<ul>";
				for ($j=0; $j<$jmlAnak; $j++) {
					if ($equipment[$i]["id_Eq"] == $group[$j]["id_eq"]) {
						$tulis = '<li><a href="home.php?idGr=%d" >%s</a></li>'."\n";
						printf($tulis, $group[$j]["id_gr"], $group[$j]["nama"]);
						//echo '<li><a href="?">' . $group[$j]["nama"] . '</a></li>';
					}
				}
			} else {
				echo "</li></ul>\n";
			}
			echo "</ul></li></ul>\n";
		}
	}
	
?>
	</div>	<!-- end div menu -->
</div> <!-- end div header -->

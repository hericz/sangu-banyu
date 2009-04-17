<!--html><head>
<title>Departemen</title>
</head>
<body-->

<?php
	require_once('database.php');
	//global $c_id_dept;
	//$c_id_dept= $_GET['id'];
	global $nDept;
	global $nPrsh;
	//echo "id dept  : " . $c_id_dept ."<br>";
?>

<div id="dept">
<?php
	global $dept;
	$dept = array();
//*
	//echo "testing php<br> " . $dept[0][0] . " " . $dept[0][1] . " <br>";
	$sql =	"select * from departemen";
	$data = db_query($sql) or die(mysql_error());
	while ($message_array = db_fetch_array($data)) {
		$i=0;
		$iddp = htmlspecialchars($message_array['id_dep']);
		$nama = htmlspecialchars($message_array['nama_dep']);
		$idpr = htmlspecialchars($message_array['id_pers']);
		$isi  = array("id_dep" => $iddp, "nama" => $nama, "id_pers" => $idpr);
		array_push($dept, $isi);
		$i++;
	}
	mysql_free_result($data);
	//echo "1: " . $dept[0]["nama"] . " " . $dept[0]["id_pers"] . "<br>";	//echo "2: " . $dept[1]["nama"] . " " . $dept[1]["id_pers"] . "<br>";
	//echo "3: " . $dept[2]["nama"] . " " . $dept[2]["id_pers"] . "<br>";	//echo "4: " . $dept[3]["nama"] . " " . $dept[3]["id_pers"] . "<br>";	
	
	global $prsh;
	$prsh = array();
	$sql =	"select * from perusahaan";
	$data = db_query($sql) or die(mysql_error());
	while ($message_array = db_fetch_array($data)) {
		$i=0;
		$idpr = htmlspecialchars($message_array['id_pers']);
		$nama = htmlspecialchars($message_array['nama_pers']);
		$almt = htmlspecialchars($message_array['alamat']);
		$isi  = array("id_pers" => $idpr, "nama" => $nama, "almt" => $almt);
		array_push($prsh, $isi);
		$i++;
	}
	mysql_free_result($data);
	//echo "1: " . $prsh[0]["nama"] . " " . $dept[0]["id_pers"] . "<br>"; 	//echo "2: " . $prsh[1]["nama"] . " " . $dept[1]["id_pers"] . "<br>";
	//echo "3: " . $prsh[2]["nama"] . " " . $dept[2]["id_pers"] . "<br>";	//echo "4: " . $dept[3]["nama"] . " " . $dept[3]["id_pers"] . "<br>";
	//echo "<br><br>";
//*/
?>	

<table border="0" bordercolor="black" cellpadding="1" cellspacing="0" width="500">
<tr><td width="200" valign="top">Pilih Perusahaan & Departemen</td><td>
<form name="formDept"><ul>
	<?php
	for($i=0; $i<count($prsh); $i++) {
		$tulis = '<li class="deptItem"> %s';
		//$tulis = '%s';
		printf($tulis,$prsh[$i]["nama"]);
		if (count($dept)) {
			?><ul> <?php
			for ($j=0; $j<count($dept); $j++) {
				if ($prsh[$i]["id_pers"] == $dept[$j]["id_pers"]) {
			?> 
				<input type="radio" name="dept" value="<?php  echo $dept[$j]["id_dep"]; ?>" 
				<?php 
					//if ($dept[$j]["id_dep"] == $c_id_dept) 
					if ($dept[$j]["id_dep"] == $_GET['id'])
					echo "checked";
					$nDept = $j;
					$nPrsh = $i;
				?>
				> <?php echo $dept[$j]["nama"] . "<br>";
				}
			}
			?> </ul> <?php
		}
		echo "</li>";
	}
?>

</ul></form>
</td></tr></table>

</div>
